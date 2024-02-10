#pragma once
#include "expression.hh"

class NumberExpression : public Expression {
 public:
  explicit NumberExpression(int value);
  void Accept(Visitor* visit) override;

  int value_;
};
