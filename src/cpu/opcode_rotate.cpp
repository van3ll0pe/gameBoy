#include "cpu.hpp"

namespace GB
{
    void
    Cpu::RLCA()
    {
        bool bit7 = this->A & BIT_7; //if the bit 7 of A register is set (true) else false

        this->A <<= 1;
        
        if (bit7) //if true, set 1 to the bit 0 of A
            this->A |= BIT_0;
        
        clear_flag(ZERO_FLAG);
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        check_flag(CARRY_FLAG, bit7);
    }

    void
    Cpu::RLA()
    {
        bool bit7 = this->A & BIT_7;

        this->A <<= 1;

        this->A |= get_flag(CARRY_FLAG); //set the bit0 at 1 by carry

        clear_flag(ZERO_FLAG);
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        check_flag(CARRY_FLAG, bit7);
    }

    void
    Cpu::RRCA()
    {
        bool bit0 = this->A & BIT_0;

        this->A >>= 1;

        if (bit0) //set the bit7 of A, no need to put a 0 because already a 0
            this->A |= BIT_7;
        
        clear_flag(ZERO_FLAG);
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        check_flag(CARRY_FLAG, bit0);
    }

    void
    Cpu::RRA()
    {
        bool bit0 = this->A & BIT_0;

        this->A >>= 1;

        this->A |= (get_flag(CARRY_FLAG) << 7); //set 1 tot the bit7 of A is the carry flag is set

        clear_flag(ZERO_FLAG);
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        check_flag(CARRY_FLAG, bit0);
    }

    void
    Cpu::RLC(uint8_t &r)
    {
        bool bit7 = r & BIT_7; //if the bit 7 of A register is set (true) else false

        r <<= 1;
        
        if (bit7) //if true, set 1 to the bit 0 of A, else, already a 0
            r |= BIT_0;

        check_flag(ZERO_FLAG, (r == 0));
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        check_flag(CARRY_FLAG, bit7);
    }

    void
    Cpu::RLC(uint16_t HL)
    {
        uint8_t m = read(HL);
        RLC(m);
        write(HL, m);
    }

    void
    Cpu::RL(uint8_t &r)
    {
        bool bit7 = r & BIT_7;

        r <<= 1;
        r |= get_flag(CARRY_FLAG);

        check_flag(ZERO_FLAG, (r == 0));
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        check_flag(CARRY_FLAG, bit7);
    }

    void
    Cpu::RL(uint16_t HL)
    {
        uint8_t m = read(HL);
        RL(m);
        write(HL, m);
    }

    void
    Cpu::RRC(uint8_t &r)
    {
        bool bit0 = r & BIT_0;

        r >>= 1;

        if (bit0)
            r |= BIT_7;
        
        check_flag(ZERO_FLAG, (r == 0));
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        check_flag(CARRY_FLAG, bit0);
    }

    void
    Cpu::RRC(uint16_t HL)
    {
        uint8_t m = read(HL);
        RRC(m);
        write(HL, m);
    }

    void
    Cpu::RR(uint8_t &r)
    {
        bool bit0 = r & BIT_0;

        r >>= 1;
        r |= (get_flag(CARRY_FLAG) << 7);

        check_flag(ZERO_FLAG, (r == 0));
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        check_flag(CARRY_FLAG, bit0);
    }

    void
    Cpu::RR(uint16_t HL)
    {
        uint8_t m = read(HL);
        RR(m);
        write(HL, m);
    }

    void
    Cpu::SLA(uint8_t &r)
    {
        bool bit7 = r & BIT_7;

        r <<= 1;

        check_flag(ZERO_FLAG, (r == 0));
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        check_flag(CARRY_FLAG, bit7);
    }

    void
    Cpu::SLA(uint16_t HL)
    {
        uint8_t m = read(HL);
        SLA(m);
        write(HL, m);
    }

    void
    Cpu::SWAP(uint8_t &r)
    {
        uint8_t htmp = (r & 0xF0) >> 4; //tmp save the 4 high bits of the register, and go to 4 lower bits
        
        r <<= 4; //the 4 lower bits become 4 high bits
        r |= htmp; //add the new 4 lower bits

        check_flag(ZERO_FLAG, (r == 0));
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        clear_flag(CARRY_FLAG);
    }

    void
    Cpu::SWAP(uint16_t HL)
    {
        uint8_t m = read(HL);
        SWAP(m);
        write(HL, m);
    }

    void
    Cpu::SRA(uint8_t &r)
    {
        bool bit7 = r & BIT_7;
        bool bit0 = r & BIT_0;

        r >>= 1;

        if (bit7)
            r |= BIT_7;
        
        check_flag(ZERO_FLAG, (r == 0));
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        check_flag(CARRY_FLAG, bit0);
    }
    
    void
    Cpu::SRA(uint16_t HL)
    {
        uint8_t m = read(HL);
        SRA(m);
        write(HL, m);
    }

    void
    Cpu::SRL(uint8_t &r)
    {
        bool bit0 = r & BIT_0;

        r >>= 1;

        check_flag(ZERO_FLAG, (r == 0));
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        check_flag(CARRY_FLAG, bit0);
    }

    void
    Cpu::SRL(uint16_t HL)
    {
        uint8_t m = read(HL);
        SRL(m);
        write(HL, m);
    }
}
