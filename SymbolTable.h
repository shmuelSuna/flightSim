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
    vector<string> allSimPath;
public:
    SymbolTable();
    ~SymbolTable();
    void addItem(string, SimulatorObject *);
    vector<string> getItemsNames();
    SimulatorObject * getSimObj(string);
    int isPathExist(string);
};
vector<string> allSimPathCreator();

#endif //FLIGHTSIM_SYMBOLTABLE_H
