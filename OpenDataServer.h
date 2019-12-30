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
#include "SymbolTable.h"
#include "ServerValuesMap.h"
#include <vector>
#include "Parser.h"
#include <mutex>

using namespace std;



class OpenDataServer : public Command {

private:

    int port;
    ServerValuesMap* serverValuesMap;
    int cliient_socket;





public:


    //constructer by parameters
    OpenDataServer(ServerValuesMap*, int);

    void setPort(int);



    void execute() override;

    //the open data server should have an access to the table to update the variables that come from the Simulator
    void dataServerUpdate(int, SimulatorObject*);

    void connectionWhileloop();

    void printHello() {
        cout<<"hello"<<endl;
        return;;
    }

    int openServer();


};


vector<float>fromBufferToFloats(string);



#endif //FLIGHTSIM__OPENDATASERVER_H_
