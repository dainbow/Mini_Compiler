#include "add_expression.hh"

AddExpression::AddExpression(Expression* e1, Expression* e2)
    : first_(e1), second_(e2) {}

void AddExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}