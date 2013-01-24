//MobileNode.h
//*****************************************************************************
//The base class for all nodes in the simulation
//*****************************************************************************

#ifndef MOBILE_NODE_H_DEFINED
#define MOBILE_NODE_H_DEFINED

#include <BeeberIPC.h>

namespace Beeber
{

class MobileNode
{
   public:
      MobileNode();
      virtual ~MobileNode();
      virtual XYPoint Position() = 0;
      virtual void    RunSingleCycle();
      virtual double  SpeedInMillimetersPerSecond() = 0;

   protected:
      double CycleTimeInSeconds();

};

typedef vector<MobileNode*> MobileNodeList;

};

#endif
