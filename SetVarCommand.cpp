//
// Created by shmuelsuna on 17/12/2019.
//

#include "SetVarCommand.h"

// defualt constructer
SetVarCommand::SetVarCommand(){
}

//constructer by parameters
//SetVarCommand::SetVarCommand(DefineVarCommand* ptrToDefineVarCommand, Expression *expression) {
SetVarCommand::SetVarCommand(DefineVarCommand* ptrToDefineVarCommand, double value_) {
  //will change in future to SetVarCommand(DefineVarCommand* ptrToDefineVarCommand,Expression*)

  this->define_var_command_ptr = ptrToDefineVarCommand;
  this->value =value_;
 // this->value =expression.calculate();
}

void SetVarCommand::execute(vector<string>::iterator &it){



}