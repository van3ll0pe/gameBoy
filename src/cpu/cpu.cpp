#include "cpu.hpp"
#include <stdexcept>
#include <iostream>
namespace GB
{
    Cpu::Cpu(): Component()
    {
        this->A = 0x1;
        this->B = 0;
        this->C = 0x13;
        this->D = 0;
        this->E = 0xD8;
        this->F = 0x80;
        this->H = 0x1;
        this->L = 0x4D;
        this->PC = 0x0100;
        this->SP = 0xFFFE;

        this->cycles = 0;
        this->IME = 0;
        this->stopped = 0;
        this->halted = 0;
    }

    Cpu::~Cpu() {}

    uint8_t
    Cpu::get_cycles()
    {
        return this->cycles;
    }

    bool
    Cpu::is_halted()
    {
       return (halted) ? true : false;
    }

    void
    Cpu::fetch_opcode()
    {
        #ifdef DEBUG_INFO_CPU
            printf("ADDRESS %04X : [opcode] %02X\n", this->PC, read(this->PC));
        #endif //DEBUG_INFO_CPU
        this->opcode = read(this->PC++);
    }

    void
    Cpu::execute_opcode()
    {

        switch(this->opcode)
        {   
            case 0x00:  //NOP
                        NOP();
                        this->cycles = 4;
                        break;

            case 0x01:  //LD BC, n16
                        LD(this->B, this->C, IMMEDIATE_16b());
                        this->cycles = 12;
                        break;

            case 0x02:  //LD (BC), A
                        LD((uint16_t)((this->B << 8) + this->C), this->A);
                        this->cycles = 8;
                        break;

            case 0x03:  //INC BC
                        INC_16b(this->B, this->C);
                        this->cycles = 8;
                        break;

            case 0x04:  //INC B
                        INC(this->B);
                        this->cycles = 4;
                        break;

            case 0x05:  //DEC B
                        DEC(this->B);
                        this->cycles = 4;
                        break;

            case 0x06:  //LD B, n8
                        LD(this->B, IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0x07:  //RLCA
                        RLCA();
                        this->cycles = 4;
                        break;

            case 0x08:  //LD (a16), SP
                        LD_a16(IMMEDIATE_16b());
                        this->cycles = 20;
                        break;

            case 0x09:  //ADD HL, BC
                        ADD_16b((uint16_t)((this->B << 8) + this->C));
                        this->cycles = 8;
                        break;

            case 0x0A:  //LD A, (BC)
                        LD(this->A, (uint16_t)((this->B << 8) + this->C));
                        this->cycles = 8;
                        break;

            case 0x0B:  //DEC BC
                        DEC_16b(this->B, this->C);
                        this->cycles = 8;
                        break;

            case 0x0C:  //INC C
                        INC(this->C);
                        this->cycles = 4;
                        break;

            case 0x0D:  //DEC C
                        DEC(this->C);
                        this->cycles = 4;
                        break;

            case 0x0E:  //LD C, n8
                        LD(this->C, IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0x0F:  //RRCA
                        RRCA();
                        this->cycles = 4;
                        break;

            case 0x10:  //STOP n8
                        STOP();
                        IMMEDIATE_8b();
                        this->cycles = 4;
                        break;

            case 0x11:  //LD DE, n16
                        LD(this->D, this->E, IMMEDIATE_16b());
                        this->cycles = 12;
                        break;

            case 0x12:  //LD (DE), A
                        LD((uint16_t)((this->D << 8) + this->E), this->A);
                        this->cycles = 8;
                        break;

            case 0x13:  //INC DE
                        INC_16b(this->D, this->E);
                        this->cycles = 8;
                        break;

            case 0x14:  //INC D
                        INC(this->D);
                        this->cycles = 4;
                        break;

            case 0x15:  //DEC D
                        DEC(this->D);
                        this->cycles = 4;
                        break;

            case 0x16:  //LD D, n8
                        LD(this->D, IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0x17:  //RLA
                        RLA();
                        this->cycles = 4;
                        break;

            case 0x18:  //JR e8
                        JR(IMMEDIATE_8b()); //IMMEDIATE returns uint8, but casted by JR which takes int8
                        this->cycles = 12;
                        break;

            case 0x19:  //ADD HL DE
                        ADD_16b((uint16_t)((this->D << 8) + this->E));
                        this->cycles = 8;
                        break;

            case 0x1A:  //LD A, (DE)
                        LD(this->A, (uint16_t)((this->D << 8) + this->E));
                        this->cycles = 8;
                        break;

            case 0x1B:  //DEC DE
                        DEC_16b(this->D, this->E);
                        this->cycles = 8;
                        break;

            case 0x1C:  //INC E
                        INC(this->E);
                        this->cycles = 4;
                        break;

            case 0x1D:  //DEC E
                        DEC(this->E);
                        this->cycles = 4;
                        break;

            case 0x1E:  //LD E, n8
                        LD(this->E, IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0x1F:  //RRA
                        RRA();
                        this->cycles = 4;
                        break;

            case 0x20:  //JR NZ, e8 (NZ not ZERO, so == 0 or != 1)
                        this->cycles = 8;
                        JR(CONDITION_NZ, IMMEDIATE_8b());
                        break;
                        
            case 0x21:  //LD HL, n16
                        LD(this->H, this->L, IMMEDIATE_16b());
                        this->cycles = 12;
                        break;

            case 0x22:  //LD (HL+), A
                        LD((uint16_t)((this->H << 8) + this->L), this->A);
                        INC_16b(this->H, this->L);
                        this->cycles = 8;
                        break;

            case 0x23:  //INC HL
                        INC_16b(this->H, this->L);
                        this->cycles = 8;
                        break;

            case 0x24:  //INC H
                        INC(this->H);
                        this->cycles = 4;
                        break;

            case 0x25:  //DEC H
                        DEC(this->H);
                        this->cycles = 4;
                        break;

            case 0x26:  //LD H, n8
                        LD(this->H, IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0x27:  //DAA
                        DAA();
                        this->cycles = 4;
                        break;

            case 0x28:  //JR Z, e8 (Z ZERO, so == 1 or != 0)
                        this->cycles = 8;
                        JR(CONDITION_Z, IMMEDIATE_8b());
                        break;

            case 0x29:  //ADD HL, HL
                        ADD_16b((uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0x2A:  //LD A, (HL+)
                        LD(this->A, (uint16_t)((this->H << 8) + this->L));
                        INC_16b(this->H, this->L);
                        this->cycles = 8;
                        break;

            case 0x2B:  //DEC HL
                        DEC_16b(this->H, this->L);
                        this->cycles = 8;
                        break;

            case 0x2C:  //INC L
                        INC(this->L);
                        this->cycles = 4;
                        break;

            case 0x2D:  //DEC L
                        DEC(this->L);
                        this->cycles = 4;
                        break;

            case 0x2E:  //LD L, n8
                        LD(this->L, IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0x2F:  //CPL
                        CPL();
                        this->cycles = 4;
                        break;

            case 0x30:  //JR NC, e8
                        this->cycles = 8;
                        JR(CONDITION_NC, IMMEDIATE_8b());
                        break;

            case 0x31:  //LD SP, n16
                        LD(this->SP, IMMEDIATE_16b());
                        this->cycles = 12;
                        break;

            case 0x32:  //LD (HL-), A
                        LD((uint16_t)((this->H << 8) + this->L), this->A);
                        DEC_16b(this->H, this->L);
                        this->cycles = 8;
                        break;

            case 0x33:  //INC SP
                        INC_16b(this->SP);
                        this->cycles = 8;
                        break;

            case 0x34:  //INC (HL)
                        INC((uint16_t)((this->H << 8) + this->L));
                        this->cycles = 12;
                        break;

            case 0x35:  //DEC (HL)
                        DEC((uint16_t)((this->H << 8) + this->L));
                        this->cycles = 12;
                        break;

            case 0x36:  //LD (HL), n8
                        LD((uint16_t)((this->H << 8) + this->L), IMMEDIATE_8b());
                        this->cycles = 12;
                        break;

            case 0x37:  //SCF
                        SCF();
                        this->cycles = 4;
                        break;

            case 0x38:  //JR C, e8
                        this->cycles = 8;
                        JR(CONDITION_C, IMMEDIATE_8b());
                        break;

            case 0x39:  //ADD HL, SP
                        ADD_16b(this->SP);
                        this->cycles = 8;
                        break;

            case 0x3A:  //LD A, (HL-)
                        LD(this->A, (uint16_t)((this->H << 8) + this->L));
                        DEC_16b(this->H, this->L);
                        this->cycles = 8;
                        break;

            case 0x3B:  //DEC SP
                        DEC_16b(this->SP);
                        this->cycles = 8;
                        break;

            case 0x3C:  //INC A
                        INC(this->A);
                        this->cycles = 4;
                        break;

            case 0x3D:  //DEC A
                        DEC(this->A);
                        this->cycles = 4;
                        break;

            case 0x3E:  //LD A, n8
                        LD(this->A, IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0x3F:  //CCF
                        CCF();
                        this->cycles = 4;
                        break;

            case 0x40:  //LD B, B
                        LD(this->B, this->B);
                        this->cycles = 4;
                        break;

            case 0x41:  //LD B, C
                        LD(this->B, this->C);
                        this->cycles = 4;
                        break;

            case 0x42:  //LD B, D
                        LD(this->B, this->D);
                        this->cycles = 4;
                        break;

            case 0x43:  //LD B, E
                        LD(this->B, this->E);
                        this->cycles = 4;
                        break;

            case 0x44:  //LD B, H
                        LD(this->B, this->H);
                        this->cycles = 4;
                        break;

            case 0x45:  //LD B, L
                        LD(this->B, this->L);
                        this->cycles = 4;
                        break;

            case 0x46:  //LD B, (HL)
                        LD(this->B, (uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0x47:  //LD B, A
                        LD(this->B, this->A);
                        this->cycles = 4;
                        break;

            case 0x48:  //LD C, B
                        LD(this->C, this->B);
                        this->cycles = 4;
                        break;

            case 0x49:  //LD C, C
                        LD(this->C, this->C);
                        this->cycles = 4;
                        break;

            case 0x4A:  //LD C, D
                        LD(this->C, this->D);
                        this->cycles = 4;
                        break;

            case 0x4B:  //LD C, E
                        LD(this->C, this->E);
                        this->cycles = 4;
                        break;

            case 0x4C:  //LD C, H
                        LD(this->C, this->H);
                        this->cycles = 4;
                        break;

            case 0x4D:  //LD C, L
                        LD(this->C, this->L);
                        this->cycles = 4;
                        break;

            case 0x4E:  //LD C, (HL)
                        LD(this->C, (uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0x4F:  //LD C, A
                        LD(this->C, this->A);
                        this->cycles = 4;
                        break;

            case 0x50:  //LD D, B
                        LD(this->D, this->B);
                        this->cycles = 4;
                        break;

            case 0x51:  //LD D, C
                        LD(this->D, this->C);
                        this->cycles = 4;
                        break;

            case 0x52:  //LD D, D
                        LD(this->D, this->D);
                        this->cycles = 4;
                        break;

            case 0x53:  //LD D, E
                        LD(this->D, this->E);
                        this->cycles = 4;
                        break;

            case 0x54:  //LD D, H
                        LD(this->D, this->H);
                        this->cycles = 4;
                        break;

            case 0x55:  //LD D, L
                        LD(this->D, this->L);
                        this->cycles = 4;
                        break;

            case 0x56:  //LD D, (HL)
                        LD(this->D, (uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0x57:  //LD D, A
                        LD(this->D, this->A);
                        this->cycles = 4;
                        break;

            case 0x58:  //LD E, B
                        LD(this->E, this->B);
                        this->cycles = 4;
                        break;

            case 0x59:  //LD E, C
                        LD(this->E, this->C);
                        this->cycles = 4;
                        break;

            case 0x5A:  //LD E, D
                        LD(this->E, this->D);
                        this->cycles = 4;
                        break;

            case 0x5B:  //LD E, E
                        LD(this->E, this->E);
                        this->cycles = 4;
                        break;

            case 0x5C:  //LD E, H
                        LD(this->E, this->H);
                        this->cycles = 4;
                        break;

            case 0x5D:  //LD E, L
                        LD(this->E, this->L);
                        this->cycles = 4;
                        break;

            case 0x5E:  //LD E, (HL)
                        LD(this->E, (uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0x5F:  //LD E, A
                        LD(this->E, this->A);
                        this->cycles = 4;
                        break;

            case 0x60:  //LD H, B
                        LD(this->H, this->B);
                        this->cycles = 4;
                        break;

            case 0x61:  //LD H, C
                        LD(this->H, this->C);
                        this->cycles = 4;
                        break;

            case 0x62:  //LD H, D
                        LD(this->H, this->D);
                        this->cycles = 4;
                        break;

            case 0x63:  //LD H, E
                        LD(this->H, this->E);
                        this->cycles = 4;
                        break;

            case 0x64:  //LD H, H
                        LD(this->H, this->H);
                        this->cycles = 4;
                        break;

            case 0x65:  //LD H, L
                        LD(this->H, this->L);
                        this->cycles = 4;
                        break;

            case 0x66:  //LD H, (HL)
                        LD(this->H, (uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0x67:  //LD H, A
                        LD(this->H, this->A);
                        this->cycles = 4;
                        break;

            case 0x68:  //LD L, B
                        LD(this->L, this->B);
                        this->cycles = 4;
                        break;

            case 0x69:  //LD L, C
                        LD(this->L, this->C);
                        this->cycles = 4;
                        break;

            case 0x6A:  //LD L, D
                        LD(this->L, this->D);
                        this->cycles = 4;
                        break;

            case 0x6B:  //LD L, E
                        LD(this->L, this->E);
                        this->cycles = 4;
                        break;

            case 0x6C:  //LD L, H
                        LD(this->L, this->H);
                        this->cycles = 4;
                        break;

            case 0x6D:  //LD L, L
                        LD(this->L, this->L);
                        this->cycles = 4;
                        break;

            case 0x6E:  //LD L, (HL)
                        LD(this->L, (uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0x6F:  //LD L, A
                        LD(this->L, this->A);
                        this->cycles = 4;
                        break;

            case 0x70:  //LD (HL), B
                        LD((uint16_t)((this->H << 8) + this->L), this->B);
                        this->cycles = 8;
                        break;

            case 0x71:  //LD (HL), C
                        LD((uint16_t)((this->H << 8) + this->L), this->C);
                        this->cycles = 8;
                        break;

            case 0x72:  //LD (HL), D
                        LD((uint16_t)((this->H << 8) + this->L), this->D);
                        this->cycles = 8;
                        break;

            case 0x73:  //LD (HL), E
                        LD((uint16_t)((this->H << 8) + this->L), this->E);
                        this->cycles = 8;
                        break;

            case 0x74:  //LD (HL), H
                        LD((uint16_t)((this->H << 8) + this->L), this->H);
                        this->cycles = 8;
                        break;

            case 0x75:  //LD (HL), L
                        LD((uint16_t)((this->H << 8) + this->L), this->L);
                        this->cycles = 8;
                        break;

            case 0x76:  //HALT
                        HALT();
                        this->cycles = 4;
                        break;

            case 0x77:  //LD (HL), A
                        LD((uint16_t)((this->H << 8) + this->L), this->A);
                        this->cycles = 8;
                        break;

            case 0x78:  //LD A, B
                        LD(this->A, this->B);
                        this->cycles = 4;
                        break;

            case 0x79:  //LD A, C
                        LD(this->A, this->C);
                        this->cycles = 4;
                        break;

            case 0x7A:  //LD A, D
                        LD(this->A, this->D);
                        this->cycles = 4;
                        break;

            case 0x7B:  //LD A, E
                        LD(this->A, this->E);
                        this->cycles = 4;
                        break;

            case 0x7C:  //LD A, H
                        LD(this->A, this->H);
                        this->cycles = 4;
                        break;

            case 0x7D:  //LD A, L
                        LD(this->A, this->L);
                        this->cycles = 4;
                        break;

            case 0x7E:  //LD A, (HL)
                        LD(this->A, (uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0x7F:  //LD A, A
                        LD(this->A, this->A);
                        this->cycles = 4;
                        break;

            case 0x80:  //ADD A, B
                        ADD(this->B);
                        this->cycles = 4;
                        break;

            case 0x81:  //ADD A, C
                        ADD(this->C);
                        this->cycles = 4;
                        break;

            case 0x82:  //ADD A, D
                        ADD(this->D);
                        this->cycles = 4;
                        break;

            case 0x83:  //ADD A, E
                        ADD(this->E);
                        this->cycles = 4;
                        break;

            case 0x84:  //ADD A, H
                        ADD(this->H);
                        this->cycles = 4;
                        break;

            case 0x85:  //ADD A, L
                        ADD(this->L);
                        this->cycles = 4;
                        break;

            case 0x86:  //ADD A, (HL)
                        ADD((uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0x87:  //ADD A, A
                        ADD(this->A);
                        this->cycles = 4;
                        break;

            case 0x88:  //ADC A, B
                        ADC(this->B);
                        this->cycles = 4;
                        break;

            case 0x89:  //ADC A, C
                        ADC(this->C);
                        this->cycles = 4;
                        break;

            case 0x8A:  //ADC A, D
                        ADC(this->D);
                        this->cycles = 4;
                        break;

            case 0x8B:  //ADC A, E
                        ADC(this->E);
                        this->cycles = 4;
                        break;

            case 0x8C:  //ADC A, H
                        ADC(this->H);
                        this->cycles = 4;
                        break;

            case 0x8D:  //ADC A, L
                        ADC(this->L);
                        this->cycles = 4;
                        break;

            case 0x8E:  //ADC A, (HL)
                        ADC((uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0x8F:  //ADC A, A
                        ADC(this->A);
                        this->cycles = 4;
                        break;

            case 0x90:  //SUB A, B
                        SUB(this->B);
                        this->cycles = 4;
                        break;

            case 0x91:  //SUB A, C
                        SUB(this->C);
                        this->cycles = 4;
                        break;

            case 0x92:  //SUB A, D
                        SUB(this->D);
                        this->cycles = 4;
                        break;

            case 0x93:  //SUB A, E
                        SUB(this->E);
                        this->cycles = 4;
                        break;

            case 0x94:  //SUB A, H
                        SUB(this->H);
                        this->cycles = 4;
                        break;

            case 0x95:  //SUB A, L
                        SUB(this->L);
                        this->cycles = 4;
                        break;

            case 0x96:  //SUB A, (HL)
                        SUB((uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0x97:  //SUB A, A
                        SUB(this->A);
                        this->cycles = 4;
                        break;

            case 0x98:  //SBC A, B
                        SBC(this->B);
                        this->cycles = 4;
                        break;

            case 0x99:  //SBC A, C
                        SBC(this->C);
                        this->cycles = 4;
                        break;

            case 0x9A:  //SBC A, D
                        SBC(this->D);
                        this->cycles = 4;
                        break;

            case 0x9B:  //SBC A, E
                        SBC(this->E);
                        this->cycles = 4;
                        break;

            case 0x9C:  //SBC A, H
                        SBC(this->H);
                        this->cycles = 4;
                        break;

            case 0x9D:  //SBC A, L
                        SBC(this->L);
                        this->cycles = 4;
                        break;

            case 0x9E:  //SBC A, (HL)
                        SBC((uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0x9F:  //SBC A, A
                        SBC(this->A);
                        this->cycles = 4;
                        break;

            case 0xA0:  //AND A, B
                        AND(this->B);
                        this->cycles = 4;
                        break;

            case 0xA1:  //AND A, C
                        AND(this->C);
                        this->cycles = 4;
                        break;

            case 0xA2:  //AND A, D
                        AND(this->D);
                        this->cycles = 4;
                        break;

            case 0xA3:  //AND A, E
                        AND(this->E);
                        this->cycles = 4;
                        break;

            case 0xA4:  //AND A, H
                        AND(this->H);
                        this->cycles = 4;
                        break;

            case 0xA5:  //AND A, L
                        AND(this->L);
                        this->cycles = 4;
                        break;

            case 0xA6:  //AND A, (HL)
                        AND((uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0xA7:  //AND A, A
                        AND(this->A);
                        this->cycles = 4;
                        break;

            case 0xA8:  //XOR A, B
                        XOR(this->B);
                        this->cycles = 4;
                        break;

            case 0xA9:  //XOR A, C
                        XOR(this->C);
                        this->cycles = 4;
                        break;

            case 0xAA:  //XOR A, D
                        XOR(this->D);
                        this->cycles = 4;
                        break;

            case 0xAB:  //XOR A, E
                        XOR(this->E);
                        this->cycles = 4;
                        break;

            case 0xAC:  //XOR A, H
                        XOR(this->H);
                        this->cycles = 4;
                        break;

            case 0xAD:  //XOR A, L
                        XOR(this->L);
                        this->cycles = 4;
                        break;

            case 0xAE:  //XOR A, (HL)
                        XOR((uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0xAF:  //XOR A, A
                        XOR(this->A);
                        this->cycles = 4;
                        break;
                        
            case 0xB0:  //OR A, B
                        OR(this->B);
                        this->cycles = 4;
                        break;

            case 0xB1:  //OR A, C
                        OR(this->C);
                        this->cycles = 4;
                        break;

            case 0xB2:  //OR A, D
                        OR(this->D);
                        this->cycles = 4;
                        break;

            case 0xB3:  //OR A, E
                        OR(this->E);
                        this->cycles = 4;
                        break;

            case 0xB4:  //OR A, H
                        OR(this->H);
                        this->cycles = 4;
                        break;

            case 0xB5:  //OR A, L
                        OR(this->L);
                        this->cycles = 4;
                        break;

            case 0xB6:  //OR A, (HL)
                        OR((uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0xB7:  //OR A, A
                        OR(this->A);
                        this->cycles = 4;
                        break;

            case 0xB8:  //CP A, B
                        CP(this->B);
                        this->cycles = 4;
                        break;

            case 0xB9:  //CP A, C
                        CP(this->C);
                        this->cycles = 4;
                        break;

            case 0xBA:  //CP A, D
                        CP(this->D);
                        this->cycles = 4;
                        break;

            case 0xBB:  //CP A, E
                        CP(this->E);
                        this->cycles = 4;
                        break;

            case 0xBC:  //CP A, H
                        CP(this->H);
                        this->cycles = 4;
                        break;

            case 0xBD:  //CP A, L
                        CP(this->L);
                        this->cycles = 4;
                        break;

            case 0xBE:  //CP A, (HL)
                        CP((uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0xBF:  //CP A, A
                        CP(this->A);
                        this->cycles = 4;
                        break;

            case 0xC0:  //RET NZ
                        this->cycles = 8;
                        RET(CONDITION_NZ);
                        break;
                        
            case 0xC1:  //POP BC
                        POP(this->B, this->C);
                        this->cycles = 12;
                        break;

            case 0xC2:  //JP NZ, a16
                        this->cycles = 12;
                        JP(CONDITION_NZ, IMMEDIATE_16b());
                        break;

            case 0xC3:  //JP a16
                        JP(IMMEDIATE_16b());
                        this->cycles = 16;
                        break;

            case 0xC4:  //CALL NZ, a16
                        this->cycles = 12;
                        CALL(CONDITION_NZ, IMMEDIATE_16b());
                        break;

            case 0xC5:  //PUSH BC
                        PUSH((uint16_t)((this->B << 8) + this->C));
                        this->cycles = 16;
                        break;

            case 0xC6:  //ADD A, n8
                        ADD(IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0xC7:  //RST 0000
                        RST(0x00);
                        this->cycles = 16;
                        break;

            case 0xC8:  //RET Z
                        this->cycles = 8;
                        RET(CONDITION_Z);
                        break;

            case 0xC9:  //RET
                        RET();
                        this->cycles = 16;
                        break;

            case 0xCA:  //JP Z, a16
                        this->cycles = 12;
                        JP(CONDITION_Z, IMMEDIATE_16b());
                        break;

            case 0xCB:  //PREFIX CB
                        this->cycles = 4;
                        fetch_opcode();
                        execute_opcode_CB();
                        break;

            case 0xCC:  //CALL Z, a16
                        this->cycles = 12;
                        CALL(CONDITION_Z, IMMEDIATE_16b());
                        break;
                        
            case 0xCD:  //CALL a16
                        CALL(IMMEDIATE_16b());
                        this->cycles = 24;
                        break;

            case 0xCE:  //ADC A, n8
                        ADC(IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0xCF:  //RST 0008
                        RST(0x08);
                        this->cycles = 16;
                        break;

            case 0xD0:  //RET NC
                        this->cycles = 8;
                        RET(CONDITION_NC);
                        break;

            case 0xD1:  //POP DE
                        POP(this->D, this->E);
                        this->cycles = 12;
                        break;

            case 0xD2:  //JP NC, a16
                        this->cycles = 12;
                        JP(CONDITION_NC, IMMEDIATE_16b());
                        break;

            case 0xD4:  //CALL NC, a16
                        this->cycles = 12;
                        CALL(CONDITION_NC, IMMEDIATE_16b());
                        break;

            case 0xD5:  //PUSH DE
                        PUSH((uint16_t)((this->D << 8) + this->E));
                        this->cycles = 16;
                        break;

            case 0xD6:  //SUB A, n8
                        SUB(IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0xD7:  //RST 0x0010
                        RST(0x10);
                        this->cycles = 16;
                        break;

            case 0xD8:  //RET C
                        this->cycles = 8;
                        RET(CONDITION_C);
                        break;

            case 0xD9:  //RETI
                        RETI();
                        this->cycles = 16;
                        break;

            case 0xDA:  //JP C, a16
                        this->cycles = 12;
                        JP(CONDITION_C, IMMEDIATE_16b());
                        break;

            case 0xDC:  //CALL C, a16
                        this->cycles = 12;
                        CALL(CONDITION_C, IMMEDIATE_16b());
                        break;

            case 0xDE:  //SBC A, n8
                        SBC(IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0xDF:  //RST 0x0018
                        RST(0x18);
                        this->cycles = 16;
                        break;

            case 0xE0:  //LDH (0xFF00 + a8), A
                        LD_WIO(IMMEDIATE_8b());
                        this->cycles = 12;
                        break;

            case 0xE1:  //POP HL
                        POP(this->H, this->L);
                        this->cycles = 12;
                        break;

            case 0xE2:  //LD (0xFF00 + C), A
                        LD_WIO(this->C);
                        this->cycles = 8;
                        break;

            case 0xE5:  //PUSH HL
                        PUSH((uint16_t)((this->H << 8) + this->L));
                        this->cycles = 16;
                        break;

            case 0xE6:  //AND A, n8
                        AND(IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0xE7:  //RST 0x0020
                        RST(0x20);
                        this->cycles = 16;
                        break;

            case 0xE8:  //ADD SP, e8
                        ADD_SPe(IMMEDIATE_8b());
                        this->cycles = 16;
                        break;

            case 0xE9:  //JP HL
                        JP((uint16_t)((this->H << 8) + this->L));
                        this->cycles = 4;
                        break;

            case 0xEA:  //LD (a16), A
                        LD(IMMEDIATE_16b(), this->A);
                        this->cycles = 16;
                        break;

            case 0xEE:  //XOR A, n8
                        XOR(IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0xEF:  //RST 0x0028
                        RST(0x28);
                        this->cycles = 16;
                        break;

            case 0xF0:  //LDH A, (0xFF00 + n8)
                        LD_RIO(IMMEDIATE_8b());
                        this->cycles = 12;
                        break;

            case 0xF1:  //POP AF
                        POP(this->A, this->F);
                        this->cycles = 12;
                        break;

            case 0xF2:  //LD A, (0xFF00 + C)
                        LD_RIO(this->C);
                        this->cycles = 8;
                        break;

            case 0xF3:  //DI
                        DI();
                        this->cycles = 4;
                        break;

            case 0xF5:  //PUSH AF
                        PUSH((uint16_t)((this->A << 8) + this->F));
                        this->cycles = 16;
                        break;

            case 0xF6:  //OR A, n8
                        OR(IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0xF7:  //RST 0x0030
                        RST(0x30);
                        this->cycles = 16;
                        break;

            case 0xF8:  //LD HL, SP + e8
                        LD_HLSPe(IMMEDIATE_8b());
                        this->cycles = 12;
                        break;

            case 0xF9:  //LD SP, HL
                        LD(this->SP, (uint16_t)((this->H << 8) + this->L));
                        this->cycles = 8;
                        break;

            case 0xFA:  //LD A, (a16)
                        LD(this->A, IMMEDIATE_16b());
                        this->cycles = 16;
                        break;

            case 0xFB:  //EI
                        EI();
                        this->cycles = 4;
                        break;

            case 0xFE:  //CP A, n8
                        CP(IMMEDIATE_8b());
                        this->cycles = 8;
                        break;

            case 0xFF:  //RST 0x0038
                        RST(0x38);
                        this->cycles = 16;
                        break;

            default: throw std::runtime_error("ILLEGAL OPCODE");
                     break;
        }
    }


    void
    Cpu::execute_opcode_CB()
    {

        switch(this->opcode)
        {
            case 0x00:  //RLC B
                        RLC(this->B);
                        this->cycles += 8;
                        break;

            case 0x01:  //RLC C
                        RLC(this->C);
                        this->cycles += 8;
                        break;

            case 0x02:  //RLC D
                        RLC(this->D);
                        this->cycles += 8;
                        break;

            case 0x03:  //RLC E
                        RLC(this->E);
                        this->cycles += 8;
                        break;

            case 0x04:  //RLC H
                        RLC(this->H);
                        this->cycles += 8;
                        break;

            case 0x05:  //RLC L
                        RLC(this->L);
                        this->cycles += 8;
                        break;

            case 0x06:  //RLC (HL)
                        RLC((uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0x07:  //RLC A
                        RLC(this->A);
                        this->cycles += 8;
                        break;

            case 0x08:  //RRC B
                        RRC(this->B);
                        this->cycles += 8;
                        break;

            case 0x09:  //RRC C
                        RRC(this->C);
                        this->cycles += 8;
                        break;

            case 0x0A:  //RRC D
                        RRC(this->D);
                        this->cycles += 8;
                        break;

            case 0x0B:  //RRC E
                        RRC(this->E);
                        this->cycles += 8;
                        break;

            case 0x0C:  //RRC H
                        RRC(this->H);
                        this->cycles += 8;
                        break;

            case 0x0D:  //RRC L
                        RRC(this->L);
                        this->cycles += 8;
                        break;

            case 0x0E:  //RRC (HL)
                        RRC((uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0x0F:  //RRC A
                        RRC(this->A);
                        this->cycles += 8;
                        break;

            case 0x10:  //RL B
                        RL(this->B);
                        this->cycles += 8;
                        break;

            case 0x11:  //RL C
                        RL(this->C);
                        this->cycles += 8;
                        break;

            case 0x12:  //RL D
                        RL(this->D);
                        this->cycles += 8;
                        break;

            case 0x13:  //RL E
                        RL(this->E);
                        this->cycles += 8;
                        break;

            case 0x14:  //RL H
                        RL(this->H);
                        this->cycles += 8;
                        break;

            case 0x15:  //RL L
                        RL(this->L);
                        this->cycles += 8;
                        break;

            case 0x16:  //RL (HL)
                        RL((uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0x17:  //RL A
                        RL(this->A);
                        this->cycles += 8;
                        break;

            case 0x18:  //RR B
                        RR(this->B);
                        this->cycles += 8;
                        break;

            case 0x19:  //RR C
                        RR(this->C);
                        this->cycles += 8;
                        break;

            case 0x1A:  //RR D
                        RR(this->D);
                        this->cycles += 8;
                        break;

            case 0x1B:  //RR E
                        RR(this->E);
                        this->cycles += 8;
                        break;

            case 0x1C:  //RR H
                        RR(this->H);
                        this->cycles += 8;
                        break;

            case 0x1D:  //RR L
                        RR(this->L);
                        this->cycles += 8;
                        break;

            case 0x1E:  //RR (HL)
                        RR((uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0x1F:  //RR A
                        RR(this->A);
                        this->cycles += 8;
                        break;
                        
            case 0x20:  //SLA B
                        SLA(this->B);
                        this->cycles += 8;
                        break;

            case 0x21:  //SLA C
                        SLA(this->C);
                        this->cycles += 8;
                        break;

            case 0x22:  //SLA D
                        SLA(this->D);
                        this->cycles += 8;
                        break;

            case 0x23:  //SLA E
                        SLA(this->E);
                        this->cycles += 8;
                        break;

            case 0x24:  //SLA H
                        SLA(this->H);
                        this->cycles += 8;
                        break;

            case 0x25:  //SLA L
                        SLA(this->L);
                        this->cycles += 8;
                        break;

            case 0x26:  //SLA (HL)
                        SLA((uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0x27:  //SLA A
                        SLA(this->A);
                        this->cycles += 8;
                        break;

            case 0x28:  //SRA B
                        SRA(this->B);
                        this->cycles += 8;
                        break;

            case 0x29:  //SRA C
                        SRA(this->C);
                        this->cycles += 8;
                        break;

            case 0x2A:  //SRA D
                        SRA(this->D);
                        this->cycles += 8;
                        break;

            case 0x2B:  //SRA E
                        SRA(this->E);
                        this->cycles += 8;
                        break;

            case 0x2C:  //SRA H
                        SRA(this->H);
                        this->cycles += 8;
                        break;

            case 0x2D:  //SRA L
                        SRA(this->L);
                        this->cycles += 8;
                        break;

            case 0x2E:  //SRA (HL)
                        SRA((uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0x2F:  //SRA A
                        SRA(this->A);
                        this->cycles += 8;
                        break;

            case 0x30:  //SWAP B
                        SWAP(this->B);
                        this->cycles += 8;
                        break;

            case 0x31:  //SWAP C
                        SWAP(this->C);
                        this->cycles += 8;
                        break;

            case 0x32:  //SWAP D
                        SWAP(this->D);
                        this->cycles += 8;
                        break;

            case 0x33:  //SWAP E
                        SWAP(this->E);
                        this->cycles += 8;
                        break;

            case 0x34:  //SWAP H
                        SWAP(this->H);
                        this->cycles += 8;
                        break;

            case 0x35:  //SWAP L
                        SWAP(this->L);
                        this->cycles += 8;
                        break;

            case 0x36:  //SWAP (HL)
                        SWAP((uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0x37:  //SWAP A
                        SWAP(this->A);
                        this->cycles += 8;
                        break;

            case 0x38:  //SRL B
                        SRL(this->B);
                        this->cycles += 8;
                        break;

            case 0x39:  //SRL C
                        SRL(this->C);
                        this->cycles += 8;
                        break;

            case 0x3A:  //SRL D
                        SRL(this->D);
                        this->cycles += 8;
                        break;

            case 0x3B:  //SRL E
                        SRL(this->E);
                        this->cycles += 8;
                        break;

            case 0x3C:  //SRL H
                        SRL(this->H);
                        this->cycles += 8;
                        break;

            case 0x3D:  //SRL L
                        SRL(this->L);
                        this->cycles += 8;
                        break;

            case 0x3E:  //SRL (HL)
                        SRL((uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0x3F:  //SRL A
                        SRL(this->A);
                        this->cycles += 8;
                        break;

            case 0x40:  //BIT 0, B
                        BIT(BIT_0, this->B);
                        this->cycles += 8;
                        break;

            case 0x41:  //BIT 0, C
                        BIT(BIT_0, this->C);
                        this->cycles += 8;
                        break;

            case 0x42:  //BIT 0, D
                        BIT(BIT_0, this->D);
                        this->cycles += 8;
                        break;
                        
            case 0x43:  //BIT 0, E
                        BIT(BIT_0, this->E);
                        this->cycles += 8;
                        break;

            case 0x44:  //BIT 0, H
                        BIT(BIT_0, this->H);
                        this->cycles += 8;
                        break;

            case 0x45:  //BIT 0, L
                        BIT(BIT_0, this->L);
                        this->cycles += 8;
                        break;

            case 0x46:  //BIT 0, (HL)
                        BIT(BIT_0, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 12;
                        break;

            case 0x47:  //BIT 0, A
                        BIT(BIT_0, this->A);
                        this->cycles += 8;
                        break;

            case 0x48:  //BIT 1, B
                        BIT(BIT_1, this->B);
                        this->cycles += 8;
                        break;

            case 0x49:  //BIT 1, C
                        BIT(BIT_1, this->C);
                        this->cycles += 8;
                        break;

            case 0x4A:  //BIT 1, D
                        BIT(BIT_1, this->D);
                        this->cycles += 8;
                        break;

            case 0x4B:  //BIT 1, E
                        BIT(BIT_1, this->E);
                        this->cycles += 8;
                        break;

            case 0x4C:  //BIT 1, H
                        BIT(BIT_1, this->H);
                        this->cycles += 8;
                        break;

            case 0x4D:  //BIT 1, L
                        BIT(BIT_1, this->L);
                        this->cycles += 8;
                        break;

            case 0x4E:  //BIT 1, (HL)
                        BIT(BIT_1, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 12;
                        break;

            case 0x4F:  //BIT 1, A
                        BIT(BIT_1, this->A);
                        this->cycles += 8;
                        break;
                        
            case 0x50:  //BIT 2, B
                        BIT(BIT_2, this->B);
                        this->cycles += 8;
                        break;

            case 0x51:  //BIT 2, C
                        BIT(BIT_2, this->C);
                        this->cycles += 8;
                        break;

            case 0x52:  //BIT 2, D
                        BIT(BIT_2, this->D);
                        this->cycles += 8;
                        break;

            case 0x53:  //BIT 2, E
                        BIT(BIT_2, this->E);
                        this->cycles += 8;
                        break;

            case 0x54:  //BIT 2, H
                        BIT(BIT_2, this->H);
                        this->cycles += 8;
                        break;

            case 0x55:  //BIT 2, L
                        BIT(BIT_2, this->L);
                        this->cycles += 8;
                        break;

            case 0x56:  //BIT 2, (HL)
                        BIT(BIT_2, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 12;
                        break;

            case 0x57:  //BIT 2, A
                        BIT(BIT_2, this->A);
                        this->cycles += 8;
                        break;

            case 0x58:  //BIT 3, B
                        BIT(BIT_3, this->B);
                        this->cycles += 8;
                        break;

            case 0x59:  //BIT 3, C
                        BIT(BIT_3, this->C);
                        this->cycles += 8;
                        break;

            case 0x5A:  //BIT 3, D
                        BIT(BIT_3, this->D);
                        this->cycles += 8;
                        break;
//
            case 0x5B:  //BIT 3, E
                        BIT(BIT_3, this->E);
                        this->cycles += 8;
                        break;

            case 0x5C:  //BIT 3, H
                        BIT(BIT_3, this->H);
                        this->cycles += 8;
                        break;

            case 0x5D:  //BIT 3, L
                        BIT(BIT_3, this->L);
                        this->cycles += 8;
                        break;

            case 0x5E:  //BIT 3, (HL)
                        BIT(BIT_3, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 12;
                        break;

            case 0x5F:  //BIT 3, A
                        BIT(BIT_3, this->A);
                        this->cycles += 8;
                        break;
                        
            case 0x60:  //BIT 4, B
                        BIT(BIT_4, this->B);
                        this->cycles += 8;
                        break;

            case 0x61:  //BIT 4, C
                        BIT(BIT_4, this->C);
                        this->cycles += 8;
                        break;

            case 0x62:  //BIT 4, D
                        BIT(BIT_4, this->D);
                        this->cycles += 8;
                        break;

            case 0x63:  //BIT 4, E
                        BIT(BIT_4, this->E);
                        this->cycles += 8;
                        break;

            case 0x64:  //BIT 4, H
                        BIT(BIT_4, this->H);
                        this->cycles += 8;
                        break;

            case 0x65:  //BIT 4, L
                        BIT(BIT_4, this->L);
                        this->cycles += 8;
                        break;

            case 0x66:  //BIT 4, (HL)
                        BIT(BIT_4, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 12;
                        break;

            case 0x67:  //BIT 4, A
                        BIT(BIT_4, this->A);
                        this->cycles += 8;
                        break;

            case 0x68:  //BIT 5, B
                        BIT(BIT_5, this->B);
                        this->cycles += 8;
                        break;

            case 0x69:  //BIT 5, C
                        BIT(BIT_5, this->C);
                        this->cycles += 8;
                        break;

            case 0x6A:  //BIT 5, D
                        BIT(BIT_5, this->D);
                        this->cycles += 8;
                        break;

            case 0x6B:  //BIT 5, E
                        BIT(BIT_5, this->E);
                        this->cycles += 8;
                        break;

            case 0x6C:  //BIT 5, H
                        BIT(BIT_5, this->H);
                        this->cycles += 8;
                        break;

            case 0x6D:  //BIT 5, L
                        BIT(BIT_5, this->L);
                        this->cycles += 8;
                        break;

            case 0x6E:  //BIT 5, (HL)
                        BIT(BIT_5, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 12;
                        break;

            case 0x6F:  //BIT 5, A
                        BIT(BIT_5, this->A);
                        this->cycles += 8;
                        break;
                        
            case 0x70:  //BIT 6, B
                        BIT(BIT_6, this->B);
                        this->cycles += 8;
                        break;

            case 0x71:  //BIT 6, C
                        BIT(BIT_6, this->C);
                        this->cycles += 8;
                        break;

            case 0x72:  //BIT 6, D
                        BIT(BIT_6, this->D);
                        this->cycles += 8;
                        break;

            case 0x73:  //BIT 6, E
                        BIT(BIT_6, this->E);
                        this->cycles += 8;
                        break;

            case 0x74:  //BIT 6, H
                        BIT(BIT_6, this->H);
                        this->cycles += 8;
                        break;

            case 0x75:  //BIT 6, L
                        BIT(BIT_6, this->L);
                        this->cycles += 8;
                        break;

            case 0x76:  //BIT 6, (HL)
                        BIT(BIT_6, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 12;
                        break;

            case 0x77:  //BIT 6, A
                        BIT(BIT_6, this->A);
                        this->cycles += 8;
                        break;

            case 0x78:  //BIT 7, B
                        BIT(BIT_7, this->B);
                        this->cycles += 8;
                        break;

            case 0x79:  //BIT 7, C
                        BIT(BIT_7, this->C);
                        this->cycles += 8;
                        break;

            case 0x7A:  //BIT 7, D
                        BIT(BIT_7, this->D);
                        this->cycles += 8;
                        break;

            case 0x7B:  //BIT 7, E
                        BIT(BIT_7, this->E);
                        this->cycles += 8;
                        break;

            case 0x7C:  //BIT 7, H
                        BIT(BIT_7, this->H);
                        this->cycles += 8;
                        break;

            case 0x7D:  //BIT 7, L
                        BIT(BIT_7, this->L);
                        this->cycles += 8;
                        break;

            case 0x7E:  //BIT 7, (HL)
                        BIT(BIT_7, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 12;
                        break;

            case 0x7F:  //BIT 7, A
                        BIT(BIT_7, this->A);
                        this->cycles += 8;
                        break;

            case 0x80:  //RES 0, B
                        RES(BIT_0, this->B);
                        this->cycles += 8;
                        break;

            case 0x81:  //RES 0, C
                        RES(BIT_0, this->C);
                        this->cycles += 8;
                        break;

            case 0x82:  //RES 0, D
                        RES(BIT_0, this->D);
                        this->cycles += 8;
                        break;

            case 0x83:  //RES 0, E
                        RES(BIT_0, this->E);
                        this->cycles += 8;
                        break;

            case 0x84:  //RES 0, H
                        RES(BIT_0, this->H);
                        this->cycles += 8;
                        break;

            case 0x85:  //RES 0, L
                        RES(BIT_0, this->L);
                        this->cycles += 8;
                        break;

            case 0x86:  //RES 0, (HL)
                        RES(BIT_0, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0x87:  //RES 0, A
                        RES(BIT_0, this->A);
                        this->cycles += 8;
                        break;

            case 0x88:  //RES 1, B
                        RES(BIT_1, this->B);
                        this->cycles += 8;
                        break;

            case 0x89:  //RES 1, C
                        RES(BIT_1, this->C);
                        this->cycles += 8;
                        break;

            case 0x8A:  //RES 1, D
                        RES(BIT_1, this->D);
                        this->cycles += 8;
                        break;

            case 0x8B:  //RES 1, E
                        RES(BIT_1, this->E);
                        this->cycles += 8;
                        break;

            case 0x8C:  //RES 1, H
                        RES(BIT_1, this->H);
                        this->cycles += 8;
                        break;

            case 0x8D:  //RES 1, L
                        RES(BIT_1, this->L);
                        this->cycles += 8;
                        break;

            case 0x8E:  //RES 1, (HL)
                        RES(BIT_1, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0x8F:  //RES 1, A
                        RES(BIT_1, this->A);
                        this->cycles += 8;
                        break;

            case 0x90:  //RES 2, B
                        RES(BIT_2, this->B);
                        this->cycles += 8;
                        break;

            case 0x91:  //RES 2, C
                        RES(BIT_2, this->C);
                        this->cycles += 8;
                        break;

            case 0x92:  //RES 2, D
                        RES(BIT_2, this->D);
                        this->cycles += 8;
                        break;

            case 0x93:  //RES 2, E
                        RES(BIT_2, this->E);
                        this->cycles += 8;
                        break;

            case 0x94:  //RES 2, H
                        RES(BIT_2, this->H);
                        this->cycles += 8;
                        break;

            case 0x95:  //RES 2, L
                        RES(BIT_2, this->L);
                        this->cycles += 8;
                        break;

            case 0x96:  //RES 2, (HL)
                        RES(BIT_2, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0x97:  //RES 2, A
                        RES(BIT_2, this->A);
                        this->cycles += 8;
                        break;

            case 0x98:  //RES 3, B
                        RES(BIT_3, this->B);
                        this->cycles += 8;
                        break;

            case 0x99:  //RES 3, C
                        RES(BIT_3, this->C);
                        this->cycles += 8;
                        break;

            case 0x9A:  //RES 3, D
                        RES(BIT_3, this->D);
                        this->cycles += 8;
                        break;

            case 0x9B:  //RES 3, E
                        RES(BIT_3, this->E);
                        this->cycles += 8;
                        break;

            case 0x9C:  //RES 3, H
                        RES(BIT_3, this->H);
                        this->cycles += 8;
                        break;

            case 0x9D:  //RES 3, L
                        RES(BIT_3, this->L);
                        this->cycles += 8;
                        break;

            case 0x9E:  //RES 3, (HL)
                        RES(BIT_3, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0x9F:  //RES 3, A
                        RES(BIT_3, this->A);
                        this->cycles += 8;
                        break;

            case 0xA0:  //RES 4, B
                        RES(BIT_4, this->B);
                        this->cycles += 8;
                        break;

            case 0xA1:  //RES 4, C
                        RES(BIT_4, this->C);
                        this->cycles += 8;
                        break;

            case 0xA2:  //RES 4, D
                        RES(BIT_4, this->D);
                        this->cycles += 8;
                        break;

            case 0xA3:  //RES 4, E
                        RES(BIT_4, this->E);
                        this->cycles += 8;
                        break;

            case 0xA4:  //RES 4, H
                        RES(BIT_4, this->H);
                        this->cycles += 8;
                        break;

            case 0xA5:  //RES 4, L
                        RES(BIT_4, this->L);
                        this->cycles += 8;
                        break;

            case 0xA6:  //RES 4, (HL)
                        RES(BIT_4, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0xA7:  //RES 4, A
                        RES(BIT_4, this->A);
                        this->cycles += 8;
                        break;

            case 0xA8:  //RES 5, B
                        RES(BIT_5, this->B);
                        this->cycles += 8;
                        break;

            case 0xA9:  //RES 5, C
                        RES(BIT_5, this->C);
                        this->cycles += 8;
                        break;

            case 0xAA:  //RES 5, D
                        RES(BIT_5, this->D);
                        this->cycles += 8;
                        break;

            case 0xAB:  //RES 5, E
                        RES(BIT_5, this->E);
                        this->cycles += 8;
                        break;

            case 0xAC:  //RES 5, H
                        RES(BIT_5, this->H);
                        this->cycles += 8;
                        break;
                        
            case 0xAD:  //RES 5, L
                        RES(BIT_5, this->L);
                        this->cycles += 8;
                        break;

            case 0xAE:  //RES 5, (HL)
                        RES(BIT_5, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0xAF:  //RES 5, A
                        RES(BIT_5, this->A);
                        this->cycles += 8;
                        break;

            case 0xB0:  //RES 6, B
                        RES(BIT_6, this->B);
                        this->cycles += 8;
                        break;

            case 0xB1:  //RES 6, C
                        RES(BIT_6, this->C);
                        this->cycles += 8;
                        break;

            case 0xB2:  //RES 6, D
                        RES(BIT_6, this->D);
                        this->cycles += 8;
                        break;

            case 0xB3:  //RES 6, E
                        RES(BIT_6, this->E);
                        this->cycles += 8;
                        break;

            case 0xB4:  //RES 6, H
                        RES(BIT_6, this->H);
                        this->cycles += 8;
                        break;

            case 0xB5:  //RES 6, L
                        RES(BIT_6, this->L);
                        this->cycles += 8;
                        break;

            case 0xB6:  //RES 6, (HL)
                        RES(BIT_6, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0xB7:  //RES 6, A
                        RES(BIT_6, this->A);
                        this->cycles += 8;
                        break;

            case 0xB8:  //RES 7, B
                        RES(BIT_7, this->B);
                        this->cycles += 8;
                        break;

            case 0xB9:  //RES 7, C
                        RES(BIT_7, this->C);
                        this->cycles += 8;
                        break;

            case 0xBA:  //RES 7, D
                        RES(BIT_7, this->D);
                        this->cycles += 8;
                        break;

            case 0xBB:  //RES 7, E
                        RES(BIT_7, this->E);
                        this->cycles += 8;
                        break;

            case 0xBC:  //RES 7, H
                        RES(BIT_7, this->H);
                        this->cycles += 8;
                        break;

            case 0xBD:  //RES 7, L
                        RES(BIT_7, this->L);
                        this->cycles += 8;
                        break;

            case 0xBE:  //RES 7, (HL)
                        RES(BIT_7, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0xBF:  //RES 7, A
                        RES(BIT_7, this->A);
                        this->cycles += 8;
                        break;

            case 0xC0:  //SET 0, B
                        SET(BIT_0, this->B);
                        this->cycles += 8;
                        break;

            case 0xC1:  //SET 0, C
                        SET(BIT_0, this->C);
                        this->cycles += 8;
                        break;

            case 0xC2:  //SET 0, D
                        SET(BIT_0, this->D);
                        this->cycles += 8;
                        break;

            case 0xC3:  //SET 0, E
                        SET(BIT_0, this->E);
                        this->cycles += 8;
                        break;

            case 0xC4:  //SET 0, H
                        SET(BIT_0, this->H);
                        this->cycles += 8;
                        break;

            case 0xC5:  //SET 0, L
                        SET(BIT_0, this->L);
                        this->cycles += 8;
                        break;

            case 0xC6:  //SET 0, (HL)
                        SET(BIT_0, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0xC7:  //SET 0, A
                        SET(BIT_0, this->A);
                        this->cycles += 8;
                        break;

            case 0xC8:  //SET 1, B
                        SET(BIT_1, this->B);
                        this->cycles += 8;
                        break;

            case 0xC9:  //SET 1, C
                        SET(BIT_1, this->C);
                        this->cycles += 8;
                        break;

            case 0xCA:  //SET 1, D
                        SET(BIT_1, this->D);
                        this->cycles += 8;
                        break;

            case 0xCB:  //SET 1, E
                        SET(BIT_1, this->E);
                        this->cycles += 8;
                        break;

            case 0xCC:  //SET 1, H
                        SET(BIT_1, this->H);
                        this->cycles += 8;
                        break;

            case 0xCD:  //SET 1, L
                        SET(BIT_1, this->L);
                        this->cycles += 8;
                        break;

            case 0xCE:  //SET 1, (HL)
                        SET(BIT_1, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0xCF:  //SET 1, A
                        SET(BIT_1, this->A);
                        this->cycles += 8;
                        break;
                        
            case 0xD0:  //SET 2, B
                        SET(BIT_2, this->B);
                        this->cycles += 8;
                        break;

            case 0xD1:  //SET 2, C
                        SET(BIT_2, this->C);
                        this->cycles += 8;
                        break;

            case 0xD2:  //SET 2, D
                        SET(BIT_2, this->D);
                        this->cycles += 8;
                        break;

            case 0xD3:  //SET 2, E
                        SET(BIT_2, this->E);
                        this->cycles += 8;
                        break;

            case 0xD4:  //SET 2, H
                        SET(BIT_2, this->H);
                        this->cycles += 8;
                        break;

            case 0xD5:  //SET 2, L
                        SET(BIT_2, this->L);
                        this->cycles += 8;
                        break;

            case 0xD6:  //SET 2, (HL)
                        SET(BIT_2, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0xD7:  //SET 2, A
                        SET(BIT_2, this->A);
                        this->cycles += 8;
                        break;

            case 0xD8:  //SET 3, B
                        SET(BIT_3, this->B);
                        this->cycles += 8;
                        break;

            case 0xD9:  //SET 3, C
                        SET(BIT_3, this->C);
                        this->cycles += 8;
                        break;

            case 0xDA:  //SET 3, D
                        SET(BIT_3, this->D);
                        this->cycles += 8;
                        break;

            case 0xDB:  //SET 3, E
                        SET(BIT_3, this->E);
                        this->cycles += 8;
                        break;

            case 0xDC:  //SET 3, H
                        SET(BIT_3, this->H);
                        this->cycles += 8;
                        break;

            case 0xDD:  //SET 3, L
                        SET(BIT_3, this->L);
                        this->cycles += 8;
                        break;

            case 0xDE:  //SET 3, (HL)
                        SET(BIT_3, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0xDF:  //SET 3, A
                        SET(BIT_3, this->A);
                        this->cycles += 8;
                        break;

            case 0xE0:  //SET 4, B
                        SET(BIT_4, this->B);
                        this->cycles += 8;
                        break;

            case 0xE1:  //SET 4, C
                        SET(BIT_4, this->C);
                        this->cycles += 8;
                        break;

            case 0xE2:  //SET 4, D
                        SET(BIT_4, this->D);
                        this->cycles += 8;
                        break;

            case 0xE3:  //SET 4, E
                        SET(BIT_4, this->E);
                        this->cycles += 8;
                        break;

            case 0xE4:  //SET 4, H
                        SET(BIT_4, this->H);
                        this->cycles += 8;
                        break;

            case 0xE5:  //SET 4, L
                        SET(BIT_4, this->L);
                        this->cycles += 8;
                        break;

            case 0xE6:  //SET 4, (HL)
                        SET(BIT_4, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0xE7:  //SET 4, A
                        SET(BIT_4, this->A);
                        this->cycles += 8;
                        break;

            case 0xE8:  //SET 5, B
                        SET(BIT_5, this->B);
                        this->cycles += 8;
                        break;

            case 0xE9:  //SET 5, C
                        SET(BIT_5, this->C);
                        this->cycles += 8;
                        break;

            case 0xEA:  //SET 5, D
                        SET(BIT_5, this->D);
                        this->cycles += 8;
                        break;

            case 0xEB:  //SET 5, E
                        SET(BIT_5, this->E);
                        this->cycles += 8;
                        break;

            case 0xEC:  //SET 5, H
                        SET(BIT_5, this->H);
                        this->cycles += 8;
                        break;

            case 0xED:  //SET 5, L
                        SET(BIT_5, this->L);
                        this->cycles += 8;
                        break;

            case 0xEE:  //SET 5, (HL)
                        SET(BIT_5, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0xEF:  //SET 5, A
                        SET(BIT_5, this->A);
                        this->cycles += 8;
                        break;
                        
            case 0xF0:  //SET 6, B
                        SET(BIT_6, this->B);
                        this->cycles += 8;
                        break;

            case 0xF1:  //SET 6, C
                        SET(BIT_6, this->C);
                        this->cycles += 8;
                        break;

            case 0xF2:  //SET 6, D
                        SET(BIT_6, this->D);
                        this->cycles += 8;
                        break;

            case 0xF3:  //SET 6, E
                        SET(BIT_6, this->E);
                        this->cycles += 8;
                        break;

            case 0xF4:  //SET 6, H
                        SET(BIT_6, this->H);
                        this->cycles += 8;
                        break;

            case 0xF5:  //SET 6, L
                        SET(BIT_6, this->L);
                        this->cycles += 8;
                        break;

            case 0xF6:  //SET 6, (HL)
                        SET(BIT_6, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0xF7:  //SET 6, A
                        SET(BIT_6, this->A);
                        this->cycles += 8;
                        break;

            case 0xF8:  //SET 7, B
                        SET(BIT_7, this->B);
                        this->cycles += 8;
                        break;

            case 0xF9:  //SET 7, C
                        SET(BIT_7, this->C);
                        this->cycles += 8;
                        break;

            case 0xFA:  //SET 7, D
                        SET(BIT_7, this->D);
                        this->cycles += 8;
                        break;

            case 0xFB:  //SET 7, E
                        SET(BIT_7, this->E);
                        this->cycles += 8;
                        break;

            case 0xFC:  //SET 7, H
                        SET(BIT_7, this->H);
                        this->cycles += 8;
                        break;

            case 0xFD:  //SET 7, L
                        SET(BIT_7, this->L);
                        this->cycles += 8;
                        break;

            case 0xFE:  //SET 7, (HL)
                        SET(BIT_7, (uint16_t)((this->H << 8) + this->L));
                        this->cycles += 16;
                        break;

            case 0xFF:  //SET 7, A
                        SET(BIT_7, this->A);
                        this->cycles += 8;
                        break;

            default: //ILLEGAL OPCODE
                    throw std::runtime_error("ILLEGAL CB OPCODE");
                    break;
        }
    }



}