#include "scope_layer.hh"

#include "types/frame_idx_type.hh"
#include "types/func_type.hh"

#include <cassert>
#include <stdexcept>

ScopeLayer::ScopeLayer(ScopeLayer* parent, ScopeStatements* my_scope)
    : scope_size_(parent->GetSize()), values_(), parent_(parent), children_() {
  parent_->AddChild(this, my_scope);
}

ScopeLayer::ScopeLayer()
    : scope_size_(0), values_(), parent_(nullptr), children_() {}

void ScopeLayer::DeclareVariable(Symbol symbol) {
  if (Has(symbol)) {
    throw std::runtime_error("Name conflict, already declared");
  }

  values_[symbol] = std::make_shared<FrameIdxType>(scope_size_++);
}

void ScopeLayer::DeclareFunction(Symbol symbol, Function* function) {
  if (Has(symbol)) {
    throw std::runtime_error("Name conflict, already declared");
  }

  values_[symbol] = std::make_shared<FuncType>(function);
}

void ScopeLayer::Put(Symbol symbol, std::shared_ptr<BasicType> value) {
  Find(symbol) = value;
}

std::shared_ptr<BasicType> ScopeLayer::Get(Symbol symbol) {
  return Find(symbol);
}

bool ScopeLayer::Has(const Symbol& symbol) {
  return values_.find(symbol) != values_.end();
}

size_t ScopeLayer::GetSize() {
  return scope_size_;
}

void ScopeLayer::AddChild(ScopeLayer* child, ScopeStatements* child_scope) {
  children_[child_scope] = child;
}

ScopeLayer* ScopeLayer::GetChild(ScopeStatements* scope) {
  assert(children_.find(scope) != children_.end());
  return children_[scope];
}

ScopeLayer* ScopeLayer::GetParent() {
  return parent_;
}

std::shared_ptr<BasicType>& ScopeLayer::Find(Symbol symbol) {
  ScopeLayer* current_layer = this;

  while (!current_layer->Has(symbol) && current_layer->parent_ != nullptr) {
    current_layer = current_layer->parent_;
  }

  if (current_layer->Has(symbol)) {
    return current_layer->values_.find(symbol)->second;
  } else {
    throw std::runtime_error("Variable not declared");
  }
}
