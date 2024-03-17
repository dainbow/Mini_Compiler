#include "ir_builder.hh"
#include "elements.hh"

#include "types/frame_idx_type.hh"

IrBuilderVisitor::IrBuilderVisitor(ScopeLayer* root, const std::string& output)
    : context_(),
      module_(),
      builder_(context_),
      current_function_(),
      frame_(root),
      output_file_(output) {}

void IrBuilderVisitor::Visit(Program* program) {
  module_ = new llvm::Module("top!", context_);

  program->functions_->Accept(this);

  std::error_code EC;
  llvm::raw_fd_ostream OS(output_file_, EC);

  module_->print(OS, nullptr);
}

void IrBuilderVisitor::Visit(StatementsList* statements_list) {
  for (auto* state : statements_list->statements_) {
    state->Accept(this);
  }
}

void IrBuilderVisitor::Visit(ScopeStatements* scope) {
  frame_.EnterScope(scope);

  scope->statements_->Accept(this);

  frame_.ExitScope();
}

void IrBuilderVisitor::Visit(AssignState* assignment) {
  builder_.CreateStore(Eval(assignment->expression_),
                       frame_.GetValue(assignment->variable_));
}

void IrBuilderVisitor::Visit(IfState* ifState) {
  static size_t if_counter = 0;

  auto* saved_block = builder_.GetInsertBlock();
  auto* true_block = llvm::BasicBlock::Create(
      context_, "Lif.true" + std::to_string(++if_counter), current_function_);
  builder_.SetInsertPoint(true_block);

  ifState->condTrue_->Accept(this);
  auto* saved_true_block = builder_.GetInsertBlock();

  auto* false_block = llvm::BasicBlock::Create(
      context_, "Lif.false" + std::to_string(if_counter), current_function_);
  builder_.SetInsertPoint(false_block);

  ifState->condFalse_->Accept(this);
  auto* saved_false_block = builder_.GetInsertBlock();

  auto* after_block = llvm::BasicBlock::Create(
      context_, "Lif.after" + std::to_string(if_counter), current_function_);

  builder_.SetInsertPoint(saved_block);
  builder_.CreateCondBr(Eval(ifState->expression_), true_block, false_block);

  builder_.SetInsertPoint(saved_true_block);
  builder_.CreateBr(after_block);

  builder_.SetInsertPoint(saved_false_block);
  builder_.CreateBr(after_block);

  builder_.SetInsertPoint(after_block);
}

void IrBuilderVisitor::Visit(PrintState* printState) {
  static auto* format = builder_.CreateGlobalStringPtr("%d\n");

  std::vector<llvm::Type*> print_args_types = {builder_.getInt8PtrTy(),
                                               builder_.getInt32Ty()};
  auto* printf_type =
      llvm::FunctionType::get(builder_.getInt32Ty(), print_args_types, false);
  auto callee = module_->getOrInsertFunction("printf", printf_type);

  std::vector<llvm::Value*> printf_args = {format,
                                           Eval(printState->expression_)};
  builder_.CreateCall(callee, printf_args);
}

void IrBuilderVisitor::Visit(InputState* input_state) {
  static auto* format = builder_.CreateGlobalStringPtr("%d");

  std::vector<llvm::Type*> input_args_types = {
      builder_.getInt8PtrTy(), builder_.getInt32Ty()->getPointerTo()};
  auto* scanf_type =
      llvm::FunctionType::get(builder_.getInt32Ty(), input_args_types, false);
  auto callee = module_->getOrInsertFunction("scanf", scanf_type);

  std::vector<llvm::Value*> scanf_args = {
      format, frame_.GetValue(input_state->var_name_)};
  builder_.CreateCall(callee, scanf_args);
}

void IrBuilderVisitor::Visit(ReturnState* returnState) {
  builder_.CreateRet(Eval(returnState->return_expression_));
  static size_t ret_counter = 0;
  builder_.SetInsertPoint(llvm::BasicBlock::Create(
      context_, "Lret.after" + std::to_string(++ret_counter),
      current_function_));
}

void IrBuilderVisitor::Visit(WhileState* whileState) {
  static size_t while_counter = 0;

  auto* condition_block = llvm::BasicBlock::Create(
      context_, "Lwhile.cond" + std::to_string(++while_counter),
      current_function_);
  builder_.CreateBr(condition_block);

  auto* body_block = llvm::BasicBlock::Create(
      context_, "Lwhile.body" + std::to_string(while_counter),
      current_function_);
  builder_.SetInsertPoint(body_block);

  whileState->cond_->Accept(this);
  builder_.CreateBr(condition_block);

  auto* after_block = llvm::BasicBlock::Create(
      context_, "Lwhile.after" + std::to_string(while_counter),
      current_function_);

  builder_.SetInsertPoint(condition_block);
  builder_.CreateCondBr(Eval(whileState->expression_), body_block, after_block);

  builder_.SetInsertPoint(after_block);
}

