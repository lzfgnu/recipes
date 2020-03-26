#include "FlvParser.h"
#include "ByteUtils.h"
#include <cstring>
#include <cstdio>
namespace AV {

  const Byte FLV_SIGNATURE[] = {'F', 'L', 'V'};
  const int FLV_HEADER_SIZE = 9;
  const int BACK_PTR_SIZE = 4;


  
  FlvParser::FlvParser(const std::string& file) :
    AVParser(file),
    version(0),
    videoExist(false),
    audioExist(false) {}

  
  ParsingResult FlvParser::Parse() {
    auto res = ParseHeader();
    if (res != ParsingResult::PARSING_OK) return res;
    return ParseBody();
  }

  
  ParsingResult FlvParser::ParsePipelined(std::function<void (const AVPacket&)> pktHandler) {
    
    return ParsingResult::BYTES_VAL_NOT_MATCH;
  }


  ParsingResult FlvParser::ParseHeader() {
    const int SIZE = FLV_HEADER_SIZE + BACK_PTR_SIZE;
    Byte buf[SIZE];
    int nread = reader->ReadNBytes(buf, SIZE);
    if (!NUM_EXPECT(nread, SIZE)) {
      return ParsingResult::FILE_CORRUPTED;
    }
    if (memcmp(buf, FLV_SIGNATURE, 3) != 0) {
      return ParsingResult::FILE_TYPE_NOT_CORRECT;
    }
    
    fileType = AVFileType::FLV;
    version = buf[3];
    videoExist = buf[4] & 0x1;
    audioExist = buf[4] & 0x4;

    if (!NUM_EXPECT(buf[5], 0) ||
	!NUM_EXPECT(buf[6], 0) ||
	!NUM_EXPECT(buf[7], 0) ||
	!NUM_EXPECT(buf[8], 9)) {
      return ParsingResult::BYTES_VAL_NOT_MATCH;
    }
    return ParsingResult::PARSING_OK;
  }

  ParsingResult FlvParser::ParseBody() {
    Byte buf[4];
    while (reader->HaveBytes()) {
      FlvTag tag;
      int nread = ReadTag(&tag);
      reader->ReadNBytes(buf, 4);
      int tagSize = BytesToInt32(buf, 4, ByteOrder::BE);
      
      if (nread != tagSize) {
	::printf("...tagSize\n");
	return ParsingResult::FILE_CORRUPTED;
      }

      ParsingResult res;
      switch (tag.type) {
      case 18: {
	// script;
	res = ParseScriptTag(tag);
	break;
      }
      case 9: {
	// video;
	res = ParseVideoTag(tag);
	break;
      }
      case 8: {
	// audio;
	res = ParseAudioTag(tag);
	break;
      }
      default: {
	return ParsingResult::BYTES_VAL_NOT_MATCH;
      }
      }

      if (res != ParsingResult::PARSING_OK) {
	return res;
      }
    }
    return ParsingResult::PARSING_OK;
  }

  ParsingResult FlvParser::ParseScriptTag(FlvTag& tag) {

    return ParsingResult::PARSING_OK;
  }

  ParsingResult FlvParser::ParseVideoTag(FlvTag& tag) {
    Byte* ptr = tag.data;
    int frameType = (ptr[0] >> 4) & Byte(0x0f);
    int codecId = ptr[0] & Byte(0x0f);
    ++ptr;
    ::printf("%d %d\n", frameType, codecId);
    // AVC
    if (codecId == 7) {
      // if avcpkttype == 0  ==> sps pps
      //    avcpkttype == 1  ==> video frame data
      int avcPktType = ptr[0];
      int compositionTime =
	avcPktType == 1 ? BytesToInt32(ptr+1, 3, ByteOrder::BE): 0;
      ptr += 4;
    }
    

    return ParsingResult::PARSING_OK;
  }

  ParsingResult FlvParser::ParseAudioTag(FlvTag& tag) {
    Byte* ptr = tag.data;
    int format = (ptr[0] >> 4) & Byte(0x0f);
    int sampleRate = (ptr[0] >> 2) & Byte(0x03);
    int sampleLen = (ptr[0] >> 1) & Byte(0x01);
    int type = ptr[0] & Byte(0x01);
    return ParsingResult::PARSING_OK;
  }
  
  int FlvParser::ReadTag(FlvTag* tag) {
    int totalRead = 0;
    int nread = 0;

    Byte buf[4];
    nread = reader->ReadNBytes(buf, 1);
    totalRead += nread;
    tag->type = buf[0];

    nread = reader->ReadNBytes(buf, 3);
    totalRead += nread;
    tag->dataSize = BytesToInt32(buf, nread, ByteOrder::BE);
    
    nread = reader->ReadNBytes(buf, 3);
    totalRead += nread;
    tag->timeStreamp = BytesToInt32(buf, nread, ByteOrder::BE);

    nread = reader->ReadNBytes(buf, 1);
    totalRead += nread;
    tag->timeStampExtended = buf[0];

    nread = reader->ReadNBytes(buf, 3);
    totalRead += nread;
    tag->streamId = BytesToInt32(buf, nread, ByteOrder::BE);

    tag->data = new Byte[tag->dataSize];
    nread = reader->ReadNBytes(tag->data, tag->dataSize);
    totalRead += nread;
    
    return totalRead;
  }
  
  bool FlvParser::VideoExist() const {
    return videoExist;
  }

  bool FlvParser::AudioExist() const {
    return audioExist;
  }

  int FlvParser::Version() const {
    return version;
  }
} // AV
