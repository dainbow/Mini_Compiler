#include "statements_list.hh"

void StatementsList::AddStatement(Statement* statement) {
  statements_.push_back(statement); 
}

void StatementsList::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
