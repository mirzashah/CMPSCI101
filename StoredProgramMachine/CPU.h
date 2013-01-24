//CPU.h
//*****************************************************************************
//Represents the Central Processing Unit (CPU) of the stored program computer.
//*****************************************************************************

#ifndef CPU_H_DEFINED
#define CPU_H_DEFINED

#include "MemoryUnit.h"

class CPU
{
   public:
      CPU();
      ~CPU();

      void        RunProgram();
      void        RunSingleCycle();

   private:
      int         CurrentInstructionAddress(){return(_currentInstructionAddress);}
      void        CurrentInstructionAddress(int newAddress){_currentInstructionAddress = newAddress;}
      int         CPUCycle(){return(_cpuCycle);}
      void        CPUCycle(int cycle){_cpuCycle = cycle;}
      void        ExecuteInstruction(Instruction i);
      MemoryUnit& Memory();
      void        PrintCPUState();

   private: //Memory calls
      Instruction FetchInstruction(int instructionAddress);
      int         FetchData(int dataAddress);
      void        WriteData(int addr, int data);

   private: //Implementation of Instruction Execution Calls
      void        ExecuteSetInstruction(int addr, int val);
      void        ExecuteSetAInstruction(int addrToAddr, int val);
      void        ExecuteCopyInstruction(int srcAddr, int destAddr);
      void        ExecuteCopyAInstruction(int srcAddr, int addrOfDestAddr);
      void        ExecuteAddInstruction(int arg1, int arg2, int destAddr);
      void        ExecuteSubInstruction(int arg1, int arg2, int destAddr);
      void        ExecuteMultInstruction(int arg1, int arg2, int destAddr);
      void        ExecuteDivInstruction(int arg1, int arg2, int destAddr);
      void        ExecuteJumpInstruction(int jumpAddr);
      void        ExecuteJumpAInstruction(int addrOfJumpAddr);
      void        ExecuteBranchEqInstruction(int arg1, int arg2, int jumpAddr);
      void        ExecuteBranchEqAInstruction(int arg1, int arg2, int addrOfJumpAddr);
      void        ExecuteBranchGTInstruction(int arg1, int arg2, int jumpAddr);
      void        ExecuteBranchGTAInstruction(int arg1, int arg2, int addrOfJumpAddr);
      void        ExecuteBranchLTInstruction(int arg1, int arg2, int jumpAddr);
      void        ExecuteBranchLTAInstruction(int arg1, int arg2, int addrOfJumpAddr);
      void        ExecuteEndInstruction();

   private:
      void        PressAnyKeyToContinue();

   private:
      int         _currentInstructionAddress;
      int         _cpuCycle;
};



#endif
