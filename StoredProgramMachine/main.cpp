#include <iostream>
#include <cstdlib>
#include "CPU.h"
#include "MemoryUnit.h"
#include "Parser.h"
using namespace std;


int main(int argc, char* argv[])
{
   cout << "*********************************************************" << endl;
   cout << "Stored Program Computer Simulator, Copyright (c) 2011,mas" << endl;
   cout << "This code is licensed with the GPLv3 open source license." << endl;
   cout << "*********************************************************" << endl;

   //The main components of the computer
   MemoryUnit& theMemoryUnit = GetMemoryUnit();
   CPU         theCPU;

   //Parse the program to generate a list of instructions (type InstructionList)
    if(argc < 2)
    {
      cout << "Not enough command line arguments, enter name of file." << endl;
      exit(-1);
    }

   //Parse File
   string          filename = string(argv[1]);
   Parser          programParser(filename); //1 refers to first command line argument
   InstructionList program;
   program = programParser.Parse();

   //Load program into Instruction Memory
   theMemoryUnit.LoadProgram(program);
   cout << "Program loaded into Instruction Memory, executing..." << endl;
   cout << "****************************************************" << endl;

   //Run it till completion
   theCPU.RunProgram();

   cout << "****************************************************" << endl;
   cout << "Program Complete"<<endl;
   cout << "****************************************************" << endl;

   return 0;
}
