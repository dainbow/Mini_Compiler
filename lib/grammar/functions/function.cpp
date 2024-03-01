#include "function.hh"

Function::Function(const std::string& name, ParamsList* params_list,
                   ScopeStatements* statements)
    : name_(name), params_list_(params_list), statements_(statements) {}

void Function::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
