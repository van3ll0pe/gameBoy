#include "cpu.hpp"


namespace GB
{
    void
    Cpu::handle_interrupt()
    {
        if (this->IME == 0) return;

        //IME SET
        uint8_t enable_interrupts = read(HR_IE);
        uint8_t request_interrupts = read(HR_IF);


        //CHECK VBLANK PRIORITY ONE
        if ((request_interrupts & BIT_VBLANK) && (enable_interrupts & BIT_VBLANK))
        {
            CALL(INTERRUPT_VBLANK);
            request_interrupts &= (~BIT_VBLANK);
            write(HR_IF, request_interrupts);
            this->IME = 0;
        }
        //CHECK LCD PRIORITY TWO
        else if ((request_interrupts & BIT_LCD) && (enable_interrupts & BIT_LCD))
        {
            CALL(INTERRUPT_LCD);
            request_interrupts &= (~BIT_LCD);
            write(HR_IF, request_interrupts);
            this->IME = 0;
        }
        //CHECK TIMER PRIORITY THREE
        else if ((request_interrupts & BIT_TIMER) && (enable_interrupts & BIT_TIMER))
        {
            CALL(INTERRUPT_TIMER);
            request_interrupts &= (~BIT_TIMER);
            write(HR_IF, request_interrupts);
            this->IME = 0;
        }
        //CHECK SERIAL PRIORITY FOUR
        else if ((request_interrupts & BIT_SERIAL) && (enable_interrupts & BIT_SERIAL))
        {
            CALL(INTERRUPT_SERIAL);
            request_interrupts &= (~BIT_SERIAL);
            write(HR_IF, request_interrupts);
            this->IME = 0;
        }
        //CHECK JOYPAD PRIORITY FIVE
        else if ((request_interrupts & BIT_JOYPAD) && (enable_interrupts & BIT_JOYPAD))
        {
            CALL(INTERRUPT_JOYPAD);
            request_interrupts &= (~BIT_JOYPAD);
            write(HR_IF, request_interrupts);
            this->IME = 0;
        }

    }
}