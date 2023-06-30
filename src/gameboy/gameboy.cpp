#include <iostream>
#include <stdexcept>
#include "gameboy.hpp"

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
}