#pragma once

enum class Type { Unknown, FrameIdxType, FuncType };

class BasicType {
 public:
  virtual Type GetType();
  virtual ~BasicType() = default;
};
