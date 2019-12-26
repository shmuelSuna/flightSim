//
// Created by shmuelsuna on 13/12/2019.
//

#ifndef FLIGHTSIM__DEFINEVARCOMMAND_H_
#define FLIGHTSIM__DEFINEVARCOMMAND_H_

#include "Command.h"
#include "ConnectCommand.h"

class DefineVarCommand : public Command{
 private:

  string varName;
  string arrow;
  string sim;
  double VarValue;
  SimulatorObject * simulator_object;
  bool hasArrow;
 public:
  bool IsHasArrow();
  void SetHasArrow(bool has_arrow);

  //Defualt Constructer
  DefineVarCommand();

  // Constructer with parameters
  DefineVarCommand(const string &var_name, string arrow, const string &sim, double var_value, SimulatorObject*);
    DefineVarCommand(const string &var_name, string arrow, const string &sim, double var_value);


  string GetArrow() const;
  void SetArrowFlagRight(string arrow);
  string GetSim();
  void SetSim( string sim);
  double GetVarValue();
  void SetVarValue(double var_value);
  SimulatorObject* getSimObj();

  //option 1
  void execute() override;

  //option 2
  // void execute()override ;

  const string &GetVarName() const;
  void SetVarName(const string &var_name);

};

#endif //FLIGHTSIM__DEFINEVARCOMMAND_H_
