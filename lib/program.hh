#pragma once

#include "statements/statements_list.hh"

class Program {
 public:
    Program(StatementsList* actions);
  StatementsList* statements_;
};
