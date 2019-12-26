//
// Created by shmuelsuna on 16/12/2019.
//

#include "PrintCommand.h"



//Defualt Constructer
PrintCommand::PrintCommand(){}

// Constructer with parameters
PrintCommand::PrintCommand(const string &message_){
  this->message = message_;
  this->isVar = false;
}
PrintCommand::PrintCommand(DefineVarCommand* v){
    this->var = v;
    this->isVar = true;
}

void PrintCommand::execute() {
    if (!isVar) {
        cout << message << endl;
    } else {
        var->execute();
        cout <<"from print command the print: " <<var->GetVarValue() << endl;
    }

}

