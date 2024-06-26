#include "ident_expression.hh"

IdentExpression::IdentExpression(const std::string& ident) : ident_(ident) {}

void IdentExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
