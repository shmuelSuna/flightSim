//
// Created by shmuelsuna on 06/11/2019.
//


#include "ex1.h"





Variable::Variable(string name1, double value1) {
  name = name1;
  value = value1;
}
Variable &Variable::operator++() {
  this->value += 1;
  return *this;

}

Variable &Variable::operator--() {
  this->value -= 1;
  //return Variable(this->name, this->value);
  return (*this);
}

Variable &Variable::operator+=(double temp1) {

  this->value += temp1;
  return (*this);

}

Variable &Variable::operator-=(double temp2) {
  this->value -= temp2;

  return (*this);
}

Variable &Variable::operator++(int temp3) {
  if (temp3 == 0) {
    this->value += 1;
    return *this;
  }
  this->value += 1;
  return *this;

}
Variable &Variable::operator--(int temp4) {
  this->value -= temp4;
  return (*this);

}

double Variable::calculate() {
  return this->value;
}

Variable::~Variable() {

}

///////////
/*
Value::Value(double value1) {
  this->value = value1;
}
 */
Value::Value(const double value1) : value(value1) {}

double Value::calculate() {
  return this->value;
}

Value::~Value() {

}


////


BinaryOperator::~BinaryOperator() {
  delete(left);
  delete(right);
}
//////

//constructer
Plus::Plus(Expression *left1, Expression *right1) {
  this->left = left1;
  this->right = right1;
}
double Plus::calculate() {
  return this->left->calculate() + this->right->calculate();
}
//destructer
//~Plus(){}

//////////

//constructer
Minus::Minus(Expression *left1, Expression *right1) {
  this->left = left1;
  this->right = right1;
}
double Minus::calculate() {
  return this->left->calculate() - this->right->calculate();
}
//destructer
//~Minus(){}

//////////

//constructer
Mul::Mul(Expression *left1, Expression *right1) {
  this->left = left1;
  this->right = right1;
}
double Mul::calculate() {
  return this->left->calculate() * this->right->calculate();
}
//destructer
//~Mul(){}

//////////

//constructer
Div::Div(Expression *left1, Expression *right1) {
  this->left = left1;
  this->right = right1;
}
double Div::calculate() {
  if (this->right->calculate() == 0) {
    throw "division by zero";
  }
  return this->left->calculate() / this->right->calculate();
}
//destructer
//~Div(){}


UnaryOperator::~UnaryOperator() {
  delete expression;
}


///////////

UPlus::UPlus(Expression *expression1) {
  this->expression = expression1;
}
double UPlus::calculate() {
  return this->expression->calculate();
}
/////////

UMinus::UMinus(Expression *expression1) {
  this->expression = expression1;
}
double UMinus::calculate() {
  return (this->expression->calculate()) * -1;
}



//////////////////////////////////////////////////////////////////////

string Interpreter::changeInfix(const string &infix) const {
  string endString;
  int numOpenBracets = 0;
  int numcloseBracets = 0;

  //check if infix string is empty
  if(infix.length()<1) {
    throw "no string";
  }



  // check string for execeptions
  for (unsigned int k = 0; k < infix.length(); k++) {
    if (isOperator(&infix[k]) && isOperator(&infix[k + 1])) {
      throw "illegal math expression";
    }


    //checking if first char is ). or last char is open bracet. or last one is operator- which is not legal
    if (infix[0] == ')' || infix[infix.length() - 1] == '(' || isOperator(&infix[infix.length() - 1])) {
      throw "not legal string";
    }

    //checking same number of bracets
    if (infix[k] == '(') {
      ++numOpenBracets;
    }
    if (infix[k] == ')') {
      ++numcloseBracets;
    }
  }

  if (numOpenBracets != numcloseBracets) {
    throw "not same amount of opening and closing bracets";
  }

  for (int i = 0; i < (signed) infix.length(); ++i) {

    if (i == 0) {
      if (infix[0] == '-') {
        endString += "~";
        continue;
      }
      if (infix[0] == '+') {
        endString += "~";
        continue;
      }
    }

    if (infix[i - 1] == '(' && infix[i] == '-') {
      endString += "~";
      continue;
    }
    if (infix[i - 1] == '(' && infix[i] == '+') {
      endString += "$";
      continue;
    }

    endString += infix[i];
  }
  return endString;
}

