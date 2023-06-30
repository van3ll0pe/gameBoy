#include "joypad.hpp"

namespace GB
{
    Joypad::Joypad() : Component()
    {
        this->button_A = false;
        this->button_B = false;
        this->button_select = false;
        this->button_start = false;
        this->button_arrow_up = false;
        this->button_arrow_down = false;
        this->button_arrow_left = false;
        this->button_arrow_right = false;
    }

}