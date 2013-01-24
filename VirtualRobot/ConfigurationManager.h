//ConfigurationManager
//*****************************************************************************
//A simple class for managing configuration parameters. Subclass and use
//FindValue calls
//*****************************************************************************

#ifndef CONFIG_MANAGER_H_DEFINED
#define CONFIG_MANAGER_H_DEFINED

#include <ctime>
#include <string>
#include <sstream>
#include <map>
using std::string;
using std::istringstream;
using std::map;

typedef map<string, string> LookupValueMap;

namespace Beeber
{

#ifdef WIN32
const string PATH_SEPARATOR = "\\";
#else
const string PATH_SEPARATOR = "/";
#endif

class ConfigurationManager
{
   public:
      ConfigurationManager(string configurationFilename);
      virtual ~ConfigurationManager();

   protected:
      string                     ConfigurationFilename(){return(_configurationFilename);}
      template <typename T> bool FindValue(const string& key, T& value)
      {
         string buffer;
         if(FindValueAsString(key, buffer))
         {
             istringstream input(buffer);
             input>>value;
             return(true);
         }
         else
             return(false);
      }
      bool                       FindValueAsString(const string& key, string& value);

      string                     NameOfFileWithFullQualifiedPath(string filename);
      string                     PathSeparator(){return(string(PATH_SEPARATOR));}
      virtual string             WorkingDirectory();

   private:
      LookupValueMap&            LookupCache(){return(_lookupCache);}

   private:
     string                     _configurationFilename;
     LookupValueMap             _lookupCache;
};

};

#endif
