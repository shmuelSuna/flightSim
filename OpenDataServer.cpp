//
// Created by shmuelsuna on 13/12/2019.
//
#include "OpenDataServer.h"






//constructer by parameters
OpenDataServer::OpenDataServer(ServerValuesMap* valuesMap, int i) {
    this->serverValuesMap = valuesMap;
    this->port = i;
}




void OpenDataServer::dataServerUpdate(int i, SimulatorObject * ob) {
    this->serverValuesMap->insert(i,ob);
}


int OpenDataServer::openServer() {


    int port = this->port;
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
    address.sin_port = htons(port);
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

    isServerConnect = true;
    cv.notify_one();

    SimulatorObject * tempObj;

    //reading from client
    char buffer[1024] = {0};

    //server is always on
    while (true) {
        int valread = read(client_socket, buffer, 1024);
        vector<float> flightValues = fromBufferToFloats(buffer);
        vector<float >::iterator valuesIter = flightValues.begin();

        int i = 0;
        for (i = 0; i < 36; i++) {
            try {
                tempObj = this->serverValuesMap->getSimObj(i);
                tempObj->setValue(*valuesIter);
                if (*valuesIter != 0 ){
                }
            } catch (const char * e) {
            }
            valuesIter++;

        }

    }
    return 1;
}








void OpenDataServer::execute() {


    openServer();

    cout<<"Another logic"<<endl;




    return;
}






/*
 * function that converts the numbers that we get from the simulator to floats in order
 * to set the value to the corresponding simulator object
 */
std::vector<float> fromBufferToFloats(std::string buffer) {
    string numStr;
    string::size_type sz;
    float tempNum;
    std::vector<float>floatsVector;
    for (char& c : buffer) {
        if (c == ',' || c == '\0') {
            try {
                tempNum = stof(numStr, &sz);
            } catch (const char* e) {
                cout<<e<<endl;
                continue;
            }
            floatsVector.push_back(tempNum);
            numStr = "";
            continue;
        }
        numStr.push_back(c);

    }
    try {
        tempNum = stof(numStr,&sz);
    } catch (const char* e) {
        cout<<e<<endl;
    }

    floatsVector.push_back(tempNum);

    return floatsVector;

}