#include "cpu.hpp"


namespace GB
{
    void
    Cpu::ADD_16b(uint16_t rr)
    {
        uint16_t HL = (this->H << 8) + this->L;

        uint32_t res = HL + rr;
        uint16_t hc = (HL & 0xFFF) + (rr & 0xFFF);

        HL = (res & 0xFFFF);

        this->H = (HL & 0xFF00) >> 8;
        this->L = (HL & 0x00FF);

        clear_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x1000));
        check_flag(CARRY_FLAG, (res & 0x10000));
    }

    uint16_t
    Cpu::INC_16b(uint16_t rr)
    {
        return rr + 1;
    }

    uint16_t
    Cpu::DEC_16b(uint16_t rr)
    {
        return rr - 1;
    }

    void
    Cpu::ADD_SPe(int8_t n)
    {
        uint16_t res = this->SP + n;
        uint8_t hc = (this->SP & 0xF) + (n & 0xF);

        this->SP = res;

        clear_flag(ZERO_FLAG);
        clear_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
        check_flag(CARRY_FLAG, (res & 0x100));
    }

    void
    Cpu::LD_HLSPe(int8_t n)
    {
        uint16_t res = this->SP + n;
        uint8_t hc = (this->SP & 0xF) + (n & 0xF);

        this->H = (res & 0xFF00) >> 8;
        this->L = (res & 0x00FF);

        clear_flag(ZERO_FLAG);
        clear_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
        check_flag(CARRY_FLAG, (res & 0x100));
    }


}