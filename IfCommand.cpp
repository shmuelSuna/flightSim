//
// Created by shmuelsuna on 21/12/2019.
//

#include "IfCommand.h"// defualt constructer
IfCommand::IfCommand() {

}

//constructer by parameters
IfCommand::IfCommand(vector<Command *> vectorOfCommands,
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

void IfCommand::execute() {
  this->SetUpExpressions();
  if (operator_ == "<") {
    if (this->GetLeftExpression()->calculate() < this->GetRightExpression()->calculate()) {

      for (auto it3 = vectorOfCommandsForWhileLoop.begin(); it3 != vectorOfCommandsForWhileLoop.end(); ++it3) {
        this->SetUpExpressions();
        Command *command = *it3;
        command->execute();
      }
    }
  }

  if (operator_ == "<=") {
    cout<<"in while command"<<endl;
    if (this->GetLeftExpression()->calculate() <= this->GetRightExpression()->calculate()) {

      for (auto it3 = vectorOfCommandsForWhileLoop.begin(); it3 != vectorOfCommandsForWhileLoop.end(); ++it3) {
        this->SetUpExpressions();
        Command *command = *it3;
        command->execute();
      }
    }
  }

  if (operator_ == ">") {
    if (this->GetLeftExpression()->calculate() > this->GetRightExpression()->calculate()) {

      for (auto it3 = vectorOfCommandsForWhileLoop.begin(); it3 != vectorOfCommandsForWhileLoop.end(); ++it3) {
        this->SetUpExpressions();
        Command *command = *it3;
        command->execute();
      }
    }
  }

  if (operator_ == ">=") {
    if (this->GetLeftExpression()->calculate() >= this->GetRightExpression()->calculate()) {

      for (auto it3 = vectorOfCommandsForWhileLoop.begin(); it3 != vectorOfCommandsForWhileLoop.end(); ++it3) {
        this->SetUpExpressions();
        Command *command = *it3;
        command->execute();
      }
    }
  }

  if (operator_ == "!=") {
    if (this->GetLeftExpression()->calculate() != this->GetRightExpression()->calculate()) {

      for (auto it3 = vectorOfCommandsForWhileLoop.begin(); it3 != vectorOfCommandsForWhileLoop.end(); ++it3) {
        this->SetUpExpressions();
        Command *command = *it3;
        command->execute();
      }
    }
  }

  if(operator_ == "==") {
    if (this->GetLeftExpression()->calculate() == this->GetRightExpression()->calculate()) {

      for (auto it3 = vectorOfCommandsForWhileLoop.begin(); it3 != vectorOfCommandsForWhileLoop.end(); ++it3){
        this->SetUpExpressions();
        Command * command = *it3;
        command->execute();
      }
    }
  }

}

bool IfCommand::checkIfNameOfADefineVarIsInString(string str) {

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

map<string, double> IfCommand::SetMapUpForInterpeter(string str) {
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

Expression *IfCommand::createLeftExpression(map<string, double> MapForInterpeter) {
  Interpreter *i2 = new Interpreter();
  i2->setVariables(MapForInterpeter);
  Expression *e1 = i2->interpret(this->leftStringToMakeIntoExpression);

}

Expression *IfCommand::createRightExpression(map<string, double> MapForInterpeter) {
  Interpreter *i3 = new Interpreter();
  i3->setVariables(MapForInterpeter);
  Expression *e2 = i3->interpret(this->rightStringToMakeIntoExpression);

}

const string &IfCommand::GetAnOperator() const {
  return operator_;
}
const string &IfCommand::GetLeftStringToMakeIntoExpression() const {
  return leftStringToMakeIntoExpression;
}
const string &IfCommand::GetRightStringToMakeIntoExpression() const {
  return rightStringToMakeIntoExpression;
}
unordered_map<string, DefineVarCommand *> IfCommand::GetMapOfDefineVarCommands() {
  return this->mapOfDefineVarCommands;
}

void IfCommand::SetUpExpressions() {
  map<string, double> mapForInterpeter_LeftString;
  map<string, double> mapForInterpeter_RightString;

  mapForInterpeter_LeftString = this->SetMapUpForInterpeter(this->leftStringToMakeIntoExpression);
  Expression *expression_left = this->createLeftExpression(mapForInterpeter_LeftString);

  mapForInterpeter_RightString = this->SetMapUpForInterpeter(this->rightStringToMakeIntoExpression);
  Expression *expression_right = this->createRightExpression(mapForInterpeter_RightString);

  this->SetLeftExpression(expression_left);
  this->SetRightExpression(expression_right);

}

void IfCommand::SetRightExpression(Expression *right_expression) {
  Right_expression_ = right_expression;
}
void IfCommand::SetLeftExpression(Expression *left_expression) {
  Left_expression_ = left_expression;
}
Expression *IfCommand::GetRightExpression() const {
  return Right_expression_;
}
Expression *IfCommand::GetLeftExpression() const {
  return Left_expression_;
}
int IfCommand::GetCounterForHowMuchIteratorShouldJump() {
  return counterForHowMuchIteratorShouldJump;
}
void IfCommand::SetCounterForHowMuchIteratorShouldJump(int counter_for_how_much_iterator_should_jump) {
  counterForHowMuchIteratorShouldJump = counter_for_how_much_iterator_should_jump;
}
