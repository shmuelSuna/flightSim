//
// Created by shmuelsuna on 13/12/2019.
//

#ifndef FLIGHTSIM_CONNECTCOMMAND_H
#define FLIGHTSIM_CONNECTCOMMAND_H

#include "Command.h"


class ConnectCommand : public Command {
  string ip;
  int port;

 public:

  // Defualt Constructer
  ConnectCommand();

  //constructer by parameters
  ConnectCommand(string ip1, int port1);


  //option 1
  void execute(vector<string>::iterator &it) override;

  //option 2
  // void execute()override ;

};


#endif //FLIGHTSIM_CONNECTCOMMAND_H