//
// Created by shmuelsuna on 13/12/2019.
//

#ifndef FLIGHTSIM__OPENDATASERVER_H_
#define FLIGHTSIM__OPENDATASERVER_H_

#include <map>
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
#include "ServerValuesMap.h"
#include <vector>

using namespace std;

static bool isServerOn;

class OpenDataServer : public Command {

private:
    int port;
    int clientSocket;
    ServerValuesMap* serverValuesMap;
public:


    //constructer by parameters
    OpenDataServer(ServerValuesMap*);

    void setPort(int);

    void execute(vector<string>::iterator &it);

    //the open data server should have an access to the table to update the variables that come from the Simulator
    void dataServerUpdate(int, SimulatorObject*);


    void setClientSocket(int i);

    void printHello() {
        cout<<"hello"<<endl;
        return;;
    }

    int openServer();


};


vector<float>fromBufferToFloats(string);



#endif //FLIGHTSIM__OPENDATASERVER_H_
