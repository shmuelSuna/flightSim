//
// Created by ori on 19/12/2019.
//

#include "ServerValuesMap.h"

void ServerValuesMap::insert(int i, SimulatorObject * obj) {
    this->map.insert(make_pair(i, obj));
}
SimulatorObject* ServerValuesMap::getSimObj(int i) {
    unordered_map<int,SimulatorObject*>::iterator it = this->map.find(i);
    if (it == this->map.end()) {
        throw ("no match");
    }
    return it->second;
}
void ServerValuesMap::printServerValuesTeset() {
    cout<<"\nServer Values Map Print:\n";
    unordered_map<int, SimulatorObject*>::iterator it = map.begin();
    SimulatorObject* temp;
    for (;it != map.end(); it++) {
        temp = it->second;
        cout<<temp->getName()<<": "<<temp->getValue()<<endl;
    }
}