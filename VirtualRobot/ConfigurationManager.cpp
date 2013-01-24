#include "ConfigurationManager.h"
#include "Containers.h"
#include <iostream>
#include <fstream>
using std::ifstream;
using std::cout;
using std::endl;

namespace Beeber
{

/*************************************************************************/
ConfigurationManager::ConfigurationManager(string configFilename) : _configurationFilename(configFilename)
/*************************************************************************/
{
}

/*************************************************************************/
ConfigurationManager::~ConfigurationManager()
/*************************************************************************/
{
}

/*************************************************************************/
bool ConfigurationManager::FindValueAsString(const string& key, string& value)
/*************************************************************************/
{
   if(Containers::ContainsKey(LookupCache(), key)) //If already cached, no need to check file
   {
      value = LookupCache()[key];
      return(true);
   }

   string filename  = ConfigurationFilename();
   ifstream input;
   input.open(filename.c_str());
	bool wasKeyFound = false;

	if(input)
	{
		string currentKey;
		string currentVal;
		while(!input.eof())
		{
			input>>currentKey;
            std::getline(input, currentVal);
			if(currentKey==key)
			{
    			wasKeyFound = true;
            value = currentVal;
            LookupCache()[key] = currentVal;
				break;
			}
		}
		input.close();
	}
	else
        cout<<"ConfigurationManager::FindValueAsString => Could not open input file "<<filename<<endl;

   if(!wasKeyFound)
      cout<<"ConfigurationManager::FindValueAsString => Could not find key "<<key<<endl;

	return(wasKeyFound);
}

/*************************************************************************/
string ConfigurationManager::NameOfFileWithFullQualifiedPath(string filename)
/*************************************************************************/
{
    return(WorkingDirectory() + PathSeparator() + filename);
}

/*************************************************************************/
string ConfigurationManager::WorkingDirectory()
/*************************************************************************/
{
    return("." + PathSeparator());
}
};
