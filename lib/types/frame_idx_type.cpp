#include "frame_idx_type.hh"

FrameIdxType::FrameIdxType(int value) : value_(value) {}

Type FrameIdxType::GetType() {
  return Type::FrameIdxType;
}

size_t FrameIdxType::GetIdx() {
  return value_;
}