vector<string> Interpreter::infixToReversePolish(const string &infix) const {
  queue<string> q;
  stack<string> s;
  vector<string> tempV;


  string changedInfix = changeInfix(infix);

  for (unsigned int i = 0; i < infix.size(); i++) {
    string s7;
    bool flag = false;

    //check if in the stirng-infix its a number(digit)
    if (TryParse(&changedInfix[i])) {
      int j = i + 1;
      while (TryParse(&changedInfix[j]) || changedInfix[j] == '.') {

        j++;
      }
      string s1 = changedInfix.substr(i, j - i);
      tempV.push_back(s1);
      i = j - 1;
      continue;
    } else if (changedInfix[i] == '(') {
      s.push("(");
      continue;
    } else if (changedInfix[i] == ')') {
      while (!s.empty() && s.top() != "(") {
        tempV.push_back(s.top());
        s.pop();
      }
      s.pop();
      continue;
    }

    if (isOperator(&changedInfix[i]) == true) {
      while (!s.empty() && Priority(s.top()) >= Priority(&changedInfix[i])) {
        //  q.push(s.top());
        tempV.push_back(s.top());
        s.pop();
      }
      string s1 = changedInfix.substr(i, 1);
      s.push(s1);
      continue;
    } else {

      //check if its a variavle
      while (isOperator(&changedInfix[i]) != true && changedInfix[i] != ')' && changedInfix[i] != '(') {

        string s4 = changedInfix.substr(i, 1);
        s7 += s4;
        i++;
      }
      for (std::map<string, double>::const_iterator it2 = m.begin(); it2 != m.end(); ++it2) {

        if (s7 == it2->first) {
          --i;
          tempV.push_back(s7);
          flag = true;
        }
      }
      //if there is no var from map that matches var we got
      if (!flag) {
        throw "no variable found that matches from set variables";
      }

    }

  }
  //pop any remaining operators from the stack and insert to vector
  while (!s.empty()) {
    //   q.push((s.top()));

    if (s.top() == "(" || s.top() == ")") {
      s.pop();
    }
    tempV.push_back(s.top());
    s.pop();
  }

  return tempV;
}

bool Interpreter::TryParse(const string &symbol) const {
  bool isNumber = false;

  if (!isdigit(symbol[0])) {
    isNumber = false;
  } else {
    isNumber = true;
  }
  // }
  return isNumber;
}
int Interpreter::Priority(const string &c) const {

  if (((c[0] == '~') || (c[0] == '$'))) {
    return 4;
  }

  if (c[0] == '^') {
    return 3;
  }
  if (c[0] == '*' || c[0] == '/') {
    return 2;
  }
  if (c[0] == '+' || c[0] == '-') {
    return 1;
  } else {
    return 0;
  }
}
bool Interpreter::isOperator(const string &c) const {

  return (c[0] == '+' || c[0] == '-' || c[0] == '*' || c[0] == '/' || c[0] == '^' || c[0] == '~' || c[0] == '$');
}

Expression *Interpreter::PostfixToExpression(const vector<string> &v) const {
  stack<Expression *> s2;


  //going over the vector of strings
  for (auto it = v.cbegin(); it != v.cend(); ++it) {
    //check if string in the vector is a number
    if (TryParse(*it)) {
      double digit = stod(*it);
      Expression *expression = new Value(digit);
      s2.push(expression);
      continue;
    }
//check if string in the vector is a variable
    for (std::map<string, double>::const_iterator it2 = m.begin(); it2 != m.end(); ++it2) {
      if (*it == it2->first) {
        Expression *expression = new Variable(it2->first, it2->second);
        s2.push(expression);
        continue;
      }
      continue;
    }

    if (isOperator(*it)) {

      //check for $
      if (*it == "$") {

        Expression *expression1 = s2.top();
        Expression *expression2 = new UPlus(expression1);
        s2.push(expression2);
        continue;
      }

      //check for ~
      if (*it == "~") {

        Expression *expression1 = s2.top();
        s2.pop();
        Expression *expression2 = new UMinus(expression1);
        s2.push(expression2);
        continue;
      }

      if (*it == "-") {

        Expression *rightExpression = s2.top();
        s2.pop();
        Expression *leftExpression = s2.top();
        s2.pop();

        Expression *expression1 = new Minus(leftExpression, rightExpression);
        s2.push(expression1);
        continue;
      }
      if (*it == "+") {

        Expression *rightExpression = s2.top();
        s2.pop();
        Expression *leftExpression = s2.top();
        s2.pop();

        Expression *expression1 = new Plus(leftExpression, rightExpression);
        s2.push(expression1);
        continue;
      }
      if (*it == "*") {
        Expression *rightExpression = s2.top();
        s2.pop();
        Expression *leftExpression = s2.top();
        s2.pop();

        Expression *expression1 = new Mul(leftExpression, rightExpression);
        s2.push(expression1);
        continue;
      }
      if (*it == "/") {
        Expression *rightExpression = s2.top();
        s2.pop();
        Expression *leftExpression = s2.top();
        s2.pop();

        Expression *expression1 = new Div(leftExpression, rightExpression);
        s2.push(expression1);
        continue;
      }

    }
  }

  Expression *finalExpression = s2.top();

  return finalExpression;

}

void Interpreter::setVariables( map<string,double> mapForSetVars) {
this->m = mapForSetVars;
}







Expression *Interpreter::interpret(const string &s) {
  vectorTokens = infixToReversePolish(s);
  Expression *expression3 = PostfixToExpression(vectorTokens);
  return expression3;
}



