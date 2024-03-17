#pragma once

#include "forwards.hh"

class Visitor {
 public:
  virtual void Visit(Program* program) = 0;
  virtual void Visit(StatementsList* program) = 0;
  virtual void Visit(ScopeStatements* scope) = 0;

  virtual void Visit(AssignState* assignment) = 0;
  virtual void Visit(DeclState* decl_state) = 0;
  virtual void Visit(IfState* if_state) = 0;
  virtual void Visit(PrintState* print_state) = 0;
  virtual void Visit(InputState* input_state) = 0;
  virtual void Visit(ReturnState* return_state) = 0;
  virtual void Visit(WhileState* while_state) = 0;

  virtual void Visit(Function* function) = 0;
  virtual void Visit(FunctionsList* function_list) = 0;
  virtual void Visit(ParamsList* value_list) = 0;
  virtual void Visit(ExpressionsList* param_list) = 0;

  virtual void Visit(AddExpression* add_expr) = 0;
  virtual void Visit(NumberExpression* num_expr) = 0;
  virtual void Visit(NegExpression* neg_expr) = 0;
  virtual void Visit(CallExpression* statement) = 0;
  virtual void Visit(MulExpression* mul_expr) = 0;
  virtual void Visit(IdentExpression* ident_expr) = 0;
  virtual void Visit(DivExpression* div_expr) = 0;

  virtual void Visit(LLogic* log) = 0;
  virtual void Visit(GLogic* log) = 0;
  virtual void Visit(LeqLogic* log) = 0;
  virtual void Visit(GeqLogic* log) = 0;
  virtual void Visit(EqLogic* log) = 0;
  virtual void Visit(NeqLogic* log) = 0;

  virtual ~Visitor() = default;
};
