#include "BeeberConfigurationManager.h"

namespace Beeber
{

/*****************************************************************************/
const string BEEBER_CONFIGFILENAME                                = "RobotConfig.txt";
BeeberConfigurationManager* BeeberConfigurationManager::_instance = NULL;
BeeberConfigurationManager& BeeberConfig(){return(BeeberConfigurationManager::Instance());}
/*****************************************************************************/

/*****************************************************************************/
BeeberConfigurationManager::BeeberConfigurationManager() :
ConfigurationManager(BEEBER_CONFIGFILENAME)
/*****************************************************************************/
{
}

/*****************************************************************************/
BeeberConfigurationManager::~BeeberConfigurationManager()
/*****************************************************************************/
{
}

/*****************************************************************************/
BeeberConfigurationManager& BeeberConfigurationManager::Instance()
/*****************************************************************************/
{
   if(_instance==NULL)
      _instance = new BeeberConfigurationManager();
   return(*_instance);
}

/*****************************************************************************/
string BeeberConfigurationManager::MOOSDB_IPAddress()
/*****************************************************************************/
{
   return("127.0.0.1");
}

/*****************************************************************************/
int BeeberConfigurationManager::MOOSDB_Port()
/*****************************************************************************/
{
   return(9000);
}

/*****************************************************************************/
string BeeberConfigurationManager::WorkingDirectory()
/*****************************************************************************/
{
   return("." + PathSeparator());
}

/*****************************************************************************/
bool BeeberConfigurationManager::IsSimulationInDisplayEnabled()
/*****************************************************************************/
{
   return(true);
}

/*****************************************************************************/
string BeeberConfigurationManager::SoundsFolder()
/*****************************************************************************/
{
   return("." + PathSeparator());
}

/*****************************************************************************/
string BeeberConfigurationManager::DataFolder()
/*****************************************************************************/
{
   return("." + PathSeparator());
}

/*****************************************************************************/
string BeeberConfigurationManager::ImagesFolder()
/*****************************************************************************/
{
   return("." + PathSeparator());
}

/*****************************************************************************/
double BeeberConfigurationManager::ObstacleAvoidanceRadiusInMillimeters()
/*****************************************************************************/
{
   return(100);

}

/*****************************************************************************/
double BeeberConfigurationManager::MinimumTimeTOCPAInSecondsBeforeChangingCourse()
/*****************************************************************************/
{
   return(5);
}

/*****************************************************************************/
double BeeberConfigurationManager::RobotRadiusInMillimeters()
/*****************************************************************************/
{
   return(165.1);
}




}
