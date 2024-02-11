#pragma once

#include "../expressions/expression.hh"

class NeqLogic : public Expression {
public:
  NeqLogic(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor);

  Expression* first_;
  Expression* second_;
};
