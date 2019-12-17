//
// Created by shmuelsuna on 17/12/2019.
//

#ifndef FLIGHTSIM__EXPRESSION_H_
#define FLIGHTSIM__EXPRESSION_H_

class Expression {

 public:
  virtual double calculate() = 0;
  virtual ~Expression() {}
};

#endif //FLIGHTSIM__EXPRESSION_H_
