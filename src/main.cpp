#include <iostream>
#include "gameboy.hpp"
#include <stdexcept>

int
main()
{

    GB::GameBoy* gameboy;
    try {
        gameboy = new GB::GameBoy();

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