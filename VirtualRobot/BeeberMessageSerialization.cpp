#include "BeeberMessageSerialization.h"
#include <MOOSGenLib/MOOSGenLib.h>
#include <sstream>
using std::ostringstream;
using std::endl;

namespace Beeber
{

//We use the following as a buffer. The buffer is shared by both serialization and deserialization routines
/*****************************************************************************/
BeeberMessage g_messageBuffer;
string        g_serialBuffer;
BeeberMessage& MessageBuffer(){return(g_messageBuffer);}
void           MessageBuffer(const BeeberMessage& msg){g_messageBuffer = msg;}
string&        SerialBuffer(){return(g_serialBuffer);}
void           SerialBuffer(const string& msg){g_serialBuffer = msg;}
/*****************************************************************************/

/*****************************************************************************/
template <typename T> void AddToSerialBuffer(const string& key, const T& val)
/*****************************************************************************/
{
   MOOSAddValToString(SerialBuffer(), key, val);
}

/*****************************************************************************/
template <typename T> void GetFromSerialBuffer(const string& key, T& val)
/*****************************************************************************/
{
   if (!(MOOSValFromString(val, SerialBuffer(), key, false)))
      throw(BeeberException("Cannot find field-value pair for key " + key));
}

/*****************************************************************************/
template <typename T> void GetEnumFromSerialBuffer(const string& key, T& val)
/*****************************************************************************/
{
   int valAsInt;
   GetFromSerialBuffer(key, valAsInt);
   val = (T)(valAsInt);
}

/*****************************************************************************/
void Deserialize(Ack& ack)
/*****************************************************************************/
{
   GetFromSerialBuffer("AckedMsgId", ack.ackedMsgID);
}

/*****************************************************************************/
void Serialize(const Ack& ack)
/*****************************************************************************/
{
   AddToSerialBuffer("AckedMsgId",  ack.ackedMsgID);
}

/*****************************************************************************/
void Deserialize(DriveCommand& dc)
/*****************************************************************************/
{
   GetFromSerialBuffer("VelocityInMillimetersPerSecond", dc.velocityInMillimetersPerSecond);
   GetFromSerialBuffer("TurningRadiusInMillimeters", dc.turningRadiusInMillimeters);
}

/*****************************************************************************/
void Serialize(const DriveCommand& dc)
/*****************************************************************************/
{
   AddToSerialBuffer("VelocityInMillimetersPerSecond", dc.velocityInMillimetersPerSecond);
   AddToSerialBuffer("TurningRadiusInMillimeters", dc.turningRadiusInMillimeters);
}

/*****************************************************************************/
void Deserialize(DriveToXYCommand& dxyc)
/*****************************************************************************/
{
   GetFromSerialBuffer("XInMillimeters", dxyc.xInMillimeters);
   GetFromSerialBuffer("YInMillimeters", dxyc.yInMillimeters);
   GetFromSerialBuffer("SpeedInMillimeters", dxyc.speedInMillimetersPerSecond);
   GetFromSerialBuffer("ArrivalThresholdInMillimeters", dxyc.arrivalThresholdInMillimeters);
}

/*****************************************************************************/
void Serialize(const DriveToXYCommand& dxyc)
/*****************************************************************************/
{
   AddToSerialBuffer("XInMillimeters", dxyc.xInMillimeters);
   AddToSerialBuffer("YInMillimeters", dxyc.yInMillimeters);
   AddToSerialBuffer("SpeedInMillimeters", dxyc.speedInMillimetersPerSecond);
   AddToSerialBuffer("ArrivalThresholdInMillimeters", dxyc.arrivalThresholdInMillimeters);
}

/*****************************************************************************/
void Deserialize(KinematicSensorActivity& ksa)
/*****************************************************************************/
{
   GetFromSerialBuffer("DistanceInMillimeters", ksa.distanceInMillimeters);
   GetFromSerialBuffer("AngleTurnedInDegrees", ksa.angleTurnedInDegrees);
   GetFromSerialBuffer("TurningRadiusInMillimeters", ksa.turningRadiusInMillimeters);
   GetFromSerialBuffer("VelocityInMillimetersPerSeconds", ksa.velocityInMillimetersPerSecond);
   GetFromSerialBuffer("X", ksa.x);
   GetFromSerialBuffer("Y", ksa.y);
   GetFromSerialBuffer("RelativeHeadingInDegrees", ksa.relativeHeadingInDegrees);

}

/*****************************************************************************/
void Serialize(const KinematicSensorActivity& ksa)
/*****************************************************************************/
{
   AddToSerialBuffer("DistanceInMillimeters", ksa.distanceInMillimeters);
   AddToSerialBuffer("AngleTurnedInDegrees", ksa.angleTurnedInDegrees);
   AddToSerialBuffer("TurningRadiusInMillimeters", ksa.turningRadiusInMillimeters);
   AddToSerialBuffer("VelocityInMillimetersPerSeconds", ksa.velocityInMillimetersPerSecond);
   AddToSerialBuffer("X", ksa.x);
   AddToSerialBuffer("Y", ksa.y);
   AddToSerialBuffer("RelativeHeadingInDegrees", ksa.relativeHeadingInDegrees);
}

/*****************************************************************************/
void Deserialize(ProbeSensorActivity& psa)
/*****************************************************************************/
{
   GetFromSerialBuffer("BumperFrontLeft", psa.bumperFrontLeft);
   GetFromSerialBuffer("BumperFrontRight", psa.bumperFrontRight);
   GetFromSerialBuffer("CliffLeft", psa.cliffLeft);
   GetFromSerialBuffer("CliffFrontLeft", psa.cliffFrontLeft);
   GetFromSerialBuffer("CliffRight", psa.cliffRight);
   GetFromSerialBuffer("CliffFrontRight", psa.cliffFrontRight);
   GetFromSerialBuffer("WheelDropLeft", psa.wheelDropLeft);
   GetFromSerialBuffer("WheelDropRight", psa.wheelDropRight);
   GetFromSerialBuffer("IsCharging", psa.isCharging);
   GetFromSerialBuffer("PercentageChargeRemaining", psa.percentageChargeRemaining);
}

/*****************************************************************************/
void Serialize(const ProbeSensorActivity& psa)
/*****************************************************************************/
{
   AddToSerialBuffer("BumperFrontLeft", psa.bumperFrontLeft);
   AddToSerialBuffer("BumperFrontRight", psa.bumperFrontRight);
   AddToSerialBuffer("CliffLeft", psa.cliffLeft);
   AddToSerialBuffer("CliffFrontLeft", psa.cliffFrontLeft);
   AddToSerialBuffer("CliffRight", psa.cliffRight);
   AddToSerialBuffer("CliffFrontRight", psa.cliffFrontRight);
   AddToSerialBuffer("WheelDropLeft", psa.wheelDropLeft);
   AddToSerialBuffer("WheelDropRight", psa.wheelDropRight);
   AddToSerialBuffer("IsCharging", psa.isCharging);
   AddToSerialBuffer("PercentageChargeRemaining", psa.percentageChargeRemaining);
}

/*****************************************************************************/
void Deserialize(SensorReport& sr)
/*****************************************************************************/
{
   GetFromSerialBuffer("RobotID", sr.robotID);
   Deserialize(sr.kinematicsInfo);
   Deserialize(sr.probeInfo);
}

/*****************************************************************************/
void Serialize(const SensorReport& sr)
/*****************************************************************************/
{
   AddToSerialBuffer("RobotID", sr.robotID);
   Serialize(sr.kinematicsInfo);
   Serialize(sr.probeInfo);
}

/*****************************************************************************/
void Deserialize(EmotionReport& er)
/*****************************************************************************/
{
   for(unsigned int c = (int)(EST_FIRST); c <= (int)(EST_LAST); c++)
   {
      ostringstream label;
      label<<"Value"<<c;
      GetFromSerialBuffer(label.str(), er.emotionValues[c]);
   }
}

/*****************************************************************************/
void Serialize(const EmotionReport& er)
/*****************************************************************************/
{
   for(unsigned int c = (int)(EST_FIRST); c <= (int)(EST_LAST); c++)
   {
      ostringstream label;
      label<<"Value"<<c;
      AddToSerialBuffer(label.str(), er.emotionValues[c]);
   }
}

/*****************************************************************************/
void Deserialize(ObstacleReport& obr)
/*****************************************************************************/
{
   GetFromSerialBuffer("SensingRobotID", obr.sensingRobotID);
   GetFromSerialBuffer("XInMillimeters", obr.xInMillimeters);
   GetFromSerialBuffer("YInMillimeters", obr.yInMillimeters);
   GetFromSerialBuffer("RadiusInMillimeters", obr.radiusInMillimeters);
}

/*****************************************************************************/
void Serialize(const ObstacleReport& obr)
/*****************************************************************************/
{
   AddToSerialBuffer("SensingRobotID", obr.sensingRobotID);
   AddToSerialBuffer("XInMillimeters", obr.xInMillimeters);
   AddToSerialBuffer("YInMillimeters", obr.yInMillimeters);
   AddToSerialBuffer("RadiusInMillimeters", obr.radiusInMillimeters);
}

/*****************************************************************************/
const BeeberMessage& Deserialize(const string& serializedMsg)
/*****************************************************************************/
{
   SerialBuffer(serializedMsg);
   BeeberMessage& msgBuffer = MessageBuffer();

   GetEnumFromSerialBuffer("Type",    msgBuffer.type);
   GetFromSerialBuffer("ID",          msgBuffer.id);
   GetFromSerialBuffer("Timestamp",   msgBuffer.timestamp);
   GetFromSerialBuffer("RequiresAck", msgBuffer.requiresAck);

   switch(msgBuffer.type)
   {
      case BMT_ACK:           Deserialize(msgBuffer.ack); break;
      case BMT_DRIVE_CMD:     Deserialize(msgBuffer.driveCmd); break;
      case BMT_DRIVETOXY_CMD: Deserialize(msgBuffer.driveToXYCmd); break;
      case BMT_SENSOR_RPT:    Deserialize(msgBuffer.sensorRpt); break;
      case BMT_EMOTION_RPT:   Deserialize(msgBuffer.emotionRpt); break;
      case BMT_OBSTACLE_RPT:  Deserialize(msgBuffer.obstacleRpt); break;
      default:                throw(BeeberException("Unknown message type"));
   }

   return(msgBuffer);
}

/*****************************************************************************/
string Serialize(const BeeberMessage& msg)
/*****************************************************************************/
{
   SerialBuffer("");
   MessageBuffer(msg);

   AddToSerialBuffer("Type",        msg.type);
   AddToSerialBuffer("ID",          msg.id);
   AddToSerialBuffer("Timestamp",   msg.timestamp);
   AddToSerialBuffer("RequiresAck", msg.requiresAck);

   switch(msg.type)
   {
      case BMT_ACK:           Serialize(msg.ack); break;
      case BMT_DRIVE_CMD:     Serialize(msg.driveCmd); break;
      case BMT_DRIVETOXY_CMD: Serialize(msg.driveToXYCmd); break;
      case BMT_SENSOR_RPT:    Serialize(msg.sensorRpt); break;
      case BMT_EMOTION_RPT:   Serialize(msg.emotionRpt); break;
      case BMT_OBSTACLE_RPT:  Serialize(msg.obstacleRpt); break;
      default: throw(BeeberException("Unknown message type"));
   };

   string toReturn = SerialBuffer();
   return(toReturn); //Bug?
}

};

