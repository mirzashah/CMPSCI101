#include "SoundHelper.h"
#include <cstdlib>
#include <sstream>
using std::ostringstream;

namespace Beeber
{

/*****************************************************************************/
bool PlaySoundAsynchronous(string musicFile)
/*****************************************************************************/
{
#ifndef WIN32
   ostringstream cmd;
   system(("mpg123 ./" + musicFile).c_str());
#endif
   return(true);
}

/*****************************************************************************/
bool PlaySoundBlocking(string musicFile)
/*****************************************************************************/
{
#ifndef WIN32
   ostringstream cmd;
   system(("mpg123 ./" + musicFile).c_str());
#endif
   return(true);
}

}
