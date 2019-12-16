//
// Created by shmuelsuna on 13/12/2019.
//

#ifndef FLIGHTSIM__COMMAND_H_
#define FLIGHTSIM__COMMAND_H_


#include <iostream>
#include <vector>

using namespace std;


class Command {

 public:

  // option one for execute
  virtual void execute(vector<string>:: iterator& it) = 0;

  // option two for execute method
  // virtual void execute()=0;


  virtual  ~Command() {}
};

#endif //FLIGHTSIM__COMMAND_H_
