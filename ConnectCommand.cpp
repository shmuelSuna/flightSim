//
// Created by shmuelsuna on 13/12/2019.
//

#include "ConnectCommand.h"


// Defualt Constructer
ConnectCommand::ConnectCommand() {}


//constructer by parameters
ConnectCommand::ConnectCommand(string ip1, int port1, MessageSim * m) {
  this->ip = ip1;
  this->port = port1;
  this->message = m;
}

/*
 * blocking call of connecting as client and then we take the client socket
 * we got and open a thread with the function that has the responsibility
 * to get the string of commands from the messanger queue and send to the simulator
 */
void ConnectCommand::execute() {

    const char* ip2 = this->ip.c_str();
    this->client_socket = connectControlClient(this->port, ip2);
    thread t1([this]{setNewValSim();});
    t1.detach();
}



/*
 * function that is a while loop as long as we want to send commands to the
 * simulator, pop a message from the messangerSim and send to the simulator.
 * as long as there are messages in the messangerSim queue we will send
 * them to the simulator in the inner loop
 */
void ConnectCommand::setNewValSim() {
    while (isClientOn) {

        while (!this->message->isMessangerEmpty()) {
            string c = this->message->getMessage();
            int n = c.size();
            char command[n + 1];
            strcpy(command, c.c_str());

            int is_sent2 = send(client_socket, command, strlen(command), 0);
            if (is_sent2 == -1) {
                std::cout << "Error sending message" << std::endl;
            }

            char buffer[1024] = {0};
            int valread = read(client_socket, buffer, 1024);
           // std::cout << "message returned from the simulator: " << buffer << std::endl;

        }


    }
    close(client_socket);

}


/*
 * connectControlClient function to create the connection between our commands to get to the simulator
 * vector of strings is the name of the variables that we will want to update
 */
int connectControlClient(int port, const char* ip) {
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
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 5402
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }
    return client_socket;





}