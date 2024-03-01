#include "scope_statements.hh"

ScopeStatements::ScopeStatements(StatementsList* list) : statements_(list) {}

void ScopeStatements::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
