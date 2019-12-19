//
// Created by ori on 15/12/2019.
//

#include "SimulatorObject.h"
SimulatorObject::SimulatorObject(string str1, string str2) {
    this->name = str1;
    this->simPath = str2;
}
SimulatorObject::~SimulatorObject() {

}
void SimulatorObject::setValue(float f) {
    this->value = f;

}
string SimulatorObject::getName() {
    return this->name;
}
float SimulatorObject::getValue() {
    return this->value;
}