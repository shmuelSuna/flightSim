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

using namespace std;


class ConnectCommand : public Command {
  string ip;
  int port;
  int client_socket;
  SymbolTable* symbolTable;
  vector<string> variableName;

 public:

  // Defualt Constructer
  ConnectCommand();

  //constructer by parameters
  ConnectCommand(string, int);


  void setSymbolTable(SymbolTable*);

  void setVariableNames(vector<string>);

  void execute(vector<string>::iterator &it) override;

  void setNewValSim(float,string);

  // void execute()override ;



};
int connectControlClient(int, const char*);


#endif //FLIGHTSIM_CONNECTCOMMAND_H