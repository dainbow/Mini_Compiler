#pragma once

#include "statement.hh"

class ReturnState : public Statement {
 public:
  explicit ReturnState(Expression* return_expression);
  void Accept(Visitor* visitor) override;

  Expression* return_expression_;
};
