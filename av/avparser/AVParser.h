#pragma once

#include "BinaryFileReader.h"
#include "AVData.h"
#include <vector>
#include <string>
#include <functional>

#define NUM_EXPECT(ACTUAL_VAL, EXPECTED_VAL) \
  ((ACTUAL_VAL) == (EXPECTED_VAL))

namespace AV {
  
  enum struct AVPacketType : uint8_t {
    AUDIO = 0,
    VIDEO,
    UNKNOWN
  };
  struct AVPacket {
    AVPacket(int len);
    AVPacket(const AVPacket&) = delete;
    ~AVPacket();
    AVPacket& operator=(const AVPacket&) = delete;
    
    Byte* data;
    int len;
    AVPacketType type;
  };

  enum struct AVFileType : uint8_t {
    FLV = 0,
    UNKNOWN
  };

  enum struct ParsingResult : uint8_t {
    PARSING_OK = 0,
    FILE_TYPE_NOT_CORRECT,
    FILE_CORRUPTED,
    BYTES_VAL_NOT_MATCH
  };
  
  class AVParser {
  public:
    AVParser(const std::string& filePath);
    AVParser(const AVParser&) = delete;
    AVParser& operator=(const AVParser&) = delete;
    virtual ~AVParser();
    
    virtual ParsingResult Parse() = 0;
    virtual ParsingResult ParsePipelined(std::function<void (const AVPacket&)> pktHandler) = 0;

    int GetFileSize() const;
    AVFileType GetFileType() const;
    std::string GetFilePath() const;
    const VideoData& GetVideoData() const;
    const AudioData& GetAudioData() const;

  protected:
    AVFileType fileType;
    BinaryFileReader* reader;
    VideoData video;
    AudioData audio;
  };
} // AV
