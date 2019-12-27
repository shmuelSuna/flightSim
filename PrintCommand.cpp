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
PrintCommand::PrintCommand(Expression* expression1){
    this->expression_ = expression1;
    this->isExpression = true;
}

void PrintCommand::execute() {
    if (!isExpression) {
        cout << message << endl;
    } else {
      cout << expression_->calculate()<< endl;
    }

}

