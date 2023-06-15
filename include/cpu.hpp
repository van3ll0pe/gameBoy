#pragma once
#ifndef __CPU_HPP__
#define __CPU_HPP__


#include <stdint.h>
#include <array>

#include "component.hpp"

#define ZERO_FLAG       0b10000000
#define SUBSTRACT_FLAG   0b01000000
#define HALF_CARRY_FLAG 0b00100000
#define CARRY_FLAG      0b00010000


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


            uint8_t cycles;
        
            //##### FLAGS #####
            void set_flag(uint8_t flag);                    //put 1 to the given flag
            void clear_flag(uint8_t flag);                  //put 0 to the given flag
            uint8_t get_flag(uint8_t flag);                 //returns the value of the flag given in the F register
            void check_flag(uint8_t flag, bool condition);  //set the flag given to 1 or 0 depending on the condition

            //##### STACK #####
            void push_8b(uint8_t data);
            void push_16b(uint16_t data);
            uint8_t pull_8b();
            uint16_t pull_16b();

            uint8_t opcode;
            void fetch_opcode();

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
            uint16_t INC_16b(uint16_t rr);
            uint16_t DEC_16b(uint16_t rr);
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
            void LD_SP(uint16_t n);                            //LD SP, nn
            void LD(uint8_t &hr, uint8_t &lr, uint16_t n);  //LD BC, nn | LD DE, nn | LD HL, nn
            void LD_a16(uint16_t a16);                      //LD (a16), SP
            void LD(uint16_t &rr, uint16_t rn);             //LD SP, HL
            void PUSH(uint16_t rr);
            void POP(uint8_t &rh, uint8_t &rl);

    };
}

#endif //__CPU_HPP__