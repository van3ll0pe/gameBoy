#include <iostream>
#include <stdexcept>
#include "gameboy.hpp"
#include <ctime>

namespace GB
{
    GameBoy::GameBoy()
    {
        this->is_open = true;
    }

    GameBoy::~GameBoy()
    {
    }

    void
    GameBoy::connect()
    {
        try
       {
        this->cpu.connectBus(&this->bus);
        this->ppu.connectBus(&this->bus);
       }
       catch (std::runtime_error e)
       {
        std::cout << e.what() << std::endl;
        throw std::runtime_error(e.what());
       }
    }

    void
    GameBoy::run()
    {
        unsigned int cyclesByFrame = 4194304 / 60; //nombre de cycle machine par rafraichissement d'écran

        unsigned int cumuledCycle = 0;
        SDL_Event event;


        while(this->is_open)
        {
            while(SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    this->is_open = false;
            }

            ppu.clear_screen();
            //ppu.draw();
            ppu.display();

            while(cumuledCycle < cyclesByFrame)
            {
                while(SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT) {
                        this->is_open = false;
                        return;
                    }
                }

                ppu.clear_screen();
                //ppu.draw();
                ppu.display();

                cpu.fetch_opcode();

                #ifdef DEBUG_INFO_CPU
                    cpu.display_registers();
                    printf("\n");
                #endif//DEBUG_INFO_CPU
                cpu.execute_opcode();

                cumuledCycle += cpu.get_cycles();
                cpu.handle_timer();
                cpu.handle_interrupt();
            }
            
            cumuledCycle = 0;

            


        }


    }

    void
    GameBoy::load_cartridge()
    {
        uint16_t starting_address = 0x0100;
        this->bus.write(starting_address++, 0x26);
        this->bus.write(starting_address++, 0xFF);
        this->bus.write(starting_address++, 0x2E);
        this->bus.write(starting_address++, 0x07);
        this->bus.write(starting_address++, 0x36);
        this->bus.write(starting_address++, 0x06);
        this->bus.write(starting_address++, 0x00);
        this->bus.write(starting_address++, 0xC6);
        this->bus.write(starting_address++, 0x01);
        this->bus.write(starting_address++, 0xC3);
        this->bus.write(starting_address++, 0x00);
        this->bus.write(starting_address++, 0x01);

        
    }
}