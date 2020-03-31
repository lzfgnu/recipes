#pragma once

namespace AV {
  struct AVPkt {};
  enum class AVResult : uint8_t {
    FILE_CORRUPTED = 0,
    FILE_TYPE_NOT_CORRECT,
    BYTE_VAL_NOT_MATCH,
    BYTE_STREAM_EMPTY,
    AV_FILE_OPEN_FAILED,
    OK
  };
#define READ_AND_EXPECT(BUF, NTOREAD)		\
  do {						\
  int nread = reader->ReadNBytes(BUF, NTOREAD);	\
  if (nread != NTOREAD) {			\
  return AVResult::FILE_CORRUPTED;		\
  }						\
  } while(false)

#define PARSING_RESULT_EXPECT(RES)		\
  do{						\
  if (RES != AVResult::OK) {			\
  return RES;					\
  }						\
  } while(false)
  
}
