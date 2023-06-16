#include "cpu.hpp"

namespace GB
{
    void
    Cpu::CCF()
    {
        bool carry = get_flag(CARRY_FLAG) ^ 1; //get_flag -> 1 / O ^ 1 -> 0 / 1

        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        check_flag(CARRY_FLAG, carry);
    }

    void
    Cpu::SCF()
    {
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        set_flag(CARRY_FLAG);
    }

    void
    Cpu::NOP()
    {
        return ;
    }

    void
    Cpu::DI() {
        this->IME = 0;
    }

    void
    Cpu::EI()
    {
        this->IME = 1;
    }

    void
    Cpu::STOP()
    {
        this->stopped = 1;
    }

    void
    Cpu::HALT()
    {
        this->halted = 1;
    }
}