void IrBuilderVisitor::Visit(DeclState* declState) {
  frame_.AssignValue(declState->variable_,
                     builder_.CreateAlloca(builder_.getInt32Ty()));
}

void IrBuilderVisitor::Visit(Function* function) {
  std::vector<llvm::Type*> args_types(function->params_list_->params_.size(),
                                      builder_.getInt32Ty());
  auto* func_type = llvm::FunctionType::get(builder_.getInt32Ty(),
                                            llvm::ArrayRef(args_types), false);

  current_function_ = llvm::Function::Create(
      func_type, llvm::GlobalValue::ExternalLinkage, function->name_, module_);
  builder_.SetInsertPoint(llvm::BasicBlock::Create(
      context_, "L" + function->name_ + ".entry", current_function_));

  frame_.EnterScope(function->statements_);
  size_t idx = 0;
  for (auto& param_name : function->params_list_->params_) {
    frame_.AssignValue(param_name,
                       builder_.CreateAlloca(builder_.getInt32Ty()));
    builder_.CreateStore(current_function_->getArg(idx++),
                         frame_.GetValue(param_name));
  }

  function->statements_->Accept(this);

  builder_.CreateRet(llvm::ConstantInt::get(builder_.getInt32Ty(), 0));
  current_function_ = nullptr;
}

void IrBuilderVisitor::Visit(FunctionsList* funcList) {
  for (auto* func : funcList->functions_) {
    func->Accept(this);
  }
}

void IrBuilderVisitor::Visit(ParamsList*) {}

void IrBuilderVisitor::Visit(ExpressionsList*) {}

void IrBuilderVisitor::Visit(AddExpression* addExpr) {
  last_value_ =
      builder_.CreateAdd(Eval(addExpr->first_), Eval(addExpr->second_));
}

void IrBuilderVisitor::Visit(NumberExpression* numExpr) {
  last_value_ = llvm::ConstantInt::get(builder_.getInt32Ty(), numExpr->value_);
}

void IrBuilderVisitor::Visit(NegExpression* negExpr) {
  last_value_ = builder_.CreateNeg(Eval(negExpr->first_));
}

void IrBuilderVisitor::Visit(CallExpression* calling) {
  auto* func = frame_.GetFunction(calling->name_);

  std::vector<llvm::Value*> params;
  for (auto param : calling->params_list_->expressions_) {
    params.push_back(Eval(param));
  }
  std::vector<llvm::Type*> params_types(func->params_list_->params_.size(),
                                        builder_.getInt32Ty());

  auto* func_type = llvm::FunctionType::get(
      builder_.getInt32Ty(), llvm::ArrayRef(params_types), false);
  auto func_callee = module_->getOrInsertFunction(calling->name_, func_type);

  last_value_ = builder_.CreateCall(func_callee, params);
}

void IrBuilderVisitor::Visit(MulExpression* mulExpr) {
  last_value_ =
      builder_.CreateMul(Eval(mulExpr->first_), Eval(mulExpr->second_));
}

void IrBuilderVisitor::Visit(IdentExpression* identExpr) {
  last_value_ = builder_.CreateLoad(builder_.getInt32Ty(),
                                    frame_.GetValue(identExpr->ident_));
}

void IrBuilderVisitor::Visit(DivExpression* divExpr) {
  last_value_ =
      builder_.CreateSDiv(Eval(divExpr->first_), Eval(divExpr->second_));
}

void IrBuilderVisitor::Visit(LLogic* log) {
  last_value_ = builder_.CreateICmpSLT(Eval(log->first_), Eval(log->second_));
}
void IrBuilderVisitor::Visit(GLogic* log) {
  last_value_ = builder_.CreateICmpSGT(Eval(log->first_), Eval(log->second_));
}
void IrBuilderVisitor::Visit(LeqLogic* log) {
  last_value_ = builder_.CreateICmpSLE(Eval(log->first_), Eval(log->second_));
}
void IrBuilderVisitor::Visit(GeqLogic* log) {
  last_value_ = builder_.CreateICmpSGE(Eval(log->first_), Eval(log->second_));
}
void IrBuilderVisitor::Visit(EqLogic* log) {
  last_value_ = builder_.CreateICmpEQ(Eval(log->first_), Eval(log->second_));
}
void IrBuilderVisitor::Visit(NeqLogic* log) {
  last_value_ = builder_.CreateICmpNE(Eval(log->first_), Eval(log->second_));
}
