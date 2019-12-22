//
// Created by shmuelsuna on 17/12/2019.
//

#ifndef FLIGHTSIM__SETVARCOMMAND_H_
#define FLIGHTSIM__SETVARCOMMAND_H_

#include <sys/socket.h>
#include <string.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <unordered_map>
#include "Command.h"
#include "CreateSymbolTable.h"
#include "SymbolTable.h"
#include "DefineVarCommand.h"
#include "ex1.h"
#include <vector>
using namespace std;



class SetVarCommand : public Command {

 private:
  DefineVarCommand *define_var_command_ptr;
//  double value;
  Expression *expression_;
  string rightSideOfEqualsOpertor;
  unordered_map<string, DefineVarCommand *> mapOfDefineVarCommands;
  map<string,double>mapForInterpeter;

 public:
  // defualt constructer
  SetVarCommand();

  //constructer by parameters
 SetVarCommand(DefineVarCommand *, string, unordered_map<string, DefineVarCommand *>, map<string, double>&);

  void execute(vector<string>::iterator &it);

  //void execute();

  bool checkIfNameOfADefineVarIsInString(string);

void SetMapUpForInterpeter(string );

DefineVarCommand* GetDefine_var_command_ptr();

void SetExpression(Expression*) ;

  unordered_map<string, DefineVarCommand *> GetMapOfDefineVarCommands();
};
#endif //FLIGHTSIM__SETVARCOMMAND_H_
