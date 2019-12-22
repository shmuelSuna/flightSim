//
// Created by ori on 22/12/2019.
//

#include "MessageSim.h"
#include <sstream>


void MessageSim::setMessage(float v, string path) {
    ostringstream oss;
    oss << "set " << path << " " << to_string(v) << "\r\n";
    this->message = oss.str();
    newMessage = true;
    cv.notify_one();
}
string MessageSim::getMessage() {
    return this->message;
}