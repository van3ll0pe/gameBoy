#include "cpu.hpp"

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
}