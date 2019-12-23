//
// Created by ori on 22/12/2019.
//

#ifndef FLIGHTSIM_MESSAGESIM_H
#define FLIGHTSIM_MESSAGESIM_H

#include <iostream>
#include <condition_variable>
#include <string>

using namespace std;

extern bool newMessage;
extern condition_variable cv;
extern mutex m;
extern unique_lock<mutex> ul;

using namespace std;

class MessageSim {
private:
    string message;
public:
    void setMessage(float, string);
    string getMessage();

};


#endif //FLIGHTSIM_MESSAGESIM_H
