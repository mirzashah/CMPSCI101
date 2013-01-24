//ObstacleNode.h
//*****************************************************************************
//Represents an obstacle node
//*****************************************************************************

#ifndef OBSTACLE_NODE_H_DEFINED
#define OBSTACLE_NODE_H_DEFINED

#include "MobileNode.h"

namespace Beeber
{

class ObstacleNode : public MobileNode
{
   public:
      ObstacleNode(double xInMillimeters, double yInMillimeters, double radiusInMillimeters, bool isAlreadyDetected);
      virtual ~ObstacleNode();

      ObstacleReport& Data(){return(_data);}
      bool            IsAlreadyDetected(){return(_isAlreadyDetected);}
      void            IsAlreadyDetected(bool isIt){_isAlreadyDetected = isIt;}
      virtual XYPoint Position();
      virtual double  SpeedInMillimetersPerSecond();
      virtual void    RunSingleCycle();

   private:
      ObstacleReport _data;
      bool           _isAlreadyDetected;


};

typedef vector<ObstacleNode*> ObstacleNodeList;

};

#endif
