//
// Created by shmuelsuna on 15/12/2019.
//

#include "Parser.h"

// Defualt Constructer
Parser::Parser() {}

//constructer by parameters
Parser::Parser(vector<string> vectorOfStrings1) {
  this->vectorOfStrings = vectorOfStrings1;
}

void Parser::setCommandVec(vector<Command *> vec) {
  this->command_vec = vec;
}

// create map1, and create vector of commands in the right order, so we can iterate over them for execution
unordered_map<string, Command *> Parser::action(vector<string> vectorOfStrings) {
  //for iteraterating over commands in the right order, so we can iterate over them for execution
  vector<Command *> vectorOfCommands;
  string arrow_;
  string sim_;

  MessageSim *messanger = new MessageSim;
  SymbolTable *symbolTable = new SymbolTable;// initialized with 36 values
  ServerValuesMap *serverValuesMap = new ServerValuesMap;


  //iterate over all vector of strings
  for (auto it = vectorOfStrings.begin(); it < vectorOfStrings.end(); ++it) {

    //OpenDataServer command
    if (*it == "openDataServer") {
      ++it;
      double digit = stod(*it);
      OpenDataServer *open_data_server = new OpenDataServer(serverValuesMap, digit);
      mapOfCommands["OpenDataServer"] = (open_data_server);
      vectorOfCommands.push_back(open_data_server);
      continue;
    }

    //Connenct control client command
    if (*it == "connectControlClient") {
      ++it;
      string ip3 = *it;
      ++it;
      double digit = stod(*it);
      ConnectCommand *connect_command = new ConnectCommand(ip3, digit, messanger);
      mapOfCommands["ConnectCommand"] = (connect_command);
      vectorOfCommands.push_back(connect_command);
      continue;
    }
    //DefineVarCommand
    if (*it == "var") {
      DefineVarCommand *temp_define_var_command = createDefineVarCommand_ptr(it, symbolTable, serverValuesMap);
      //check where to put the defineVarCommandPtr
      if (temp_define_var_command->IsHasArrow()) {
        mapOfCommands[temp_define_var_command->GetVarName()] = (temp_define_var_command);
        mapOfDefineVarCommands[temp_define_var_command->GetVarName()] = (temp_define_var_command);
        vectorOfCommands.push_back(temp_define_var_command);
        it += 4;
      } else {
        mapOfDefineVarCommands[temp_define_var_command->GetVarName()] = (temp_define_var_command);
        it += 3;
      }
      continue;
    }

    //set var command
    if (checkIfIteratorIsUpTooSetVarCommand(it)) {
      SetVarCommand *set_var_command = createSetVarCommand(it);
      mapOfCommands["SetVarCommand" + set_var_command->GetDefine_var_command_ptr()->GetVarName()] = (set_var_command);
      vectorOfCommands.push_back(set_var_command);
      it+=2;
      continue;
    }
    // Print command
    if (*it == "Print") {
      ++it;
      string message_ = *it;
      //check if print message is a defineVarVarible for example: Print(rpm)
      unordered_map<string, DefineVarCommand *>::iterator itOverMap = mapOfDefineVarCommands.find(*it);

      if (itOverMap != mapOfDefineVarCommands.end()) {//found a defneVarVariable in print message
        string s = to_string(itOverMap->second->GetVarValue());
        PrintCommand print_command(s);
        mapOfCommands["Print" + *it] = (&print_command);
        vectorOfCommands.push_back(&print_command);
        continue;
      }
      //did not find a deifneVarVariable in print message
      PrintCommand print_command(message_);
      mapOfCommands["Print" + *it] = (&print_command);
      vectorOfCommands.push_back(&print_command);
      continue;
    }

    //Sleep command
    if (*it == "Sleep") {
      ++it;
      int timeToSleep_ = stod(*it);
      SleepCommand *sleep_command = new SleepCommand(timeToSleep_);
      mapOfCommands["Sleep" + *it] = (sleep_command);
      vectorOfCommands.push_back(sleep_command);
      continue;
    }

    //While command
    if (*it == "while") {
      WhileCommand *while_command = createWhileCommand_ptr(it, symbolTable, serverValuesMap);

      mapOfCommands["While" + while_command->GetLeftStringToMakeIntoExpression()
          + while_command->GetAnOperator() + while_command->GetRightStringToMakeIntoExpression()] = (while_command);
      vectorOfCommands.push_back(while_command);
      continue;
    }

  }
  setCommandVec(vectorOfCommands);
  return this->GetMapOfCommands();
}

unordered_map<string, Command *> Parser::GetMapOfCommands() {
  return mapOfCommands;
}

