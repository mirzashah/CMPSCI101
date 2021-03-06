#include "Thread.h"
#include <cstdio>

namespace Beeber
{

/*****************************************************************************/
Thread::Thread()
/*****************************************************************************/
{
}

/*****************************************************************************/
Thread::~Thread()
/*****************************************************************************/
{
}

/*****************************************************************************/
void* Thread::EntryPoint(void* arg)
/*****************************************************************************/
{
   Thread* theThreadObj = (Thread*)(arg);
   theThreadObj->Run();
   return(NULL);
}

/*****************************************************************************/
void Thread::Exit()
/*****************************************************************************/
{
   pthread_exit(NULL);
}

/*****************************************************************************/
void Thread::Join()
/*****************************************************************************/
{
   pthread_join(LowLevelThread(), NULL);
}

/*****************************************************************************/
void Thread::Run()
/*****************************************************************************/
{
   static int count = 0;
   while(count < 1000)
   {
      count++;
      printf("This is thread %p\n", &_lowLevelThread);
      fflush(stdout);
      //MOOSPause(10);
   }
}

/*****************************************************************************/
bool Thread::Start()
/*****************************************************************************/
{
   if(pthread_create(&(LowLevelThread()), NULL, &(Thread::EntryPoint), this))
   {
      printf("Could not create thread\n");
      return(false);
   }
   return(true);
}

};
