//
// Created by ori on 15/12/2019.
//

#include "SimulatorObject.h"
SimulatorObject::SimulatorObject(const string str) {
    this->name = str;
}
SimulatorObject::~SimulatorObject() {

}
void SimulatorObject::setValue(float f) {
    this->value = f;

}
void SimulatorObject::setSimPath(string pathStr) {
    this->simPath = pathStr;
}
string SimulatorObject::getName() {
    return this->name;
}
float SimulatorObject::getValue() {
    return this->value;
}