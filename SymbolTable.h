//
// Created by ori on 16/12/2019.
//

#ifndef FLIGHTSIM_SYMBOLTABLE_H
#define FLIGHTSIM_SYMBOLTABLE_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include "SimulatorObject.h"
using namespace std;

/*
 * class that identifies the map between string and SimulatorObject
 */

class SymbolTable {
private:
    unordered_map<string, SimulatorObject *> table;
    vector<string> itemsNames;
public:
    void addItem(string str, SimulatorObject * obj) {
        table.insert(std::make_pair(str, obj));
        itemsNames.push_back(str);
    }
    vector<string> getItemsNames() {
        return this->itemsNames;
    }
    SimulatorObject * getSimObj(string objName) {
        unordered_map<string, SimulatorObject *>::iterator it = table.find(objName);
        if (it == table.end()) {
            std::cout<<"name of the object is not in the table"<<std::endl;
        }
        return it->second;
    }
};


#endif //FLIGHTSIM_SYMBOLTABLE_H
