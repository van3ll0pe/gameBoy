#pragma once
#ifndef __BUS_HPP__
#define __BUS_HPP__

#include <array>
#include <stdint.h>

#define MEMORY_SIZE 0x10000

namespace GB
{
    class Bus
    {
        private:
            std::array<uint8_t, MEMORY_SIZE> memory;
        
        public:
            Bus();
            ~Bus();
            uint8_t read(uint16_t addr);
            void write(uint16_t addr, uint8_t data);
        

    };
}

#endif //__BUS_HPP__