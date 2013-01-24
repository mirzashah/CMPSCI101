//Parser.h
//*****************************************************************************
//Parses the program file containing instructions
//*****************************************************************************

#ifndef PARSER_H_DEFINED
#define PARSER_H_DEFINED

#include "Instruction.h"
#include <string>
using std::string;

typedef vector<string> StringList;
class Parser
{
   public:
      Parser(string inputFile);
      ~Parser();

      InstructionList Parse();

   private:
      StringList      BreakInputFileUpIntoLines();
      InstructionList ParseInstructions(StringList unparsedInstructions);
      Instruction     ParseInstruction(string instruction);
      StringList      TokenizeStringBySpaces(string untokenizedString);

      template <typename T> vector<T> RemoveFirst(const vector<T>& v)
      {
         vector<T> toReturn;
         for(unsigned int c = 1; c < v.size(); c++)
            toReturn.push_back(v.at(c));
         return(toReturn);
      }

   private:
      Instruction ParseSET(StringList tokens);
      Instruction ParseSETA(StringList tokens);
      Instruction ParseCOPY(StringList tokens);
      Instruction ParseCOPYA(StringList tokens);
      Instruction ParseADD(StringList tokens);
      Instruction ParseSUB(StringList tokens);
      Instruction ParseMULT(StringList tokens);
      Instruction ParseDIV(StringList tokens);
      Instruction ParseJUMP(StringList tokens);
      Instruction ParseJUMPA(StringList tokens);
      Instruction ParseBRANCHEQ(StringList tokens);
      Instruction ParseBRANCHEQA(StringList tokens);
      Instruction ParseBRANCHLT(StringList tokens);
      Instruction ParseBRANCHLTA(StringList tokens);
      Instruction ParseBRANCHGT(StringList tokens);
      Instruction ParseBRANCHGTA(StringList tokens);
      Instruction ParseEND(StringList tokens);

      OpCode      ParseOpCode(string token);
      int         ParseAddressToken(string token);
      int         ParseLiteralToken(string token);
      void        ParseCommentTokens(StringList tokens);

   private:
      string _inputFile;

};


#endif
