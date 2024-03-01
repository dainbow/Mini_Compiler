#pragma once

#include "expression.hh"

class AddExpression : public Expression {
 public:
  AddExpression(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor);

  Expression* first_;
  Expression* second_;
};
