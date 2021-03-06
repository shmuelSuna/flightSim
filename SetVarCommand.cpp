//
// Created by shmuelsuna on 17/12/2019.
//

#include "SetVarCommand.h"

// defualt constructer
SetVarCommand::SetVarCommand(){
}

//constructer by parameters

SetVarCommand::SetVarCommand(DefineVarCommand* ptrToDefineVarCommand, string str,
                             unordered_map<string, DefineVarCommand *>mapOfDefineVarCommands_, map<string,double>&m) {


  this->define_var_command_ptr = ptrToDefineVarCommand;
  this->rightSideOfEqualsOpertor = str;
  this->mapOfDefineVarCommands = mapOfDefineVarCommands_;
  this->mapForInterpeter = m;
}





/*
 * function that executes a set var command- gets expression and calculates it and sets it as value of
 * correct define var varialbe and adds correct message
 */
void SetVarCommand::execute(){unordered_map<string, DefineVarCommand*>::iterator it = mapOfDefineVarCommands.begin();

    Interpreter *i2 = new Interpreter();
    SetMapUpForInterpeter(this->rightSideOfEqualsOpertor);
    i2->setVariables(mapForInterpeter);
    Expression *e1 = i2->interpret(rightSideOfEqualsOpertor);

    double newValue = e1->calculate();
    GetDefine_var_command_ptr()->SetVarValue(newValue);
    string s = define_var_command_ptr->GetSim();
    messageSim->addMessage(newValue, s);




}
/*
 * function that checks If Name Of A DefineVarIsInString- so we know if we should handle expressins with varialbes
 */
bool SetVarCommand::checkIfNameOfADefineVarIsInString(string stringThatsRightOfEquals) {
  //
  //
 //check in map of defineVarcommands if there is a substring in the string to equals
 unordered_map<string,DefineVarCommand*> temp = GetMapOfDefineVarCommands();
 unordered_map<string,DefineVarCommand*>::iterator it = temp.begin();
  for (;it != temp.end(); ++it) {
    if(stringThatsRightOfEquals.find(it->first)!= string::npos) {
      return true;
    }
  }
  return false;
}

/*
 * function that Sets up Map For Interpeter -so we can handle expressions
 */
void  SetVarCommand::SetMapUpForInterpeter(string stringThatsRightOfEquals) {

  if (this->checkIfNameOfADefineVarIsInString(stringThatsRightOfEquals)) {//there is a define var in the string
      unordered_map<string,DefineVarCommand*> temp = GetMapOfDefineVarCommands();
      unordered_map<string,DefineVarCommand*>::iterator it = temp.begin();
    for (; it != temp.end(); ++it) {
      if (stringThatsRightOfEquals.find(it->first) != string::npos) {
        mapForInterpeter[it->first] = it->second->GetVarValue();
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

void SetVarCommand::setMessanger(MessageSim * m) {
    this->messageSim = m;
}