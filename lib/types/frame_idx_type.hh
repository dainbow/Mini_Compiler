#pragma once

#include <cstddef>
#include "type.hh"

class FrameIdxType : public BasicType {
 public:
  explicit FrameIdxType(int value);

  virtual Type GetType() override;
  size_t GetIdx();

 private:
  size_t value_;
};
