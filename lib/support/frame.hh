#pragma once

#include <vector>
#include "symbol_table/scope_layer.hh"
#include "types/frame_idx_type.hh"
#include "types/func_type.hh"

template <typename T>
class Frame {
  std::vector<T> frame_data_;

  ScopeLayer* root_;
  ScopeLayer* current_layer_;

 public:
  Frame(ScopeLayer* root) : frame_data_(), root_(root), current_layer_(root) {}

  ScopeLayer* GetRoot() { return root_; }

  void EnterScope(ScopeStatements* new_scope) {
    if (current_layer_->AsStatements() == new_scope) {
      return;
    }

    current_layer_ = current_layer_->GetChild(new_scope);
    frame_data_.resize(frame_data_.size() +
                       current_layer_->GetValuesAmount<FrameIdxType>());
  }

  void ExitScope(bool is_truncate = true) {
    if (is_truncate) {
      frame_data_.resize(frame_data_.size() -
                         current_layer_->GetValuesAmount<FrameIdxType>());
    }

    current_layer_ = current_layer_->GetParent();
    assert(current_layer_);
  }

  void AssignValue(const Symbol& symbol, T value) {
    size_t frame_idx =
        current_layer_->DynamicGet<FrameIdxType>(symbol)->GetIdx();

    frame_data_[frame_data_.size() - frame_idx] = value;
  }

  T GetValue(const Symbol& symbol) {
    size_t frame_idx =
        current_layer_->DynamicGet<FrameIdxType>(symbol)->GetIdx();

    return frame_data_[frame_data_.size() - frame_idx];
  }

  Function* GetFunction(const Symbol& name) {
    return root_->DynamicGet<FuncType>(name)->GetFunction();
  }
};
