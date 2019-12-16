//
// Created by shmuelsuna on 16/12/2019.
//

#ifndef FLIGHTSIM__SLEEPCOMMAND_H_
#define FLIGHTSIM__SLEEPCOMMAND_H_



#include "Command.h"
class SleepCommand : public Command {
 private:

  int timeToSleep;

 public:



  //Defualt Constructer
  SleepCommand();

  // Constructer with parameters
  SleepCommand( int timeToSleep_);




  //option 1
  void execute(vector<string>::iterator &it) override;

  //option 2
  // void execute()override ;


};

#endif //FLIGHTSIM__SLEEPCOMMAND_H_
