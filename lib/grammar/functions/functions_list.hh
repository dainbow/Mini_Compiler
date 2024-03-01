#pragma once

#include <vector>
#include "function.hh"

class FunctionsList : public BaseElement {
 public:
  FunctionsList();
  void AddFunction(Function* function);

  void Accept(Visitor* visitor) override;

  std::vector<Function*> functions_;
};
