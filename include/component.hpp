#pragma once
#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__

#include <stdint.h>

#include "bus.hpp"

namespace GB
{
    class Component
    {
        public:
            Component();
            virtual ~Component();

            void connectBus(Bus* bus);
            uint8_t read(uint16_t addr);
            void write(uint16_t addr, uint8_t data);

        protected:
            Bus* bus;
    };
}

#endif //__COMPONENT_HPP__