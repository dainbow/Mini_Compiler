#pragma once

#include <vector>

#include "statement.hh"

class StatementsList : public Statement {
public:
  void AddStatement(Statement* statement);
  void Accept(Visitor* visitor);

  std::vector<Statement*> statements_;
};