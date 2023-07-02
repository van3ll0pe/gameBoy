#include "cpu.hpp"
#include <iostream>

namespace GB
{
    uint8_t
    Cpu::IMMEDIATE_8b()
    {
        #ifdef DEBUG_INFO_CPU
            printf("ADDRESS %04X : [immediate 8bits] %2X\n", this->PC, read(this->PC));
        #endif //DEBUG_INFO_CPU
        return read(this->PC++);
    }

    uint16_t
    Cpu::IMMEDIATE_16b()
    {
        uint16_t data = 0;
        #ifdef DEBUG_INFO_CPU
            printf("ADDRESS %04X : [immediate 16bits - low byte] %2X\n", this->PC, read(this->PC));
        #endif //DEBUG_INFO_CPU
        data = read(this->PC++);            //low bytes
        #ifdef DEBUG_INFO_CPU
            printf("ADDRESS %04X : [immediate 16bits - high byte] %2X\n", this->PC, read(this->PC));
        #endif //DEBUG_INFO_CPU
        data |= (read(this->PC++) << 8);    //high bytes (little endian)

        return data;
    }
}