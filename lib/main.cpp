#include "driver.hh"
#include "llvm/Support/CommandLine.h"

using namespace llvm::cl;

opt<bool> TraceParsing("p", desc("Enable verbose parsing"), init(false));
opt<bool> TraceScanning("s", desc("Enable verbose scanning"), init(false));

opt<std::string> InputFilename(Positional, Required, desc("<input file>"));

opt<std::string> TreeDumpFilename("tree",
                                  desc("Name for file with AST tree dump"),
                                  value_desc("filename"), init(""));

opt<std::string> EmitLLVMFilename(
    "emit-llvm",
    desc("Specify if you want generate IR, otherwise interpretate"),
    value_desc("filename"), init(""));

int main(int argc, char** argv) {
  ParseCommandLineOptions(argc, argv);

  Driver driver;

  driver.trace_parsing = TraceParsing;
  driver.trace_scanning = TraceScanning;

  driver.parse(InputFilename);

  if (EmitLLVMFilename.empty()) {
    driver.Evaluate();
  } else {
    driver.PrintIR(EmitLLVMFilename);
  }

  if (!TreeDumpFilename.empty()) {
    driver.PrintTree(TreeDumpFilename);
  }
}
