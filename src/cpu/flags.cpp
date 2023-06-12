#include "cpu.hpp"


namespace GB
{
    void
    Cpu::set_flag(uint8_t flag)
    {
        this->F |= flag;
    }

    void
    Cpu::clear_flag(uint8_t flag)
    {
        this->F &= (~flag);
    }

    uint8_t
    Cpu::get_flag(uint8_t flag)
    {
        return (this->F & flag) ? 1 : 0;
    }

    void
    Cpu::check_flag(uint8_t flag, bool condition)
    {
        if (condition)
            set_flag(flag);
        else
            clear_flag(flag);
    }
}