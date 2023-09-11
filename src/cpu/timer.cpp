#include "cpu.hpp"
#include <ctime>
#include <chrono>
#include <stdio.h>

namespace GB
{
   void
   Cpu::handle_timer()
   {
      
      //DIVISION TIMER
      static int divider_clock = 0;
      divider_clock += this->cycles;
      if (divider_clock > 0xFF)
      {
         divider_clock = 0;
         write(HR_DIV, read(HR_DIV) + 1);
      }

      //TAC TIMER ENABLE VERIFICATION, if the BIT 2 is 0, no need to increment TIMA
      if ((read(HR_TAC) & BIT_2) == 0) {
            return;
      }


      int frequency_speed = 1;

      if ((read(HR_TAC) & 0x3) == 0)
         frequency_speed = 4096;
      else if ((read(HR_TAC) & 0x3) == 1)
         frequency_speed = 262144;
      else if ((read(HR_TAC) & 0x3) == 2)
         frequency_speed = 65536;
      else if ((read(HR_TAC) & 0x3) == 3)
         frequency_speed = 16384;
      

      static int clock_sum = (int)(4'194'304 / frequency_speed);

      clock_sum -= this->cycles;

      if (clock_sum <= 0)
      {
         clock_sum = (int)(4'194'304 / frequency_speed);

         if (read(HR_TIMA) == 0xFF) //if TIMA is going to overflow
         {
            write(HR_TIMA, read(HR_TMA)); //the TMA value is put in TIMA storage
            write(HR_IF, read(HR_IF) | 4); //request interrupt timer
         } else //if not overflow increment TIMA
         {
            write(HR_TIMA, read(HR_TIMA) + 1);

         }
      }
   }
}