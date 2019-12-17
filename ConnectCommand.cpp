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

void ConnectCommand::setVariableNames(vector<string> vec) {
    this->variableName = vec;
}


void ConnectCommand::setSymbolTable(SymbolTable * st) {
    this->symbolTable = st;
}
void ConnectCommand::execute(vector<string>::iterator &it) {

    const char* ip2 = this->ip.c_str();
    vector<string> vec;
    vec.push_back("hello test");
    connectControlClient(this->port, ip2, this->symbolTable, vec);

}


/*
 * connectControlClient function to create the connection between our commands to get to the simulator
 * vector of strings is the name of the variables that we will want to update
 */
int connectControlClient(int port, const char* ip, SymbolTable* symbolTable, vector<string> variableNames) {
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(ip);  //the localhost address
    address.sin_port = htons(port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }

    //if here we made a connection
    char hello[] = "Hi from client";
    int is_sent = send(client_socket , hello , strlen(hello) , 0 );
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    } else {
        std::cout<<"Hello message sent to server" <<std::endl;
    }

    char buffer[1024] = {0};
    int valread = read( client_socket , buffer, 1024);
    std::cout<<buffer<<std::endl;

    close(client_socket);

    return 0;






}