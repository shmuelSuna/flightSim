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

