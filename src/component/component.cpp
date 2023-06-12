#include "component.hpp"
#include <stdexcept>

namespace GB
{
    Component::Component()
    {
        this->connected = false;
        this->bus = nullptr;
    }

    Component::~Component()
    {
        if (this->bus != nullptr)
            delete this->bus;
    }

    bool
    Component::connectBus(Bus* bus)
    {
        if (bus == nullptr) {
            this->connected = false;
        }
        else {
            this->bus = bus;
            this->connected = true;
        }
        
        return this->connected;
    }

    uint8_t
    Component::read(uint16_t addr)
    {
        if (!(this->connected))
            throw new std::runtime_error("[Error] - Component not connected to the bus (to read in memory)\n");
        
        return this->bus->read(addr);
    }

    void
    Component::write(uint16_t addr, uint8_t data)
    {
        if (!(this->connected))
            throw new std::runtime_error("[Error] - Component not connected to the bus (to write in memory)\n");
        
        this->bus->write(addr, data);
    }
}