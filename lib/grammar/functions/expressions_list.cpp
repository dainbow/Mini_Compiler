#include "expressions_list.hh"

ExpressionsList::ExpressionsList() {}

ExpressionsList::ExpressionsList(Expression* expression)
    : expressions_{expression} {}

void ExpressionsList::AddExpression(Expression* expression) {
  expressions_.push_back(expression);
}

void ExpressionsList::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
