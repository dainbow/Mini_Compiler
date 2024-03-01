#include "div_expression.hh"

DivExpression::DivExpression(Expression* e1, Expression* e2)
    : first_(e1), second_(e2) {}

void DivExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}