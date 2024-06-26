#pragma once

#include <fstream>
#include <string>
#include "parser.hh"
#include "scanner.h"

#include "program.hh"

class Driver {
 public:
  Driver();
  int result;
  int parse(const std::string& f);
  void Evaluate();
  
  void PrintIR(const std::string& filename);
  void PrintTree(const std::string& filename);
  std::string file;
  bool trace_parsing;

  void scan_begin();
  void scan_end();

  bool trace_scanning;
  yy::location location;

  friend class Scanner;
  Scanner scanner;
  yy::parser parser;
  Program* program;

 private:
  std::ifstream stream;
};
