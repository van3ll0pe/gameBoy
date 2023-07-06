#include "cpu.hpp"


namespace GB
{
    void
    Cpu::handle_interrupt()
    {
        if (this->IME == 0) return; //no need to check the request because IME is false

        //IME SET
        uint8_t enable_interrupts = read(HR_IE);
        uint8_t request_interrupts = read(HR_IF);

        if ((enable_interrupts & request_interrupts) == 0x00) return; //if enable_interrupts and request_interrupts have no corresponding bits for interrupts (so 0), return


        //CHECK VBLANK is requested and enabled PRIORITY ONE
        if ((request_interrupts & BIT_VBLANK) && (enable_interrupts & BIT_VBLANK))
        {
            CALL(INTERRUPT_VBLANK);
            write(HR_IF, request_interrupts & (~BIT_VBLANK)); //clear the bit VBLANK in the request interrupts
            this->IME = 0;
            this->cycles = 5;
        }
        //CHECK LCD is requested and enabled PRIORITY TWO
        else if ((request_interrupts & BIT_LCD) && (enable_interrupts & BIT_LCD))
        {
            CALL(INTERRUPT_LCD);
            write(HR_IF, request_interrupts & (~BIT_LCD)); //clear the bit VBLANK in the request interrupts
            this->IME = 0;
            this->cycles = 5;
        }
        //CHECK TIMER is requested and enabled PRIORITY THREE
        else if ((request_interrupts & BIT_TIMER) && (enable_interrupts & BIT_TIMER))
        {
            CALL(INTERRUPT_TIMER);
            write(HR_IF, request_interrupts & (~BIT_TIMER)); //clear the bit VBLANK in the request interrupts
            this->IME = 0;
            this->cycles = 5;
        }
        //CHECK SERIAL is requested and enabled PRIORITY FOUR
        else if ((request_interrupts & BIT_SERIAL) && (enable_interrupts & BIT_SERIAL))
        {
            CALL(INTERRUPT_SERIAL);
            write(HR_IF, request_interrupts & (~BIT_SERIAL)); //clear the bit VBLANK in the request interrupts
            this->IME = 0;
            this->cycles = 5;
        }
        //CHECK JOYPAD is requested and enabled PRIORITY FIVE
        else if ((request_interrupts & BIT_JOYPAD) && (enable_interrupts & BIT_JOYPAD))
        {
            CALL(INTERRUPT_JOYPAD);
            write(HR_IF, request_interrupts & (~BIT_JOYPAD)); //clear the bit VBLANK in the request interrupts
            this->IME = 0;
            this->cycles = 5;
        }
    }
}