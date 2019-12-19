//
// Created by ori on 19/12/2019.
//

#include "ServerValuesMap.h"

void ServerValuesMap::insert(int i, SimulatorObject * obj) {
    this->map.insert(make_pair(i, obj));
}
SimulatorObject* ServerValuesMap::getSimObj(int i) {
    unordered_map<int,SimulatorObject*>::iterator it = this->map.find(i);
    if (it != this->map.end()) {
        throw ("no match");
    }
    return it->second;
}