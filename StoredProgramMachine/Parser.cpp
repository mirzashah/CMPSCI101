#include "Parser.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

/*****************************************************************************/
Parser::Parser(string inputFile) :
_inputFile(inputFile)
/*****************************************************************************/
{
}

/*****************************************************************************/
Parser::~Parser()
/*****************************************************************************/
{
}

/*****************************************************************************/
StringList Parser::BreakInputFileUpIntoLines()
/*****************************************************************************/
{
   ifstream infile(_inputFile.c_str());
   if(!infile)
   {
      cout<<"Error opening program file. Exiting...";
      exit(-1);
   }
   StringList toReturn;
   while(!infile.eof())
   {
      string buffer;
      getline(infile,buffer);
      toReturn.push_back(buffer);
   }

   return(toReturn);
}

/*****************************************************************************/
InstructionList Parser::ParseInstructions(StringList unparsedInstructions)
/*****************************************************************************/
{
   InstructionList toReturn;
   for(unsigned int c = 0; c < unparsedInstructions.size(); c++)
   {
      cout <<"Parsing line " << c + 1 <<endl;
      string unparsedInstr = unparsedInstructions.at(c);
      if(unparsedInstr.size() > 0)
         toReturn.push_back(ParseInstruction(unparsedInstr));
   }
   return(toReturn);
}


/*****************************************************************************/
Instruction Parser::ParseInstruction(string instruction)
/*****************************************************************************/
{
   StringList tokens = TokenizeStringBySpaces(instruction);
   if(tokens.size()== 0)
   {
      cout << "Error, no tokens when parsing...exiting." <<endl;
      exit(-1);
   }

   OpCode opCode = ParseOpCode(tokens.at(0));
   tokens = RemoveFirst(tokens);
   switch(opCode)
   {
      case SET:       return(ParseSET(tokens));
      case SETA:      return(ParseSETA(tokens));
      case COPY:      return(ParseCOPY(tokens));
      case COPYA:     return(ParseCOPYA(tokens));
      case ADD:       return(ParseADD(tokens));
      case SUB:       return(ParseSUB(tokens));
      case MULT:      return(ParseMULT(tokens));
      case DIV:       return(ParseDIV(tokens));
      case JUMP:      return(ParseJUMP(tokens));
      case JUMPA:     return(ParseJUMPA(tokens));
      case BRANCHEQ:  return(ParseBRANCHEQ(tokens));
      case BRANCHEQA: return(ParseBRANCHEQA(tokens));
      case BRANCHLT:  return(ParseBRANCHLT(tokens));
      case BRANCHLTA: return(ParseBRANCHLTA(tokens));
      case BRANCHGT:  return(ParseBRANCHGT(tokens));
      case BRANCHGTA: return(ParseBRANCHGTA(tokens));
      case END:       return(ParseEND(tokens));
      default:
         cout << "Error: Unknown instruction type (opcode) when parsing instruction" << endl;
         exit(-1);
   };
}

/*****************************************************************************/
InstructionList Parser::Parse()
/*****************************************************************************/
{
   return(ParseInstructions(BreakInputFileUpIntoLines()));
}

/*****************************************************************************/
Instruction Parser::ParseSET(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 2)
   {
      int addr = ParseAddressToken(tokens.at(0));
      int val = ParseLiteralToken(tokens.at(1));
      if(tokens.size() >= 3)
         ParseCommentTokens(RemoveFirst(RemoveFirst(tokens)));
      return(Instruction(SET, addr, val));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }
}

/*****************************************************************************/
Instruction Parser::ParseSETA(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 2)
   {
      int addr = ParseAddressToken(tokens.at(0));
      int val = ParseLiteralToken(tokens.at(1));
      if(tokens.size() >= 3)
         ParseCommentTokens(RemoveFirst(RemoveFirst(tokens)));
      return(Instruction(SETA, addr, val));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }
}

/*****************************************************************************/
Instruction Parser::ParseCOPY(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 2)
   {
      int srcAddr = ParseAddressToken(tokens.at(0));
      int destAddr = ParseAddressToken(tokens.at(1));
      if(tokens.size() >= 3)
         ParseCommentTokens(RemoveFirst(RemoveFirst(tokens)));
      return(Instruction(COPY, srcAddr, destAddr));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }
}

