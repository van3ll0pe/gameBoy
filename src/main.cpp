#include <iostream>
#include "gameboy.hpp"
#include <stdexcept>
#include <memory>

int
main()
{

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



    return 0;
}