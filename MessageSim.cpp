//
// Created by ori on 22/12/2019.
//

#include "MessageSim.h"



void MessageSim::addMessage(float v, string path) {
    ostringstream oss;
    oss << "set " << path << " " << to_string(v) << "\r\n";
    string s = oss.str();
    const char * string1 = s.c_str();
    this->message_queue.push(string1);

}
string MessageSim::getMessage() {
    string s =  this->message_queue.front();
    this->message_queue.pop();
    return s;
}
bool MessageSim::isMessangerEmpty() {
    return this->message_queue.empty();
}

