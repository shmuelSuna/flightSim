//
// Created by ori on 16/12/2019.
//

#ifndef FLIGHTSIM_SYMBOLTABLE_H
#define FLIGHTSIM_SYMBOLTABLE_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include "SimulatorObject.h"

class SymbolTable {
private:
    std::unordered_map<std::string, SimulatorObject *> table;
    std::vector<std::string> itemsNames;
public:
    void addItem(std::string str, SimulatorObject * obj) {
        table.insert(std::make_pair(str, obj));
        itemsNames.push_back(str);
    }
    std::vector<std::string> getItemsNames() {
        return this->itemsNames;
    }
    SimulatorObject * getSimObj(std::string objName) {
        std::unordered_map<std::string, SimulatorObject *>::iterator it = table.find(objName);
        if (it == table.end()) {
            std::cout<<"name of the object is not in the table"<<std::endl;
        }
        return it->second;
    }
};


#endif //FLIGHTSIM_SYMBOLTABLE_H
