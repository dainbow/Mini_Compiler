#include "func_type.hh"

FuncType::FuncType(Function* function) : function_(function) {}

size_t FuncType::GetArgsAmount() {
  return function_->params_list_->params_.size();
}

Type FuncType::GetType() {
  return Type::FuncType;
}

Function* FuncType::GetFunction() {
  return function_;
}
