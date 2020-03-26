#pragma once

#include <cstdint>

namespace AV {

  enum struct ByteOrder : uint8_t {
    LE = 0,
    BE,
  };
  
  using Byte = uint8_t;

  // len must be less or eq then 4;
  int32_t BytesToInt32(Byte* bytes, int len, ByteOrder order);
}
