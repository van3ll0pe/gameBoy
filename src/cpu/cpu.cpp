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
                        JR(CONDITION_C, )
            case 0x39:
            case 0x3A:
            case 0x3B:
            case 0x3C:
            case 0x3D:
            case 0x3E:
            case 0x3F:

            case 0x40:
            case 0x41:
            case 0x42:
            case 0x43:
            case 0x44:
            case 0x45:
            case 0x46:
            case 0x47:
            case 0x48:
            case 0x49:
            case 0x4A:
            case 0x4B:
            case 0x4C:
            case 0x4D:
            case 0x4E:
            case 0x4F:

            case 0x50:
            case 0x51:
            case 0x52:
            case 0x53:
            case 0x54:
            case 0x55:
            case 0x56:
            case 0x57:
            case 0x58:
            case 0x59:
            case 0x5A:
            case 0x5B:
            case 0x5C:
            case 0x5D:
            case 0x5E:
            case 0x5F:

            case 0x60:
            case 0x61:
            case 0x62:
            case 0x63:
            case 0x64:
            case 0x65:
            case 0x66:
            case 0x67:
            case 0x68:
            case 0x69:
            case 0x6A:
            case 0x6B:
            case 0x6C:
            case 0x6D:
            case 0x6E:
            case 0x6F:

            case 0x70:
            case 0x71:
            case 0x72:
            case 0x73:
            case 0x74:
            case 0x75:
            case 0x76:
            case 0x77:
            case 0x78:
            case 0x79:
            case 0x7A:
            case 0x7B:
            case 0x7C:
            case 0x7D:
            case 0x7E:
            case 0x7F:

            case 0x80:
            case 0x81:
            case 0x82:
            case 0x83:
            case 0x84:
            case 0x85:
            case 0x86:
            case 0x87:
            case 0x88:
            case 0x89:
            case 0x8A:
            case 0x8B:
            case 0x8C:
            case 0x8D:
            case 0x8E:
            case 0x8F:

            case 0x90:
            case 0x91:
            case 0x92:
            case 0x93:
            case 0x94:
            case 0x95:
            case 0x96:
            case 0x97:
            case 0x98:
            case 0x99:
            case 0x9A:
            case 0x9B:
            case 0x9C:
            case 0x9D:
            case 0x9E:
            case 0x9F:

            case 0xA0:
            case 0xA1:
            case 0xA2:
            case 0xA3:
            case 0xA4:
            case 0xA5:
            case 0xA6:
            case 0xA7:
            case 0xA8:
            case 0xA9:
            case 0xAA:
            case 0xAB:
            case 0xAC:
            case 0xAD:
            case 0xAE:
            case 0xAF:

            case 0xB0:
            case 0xB1:
            case 0xB2:
            case 0xB3:
            case 0xB4:
            case 0xB5:
            case 0xB6:
            case 0xB7:
            case 0xB8:
            case 0xB9:
            case 0xBA:
            case 0xBB:
            case 0xBC:
            case 0xBD:
            case 0xBE:
            case 0xBF:

            case 0xC0:
            case 0xC1:
            case 0xC2:
            case 0xC3:
            case 0xC4:
            case 0xC5:
            case 0xC6:
            case 0xC7:
            case 0xC8:
            case 0xC9:
            case 0xCA:
            case 0xCB:
            case 0xCC:
            case 0xCD:
            case 0xCE:
            case 0xCF:

            case 0xD0:
            case 0xD1:
            case 0xD2:
            case 0xD3:
            case 0xD4:
            case 0xD5:
            case 0xD6:
            case 0xD7:
            case 0xD8:
            case 0xD9:
            case 0xDA:
            case 0xDB:
            case 0xDC:
            case 0xDD:
            case 0xDE:
            case 0xDF:

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