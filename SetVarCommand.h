//
// Created by shmuelsuna on 17/12/2019.
//

#ifndef FLIGHTSIM__SETVARCOMMAND_H_
#define FLIGHTSIM__SETVARCOMMAND_H_

#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <unordered_map>
#include "Command.h"
#include "CreateSymbolTable.h"
#include "SymbolTable.h"
#include "DefineVarCommand.h"
#include "Expression.h"
#include <vector>
using namespace std;



class SetVarCommand : public Command {

 private:
DefineVarCommand* define_var_command_ptr;
double value;
//Expression ex

 public:
  // defualt constructer
  SetVarCommand();

  //constructer by parameters
  SetVarCommand(DefineVarCommand*, double);//will change in futute to  SetVarCommand(DefineVarCommand*,Expression*)
  // SetVarCommand(DefineVarCommand*, Expression*);

  void execute(vector<string>::iterator &it);
  //void execute();
};

#endif //FLIGHTSIM__SETVARCOMMAND_H_
