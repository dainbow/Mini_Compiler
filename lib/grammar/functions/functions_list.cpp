#include "functions_list.hh"

FunctionsList::FunctionsList() {}

void FunctionsList::AddFunction(Function* function) {
  functions_.push_back(function);
}

void FunctionsList::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
