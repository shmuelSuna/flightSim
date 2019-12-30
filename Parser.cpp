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
  this->mapTest = serverValuesMap;


  //iterate over all vector of strings
  for (auto it = vectorOfStrings.begin(); it < vectorOfStrings.end(); ++it) {

    //OpenDataServer command
    if (*it == "openDataServer") {
      ++it;
      //double digit = stod(*it);
      Expression *expression_of_open_data_server = GetExpressionFromString(*it);
      OpenDataServer
          *open_data_server = new OpenDataServer(serverValuesMap, expression_of_open_data_server->calculate());
      mapOfCommands["OpenDataServer"] = (open_data_server);
      vectorOfCommands.push_back(open_data_server);
      continue;
    }

    //Connenct control client command
    if (*it == "connectControlClient") {
      ++it;
      string ip3 = *it;
      ++it;
      //double digit = stod(*it);
      Expression *expression_of_connect = GetExpressionFromString(*it);
      ConnectCommand *connect_command = new ConnectCommand(ip3, expression_of_connect->calculate(), messanger);
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

        it += 4;
      } else {
        mapOfDefineVarCommands[temp_define_var_command->GetVarName()] = (temp_define_var_command);
        it += 3;
      }
      vectorOfCommands.push_back(temp_define_var_command);

      continue;
    }

    //set var command
    if (checkIfIteratorIsUpTooSetVarCommand(it)) {
      SetVarCommand *set_var_command = createSetVarCommand(it, messanger);
      mapOfCommands["SetVarCommand" + set_var_command->GetDefine_var_command_ptr()->GetVarName()] = (set_var_command);
      vectorOfCommands.push_back(set_var_command);
     it+=2;
      continue;
    }
    // Print command
    if (*it == "Print") {
      PrintCommand *print_command;
      Expression *expression_for_print_command;
      map<string,double> mapForInterpeter_;
      ++it;
      string message_ = *it;

      if (message_[0] != '"') {
/*
      unordered_map<string, DefineVarCommand *> temp_map_of_definevarcommand = GetMapOfDefineVarCommands();
      unordered_map<string, DefineVarCommand *>::iterator itOverMap = temp_map_of_definevarcommand.begin();
      for (itOverMap;itOverMap!= temp_map_of_definevarcommand.end();itOverMap++) {
          //found one define var command \ expression in string
          expression_for_print_command = GetExpressionFromString(message_);
          print_command = new PrintCommand(expression_for_print_command);
          mapOfCommands["Print" + message_] = (print_command);
          vectorOfCommands.push_back(print_command);
         break;
*/
        print_command = new PrintCommand(message_,GetMapOfDefineVarCommands(),mapForInterpeter_);
        mapOfCommands["Print" + message_] = (print_command);
        vectorOfCommands.push_back(print_command);
        break;

      } else {
            //did not find a deifneVarVariable in print message
            print_command = new PrintCommand(message_);
            mapOfCommands["Print" + *it] = (print_command);
            vectorOfCommands.push_back(print_command);
        }
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
      WhileCommand *while_command = createWhileCommand_ptr(it, symbolTable, serverValuesMap, messanger);

      mapOfCommands["While" + while_command->GetLeftStringToMakeIntoExpression()
          + while_command->GetAnOperator() + while_command->GetRightStringToMakeIntoExpression()] = (while_command);
      vectorOfCommands.push_back(while_command);

      it += while_command->GetCounterForHowMuchIteratorShouldJump();
      continue;
    }
    //IfCommand
    if (*it == "if") {
      IfCommand *if_command = createIfCommand_ptr(it, symbolTable, serverValuesMap, messanger);

      mapOfCommands["if" + if_command->GetLeftStringToMakeIntoExpression()
          + if_command->GetAnOperator() + if_command->GetRightStringToMakeIntoExpression()] = (if_command);
      vectorOfCommands.push_back(if_command);

      it += if_command->GetCounterForHowMuchIteratorShouldJump();
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
  unordered_map<string, DefineVarCommand *> temp_map_of_definevarcommand = GetMapOfDefineVarCommands();

  unordered_map<string, DefineVarCommand *>::iterator itOverMap = temp_map_of_definevarcommand.begin();
    while (itOverMap!= temp_map_of_definevarcommand.end()){
      string itOverMapfirst =itOverMap->first;
      if (str.find(itOverMapfirst) != string::npos) {
        return true;
      }
      itOverMap++;
    }
  return false;
}

