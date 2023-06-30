#pragma once
#ifndef __GAME_BOY__
#define __GAME_BOY__

#include "bus.hpp"
#include "component.hpp"
#include "cpu.hpp"

namespace GB
{
    class GameBoy
    {
        private:
            Bus bus {};
            Component*  cpu;
        
        public:
            GameBoy();
            ~GameBoy();
            //void start();
            
    };


}

#endif //__GAME_BOY__