#ifndef SIMULATOR_ENGINE_H_DEFINED
#define SIMULATOR_ENGINE_H_DEFINED

#include "MobileNode.h"
#include "ObstacleNode.h"
#include "BeeberNode.h"

namespace Beeber
{
class SimulatorEngine
{
   public:
      static SimulatorEngine& Instance();
      virtual ~SimulatorEngine();

      void                    AddMobileNode(MobileNode* node);
      BeeberMessageList       RunSingleCycle();
      BeeberNode*             GetRobotWithID(int robotID);
      BeeberNodeList          AllRobots();
      ObstacleNodeList        AllObstacles();
      double                  CycleTimeInSeconds(){return(_cycleTimeInSeconds);}
      void                    CycleTimeInSeconds(double cycleLength){_cycleTimeInSeconds = cycleLength;}

   private:
      SimulatorEngine();
      MobileNodeList&         AllNodes(){return(_allNodes);}
      BeeberMessageList       GenerateObstacleReportsForObstaclesWithinSensorRange();
      BeeberMessageList       GenerateSensorReportsForAllRobots();

   private:
      double                  _cycleTimeInSeconds;
      static SimulatorEngine* _instance;
      MobileNodeList          _allNodes;
};

SimulatorEngine& GetSimulatorEngine();

};


#endif
