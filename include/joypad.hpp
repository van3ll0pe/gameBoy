#pragma once
#ifndef __JOYPAD_HPP
#define __JOYPAD_HPP

#include "component.hpp"
#include <SDL2/SDL.h>

namespace GB
{
    class Joypad : public Component
    {
        private:
            uint8_t* keyboard;
        public:
            Joypad();
            ~Joypad();
            void handle_input();
    };
}

#endif //__JOYPAD_HPP