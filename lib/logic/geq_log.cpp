#include "geq_log.hh"

GeqLogic::GeqLogic(Expression* e1, Expression* e2) : first_(e1), second_(e2) {}

void GeqLogic::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
