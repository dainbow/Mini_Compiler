#pragma once

#include "../expressions/expression.hh"
#include "statement.hh"

class WhileState : public Statement {
 public:
  WhileState(Expression* expression, Statement* cond);
  void Accept(Visitor* visitor);

  Expression* expression_;
  Statement* cond_;
};