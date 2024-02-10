#pragma once

#include "../expressions/expression.hh"
#include "statement.hh"

class WhileState : public Statement {
  WhileState(Expression* expression, StatementsList* cond);
  void Accept(Visitor* visitor);

  Expression* expression_;
  StatementsList* cond_;
};