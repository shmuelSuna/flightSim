//
// Created by shmuelsuna on 13/12/2019.
//

#include "OpenDataServer.h"
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>

// defualt constructer
OpenDataServer::OpenDataServer(){
}

//constructer by parameters
OpenDataServer::OpenDataServer(int x){}   //int x - is just to show that there is parameters. not sure which parameters yet

void OpenDataServer::execute(vector<string>::iterator &it) {


    std::string portStr = *it;
    unsigned int PORT = atoi(portStr.c_str());
    openServer(this->port);




}

int OpenDataServer::openServer(int PORT) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(PORT);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    } else {
        std::cout << "Server is now listening ...\n" << std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *) &address,
                               (socklen_t *) &address);

    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }

    close(socketfd); //closing the listening socket
    std::cout << "wating for a messegae" << std::endl;

    //reading from client
    char buffer[1024] = {0};
    while (true) {
        int valread = read(client_socket, buffer, 1024);
        std::cout << buffer << std::endl;





    }

    return 0;





}


// open/create a thread that runs a server that listents to port 5400 (5400 is prameter)