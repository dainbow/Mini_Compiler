#include "number_expression.hh"

NumberExpression::NumberExpression(int value) : value_(value) {}

void NumberExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}