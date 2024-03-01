#pragma once

#include "../expressions/expression.hh"
#include "statement.hh"

class IfState : public Statement {
 public:
  IfState(Expression* expression, Statement* condTrue, Statement* condFalse);
  void Accept(Visitor* visitor);

  Expression* expression_;

  Statement* condTrue_;
  Statement* condFalse_;
};
