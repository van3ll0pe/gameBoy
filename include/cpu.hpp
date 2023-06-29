#pragma once
#ifndef __CPU_HPP__
#define __CPU_HPP__


#include <stdint.h>
#include <array>

#include "component.hpp"

#define ZERO_FLAG           0b10000000
#define SUBSTRACT_FLAG      0b01000000
#define HALF_CARRY_FLAG     0b00100000
#define CARRY_FLAG          0b00010000

#define BIT_7 0b10000000
#define BIT_6 0b01000000
#define BIT_5 0b00100000
#define BIT_4 0b00010000
#define BIT_3 0b00001000
#define BIT_2 0b00000100
#define BIT_1 0b00000010
#define BIT_0 0b00000001

//##### CONDITION CALL/RET/JR/ with condition ######

#define CONDITION_Z   (get_flag(ZERO_FLAG) == 1)
#define CONDITION_NZ  (get_flag(ZERO_FLAG) == 0)
#define CONDITION_C   (get_flag(CARRY_FLAG) == 1)
#define CONDITION_NC  (get_flag(CARRY_FLAG) == 0)

//##### HARDWARE REGISTERS

#define HR_P1   0xFF00
#define HR_SB   0xFF01
#define HR_SC   0xFF02
#define HR_DIV  0xFF04
#define HR_TIMA 0xFF05
#define HR_TMA  0xFF06
#define HR_TAC  0xFF07
#define HR_IF   0xFF0F
#define HR_NR10 0xFF10
#define HR_NR11 0xFF11
#define HR_NR12 0xFF12
#define HR_NR13 0xFF13
#define HR_NR14 0xFF14
#define HR_NR21 0xFF16
#define HR_NR22 0xFF17
#define HR_NR23 0xFF18
#define HR_NR24 0xFF19
#define HR_NR30 0xFF1A
#define HR_NR31 0xFF1B
#define HR_NR32 0xFF1C
#define HR_NR33 0xFF1D
#define HR_NR34 0xFF1E
#define HR_NR41 0xFF20
#define HR_NR42 0xFF21
#define HR_NR43 0xFF22
#define HR_NR44 0xFF23
#define HR_NR50 0xFF24
#define HR_NR51 0xFF25
#define HR_NR52 0xFF26
#define HR_LCDC 0xFF40
#define HR_STAT 0xFF41
#define HR_SCY  0xFF42
#define HR_SCX  0xFF43
#define HR_LY   0xFF44
#define HR_LYC  0xFF45
#define HR_DMA  0xFF46
#define HR_BGP  0xFF47
#define HR_OBP0 0xFF48
#define HR_OBP1 0xFF49
#define HR_WY   0xFF4A
#define HR_WX   0xFF4B
#define HR_KEY1 0xFF4D
#define HR_VBK  0xFF4F
#define HR_HDMA1    0xFF51
#define HR_HDMA2    0xFF52
#define HR_HDMA3    0xFF53
#define HR_HDMA4    0xFF54
#define HR_HDMA5    0xFF55
#define HR_RP   0xFF56
#define HR_BCPS 0xFF68
#define HR_BCPD 0xFF69
#define HR_OCPS 0xFF6A
#define HR_OCPD 0xFF6B
#define HR_SVBK 0xFF70
#define HR_IE   0xFFFF


namespace GB
{
    class Cpu : public Component
    {
        public:
            Cpu();
            ~Cpu();

        private:
            //##### REGISTERS #####
            uint8_t A;
            uint8_t B;
            uint8_t C;
            uint8_t D;
            uint8_t E;
            uint8_t F;
            uint8_t H;
            uint8_t L;

            uint16_t SP;
            uint16_t PC;

            uint8_t IME;
            uint8_t stopped; //if the instruction is STOP, set to 1
            uint8_t halted; //if the instruction is HALT, set to 1

            uint8_t cycles;
        
            //##### FLAGS #####
            void set_flag(uint8_t flag);                    //put 1 to the given flag
            void clear_flag(uint8_t flag);                  //put 0 to the given flag
            uint8_t get_flag(uint8_t flag);                 //returns the value of the flag given in the F register 1 or 0
            void check_flag(uint8_t flag, bool condition);  //set the flag given to 1 or 0 depending on the condition

            //##### STACK #####
            void push_8b(uint8_t data);
            void push_16b(uint16_t data);
            uint8_t pull_8b();
            uint16_t pull_16b();

            uint8_t opcode;
            void fetch_opcode();
            void execute_opcode();
            void execute_opcode_CB();

            //##### ADDRESSING MODE #####
            uint8_t IMMEDIATE_8b(); //get the immediate value at PC address
            uint16_t IMMEDIATE_16b(); //get the immediate value at PC address

