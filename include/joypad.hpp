#pragma once
#ifndef __JOYPAD_HPP
#define __JOYPAD_HPP

#include "component.hpp"

namespace GB
{
    class Joypad : public Component
    {
        public:
            Joypad();
            ~Joypad();
            void getInput();
            void updateInput();
        
        private:
            bool button_A;          //if pressed -> true
            bool button_B;          //if pressed -> true
            bool button_arrow_up;   //if pressed -> true
            bool button_arrow_down; //if pressed -> true
            bool button_arrow_left; //if pressed -> true
            bool button_arrow_right;    //if pressed -> true
            bool button_select;         //if pressed -> true
            bool button_start;          //if pressed -> true
    };
}

#endif //__JOYPAD_HPP