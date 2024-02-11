#pragma once

#include "../expressions/expression.hh"
#include "statement.hh"

class PrintState : public Statement {
public:
  PrintState(Expression* expression);
  void Accept(Visitor* visitor);

  Expression* expression_;
};