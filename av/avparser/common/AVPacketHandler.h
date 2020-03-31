#pragma once

#include "AVCommon.h"
namespace AV {
  class AVPacketHandler {
  public:
    virtual AVResult Handle(const AVPkt& pkt) = 0;
  };
}
