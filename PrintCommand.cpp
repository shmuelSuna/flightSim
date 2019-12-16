//
// Created by shmuelsuna on 16/12/2019.
//

#include "PrintCommand.h"



//Defualt Constructer
PrintCommand::PrintCommand(){}

// Constructer with parameters
PrintCommand::PrintCommand(const string &message_){
  this->message = message_;
}

void PrintCommand::execute(vector<string>::iterator &it) {

}

