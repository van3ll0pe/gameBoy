#include "component.hpp"
#include <stdexcept>

namespace GB
{
    Component::Component()
    {
        this->bus = nullptr;
    }

    Component::~Component()
    { }

    void
    Component::connectBus(Bus* bus)
    {
        if (bus == nullptr)
            throw std::runtime_error("[Error] - Component failed to connect the bus (bus given is not existing)\n");

        else
            this->bus = bus;
    }

    uint8_t
    Component::read(uint16_t addr)
    {
        if (!(this->bus))
            throw std::runtime_error("[Error] - Component not connected to the bus (to read in memory)\n");
        
        return this->bus->read(addr);
    }

    void
    Component::write(uint16_t addr, uint8_t data)
    {
        if (!(this->bus))
            throw std::runtime_error("[Error] - Component not connected to the bus (to write in memory)\n");
        
        this->bus->write(addr, data);
    }
}