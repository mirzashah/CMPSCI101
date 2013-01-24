#include "BeeberSim.h"
#include "BeeberNode.h"
#include "ObstacleNode.h"
#include "SimulatorEngine.h"
#include <BeeberIPC.h>

#include <iostream>
using std::cout;
using std::endl;

namespace Beeber
{

namespace Simulator
{

int g_robotIDCounter = 0;

//These are to protect the calls for VirtualRobot's multiple threads from clashing
Beeber::Semaphore g_callProtect;
void Lock(){g_callProtect.Lock();}
void Unlock(){g_callProtect.Unlock();}

/*****************************************************************************/
void AddNewObstacle(double xInMillimeters, double yInMillimeters, double radiusInMillimeters,  bool isAlreadyDetected)
/*****************************************************************************/
{
   Lock();
   GetSimulatorEngine().AddMobileNode(new ObstacleNode(xInMillimeters, yInMillimeters, radiusInMillimeters, isAlreadyDetected));
   Unlock();
}

/*****************************************************************************/
int AddNewRobot(double xInMillimeters, double yInMillimeters, double headingInDegrees, double speedInMillimetersPerSecond)
/*****************************************************************************/
{
   Lock();
   GetSimulatorEngine().AddMobileNode(new BeeberNode(g_robotIDCounter, xInMillimeters, yInMillimeters, headingInDegrees, speedInMillimetersPerSecond));
   int toReturn = g_robotIDCounter++;
   Unlock();
   return(toReturn);
}

/*****************************************************************************/
void CommandRobotToGoToPoint(int robotID, double xInMillimeters, double yInMillimeters, double speedInMillimetersPerSecond, double arrivalThresholdInMillimeters)
/*****************************************************************************/
{
   Lock();
   BeeberNode* robot = GetSimulatorEngine().GetRobotWithID(robotID);
   if(robot != NULL)
   {
      robot->CommandBeeberToXY(BuildDriveToXYCommand(xInMillimeters, yInMillimeters, speedInMillimetersPerSecond, arrivalThresholdInMillimeters));
   }
   else
      cout << "BeeberSim: Could not find robot to command." << endl;
   Unlock();
}

/*****************************************************************************/
BeeberMessageList RunSingleSimulatorEngineCycle()
/*****************************************************************************/
{
   Lock();
   BeeberMessageList toReturn = GetSimulatorEngine().RunSingleCycle();
   Unlock();
   return(toReturn);
}

/*****************************************************************************/
void SetSimulatorTimestepGranularityInSeconds(double seconds)
/*****************************************************************************/
{
   Lock();
   GetSimulatorEngine().CycleTimeInSeconds(seconds);
   Unlock();
}

/*****************************************************************************/
SensorReport GetLatestRobotStatus(int robotID)
/*****************************************************************************/
{
   SensorReport toReturn;
   Lock();
   Beeber::BeeberNode* bot = GetSimulatorEngine().GetRobotWithID(robotID);
   toReturn = bot->Data();
   Unlock();
   return(toReturn);
}

/*****************************************************************************/
ObstacleReport GetObstacle(int obstacleIndex)
/*****************************************************************************/
{
   ObstacleReport toReturn;
   Lock();
   toReturn = GetSimulatorEngine().AllObstacles().at(obstacleIndex)->Data();
   Unlock();
   return(toReturn);
}

/*****************************************************************************/
int NumberOfObstacles()
/*****************************************************************************/
{
   int toReturn;
   Lock();
   toReturn = GetSimulatorEngine().AllObstacles().size();
   Unlock();
   return toReturn;
}

/*****************************************************************************/
void SetRobotSensorRange(int robotID, double rangeInMillimeters)
/*****************************************************************************/
{
   Lock();
   GetSimulatorEngine().GetRobotWithID(robotID)->SensorRangeInMillimeters(rangeInMillimeters);
   Unlock();
}

/*****************************************************************************/
void SetRobotTurnRate(int robotID, double turnRateInDegreesPerSecond)
/*****************************************************************************/
{
   Lock();
   GetSimulatorEngine().GetRobotWithID(robotID)->TurnRateInDegreesPerSecond(turnRateInDegreesPerSecond);
   Unlock();
}

}
}