            //##### OPCODES ARITHMETIC 8bits #####
            void ADD(uint8_t rn);
            void ADD(uint16_t HL);
            void ADC(uint8_t rn);
            void ADC(uint16_t HL);

            void SUB(uint8_t rn);
            void SUB(uint16_t HL);
            void SBC(uint8_t rn);
            void SBC(uint16_t HL);
            void CP(uint8_t rn);
            void CP(uint16_t HL);

            void AND(uint8_t rn);
            void AND(uint16_t HL);
            void XOR(uint8_t rn);
            void XOR(uint16_t HL);
            void OR(uint8_t rn);
            void OR(uint16_t HL);

            void INC(uint8_t &r);
            void INC(uint16_t HL);
            void DEC(uint8_t &r);
            void DEC(uint16_t HL);

            void DAA();
            void CPL();

            //##### OPCODES ARITHMETIC 16bits #####
            void ADD_16b(uint16_t rr);
            void INC_16b(uint16_t &rr);
            void INC_16b(uint8_t &hr, uint8_t &lr);
            void DEC_16b(uint16_t &rr);
            void DEC_16b(uint8_t &hr, uint8_t &lr);
            void ADD_SPe(int8_t n);
            void LD_HLSPe(int8_t n);

            //###### OPCODES LOAD 8bits #####
            void LD(uint8_t &r, uint8_t rn);    //LD r, r | LD r, n
            void LD(uint8_t &r, uint16_t rr);   //LD r, (HL) | LD A (BC) | LD A (DE) | LD A (nn)
            void LD(uint16_t rr, uint8_t rn);   //LD (HL), r | LD (HL), n | LD (BC), A | LD (DE), A | LD (nn), A
            void LD_RIO(uint8_t rn); //LD A, (FF00 + n) | LD A, (FF00 + C)
            void LD_WIO(uint8_t rn); //LD (FF00 + n), A | LD (FF00 + C), A
            //LDI A, (HL) -> LD A, (HL); INC HL
            //LDI (HL), A -> LD (HL), A; INC HL
            //LDD A, (HL) -> LD A, (HL); DEC HL
            //LDD (HL), A -> LD (HL), A; DEC HL

            //##### OPCODES LOAD 16bits #####
            void LD(uint8_t &hr, uint8_t &lr, uint16_t n);  //LD BC, nn | LD DE, nn | LD HL, nn
            void LD_a16(uint16_t a16);                      //LD (a16), SP
            void LD(uint16_t &rr, uint16_t rn);             //LD SP, HL | LD SP, n16
            void PUSH(uint16_t rr);             //PUSH((A << 8) + F) -> PUSH AF, etc
            void POP(uint8_t &hr, uint8_t &lr); //POP(A, F) -> pop AF, etc

            //##### OPCODES ROTATE SWIFT
            void RLCA();
            void RLA();
            void RRCA();
            void RRA();
            void RLC(uint8_t &r);
            void RLC(uint16_t HL);
            void RL(uint8_t &r);
            void RL(uint16_t HL);
            void RRC(uint8_t &r);
            void RRC(uint16_t HL);
            void RR(uint8_t &r);
            void RR(uint16_t HL);
            void SLA(uint8_t &r);
            void SLA(uint16_t HL);
            void SWAP(uint8_t &r);
            void SWAP(uint16_t HL);
            void SRA(uint8_t &r);
            void SRA(uint16_t HL);
            void SRL(uint8_t &r);
            void SRL(uint16_t HL);

            //##### OPCODES BIT OPERATION #####
            void BIT(uint8_t b, uint8_t r);     //register not changed (no reference)
            void BIT(uint8_t b, uint16_t HL);
            void SET(uint8_t b, uint8_t &r);    //register modified (reference needed)
            void SET(uint8_t b, uint16_t HL);
            void RES(uint8_t b, uint8_t &r);    //register modified (reference needed)
            void RES(uint8_t b, uint16_t HL);

            //##### OPCODES JUMP #####
            void JP(uint16_t nn);
            void JP();              //JP HL
            void JP(bool condition, uint16_t nn); //conditionnal JP
            void JR(int8_t d);
            void JR(bool condition, int8_t d);
            void CALL(uint16_t nn);
            void CALL(bool condition, uint16_t nn);
            void RET();
            void RET(bool condition);
            void RETI();
            void RST(uint8_t n);

            //##### OPCODES CONTROL #####
            void CCF();
            void SCF();
            void NOP();
            void HALT();
            void STOP();
            void DI();
            void EI(); 




    };
}

#endif //__CPU_HPP__