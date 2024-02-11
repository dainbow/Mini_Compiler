#pragma once

#include "../expressions/expression.hh"
#include "statement.hh"
#include "statements_list.hh"

class IfState : public Statement {
public:
  IfState(Expression* expression, StatementsList* condTrue,
          StatementsList* condFalse);
  void Accept(Visitor* visitor);

  Expression* expression_;
  
  StatementsList* condTrue_;
  StatementsList* condFalse_;
};