//
// Created by shmuelsuna on 13/12/2019.
//

#ifndef FLIGHTSIM__OPENDATASERVER_H_
#define FLIGHTSIM__OPENDATASERVER_H_

#include <map>
#include "OpenDataServer.h"
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <unordered_map>
#include "Command.h"
#include "CreateSymbolTable.h"
#include "SymbolTable.h"
#include <vector>
using namespace std;



class OpenDataServer : public Command {

private:
    std::vector<string> variableNames;


public:
    // defualt constructer
    OpenDataServer();

    //constructer by parameters
    OpenDataServer(int x);   //int x - is just to show that there is parameters. not sure which parameters yet

    void execute(vector<string>::iterator &it);




};
int openServer(int);

std::vector<float>fromBufferToFloats(std::string str);



#endif //FLIGHTSIM__OPENDATASERVER_H_
