//
// Created by ori on 19/12/2019.
//

#ifndef FLIGHTSIM_SERVERVALUESMAP_H
#define FLIGHTSIM_SERVERVALUESMAP_H

#include <unordered_map>
#include "SimulatorObject.h"

using namespace std;


/*
 * this map holds a name of a simulator and its object
 * all the simulatorObject in this map are objects that
 * we need to change their values according to what we
 * get from the simulator (the 36 values from the XML file)
 * in the openDataServer class we update their value and
 * the DefineVarCommand updates its value by the appropriate simulatorObject
 */
class ServerValuesMap {
private:
    unordered_map<int,SimulatorObject*> map;
public:
    void insert(int, SimulatorObject*);
    SimulatorObject* getSimObj(int);
    void printServerValuesTeset();
};

#endif //FLIGHTSIM_SERVERVALUESMAP_H
