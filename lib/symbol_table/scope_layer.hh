#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>

#include "statements/scope_statements.hh"
#include "symbol.hh"
#include "types/type.hh"

class ScopeLayer {
 public:
  ScopeLayer(ScopeLayer* parent, ScopeStatements* my_scope);
  ScopeLayer();

  void DeclareVariable(Symbol symbol);
  void DeclareFunction(Symbol symbol, Function* params);

  std::shared_ptr<BasicType> Get(Symbol symbol);
#define DYNAMIC_GET(type, instance, symbol)                \
  (assert(instance->Get(symbol)->GetType() == Type::type), \
   dynamic_cast<type*>(instance->Get(symbol).get()))

  bool Has(const Symbol& symbol);
  size_t GetSize();

  void AddChild(ScopeLayer* child, ScopeStatements* child_scope);

  ScopeLayer* GetChild(ScopeStatements* scope);
  ScopeLayer* GetParent();

 private:
  void Put(Symbol symbol, std::shared_ptr<BasicType> value);

  std::shared_ptr<BasicType>& Find(Symbol symbol);

  size_t scope_size_;
  std::unordered_map<Symbol, std::shared_ptr<BasicType>> values_;

  ScopeLayer* parent_;
  std::unordered_map<ScopeStatements*, ScopeLayer*> children_;
};