map<string, double> Parser::SetMapUpForInterpeter(string str) {
  map<string, double> mapForInterpeter;

unordered_map<string, DefineVarCommand *> temp_map_of_definevarcommand = GetMapOfDefineVarCommands();
unordered_map<string, DefineVarCommand *>::iterator itOverMap = temp_map_of_definevarcommand.begin();
  if (this->checkIfNameOfADefineVarIsInString(str)) {//there is a define var in the string
    for (; itOverMap != GetMapOfDefineVarCommands().end();
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
  return expression_;
}

void Parser::operateCommands() {

  vector<Command *>::iterator it = this->command_vec.begin();

  for (; it < this->command_vec.end(); it++) {
    Command *temp = *it;
    temp->execute();
  }

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
  ++it;
  SimulatorObject *temp = mapOfDefineVarCommands[*it]->getSimObj();
  DefineVarCommand *define_var_command = new DefineVarCommand(varName_, "", "", 0, temp);
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
SetVarCommand *Parser::createSetVarCommand(vector<string>::iterator it, MessageSim *ms) {
  string nameOfSetVarCommand = *it;
  unordered_map<string, DefineVarCommand *>::iterator itOverMap = mapOfDefineVarCommands.find(*it);
  it += 2;
  map<string, double> mapForInterpeter2;//for expressions

  SetVarCommand *set_var_command =
      new SetVarCommand(itOverMap->second, *it, mapOfDefineVarCommands, mapForInterpeter2);
  set_var_command->setMessanger(ms);
  return set_var_command;

}

WhileCommand *Parser::createWhileCommand_ptr(vector<string>::iterator it,
                                             SymbolTable *symbol_table,
                                             ServerValuesMap *server_values_map,
                                             MessageSim *ms) {

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
        counter += 4;
      } else {
        mapOfDefineVarCommandsForWhileLoop[temp_define_var_command->GetVarName()] = (temp_define_var_command);
        it += 3;
        counter += 3;
      }
      it++;
      counter++;
    }
    //set var command for while loop
    if (checkIfIteratorIsUpTooSetVarCommand(it)) {
      SetVarCommand *set_var_command = createSetVarCommand(it, ms);
      // mapOfDefineVarCommandsForWhileLoop["SetVarCommand" + set_var_command->GetDefine_var_command_ptr()->GetVarName()] = (set_var_command);
      vectorOfCommandsForWhileLoop.push_back(set_var_command);
      it += 3;
      counter += 3;
    }
    // Print command fow while loop NEW
    if (*it == "Print") {
      PrintCommand *print_command;
      Expression *expression_for_print_command;
      map<string,double> mapForInterpeter_;
      ++it;
      string message_ = *it;

        if (message_[0] != '"') {
/*
            unordered_map<string, DefineVarCommand *> temp_map_of_definevarcommand = GetMapOfDefineVarCommands();
            unordered_map<string, DefineVarCommand *>::iterator itOverMap = temp_map_of_definevarcommand.begin();
            for (itOverMap;itOverMap!= temp_map_of_definevarcommand.end();itOverMap++) {
                //found one define var command \ expression in string
                expression_for_print_command = GetExpressionFromString(message_);
                print_command = new PrintCommand(expression_for_print_command);
                mapOfCommands["Print" + message_] = (print_command);
                vectorOfCommandsForWhileLoop.push_back(print_command);
                break;
            }
*/
          print_command = new PrintCommand(message_,GetMapOfDefineVarCommands(),mapForInterpeter_);
          mapOfCommands["Print" + message_] = (print_command);
          vectorOfCommandsForWhileLoop.push_back(print_command);
          break;
        } else {
            //did not find a deifneVarVariable in print message
            print_command = new PrintCommand(message_);
            mapOfCommands["Print" + *it] = (print_command);
            vectorOfCommandsForWhileLoop.push_back(print_command);
        }
        ++it;
        continue;
    }


    //Sleep command for while loop
    if (*it == "Sleep") {
      ++it;
      counter++;
      int timeToSleep_ = stod(*it);
      SleepCommand *sleep_command = new SleepCommand(timeToSleep_);
      //  mapOfCommands["Sleep" + *it] = (sleep_command);
      vectorOfCommandsForWhileLoop.push_back(sleep_command);
      it++;
      counter++;
      continue;
    }
  }
  //NOTICE CHANGE I PUT THE MAP OF THE DEFINE VAR OF THE PARSER AND NOT OF THE CREATEWHILE
  WhileCommand *while_command = new WhileCommand(vectorOfCommandsForWhileLoop,
                                                 leftStringToMakeIntoExpression,
                                                 operator_,
                                                 rightStringToMakeIntoExpression,
                                                 this->mapOfDefineVarCommands);

  while_command->SetCounterForHowMuchIteratorShouldJump(counter);
  return while_command;

}

