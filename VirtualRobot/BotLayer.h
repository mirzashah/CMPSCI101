//BotLayer.h
//*****************************************************************************
//Draws the bot's position, history, and any obstacles it encounters.
//*****************************************************************************

#ifndef BOT_LAYER_H_DEFINED
#define BOT_LAYER_H_DEFINED

#include "Layer.h"
#include <BeeberIPC.h>

namespace Beeber
{

struct TimedSensorReport
{
   TimedSensorReport(time_t timestampIn, const SensorReport& reportIn){timestamp = timestampIn; report = reportIn;}
   time_t       timestamp;
   SensorReport report;
};

typedef vector<TimedSensorReport> SensorReportList;

class BotLayer : public Layer
{
   public:
      BotLayer();
      virtual ~BotLayer();

      virtual void      OnDraw();
      virtual void      OnTimer();
      virtual void      OnMouseDown(MouseButton button);

   private:
      double            ArrivalThresholdToUseForDriveToXYCommands(){return(55.0f);} //TODO: From file, alternative interface?
      double            SpeedToUseForDriveToXYCommands(){return(150.0f);} //TODO: Same as above

      void              CommandRobotToNewPosition(const XYPoint& p);
      XYPoint           CurrentDestination(){return(_currentDestination);}
      void              CurrentDestination(const XYPoint& newDestination){_currentDestination = newDestination;}

      void              DrawCurrentDestination();
      void              DrawRobot();
      void              DrawHistory();
      void              DrawRobotInfo();
      virtual void      OnIncomingMessage(time_t timestamp, const SensorReport& report);
      SensorReportList& SensorReports(){return(_sensorReports);}
      void              SensorReports(const SensorReportList& reports){_sensorReports = reports;}
      static bool       LessThan(TimedSensorReport rpt1,TimedSensorReport rpt2);

   private:
      SensorReportList _sensorReports;
      XYPoint          _currentDestination;
};

};

#endif
