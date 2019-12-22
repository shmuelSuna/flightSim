//
// Created by ori on 21/12/2019.
//

#include "ClientValuesMap.h"


void ClientValuesMap::addValue(string s, SimulatorObject * ob) {
    map.insert(make_pair(s, ob));
}