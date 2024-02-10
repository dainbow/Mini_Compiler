#pragma once

#include "visitor.hh"

#include <fstream>
#include <string>

class Printer : public Visitor {
 public:
  Printer(const std::string& filename);
  ~Printer();

  virtual void Visit(Program* program) override;
  virtual void Visit(StatementsList* program) override;
  virtual void Visit(AssignState* assignment) override;
  virtual void Visit(IfState* ifState) override;
  virtual void Visit(PrintState* printState) override;
  virtual void Visit(WhileState* whileState) override;

  virtual void Visit(AddExpression* addExpr) override;
  virtual void Visit(NumberExpression* numExpr) override;
  virtual void Visit(NegExpression* negExpr) override;
  virtual void Visit(MulExpression* mulExpr) override;
  virtual void Visit(IdentExpression* identExpr) override;
  virtual void Visit(DivExpression* divExpr) override;

 private:
  void PrintTabs();
  std::ofstream stream_;
  int num_tabs_ = 0;
};