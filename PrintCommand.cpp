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
  this->isExpression = true;
  this->mapForInterpeter = mapForInterpeter1;
  this->mapOfDefineVarCommands_ = mapOfDefineVarCommands1_;
}




PrintCommand::PrintCommand(Expression* expression1){
    this->expression_ = expression1;
    this->isExpression = true;
}



/*
 * function that checks If a Name Of A DefineVar Is In String, to know how to handle print message
 */
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

/*
 * function that sets up the map for interpeter so we can handle expressions inside message of print
 */
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








/*
 * function that executes a print command based on what needs to be printed
 */
void PrintCommand::execute() {
    if (!isExpression) {
        cout << message << endl;
        if (message == "done") {
            isScript = false;
            this_thread::sleep_for(1s);
        }
    } else {
      Interpreter *i2 = new Interpreter();
      SetMapUpForInterpeter(this->message);
      i2->setVariables(mapForInterpeter);
      Expression *e1 = i2->interpret(message);

      cout << e1->calculate() << endl;
    }

}

