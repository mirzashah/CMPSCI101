// Collision Avoidance
//*****************************************************************************
// Simple routines to determine best path to avoid collisions
//*****************************************************************************

#ifndef COLLISION_AVOIDANCE_H_DEFINED
#define COLLISION_AVOIDANCE_H_DEFINED

#include "BeeberMessage.h"
#include "Geometry.h"

namespace Beeber
{

namespace CollisionAvoidance
{


bool WillPathYieldCollision(const XYPoint& currentPosition,
                            double pathHeadingInDegrees,
                            double currentSpeedInMillimetersPerSecond,
                            const ObstacleReportList& obstacles);

struct NoObstacleFreePathsException{};

//Returns the closest heading to some desired heading based on current speed. Throws
//"NoObstacleFreePathsException" if can't find anything
double GetClosestNonCollisionHeadingInDegrees(const XYPoint& currentPosition,
                                              double currentSpeedInMillimetersPerSecond,
                                              double desiredHeadingInDegrees,
                                              const ObstacleReportList& obstacles);


};
};

#endif
