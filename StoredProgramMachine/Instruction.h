//Instruction.h
//*****************************************************************************
//Encodes CPU instructions
//*****************************************************************************

#ifndef INSTRUCTION_H_DEFINED
#define INSTRUCTION_H_DEFINED

#include <vector>
using std::vector;

enum OpCode
{
   SET,
   SETA,
   COPY,
   COPYA,
   ADD,
   SUB,
   MULT,
   DIV,
   JUMP,
   JUMPA,
   BRANCHEQ,
   BRANCHEQA,
   BRANCHLT,
   BRANCHLTA,
   BRANCHGT,
   BRANCHGTA,
   END
};

struct Instruction
{
   Instruction()
   {
      opCode = END;
      arg1 = -1;
      arg2 = -1;
      arg3 = -1;
   }
   Instruction(OpCode opCodeIn, int arg1In = 0, int arg2In = 0, int arg3In = 0)
   {
      opCode = opCodeIn;
      arg1 = arg1In;
      arg2 = arg2In;
      arg3 = arg3In;
   }
   OpCode opCode;
   int    arg1;
   int    arg2;
   int    arg3;
};

typedef vector<Instruction> InstructionList;


#endif
