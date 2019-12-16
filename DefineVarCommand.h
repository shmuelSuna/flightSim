//
// Created by shmuelsuna on 13/12/2019.
//

#ifndef FLIGHTSIM__DEFINEVARCOMMAND_H_
#define FLIGHTSIM__DEFINEVARCOMMAND_H_

#include "Command.h"


class DefineVarCommand : public Command{
 private:

  string varName;
  bool arrowFlagRight;
  string sim;
  double VarValue;
 public:



  //Defualt Constructer
  DefineVarCommand();

  // Constructer with parameters
  DefineVarCommand(const string &var_name, bool arrow_flag_right, const string &sim, double var_value);




  //option 1
  void execute(vector<string>::iterator &it) override;

  //option 2
  // void execute()override ;


};

#endif //FLIGHTSIM__DEFINEVARCOMMAND_H_
