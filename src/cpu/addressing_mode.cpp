#include "cpu.hpp"

namespace GB
{
    void
    Cpu::IMPLIED()
    {
        return ;
    }

    uint8_t
    Cpu::IMMEDIATE_8b()
    {
        return read(this->PC++);
    }

    uint16_t
    Cpu::IMMEDIATE_16b()
    {
        uint16_t data = 0;
        data = read(this->PC++);            //low bytes
        data |= (read(this->PC++) << 8);    //high bytes (little endian)

        return data;
    }
}