bool Parser::checkIfNameOfADefineVarIsInString(string str) {

  //check in map of defineVarcommands if there is a substring in the string to equals
  for (auto itOverMap = GetMapOfDefineVarCommands().begin(); itOverMap != GetMapOfDefineVarCommands().end();
       ++itOverMap) {
    if (str.find(itOverMap->first) != string::npos) {
      return true;
    }
  }
  return false;
}

map<string, double> Parser::SetMapUpForInterpeter(string str) {
  map<string, double> mapForInterpeter;

  if (this->checkIfNameOfADefineVarIsInString(str)) {//there is a define var in the string
    for (auto itOverMap = GetMapOfDefineVarCommands().begin(); itOverMap != GetMapOfDefineVarCommands().end();
         ++itOverMap) {
      if (str.find(itOverMap->first) != string::npos) {
        mapForInterpeter[itOverMap->first] = itOverMap->second->GetVarValue();
      }
    }
  }
  return mapForInterpeter;

}

Expression *Parser::createExpression(map<string, double> MapForInterpeter, string str) {
  Interpreter *i3 = new Interpreter();
  i3->setVariables(MapForInterpeter);
  Expression *e2 = i3->interpret(str);

}

unordered_map<string, DefineVarCommand *> Parser::GetMapOfDefineVarCommands() {
  return this->mapOfDefineVarCommands;
}

Expression *Parser::GetExpressionFromString(string str) {
  map<string, double> mapForInterpeter;

  mapForInterpeter = this->SetMapUpForInterpeter(str);
  Expression *expression_ = this->createExpression(mapForInterpeter, str);

}

void Parser::operateCommands() {
  vector<Command *>::iterator it = this->command_vec.begin();
  Command *temp = *it;

  thread t1(&Command::execute, temp);
/*
    cout<<"in parser befor sleep server"<<endl;
    this_thread::sleep_for(40s);
    cout<<"in parser after sleep server"<<endl;
*/

  cv.wait(ul, [] { return isServerConnect; });

  it++;

  temp = *it;

  thread t2(&Command::execute, temp);
  it++;

  for (; it < this->command_vec.end(); it++) {
    Command *temp = *it;
    temp->execute();
  }

  t2.join();
  t1.join();

}

DefineVarCommand *Parser::createDefineVarCommand_ptr(vector<string>::iterator it,
                                                     SymbolTable *symbolTable,
                                                     ServerValuesMap *serverValuesMap) {
  string arrow_;
  string sim_;
  DefineVarCommand *temp_define_var_command_ptr;

  ++it;
  string varName_ = *it;
  ++it;
  if (*it == "->" || (*it == "<-")) { // define var that has arrow and sim
    temp_define_var_command_ptr =
        createDefineVarCommand_ptrThatHasArrowAndSim(it, symbolTable, serverValuesMap, varName_);
  } else {
    temp_define_var_command_ptr = createDefineVarCommand_ptrThatHas_NO_ArrowAndSim(it, varName_);
  }
  return temp_define_var_command_ptr;
}

DefineVarCommand *Parser::createDefineVarCommand_ptrThatHasArrowAndSim(vector<string>::iterator it,
                                                                       SymbolTable *symbolTable,
                                                                       ServerValuesMap *serverValuesMap,
                                                                       string varName_) {
  string arrow_;
  string sim_;
  DefineVarCommand *define_var_command;

  if (*it == "->") {
    arrow_ = "->";
  } else {
    arrow_ = "<-";
  }
  ++it;
  if (*it == "sim") {

    ++it;
    sim_ = *it;
    SimulatorObject *simulatorObject = new SimulatorObject(varName_, sim_);
    if (arrow_ == "<-") {
      int index = symbolTable->isPathExist(sim_);
      serverValuesMap->insert(index, simulatorObject);
    }

    define_var_command = new DefineVarCommand(varName_, arrow_, sim_, 0, simulatorObject);
    define_var_command->SetHasArrow(true);

  }
  return define_var_command;
}

DefineVarCommand *Parser::createDefineVarCommand_ptrThatHas_NO_ArrowAndSim
    (vector<string>::iterator it, string varName_) {
  DefineVarCommand *define_var_command = new DefineVarCommand(varName_, "", "", 0);
  define_var_command->SetHasArrow(false);

  // it--;//
  return define_var_command;

}

