#include "driver.hh"
#include "parser.hh"

#include "visitors/interpreter.hh"
#include "visitors/printer.hh"
#include "visitors/symbol_tree.hh"

Driver::Driver()
    : trace_parsing(false),
      trace_scanning(false),
      scanner(*this),
      parser(scanner, *this) {}

int Driver::parse(const std::string& f) {
  file = f;
  location.initialize(&file);
  scan_begin();
  parser.set_debug_level(trace_parsing);
  int res = parser();
  std::cout << "parser " << res << std::endl;
  scan_end();
  return res;
}

void Driver::Evaluate() {
  SymbolTree visitor;
  visitor.Visit(program);

  ScopeLayer* root = visitor.GetRoot();
  Interpreter interpreter(root, {});
  interpreter.Visit(program);
}

void Driver::scan_begin() {
  scanner.set_debug(trace_scanning);
  if (file.empty() || file == "-") {
  } else {
    stream.open(file);
    std::cout << file << std::endl;
    scanner.yyrestart(&stream);
  }
}

void Driver::scan_end() {
  stream.close();
}

void Driver::PrintTree(const std::string& filename) {
  Printer visitor(filename);
  visitor.Visit(program);
}
