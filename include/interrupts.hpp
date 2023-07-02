#pragma once
#ifndef __INTERRUPTS_HPP__
#define __INTERRUPTS_HPP__

//##### INTERRUPTS ADDRESS and INTERRUPTS BIT corresponding in IE and IF
#define BIT_VBLANK  0b00000001
#define BIT_LCD     0b00000010
#define BIT_TIMER   0b00000100
#define BIT_SERIAL  0b00001000
#define BIT_JOYPAD  0b00010000


#define INTERRUPT_VBLANK  0x0040
#define INTERRUPT_LCD     0x0048
#define INTERRUPT_TIMER   0x0050
#define INTERRUPT_SERIAL  0x0058
#define INTERRUPT_JOYPAD  0x0060

#endif //__INTERRUPTS_HPP__