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


/*
 * function thats executes sleep command- to sleep for correct amount of milisecounds
 */
void SleepCommand:: execute(){
    this_thread::sleep_for(chrono::milliseconds(timeToSleep));

}
