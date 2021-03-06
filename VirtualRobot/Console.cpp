#include "Console.h"

namespace Beeber
{

/*****************************************************************************/
Console& GetConsole()
/*****************************************************************************/
{
   return(Console::Instance());
}

/*****************************************************************************/
Console* Console::_instance = NULL;
/*****************************************************************************/

/*****************************************************************************/
Console::Console() :
_enableConsole(true)
/*****************************************************************************/
{
}

/*****************************************************************************/
Console::~Console()
/*****************************************************************************/
{
}

/*****************************************************************************/
Console& Console::Instance()
/*****************************************************************************/
{
   if(_instance == NULL)
      _instance = new Console();
   return(*_instance);
}

};
