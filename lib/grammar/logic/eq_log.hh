#pragma once

#include "../expressions/expression.hh"

class EqLogic : public Expression {
public:
  EqLogic(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor);

  Expression* first_;
  Expression* second_;
};
