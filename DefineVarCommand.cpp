//
// Created by shmuelsuna on 13/12/2019.
//

#include "DefineVarCommand.h"

//Defualt Constructer
DefineVarCommand::DefineVarCommand(){}

DefineVarCommand::DefineVarCommand(const string &var_name, string arrow, const string &sim, double var_value, SimulatorObject * simObj)
    : varName(var_name), arrow(arrow), sim(sim), VarValue(var_value), simulator_object(simObj) {}

DefineVarCommand::DefineVarCommand(const string &var_name, string arrow, const string &sim, double var_value)
        : varName(var_name), arrow(arrow), sim(sim), VarValue(var_value) {}

void DefineVarCommand:: DefineVarCommand::execute() {
    if (arrow == "<-") {
        VarValue = simulator_object->getValue();
    }


}
const string &DefineVarCommand::GetVarName() const {
  return varName;
}
void DefineVarCommand::SetVarName(const string &var_name) {
  varName = var_name;
}
string DefineVarCommand::GetArrow() const {
  return arrow;
}
void DefineVarCommand::SetArrowFlagRight(string arrow_) {
  arrow = arrow_;
}
 string DefineVarCommand::GetSim() {
  return sim;
}
void DefineVarCommand::SetSim(string sim) {
  DefineVarCommand::sim = sim;
}
double DefineVarCommand::GetVarValue() {
  return VarValue;
}
void DefineVarCommand::SetVarValue(double var_value) {
  VarValue = var_value;
}
bool DefineVarCommand::IsHasArrow()  {
  return hasArrow;
}
void DefineVarCommand::SetHasArrow(bool has_arrow) {
  hasArrow = has_arrow;
}

