//
// Created by shmuelsuna on 19/12/2019.
//

#ifndef FLIGHTSIM__CONDTIONPARSERCOMMAND_H_
#define FLIGHTSIM__CONDTIONPARSERCOMMAND_H_

#include <list>
#include "Command.h"
class CondtionParserCommand : public Command {
 private:

 protected:
  list<Command> listOfCommands;

};

#endif //FLIGHTSIM__CONDTIONPARSERCOMMAND_H_
