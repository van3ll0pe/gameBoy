#pragma once
#ifndef __CPU_HPP__
#define __CPU_HPP__


#include <stdint.h>
#include <array>

#include "component.hpp"

#define ZERO_FLAG       0b10000000
#define NEGATIVE_FLAG   0b01000000
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

            //##### OPCODES LOAD #####
            void LD(uint8_t &registre_dst, uint8_t registre_src); //LD r, r
            void LD(uint8_t &registre_dst); //LD r, (HL)
            void LD(uint8_t)


    };
}

#endif //__CPU_HPP__