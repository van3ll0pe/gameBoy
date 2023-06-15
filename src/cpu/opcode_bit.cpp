#include "cpu.hpp"

namespace GB
{
    void
    Cpu::BIT(uint8_t b, uint8_t r)
    {
        bool res = b & r;

        check_flag(ZERO_FLAG, (!res)); //Z is set if res = false
        clear_flag(SUBSTRACT_FLAG);
        set_flag(HALF_CARRY_FLAG);
    }

    void
    Cpu::BIT(uint8_t b, uint16_t HL)
    {
        uint8_t m = read(HL);
        BIT(b, m);
    }

    void
    Cpu::SET(uint8_t b, uint8_t &r)
    {
        r |= b;
    }

    void
    Cpu::SET(uint8_t b, uint16_t HL)
    {
        uint8_t m = read(HL);
        SET(b, m);
        write(HL, m);
    }

    void
    Cpu::RES(uint8_t b, uint8_t &r)
    {
        r &= (~b);
    }

    void
    Cpu::RES(uint8_t b, uint16_t HL)
    {
        uint8_t m = read(HL);
        RES(b, m);
        write(HL, m);
    }
}
