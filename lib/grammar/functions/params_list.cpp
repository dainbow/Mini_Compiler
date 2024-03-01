#include "params_list.hh"

#include <algorithm>
#include <stdexcept>

ParamsList::ParamsList() {}

ParamsList::ParamsList(const std::string& param) : params_{param} {}

void ParamsList::AddParam(const std::string& param) {
  if (std::find(params_.begin(), params_.end(), param) != params_.end()) {
    std::runtime_error("Param has been defined");
  }

  params_.push_back(param);
}

void ParamsList::Accept(Visitor* visitor) {
  visitor->Visit(this);
}