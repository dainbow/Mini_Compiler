#pragma once

#include <string>
#include <vector>
#include "base_element.hh"

class ParamsList : public BaseElement {
 public:
  ParamsList();
  explicit ParamsList(const std::string& param);
  void AddParam(const std::string& param);

  void Accept(Visitor* visitor);

  std::vector<std::string> params_;
};
