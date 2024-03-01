#pragma once

#include "../expressions/expression.hh"

class LLogic : public Expression {
public:
  LLogic(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor);

  Expression* first_;
  Expression* second_;
};
