//
// Created by ori on 16/12/2019.
//

#include "SymbolTable.h"

void SymbolTable::addItem(string str, SimulatorObject * obj) {
    table.insert(std::make_pair(str, obj));
    itemsNames.push_back(str);
}
vector<string> SymbolTable::getItemsNames() {
    return this->itemsNames;
}
SimulatorObject * SymbolTable::getSimObj(string objName) {
    unordered_map<string, SimulatorObject *>::iterator it = table.find(objName);
    if (it == table.end()) {
        std::cout<<"name of the object is not in the table"<<std::endl;
    }
    return it->second;
}
