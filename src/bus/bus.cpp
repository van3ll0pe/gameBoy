#include "bus.hpp"

namespace GB
{
    Bus::Bus()
    {
        this->memory.fill(0);
    }

    Bus::~Bus() {}

    uint8_t
    Bus::read(uint16_t addr)
    {
        return this->memory[addr];
    }

    void
    Bus::write(uint16_t addr, uint8_t data)
    {
        this->memory[addr] = data;
    }
}