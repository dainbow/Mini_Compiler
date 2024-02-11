#include "leq_log.hh"

LeqLogic::LeqLogic(Expression* e1, Expression* e2) : first_(e1), second_(e2) {}

void LeqLogic::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