/*****************************************************************************/
Instruction Parser::ParseCOPYA(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 2)
   {
      int srcAddr = ParseAddressToken(tokens.at(0));
      int destAddr = ParseAddressToken(tokens.at(1));
      if(tokens.size() >= 3)
         ParseCommentTokens(RemoveFirst(RemoveFirst(tokens)));
      return(Instruction(COPYA, srcAddr, destAddr));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }
}

/*****************************************************************************/
Instruction Parser::ParseADD(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 3)
   {
      int addr1 = ParseAddressToken(tokens.at(0));
      int addr2 = ParseAddressToken(tokens.at(1));
      int destAddr = ParseAddressToken(tokens.at(2));
      if(tokens.size() >= 4)
         ParseCommentTokens(RemoveFirst(RemoveFirst(RemoveFirst(tokens))));
      return(Instruction(ADD, addr1, addr2, destAddr));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }

}

/*****************************************************************************/
Instruction Parser::ParseSUB(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 3)
   {
      int addr1 = ParseAddressToken(tokens.at(0));
      int addr2 = ParseAddressToken(tokens.at(1));
      int destAddr = ParseAddressToken(tokens.at(2));
      if(tokens.size() >= 4)
         ParseCommentTokens(RemoveFirst(RemoveFirst(RemoveFirst(tokens))));
      return(Instruction(SUB, addr1, addr2, destAddr));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }

}

/*****************************************************************************/
Instruction Parser::ParseMULT(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 3)
   {
      int addr1 = ParseAddressToken(tokens.at(0));
      int addr2 = ParseAddressToken(tokens.at(1));
      int destAddr = ParseAddressToken(tokens.at(2));
      if(tokens.size() >= 4)
         ParseCommentTokens(RemoveFirst(RemoveFirst(RemoveFirst(tokens))));
      return(Instruction(MULT, addr1, addr2, destAddr));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }

}

/*****************************************************************************/
Instruction Parser::ParseDIV(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 3)
   {
      int addr1 = ParseAddressToken(tokens.at(0));
      int addr2 = ParseAddressToken(tokens.at(1));
      int destAddr = ParseAddressToken(tokens.at(2));
      if(tokens.size() >= 4)
         ParseCommentTokens(RemoveFirst(RemoveFirst(RemoveFirst(tokens))));
      return(Instruction(DIV, addr1, addr2, destAddr));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }

}

/*****************************************************************************/
Instruction Parser::ParseJUMP(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 1)
   {
      int jumpAddr = ParseLiteralToken(tokens.at(0));
      if(tokens.size() >= 2)
         ParseCommentTokens(RemoveFirst(tokens));
      return(Instruction(JUMP, jumpAddr));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }
}

/*****************************************************************************/
Instruction Parser::ParseJUMPA(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 1)
   {
      int jumpAddr = ParseAddressToken(tokens.at(0));
      if(tokens.size() >= 2)
         ParseCommentTokens(RemoveFirst(tokens));
      return(Instruction(JUMPA, jumpAddr));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }

}

/*****************************************************************************/
Instruction Parser::ParseBRANCHEQ(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 3)
   {
      int addr1 = ParseAddressToken(tokens.at(0));
      int addr2 = ParseAddressToken(tokens.at(1));
      int branchAddr = ParseLiteralToken(tokens.at(2));
      if(tokens.size() >= 4)
         ParseCommentTokens(RemoveFirst(RemoveFirst(RemoveFirst(tokens))));
      return(Instruction(BRANCHEQ, addr1, addr2, branchAddr));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }

}

/*****************************************************************************/
Instruction Parser::ParseBRANCHEQA(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 3)
   {
      int addr1 = ParseAddressToken(tokens.at(0));
      int addr2 = ParseAddressToken(tokens.at(1));
      int branchAddr= ParseAddressToken(tokens.at(2));
      if(tokens.size() >= 4)
         ParseCommentTokens(RemoveFirst(RemoveFirst(RemoveFirst(tokens))));
      return(Instruction(BRANCHEQA, addr1, addr2, branchAddr));

   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }

}

/*****************************************************************************/
Instruction Parser::ParseBRANCHLT(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 3)
   {
      int addr1 = ParseAddressToken(tokens.at(0));
      int addr2 = ParseAddressToken(tokens.at(1));
      int branchAddr = ParseLiteralToken(tokens.at(2));
      if(tokens.size() >= 4)
         ParseCommentTokens(RemoveFirst(RemoveFirst(RemoveFirst(tokens))));
      return(Instruction(BRANCHLT, addr1, addr2, branchAddr));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }
}

