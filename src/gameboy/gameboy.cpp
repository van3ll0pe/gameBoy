#include <iostream>
#include <stdexcept>
#include "gameboy.hpp"
#include <ctime>

namespace GB
{
    GameBoy::GameBoy()
    {

        this->cpu = std::make_unique<Cpu>();

       try
       {
        this->cpu->connectBus(&this->bus);
       }
       catch (std::runtime_error e)
       {
        std::cout << e.what() << std::endl;
        throw std::runtime_error(e.what());
       }
    }

    GameBoy::~GameBoy()
    {
    }

    void
    GameBoy::run()
    {
        while(true)
        {
            cpu->run();
            clock_t timer = clock();
            clock_t temp = timer;
            while(timer <= temp + 10000){
                timer = clock();
            }
        }
    }

    void
    GameBoy::load_cartridge()
    {
        uint16_t starting_address = 0x0100;
        this->bus.write(starting_address++, 0xC6);
        this->bus.write(starting_address++, 0x01);
        this->bus.write(starting_address++, 0xC3);
        this->bus.write(starting_address++, 0x00);
        this->bus.write(starting_address++, 0x01);
    }
}