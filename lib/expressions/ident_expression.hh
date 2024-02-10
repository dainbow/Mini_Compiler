#pragma once

#include <string>
#include "expression.hh"

class IdentExpression : public Expression {
 public:
  IdentExpression(const std::string& ident);
  void Accept(Visitor* visitor);

  std::string ident_;
};