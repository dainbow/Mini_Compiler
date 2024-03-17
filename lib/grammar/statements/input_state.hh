#pragma once

#include <string>
#include "../expressions/expression.hh"
#include "statement.hh"

class InputState : public Statement {
 public:
  InputState(const std::string& ident);
  void Accept(Visitor* visitor);

  std::string var_name_;
};
