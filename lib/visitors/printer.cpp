#include "printer.hh"

#include "../elements.hh"

#include <iostream>

Printer::Printer(const std::string& filename) : stream_(filename) {}

void Printer::Visit(Program* program) {
  stream_ << "Program:" << std::endl;

  ++num_tabs_;
  program->statements_->Accept(this);
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
