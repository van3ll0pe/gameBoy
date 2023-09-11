#pragma once
#ifndef __GAME_BOY__
#define __GAME_BOY__

#include <memory>

#include "bus.hpp"
#include "cpu.hpp"
#include "ppu.hpp"

namespace GB
{
    class GameBoy
    {
        private:
            Bus bus {};
            Cpu cpu {};
            //Joypad joypad {};
            Ppu ppu {};

            bool is_open;
        
        public:
            GameBoy();
            ~GameBoy();
            void connect();
            void run();
            void load_cartridge();
            
    };


}

#endif //__GAME_BOY__