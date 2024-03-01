#pragma once

#include "symbol_table/scope_layer.hh"
#include "visitor.hh"

class SymbolTree : public Visitor {
 public:
  SymbolTree();
  ~SymbolTree() = default;

  virtual void Visit(Program* program) override;
  virtual void Visit(StatementsList* program) override;
  virtual void Visit(ScopeStatements* scope) override;
  virtual void Visit(AssignState* assignment) override;
  virtual void Visit(IfState* ifState) override;
  virtual void Visit(PrintState* printState) override;
  virtual void Visit(ReturnState* returnState) override;
  virtual void Visit(WhileState* whileState) override;
  virtual void Visit(DeclState* declState) override;

  virtual void Visit(Function* function) override;
  virtual void Visit(FunctionsList* function_list) override;
  virtual void Visit(ParamsList* value_list) override;
  virtual void Visit(ExpressionsList* param_list) override;

  virtual void Visit(AddExpression* addExpr) override;
  virtual void Visit(NumberExpression* numExpr) override;
  virtual void Visit(NegExpression* negExpr) override;
  virtual void Visit(CallExpression* calling) override;
  virtual void Visit(MulExpression* mulExpr) override;
  virtual void Visit(IdentExpression* identExpr) override;
  virtual void Visit(DivExpression* divExpr) override;

  virtual void Visit(LLogic* log) override;
  virtual void Visit(GLogic* log) override;
  virtual void Visit(LeqLogic* log) override;
  virtual void Visit(GeqLogic* log) override;
  virtual void Visit(EqLogic* log) override;
  virtual void Visit(NeqLogic* log) override;

  ScopeLayer* GetRoot();

 private:
  ScopeLayer* root_;
  ScopeLayer* current_layer_;
};
