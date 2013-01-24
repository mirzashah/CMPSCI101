#include "CPU.h"
#include <cstdlib>
#include <iostream>
#include <limits>
using std::cout;
using std::endl;
using std::cin;

/*****************************************************************************/
CPU::CPU()
/*****************************************************************************/
{
   CPUCycle(0);
   CurrentInstructionAddress(0);
}

/*****************************************************************************/
CPU::~CPU()
/*****************************************************************************/
{
}

/*****************************************************************************/
void CPU::PressAnyKeyToContinue()
/*****************************************************************************/
{
  std::cout<<"Press [Enter] to continue . . .";
  std::cin.get();
}

/*****************************************************************************/
void CPU::ExecuteSetInstruction(int addr, int val)
/*****************************************************************************/
{
   WriteData(addr, val);
   CurrentInstructionAddress(CurrentInstructionAddress() + 1);
}

/*****************************************************************************/
void CPU::ExecuteSetAInstruction(int addrToAddr, int val)
/*****************************************************************************/
{
   WriteData(FetchData(addrToAddr), val);
   CurrentInstructionAddress(CurrentInstructionAddress() + 1);

}

/*****************************************************************************/
void CPU::ExecuteCopyInstruction(int srcAddr, int destAddr)
/*****************************************************************************/
{
   WriteData(destAddr, FetchData(srcAddr));
   CurrentInstructionAddress(CurrentInstructionAddress() + 1);
}

/*****************************************************************************/
void CPU::ExecuteCopyAInstruction(int srcAddr, int addrOfDestAddr)
/*****************************************************************************/
{
   WriteData(FetchData(addrOfDestAddr), FetchData(srcAddr));
   CurrentInstructionAddress(CurrentInstructionAddress() + 1);
}

/*****************************************************************************/
void CPU::ExecuteAddInstruction(int arg1, int arg2, int destAddr)
/*****************************************************************************/
{
   WriteData(destAddr, FetchData(arg1) + FetchData(arg2));
   CurrentInstructionAddress(CurrentInstructionAddress() + 1);
}

/*****************************************************************************/
void CPU::ExecuteSubInstruction(int arg1, int arg2, int destAddr)
/*****************************************************************************/
{
   WriteData(destAddr, FetchData(arg1) - FetchData(arg2));
   CurrentInstructionAddress(CurrentInstructionAddress() + 1);
}

/*****************************************************************************/
void CPU::ExecuteMultInstruction(int arg1, int arg2, int destAddr)
/*****************************************************************************/
{
   WriteData(destAddr, FetchData(arg1) * FetchData(arg2));
   CurrentInstructionAddress(CurrentInstructionAddress() + 1);
}

/*****************************************************************************/
void CPU::ExecuteDivInstruction(int arg1, int arg2, int destAddr)
/*****************************************************************************/
{
   WriteData(destAddr, FetchData(arg1) / FetchData(arg2));
   CurrentInstructionAddress(CurrentInstructionAddress() + 1);
}

/*****************************************************************************/
void CPU::ExecuteJumpInstruction(int jumpAddr)
/*****************************************************************************/
{
   CurrentInstructionAddress(jumpAddr);
}

/*****************************************************************************/
void CPU::ExecuteJumpAInstruction(int addrOfJumpAddr)
/*****************************************************************************/
{
   ExecuteJumpInstruction(FetchData(addrOfJumpAddr));
}

/*****************************************************************************/
void CPU::ExecuteBranchEqInstruction(int arg1, int arg2, int jumpAddr)
/*****************************************************************************/
{
   if(FetchData(arg1) == FetchData(arg2))
      CurrentInstructionAddress(jumpAddr);
   else
      CurrentInstructionAddress(CurrentInstructionAddress() + 1);
}

/*****************************************************************************/
void CPU::ExecuteBranchEqAInstruction(int arg1, int arg2, int addrOfJumpAddr)
/*****************************************************************************/
{
   ExecuteBranchEqInstruction(arg1, arg2, FetchData(addrOfJumpAddr));
}

/*****************************************************************************/
void CPU::ExecuteBranchGTInstruction(int arg1, int arg2, int jumpAddr)
/*****************************************************************************/
{
   if(FetchData(arg1) > FetchData(arg2))
      CurrentInstructionAddress(jumpAddr);
   else
      CurrentInstructionAddress(CurrentInstructionAddress() + 1);
}

/*****************************************************************************/
void CPU::ExecuteBranchGTAInstruction(int arg1, int arg2, int addrOfJumpAddr)
/*****************************************************************************/
{
   ExecuteBranchGTInstruction(arg1, arg2, FetchData(addrOfJumpAddr));
}

