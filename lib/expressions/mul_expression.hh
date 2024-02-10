#pragma once

#include "expression.hh"

class MulExpression : public Expression {
 public:
  MulExpression(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor);

  Expression* first_;
  Expression* second_;
};
