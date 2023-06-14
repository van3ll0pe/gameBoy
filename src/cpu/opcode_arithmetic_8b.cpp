#include "cpu.hpp"

namespace GB
{
    void
    Cpu::ADD(uint8_t rn)
    {
        uint16_t res = this->A + rn;
        uint8_t hc = (this->A & 0xF) + (rn & 0xF);

        this->A = (res & 0xFF);

        check_flag(ZERO_FLAG, (this->A == 0));
        clear_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
        check_flag(CARRY_FLAG, (res & 0x100));
    }

    void
    Cpu::ADD(uint16_t HL)
    {
        uint16_t res = this->A + read(HL);
        uint8_t hc = (this->A & 0xF) + (read(HL) & 0xF);

        this->A = (res & 0xFF);

        check_flag(ZERO_FLAG, (this->A == 0));
        clear_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
        check_flag(CARRY_FLAG, (res & 0x100));
    }

    void
    Cpu::ADC(uint8_t rn)
    {
        uint16_t res = this->A + rn + get_flag(CARRY_FLAG);
        uint8_t hc = (this->A & 0xF) + (rn & 0xF) + get_flag(CARRY_FLAG);

        this->A = (res & 0xFF);

        check_flag(ZERO_FLAG, (this->A == 0));
        clear_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
        check_flag(CARRY_FLAG, (res & 0x100));
    }

    void
    Cpu::ADC(uint16_t HL)
    {
        uint16_t res = this->A + read(HL) + get_flag(CARRY_FLAG);
        uint8_t hc = (this->A & 0xF) + (read(HL) & 0xF) + get_flag(CARRY_FLAG);

        this->A = (res & 0xFF);

        check_flag(ZERO_FLAG, (this->A == 0));
        clear_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
        check_flag(CARRY_FLAG, (res & 0x100));
    }

    void
    Cpu::SUB(uint8_t rn)
    {
        uint16_t res = this->A - rn;
        uint8_t hc = (this->A & 0xF) - (rn & 0xF);

        this->A = (res & 0xFF);

        check_flag(ZERO_FLAG, (this->A == 0));
        set_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
        check_flag(CARRY_FLAG, (res & 0x100));
    }

    void
    Cpu::SUB(uint16_t HL)
    {
        uint16_t res = this->A - read(HL);
        uint8_t hc = (this->A & 0xF) - (read(HL) & 0xF);

        this->A = (res & 0xFF);

        check_flag(ZERO_FLAG, (this->A == 0));
        set_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
        check_flag(CARRY_FLAG, (res & 0x100));
    }

    void
    Cpu::SBC(uint8_t rn)
    {
        uint16_t res = this->A - rn - get_flag(CARRY_FLAG);
        uint8_t hc = (this->A & 0xF) - (rn & 0xF) - get_flag(CARRY_FLAG);

        this->A = (res & 0xFF);

        check_flag(ZERO_FLAG, (this->A == 0));
        set_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
        check_flag(CARRY_FLAG, (res & 0x100));
    }

    void
    Cpu::SBC(uint16_t HL)
    {
        uint16_t res = this->A - read(HL) - get_flag(CARRY_FLAG);
        uint8_t hc = (this->A & 0xF) - (read(HL) & 0xF) - get_flag(CARRY_FLAG);

        this->A = (res & 0xFF);

        check_flag(ZERO_FLAG, (this->A == 0));
        set_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
        check_flag(CARRY_FLAG, (res & 0x100));
    }

    void
    Cpu::AND(uint8_t rn)
    {
        this->A &= rn;

        check_flag(ZERO_FLAG, (this->A == 0));
        clear_flag(SUBSTRACT_FLAG);
        set_flag(HALF_CARRY_FLAG);
        clear_flag(CARRY_FLAG);
    }

    void
    Cpu::AND(uint16_t HL)
    {
        this->A &= read(HL);

        check_flag(ZERO_FLAG, (this->A == 0));
        clear_flag(SUBSTRACT_FLAG);
        set_flag(HALF_CARRY_FLAG);
        clear_flag(CARRY_FLAG);
    }

    void
    Cpu::XOR(uint8_t rn)
    {
        this->A ^= rn;

        check_flag(ZERO_FLAG, (this->A == 0));
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        clear_flag(CARRY_FLAG);
    }