/*****************************************************************************/
Instruction Parser::ParseBRANCHLTA(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 3)
   {
      int addr1 = ParseAddressToken(tokens.at(0));
      int addr2 = ParseAddressToken(tokens.at(1));
      int branchAddr= ParseAddressToken(tokens.at(2));
      if(tokens.size() >= 4)
         ParseCommentTokens(RemoveFirst(RemoveFirst(RemoveFirst(tokens))));
      return(Instruction(BRANCHLTA, addr1, addr2, branchAddr));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }

}

/*****************************************************************************/
Instruction Parser::ParseBRANCHGT(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 3)
   {
      int addr1 = ParseAddressToken(tokens.at(0));
      int addr2 = ParseAddressToken(tokens.at(1));
      int branchAddr = ParseLiteralToken(tokens.at(2));
      if(tokens.size() >= 4)
         ParseCommentTokens(RemoveFirst(RemoveFirst(RemoveFirst(tokens))));
      return(Instruction(BRANCHGT, addr1, addr2, branchAddr));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }
}

/*****************************************************************************/
Instruction Parser::ParseBRANCHGTA(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() >= 3)
   {
      int addr1 = ParseAddressToken(tokens.at(0));
      int addr2 = ParseAddressToken(tokens.at(1));
      int branchAddr= ParseAddressToken(tokens.at(2));
      if(tokens.size() >= 4)
         ParseCommentTokens(RemoveFirst(RemoveFirst(RemoveFirst(tokens))));
      return(Instruction(BRANCHGTA, addr1, addr2, branchAddr));
   }
   else
   {
      cout << "Error not enough arguments. Exiting..."<<endl;
      exit(-1);
   }

   throw; //Unreachable, gets rid of warning
}

/*****************************************************************************/
Instruction Parser::ParseEND(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() > 1)
      ParseCommentTokens(tokens);
   return(Instruction(END));
}

/*****************************************************************************/
int Parser::ParseAddressToken(string token)
/*****************************************************************************/
{
   if(token.size() <= 0 || token.at(0) != '@')
   {
      cout<<"Invalid address token, exiting..."<<endl;
      exit(-1);
   }

   token = token.substr(1,token.size());
   istringstream asNumStream(token);
   int address;
   asNumStream >> address;
   return(address);
}

/*****************************************************************************/
int Parser::ParseLiteralToken(string token)
/*****************************************************************************/
{
   istringstream asNumStream(token);
   int address;
   asNumStream >> address;
   return(address);
}

/*****************************************************************************/
void Parser::ParseCommentTokens(StringList tokens)
/*****************************************************************************/
{
   if(tokens.size() <= 0)
      return;
   else
   {
      string firstToken = tokens.at(0);
      if(firstToken.at(0) != '#')
      {
         cout<<"Invalid comment, comment must start with #. Exiting..."<<endl;
         exit(-1);
      }
   }
}

/*****************************************************************************/
OpCode Parser::ParseOpCode(string token)
/*****************************************************************************/
{
   if(token == "SET")       return SET;
   if(token == "SETA")      return SETA;
   if(token == "ADD")       return ADD;
   if(token == "SUB")       return SUB;
   if(token == "MULT")      return MULT;
   if(token == "DIV")       return DIV;
   if(token == "JUMP")      return JUMP;
   if(token == "JUMPA")     return JUMPA;
   if(token == "COPY")      return COPY;
   if(token == "COPYA")     return COPYA;
   if(token == "BRANCHEQ")  return BRANCHEQ;
   if(token == "BRANCHEQA") return BRANCHEQA;
   if(token == "BRANCHLT")  return BRANCHLT;
   if(token == "BRANCHLTA") return BRANCHLTA;
   if(token == "BRANCHGT")  return BRANCHGT;
   if(token == "BRANCHGTA") return BRANCHGTA;
   if(token == "END")       return END;

   cout << "Unknown instruction type (opcode) during parsing. Exiting..." << endl;
   exit(-1);
}

/*****************************************************************************/
StringList Parser::TokenizeStringBySpaces(string untokenizedString)
/*****************************************************************************/
{
   StringList toReturn;
   string currentToken = "";
   for(unsigned int c=0; c<untokenizedString.size(); c++)
   {
      char current = untokenizedString.at(c);
      if(current == ' ' || c == (untokenizedString.size() - 1))
      {
         if(current != ' ')
            currentToken.push_back(current);

         if(currentToken!="")
            toReturn.push_back(currentToken);
         currentToken = "";
      }
      else
      {
         currentToken.push_back(current);
      }
   }
   return(toReturn);
}
