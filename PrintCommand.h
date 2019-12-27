//
// Created by shmuelsuna on 16/12/2019.
//

#ifndef FLIGHTSIM__PRINTCOMMAND_H_
#define FLIGHTSIM__PRINTCOMMAND_H_

#include "Command.h"
#include "DefineVarCommand.h"
#include "ex1.h"
class PrintCommand: public Command {
 private:

  string message;
  Expression* expression_;
  bool isExpression;

 public:



  //Defualt Constructer
  PrintCommand();

  // Constructer with parameters
  PrintCommand(const string &message_);
  PrintCommand(Expression*);




  //option 1
  void execute() override;

  //option 2
  // void execute()override ;


};

#endif //FLIGHTSIM__PRINTCOMMAND_H_