    void
    Cpu::XOR(uint16_t HL)
    {
        this->A ^= read(HL);

        check_flag(ZERO_FLAG, (this->A == 0));
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        clear_flag(CARRY_FLAG);
    }

    void
    Cpu::OR(uint8_t rn)
    {
        this->A |= rn;

        check_flag(ZERO_FLAG, (this->A == 0));
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        clear_flag(CARRY_FLAG);
    }

    void
    Cpu::OR(uint16_t HL)
    {
        this->A |= read(HL);

        check_flag(ZERO_FLAG, (this->A == 0));
        clear_flag(SUBSTRACT_FLAG);
        clear_flag(HALF_CARRY_FLAG);
        clear_flag(CARRY_FLAG);
    }

    void
    Cpu::CP(uint8_t rn)
    {
        uint16_t res = this->A - rn;
        uint8_t hc = (this->A & 0xF) - (rn & 0xF);

        check_flag(ZERO_FLAG, ((res & 0xFF) == 0));
        set_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
        check_flag(CARRY_FLAG, (res & 0x100));
    }

    void
    Cpu::CP(uint16_t HL)
    {
        uint16_t res = this->A - read(HL);
        uint8_t hc = (this->A & 0xF) - (read(HL) & 0xF);

        check_flag(ZERO_FLAG, ((res & 0xFF) == 0));
        set_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
        check_flag(CARRY_FLAG, (res & 0x100));
    }

    void
    Cpu::INC(uint8_t &r)
    {
        uint8_t res = r + 1;
        uint8_t hc = (r & 0xF) + 1;
        
        r = res;

        check_flag(ZERO_FLAG, (r == 0));
        clear_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
    }

    void
    Cpu::INC(uint16_t HL)
    {
        uint8_t res = read(HL) + 1;
        uint8_t hc = (read(HL) & 0xF) + 1;

        write(HL, res);

        check_flag(ZERO_FLAG, (res == 0));
        clear_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
    }

    void
    Cpu::DEC(uint8_t &r)
    {
        uint8_t res = r - 1;
        uint8_t hc = (r & 0xF) - 1;

        r = res;

        check_flag(ZERO_FLAG, (r == 0));
        set_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
    }

    void
    Cpu::DEC(uint16_t HL)
    {
        uint8_t res = read(HL) - 1;
        uint8_t hc = (read(HL) & 0xF) - 1;

        write(HL, res);

        check_flag(ZERO_FLAG, (res == 0));
        set_flag(SUBSTRACT_FLAG);
        check_flag(HALF_CARRY_FLAG, (hc & 0x10));
    }

    void
    Cpu::DAA()
    {

        if (get_flag(SUBSTRACT_FLAG) == 0) { //if the last operation was addition

            if (((this->A & 0xF) > 0x9) || get_flag(HALF_CARRY_FLAG)) //if the 4 lower bits isn't BCD or if HALF CARRY flag is SET
                this->A += 0x06;
            
            if (((this->A & 0xF0) > 0x90) || get_flag(CARRY_FLAG)) //if the 4 upper bits isn't BCD or CARRY flag is SET
            { 
                this->A += 0x60;
                set_flag(CARRY_FLAG);
            } else
            {
                clear_flag(CARRY_FLAG);
            }
            
        }
        else { //if the last operation was substraction

            if (((this->A & 0xF) > 0x9) || get_flag(HALF_CARRY_FLAG)) //if the 4 lower bits isn't BCD or if HALF CARRY flag is SET
                this->A -= 0x06;
            
            if (((this->A & 0xF0) > 0x90) || get_flag(CARRY_FLAG))  //if the 4 upper bits isn't BCD or CARRY flag is SET
            {
                this->A -= 0x60;
                set_flag(CARRY_FLAG);
            } else
            {
                clear_flag(CARRY_FLAG);
            }
        }


        check_flag(ZERO_FLAG, (this->A == 0));
        clear_flag(HALF_CARRY_FLAG);
    }

    void
    Cpu::CPL()
    {
        this->A ^= 0xFF;

        set_flag(SUBSTRACT_FLAG);
        set_flag(HALF_CARRY_FLAG);
    }
}