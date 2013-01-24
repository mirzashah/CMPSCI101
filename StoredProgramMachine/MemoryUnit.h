//MemoryUnit.h
//*****************************************************************************
//Represents the Memory Unit (MU) of the Stored Program Computer
//*****************************************************************************

#ifndef MEMORY_UNIT_H_DEFINED
#define MEMORY_UNIT_H_DEFINED

#include "Instruction.h"
#include <map>
using std::map;

typedef map<int, Instruction> InstructionMemoryUnit ;
typedef map<int, int>         DataMemoryUnit;

class MemoryUnit
{
   public:
      ~MemoryUnit();
      static MemoryUnit& Instance();
      void           LoadProgram(InstructionList program);
      Instruction    FetchInstruction(int instructionAddress);
      int            FetchData(int dataAddress);
      void           WriteData(int dataAddress, int data);
      void           PrintMemoryState();

   private:
      MemoryUnit();
      template <typename S, typename T> bool ContainsKey(const map<S,T>& m, const S& key)
      {
         typename std::map<S, T>::const_iterator itr;
         for(itr = m.begin(); itr!=m.end(); itr++)
         {
            if(itr->first == key)
               return(true);
         }
         return(false);
      }

   private:
      InstructionMemoryUnit _instructionMemory;
      DataMemoryUnit        _dataMemory;
      static MemoryUnit*    _instance;
};

MemoryUnit& GetMemoryUnit();

#endif
