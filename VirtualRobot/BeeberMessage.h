//BeeberMessage.h
//*****************************************************************************
//Defines the main structure used in encoding messages used in Beeber internal
//communications
//*****************************************************************************

#ifndef BEEBER_MESSAGE_H_DEFINED
#define BEEBER_MESSAGE_H_DEFINED

#include <ctime>
#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::map;

namespace Beeber
{

enum BeeberMessageType
{
   BMT_ACK,
   BMT_DRIVE_CMD,
   BMT_DRIVETOXY_CMD,
   BMT_SENSOR_RPT,
   BMT_EMOTION_RPT,
   BMT_OBSTACLE_RPT
};


enum AckState
{
   MSG_RECEIVED,
   CMD_FAILED,
   CMD_FINISHED,
};

struct Ack
{
   int      ackedMsgID;
   AckState ackState;
};

struct DriveCommand
{
   int velocityInMillimetersPerSecond;
   int turningRadiusInMillimeters;
};

struct KinematicSensorActivity
{
   float x; //Millimeters
   float y; //Millimeters
   float relativeHeadingInDegrees;
   int distanceInMillimeters;
   int angleTurnedInDegrees;
   int velocityInMillimetersPerSecond;
   int turningRadiusInMillimeters;
};

struct ProbeSensorActivity
{
   bool  bumperFrontLeft;
   bool  bumperFrontRight;
   bool  wheelDropLeft;
   bool  wheelDropRight;
   bool  cliffLeft;
   bool  cliffFrontLeft;
   bool  cliffFrontRight;
   bool  cliffRight;
   int   percentageChargeRemaining;
   bool  isCharging;
};

struct SensorReport
{
   int robotID;
   KinematicSensorActivity kinematicsInfo;
   ProbeSensorActivity     probeInfo;
};

enum EmotionSpectrumType
{
   EST_FIRST               = 0, //Delimiter
   BRAVE_AFRAID            = 0,
   HAPPY_SAD               = 1,
   PEACEFUL_ANGRY          = 2,
   LOVED_LONELY            = 3,
   SOCIAL_INDIVIDUALISTIC  = 4,
   CURIOUS_APATHETIC       = 5,
   SATIATED_HUNGRY         = 6,
   EXCITED_BORED           = 7,
   PROACTIVE_LAZY          = 8,
   CONTENT_FRUSTRATED      = 9,
   EST_LAST                = 9, //Delimiter
};

struct EmotionReport
{
   float emotionValues[(int)(EST_LAST) + 1]; //Cast int index to type EmotionSpectrumType
};

typedef map<EmotionSpectrumType, float> EmotionMap;

struct ObstacleReport
{
   int    sensingRobotID;
   double xInMillimeters;
   double yInMillimeters;
   double radiusInMillimeters;
};

typedef vector<ObstacleReport> ObstacleReportList;

struct DriveToXYCommand
{
   double xInMillimeters;
   double yInMillimeters;
   double speedInMillimetersPerSecond;
   double arrivalThresholdInMillimeters;
};

struct BeeberMessage
{
   int               id;
   time_t            timestamp;
   bool              requiresAck;
   BeeberMessageType type;
   union
   {
      Ack              ack;
      DriveCommand     driveCmd;
      DriveToXYCommand driveToXYCmd;
      SensorReport     sensorRpt;
      EmotionReport    emotionRpt;
      ObstacleReport   obstacleRpt;
   };

   string TypeAsString() const;
   void   PrintMessageInfo() const;
};

typedef vector<BeeberMessage> BeeberMessageList;

string                        BeeberMessageTypeToString(const BeeberMessageType& msgType);
string                        BeeberEmotionSpectrumToString(const EmotionSpectrumType& type);

//These are functions representing constructors for structs. Cannot use actual constructors because of use of union.
SensorReport                  BuildSensorReport(const KinematicSensorActivity& kinematicInfo, const ProbeSensorActivity& probeInfo);
KinematicSensorActivity       BuildKinematicSensorActivity(float x, float y, int relativeHeadingInDegrees, int distanceInMillimeters, int angleTurnedInDegrees, int velocityInMillimetersPerSecond, int turningRadiusInMillimeters);
ProbeSensorActivity           BuildProbeSensorActivity(bool bumperFrontLeft, bool bumperFrontRight, bool cliffFrontLeft, bool cliffFrontRight, bool cliffLeft, bool cliffRight, int percentageChargeRemaining, bool isCharging, bool wheelDropLeft, bool wheelDropRight);
DriveCommand                  BuildDriveCommand(int velocityInMillimetersPerSecond, int turnRadiusInMillimeters);
DriveToXYCommand              BuildDriveToXYCommand(double xInMillimeters, double yInMillimeters, double speedInMillimetersPerSecond, double arrivalThresholdInMillimeters);
EmotionReport                 BuildEmotionReport(const EmotionMap& emotionValues);
ObstacleReport                BuildObstacleReport(int sensingRobotID, double xInMillimetrs, double yInMillimeters, double rInMillimeters);
};

#endif
