#include "cpu.hpp"


namespace GB
{
    void
    Cpu::LD(uint8_t &r, uint8_t rn)
    {
        r = rn;
    }

    void
    Cpu::LD(uint8_t &r, uint16_t rr)
    {
        r = read(rr);
    }

    void
    Cpu::LD(uint16_t rr, uint8_t rn)
    {
        write(rr, rn);
    }

    void
    Cpu::LD_RIO(uint8_t rn)
    {
        this->A = read((0xFF00 + rn));
    }

    void
    Cpu::LD_WIO(uint8_t rn)
    {
        write((0xFF00 + rn), this->A);
    }

}