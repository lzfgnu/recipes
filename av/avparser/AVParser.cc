#include "AVParser.h"
#include <cassert>

namespace AV {
  AVPacket::AVPacket(int len) :
    len(len), type(AVPacketType::UNKNOWN) {
    
    assert(len > 0);
    data = new Byte[len];
  }
  AVPacket::~AVPacket() {
    delete[] data;
    data = nullptr;
    len = 0;
    type = AVPacketType::UNKNOWN;
  }


  
  AVParser::AVParser(const std::string& filePath) :
    fileType(AVFileType::UNKNOWN),
    reader(new BinaryFileReader) {
    bool res = reader->OpenFile(filePath);
    assert(res);
  }

  AVParser::~AVParser() {
    delete reader;
    reader = nullptr;
    fileType = AVFileType::UNKNOWN;
  }

  int AVParser::GetFileSize() const {
    return reader->GetFileSize();
  }

  AVFileType AVParser::GetFileType() const {
    return fileType;
  }

  std::string AVParser::GetFilePath() const {
    return reader->GetFilePath();
  }

  const VideoData& AVParser::GetVideoData() const {
    return video;
  }

  const AudioData& AVParser::GetAudioData() const {
    return audio;
  }
} // AV
