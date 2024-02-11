#pragma once

#include "../expressions/expression.hh"

class GLogic : public Expression {
public:
  GLogic(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor);

  Expression* first_;
  Expression* second_;
};
