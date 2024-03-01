#include "neg_expression.hh"

NegExpression::NegExpression(Expression* e) : first_(e) {}

void NegExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}