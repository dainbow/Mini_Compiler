#include "printer.hh"

#include "elements.hh"

#include <iostream>

Printer::Printer(const std::string& filename) : stream_(filename) {}

Printer::~Printer() {
  stream_.close();
}

void Printer::Visit(Program* program) {
  stream_ << "Program:" << std::endl;

  ++num_tabs_;
  program->functions_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(StatementsList* statements_list) {
  for (auto* state : statements_list->statements_) {
    ++num_tabs_;
    state->Accept(this);
    --num_tabs_;
    stream_ << ";" << std::endl;
  }
}

void Printer::Visit(ScopeStatements* scope) {
  stream_ << "ScopeStatements:" << std::endl;

  ++num_tabs_;
  scope->statements_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(AssignState* assignment) {
  PrintTabs();
  stream_ << "Assignment: " << assignment->variable_ << std::endl;
  ++num_tabs_;
  assignment->expression_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(IfState* ifState) {
  PrintTabs();
  stream_ << "If: " << std::endl;
  ++num_tabs_;
  ifState->expression_->Accept(this);
  --num_tabs_;

  stream_ << "Then: " << std::endl;
  ++num_tabs_;
  ifState->condTrue_->Accept(this);
  --num_tabs_;

  stream_ << "Else: " << std::endl;
  ++num_tabs_;
  ifState->condFalse_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(PrintState* printState) {
  PrintTabs();
  stream_ << "Print: " << std::endl;
  ++num_tabs_;
  printState->expression_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(InputState* input_state) {
  PrintTabs();
  stream_ << "Input: " << input_state->var_name_ << std::endl;
}

void Printer::Visit(ReturnState* returnState) {
  PrintTabs();
  stream_ << "ReturnStatement:" << std::endl;

  ++num_tabs_;
  returnState->return_expression_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(WhileState* whileState) {
  PrintTabs();
  stream_ << "While: " << std::endl;
  ++num_tabs_;
  whileState->expression_->Accept(this);
  --num_tabs_;

  stream_ << "Then: " << std::endl;
  ++num_tabs_;
  whileState->cond_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(DeclState* declState) {
  PrintTabs();
  stream_ << "Declare " << declState->variable_ << std::endl;
}

void Printer::Visit(Function* function) {
  PrintTabs();
  stream_ << "Function:" << std::endl;

  ++num_tabs_;

  PrintTabs();
  stream_ << "Name: " << function->name_ << std::endl;
  function->params_list_->Accept(this);
  function->statements_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(FunctionsList* function_list) {
  PrintTabs();
  stream_ << "FunctionList:" << std::endl;

  ++num_tabs_;
  for (auto* function : function_list->functions_) {
    function->Accept(this);
  }
  --num_tabs_;
}

void Printer::Visit(ParamsList* value_list) {
  PrintTabs();
  stream_ << "ParamList:" << std::endl;

  ++num_tabs_;

  for (const std::string& param : value_list->params_) {
    PrintTabs();
    stream_ << param << std::endl;
  }
  --num_tabs_;
}

void Printer::Visit(ExpressionsList* param_list) {
  PrintTabs();
  stream_ << "ParamValueList:" << std::endl;

  ++num_tabs_;

  for (Expression* param : param_list->expressions_) {
    param->Accept(this);
  }
  --num_tabs_;
}

void Printer::Visit(AddExpression* addExpr) {
  PrintTabs();
  stream_ << "AddExpression is:" << std::endl;

  ++num_tabs_;
  addExpr->first_->Accept(this);
  addExpr->second_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(NumberExpression* numExpr) {
  PrintTabs();
  stream_ << "NumExpression " << numExpr->value_ << std::endl;
}

void Printer::Visit(NegExpression* negExpr) {
  PrintTabs();
  stream_ << "NegExpression is:" << std::endl;

  ++num_tabs_;
  negExpr->first_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(CallExpression* calling) {
  PrintTabs();
  stream_ << "CallStatement:" << std::endl;
  ++num_tabs_;

  PrintTabs();
  stream_ << "Name: " << calling->name_ << std::endl;
  calling->params_list_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(MulExpression* mulExpr) {
  PrintTabs();
  stream_ << "MulExpression is:" << std::endl;

  ++num_tabs_;
  mulExpr->first_->Accept(this);
  mulExpr->second_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(IdentExpression* identExpr) {
  PrintTabs();
  stream_ << "IdentExpression " << identExpr->ident_ << std::endl;
}

void Printer::Visit(DivExpression* divExpr) {
  PrintTabs();
  stream_ << "DivExpression is:" << std::endl;

  ++num_tabs_;
  divExpr->first_->Accept(this);
  divExpr->second_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(LLogic* log) {
  PrintTabs();
  stream_ << "LessLogic is:" << std::endl;

  ++num_tabs_;
  log->first_->Accept(this);
  log->second_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(GLogic* log) {
  PrintTabs();
  stream_ << "GreaterLogic is:" << std::endl;

  ++num_tabs_;
  log->first_->Accept(this);
  log->second_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(LeqLogic* log) {
  PrintTabs();
  stream_ << "LessEqLogic is:" << std::endl;

  ++num_tabs_;
  log->first_->Accept(this);
  log->second_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(GeqLogic* log) {
  PrintTabs();
  stream_ << "GreaterEqLogic is:" << std::endl;

  ++num_tabs_;
  log->first_->Accept(this);
  log->second_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(EqLogic* log) {
  PrintTabs();
  stream_ << "EqualLogic is:" << std::endl;

  ++num_tabs_;
  log->first_->Accept(this);
  log->second_->Accept(this);
  --num_tabs_;
}

void Printer::Visit(NeqLogic* log) {
  PrintTabs();
  stream_ << "NonEqualLogic is:" << std::endl;

  ++num_tabs_;
  log->first_->Accept(this);
  log->second_->Accept(this);
  --num_tabs_;
}

void Printer::PrintTabs() {
  stream_ << std::string(num_tabs_, '\t');
}
