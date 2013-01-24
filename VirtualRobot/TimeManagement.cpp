#include "TimeManagement.h"
#include <MOOSGenLib/MOOSGenLib.h>

namespace Beeber
{

/*****************************************************************************/
void Pause(int microseconds)
/*****************************************************************************/
{
   #ifdef _WIN32
      ::Sleep(microseconds);
   #else

       timespec TimeSpec;
       TimeSpec.tv_sec     = microseconds / 1000;
       TimeSpec.tv_nsec    = (microseconds%1000) *1000000;

       nanosleep(&TimeSpec,NULL);

   #endif
}

}
