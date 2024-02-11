#include "interpreter.hh"
#include <cassert>
#include <iostream>
#include "../elements.hh"

void Interpreter::Visit(Program* program) {
  variables_.clear();
  values_ = {};

  program->statements_->Accept(this);
}

void Interpreter::Visit(StatementsList* statements_list) {
  for (auto* state : statements_list->statements_) {
    state->Accept(this);
  }
}

void Interpreter::Visit(AssignState* assignment) {
  assignment->expression_->Accept(this);

  assert(variables_.find(assignment->variable_) != variables_.end());
  variables_[assignment->variable_] = Eval(assignment->expression_);
}

void Interpreter::Visit(IfState* ifState) {
  if (Eval(ifState->expression_)) {
    ifState->condTrue_->Accept(this);
  } else {
    ifState->condFalse_->Accept(this);
  }
}

void Interpreter::Visit(PrintState* printState) {
  std::cout << Eval(printState->expression_) << std::endl;
}

void Interpreter::Visit(WhileState* whileState) {
  while (Eval(whileState->expression_)) {
    whileState->cond_->Accept(this);
  }
}

void Interpreter::Visit(DeclState* declState) {
  variables_[declState->variable_] = 0;
}

void Interpreter::Visit(AddExpression* addExpr) {
  values_.push(Eval(addExpr->first_) + Eval(addExpr->second_));
}

void Interpreter::Visit(NumberExpression* numExpr) {
  values_.push(numExpr->value_);
}

void Interpreter::Visit(NegExpression* negExpr) {
  values_.push(-Eval(negExpr->first_));
}

void Interpreter::Visit(MulExpression* mulExpr) {
  values_.push(Eval(mulExpr->first_) * Eval(mulExpr->second_));
}

void Interpreter::Visit(IdentExpression* identExpr) {
  values_.push(variables_[identExpr->ident_]);
}

void Interpreter::Visit(DivExpression* divExpr) {
  values_.push(Eval(divExpr->first_) * Eval(divExpr->second_));
}

void Interpreter::Visit(LLogic* log) {
  values_.push(Eval(log->first_) < Eval(log->second_));
}
void Interpreter::Visit(GLogic* log) {
  values_.push(Eval(log->first_) > Eval(log->second_));
}
void Interpreter::Visit(LeqLogic* log) {
  values_.push(Eval(log->first_) <= Eval(log->second_));
}
void Interpreter::Visit(GeqLogic* log) {
  values_.push(Eval(log->first_) >= Eval(log->second_));
}
void Interpreter::Visit(EqLogic* log) {
  values_.push(Eval(log->first_) == Eval(log->second_));
}
void Interpreter::Visit(NeqLogic* log) {
  values_.push(Eval(log->first_) != Eval(log->second_));
}

int Interpreter::Eval(Expression* expr) {
  expr->Accept(this);

  assert(!values_.empty());
  auto val = values_.top();
  values_.pop();

  return val;
}
