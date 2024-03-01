#pragma once

#include "expression.hh"

class DivExpression : public Expression {
 public:
  DivExpression(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor);

  Expression* first_;
  Expression* second_;
};