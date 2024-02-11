#pragma once

#include "../expressions/expression.hh"

class GeqLogic : public Expression {
public:
  GeqLogic(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor);

  Expression* first_;
  Expression* second_;
};
