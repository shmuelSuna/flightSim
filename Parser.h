//
// Created by shmuelsuna on 15/12/2019.
//

#ifndef FLIGHTSIM_PARSER_H
#define FLIGHTSIM_PARSER_H


#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include "Command.h"
#include <map>
#include "OpenDataServer.h"
#include "ConnectCommand.h"
#include <unordered_map>
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "SetVarCommand.h"
#include "WhileCommand.h"
#include "MessageSim.h"
using namespace std;


class Parser {
 private:
  vector<string> vectorOfStrings;
  unordered_map<string, Command*> mapOfCommands;
  unordered_map<string, DefineVarCommand*> mapOfDefineVarCommands;
  vector<Command*> command_vec;
 public:
  // Defualt Constructer
  Parser();

  //constructer by parameters
  Parser(vector<string> vectorOfStrings);

  unordered_map<string, Command*> action(vector<string> vectorOfStrings);

  unordered_map<string,  Command*> GetMapOfCommands();

  void setCommandVec(vector<Command *>);


  bool checkIfNameOfADefineVarIsInString(string);

  map<string, double> SetMapUpForInterpeter(string );

  unordered_map<string, DefineVarCommand *> GetMapOfDefineVarCommands();

  void operateCommands();


  Expression* createExpression( map<string, double>,string);

  void SetUpExpression();

  Expression* GetExpressionFromString(string);



  DefineVarCommand* createDefineVarCommand_ptr(vector<string>::iterator,SymbolTable*,ServerValuesMap*);
  DefineVarCommand* createDefineVarCommand_ptrThatHasArrowAndSim(vector<string>::iterator,SymbolTable*,ServerValuesMap*,string);
  DefineVarCommand* createDefineVarCommand_ptrThatHas_NO_ArrowAndSim(vector<string>::iterator,string);

  bool checkIfIteratorIsUpTooSetVarCommand(vector<string>::iterator);
  SetVarCommand* createSetVarCommand(vector<string>::iterator);

  WhileCommand* createWhileCommand_ptr(vector<string>::iterator,SymbolTable*,ServerValuesMap*);
};

#endif //FLIGHTSIM_PARSER_H