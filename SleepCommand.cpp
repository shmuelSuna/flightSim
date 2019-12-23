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




//option 1
void SleepCommand:: execute(){
    cout<<"In sleep command sleeping"<<endl;
    this_thread::sleep_for(chrono::milliseconds(timeToSleep));

}

//option 2
// void execute()override ;
