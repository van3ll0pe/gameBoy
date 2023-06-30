#include <iostream>
#include "gameboy.hpp"
#include <stdexcept>

int
main()
{
    try {
        GB::GameBoy gameboy {};

    }
    catch(std::runtime_error e)
    {
        return 1;
    }

    std::cout << "everything is ok !" << std::endl;

    return 0;
}