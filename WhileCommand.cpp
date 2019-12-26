//
// Created by shmuelsuna on 21/12/2019.
//

#include "WhileCommand.h"

// defualt constructer
WhileCommand::WhileCommand() {

}

//constructer by parameters
WhileCommand::WhileCommand(vector<Command *> vectorOfCommands,
                           string leftStringToMakeIntoExpression_,
                           string op,
                           string rightStringToMakeIntoExpression_,
                           unordered_map<string, DefineVarCommand *> mapOfDefineVarCommands1) {
  this->vectorOfCommandsForWhileLoop = vectorOfCommands;
  this->leftStringToMakeIntoExpression = leftStringToMakeIntoExpression_;
  this->operator_ = op;
  this->rightStringToMakeIntoExpression = rightStringToMakeIntoExpression_;
  this->mapOfDefineVarCommands = mapOfDefineVarCommands1;

}

void WhileCommand::execute() {
    this->SetUpExpressions();
    if (operator_ == "<") {
    while (this->GetLeftExpression()->calculate() < this->GetRightExpression()->calculate()) {

      for (auto it3 = vectorOfCommandsForWhileLoop.begin(); it3 != vectorOfCommandsForWhileLoop.end(); ++it3) {
        this->SetUpExpressions();
        Command *command = *it3;
        command->execute();
      }
    }
  }

  if (operator_ == "<=") {
      while (this->GetLeftExpression()->calculate() <= this->GetRightExpression()->calculate()) {

      for (auto it3 = vectorOfCommandsForWhileLoop.begin(); it3 != vectorOfCommandsForWhileLoop.end(); ++it3) {
        this->SetUpExpressions();
        Command *command = *it3;
        command->execute();
      }
    }
  }

  if (operator_ == ">") {
    while (this->GetLeftExpression()->calculate() > this->GetRightExpression()->calculate()) {

      for (auto it3 = vectorOfCommandsForWhileLoop.begin(); it3 != vectorOfCommandsForWhileLoop.end(); ++it3) {
        this->SetUpExpressions();
        Command *command = *it3;
        command->execute();
      }
    }
  }

  if (operator_ == ">=") {
    while (this->GetLeftExpression()->calculate() >= this->GetRightExpression()->calculate()) {

      for (auto it3 = vectorOfCommandsForWhileLoop.begin(); it3 != vectorOfCommandsForWhileLoop.end(); ++it3) {
        this->SetUpExpressions();
        Command *command = *it3;
        command->execute();
      }
    }
  }

  if (operator_ == "!=") {
    while (this->GetLeftExpression()->calculate() != this->GetRightExpression()->calculate()) {

      for (auto it3 = vectorOfCommandsForWhileLoop.begin(); it3 != vectorOfCommandsForWhileLoop.end(); ++it3) {
        this->SetUpExpressions();
        Command *command = *it3;
        command->execute();
      }
    }
  }

  if(operator_ == "==") {
    while (this->GetLeftExpression()->calculate() == this->GetRightExpression()->calculate()) {

      for (auto it3 = vectorOfCommandsForWhileLoop.begin(); it3 != vectorOfCommandsForWhileLoop.end(); ++it3){
        this->SetUpExpressions();
        Command * command = *it3;
        command->execute();
      }
    }
  }

}

bool WhileCommand::checkIfNameOfADefineVarIsInString(string str) {

  //check in map of defineVarcommands if there is a substring in the string to equals
  unordered_map<string,DefineVarCommand*> temp_map = this->mapOfDefineVarCommands;
    unordered_map<string,DefineVarCommand*>::iterator it = temp_map.begin();
  for (; it != temp_map.end(); ++it) {
    if (str.find(it->first) != string::npos) {
      return true;
    }
  }
  return false;
}

map<string, double> WhileCommand::SetMapUpForInterpeter(string str) {
  map<string, double> mapForInterpeter;



  if (this->checkIfNameOfADefineVarIsInString(str)) {//there is a define var in the string
      unordered_map<string,DefineVarCommand*> temp_map = this->mapOfDefineVarCommands;
      unordered_map<string,DefineVarCommand*>::iterator it = temp_map.begin();
    for ( ; it != temp_map.end(); ++it) {
      if (str.find(it->first) != string::npos) {
        mapForInterpeter[it->first] = it->second->GetVarValue();
      }
    }
  }
  return mapForInterpeter;

}

Expression *WhileCommand::createLeftExpression(map<string, double> MapForInterpeter) {
  Interpreter *i2 = new Interpreter();
  i2->setVariables(MapForInterpeter);
  Expression *e1 = i2->interpret(this->leftStringToMakeIntoExpression);

}

Expression *WhileCommand::createRightExpression(map<string, double> MapForInterpeter) {
  Interpreter *i3 = new Interpreter();
  i3->setVariables(MapForInterpeter);
  Expression *e2 = i3->interpret(this->rightStringToMakeIntoExpression);

}

const string &WhileCommand::GetAnOperator() const {
  return operator_;
}
const string &WhileCommand::GetLeftStringToMakeIntoExpression() const {
  return leftStringToMakeIntoExpression;
}
const string &WhileCommand::GetRightStringToMakeIntoExpression() const {
  return rightStringToMakeIntoExpression;
}
unordered_map<string, DefineVarCommand *> WhileCommand::GetMapOfDefineVarCommands() {
  return this->mapOfDefineVarCommands;
}

void WhileCommand::SetUpExpressions() {
  map<string, double> mapForInterpeter_LeftString;
  map<string, double> mapForInterpeter_RightString;

  mapForInterpeter_LeftString = this->SetMapUpForInterpeter(this->leftStringToMakeIntoExpression);
  Expression *expression_left = this->createLeftExpression(mapForInterpeter_LeftString);

  mapForInterpeter_RightString = this->SetMapUpForInterpeter(this->rightStringToMakeIntoExpression);
  Expression *expression_right = this->createRightExpression(mapForInterpeter_RightString);

  this->SetLeftExpression(expression_left);
  this->SetRightExpression(expression_right);

}

void WhileCommand::SetRightExpression(Expression *right_expression) {
  Right_expression_ = right_expression;
}
void WhileCommand::SetLeftExpression(Expression *left_expression) {
  Left_expression_ = left_expression;
}
Expression *WhileCommand::GetRightExpression() const {
  return Right_expression_;
}
Expression *WhileCommand::GetLeftExpression() const {
  return Left_expression_;
}
int WhileCommand::GetCounterForHowMuchIteratorShouldJump() {
  return counterForHowMuchIteratorShouldJump;
}
void WhileCommand::SetCounterForHowMuchIteratorShouldJump(int counter_for_how_much_iterator_should_jump) {
  counterForHowMuchIteratorShouldJump = counter_for_how_much_iterator_should_jump;
}
