#pragma once

#include "../expressions/expression.hh"
#include "statement.hh"

#include <string>

class AssignState : public Statement {
public:
  AssignState(const std::string& variable, Expression* expression);
  void Accept(Visitor* visitor);

  std::string variable_;
  Expression* expression_;
};
