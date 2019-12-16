//
// Created by shmuelsuna on 16/12/2019.
//

#ifndef FLIGHTSIM__PRINTCOMMAND_H_
#define FLIGHTSIM__PRINTCOMMAND_H_

#include "Command.h"
class PrintCommand: public Command {
 private:

  string message;

 public:



  //Defualt Constructer
  PrintCommand();

  // Constructer with parameters
  PrintCommand(const string &message_);




  //option 1
  void execute(vector<string>::iterator &it) override;

  //option 2
  // void execute()override ;


};

#endif //FLIGHTSIM__PRINTCOMMAND_H_
