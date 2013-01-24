#include "Semaphore.h"
#include "BeeberException.h"

namespace Beeber
{

/*****************************************************************************/
Semaphore::Semaphore(int n)
/*****************************************************************************/
{
   if(sem_init(&LowLevelSemaphore(), 0, n) == -1)
      throw(BeeberException("Semaphore: Could not initialize semaphore"));
}

/*****************************************************************************/
Semaphore::~Semaphore()
/*****************************************************************************/
{
   sem_destroy(&LowLevelSemaphore());
}

/*****************************************************************************/
bool Semaphore::TryLock()
/*****************************************************************************/
{
   if(sem_trywait(&LowLevelSemaphore()) == 0)
      return(true);

   return(false);
}

/*****************************************************************************/
void Semaphore::Lock()
/*****************************************************************************/
{
   if(sem_wait(&LowLevelSemaphore()) == -1)
      throw(BeeberException("Semaphore: Failed to lock."));
}

/*****************************************************************************/
void Semaphore::Unlock()
/*****************************************************************************/
{
   if(sem_post(&LowLevelSemaphore()) == -1)
      throw(BeeberException("Semaphore: Failed to unlock."));
}




};
