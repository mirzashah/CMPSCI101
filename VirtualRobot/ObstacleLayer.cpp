#include "ObstacleLayer.h"
#include <BeeberSim.h>
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

namespace Beeber
{

/*****************************************************************************/
ObstacleLayer::ObstacleLayer()
/*****************************************************************************/
{
}

/*****************************************************************************/
ObstacleLayer::~ObstacleLayer()
/*****************************************************************************/
{
}

/*****************************************************************************/
void ObstacleLayer::OnDraw()
/*****************************************************************************/
{
   DrawAllObstacles();
}

/*****************************************************************************/
void ObstacleLayer::OnTimer()
/*****************************************************************************/
{
   Layer::OnTimer();
}

/*****************************************************************************/
void ObstacleLayer::DrawAllObstacles()
/*****************************************************************************/
{
   ObstacleReportList obstacles = Obstacles();
   for(unsigned int c = 0; c < obstacles.size(); c++)
      DrawObstacle(obstacles.at(c));
}

/*****************************************************************************/
void ObstacleLayer::DrawObstacle(const ObstacleReport& obstacle)
/*****************************************************************************/
{
   Drawing::SetColor(200,0,0);
   glLineWidth(2);
   Drawing::Circle(XYPoint(obstacle.xInMillimeters, obstacle.yInMillimeters), obstacle.radiusInMillimeters*2, false);

   const int OBSTACLE_GLYPH_DIAMETER = 10;
   Drawing::SetColor(240,100,20);
   Drawing::CircleDevice(XYPoint(obstacle.xInMillimeters, obstacle.yInMillimeters), OBSTACLE_GLYPH_DIAMETER, true);
}

/*****************************************************************************/
void ObstacleLayer::MergeWithExistingObstacleIfPossible(const ObstacleReport& report)
/*****************************************************************************/
{

   XYPoint newObstaclePos(report.xInMillimeters, report.yInMillimeters);
   const double mergeThresholdInMillimeters = 15;
   ObstacleReportList& obstacles = Obstacles();
   for(unsigned int c = 0; c < obstacles.size(); c++)
   {
      ObstacleReport& current = obstacles.at(c);
      XYPoint currentPos(current.xInMillimeters, current.yInMillimeters);
      if(Distance(currentPos, newObstaclePos) <= mergeThresholdInMillimeters)
      {
         current = report;
         return;
      }
   }

   //Could not merge...
   obstacles.push_back(report);
}

/*****************************************************************************/
void ObstacleLayer::OnIncomingMessage(time_t timestamp, const ObstacleReport& report)
/*****************************************************************************/
{
   MergeWithExistingObstacleIfPossible(report);
}


}
