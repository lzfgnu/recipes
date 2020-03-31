#pragma once

#include "BinaryReader.h"
#include "AVInfo.h"
#include "AVPacketHandler.h"
#include "AVCommon.h"
#include <string>
#include <memory>


namespace AV {
  class AVParser {
  public:
    virtual ~AVParser();
    
    AVResult Parse(const std::string& filePath);
    AVResult Parse(BinaryReader* reader);
    AVResult ParsePipelined(const std::string& filePath, std::shared_ptr<AVPacketHandler> handler);
    AVResult ParsePipelined(BinaryReader* reader, std::shared_ptr<AVPacketHandler> handler);

    AVInfo* GetInfo() const;

    
  private:
    virtual AVResult ParseImpl(BinaryReader* reader) = 0;
    virtual AVResult ParsePipelinedImpl(BinaryReader* reader, std::shared_ptr<AVPacketHandler> handler) = 0;
  protected:
    AVInfo* info;
  };

} // AV
