//
// Created by shmuelsuna on 17/12/2019.
//

#include "SetVarCommand.h"

// defualt constructer
SetVarCommand::SetVarCommand(){
}

//constructer by parameters

 SetVarCommand::SetVarCommand(DefineVarCommand* ptrToDefineVarCommand, string str,
    unordered_map<string, DefineVarCommand *>mapOfDefineVarCommands_, map<string,double>&m, MessageSim* ms) {


  this->define_var_command_ptr = ptrToDefineVarCommand;
  this->rightSideOfEqualsOpertor = str;
  this->mapOfDefineVarCommands = mapOfDefineVarCommands_;
  this->mapForInterpeter = m;
  this->messageSim = ms;
}

//constructer without message sim
SetVarCommand::SetVarCommand(DefineVarCommand* ptrToDefineVarCommand, string str,
                             unordered_map<string, DefineVarCommand *>mapOfDefineVarCommands_, map<string,double>&m) {


  this->define_var_command_ptr = ptrToDefineVarCommand;
  this->rightSideOfEqualsOpertor = str;
  this->mapOfDefineVarCommands = mapOfDefineVarCommands_;
  this->mapForInterpeter = m;
}






void SetVarCommand::execute(){
    Interpreter *i2 = new Interpreter();
    i2->setVariables(mapForInterpeter);
    Expression *e1 = i2->interpret(rightSideOfEqualsOpertor);

    float newValue = e1->calculate();
    GetDefine_var_command_ptr()->SetVarValue(newValue);
    string s = define_var_command_ptr->GetSim();
    messageSim->setMessage(newValue, s);
    cout<<"in set var command set new var"<<newValue<<s<<endl;



    // double test1 = set_var_command.GetDefine_var_command_ptr()->GetVarValue(); //testtttttttt1
   // double test2 = itOverMap->second->GetVarValue();

}

bool SetVarCommand::checkIfNameOfADefineVarIsInString(string stringThatsRightOfEquals) {
  //
  //
 //check in map of defineVarcommands if there is a substring in the string to equals
  for (auto itOverMap = GetMapOfDefineVarCommands().begin(); itOverMap != GetMapOfDefineVarCommands().end();
       ++itOverMap) {
    if(stringThatsRightOfEquals.find(itOverMap->first)!= string::npos) {
      return true;
    }
  }
  return false;
}


void  SetVarCommand::SetMapUpForInterpeter(string stringThatsRightOfEquals) {

  if (this->checkIfNameOfADefineVarIsInString(stringThatsRightOfEquals)) {//there is a define var in the string
    for (auto itOverMap = GetMapOfDefineVarCommands().begin(); itOverMap != GetMapOfDefineVarCommands().end();
         ++itOverMap) {
      if (stringThatsRightOfEquals.find(itOverMap->first) != string::npos) {
        mapForInterpeter[itOverMap->first] = itOverMap->second->GetVarValue();
      }
    }
  }

}

unordered_map<string, DefineVarCommand*>SetVarCommand::GetMapOfDefineVarCommands() {
  return this->mapOfDefineVarCommands;
}


void SetVarCommand::SetExpression(Expression *ex) {
  this->expression_ = ex;
}

DefineVarCommand* SetVarCommand::GetDefine_var_command_ptr() {
  return this->define_var_command_ptr;
}