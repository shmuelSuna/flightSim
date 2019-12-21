//
// Created by ori on 21/12/2019.
//

#include "ClientValuesMap.h"
void ClientValuesMap::setConnentor(ConnectCommand * c) {
    this->cc = c;
}
void ClientValuesMap::updateValue(string s, float f) {
    unordered_map<string,SimulatorObject*>::iterator it = map.find(s);
    SimulatorObject * temp = it->second;
    temp->setValue(f);
    cc->setNewValSim(f, temp->getSim());
}
void ClientValuesMap::addValue(string s, SimulatorObject * ob) {
    map.insert(make_pair(s, ob));
}