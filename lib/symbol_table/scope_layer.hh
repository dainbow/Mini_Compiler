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

  void Declare(Symbol symbol, std::shared_ptr<BasicType> value);

  std::shared_ptr<BasicType> Get(Symbol symbol);

  template <typename T>
  T* DynamicGet(Symbol symbol) {
    T* res = dynamic_cast<T*>(Get(symbol).get());
    assert(res);

    return res;
  }

  template <typename T>
  size_t GetValuesAmount() {
    size_t counter = 0;
    
    for (auto& val : values_) {
      if (dynamic_cast<T*>(val.second.get())) {
        counter++;
      }
    }

    return counter;
  }

  bool Has(const Symbol& symbol);
  ScopeStatements* AsStatements();

  void AddChild(ScopeLayer* child, ScopeStatements* child_scope);

  ScopeLayer* GetChild(ScopeStatements* scope);
  ScopeLayer* GetParent();

 private:
  void Put(Symbol symbol, std::shared_ptr<BasicType> value);

  std::shared_ptr<BasicType>& Find(Symbol symbol);
  std::unordered_map<Symbol, std::shared_ptr<BasicType>> values_;

  ScopeStatements* statements_;
  ScopeLayer* parent_;
  std::unordered_map<ScopeStatements*, ScopeLayer*> children_;
};
