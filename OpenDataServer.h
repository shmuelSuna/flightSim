//
// Created by shmuelsuna on 13/12/2019.
//

#ifndef FLIGHTSIM__OPENDATASERVER_H_
#define FLIGHTSIM__OPENDATASERVER_H_

#include <map>
#include "Command.h"

class OpenDataServer : public Command{
private:
    int port;
private:
    std::map<std::string,float> flightDataServer;


 public:
  // defualt constructer
  OpenDataServer();

  //constructer by parameters
  OpenDataServer(int x);   //int x - is just to show that there is parameters. not sure which parameters yet


  void execute(vector<string>::iterator &it);

  int openServer(int);
};
#endif //FLIGHTSIM__OPENDATASERVER_H_
