#include "symbol_tree.hh"
#include "elements.hh"
#include "types/frame_idx_type.hh"
#include "types/func_type.hh"

SymbolTree::SymbolTree()
    : root_(new ScopeLayer()), current_layer_(root_), scope_sizes_() {}

void SymbolTree::Visit(Program* program) {
  program->functions_->Accept(this);
}

void SymbolTree::Visit(StatementsList* statements_list) {
  for (auto* state : statements_list->statements_) {
    state->Accept(this);
  }
}

void SymbolTree::Visit(ScopeStatements* scope) {
  current_layer_ = new ScopeLayer(current_layer_, scope);
  scope->statements_->Accept(this);
  current_layer_ = current_layer_->GetParent();
}

void SymbolTree::Visit(AssignState* assignment) {
  current_layer_->DynamicGet<FrameIdxType>(assignment->variable_);

  assignment->expression_->Accept(this);
}

void SymbolTree::Visit(IfState* ifState) {
  ifState->expression_->Accept(this);
  ifState->condTrue_->Accept(this);
  ifState->condFalse_->Accept(this);
}

void SymbolTree::Visit(PrintState* printState) {
  printState->expression_->Accept(this);
}

void SymbolTree::Visit(InputState* input_state) {
  current_layer_->DynamicGet<FrameIdxType>(input_state->var_name_);
}

void SymbolTree::Visit(ReturnState* returnState) {
  returnState->return_expression_->Accept(this);
}

void SymbolTree::Visit(WhileState* whileState) {
  whileState->expression_->Accept(this);
  whileState->cond_->Accept(this);
}

void SymbolTree::Visit(DeclState* declState) {
  DeclareVariable(declState->variable_);
}

void SymbolTree::Visit(Function* function) {
  DeclareFunction(function->name_, function);

  current_layer_ = new ScopeLayer(current_layer_, function->statements_);

  function->params_list_->Accept(this);
  function->statements_->statements_->Accept(this);

  current_layer_ = current_layer_->GetParent();
}

void SymbolTree::Visit(FunctionsList* function_list) {
  for (auto* function : function_list->functions_) {
    function->Accept(this);
  }
}

void SymbolTree::Visit(ParamsList* value_list) {
  for (auto& param : value_list->params_) {
    DeclareVariable(param);
  }
}

void SymbolTree::Visit(ExpressionsList* param_list) {
  for (auto* expression : param_list->expressions_) {
    expression->Accept(this);
  }
}

void SymbolTree::Visit(AddExpression* addExpr) {
  addExpr->first_->Accept(this);
  addExpr->second_->Accept(this);
}

void SymbolTree::Visit(NumberExpression*) {}

void SymbolTree::Visit(NegExpression* negExpr) {
  negExpr->first_->Accept(this);
}

void SymbolTree::Visit(CallExpression* calling) {
  // We don't check function name because function could be created after
  calling->params_list_->Accept(this);
}

void SymbolTree::Visit(MulExpression* mulExpr) {
  mulExpr->first_->Accept(this);
  mulExpr->second_->Accept(this);
}

void SymbolTree::Visit(IdentExpression* identExpr) {
  current_layer_->DynamicGet<FrameIdxType>(identExpr->ident_);
}

void SymbolTree::Visit(DivExpression* divExpr) {
  divExpr->first_->Accept(this);
  divExpr->second_->Accept(this);
}

void SymbolTree::Visit(LLogic* log) {
  log->first_->Accept(this);
  log->second_->Accept(this);
}

void SymbolTree::Visit(GLogic* log) {
  log->first_->Accept(this);
  log->second_->Accept(this);
}

void SymbolTree::Visit(LeqLogic* log) {
  log->first_->Accept(this);
  log->second_->Accept(this);
}

void SymbolTree::Visit(GeqLogic* log) {
  log->first_->Accept(this);
  log->second_->Accept(this);
}

void SymbolTree::Visit(EqLogic* log) {
  log->first_->Accept(this);
  log->second_->Accept(this);
}

void SymbolTree::Visit(NeqLogic* log) {
  log->first_->Accept(this);
  log->second_->Accept(this);
}

ScopeLayer* SymbolTree::GetRoot() {
  return root_;
}

void SymbolTree::DeclareVariable(Symbol symbol) {
  current_layer_->Declare(
      symbol, std::make_shared<FrameIdxType>(++scope_sizes_[current_layer_]));
}

void SymbolTree::DeclareFunction(Symbol symbol, Function* function) {
  current_layer_->Declare(symbol, std::make_shared<FuncType>(function));
}
