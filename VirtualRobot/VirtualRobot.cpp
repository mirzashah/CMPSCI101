#include "VirtualRobot.h"
#include <BeeberDisplayCore.h>
#include <BeeberSim.h>
#include "DisplayThread.h"

using namespace Beeber; //See what I did there ;)

namespace VirtualRobot
{

DisplayThread    g_displayThread;

/*****************************************************************************/
void InitializeVirtualRobot()
/*****************************************************************************/
{
   cout << "VirtualRobot Display" << endl;
   cout << "Copyright (c) 2011, Mirza A. Shah" << endl;
   cout << "**********************************\n" << endl;

   //Initial display stuff

   //Start display thread
   g_displayThread.Start();

   g_displayThread.IsDone().Lock(); //Little hack: Need to make sure display thread is done initializing GLUT, this is how i signal :P

   //TODO: Robot 0 should be added here
   Beeber::Simulator::AddNewRobot(0, 0, 0, 0);
   SetSensorRange(1000);
}

/*****************************************************************************/
void AddObstacle(double x, double y, double obstacleRadiusInMillimeters)
/*****************************************************************************/
{
   Beeber::Simulator::AddNewObstacle(x, y, obstacleRadiusInMillimeters, false);
}

/*****************************************************************************/
static Beeber::XYPoint RobotPosition()
/*****************************************************************************/
{
   SensorReport robotStatus = Beeber::Simulator::GetLatestRobotStatus(0);
   return(XYPoint(robotStatus.kinematicsInfo.x, robotStatus.kinematicsInfo.y));
}

/*****************************************************************************/
void DriveToPoint(double x, double y, double rangeInMillimeters, double speedInMillimetersPerSecond)
/*****************************************************************************/
{
   //Drive to point, do not stop until you get there!
   Beeber::Simulator::CommandRobotToGoToPoint(0, x, y, speedInMillimetersPerSecond, rangeInMillimeters);

   //while(Robot is not at desired point)
   while(Distance(RobotPosition(), XYPoint(x,y)) > rangeInMillimeters)
      Pause(10); //Don't kill the CPU!
}

/*****************************************************************************/
int GetNumberOfObstacles()
/*****************************************************************************/
{
   return Beeber::Simulator::NumberOfObstacles();
}

/*****************************************************************************/
bool GetObstacle(int i, double& x, double& y)
/*****************************************************************************/
{
   Beeber::ObstacleReport obstacle = Beeber::Simulator::GetObstacle(i);
   x = obstacle.xInMillimeters;
   y = obstacle.yInMillimeters;
   return true;
}

/*****************************************************************************/
void SetTurnRate(double turnRateInDegreesPerSecond)
/*****************************************************************************/
{
   Beeber::Simulator::SetRobotTurnRate(0, turnRateInDegreesPerSecond);
}

/*****************************************************************************/
void SetSensorRange(double rangeInMillimeters)
/*****************************************************************************/
{
   Beeber::Simulator::SetRobotSensorRange(0, rangeInMillimeters);
}

/*****************************************************************************/
void WaitForVirtualRobotToFinish()
/*****************************************************************************/
{
   g_displayThread.Join();
}



};
