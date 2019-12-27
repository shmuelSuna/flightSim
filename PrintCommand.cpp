//
// Created by shmuelsuna on 16/12/2019.
//

#include "PrintCommand.h"



//Defualt Constructer
PrintCommand::PrintCommand(){}

// Constructer with parameters
PrintCommand::PrintCommand(const string &message_){
  this->message = message_;
  this->isDouble = false;
}
PrintCommand::PrintCommand(double expression_calculate1){
    this->expression_calculate = expression_calculate1;
    this->isDouble = true;
}

void PrintCommand::execute() {
    if (!isDouble) {
        cout << message << endl;
        if (message == "done") {
            isClientOn = false;
        }
    } else {

        cout << expression_calculate<< endl;
    }

}

