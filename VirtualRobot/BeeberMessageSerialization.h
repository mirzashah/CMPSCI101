//BeeberMessageSerialization.h
//*****************************************************************************
//Encodes and decodes messages used in Beeber interprocess communication
//*****************************************************************************

#ifndef BEEBER_MESSAGE_SERIALIZATION_H_DEFINED
#define BEEBER_MESSAGE_SERIALIZATION_H_DEFINED

#include "BeeberMessage.h"
#include "BeeberException.h"

namespace Beeber
{

//Recovers a BeeberMessage from its serialized (string) form
const BeeberMessage& Deserialize(const string& serializedMsg);

//Encodes a BeeberMessage as a serialized string that can be transmitted over network
string               Serialize(const BeeberMessage& msg);

};

#endif
