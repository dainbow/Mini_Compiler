#pragma once

#include <cstddef>
#include "type.hh"

class FrameIdxType : public BasicType {
 public:
  explicit FrameIdxType(size_t value);

  size_t GetIdx();

 private:
  size_t value_;
};
