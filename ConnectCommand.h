//
// Created by shmuelsuna on 13/12/2019.
//

#ifndef FLIGHTSIM_CONNECTCOMMAND_H
#define FLIGHTSIM_CONNECTCOMMAND_H

#include "Command.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "SymbolTable.h"
#include <string.h>
#include "MessageSim.h"
#include <condition_variable>
#include <mutex>

using namespace std;
extern bool newMessage;
extern condition_variable cv;
extern mutex m;

class ConnectCommand : public Command {
  string ip;
  int port;
  int client_socket;
  MessageSim * message;

 public:

  // Defualt Constructer
  ConnectCommand();

  //constructer by parameters
  ConnectCommand(string, int, MessageSim*);



  void execute() override;

  void setNewValSim();

  // void execute()override ;



};
int connectControlClient(int, const char*);


#endif //FLIGHTSIM_CONNECTCOMMAND_H