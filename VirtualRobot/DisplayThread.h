#ifndef DISPLAY_THREAD_H_DEFINED
#define DISPLAY_THREAD_H_DEFINED

#include <BeeberIPC.h>

namespace VirtualRobot
{

class DisplayThread : public Beeber::Thread
{
   public:
      DisplayThread(){IsDone().Lock();}
      virtual ~DisplayThread(){};

      Beeber::Semaphore& IsDone(){return(_isDone);}

   protected:
      virtual void Run();
      Beeber::Semaphore _isDone;

};


};


#endif
