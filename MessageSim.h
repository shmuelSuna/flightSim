//
// Created by ori on 22/12/2019.
//

#ifndef FLIGHTSIM_MESSAGESIM_H
#define FLIGHTSIM_MESSAGESIM_H

#include <iostream>
#include <condition_variable>
#include <string>
#include <queue>
#include <thread>
#include <cstring>
#include <sstream>

using namespace std;

extern condition_variable cv;
extern mutex m;
extern unique_lock<mutex> ul;

using namespace std;

class MessageSim {
private:
    queue<string> message_queue;
public:
    void addMessage(float, string);
    string getMessage();
    bool isMessangerEmpty();

};


#endif //FLIGHTSIM_MESSAGESIM_H
