#include "interpreter.hh"
#include <cassert>
#include <iostream>

#include "elements.hh"
#include "types/frame_idx_type.hh"

Interpreter::Interpreter(ScopeLayer* root, std::vector<int> params)
    : frame_(root),
      params_(std::move(params)),
      is_returned_(false),
      return_value_(0) {}

void Interpreter::Visit(Program*) {
  frame_.GetFunction("main")->Accept(this);
}

void Interpreter::Visit(StatementsList* statements_list) {
  for (auto* state : statements_list->statements_) {
    if (!is_returned_) {
      state->Accept(this);
    }
  }
}

void Interpreter::Visit(ScopeStatements* scope) {
  frame_.EnterScope(scope);

  scope->statements_->Accept(this);

  frame_.ExitScope();
}

void Interpreter::Visit(AssignState* assignment) {
  frame_.AssignValue(assignment->variable_, Eval(assignment->expression_));
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

void Interpreter::Visit(InputState* input_state) {
  int value = 0;
  std::cin >> value;

  frame_.AssignValue(input_state->var_name_, value);
}

void Interpreter::Visit(ReturnState* returnState) {
  last_value_ = Eval(returnState->return_expression_);

  return_value_ = last_value_;
  is_returned_ = true;
}

void Interpreter::Visit(WhileState* whileState) {
  while (Eval(whileState->expression_)) {
    whileState->cond_->Accept(this);
  }
}

void Interpreter::Visit(DeclState*) {}

void Interpreter::Visit(Function* function) {
  if (function->params_list_->params_.size() != params_.size()) {
    std::runtime_error("Bad params for calling this function");
  }

  frame_.EnterScope(function->statements_);
  size_t idx = 0;
  for (auto& param_name : function->params_list_->params_) {
    frame_.AssignValue(param_name, params_[idx++]);
  }

  function->statements_->Accept(this);
}

void Interpreter::Visit(FunctionsList*) {}

void Interpreter::Visit(ParamsList*) {}

void Interpreter::Visit(ExpressionsList*) {}

void Interpreter::Visit(AddExpression* addExpr) {
  last_value_ = Eval(addExpr->first_) + Eval(addExpr->second_);
}

void Interpreter::Visit(NumberExpression* numExpr) {
  last_value_ = numExpr->value_;
}

void Interpreter::Visit(NegExpression* negExpr) {
  last_value_ = -Eval(negExpr->first_);
}

void Interpreter::Visit(CallExpression* calling) {
  auto* func = frame_.GetFunction(calling->name_);

  std::vector<int> params;
  for (auto param : calling->params_list_->expressions_) {
    params.push_back(Eval(param));
  }

  Interpreter new_visitor(frame_.GetRoot(), std::move(params));
  new_visitor.Visit(func);

  last_value_ = new_visitor.return_value_;
}

void Interpreter::Visit(MulExpression* mulExpr) {
  last_value_ = Eval(mulExpr->first_) * Eval(mulExpr->second_);
}

void Interpreter::Visit(IdentExpression* identExpr) {
  last_value_ = frame_.GetValue(identExpr->ident_);
}

void Interpreter::Visit(DivExpression* divExpr) {
  last_value_ = Eval(divExpr->first_) / Eval(divExpr->second_);
}

void Interpreter::Visit(LLogic* log) {
  last_value_ = Eval(log->first_) < Eval(log->second_);
}
void Interpreter::Visit(GLogic* log) {
  last_value_ = Eval(log->first_) > Eval(log->second_);
}
void Interpreter::Visit(LeqLogic* log) {
  last_value_ = Eval(log->first_) <= Eval(log->second_);
}
void Interpreter::Visit(GeqLogic* log) {
  last_value_ = Eval(log->first_) >= Eval(log->second_);
}
void Interpreter::Visit(EqLogic* log) {
  last_value_ = Eval(log->first_) == Eval(log->second_);
}
void Interpreter::Visit(NeqLogic* log) {
  last_value_ = Eval(log->first_) != Eval(log->second_);
}
