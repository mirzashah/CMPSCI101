#ifndef BEEBER_SIM_H_DEFINED
#define BEEBER_SIM_H_DEFINED

#include <BeeberIPC.h>

namespace Beeber
{

namespace Simulator

{
//Adds a new obstacle to the simulation
void              AddNewObstacle(double xInMillimeters, double yInMillimeters, double radiusInMillimeters, bool isAlreadyDetected = false);

//Adds a new robot into the simulation. Returns ID of newly created robot
int               AddNewRobot(double xInMillimeters, double yInMillimeters, double headingInDegrees, double speedInMillimetersPerSecond);

//Command robot to go to a point within certain arrival threshold
void              CommandRobotToGoToPoint(int robotID, double xInMillimeters, double yInMillimeters, double speedInMillimetersPerSecond, double arrivalThresholdInMillimeters);

//Runs a single cycle of the simulation library and returns a list of SensorReport and ObstacleReport messages
BeeberMessageList RunSingleSimulatorEngineCycle();

//Represents the level of detail of the simulation, by default 1 second.
void              SetSimulatorTimestepGranularityInSeconds(double seconds);

//Gets the latest robot status report for a particular robot
SensorReport      GetLatestRobotStatus(int robotID);

//Gets the obstacle report associated with some obstacle
ObstacleReport    GetObstacle(int obstacleID);

//Returns total number of obstacles
int               NumberOfObstacles();

//Set a robot's sensor range
void              SetRobotSensorRange(int robotID, double rangeInMillimeters);

//Set a robot's turn rate
void              SetRobotTurnRate(int robotID, double turnRateInDegreesPerSecond);


}

}


#endif
