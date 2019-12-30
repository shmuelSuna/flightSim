//
// Created by shmuelsuna on 16/12/2019.
//

#include "PrintCommand.h"



//Defualt Constructer
PrintCommand::PrintCommand(){}

// Constructer with parameters
PrintCommand::PrintCommand(const string &message_){
  this->message = message_;
  this->isExpression = false;
}
// Constructer with parameters
PrintCommand::PrintCommand(const string &message_,unordered_map<string, DefineVarCommand *>mapOfDefineVarCommands1_,map<string,double> mapForInterpeter1){
  this->message = message_;
  this->isExpression = false;
  this->mapForInterpeter = mapForInterpeter1;
  this->mapOfDefineVarCommands_ = mapOfDefineVarCommands1_;
}




PrintCommand::PrintCommand(Expression* expression1){
    this->expression_ = expression1;
    this->isExpression = true;
}




bool PrintCommand::checkIfNameOfADefineVarIsInString(string stringThatsRightOfEquals) {
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


void  PrintCommand::SetMapUpForInterpeter(string stringThatsRightOfEquals) {

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


unordered_map<string, DefineVarCommand*>PrintCommand::GetMapOfDefineVarCommands() {
  return this->mapOfDefineVarCommands_;
}









void PrintCommand::execute() {
    if (!isExpression) {
        cout << message << endl;
        if (message == "done") {
            isClientOn = false;
        }
    } else {
      Interpreter *i2 = new Interpreter();
      SetMapUpForInterpeter(this->message);
      i2->setVariables(mapForInterpeter);
      Expression *e1 = i2->interpret(message);

      cout << e1->calculate() << endl;
    }

}

