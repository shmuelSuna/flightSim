//
// Created by shmuelsuna on 13/12/2019.
//

#include "DefineVarCommand.h"

//Defualt Constructer
DefineVarCommand::DefineVarCommand(){}

DefineVarCommand::DefineVarCommand(const string &var_name, bool arrow_flag_right, const string &sim, double var_value)
    : varName(var_name), arrowFlagRight(arrow_flag_right), sim(sim), VarValue(var_value) {}

void DefineVarCommand::execute(vector<string>::iterator &it) {

}
const string &DefineVarCommand::GetVarName() const {
  return varName;
}
void DefineVarCommand::SetVarName(const string &var_name) {
  varName = var_name;
}
bool DefineVarCommand::IsArrowFlagRight() const {
  return arrowFlagRight;
}
void DefineVarCommand::SetArrowFlagRight(bool arrow_flag_right) {
  arrowFlagRight = arrow_flag_right;
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

