#include <iostream>
#include "gameboy.hpp"
#include <stdexcept>
#include <memory>

#include <SDL2/SDL.h>

int
main(int argc, char** argv)
{   
    GB::GameBoy gameboy {};

    try {
        gameboy.connect();
    }
    catch(std::runtime_error e)
    {
        return 1;
    }

    std::cout << "STARTED WITH NO FAILURE" << std::endl;
    gameboy.load_cartridge();
    gameboy.run();

    return 0;

    
}