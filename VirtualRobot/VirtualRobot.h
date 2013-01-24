//VirtualRobot.h
//*****************************************************************************
/*
Header file for the VirtualRobot simulator. Use this as a reference when
coding.
//CMPSCI101 Students - Include this in your program with the line:
#include <VirtualRobot.h>
using namepsace VirtualRobot
*/
//-----------------------------------------------------------------------------
//Copyright (c) 2011, Mirza A. Shah.
//*****************************************************************************

#ifndef VIRTUAL_ROBOT_H_DEFINED
#define VIRTUAL_ROBOT_H_DEFINED

namespace VirtualRobot
{

// Initialize the VirtualRobot simulator
// YOU MUST ALWAYS CALL THIS FUNCTION FIRST
void InitializeVirtualRobot();

//Adds an obstacle to the simulation
void AddObstacle(double x, double y, double obstacleRadiusInMillimeters);

// Drive to some point (x,y). The call does not return until the robot is within range
void DriveToPoint(double x, double y, double rangeInMillimeters, double speedInMillimetersPerSecond);

// Get number of obstacles the robot's sensors have picked up
int  GetNumberOfObstacles();

// Get the x,y position of an obstacle the robot sees. The passed index 'i' must be between 1 and the return value of GetNumberOfObstacles().
// Returns true if i is a valid index, otherwise false. Result stored to x and y.
bool GetObstacle(int i, double& x, double& y);

// Set's the turn rate (i.e. the rate at which the robot can rotate to change direction) of the robot
void SetTurnRate(double turnRateInDegreesPerSecond);

// Set's the sensor range of the robot. The robot has an omnidirectional (i.e 360 degree) sensor that can see obstacles you place on the grid with the
// AddObstacle() function
void SetSensorRange(double rangeInMillimeters);

// Prevents the program from ending prematurely. Use this to stop the program from ending after the robot finishes its last drive command.
void WaitForVirtualRobotToFinish();

};

#endif
