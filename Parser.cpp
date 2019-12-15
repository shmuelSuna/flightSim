//
// Created by shmuelsuna on 15/12/2019.
//

#include "Parser.h"

#include "OpenDataServer.h"
#include "ConnectCommand.h"
#include <unordered_map>
#include "DefineVarCommand.h"



// Defualt Constructer
Parser::Parser(){}

//constructer by parameters
Parser::Parser(vector<string>vectorOfStrings1) {
  this->vectorOfStrings = vectorOfStrings1;
}

//iterate over vector of strings, make map1
void Parser:: action(vector<string> vectorOfStrings){

  //iterate over all vector of strings
  for (auto it = vectorOfStrings.begin();it< vectorOfStrings.end(); ++it) {

    //OpenDataServer command
    if(*it == "OpenDataServer") {
      ++it;
      double digit = stod(*it);
      OpenDataServer open_data_server(digit);
      mapOfCommands["OpenDataServer"]=(open_data_server);
      continue;
    }


    //Connenct control client command
    if(*it == "ConnectCommand") {
      ++it;
      string ip3 = *it;
      ++it;
      double digit = stod(*it);
      ConnectCommand connect_command(ip3,digit);
      continue;
    }


    //DefineVarCommand
    if(*it == "var") {
      ++it;
      string varName1 = *it;
      ++it;

      if (*it == "->"){
        bool arrowFlagRight1 = true;
      } else {
        bool arrowFlagRight1 = false;
      }










//      ConnectCommand connect_command(ip3,digit);
      continue;
    }

  }


}