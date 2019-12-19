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

//iterate over vector of strings, make map1
unordered_map<string, Command*> Parser::action(vector<string> vectorOfStrings) {
    SymbolTable * simTable = new SymbolTable();

    //map of the server to know which values that we get from the text file to update
    ServerValuesMap * serverValuesMap = new ServerValuesMap;


    OpenDataServer open_data_server(serverValuesMap);
    isServerOn = false;


    //iterate over all vector of strings
  for (auto it = vectorOfStrings.begin(); it < vectorOfStrings.end(); ++it) {


    //OpenDataServer command
    if (*it == "openDataServer") {
      ++it;
      double digit = stod(*it);
      open_data_server.setPort(digit);
      // mapOfCommands["OpenDataServer"] = (&open_data_server);

      continue;

    }

      thread t1([&]() {
          return open_data_server.execute(it);});
    int i = 0;
    while (!isServerOn) {
        cout<<i<<endl;
        cout<<"isServerOn is::"<<isServerOn<<endl;
        this_thread::sleep_for(10s);
        if (i == 2) {
            isServerOn = true;
        }
        i++;
    }
    cout<<"xxxxxxxxxxxxx"<<endl;
    t1.join();

    //Connenct control client command
    if (*it == "connectControlClient") {
      ++it;
      string ip3 = *it;
      ++it;
      double digit = stod(*it);
      ConnectCommand connect_command(ip3, digit);
      mapOfCommands["ConnectCommand"] = (&connect_command);
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
        SimulatorObject * simObj = new SimulatorObject(varName_, sim_);

        //in this if statement we check the index of the path in the XML file in order to call the dataServer to update values in the symbol table in those indexes.
      if (!arrowFlagRight_) {
          int index = simTable->isPathExist(sim_);
          if (index == -1) {
              cout << "the sim path is not in the XML file" << endl;
          } else {
              cout<< "the index of the var in the XML is " << index<< endl;
              serverValuesMap->insert(index, simObj);
          }
      }

      DefineVarCommand define_var_command(varName_, arrowFlagRight_, sim_, 0);
      mapOfCommands[varName_] = (&define_var_command);
      continue;
    }
    // Print command
    if (*it == "Print") {
      ++it;
      string message_ = *it;
      PrintCommand print_command(message_);
      mapOfCommands["Print"] = (&print_command);
    }
    //Sleep command
    if (*it == "Sleep") {
      ++it;
      int timeToSleep_ = stod(*it);
      SleepCommand sleep_command(timeToSleep_);
      mapOfCommands["Sleep"] = (&sleep_command);
    }


  }


  return this->GetMapOfCommands();
}



 unordered_map<string, Command*> Parser::GetMapOfCommands()  {
  return mapOfCommands;
}
