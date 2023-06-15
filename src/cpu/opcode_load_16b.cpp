#include "cpu.hpp"

namespace GB
{
    void
    Cpu::LD_SP(uint16_t n)
    {
        this->SP = n;
    }

    void
    Cpu::LD(uint8_t &hr, uint8_t &lr, uint16_t n)
    {
        hr = (n & 0xFF00) >> 8;
        lr = (n & 0xFF);
    }

    void
    Cpu::LD_a16(uint16_t a16)
    {
        write(a16, (this->SP & 0xFF));
        write((a16 + 1), (this->SP & 0xFF00) >> 8);
    }

    void
    Cpu::LD(uint16_t &rr, uint16_t rn)
    {
        rr = rn;
    }

    void
    Cpu::PUSH(uint16_t rr)
    {
        push_16b(rr);
    }

    void
    Cpu::POP(uint8_t &hr, uint8_t &lr)
    {
        uint16_t rr = pull_16b();

        hr = (rr & 0xFF00) >> 8;
        lr = (rr & 0x00FF); 
    }
}