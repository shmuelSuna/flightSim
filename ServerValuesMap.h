//
// Created by ori on 19/12/2019.
//

#ifndef FLIGHTSIM_SERVERVALUESMAP_H
#define FLIGHTSIM_SERVERVALUESMAP_H

#include <unordered_map>
#include "SimulatorObject.h"

using namespace std;



class ServerValuesMap {
private:
    unordered_map<int,SimulatorObject*> map;
public:
    void insert(int, SimulatorObject*);
    SimulatorObject* getSimObj(int);
    void printServerValuesTeset();
};

#endif //FLIGHTSIM_SERVERVALUESMAP_H
