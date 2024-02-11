#pragma once

#include "statement.hh"

#include <string>

class DeclState : public Statement {
public:
  DeclState(const std::string& variable);
  void Accept(Visitor* visitor);

  std::string variable_;
};
