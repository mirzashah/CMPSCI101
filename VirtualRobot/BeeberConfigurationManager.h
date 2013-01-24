//BeeberConfigurationManager.h
//*****************************************************************************
//Managed the global configuration of Beeber software
//*****************************************************************************

#ifndef BEEBER_CONFIGURATION_H_DEFINED
#define BEEBER_CONFIGURATION_H_DEFINED

#include "ConfigurationManager.h"

namespace Beeber
{

class BeeberConfigurationManager : public ConfigurationManager
{
   public:
      static BeeberConfigurationManager& Instance();
      virtual ~BeeberConfigurationManager();

      //The IP Address/Hostname of the MOOSDB IPC Server
      string                             MOOSDB_IPAddress();

      //The listen port of the MOOSDB IPC Server
      int                                MOOSDB_Port();

      //The directory which contains all the software and data folders
      virtual string                     WorkingDirectory();

      //Is the simulator (which is integrated in the display) enabled
      bool                               IsSimulationInDisplayEnabled();

      //The name of the folder in the working directory that contains sound files;
      string                             SoundsFolder();

      //The name of the folder in the working directory that contains misc. data;
      string                             DataFolder();

      //The name of the folder in the working directory that contains image files;
      string                             ImagesFolder();

      //Random stuff that needs to make it into file:
      double                             ObstacleAvoidanceRadiusInMillimeters();
      double                             MinimumTimeTOCPAInSecondsBeforeChangingCourse();
      double                             RobotRadiusInMillimeters();


   private:
      BeeberConfigurationManager();
      static BeeberConfigurationManager* _instance;
};

BeeberConfigurationManager& BeeberConfig();

};

#endif
