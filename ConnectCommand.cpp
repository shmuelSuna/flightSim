//
// Created by shmuelsuna on 13/12/2019.
//

#include "ConnectCommand.h"


// Defualt Constructer
ConnectCommand::ConnectCommand() {}


//constructer by parameters
ConnectCommand::ConnectCommand(string ip1, int port1) {
  this->ip = ip1;
  this->port = port1;
}
void ConnectCommand::execute(vector<string>::iterator &it) {

}