bool Parser::checkIfIteratorIsUpTooSetVarCommand(vector<string>::iterator it) {
  //get iterator over map of defineVarcommands and look for define var that needs to be set
  unordered_map<string, DefineVarCommand *>::iterator itOverMap = mapOfDefineVarCommands.find(*it);
  //
  if (itOverMap != mapOfDefineVarCommands.end()) {//found a var that needs to be set
    ++it;
    if (*it == "=") {
      return true;
    }
  }
  return false;

}
SetVarCommand *Parser::createSetVarCommand(vector<string>::iterator it) {
  string nameOfSetVarCommand = *it;
  unordered_map<string, DefineVarCommand *>::iterator itOverMap = mapOfDefineVarCommands.find(*it);
  it += 2;
  map<string, double> mapForInterpeter2;//for expressions

  SetVarCommand*set_var_command =
      new SetVarCommand(itOverMap->second, nameOfSetVarCommand, mapOfDefineVarCommands, mapForInterpeter2);
  return set_var_command;

}

/*
WhileCommand* Parser::createWhileCommand_ptr(vector<string>::iterator it,
    SymbolTable* symbol_table,ServerValuesMap* server_values_map) {

  string leftStringToMakeIntoExpression;
  string rightStringToMakeIntoExpression;
  string operator_;
  vector<Command *> vectorOfCommandsForWhileLoop;
  unordered_map<string, DefineVarCommand *> mapOfDefineVarCommandsForWhileLoop;
  int counter = 0;

  ++it;
  counter++;
  while ((*it != "<") && (*it != "<=") && (*it != ">") && (*it != ">=") && (*it != "!=") && (*it != "==")) {
    leftStringToMakeIntoExpression += (*it);
    it++;
    counter++;
  }
  operator_ = *it;
  ++it;
  counter++;
  while (*it != "{") {
    rightStringToMakeIntoExpression += (*it);
    it++;
    counter++;
  }
  it++;
  counter++;

  while (*it != "}") {



    //DefineVarCommand for whileCommand
    if (*it == "var") {
      DefineVarCommand *temp_define_var_command = createDefineVarCommand_ptr(it, symbol_table, server_values_map);
      //check where to put the defineVarCommandPtr
      if (temp_define_var_command->IsHasArrow()) {
        mapOfDefineVarCommandsForWhileLoop[temp_define_var_command->GetVarName()] = (temp_define_var_command);
        vectorOfCommandsForWhileLoop.push_back(temp_define_var_command);
        it += 4;
        counter+=4;
      } else {
        mapOfDefineVarCommandsForWhileLoop[temp_define_var_command->GetVarName()] = (temp_define_var_command);
        it += 3;
        counter+=3;
      }
      it++;
      counter++;
    }
    //set var command for while loop
    if (checkIfIteratorIsUpTooSetVarCommand(it)) {
      SetVarCommand *set_var_command = createSetVarCommand(it);
      // mapOfDefineVarCommandsForWhileLoop["SetVarCommand" + set_var_command->GetDefine_var_command_ptr()->GetVarName()] = (set_var_command);
      vectorOfCommandsForWhileLoop.push_back(set_var_command);
      it += 3;
      counter+=3;
    }

    // Print command for while loop
    if (*it == "Print") {
      ++it;
      counter++;
      string message_ = *it;
      //check if print message is a defineVarVarible for example: Print(rpm)
      unordered_map<string, DefineVarCommand *>::iterator itOverMap = mapOfDefineVarCommands.find(*it);

      if (itOverMap != mapOfDefineVarCommands.end()) {//found a defneVarVariable in print message
        string s = to_string(itOverMap->second->GetVarValue());
        PrintCommand print_command(s);
        // mapOfCommands["Print" + *it] = (&print_command);
        vectorOfCommandsForWhileLoop.push_back(&print_command);
        continue;
      }
      //did not find a deifneVarVariable in print message
      PrintCommand print_command(message_);
      // mapOfCommands["Print" + *it] = (&print_command);
      vectorOfCommandsForWhileLoop.push_back(&print_command);
      continue;
    }

    //Sleep command for while loop
    if (*it == "Sleep") {
      ++it;
      int timeToSleep_ = stod(*it);
      SleepCommand *sleep_command = new SleepCommand(timeToSleep_);
      //  mapOfCommands["Sleep" + *it] = (sleep_command);
      vectorOfCommandsForWhileLoop.push_back(sleep_command);
      continue;
    }
  }
    WhileCommand* while_command = new WhileCommand(vectorOfCommandsForWhileLoop, leftStringToMakeIntoExpression,operator_, rightStringToMakeIntoExpression, mapOfDefineVarCommandsForWhileLoop);

while_command->SetCounterForHowMuchIteratorShouldJump(counter);
 // return while_command;

  }
  */

