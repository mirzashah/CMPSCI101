//BeeberNode.h
//*****************************************************************************
//Represents a Beeber
//*****************************************************************************

#ifndef BEEBER_NODE_H_DEFINED
#define BEEBER_NODE_H_DEFINED

#include "MobileNode.h"
#include "ObstacleNode.h"

namespace Beeber
{

class BeeberNode : public MobileNode
{
   public:
      BeeberNode(int robotID, double xInMillimeters, double yInMillimeters, double headingInDegrees, double speedInMillimetersPerSecond);
      virtual ~BeeberNode();

      void              CommandBeeberToXY(const DriveToXYCommand& cmd){_latestCommand = cmd;}
      SensorReport&     Data(){return(_data);}
      BeeberMessageList AllObstaclesWithinSensorRangeAsMessages();
      ObstacleNodeList  AllObstaclesWithinSensorRange();
      virtual XYPoint   Position();
      virtual double    SpeedInMillimetersPerSecond();
      double            DesiredHeadingInDegrees();
      double            HeadingInDegrees(){return(Data().kinematicsInfo.relativeHeadingInDegrees);}
      void              HeadingInDegrees(double hdg){Data().kinematicsInfo.relativeHeadingInDegrees = hdg;}
      double            SensorRangeInMillimeters(){return(_sensorRangeInMillimeters);}
      void              SensorRangeInMillimeters(double range){_sensorRangeInMillimeters = range;}
      int               RobotID(){return(Data().robotID);}
      double            TurnRateInDegreesPerSecond(){return(_turnRateInDegreesPerSecond);}
      void              TurnRateInDegreesPerSecond(double turnRate){_turnRateInDegreesPerSecond = turnRate;}

   protected:
      double            CalculateChangeInHeading();
      void              CheckForDetectedObstaclesAndActiveKnownPresences();
      virtual void      RunSingleCycle();
      void              UpdatePosition();
      void              UpdateHeadingAndSpeedToReachCommandedWaypoint();

   private:
      ObstacleReportList AllObstaclesAsObstacleReportList();
      DriveToXYCommand&  LatestCommand(){return(_latestCommand);}
      XYPoint            LatestCommandedWaypoint(){return(XYPoint(LatestCommand().xInMillimeters, LatestCommand().yInMillimeters));}

   private:
      SensorReport     _data;
      DriveToXYCommand _latestCommand;
      double           _sensorRangeInMillimeters;
      double           _turnRateInDegreesPerSecond;
};

typedef vector<BeeberNode*> BeeberNodeList;

};

#endif
