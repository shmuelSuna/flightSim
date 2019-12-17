//
// Created by ori on 16/12/2019.
//

#ifndef FLIGHTSIM_CREATESYMBOLTABLE_H
#define FLIGHTSIM_CREATESYMBOLTABLE_H

#include <string>
#include "SymbolTable.h"

using namespace std;
/*
 * static method that creates a map of 23 items. those are the items that we should get from the Simulator,
 * according to the given XML file. we map between the variable string to its simulator object.
 * the function returns a pointer to the table. some of the objects have names like thier name in the fly.txt file
 */
static SymbolTable *  createSymbolTable() {
    SymbolTable * symbolTablePtr = new SymbolTable();

    SimulatorObject * simObj1 = new SimulatorObject("airspeed");
    symbolTablePtr->addItem("airspeed", simObj1);
    simObj1->setSimPath("/instrumentation/airspeed-indicator/indicated-speed-kt");

    SimulatorObject * simObj2 = new SimulatorObject("heading");
    symbolTablePtr->addItem("heading", simObj2);
    simObj2->setSimPath("/instrumentation/heading-indicator/offset-deg");

    SimulatorObject * simObj3 = new SimulatorObject("alt");
    symbolTablePtr->addItem("alt", simObj3);
    simObj3->setSimPath("/instrumentation/altimeter/indicated-altitude-ft");

    SimulatorObject * simObj4 = new SimulatorObject("altimeter_pressure-alt-ft");
    symbolTablePtr->addItem("altimeter_pressure-alt-ft", simObj4);
    simObj4->setSimPath("/instrumentation/altimeter/pressure-alt-ft");

    SimulatorObject * simObj5 = new SimulatorObject("attitude-indicator_indicated-pitch-deg");
    symbolTablePtr->addItem("attitude-indicator_indicated-pitch-deg", simObj5);
    simObj5->setSimPath("/instrumentation/attitude-indicator/indicated-pitch-deg");

    SimulatorObject * simObj6 = new SimulatorObject("roll");
    symbolTablePtr->addItem("roll", simObj6);
    simObj6->setSimPath("/instrumentation/attitude-indicator/indicated-roll-deg");

    SimulatorObject * simObj7 = new SimulatorObject("pitch");
    symbolTablePtr->addItem("pitch", simObj7);
    simObj7->setSimPath("/instrumentation/attitude-indicator/internal-pitch-deg");

    SimulatorObject * simObj8 = new SimulatorObject("attitude-indicator_internal-roll-deg");
    symbolTablePtr->addItem("attitude-indicator_internal-roll-deg", simObj8);
    simObj8->setSimPath("/instrumentation/attitude-indicator/internal-roll-deg");

    SimulatorObject * simObj9 = new SimulatorObject("encoder_indicated-altitude-ft");
    symbolTablePtr->addItem("encoder_indicated-altitude-ft", simObj9);
    simObj9->setSimPath("/instrumentation/encoder/indicated-altitude-ft");

    SimulatorObject * simObj10 = new SimulatorObject("encoder_pressure-alt-ft");
    symbolTablePtr->addItem("encoder_pressure-alt-ft", simObj10);
    simObj10->setSimPath("/instrumentation/encoder/pressure-alt-ft");

    SimulatorObject * simObj11 = new SimulatorObject("gps_indicated-altitude-ft");
    symbolTablePtr->addItem("gps_indicated-altitude-ft", simObj11);
    simObj11->setSimPath("/instrumentation/gps/indicated-altitude-ft");

    SimulatorObject * simObj12 = new SimulatorObject("gps_indicated-ground-speed-kt");
    symbolTablePtr->addItem("gps_indicated-ground-speed-kt", simObj12);
    simObj12->setSimPath("/instrumentation/gps/indicated-ground-speed-kt");

    SimulatorObject * simObj13 = new SimulatorObject("gps_indicated-vertical-speed");
    symbolTablePtr->addItem("gps_indicated-vertical-speed", simObj13);
    simObj13->setSimPath("/instrumentation/gps/indicated-vertical-speed");

    SimulatorObject * simObj14 = new SimulatorObject("indicated-heading-deg");
    symbolTablePtr->addItem("indicated-heading-deg", simObj14);
    simObj14->setSimPath("/instrumentation/heading-indicator/indicated-heading-deg");

    SimulatorObject * simObj15 = new SimulatorObject("magnetic-compass_indicated-heading-deg");
    symbolTablePtr->addItem("magnetic-compass_indicated-heading-deg", simObj15);
    simObj15->setSimPath("/instrumentation/magnetic-compass/indicated-heading-deg");

    SimulatorObject * simObj16 = new SimulatorObject("slip-skid-ball_indicated-slip-skid");
    symbolTablePtr->addItem("slip-skid-ball_indicated-slip-skid", simObj16);
    simObj16->setSimPath("/instrumentation/slip-skid-ball/indicated-slip-skid");

    SimulatorObject * simObj17 = new SimulatorObject("turn-indicator_indicated-turn-rate");
    symbolTablePtr->addItem("turn-indicator_indicated-turn-rate", simObj17);
    simObj17->setSimPath("/instrumentation/turn-indicator/indicated-turn-rate");

    SimulatorObject * simObj18 = new SimulatorObject("vertical-speed-indicator_indicated-speed-fpm");
    symbolTablePtr->addItem("vertical-speed-indicator_indicated-speed-fpm", simObj18);
    simObj18->setSimPath("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");

    SimulatorObject * simObj19 = new SimulatorObject("flight_aileron");
    symbolTablePtr->addItem("flight_aileron", simObj19);
    simObj19->setSimPath("/controls/flight/aileron");

    SimulatorObject * simObj20 = new SimulatorObject("flight_elevator");
    symbolTablePtr->addItem("flight_elevator", simObj20);
    simObj20->setSimPath("/controls/flight/elevator");

    SimulatorObject * simObj21 = new SimulatorObject("flight_rudder");
    symbolTablePtr->addItem("flight_rudder", simObj21);
    simObj21->setSimPath("/controls/flight/rudder");

    SimulatorObject * simObj22 = new SimulatorObject("flight_flaps");
    symbolTablePtr->addItem("flight_flaps", simObj22);
    simObj22->setSimPath("/controls/flight/flaps");

    SimulatorObject * simObj23 = new SimulatorObject("engine_throttle");
    symbolTablePtr->addItem("engine_throttle", simObj23);
    simObj23->setSimPath("/controls/engines/engine/throttle");

    SimulatorObject * simObj24 = new SimulatorObject("rpm");
    symbolTablePtr->addItem("rpm", simObj24);
    simObj24->setSimPath("/engines/engine/rpm");



    return symbolTablePtr;
}


#endif //FLIGHTSIM_CREATESYMBOLTABLE_H
