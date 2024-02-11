#pragma once

#include "../expressions/expression.hh"

class LeqLogic : public Expression {
public:
  LeqLogic(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor);

  Expression* first_;
  Expression* second_;
};
