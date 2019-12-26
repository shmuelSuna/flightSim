//
// Created by shmuelsuna on 26/12/2019.
//

#ifndef FLIGHTSIM__IFCOMMAND_H_
#define FLIGHTSIM__IFCOMMAND_H_



#include "DefineVarCommand.h"
#include "Command.h"
#include "ex1.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include "Command.h"
#include <map>
#include <unordered_map>
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "SetVarCommand.h"
#include "MessageSim.h"


class IfCommand: public Command {
  string operator_;

  Expression* Right_expression_;
  Expression* Left_expression_;

  string leftStringToMakeIntoExpression;
  string rightStringToMakeIntoExpression;

  vector<Command*> vectorOfCommandsForWhileLoop;
  unordered_map<string, DefineVarCommand *> mapOfDefineVarCommands;

  int counterForHowMuchIteratorShouldJump=0;

 public:


// defualt constructer
  IfCommand();

  //constructer by parameters
  IfCommand(vector<Command*>,string,string,string,unordered_map<string, DefineVarCommand *>);


  void execute() override ;

  bool checkIfNameOfADefineVarIsInString(string);

  map<string, double> SetMapUpForInterpeter(string );

  unordered_map<string, DefineVarCommand *> GetMapOfDefineVarCommands();

  Expression* createLeftExpression( map<string, double>);
  Expression* createRightExpression( map<string, double>);

  void SetUpExpressions();

  void SetRightExpression(Expression *right_expression);
  void SetLeftExpression(Expression *left_expression);

  Expression *GetRightExpression() const;
  Expression *GetLeftExpression() const;
  const string &GetAnOperator() const;
  const string &GetLeftStringToMakeIntoExpression() const;
  const string &GetRightStringToMakeIntoExpression() const;
  int GetCounterForHowMuchIteratorShouldJump();
  void SetCounterForHowMuchIteratorShouldJump(int counter_for_how_much_iterator_should_jump);

};


#endif //FLIGHTSIM__IFCOMMAND_H_
