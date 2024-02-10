#include "mul_expression.hh"

MulExpression::MulExpression(Expression* e1, Expression* e2)
    : first_(e1), second_(e2) {}

void MulExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}