//
// Created by shmuelsuna on 15/12/2019.
//

#include "Parser.h"

#include "Parser.h"
#include "OpenDataServer.h"
#include <unordered_map>
#include <map>



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
    }


    //Connenct control client command
    if(*it == "ConnectCommand") {
      ++it;

      double digit = stod(*it);
      OpenDataServer open_data_server(digit);
    }

  }


}