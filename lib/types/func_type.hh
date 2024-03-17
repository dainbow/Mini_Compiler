#pragma once

#include <cstddef>

#include "functions/function.hh"
#include "type.hh"

class FuncType : public BasicType {
 public:
  explicit FuncType(Function* function);

  size_t GetArgsAmount();
  Function* GetFunction();

 private:
  Function* function_;
};
