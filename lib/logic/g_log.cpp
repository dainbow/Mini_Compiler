#include "g_log.hh"

GLogic::GLogic(Expression* e1, Expression* e2) : first_(e1), second_(e2) {}

void GLogic::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
