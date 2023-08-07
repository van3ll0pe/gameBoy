#include <iostream>
#include "gameboy.hpp"
#include <stdexcept>
#include <memory>

#include <SDL2/SDL.h>

int
main()
{   
    //INITIALIZATION OF SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        return 1;


    std::unique_ptr<GB::GameBoy> gameboy;
    try {
        gameboy = std::make_unique<GB::GameBoy>();

    }
    catch(std::runtime_error e)
    {
        return 1;
    }

    std::cout << "STARTED WITH NO FAILURE" << std::endl;
    gameboy->load_cartridge();
    gameboy->run();


    SDL_Quit();

    return 0;
}