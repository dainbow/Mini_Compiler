#pragma once

#include "expression.hh"

class NegExpression : public Expression {
 public:
  NegExpression(Expression* e1);
  void Accept(Visitor* visitor);

  Expression* first_;
};
