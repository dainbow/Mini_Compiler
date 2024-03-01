#pragma once

#include <string>
#include "expression.hh"

class CallExpression : public Expression {
 public:
  CallExpression(const std::string& name, ExpressionsList* params_list);
  void Accept(Visitor* visitor);

  std::string name_;
  ExpressionsList* params_list_;
};
