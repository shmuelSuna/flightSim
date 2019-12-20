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
    pathVec.push_back("/sim/time/warp"); //2
    pathVec.push_back("/controls/switches/magnetos"); //3
    pathVec.push_back("/instrumentation/heading-indicator/offset-deg"); //4
    pathVec.push_back("/instrumentation/altimeter/indicated-altitude-ft"); //5
    pathVec.push_back("/instrumentation/altimeter/pressure-alt-ft"); //6
    pathVec.push_back("/instrumentation/attitude-indicator/indicated-pitch-deg"); //7
    pathVec.push_back("/instrumentation/attitude-indicator/indicated-roll-deg"); //8
    pathVec.push_back("/instrumentation/attitude-indicator/internal-pitch-deg"); //9
    pathVec.push_back("/instrumentation/attitude-indicator/internal-roll-deg"); //10
    pathVec.push_back("instrumentation/encoder/indicated-altitude-ft"); //11
    pathVec.push_back("/instrumentation/encoder/pressure-alt-ft"); //12
    pathVec.push_back("/instrumentation/gps/indicated-altitude-ft"); //13
    pathVec.push_back("/instrumentation/gps/indicated-ground-speed-kt"); //14
    pathVec.push_back("/instrumentation/gps/indicated-vertical-speed"); //15
    pathVec.push_back("/instrumentation/heading-indicator/indicated-heading-deg"); //16
    pathVec.push_back("/instrumentation/magnetic-compass/indicated-heading-deg"); //17
    pathVec.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid"); //18
    pathVec.push_back("/instrumentation/turn-indicator/indicated-turn-rate"); //19
    pathVec.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm"); //20

    pathVec.push_back("/controls/flight/aileron"); //21
    pathVec.push_back("/controls/flight/elevator"); //22
    pathVec.push_back("/controls/flight/rudder"); //23
    pathVec.push_back("/controls/flight/flaps"); //24
    pathVec.push_back("/controls/engines/engine/throttle"); //25
    pathVec.push_back("/controls/engines/current-engine/throttle"); //26
    pathVec.push_back("/controls/switches/master-avionics"); //27
    pathVec.push_back("/controls/switches/starter"); //28
    pathVec.push_back("/engines/active-engine/auto-start"); //29
    pathVec.push_back("/controls/flight/speedbrake"); //30
    pathVec.push_back("/sim/model/c172p/brake-parking"); //31
    pathVec.push_back("/controls/engines/engine/primer"); //32
    pathVec.push_back("/controls/engines/current-engine/mixture"); //33
    pathVec.push_back("/controls/switches/master-bat"); //34
    pathVec.push_back("/controls/switches/master-alt"); //35
    pathVec.push_back("/engines/engine/rpm"); //36

    return pathVec;
}

/*
 *
 *      <node>/instrumentation/airspeed-indicator/indicated-speed-kt</node>
<node>/sim/time/warp</node>
<node>/controls/switches/magnetos</node>
<node>//instrumentation/heading-indicator/offset-deg</node>
<node>/instrumentation/altimeter/indicated-altitude-ft</node>

<node>/instrumentation/altimeter/pressure-alt-ft</node>
<node>/instrumentation/attitude-indicator/indicated-pitch-deg</node>
<node>/instrumentation/attitude-indicator/indicated-roll-deg</node>
<node>/instrumentation/attitude-indicator/internal-pitch-deg</node>
<node>/instrumentation/attitude-indicator/internal-roll-deg</node>

<node>/instrumentation/encoder/indicated-altitude-ft</node>
<node>/instrumentation/encoder/pressure-alt-ft</node>
<node>/instrumentation/gps/indicated-altitude-ft</node>
<node>/instrumentation/gps/indicated-ground-speed-kt</node>
<node>/instrumentation/gps/indicated-vertical-speed</node>

<node>/instrumentation/heading-indicator/indicated-heading-deg</node>
<node>/instrumentation/magnetic-compass/indicated-heading-deg</node>
<node>/instrumentation/slip-skid-ball/indicated-slip-skid</node>
<node>/instrumentation/turn-indicator/indicated-turn-rate</node>
<node>/instrumentation/vertical-speed-indicator/indicated-speed-fpm</node>

<node>/controls/flight/aileron</node>
<node>/controls/flight/elevator</node>
<node>/controls/flight/rudder</node>
<node>/controls/flight/flaps</node>
<node>/controls/engines/engine/throttle</node>

<node>/controls/engines/current-engine/throttle</node>
<node>/controls/switches/master-avionics</node>
<node>/controls/switches/starter</node>
<node>/engines/active-engine/auto-start</node>
<node>/controls/flight/speedbrake</node>

<node>/sim/model/c172p/brake-parking</node>
<node>/controls/engines/engine/primer</node>
<node>/controls/engines/current-engine/mixture</node>
<node>/controls/switches/master-bat</node>
<node>/controls/switches/master-alt</node>
<node>/engines/engine/rpm</node>
 */
