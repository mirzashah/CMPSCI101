//BeeberIPC.h
//*****************************************************************************
//The include header for the BeeberIPC library. The BeeberIPC library was
//intended at first just to be the library for interprocess communication,
//but ended up being a collection of highly useful and simple components
//that are used by all Beeber agents such as Threads, Semaphores, a thread
//safe console, and functional style Containers. BeeberIPC can be considered
//the kernel of all Beeber software agents.
//*****************************************************************************

#ifndef BEEBER_CORE_H_DEFINED
#define BEEBER_CORE_H_DEFINED

#include "BeeberException.h"
#include "BeeberMessage.h"
#include "BeeberMessageSerialization.h"
#include "BeeberConfigurationManager.h"
#include "Containers.h"
#include "Thread.h"
#include "Semaphore.h"
#include "Console.h"
#include "Geometry.h"
#include "TimeManagement.h"
#include "CollisionAvoidance.h"

#endif
