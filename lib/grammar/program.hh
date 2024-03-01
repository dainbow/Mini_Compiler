#pragma once

#include "functions/functions_list.hh"

class Program {
 public:
  Program(FunctionsList* functions);
  FunctionsList* functions_;
};
