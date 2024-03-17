#include "frame_idx_type.hh"

FrameIdxType::FrameIdxType(size_t value) : value_(value) {}

size_t FrameIdxType::GetIdx() {
  return value_;
}
