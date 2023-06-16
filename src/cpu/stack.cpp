#include "cpu.hpp"


namespace GB
{
    void
    Cpu::push_8b(uint8_t data)
    {
        write(this->SP--, data);
    }

    uint8_t
    Cpu::pull_8b()
    {
        return read(++this->SP);
    }

    void
    Cpu::push_16b(uint16_t data)
    {
        write(this->SP--, (data & 0xFF00) >> 8);    //push high byte
        write(this->SP--, (data & 0x00FF));         //push low byte
    }

    uint16_t
    Cpu::pull_16b()
    {
        uint16_t data = read(++this->SP);   //get low byte
        data |= (read(++this->SP) << 8);    //get high byte

        return data;
    }
}