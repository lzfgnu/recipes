#include "AVParser.h"
#include "BinaryFileReader.h"
#include <cassert>
namespace AV {
  AVParser::~AVParser() {
    delete info;
  }
  
  AVResult AVParser::Parse(const std::string& filePath) {
    BinaryFileReader reader;
    if (!reader.OpenFile(filePath)) {
      return AVResult::AV_FILE_OPEN_FAILED;
    }
    return ParseImpl(&reader);
  }
  
  AVResult AVParser::Parse(BinaryReader* reader) {
    assert(reader != nullptr);
    if (!reader->HaveBytes()) {
      return AVResult::BYTE_STREAM_EMPTY;
    }
    return ParseImpl(reader);
  }
  
  AVResult AVParser::ParsePipelined(const std::string& filePath, std::shared_ptr<AVPacketHandler> handler) {
    BinaryFileReader reader;
    reader.OpenFile(filePath);
    return ParsePipelinedImpl(&reader, handler);
  }
  
  AVResult AVParser::ParsePipelined(BinaryReader* reader, std::shared_ptr<AVPacketHandler> handler) {
    return ParsePipelinedImpl(reader, handler);
  }

  AVInfo* AVParser::GetInfo() const {
    return info;
  }
} // AV
