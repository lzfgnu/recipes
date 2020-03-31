#include "ByteUtils.h"
#include <cstring>

namespace AV {

  static void ReverseBytes(Byte* bytes, int len) {
    int i = 0;
    int j = len-1;
    while (i < j) {
      Byte tmp = bytes[i];
      bytes[i] = bytes[j];
      bytes[j] = tmp;
      ++i; --j;
    }
  }
  
  int32_t BytesToInt32(Byte* bytes, int len, ByteOrder order) {
    if (len < 0) return -1;
    if (order == ByteOrder::BE) {
      ReverseBytes(bytes, len);
    }
    int32_t ret = 0;
    memmove(&ret, bytes, len);
    return ret;
  }
}
