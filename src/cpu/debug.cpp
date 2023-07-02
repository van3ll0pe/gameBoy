#include "cpu.hpp"
#include <iostream>


namespace GB
{
    void
    Cpu::display_registers()
    {
        printf("REGISTERS :\n");
        printf("SP = %04X, PC = %04X, A = %02X , B = %02X, C = %02X, D = %02X, E = %02X, H = %02X, L = %02X, F = ",this->SP, this->PC, this->A, this->B, this->C, this->D, this->E, this->H, this->L);
        if (get_flag(ZERO_FLAG))
            printf("Z");
        else
            printf("-");
        
        if (get_flag(SUBSTRACT_FLAG))
            printf("S");
        else
            printf("-");
        
        if (get_flag(HALF_CARRY_FLAG))
            printf("H");
        else
            printf("-");
        
        if (get_flag(CARRY_FLAG))
            printf("C");
        else
            printf("-");
    }
}