IfCommand *Parser::createIfCommand_ptr(vector<string>::iterator it,
                                       SymbolTable *symbol_table, ServerValuesMap *server_values_map, MessageSim *ms) {

  string leftStringToMakeIntoExpression;
  string rightStringToMakeIntoExpression;
  string operator_;
  vector<Command *> vectorOfCommandsForIfCommand;
  unordered_map<string, DefineVarCommand *> mapOfDefineVarCommandsForIfCommand;
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



    //DefineVarCommand for IfCommand
    if (*it == "var") {
      DefineVarCommand *temp_define_var_command = createDefineVarCommand_ptr(it, symbol_table, server_values_map);
      //check where to put the defineVarCommandPtr
      if (temp_define_var_command->IsHasArrow()) {
        mapOfDefineVarCommandsForIfCommand[temp_define_var_command->GetVarName()] = (temp_define_var_command);
        vectorOfCommandsForIfCommand.push_back(temp_define_var_command);
        it += 4;
        counter += 4;
      } else {
        mapOfDefineVarCommandsForIfCommand[temp_define_var_command->GetVarName()] = (temp_define_var_command);
        it += 3;
        counter += 3;
      }
      it++;
      counter++;
    }
    //set var command for IfCommand
    if (checkIfIteratorIsUpTooSetVarCommand(it)) {
      SetVarCommand *set_var_command = createSetVarCommand(it, ms);

      vectorOfCommandsForIfCommand.push_back(set_var_command);
      it += 3;
      counter += 3;
    }
    // Print command for IF NEW
    if (*it == "Print") {
      PrintCommand *print_command;
      Expression *expression_for_print_command;
      map <string, double>mapForInterpeter_;
      ++it;
      string message_ = *it;
      //check if print message is a defineVarVarible for example: Print(rpm)
      //unordered_map<string, DefineVarCommand *>::iterator itOverMap = mapOfDefineVarCommands.find(*it);
      //  if (itOverMap != mapOfDefineVarCommands.end()) {//found a defneVarVariable in print message
      // string s = to_string(itOverMap->second->GetVarValue());
      // print_command = new PrintCommand(itOverMap->second);
        if (message_[0] != '"') {
/*
            unordered_map<string, DefineVarCommand *> temp_map_of_definevarcommand = GetMapOfDefineVarCommands();
            unordered_map<string, DefineVarCommand *>::iterator itOverMap = temp_map_of_definevarcommand.begin();
            for (itOverMap;itOverMap!= temp_map_of_definevarcommand.end();itOverMap++) {
                //found one define var command \ expression in string
                expression_for_print_command = GetExpressionFromString(message_);
                print_command = new PrintCommand(expression_for_print_command);
                mapOfCommands["Print" + message_] = (print_command);
                vectorOfCommandsForIfCommand.push_back(print_command);
                break;
            }
*/



          print_command = new PrintCommand(message_,GetMapOfDefineVarCommands(),mapForInterpeter_);
          mapOfCommands["Print" + message_] = (print_command);
          vectorOfCommandsForIfCommand.push_back(print_command);
          break;
        } else {
            //did not find a deifneVarVariable in print message
            print_command = new PrintCommand(message_);
            mapOfCommands["Print" + *it] = (print_command);
            vectorOfCommandsForIfCommand.push_back(print_command);
        }
        ++it;
        continue;
    }

    //Sleep command for while loop
    if (*it == "Sleep") {
      ++it;
      counter++;
      int timeToSleep_ = stod(*it);
      SleepCommand *sleep_command = new SleepCommand(timeToSleep_);
      //  mapOfCommands["Sleep" + *it] = (sleep_command);
      vectorOfCommandsForIfCommand.push_back(sleep_command);
      it++;
      counter++;
      continue;
    }
  }
  //NOTICE CHANGE I PUT THE MAP OF THE DEFINE VAR OF THE PARSER AND NOT OF THE CREATEWHILE
  IfCommand *if_command = new IfCommand(vectorOfCommandsForIfCommand,
                                        leftStringToMakeIntoExpression,
                                        operator_,
                                        rightStringToMakeIntoExpression,
                                        this->mapOfDefineVarCommands);

  if_command->SetCounterForHowMuchIteratorShouldJump(counter);
  return if_command;

}