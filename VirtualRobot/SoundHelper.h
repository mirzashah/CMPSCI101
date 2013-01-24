// SoundHelper
//*****************************************************************************
// Simple calls to play sound files.
//*****************************************************************************

#ifndef SOUND_HELPER_H_DEFINED
#define SOUND_HELPER_H_DEFINED

#include <string>
using std::string;

namespace Beeber
{

bool PlaySoundAsynchronous(string musicFile);
bool PlaySoundBlocking(string musicFile);


};
#endif
