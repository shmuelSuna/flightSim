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
int SymbolTable::isPathExist(string str) {
    vector<string>::iterator it  = this->allSimPath.begin();
    int i = 0;
    for (it; it < this->allSimPath.end(); it++) {
        if (*it == str) {
            return i;
        }
        i++;
    }
    return -1;
}

SymbolTable::SymbolTable() {
    this->allSimPath = allSimPathCreator();
}





/*
 * function that takes all 24 values of the XML file and put them as a data membet of the table
 *
 */
vector <string> allSimPathCreator() {
    vector <string> pathVec;
    pathVec.push_back("/instrumentation/airspeed-indicator/indicated-speed-kt"); //1
    pathVec.push_back("/instrumentation/heading-indicator/offset-deg"); //2
    pathVec.push_back("/instrumentation/altimeter/indicated-altitude-ft"); //3
    pathVec.push_back("/instrumentation/altimeter/pressure-alt-ft"); //4
    pathVec.push_back("/instrumentation/attitude-indicator/indicated-pitch-deg"); //5
    pathVec.push_back("/instrumentation/attitude-indicator/indicated-roll-deg"); //6
    pathVec.push_back("/instrumentation/attitude-indicator/internal-pitch-deg"); //7
    pathVec.push_back("/instrumentation/attitude-indicator/internal-roll-deg"); //8
    pathVec.push_back("/instrumentation/encoder/indicated-altitude-ft"); //9
    pathVec.push_back("/instrumentation/encoder/pressure-alt-ft"); //10
    pathVec.push_back("/instrumentation/gps/indicated-altitude-ft"); //11
    pathVec.push_back("/instrumentation/gps/indicated-ground-speed-kt"); //12
    pathVec.push_back("/instrumentation/gps/indicated-vertical-speed"); //13
    pathVec.push_back("/instrumentation/heading-indicator/indicated-heading-deg"); //14
    pathVec.push_back("/instrumentation/magnetic-compass/indicated-heading-deg"); //15
    pathVec.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid"); //16
    pathVec.push_back("/instrumentation/turn-indicator/indicated-turn-rate"); //17
    pathVec.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm"); //18
    pathVec.push_back("/controls/flight/aileron"); //19
    pathVec.push_back("/controls/flight/elevator"); //20
    pathVec.push_back("/controls/flight/rudder"); //21
    pathVec.push_back("/controls/flight/flaps"); //22
    pathVec.push_back("/controls/engines/engine/throttle"); //23
    pathVec.push_back("/engines/engine/rpm"); //24

    return pathVec;
}
