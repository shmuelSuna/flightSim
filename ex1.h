//
// Created by shmuelsuna on 06/11/2019.
//

#ifndef EX1_H
#define EX1_H

#include <stack>

#include <vector>
#include <queue>
#include <map>


using namespace std;

class Expression {

 public:
  virtual double calculate() = 0;
  virtual ~Expression() {}
};

class Variable: public Expression
{
 private:
  string name;
  double value;
 public:
  //constructer
  Variable(string name, double value);

  Variable& operator++();
  Variable& operator--();
  Variable& operator+=(double temp1);
  Variable& operator-=(double temp2);
  Variable& operator++(int temp3);
  Variable& operator--(int temp4);

  double calculate();
  ~Variable();

};

class Value: public Expression {
 private:
  const double value;
  //double value;
 public:
  //constructer
  //  Value(double value1);
  Value(const double value);
  double calculate();
  ~Value();
};

class BinaryOperator: public Expression
{
 protected:
  Expression *right;
  Expression *left;
 public:
  //constructer
  //  BinaryOperator(Expression *left, Expression *right);
  //destructer
  ~BinaryOperator();
};



class Plus: public  BinaryOperator{
 public:
  //constructer
  Plus(Expression *left,Expression *right);
  double calculate() override ;
  //destructer

};

class Minus: public  BinaryOperator{
 public:
  //constructer
  Minus(Expression *left,Expression *right);
  double calculate() override ;
  //destructer

};



class Mul: public  BinaryOperator{
 public:
//constructer
  Mul(Expression *left,Expression *right);
  double calculate() override ;
//destructer

};



class Div: public  BinaryOperator{
 public:
//constructer
  Div(Expression *left,Expression *right);
  double calculate() override ;
//destructer

};


class UnaryOperator: public Expression
{
 protected:
  Expression *expression;

 public:
  ~UnaryOperator();
};

class UPlus: public  UnaryOperator
{
 public:
  //constructer
  UPlus(Expression *expression1);
  double calculate() override ;
};

class UMinus: public  UnaryOperator
{
 public:
  //constructer
  UMinus(Expression *expression1);
  double calculate() override ;
};


class Interpreter
{
 private:

  map<string,double>m;
  vector<string> vectorTokens;
 public:

  string changeInfix(const string &infix)const;
  bool TryParse(const string &symbol)const;
  int Priority(const string &c)const;
  bool isOperator(const string &c)const;
  vector<string> infixToReversePolish(const string &string2)const;
  Expression * PostfixToExpression(const vector<string> &vector)const;
  void setVariables( map<string,double>);
  Expression* interpret(const string &s);

};



#endif //EX1_H
