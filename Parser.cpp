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

void Parser::setCommandVec(vector<Command*> vec) {
    this->command_vec = vec;
}

// create map1, and create vector of commands in the right order, so we can iterate over them for execution
unordered_map<string, Command *> Parser::action(vector<string> vectorOfStrings) {
  //for iteraterating over commands in the right order, so we can iterate over them for execution
  vector<Command *> vectorOfCommands;
  string arrow_;
  string sim_;

  MessageSim * messanger = new MessageSim;
  SymbolTable * symbolTable = new SymbolTable;// initialized with 36 values
  ServerValuesMap * serverValuesMap = new ServerValuesMap;


  //iterate over all vector of strings
  for (auto it = vectorOfStrings.begin(); it < vectorOfStrings.end(); ++it) {

    //OpenDataServer command
    if (*it == "openDataServer") {
      ++it;
      double digit = stod(*it);
      OpenDataServer* open_data_server = new OpenDataServer(serverValuesMap, digit);
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
      ConnectCommand* connect_command = new ConnectCommand(ip3, digit, messanger);
      mapOfCommands["ConnectCommand"] = (connect_command);
      vectorOfCommands.push_back(connect_command);
      continue;
    }
    //DefineVarCommand
    if (*it == "var") {
      ++it;
      string varName_ = *it;
      ++it;
      if (*it == "->" || (*it == "<-")) {
        if (*it == "->") {
          arrow_ = "->";
        } else {
          arrow_ = "<-";
        }
        ++it;
        if (*it == "sim") {
          ++it;
          sim_ = *it;
          SimulatorObject * simulatorObject = new SimulatorObject(varName_, sim_);
          if (arrow_ == "<-") {
              int index = symbolTable->isPathExist(sim_);
              serverValuesMap->insert(index, simulatorObject);
          }

          DefineVarCommand* define_var_command = new DefineVarCommand(varName_, arrow_, sim_, 0, simulatorObject);
          mapOfCommands[varName_] = (define_var_command);
          mapOfDefineVarCommands[varName_] = (define_var_command);
          //vectorOfCommands.push_back(&define_var_command);
          continue;
        }

      } else { // it== '='
        DefineVarCommand define_var_command(varName_, arrow_, sim_, 0);
        mapOfCommands[varName_] = (&define_var_command);
        mapOfDefineVarCommands[varName_] = (&define_var_command);
        it--;
        // vectorOfCommands.push_back(&define_var_command);

        //set var command
        while (true) {

          //get iterator over map of defineVarcommands and look for define var that needs to be set
          unordered_map<string, DefineVarCommand *>::iterator itOverMap = mapOfDefineVarCommands.find(*it);
          //
          if (itOverMap != mapOfDefineVarCommands.end()) {//found a var that needs to be set
            map<string, double> mapForInterpeter2;//for expressions
            string nameOfSetVarCommand = varName_;
            it += 2;
            //SetVarCommand set_var_command(itOverMap->second, *it, mapOfDefineVarCommands, mapForInterpeter2);
            //Interpreter *i2 = new Interpreter();
            //i2->setVariables(mapForInterpeter2);
            //Expression *e1 = i2->interpret(*it); //need to get from simulator value
            //set_var_command.GetDefine_var_command_ptr()->SetVarValue(e1->calculate()); //need to get from simulator value
            //mapOfCommands["SetVarCommand" + nameOfSetVarCommand] = (&set_var_command);
            //vectorOfCommands.push_back(set_var_command);
            break;
          }
          break;
        }
        continue;
      }
    }
    /*
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
     */
    //Sleep command
    if (*it == "Sleep") {
      ++it;
      int timeToSleep_ = stod(*it);
      SleepCommand * sleep_command = new SleepCommand(timeToSleep_);
      mapOfCommands["Sleep" + *it] = (sleep_command);
      vectorOfCommands.push_back(sleep_command);
      continue;
    }

    //set var command
    while (true) {
      //get iterator over map of defineVarcommands and look for define var that needs to be set
      unordered_map<string, DefineVarCommand *>::iterator itOverMap = mapOfDefineVarCommands.find(*it);
      if (itOverMap != mapOfDefineVarCommands.end()) {//found a var that needs to be set
        map<string, double> mapForInterpeter;

        string nameOfSetVarCommand = *it;
        it += 2;
        SetVarCommand* set_var_command = new SetVarCommand(itOverMap->second, *it, mapOfDefineVarCommands, mapForInterpeter, messanger);
        /*
        Interpreter *i2 = new Interpreter();
        i2->setVariables(mapForInterpeter);
        Expression *e1 = i2->interpret(*it);

        set_var_command.GetDefine_var_command_ptr()->SetVarValue(e1->calculate());
        double test1 = set_var_command.GetDefine_var_command_ptr()->GetVarValue(); //testtttttttt1
        double test2 = itOverMap->second->GetVarValue();  //testtttt2
         */

        //mapOfCommands["SetVarCommand" + nameOfSetVarCommand] = (&set_var_command);
        vectorOfCommands.push_back(set_var_command);
        //break;
      }
      break;
    }

/*
    //While command
    if (*it == "while") {
      string leftStringToMakeIntoExpression;
      string rightStringToMakeIntoExpression;
      string operator_;
      vector<Command *> vectorOfCommandsForWhileLoop;
      unordered_map<string, DefineVarCommand *> mapOfDefineVarCommandsForWhileLoop;

      ++it;
      while ((*it != "<") && (*it != "<=") && (*it != ">") && (*it != ">=") && (*it != "!=") && (*it != "==")) {
        leftStringToMakeIntoExpression += (*it);
        it++;
      }
      operator_ = *it;
      ++it;
      while (*it != "{") {
        rightStringToMakeIntoExpression += (*it);
        it++;
      }
      it++;

      while (*it != "}") {
        vector<string> vectorOfStringsForWhileLoop;


        //DefineVarCommand for whileCommand
        if (*it == "var") {
          ++it;
          string varName_ = *it;
          ++it;
          if (*it == "->" || (*it == "<-")) {
            if (*it == "->") {
              arrow_ = "->";
            } else {
              arrow_ = "<-";
            }
            ++it;
            if (*it == "sim") {
              ++it;
              sim_ = *it;
              DefineVarCommand define_var_command(varName_, arrow_, sim_, 0);
              // mapOfCommands[varName_] = (&define_var_command);
              mapOfDefineVarCommandsForWhileLoop[varName_] = (&define_var_command);
              // vectorOfCommands.push_back(&define_var_command);
              vectorOfCommandsForWhileLoop.push_back(&define_var_command);

              continue;

            }

          } else { // it== '='



            DefineVarCommand define_var_command(varName_, arrow_, sim_, 0);
            //  mapOfCommands[varName_] = (&define_var_command);
            mapOfDefineVarCommandsForWhileLoop[varName_] = (&define_var_command);

            vectorOfCommandsForWhileLoop.push_back(&define_var_command);




            // vectorOfCommands.push_back(&define_var_command);

            //set var command for whileCommand

            while (true) {
              unordered_map<string, DefineVarCommand *>::iterator itOverMap =
                  mapOfDefineVarCommandsForWhileLoop.find(*it);
              //
              if (itOverMap != mapOfDefineVarCommandsForWhileLoop.end()) {//found a var that needs to be set
                //temporary untill we do expressions
                //   DefineVarCommand* define_var_command_ptr = itOverMap->second;
                string nameOfSetVarCommand = *it;
                it += 2;
                map<string, double> mapForInterpeter2;

                SetVarCommand set_var_command(itOverMap->second, *it, mapOfDefineVarCommands, mapForInterpeter2);
                Interpreter *i2 = new Interpreter();
                i2->setVariables(mapForInterpeter2);
                Expression *e1 = i2->interpret(*it);

                set_var_command.GetDefine_var_command_ptr()->SetVarValue(e1->calculate());
                double test1 = set_var_command.GetDefine_var_command_ptr()->GetVarValue(); //testtttttttt1
                double test2 = itOverMap->second->GetVarValue();  //testtttt2

                vectorOfCommandsForWhileLoop.push_back(&set_var_command);
                break;
              }
              break;
            }
            continue;
          }

        }
















        // Print command
        if (*it == "Print") {
          ++it;
          string message_ = *it;
          PrintCommand print_command(message_);

          vectorOfCommandsForWhileLoop.push_back(&print_command);
          ++it;
          continue;
        }
        //Sleep command
        if (*it == "Sleep") {
          ++it;

          int timeToSleep_ = stod(*it);
          SleepCommand sleep_command(timeToSleep_);
          vectorOfCommandsForWhileLoop.push_back(&sleep_command);
          ++it;//
          continue;
        }
        //set var command for while loop

        while (true) {
          unordered_map<string, DefineVarCommand *>::iterator itOverMap = mapOfDefineVarCommands.find(*it);
          //
          if (itOverMap != mapOfDefineVarCommands.end()) {//found a var that needs to be set

            string nameOfSetVarCommand = *it;
            it += 2;

            map<string, double> mapForInterpeter;
            SetVarCommand set_var_command(itOverMap->second, *it, mapOfDefineVarCommands, mapForInterpeter);
            Interpreter *i2 = new Interpreter();
            i2->setVariables(mapForInterpeter);
              Expression *e1 = i2->interpret(*it); // rpm needs to get value from sim

               set_var_command.GetDefine_var_command_ptr()->SetVarValue(e1->calculate());//  rpm needs to get value from sim

            vectorOfCommandsForWhileLoop.push_back(&set_var_command);
            it++;
            //break;
          }
          break;
        }

      }
      WhileCommand while_command( vectorOfCommandsForWhileLoop, leftStringToMakeIntoExpression,
          operator_,rightStringToMakeIntoExpression, mapOfDefineVarCommandsForWhileLoop);

      mapOfCommands["While"+while_command.GetLeftStringToMakeIntoExpression()
      +while_command.GetAnOperator()+while_command.GetRightStringToMakeIntoExpression()] = (&while_command);
      vectorOfCommands.push_back(&while_command);
      continue;

    }//end of whilecommand





*/



    //condition command


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
    vector<Command*>::iterator it = this->command_vec.begin();
    Command* temp = *it;


    thread t1(&Command::execute, temp);
    cout<<"in parser befor sleep server"<<endl;
    this_thread::sleep_for(40s);
    cout<<"in parser after sleep server"<<endl;

    /*
    unique_lock <mutex> ul1(m);
    cv.wait(ul1, []{ return isServerConnect;});
     */

    it++;

    temp = *it;

    thread t2(&Command::execute, temp);
    it++;

    for (; it < this->command_vec.end(); it++) {
        Command* temp = *it;
        temp->execute();
    }




    t2.join();
    t1.join();

}



