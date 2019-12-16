//
// Created by ori on 15/12/2019.
//

#ifndef FLIGHTSIM_SIMULATOROBJECT_H
#define FLIGHTSIM_SIMULATOROBJECT_H
#include <string>
#include <iostream>



class SimulatorObject {
private:
    float value;
     std::string name;
     std::string simPath;
public:
    SimulatorObject(std::string str) {
        this->name = str;
    }
    ~SimulatorObject() {

    }
    void setValue(float f) {
        if (f != value) {
        std::cout<<name<<" is changed to "<<value<<std::endl;
        }
        this->value = f;

    }
    void setSimPath(std::string pathStr) {
        this->simPath = pathStr;
    }
    std::string getName() {
        return this->name;
    }
    float getValue() {
        return this->value;
    }

};


#endif //FLIGHTSIM_SIMULATOROBJECT_H
