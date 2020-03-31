#pragma once
#include "AVParser.h"

namespace AV {
  struct FlvInfo : public AVInfo {
    virtual ~FlvInfo() {}
    int version;
    bool videoExist;
    bool audioExist;
  };
  
  class FlvParser : public AVParser {
  public:
    FlvParser();
    virtual ~FlvParser();
    
  private:
    virtual AVResult ParseImpl(BinaryReader* reader);
    virtual AVResult ParsePipelinedImpl(BinaryReader* reader, std::shared_ptr<AVPacketHandler> handler);

    AVResult ParseHeader(BinaryReader* reader);
    AVResult ParseBody(BinaryReader* reader);
    AVResult ParseTag(BinaryReader* reader);
  };
} // AV