/*****************************************************************************/
void CPU::ExecuteBranchLTInstruction(int arg1, int arg2, int jumpAddr)
/*****************************************************************************/
{
   if(FetchData(arg1) < FetchData(arg2))
      CurrentInstructionAddress(jumpAddr);
   else
      CurrentInstructionAddress(CurrentInstructionAddress() + 1);
}

/*****************************************************************************/
void CPU::ExecuteBranchLTAInstruction(int arg1, int arg2, int addrOfJumpAddr)
/*****************************************************************************/
{
   ExecuteBranchLTInstruction(arg1, arg2, FetchData(addrOfJumpAddr));
}

/*****************************************************************************/
void CPU::ExecuteEndInstruction()
/*****************************************************************************/
{
   exit(1);
}

/*****************************************************************************/
void CPU::ExecuteInstruction(Instruction i)
/*****************************************************************************/
{
   switch(i.opCode)
   {
      case SET:       ExecuteSetInstruction(i.arg1, i.arg2);               break;
      case SETA:      ExecuteSetAInstruction(i.arg1, i.arg2);              break;
      case COPY:      ExecuteCopyInstruction(i.arg1, i.arg2);              break;
      case COPYA:     ExecuteCopyAInstruction(i.arg1, i.arg2);             break;
      case ADD:       ExecuteAddInstruction(i.arg1, i.arg2, i.arg3);       break;
      case SUB:       ExecuteSubInstruction(i.arg1, i.arg2, i.arg3);       break;
      case MULT:      ExecuteMultInstruction(i.arg1, i.arg2, i.arg3);      break;
      case DIV:       ExecuteDivInstruction(i.arg1, i.arg2, i.arg3);       break;
      case JUMP:      ExecuteJumpInstruction(i.arg1);                      break;
      case JUMPA:     ExecuteJumpAInstruction(i.arg1);                     break;
      case BRANCHEQ:  ExecuteBranchEqInstruction(i.arg1, i.arg2, i.arg3);  break;
      case BRANCHEQA: ExecuteBranchEqAInstruction(i.arg1, i.arg2, i.arg3); break;
      case BRANCHLT:  ExecuteBranchLTInstruction(i.arg1, i.arg2, i.arg3);  break;
      case BRANCHLTA: ExecuteBranchLTAInstruction(i.arg1, i.arg2, i.arg3); break;
      case BRANCHGT:  ExecuteBranchGTInstruction(i.arg1, i.arg2, i.arg3);  break;
      case BRANCHGTA: ExecuteBranchGTAInstruction(i.arg1, i.arg2, i.arg3); break;
      case END:       ExecuteEndInstruction(); break;
      default:
         cout << "Error: Unknown Instruction Type being executed by CPU." << endl;
         exit(-1);
   };
}

/*****************************************************************************/
int CPU::FetchData(int dataAddress)
/*****************************************************************************/
{
   return(Memory().FetchData(dataAddress));
}

/*****************************************************************************/
Instruction CPU::FetchInstruction(int instructionAddress)
/*****************************************************************************/
{
   return(Memory().FetchInstruction(instructionAddress));
}

/*****************************************************************************/
MemoryUnit& CPU::Memory()
/*****************************************************************************/
{
   return(GetMemoryUnit());
}

/*****************************************************************************/
void CPU::PrintCPUState()
/*****************************************************************************/
{
   cout << "Current Instruction Address: I" << CurrentInstructionAddress() << endl;
}

/*****************************************************************************/
void CPU::RunProgram()
/*****************************************************************************/
{
   while(true) //Runs for ever, program ends on invalid instruction or END instruction
   {
      cout << "CPU CYCLE = " << CPUCycle() << endl;
      cout << "****************************************************" << endl;
      PrintCPUState();
      Memory().PrintMemoryState();
      RunSingleCycle();
      cout << "****************************************************" << endl << endl;
      PressAnyKeyToContinue();
   }

}

/*****************************************************************************/
void CPU::RunSingleCycle()
/*****************************************************************************/
{
   //Fetch instruction
   Instruction current = FetchInstruction(CurrentInstructionAddress());

   //Execute
   ExecuteInstruction(current);

   //Increment CPU cycle
   CPUCycle(CPUCycle() + 1);
}

/*****************************************************************************/
void CPU::WriteData(int addr, int data)
/*****************************************************************************/
{
   Memory().WriteData(addr, data);
}
