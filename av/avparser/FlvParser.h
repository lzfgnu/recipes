
#pragma once

#include "AVParser.h"

namespace AV {
struct FlvTag {
    FlvTag() : data(nullptr) {}
    ~FlvTag() { delete[] data; }
    int type;
    int dataSize;
    int timeStreamp;
    int timeStampExtended;
    int streamId;
    Byte* data;
  };
  
  class FlvParser : public AVParser {
  public:
    FlvParser(const std::string& file);
    
    virtual ParsingResult Parse();
    virtual ParsingResult ParsePipelined(std::function<void (const AVPacket&)> pktHandler);
    bool VideoExist() const;
    bool AudioExist() const;
    int Version() const;
    
  private:
    ParsingResult ParseHeader();
    ParsingResult ParseBody();
    ParsingResult ParseScriptTag(FlvTag& tag);
    ParsingResult ParseVideoTag(FlvTag& tag);
    ParsingResult ParseAudioTag(FlvTag& tag);
    int ReadTag(FlvTag* tag);
    
  private:
    int version;
    bool videoExist;
    bool audioExist;
  };
} // AV
