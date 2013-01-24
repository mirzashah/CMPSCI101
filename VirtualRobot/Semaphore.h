// Sempahore
//*****************************************************************************
// A simple OO abstraction for POSIX semaphores
//*****************************************************************************

#ifndef SEMAPHORE_H_DEFINED
#define SEMAPHORE_H_DEFINED

#include <pthread.h>
//#include <semaphore.h> //Note: Different from this file which starts with capital 'S'
#include <C:\Program Files\CodeBlocks\MinGW\include\semaphore.h>

namespace Beeber
{

class Semaphore
{
   public:
      //Constructor, n indicates qty of resource, by default it is
      Semaphore(int n = 1);
      virtual ~Semaphore();

      //Does not return until lock acquired
      void Lock();

      //Attempts to lock immediately. If success, lock is obtained and returns true, otherwise no lock and returns false
      bool TryLock();

      //Unlocks when resource finished.
      void Unlock();

   private:
      //Handle to the low level POSIX semaphore
      sem_t& LowLevelSemaphore(){return(_lowLevelSemaphore);}

   private:
      sem_t _lowLevelSemaphore;
};

};

#endif
