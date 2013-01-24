#include "ObstacleNode.h"
#include <cstring>

namespace Beeber
{

/*****************************************************************************/
ObstacleNode::ObstacleNode(double xInMillimeters, double yInMillimeters,  double radiusInMillimeters, bool isAlreadyDetected)
/*****************************************************************************/
{
   memset(&_data, 0x00, sizeof(ObstacleReport));
   Data().xInMillimeters = xInMillimeters;
   Data().yInMillimeters = yInMillimeters;
   Data().radiusInMillimeters = radiusInMillimeters;
   IsAlreadyDetected(isAlreadyDetected);
}

/*****************************************************************************/
ObstacleNode::~ObstacleNode()
/*****************************************************************************/
{
}

/*****************************************************************************/
XYPoint ObstacleNode::Position()
/*****************************************************************************/
{
   return(XYPoint(Data().xInMillimeters, Data().yInMillimeters));
}

/*****************************************************************************/
void ObstacleNode::RunSingleCycle()
/*****************************************************************************/
{
   //No-op
}

/*****************************************************************************/
double ObstacleNode::SpeedInMillimetersPerSecond()
/*****************************************************************************/
{
   return(0);
}



}
