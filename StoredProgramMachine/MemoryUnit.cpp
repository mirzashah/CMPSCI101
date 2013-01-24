#include "MemoryUnit.h"
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

/*****************************************************************************/
MemoryUnit* MemoryUnit::_instance = NULL;
/*****************************************************************************/

/*****************************************************************************/
MemoryUnit& GetMemoryUnit()
/*****************************************************************************/
{
   return(MemoryUnit::Instance());
}

/*****************************************************************************/
MemoryUnit::MemoryUnit()
/*****************************************************************************/
{
}

/*****************************************************************************/
MemoryUnit::~MemoryUnit()
/*****************************************************************************/
{
}

/*****************************************************************************/
MemoryUnit& MemoryUnit::Instance()
/*****************************************************************************/
{
   if(_instance == NULL)
      _instance = new MemoryUnit();
   return(*_instance);
}

/*****************************************************************************/
void MemoryUnit::LoadProgram(InstructionList program)
/*****************************************************************************/
{
   _instructionMemory = InstructionMemoryUnit(); //Overwrite just incase clear() doesn't work
   unsigned int n = program.size();
   for(unsigned int c = 0; c < n; c++)
      _instructionMemory[c] = program.at(c);
}

/*****************************************************************************/
Instruction MemoryUnit::FetchInstruction(int instructionAddress)
/*****************************************************************************/
{
   if(ContainsKey(_instructionMemory, instructionAddress))
      return(_instructionMemory[instructionAddress]);
   else
   {
      cout<<"Error: No instruction found at memory location I"<<instructionAddress<<endl;
      exit(-1);
   }
}

/*****************************************************************************/
int MemoryUnit::FetchData(int dataAddress)
/*****************************************************************************/
{
   if(ContainsKey(_dataMemory, dataAddress))
      return(_dataMemory[dataAddress]);
   else
   {
      cout<<"Error: No data found at memory location D"<<dataAddress<<endl;
      exit(-1);
   }
}

/*****************************************************************************/
void MemoryUnit::PrintMemoryState()
/*****************************************************************************/
{
   DataMemoryUnit& data = _dataMemory;
   for(DataMemoryUnit::iterator itr = data.begin(); itr != data.end(); itr++)
   {
      cout<<"D"<<itr->first<<": "<<itr->second<<endl;
   }

}

/*****************************************************************************/
void MemoryUnit::WriteData(int dataAddress, int data)
/*****************************************************************************/
{
   _dataMemory[dataAddress] = data;
}
