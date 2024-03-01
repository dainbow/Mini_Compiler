#pragma once

#include <vector>
#include "base_element.hh"

class ExpressionsList : public BaseElement {
 public:
  ExpressionsList();
  explicit ExpressionsList(Expression* expression);

  void AddExpression(Expression* expression);
  void Accept(Visitor* visitor);

  std::vector<Expression*> expressions_;
};
