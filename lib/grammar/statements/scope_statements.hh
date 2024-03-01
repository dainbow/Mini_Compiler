#pragma once

#include "statement.hh"
#include "statements_list.hh"

class ScopeStatements : public Statement {
public:
  explicit ScopeStatements(StatementsList* list);
  void Accept(Visitor* visitor) override;

  StatementsList* statements_;
};