#include "neq_log.hh"

NeqLogic::NeqLogic(Expression* e1, Expression* e2) : first_(e1), second_(e2) {}

void NeqLogic::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
