//
// Created by shmuelsuna on 16/12/2019.
//

#include "SleepCommand.h"

//Defualt Constructer
SleepCommand::SleepCommand(){}

// Constructer with parameters
SleepCommand::SleepCommand(int timeToSleep_){
  this->timeToSleep = timeToSleep_;
}



void SleepCommand:: execute(){
    this_thread::sleep_for(chrono::milliseconds(timeToSleep));

}
