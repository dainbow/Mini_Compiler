#include "l_log.hh"

LLogic::LLogic(Expression* e1, Expression* e2) : first_(e1), second_(e2) {}

void LLogic::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
