#pragma once
#ifndef __BUS_HPP__
#define __BUS_HPP__

#include <array>
#include <stdint.h>

#define MEMORY_SIZE 0x10000

//##### HARDWARE REGISTERS

#define HR_P1   0xFF00
#define HR_SB   0xFF01
#define HR_SC   0xFF02
#define HR_DIV  0xFF04
#define HR_TIMA 0xFF05
#define HR_TMA  0xFF06
#define HR_TAC  0xFF07
#define HR_IF   0xFF0F
#define HR_NR10 0xFF10
#define HR_NR11 0xFF11
#define HR_NR12 0xFF12
#define HR_NR13 0xFF13
#define HR_NR14 0xFF14
#define HR_NR21 0xFF16
#define HR_NR22 0xFF17
#define HR_NR23 0xFF18
#define HR_NR24 0xFF19
#define HR_NR30 0xFF1A
#define HR_NR31 0xFF1B
#define HR_NR32 0xFF1C
#define HR_NR33 0xFF1D
#define HR_NR34 0xFF1E
#define HR_NR41 0xFF20
#define HR_NR42 0xFF21
#define HR_NR43 0xFF22
#define HR_NR44 0xFF23
#define HR_NR50 0xFF24
#define HR_NR51 0xFF25
#define HR_NR52 0xFF26
#define HR_LCDC 0xFF40
#define HR_STAT 0xFF41
#define HR_SCY  0xFF42
#define HR_SCX  0xFF43
#define HR_LY   0xFF44
#define HR_LYC  0xFF45
#define HR_DMA  0xFF46
#define HR_BGP  0xFF47
#define HR_OBP0 0xFF48
#define HR_OBP1 0xFF49
#define HR_WY   0xFF4A
#define HR_WX   0xFF4B
#define HR_KEY1 0xFF4D
#define HR_VBK  0xFF4F
#define HR_HDMA1    0xFF51
#define HR_HDMA2    0xFF52
#define HR_HDMA3    0xFF53
#define HR_HDMA4    0xFF54
#define HR_HDMA5    0xFF55
#define HR_RP   0xFF56
#define HR_BCPS 0xFF68
#define HR_BCPD 0xFF69
#define HR_OCPS 0xFF6A
#define HR_OCPD 0xFF6B
#define HR_SVBK 0xFF70
#define HR_IE   0xFFFF

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