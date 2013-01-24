#include "BeeberMessage.h"
#include <iostream>
using std::cout;
using std::endl;

namespace Beeber
{

/*****************************************************************************/
string BeeberMessageTypeToString(const BeeberMessageType& msgType)
/*****************************************************************************/
{
   switch(msgType)
   {
      case BMT_ACK: return("Ack");
      case BMT_DRIVE_CMD: return("Drive Command");
      case BMT_SENSOR_RPT: return("Sensor Report");
      case BMT_DRIVETOXY_CMD: return("Drive-To-XY Command");
      case BMT_OBSTACLE_RPT: return("Obstacle Report");
      case BMT_EMOTION_RPT: return("Emotion Report");
      default: return("Unknown");
   };
}

/*****************************************************************************/
string BeeberEmotionSpectrumToString(const EmotionSpectrumType& type)
/*****************************************************************************/
{
   switch(type)
   {
      case BRAVE_AFRAID:           return("Brave/Afraid");
      case HAPPY_SAD:              return("Happy/Sad");
      case PEACEFUL_ANGRY:         return("Peaceful/Angry");
      case LOVED_LONELY:           return("Loved/Lonely");
      case SOCIAL_INDIVIDUALISTIC: return("Social/Individualistic");
      case CURIOUS_APATHETIC:      return("Curious/Apathetic");
      case SATIATED_HUNGRY:        return("Satiated/Hungry");
      case EXCITED_BORED:          return("Excited/Bored");
      case PROACTIVE_LAZY:         return("Proactive/Lazy");
      case CONTENT_FRUSTRATED:     return("Content/Frustrated");
      default: return("Unknown");

   };
}

/*****************************************************************************/
string BeeberMessage::TypeAsString() const
/*****************************************************************************/
{
   return(BeeberMessageTypeToString(type));
}

/*****************************************************************************/
void BeeberMessage::PrintMessageInfo() const
/*****************************************************************************/
{
   cout<<"Type: "<<TypeAsString();
   cout<<"ID: "<<id;
   cout<<"Timestamp (UTC): "<<timestamp<<endl;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

/*****************************************************************************/
SensorReport BuildSensorReport(int robotID, const KinematicSensorActivity& kinematicInfo, const ProbeSensorActivity& probeInfo)
/*****************************************************************************/
{
   SensorReport toReturn;
   toReturn.robotID = robotID;
   toReturn.kinematicsInfo = kinematicInfo;
   toReturn.probeInfo = probeInfo;
   return(toReturn);
}

/*****************************************************************************/
KinematicSensorActivity BuildKinematicSensorActivity(float x, float y, int relativeHeadingInDegrees, int distanceInMillimeters, int angleTurnedInDegrees, int velocityInMillimetersPerSecond, int turningRadiusInMillimeters)
/*****************************************************************************/
{
   KinematicSensorActivity toReturn;

   toReturn.x                              = x;
   toReturn.y                              = y;
   toReturn.relativeHeadingInDegrees       = relativeHeadingInDegrees;
   toReturn.distanceInMillimeters          = distanceInMillimeters;
   toReturn.angleTurnedInDegrees           = angleTurnedInDegrees;
   toReturn.velocityInMillimetersPerSecond = velocityInMillimetersPerSecond;
   toReturn.turningRadiusInMillimeters     = turningRadiusInMillimeters;

   return(toReturn);
}

/*****************************************************************************/
ProbeSensorActivity BuildProbeSensorActivity(bool bumperFrontLeft, bool bumperFrontRight, bool cliffFrontLeft, bool cliffFrontRight, bool cliffLeft, bool cliffRight, int percentageChargeRemaining, bool isCharging, bool wheelDropLeft, bool wheelDropRight)
/*****************************************************************************/
{
   ProbeSensorActivity toReturn;

   toReturn.bumperFrontLeft           = bumperFrontLeft;
   toReturn.bumperFrontRight          = bumperFrontRight;
   toReturn.cliffFrontLeft            = cliffFrontLeft;
   toReturn.cliffFrontRight           = cliffFrontRight;
   toReturn.cliffLeft                 = cliffLeft;
   toReturn.cliffRight                = cliffRight;
   toReturn.percentageChargeRemaining = percentageChargeRemaining;
   toReturn.isCharging                = isCharging;
   toReturn.wheelDropLeft             = wheelDropLeft;
   toReturn.wheelDropRight            = wheelDropRight;

   return(toReturn);
}

/*****************************************************************************/
DriveCommand BuildDriveCommand(int velocityInMillimetersPerSecond, int turnRadiusInMillimeters)
/*****************************************************************************/
{
   DriveCommand toReturn;
   toReturn.velocityInMillimetersPerSecond = velocityInMillimetersPerSecond;
   toReturn.turningRadiusInMillimeters     = turnRadiusInMillimeters;
   return(toReturn);
}

/*****************************************************************************/
DriveToXYCommand BuildDriveToXYCommand(double xInMillimeters, double yInMillimeters, double speedInMillimetersPerSecond, double arrivalThresholdInMillimeters)
/*****************************************************************************/
{
   DriveToXYCommand toReturn;
   toReturn.xInMillimeters = xInMillimeters;
   toReturn.yInMillimeters = yInMillimeters;
   toReturn.speedInMillimetersPerSecond = speedInMillimetersPerSecond;
   toReturn.arrivalThresholdInMillimeters = arrivalThresholdInMillimeters;
   return(toReturn);
}

/*****************************************************************************/
EmotionReport BuildEmotionReport(const EmotionMap& emotionValues)
/*****************************************************************************/
{
   EmotionReport toReturn;
   for(EmotionMap::const_iterator itr = emotionValues.begin(); itr != emotionValues.end(); itr++)
      toReturn.emotionValues[(int)(itr->first)] = itr->second;
   return(toReturn);
}

/*****************************************************************************/
ObstacleReport BuildObstacleReport(int sensingRobotID, double xInMillimeters, double yInMillimeters, double radiusInMillimeters)
/*****************************************************************************/
{
   ObstacleReport toReturn;
   toReturn.sensingRobotID = sensingRobotID;
   toReturn.xInMillimeters = xInMillimeters;
   toReturn.yInMillimeters = yInMillimeters;
   toReturn.radiusInMillimeters = radiusInMillimeters;
   return(toReturn);

}
};
