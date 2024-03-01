#include "eq_log.hh"

EqLogic::EqLogic(Expression* e1, Expression* e2) : first_(e1), second_(e2) {}

void EqLogic::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
