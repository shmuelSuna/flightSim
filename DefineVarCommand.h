//
// Created by shmuelsuna on 13/12/2019.
//

#ifndef FLIGHTSIM__DEFINEVARCOMMAND_H_
#define FLIGHTSIM__DEFINEVARCOMMAND_H_

#include "Command.h"


class DefineVarCommand : public Command{

  //Defualt Constructer
  DefineVarCommand() {}

  // Constructer with parameters
 // DefineVarCommand(.....) {}


  //option 1
  void execute(vector<string>::iterator &it) override;

  //option 2
  // void execute()override ;


};

#endif //FLIGHTSIM__DEFINEVARCOMMAND_H_
