#include "call_expression.hh"

CallExpression::CallExpression(const std::string& name,
                               ExpressionsList* params_list)
    : name_(name), params_list_(params_list) {}

void CallExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
