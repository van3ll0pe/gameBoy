#include "cpu.hpp"
#include <ctime>
#include <chrono>

namespace GB
{
   void
   Cpu::handle_timer()
   {
      unsigned int frequency = 4'194'304;
      float frameTime = 1 / frequency;

      static float elapsedTotal = 0.;
      clock_t clockCpu = clock();

      elapsedTotal = clock() - clockCpu;
      while(elapsedTotal > frameTime)
      {

      }


   }
}