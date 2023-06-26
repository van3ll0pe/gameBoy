#include "cpu.hpp"
#include <stdexcept>
namespace GB
{
    Cpu::Cpu(): Component()
    {
        this->A = 0x1;
        this->B = 0;
        this->C = 0x13;
        this->D = 0;
        this->E = 0xD8;
        this->F = 0;
        this->H = 0x1;
        this->L = 0x4D;
        this->PC = 0x0100;
        this->SP = 0xFFFE;

        this->cycles = 0;
    }

    Cpu::~Cpu() {}

    void
    Cpu::fetch_opcode()
    {
        this->opcode = read(this->PC++);
    }

    void
    Cpu::execute_opcode()
    {
        fetch_opcode();

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

            case 0xE0:
            case 0xE1:
            case 0xE2:
            case 0xE3:
            case 0xE4:
            case 0xE5:
            case 0xE6:
            case 0xE7:
            case 0xE8:
            case 0xE9:
            case 0xEA:
            case 0xEB:
            case 0xEC:
            case 0xED:
            case 0xEE:
            case 0xEF:

            case 0xF0:
            case 0xF1:
            case 0xF2:
            case 0xF3:
            case 0xF4:
            case 0xF5:
            case 0xF6:
            case 0xF7:
            case 0xF8:
            case 0xF9:
            case 0xFA:
            case 0xFB:
            case 0xFC:
            case 0xFD:
            case 0xFE:
            case 0xFF:

            default: throw std::runtime_error("ILLEGAL OPCODE");
                     break;
        }
    }


    void execute_opcode_CB();



}