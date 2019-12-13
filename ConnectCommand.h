//
// Created by shmuelsuna on 13/12/2019.
//

#ifndef FLIGHTSIM__CONNECTCOMMAND_H_
#define FLIGHTSIM__CONNECTCOMMAND_H_

#include "Command.h"


class ConnectCommand : public Command {
 public:

  // Defualt Constructer
  ConnectCommand(){}

  //constructer by parameters
 //  ConnectCommand(.......){}


  //option 1
  void execute(vector<string>::iterator &it) override;

  //option 2
 // void execute()override ;

};


#endif //FLIGHTSIM__CONNECTCOMMAND_H_
