#include "bus.hpp"

namespace GB
{
    Bus::Bus()
    {
        this->memory.fill(0);
        
        //value in hard registers
        this->memory[HR_P1] = 0xCF;
        this->memory[HR_SB] = 0x00;
        this->memory[HR_SC] = 0x7E;
        this->memory[HR_DIV] = 0xAB;
        this->memory[HR_TIMA] = 0x00;
        this->memory[HR_TMA] = 0x00;
        this->memory[HR_TAC] = 0xF8;
        this->memory[HR_IF] = 0xE1;
        this->memory[HR_NR10] = 0x80;
        this->memory[HR_NR11] = 0xBF;
        this->memory[HR_NR12] = 0xF3;
        this->memory[HR_NR13] = 0xFF;
        this->memory[HR_NR14] = 0xBF;
        this->memory[HR_NR21] = 0x3F;
        this->memory[HR_NR22] = 0x00;
        this->memory[HR_NR23] = 0xFF;
        this->memory[HR_NR24] = 0xBF;
        this->memory[HR_NR30] = 0x7F;
        this->memory[HR_NR31] = 0xFF;
        this->memory[HR_NR32] = 0x9F;
        this->memory[HR_NR33] = 0xFF;
        this->memory[HR_NR34] = 0xBF;
        this->memory[HR_NR41] = 0xFF;
        this->memory[HR_NR42] = 0x00;
        this->memory[HR_NR43] = 0x00;
        this->memory[HR_NR44] = 0xBF;
        this->memory[HR_NR50] = 0x77;
        this->memory[HR_NR51] = 0xF3;
        this->memory[HR_NR52] = 0xF1;
        this->memory[HR_LCDC] = 0x91;
        this->memory[HR_STAT] = 0x85;
        this->memory[HR_SCY] = 0x00;
        this->memory[HR_SCX] = 0x00;
        this->memory[HR_LY] = 0x00;
        this->memory[HR_LYC] = 0x00;
        this->memory[HR_DMA] = 0xFF;
        this->memory[HR_BGP] = 0xFC;
        this->memory[HR_OBP0] = 0x00;
        this->memory[HR_OBP1] = 0x00;
        this->memory[HR_WY] = 0x00;
        this->memory[HR_WX] = 0x00;
        this->memory[HR_KEY1] = 0xFF;
        this->memory[HR_VBK] = 0xFF;
        this->memory[HR_HDMA1] = 0xFF;
        this->memory[HR_HDMA2] = 0xFF;
        this->memory[HR_HDMA3] = 0xFF;
        this->memory[HR_HDMA4] = 0xFF;
        this->memory[HR_HDMA5] = 0xFF;
        this->memory[HR_RP] = 0xFF;
        this->memory[HR_BCPS] = 0xFF;
        this->memory[HR_BCPD] = 0xFF;
        this->memory[HR_OCPS] = 0xFF;
        this->memory[HR_OCPD] = 0xFF;
        this->memory[HR_SVBK] = 0xFF;
        this->memory[HR_IE] = 0x00;
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
        if (addr == HR_DIV) //if the address is the DIV hard register, we put a 0, not the data, because writing in it reset the div clock count
            this->memory[addr] = 0x00;
        
        this->memory[addr] = data;
    }
}