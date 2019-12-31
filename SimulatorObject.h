//
// Created by ori on 15/12/2019.
//

#ifndef FLIGHTSIM_SIMULATOROBJECT_H
#define FLIGHTSIM_SIMULATOROBJECT_H

#include <string>
#include <iostream>

using namespace std;

/*
 * class SimulatorObject that holds the details about a variable in the simulator
 * we will want to set all the time its value.
 */

class SimulatorObject {
private:
    float value;
     string name;
     string simPath;
public:
    SimulatorObject(string, string);
    ~SimulatorObject();
    void setValue(float);
    string getName();
    float getValue();

};


#endif //FLIGHTSIM_SIMULATOROBJECT_H
