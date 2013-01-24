#include "SimulatorEngine.h"

namespace Beeber
{

/*****************************************************************************/
SimulatorEngine* SimulatorEngine::_instance = NULL;
/*****************************************************************************/

/*****************************************************************************/
SimulatorEngine& GetSimulatorEngine(){return SimulatorEngine::Instance();}
/*****************************************************************************/

/*****************************************************************************/
SimulatorEngine::SimulatorEngine() :
_cycleTimeInSeconds(1)
/*****************************************************************************/
{
}

/*****************************************************************************/
SimulatorEngine::~SimulatorEngine()
/*****************************************************************************/
{
}

/*****************************************************************************/
BeeberNodeList SimulatorEngine::AllRobots()
/*****************************************************************************/
{
   MobileNodeList all = AllNodes();
   unsigned int n = all.size();
   BeeberNodeList toReturn;
   for (unsigned int c = 0; c < n; c++)
   {
      BeeberNode* next = dynamic_cast<BeeberNode*>(all.at(c));
      if(next)
         toReturn.push_back(next);
   }
   return(toReturn);
}

/*****************************************************************************/
void SimulatorEngine::AddMobileNode(MobileNode* node)
/*****************************************************************************/
{
   AllNodes().push_back(node);
}

/*****************************************************************************/
ObstacleNodeList SimulatorEngine::AllObstacles()
/*****************************************************************************/
{
   MobileNodeList all = AllNodes();
   unsigned int n = all.size();
   ObstacleNodeList toReturn;
   for (unsigned int c = 0; c < n; c++)
   {
      ObstacleNode* next = dynamic_cast<ObstacleNode*>(all.at(c));
      if(next)
         toReturn.push_back(next);
   }
   return(toReturn);
}

/*****************************************************************************/
BeeberMessageList SimulatorEngine::GenerateSensorReportsForAllRobots()
/*****************************************************************************/
{
   BeeberNodeList allRobots = AllRobots();
   BeeberMessageList statusReports;
   BeeberMessage status;
   status.timestamp = time(0);
   status.type = BMT_SENSOR_RPT;
   status.id = 0;
   for(unsigned int c = 0; c < allRobots.size(); c++)
   {
      status.sensorRpt = allRobots.at(c)->Data();
      statusReports.push_back(status);
      status.id++;
   }

   return(statusReports);
}

/*****************************************************************************/
BeeberMessageList SimulatorEngine::GenerateObstacleReportsForObstaclesWithinSensorRange()
/*****************************************************************************/
{
   BeeberNodeList allRobots = AllRobots();
   BeeberMessageList obstacleMessages;
   for(unsigned int c = 0; c < allRobots.size(); c++)
      obstacleMessages = Containers::Append(obstacleMessages, allRobots.at(c)->AllObstaclesWithinSensorRangeAsMessages());
   return(obstacleMessages);
}

/*****************************************************************************/
BeeberNode* SimulatorEngine::GetRobotWithID(int robotID)
/*****************************************************************************/
{
   BeeberNode* toReturn  = NULL;
   BeeberNodeList robots = AllRobots();
   for(unsigned int c = 0; c < robots.size(); c++)
   {
      if(robots.at(c)->RobotID()==robotID)
      {
         toReturn = robots.at(c);
         break;
      }
   }
   return(toReturn);
}

/*****************************************************************************/
SimulatorEngine& SimulatorEngine::Instance()
/*****************************************************************************/
{
   if(_instance==NULL)
      _instance = new SimulatorEngine();
   return(*_instance);
}

/*****************************************************************************/
BeeberMessageList SimulatorEngine::RunSingleCycle()
/*****************************************************************************/
{
   MobileNodeList nodes = AllNodes();
   for(unsigned int c=0; c < nodes.size(); c++)
      nodes.at(c)->RunSingleCycle();

   return(Containers::Append(GenerateSensorReportsForAllRobots(), GenerateObstacleReportsForObstaclesWithinSensorRange()));
}

};
