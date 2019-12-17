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
#include <vector>
using namespace std;



class OpenDataServer : public Command {

private:
    int port;
    std::vector<string> variableNames;
    SymbolTable* symbolTable;

public:
    // defualt constructer
    OpenDataServer();

    //constructer by parameters
    OpenDataServer(int x);

    void execute(vector<string>::iterator &it);

    //the open data server should have an accecc to the table to update the variables that come from the Simulator
    void setSymbolTable(SymbolTable*);

    void printHello() {
        cout<<"hello"<<endl;
        return;;
    }

};
int openServer(int, SymbolTable*);

vector<float>fromBufferToFloats(string);



#endif //FLIGHTSIM__OPENDATASERVER_H_
