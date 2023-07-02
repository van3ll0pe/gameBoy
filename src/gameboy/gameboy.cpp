#include <iostream>
#include <stdexcept>
#include "gameboy.hpp"
#include <ctime>

namespace GB
{
    GameBoy::GameBoy()
    {   
        this->cpu = new Cpu();

        if (this->cpu == nullptr)
            throw std::runtime_error("[Error] failed to create the CPU\n");

       try
       {
        this->cpu->connectBus(&this->bus);
       }
       catch (std::runtime_error e)
       {
        std::cout << e.what() << std::endl;
        delete this->cpu;
        throw std::runtime_error(e.what());
       }
    }

    GameBoy::~GameBoy()
    {
        if (this->cpu != nullptr)
            delete this->cpu;
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
        this->bus.write(starting_address++, 0x01);
        this->bus.write(starting_address++, 0xAA);
        this->bus.write(starting_address++, 0xFF);
        this->bus.write(starting_address++, 0x3E);
        this->bus.write(starting_address++, 0xF0);
        this->bus.write(starting_address++, 0x80);
    }
}