#pragma once
#ifndef __GAME_BOY__
#define __GAME_BOY__

#include <memory>

#include "bus.hpp"
#include "cpu.hpp"

namespace GB
{
    class GameBoy
    {
        private:
            Bus bus {};
            Cpu cpu {};
        
        public:
            GameBoy();
            ~GameBoy();
            void run();
            void load_cartridge();
            
    };


}

#endif //__GAME_BOY__