//
// Created by shmuelsuna on 16/12/2019.
//

#ifndef FLIGHTSIM__PRINTCOMMAND_H_
#define FLIGHTSIM__PRINTCOMMAND_H_

#include "Command.h"
#include "DefineVarCommand.h"
#include "ex1.h"
class PrintCommand: public Command {
 private:

  string message;
  Expression* expression_;
  map<string,double>mapForInterpeter;
  bool isExpression;
  unordered_map<string, DefineVarCommand *>mapOfDefineVarCommands_;

 public:



  //Defualt Constructer
  PrintCommand();

  // Constructer with parameters
  PrintCommand(const string &message_);
  PrintCommand(const string &message_,unordered_map<string, DefineVarCommand *>,map<string,double>);
  PrintCommand(Expression*);




  //option 1
  void execute() override;

  //option 2
  // void execute()override ;
  bool checkIfNameOfADefineVarIsInString(string);

  void SetMapUpForInterpeter(string );
  unordered_map<string, DefineVarCommand *> GetMapOfDefineVarCommands();

};

#endif //FLIGHTSIM__PRINTCOMMAND_H_
