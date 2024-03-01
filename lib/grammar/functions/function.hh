#pragma once

#include "base_element.hh"
#include "params_list.hh"

#include <string>

class Function : public BaseElement {
 public:
  Function(const std::string& name, ParamsList* params_list,
           ScopeStatements* statements);
  void Accept(Visitor* visitor) override;

  std::string name_;
  ParamsList* params_list_;
  ScopeStatements* statements_;
};
