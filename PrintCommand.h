//
// Created by shmuelsuna on 16/12/2019.
//

#ifndef FLIGHTSIM__PRINTCOMMAND_H_
#define FLIGHTSIM__PRINTCOMMAND_H_

#include "Command.h"
#include "DefineVarCommand.h"
extern bool isClientOn;
class PrintCommand: public Command {
 private:

  string message;
  double expression_calculate;
  bool isDouble;

 public:



  //Defualt Constructer
  PrintCommand();

  // Constructer with parameters
  PrintCommand(const string &message_);
  PrintCommand(double);




  //option 1
  void execute() override;

  //option 2
  // void execute()override ;


};

#endif //FLIGHTSIM__PRINTCOMMAND_H_
