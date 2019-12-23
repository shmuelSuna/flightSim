//
// Created by shmuelsuna on 19/12/2019.
//

#ifndef FLIGHTSIM_WHILECOMMAND_H
#define FLIGHTSIM_WHILECOMMAND_H


#include "DefineVarCommand.h"
#include "Command.h"
#include "CondtionParserCommand.h"
#include "ex1.h"
#include "Parser.h"
class WhileCommand: public Command {
  string operator_;

  Expression* Right_expression_;
  Expression* Left_expression_;

 string leftStringToMakeIntoExpression;
  string rightStringToMakeIntoExpression;

  vector<Command*> vectorOfCommandsForWhileLoop;
  unordered_map<string, DefineVarCommand *> mapOfDefineVarCommands;

//  Parser parser_for_while_loop;


 public:


// defualt constructer
  WhileCommand();

  //constructer by parameters
  WhileCommand(vector<Command*>,string,string,string,unordered_map<string, DefineVarCommand *>);
  // WhileCommand(list<Command>,Expression*, bool,string);
  // WhileCommand(list<Command>,bool,Expression*,string);
//  WhileCommand(list<Command>,DefineVarCommand,double ,string);



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

};

#endif //FLIGHTSIM_WHILECOMMAND_H