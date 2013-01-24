// Thread
//*****************************************************************************
// A simple OO abstraction for POSIX threads (pthreads)
//*****************************************************************************

#ifndef BEEBER_THREAD_H_DEFINED
#define BEEBER_THREAD_H_DEFINED

#include <pthread.h>

namespace Beeber
{

class Thread
{
   public:
      Thread();
      virtual ~Thread();

      //Start thread
      bool         Start();

      //Exit thread
      void         Exit();

      //Caller thread joins to this thread, meaning caller halts until this thread is finished
      void         Join();

   protected:
      //Entry point for thread, subclasses should implement
      virtual void Run();

   private:

      static void* EntryPoint(void* arg);
      pthread_t&   LowLevelThread(){return(_lowLevelThread);}

   private:
      pthread_t    _lowLevelThread;
};

};

#endif
