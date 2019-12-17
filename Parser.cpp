//
// Created by shmuelsuna on 15/12/2019.
//

#include "Parser.h"


// Defualt Constructer
Parser::Parser() {}

//constructer by parameters
Parser::Parser(vector<string> vectorOfStrings1) {
  this->vectorOfStrings = vectorOfStrings1;
}

// create map1, and create vector of commands in the right order, so we can iterate over them for execution
unordered_map<string, Command*> Parser::action(vector<string> vectorOfStrings) {
  //for iteraterating over commands in the right order, so we can iterate over them for execution
  vector< Command*> vectorOfCommands;

  //iterate over all vector of strings
  for (auto it = vectorOfStrings.begin(); it < vectorOfStrings.end(); ++it) {


    //OpenDataServer command
    if (*it == "openDataServer") {
      ++it;
      double digit = stod(*it);
      OpenDataServer open_data_server(digit);
      mapOfCommands["OpenDataServer"] = (&open_data_server);
      vectorOfCommands.push_back(&open_data_server);
      continue;
    }


    //Connenct control client command
    if (*it == "connectControlClient") {
      ++it;
      string ip3 = *it;
      ++it;
      double digit = stod(*it);
      ConnectCommand connect_command(ip3, digit);
      mapOfCommands["ConnectCommand"] = (&connect_command);
      vectorOfCommands.push_back(&connect_command);
      continue;
    }


    //DefineVarCommand
    if (*it == "var") {
      ++it;
      string varName_ = *it;
      ++it;

      bool arrowFlagRight_;
      if (*it == "->") {
       arrowFlagRight_ = true;
      } else {
         arrowFlagRight_ = false;
      }
      ++it;

      string sim_;
      if (*it == "sim") {
        ++it;
         sim_ = *it;
      }

      DefineVarCommand define_var_command(varName_, arrowFlagRight_, sim_, 0);
      mapOfCommands[varName_] = (&define_var_command);
      mapOfDefineVarCommands[varName_] = (&define_var_command);
      vectorOfCommands.push_back(&define_var_command);
      continue;
    }
    // Print command
    if (*it == "Print") {
      ++it;
      string message_ = *it;
      PrintCommand print_command(message_);
      mapOfCommands["Print"+*it] = (&print_command);
      vectorOfCommands.push_back(&print_command);
      continue;
    }
    //Sleep command
    if (*it == "Sleep") {
      ++it;

      int timeToSleep_ = stod(*it);
      SleepCommand sleep_command(timeToSleep_);
      mapOfCommands["Sleep"+*it] = (&sleep_command);
      vectorOfCommands.push_back(&sleep_command);
      continue;
    }
    //set var command

    while (true) {
      unordered_map<string, DefineVarCommand *>::iterator itOverMap =  mapOfDefineVarCommands.find(*it);
      //
      if (itOverMap != mapOfDefineVarCommands.end()) {//found a var that needs to be set
        //temporary untill we do expressions
        DefineVarCommand* define_var_command_ptr = itOverMap->second;
        it+=2;
        double digit = stod(*it);
        // Expression *tempExpression;
        SetVarCommand set_var_command(define_var_command_ptr,digit);
        mapOfCommands["SetVarCommand" + itOverMap->first] = (&set_var_command);
        vectorOfCommands.push_back(&set_var_command);
        break;
      }
      break;
    }

//set var command


/*
    unordered_map<string, Command *>::iterator itOverMap =  mapOfCommands.find(*it);
    itOverMap->second->execute();
*/















    //condition command



  }
  return this->GetMapOfCommands();
}



 unordered_map<string, Command*> Parser::GetMapOfCommands()  {
  return mapOfCommands;
}
