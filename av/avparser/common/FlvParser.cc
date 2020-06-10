#include "FlvParser.h"
#include "ByteUtils.h"
#include <cassert>


namespace AV {
  const int FLV_HEADER_SIZE = 9;
  const int BACK_PTR_SIZE = 4;
  FlvParser::FlvParser() {
    info = new FlvInfo();
  }
  FlvParser::~FlvParser() {}

  AVResult FlvParser::ParseImpl(BinaryReader* reader) {
    AVResult res = ParseHeader(reader);
    PARSING_RESULT_EXPECT(res);
    return ParseBody(reader);
  }

  AVResult FlvParser::ParsePipelinedImpl(BinaryReader* reader, std::shared_ptr<AVPacketHandler> handler) {
    AVResult res = ParseHeader(reader);
    PARSING_RESULT_EXPECT(res);
  }

  AVResult FlvParser::ParseHeader(BinaryReader* reader) {
    FlvInfo* flvInfo = static_cast<FlvInfo*>(info);
    const int size = FLV_HEADER_SIZE + BACK_PTR_SIZE;
    Byte buf[size];
    READ_AND_EXPECT(buf, size);

    // signature;
    if (buf[0] != 'F' ||
	buf[1] != 'L' ||
	buf[2] != 'V') {
      return AVResult::FILE_TYPE_NOT_CORRECT;
    }

    // version;
    flvInfo->version = buf[3];

    // flags;
    flvInfo->videoExist = (buf[4]>>2) & 0x1;
    flvInfo->audioExist = buf[4] & 0x1;

    // dataOffset;
    if (buf[5] != 0 ||
	buf[6] != 0 ||
	buf[7] != 0 ||
	buf[8] != 9) {
      return AVResult::BYTE_VAL_NOT_MATCH;
    }
    return AVResult::OK;
  }


  AVResult FlvParser::ParseBody(BinaryReader* reader) {
    while (reader->HaveBytes()) {
      AVResult res = ParseTag(reader);
      if (res != AVResult::OK) {
	// TODO  ==>  Clean up
      }

    }


    return AVResult::OK;
  }

  AVResult FlvParser::ParseTag(BinaryReader* reader) {
    // type => 1byte
    // tag_data_size => 3byte
    // time_streamp => 3byte
    // time_stamp_extended => 1byte
    // stream_id => 3byte
    Byte type;
    READ_AND_EXPECT(&type, 1);
    switch (type) {
    case 9: {
      return ParseVideoTag(reader);
      break;
    }
    case 8: {
      return ParseAudioTag(reader);
      break;
    }
    case 18 {
      return ParseScriptTag(reader);
      break;
    }
    default {
      break;
    }
    }
    return AVResult::OK;
  }

  AVResult FlvParser::ParseVideoTag(BinaryReader* reader) {
    Byte buf[10];
    READ_AND_EXPECT(buf, 10);
    int size = BytesToInt32(buf, 3, ByteOrder::BE);
    
  }

  AVResult FlvParser::ParseAudioTag(BinaryReader* reader) {
    Byte buf[10];
    READ_AND_EXPECT(buf, 10);
    int size = BytesToInt32(buf, 3, ByteOrder::BE);
  }

  AVResult FlvParser::ParseScriptTag(BinaryReader* reader) {
    Byte buf[10];
    READ_AND_EXPECT(buf, 10);
    int size = BytesToInt32(buf, 3, ByteOrder::BE);
  }
} // AV
