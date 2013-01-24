//BeeberException.h
//*****************************************************************************
//A generic base class for Beeber-specific exceptions
//*****************************************************************************

#ifndef BEEBER_EXCEPTION_H_DEFINED
#define BEEBER_EXCEPTION_H_DEFINED

#include <string>
using std::string;

namespace Beeber
{

class BeeberException
{
   public:
      BeeberException(string error)
      {
         _error = error;
      }

      string Error() {return(_error);}


   private:
      string _error;
};

};
#endif
