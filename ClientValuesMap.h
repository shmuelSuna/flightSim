//
// Created by ori on 21/12/2019.
//

#ifndef FLIGHTSIM_CLIENTVALUESMAP_H
#define FLIGHTSIM_CLIENTVALUESMAP_H

#include <unordered_map>
#include "ConnectCommand.h"
class ClientValuesMap {
private:
    unordered_map<string, SimulatorObject*> map;
    ConnectCommand * cc;
public:void setConnentor(ConnectCommand *);
    void updateValue(string, float);
    void addValue(string, SimulatorObject*);

};


#endif //FLIGHTSIM_CLIENTVALUESMAP_H
