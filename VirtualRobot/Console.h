//Console
//*****************************************************************************
//A thread safe and controllable console wrapper for std::cout.
//Allows disabling for higher performance and enabling for
//debugging.
//*****************************************************************************

#ifndef PRINTER_H_DEFINED
#define PRINTER_H_DEFINED

#include "Semaphore.h"
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

namespace Beeber
{

class Console : public Semaphore
{
   public:
      Console();
      virtual ~Console();

      template <typename T> Console& operator<<(const T& val)
      {
         if(IsEnabled())
         {
            Lock();
            std::cout << val;
            flush(cout);
            Unlock();
         }
         return(*this);
      }
      void                  EnableConsole(bool enable){Lock(); _enableConsole = enable; Unlock();}
      static Console&       Instance();

   private:
      bool                  IsEnabled(){return(_enableConsole);}

   private:
      bool                  _enableConsole;
      static Console*       _instance;
};

Console& GetConsole();
};

#endif
