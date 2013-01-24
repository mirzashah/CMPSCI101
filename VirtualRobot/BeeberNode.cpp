#include "BeeberNode.h"
#include "ObstacleNode.h"
#include "SimulatorEngine.h"
#include <cstring> //I always found it odd memset and memcpy were in string.h aka cstring
#include <cmath>
#include <ctime>

namespace Beeber
{

/*****************************************************************************/
BeeberNode::BeeberNode(int robotID, double xInMillimeters, double yInMillimeters, double headingInDegrees, double speedInMillimetersPerSecond)
/*****************************************************************************/
{
   memset(&(Data()),0x00,sizeof(SensorReport));
   memset(&(LatestCommand()), 0x00, sizeof(DriveToXYCommand));

   Data().robotID = robotID;
   Data().kinematicsInfo.x = xInMillimeters;
   Data().kinematicsInfo.y = yInMillimeters;
   Data().kinematicsInfo.relativeHeadingInDegrees = headingInDegrees;
   Data().kinematicsInfo.velocityInMillimetersPerSecond = speedInMillimetersPerSecond;

   TurnRateInDegreesPerSecond(70);
   SensorRangeInMillimeters(500);
}

/*****************************************************************************/
BeeberNode::~BeeberNode()
/*****************************************************************************/
{
}

/*****************************************************************************/
BeeberMessageList BeeberNode::AllObstaclesWithinSensorRangeAsMessages()
/*****************************************************************************/
{
   BeeberMessageList toReturn;
   BeeberMessage msg;
   msg.type        = BMT_OBSTACLE_RPT;
   msg.id          = 0;
   msg.timestamp   = time(NULL);
   msg.requiresAck = false;

   ObstacleNodeList obstaclesWithinRange = AllObstaclesWithinSensorRange();
   for(unsigned int c = 0; c < obstaclesWithinRange.size(); c++)
   {
      msg.obstacleRpt = obstaclesWithinRange.at(c)->Data();
      toReturn.push_back(msg);
      msg.id++;
   }

   return(toReturn);
}

/*****************************************************************************/
ObstacleNodeList  BeeberNode::AllObstaclesWithinSensorRange()
/*****************************************************************************/
{
   ObstacleNodeList obstacles = GetSimulatorEngine().AllObstacles();
   ObstacleNodeList toReturn;

   for(unsigned int c = 0; c < obstacles.size(); c++)
   {
      ObstacleNode* obstacle = obstacles.at(c);
      if(Distance(obstacle->Position(), Position()) < SensorRangeInMillimeters())
         toReturn.push_back(obstacle);
   }

   return(toReturn);
}

/*****************************************************************************/
void BeeberNode::CheckForDetectedObstaclesAndActiveKnownPresences()
/*****************************************************************************/
{
   //TODO: Make more advanced to model sensors more realistically
   ObstacleNodeList nodesInRange = AllObstaclesWithinSensorRange();
   for(unsigned int c=0; c<nodesInRange.size(); c++)
      nodesInRange.at(c)->IsAlreadyDetected(true);
}


/*****************************************************************************/
void BeeberNode::RunSingleCycle()
/*****************************************************************************/
{
   //TODO: Refactor this, I kept changing to get steering rules right...
   double heading = HeadingInDegrees();
   UpdateHeadingAndSpeedToReachCommandedWaypoint();
   double headingDiff = fabs(HeadingInDegrees() - heading);
   while(headingDiff > 360.0f)
      headingDiff = headingDiff - 360.0f;
   //if(headingDiff < 0.1)
      UpdatePosition();
   //End TODO

   CheckForDetectedObstaclesAndActiveKnownPresences();
}

/*****************************************************************************/
XYPoint BeeberNode::Position()
/*****************************************************************************/
{
   return(XYPoint(Data().kinematicsInfo.x, Data().kinematicsInfo.y));
}

/*****************************************************************************/
double BeeberNode::SpeedInMillimetersPerSecond()
/*****************************************************************************/
{
   return(Data().kinematicsInfo.velocityInMillimetersPerSecond);
}

/*****************************************************************************/
double BeeberNode::DesiredHeadingInDegrees()
/*****************************************************************************/
{
   double desired = GetHeadingToPoint(Position(), LatestCommandedWaypoint());
   return(desired);
}

/*****************************************************************************/
ObstacleReportList BeeberNode::AllObstaclesAsObstacleReportList()
/*****************************************************************************/
{
   ObstacleNodeList obstacles = GetSimulatorEngine().AllObstacles();
   ObstacleReportList toReturn;
   for(unsigned int c=0; c<obstacles.size(); c++)
      toReturn.push_back(obstacles.at(c)->Data());
   return(toReturn);
}

/*****************************************************************************/
double BeeberNode::CalculateChangeInHeading()
/*****************************************************************************/
{
   //Note: Collision avoidance is handled here.
   double closestHeadingToDesiredHeading =  Beeber::CollisionAvoidance::GetClosestNonCollisionHeadingInDegrees(Position(), SpeedInMillimetersPerSecond(), DesiredHeadingInDegrees(), AllObstaclesAsObstacleReportList());

   double deltaTheta;
   double turnRateInDegPerSec   = TurnRateInDegreesPerSecond();

   double currentHeading        = HeadingInDegrees();
   double deltaDegreesLeft      = DeltaDegreesTurningLeft(currentHeading, closestHeadingToDesiredHeading);
   double deltaDegreesRight     = DeltaDegreesTurningRight(currentHeading, closestHeadingToDesiredHeading);

   if (deltaDegreesLeft <= deltaDegreesRight) // Turn Left
   {
      if (deltaDegreesLeft < turnRateInDegPerSec)
         deltaTheta = deltaDegreesLeft;
      else
         deltaTheta = turnRateInDegPerSec;
   }
   else //Turn Right
   {
      if (deltaDegreesRight < turnRateInDegPerSec)
         deltaTheta = -1 * deltaDegreesRight;
      else
         deltaTheta = -1 * turnRateInDegPerSec;
   }

   return(deltaTheta * CycleTimeInSeconds());
}

/*****************************************************************************/
void BeeberNode::UpdateHeadingAndSpeedToReachCommandedWaypoint()
/*****************************************************************************/
{
   XYPoint currentDest = LatestCommandedWaypoint();

   if(Distance(Position(), LatestCommandedWaypoint()) <= LatestCommand().arrivalThresholdInMillimeters)
   {
      Data().kinematicsInfo.velocityInMillimetersPerSecond = 0; //Full stop
   }
   else
   {
      Data().kinematicsInfo.velocityInMillimetersPerSecond = LatestCommand().speedInMillimetersPerSecond;

      double newHdg = HeadingInDegrees() + CalculateChangeInHeading();

      while(newHdg >= 360.0)
          newHdg = newHdg - 360.0;

      while(newHdg < 0)
          newHdg = newHdg + 360.0;

      HeadingInDegrees(newHdg);
   }
}

/*****************************************************************************/
void BeeberNode::UpdatePosition()
/*****************************************************************************/
{
   SensorReport& data    = Data();
   double speed          = data.kinematicsInfo.velocityInMillimetersPerSecond;
   double hdg            = Deg2Rad(data.kinematicsInfo.relativeHeadingInDegrees);
   double x              = data.kinematicsInfo.x;
   double y              = data.kinematicsInfo.y;
   double deltaX         = (speed * CycleTimeInSeconds()) * cos(hdg);
   double deltaY         = (speed * CycleTimeInSeconds()) * sin(hdg);
   data.kinematicsInfo.x = x + deltaX;
   data.kinematicsInfo.y = y + deltaY;
}

}
