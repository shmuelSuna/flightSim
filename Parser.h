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
#include "SymbolTable.h"
#include <mutex>
#include <condition_variable>
#include "ClientValuesMap.h"
using namespace std;

extern mutex m;
extern condition_variable cv;




class Parser {
 private:
  vector<string> vectorOfStrings;
  unordered_map<string, Command*> mapOfCommands;


public:
  // Defualt Constructer
  Parser();

  //constructer by parameters
  Parser(vector<string> vectorOfStrings);

 public:
  unordered_map<string, Command*> action(vector<string> vectorOfStrings);

  unordered_map<string,  Command*> GetMapOfCommands();


};

#endif //FLIGHTSIM_PARSER_H