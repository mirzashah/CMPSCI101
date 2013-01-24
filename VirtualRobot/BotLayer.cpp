#include "BotLayer.h"
#include <BeeberIPC.h>
#include <Containers.h>
#include <BeeberSim.h>
#include <cstdlib>
#include <cstring>
#include <sstream>
using std::ostringstream;

namespace Beeber
{

/*****************************************************************************/
BotLayer::BotLayer()
/*****************************************************************************/
{
}

/*****************************************************************************/
BotLayer::~BotLayer()
/*****************************************************************************/
{
}

/*****************************************************************************/
void BotLayer::CommandRobotToNewPosition(const XYPoint& p)
/*****************************************************************************/
{
   double speed = SpeedToUseForDriveToXYCommands();
   double arrivalRadius = ArrivalThresholdToUseForDriveToXYCommands();

   Beeber::Simulator::CommandRobotToGoToPoint(0, p.x, p.y, speed, arrivalRadius);
}

/*****************************************************************************/
void BotLayer::OnDraw()
/*****************************************************************************/
{
   DrawCurrentDestination();
   DrawRobot();
   DrawHistory();
   DrawRobotInfo();
}

/*****************************************************************************/
void BotLayer::DrawCurrentDestination()
/*****************************************************************************/
{
   Drawing::SetColor(100, 149, 237);
   Drawing::CircleDevice(CurrentDestination(), 10, true);
   glLineWidth(3);
   Drawing::Circle(CurrentDestination(), ArrivalThresholdToUseForDriveToXYCommands(), false);
}

/*****************************************************************************/
void BotLayer::DrawRobot()
/*****************************************************************************/
{
   SensorReportList& reports = SensorReports();
   const double DIAMETER_OF_ROOMBA_IN_MILLIMETERS = BeeberConfig().RobotRadiusInMillimeters() * 2;

   if(reports.size() > 0)
   {
      SensorReport current = reports.at(reports.size() - 1).report;
      XYPoint robotPos(current.kinematicsInfo.x, current.kinematicsInfo.y);

      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glTranslated(robotPos.x, robotPos.y, 0);

      //Draw robot body
      SetColor(234, 234, 236); //grey on top of iRobot Create
      Circle(XYPoint(0,0), DIAMETER_OF_ROOMBA_IN_MILLIMETERS, true);
      SetColor(182,179,174); //Grey on bottom of iRobot Create
      glLineWidth(3.0f);
      Circle(XYPoint(0,0), DIAMETER_OF_ROOMBA_IN_MILLIMETERS, false); //Draw an outline around the robot

      //Draw heading pointer
      double heading = current.kinematicsInfo.relativeHeadingInDegrees - 90.0f;

      glRotated(heading, 0, 0, 1);
      glTranslated(0,DIAMETER_OF_ROOMBA_IN_MILLIMETERS / 4,0);
      Circle(XYPoint(0,0), DIAMETER_OF_ROOMBA_IN_MILLIMETERS / 8, true);
      Line(XYPoint(0,0), XYPoint(0, DIAMETER_OF_ROOMBA_IN_MILLIMETERS / 8));

      glPopMatrix();
   }
}

/*****************************************************************************/
void BotLayer::DrawRobotInfo()
/*****************************************************************************/
{
   SensorReportList& reports = SensorReports();
   if(reports.size() > 0)
   {
      SensorReport current = reports.at(reports.size() - 1).report;
      XYPoint robotPos(current.kinematicsInfo.x, current.kinematicsInfo.y);

	   const int leftXOffsetInPixels = 10;
      const int ySpacingInPixels = 18;
      const int bottomYOffsetInPixels = 10 + (2 * ySpacingInPixels);


      Drawing::SetColor(154, 205, 50);
      ostringstream posStr, hdgStr, spdStr;
      posStr.precision(6);
      posStr << "Position: " << std::fixed <<  robotPos.x << ", " << robotPos.y;
      hdgStr << "Heading: " << std::fixed << current.kinematicsInfo.relativeHeadingInDegrees << " deg";
      spdStr << "Speed: " << std::fixed << current.kinematicsInfo.velocityInMillimetersPerSecond << " mm/s";

      Drawing::Text(DevicePoint(leftXOffsetInPixels, bottomYOffsetInPixels), posStr.str(), FN_BITMAP_8_BY_13);
      Drawing::Text(DevicePoint(leftXOffsetInPixels, bottomYOffsetInPixels - ySpacingInPixels), hdgStr.str(), FN_BITMAP_8_BY_13);
      Drawing::Text(DevicePoint(leftXOffsetInPixels, bottomYOffsetInPixels - 2 * ySpacingInPixels), spdStr.str(), FN_BITMAP_8_BY_13);
   }
}

/*****************************************************************************/
void BotLayer::DrawHistory()
/*****************************************************************************/
{
   SensorReportList& reports = SensorReports();

   glColor3f(0.5,0.5,0.5); //Grey?
   glLineWidth(1);
   glBegin(GL_LINE_STRIP);
      for(unsigned int c = 0; c < reports.size(); c++)
      {
         SensorReport& current = reports.at(c).report;
         glVertex2d(current.kinematicsInfo.x, current.kinematicsInfo.y);
      }
   glEnd();
}

/*****************************************************************************/
void BotLayer::OnMouseDown(MouseButton button)
/*****************************************************************************/
{
   XYPoint mousePos;
   switch(button)
   {
      case(MB_MIDDLE):
         mousePos = MousePosition();
         CurrentDestination(mousePos);
         CommandRobotToNewPosition(mousePos);
         break;
      default: break;
   }

   Layer::OnMouseDown(button);
}

/*****************************************************************************/
void BotLayer::OnTimer()
/*****************************************************************************/
{
   Layer::OnTimer(); //Need to call parent version to drive IPC
}

/*****************************************************************************/
void BotLayer::OnIncomingMessage(time_t timestamp, const SensorReport& report)
/*****************************************************************************/
{
   //SensorReports(Containers::Construct(TimedSensorReport(timestamp, report)));
   SensorReports().push_back(TimedSensorReport(timestamp, report));
//   const SensorReportList& all = SensorReports();
//   SensorReportList sorted = Beeber::Containers::SortAscending(all, BotLayer::LessThan);
//  SensorReports(sorted);
}

/*****************************************************************************/
bool BotLayer::LessThan(TimedSensorReport rpt1, TimedSensorReport rpt2)
/*****************************************************************************/
{
   return(rpt1.timestamp < rpt2.timestamp);
}


}
