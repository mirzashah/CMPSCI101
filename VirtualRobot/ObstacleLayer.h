//Obstacle Layer
//*****************************************************************************
//Shows any sensor detections
//*****************************************************************************

#ifndef OBSTACLE_LAYER_H_DEFINED
#define OBSTACLE_LAYER_H_DEFINED

#include "Layer.h"
#include <BeeberIPC.h>

namespace Beeber
{

class ObstacleLayer : public Layer
{
   public:
      ObstacleLayer();
      virtual ~ObstacleLayer();

      virtual void        OnDraw();
      virtual void        OnTimer();

   private:
      void                DrawAllObstacles();
      void                DrawObstacle(const ObstacleReport& obstacle);
      void                MergeWithExistingObstacleIfPossible(const ObstacleReport& report);
      void                OnIncomingMessage(time_t timestamp, const ObstacleReport& report);
      ObstacleReportList& Obstacles(){return(_obstacles);}
      void                Obstacles(const ObstacleReportList& obstacles){_obstacles = obstacles;}


   private:
      ObstacleReportList _obstacles;
};

};


#endif
