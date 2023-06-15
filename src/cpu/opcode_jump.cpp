#include "cpu.hpp"

namespace GB
{
    void
    Cpu::JP(uint16_t nn)
    {
        this->PC = nn;
    }

    void
    Cpu::JP()
    {
        this->PC = ((this->H << 8) + this->L);
    }

    void
    Cpu::JP(bool condition, uint16_t nn)
    {
        if (condition) {
            JP(nn);
            this->cycles = 16;
        }
    }

    void
    Cpu::JR(int8_t d)
    {
        this->PC += d;
    }

    void
    Cpu::JR(bool condition, int8_t d)
    {
        if (condition) {
            JR(d);
            this->cycles = 12;
        }
    }

    void
    Cpu::CALL(uint16_t nn)
    {
        push_16b(this->PC);
        this->PC = nn;
    }

    void
    Cpu::CALL(bool condition, uint16_t nn)
    {
        if (condition) {
            CALL(nn);
            this->cycles = 24;
        }
    }

    void
    Cpu::RET()
    {
        this->PC = pull_16b();
    }

    void
    Cpu::RET(bool condition)
    {
        if (condition) {
            RET();
            this->cycles = 20;
        }
    }

    void
    Cpu::RETI()
    {
        RET();
        this->IME = 1;
    }

    void
    Cpu::RST(uint8_t n)
    {
        CALL((uint16_t)n);
    }


}