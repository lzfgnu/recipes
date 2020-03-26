#include "BinaryReader.h"
#include <cstring>
#include <cstdio>
#include <cassert>

namespace AV {
  const int BinaryReader::DEFAULT_BUFFER_SIZE = 40960;
  BinaryReader::BinaryReader(int bufferSize) :
    beg(nullptr),
    cur(nullptr),
    end(nullptr) {
    CreateBuffer(bufferSize);
  }

  BinaryReader::BinaryReader(Byte* buf, int bufferSize) :
    beg(nullptr),
    cur(nullptr),
    end(nullptr) {

    CreateBuffer(bufferSize);
    memmove(beg, buf, bufferSize);
  }

  BinaryReader::~BinaryReader() {
    DestoryBuffer();
  }

  int BinaryReader::ReadNBytes(Byte* buf, int n) {
    int nread =
      (cur + n <= end ? n : end - cur);
    memmove(buf, cur, nread);
    cur += nread;
    return nread;
  }

  int BinaryReader::SkipNBytes(int n) {
    int nskip =
      (cur + n <= end ? n : end - cur);
    cur += nskip;
    return nskip;
  }

  int BinaryReader::PeekNBytes(Byte* buf, int n) {
    int npeek =
      (cur + n <= end ? n : end - cur);
    memmove(buf, cur, npeek);
    return npeek;
  }


  int BinaryReader::GetBufferSize() const {
    return bufferSize;
  }

  bool BinaryReader::HaveBytes() {
    return cur < end;
  }
 
  void BinaryReader::CreateBuffer(int bufferSize) {
    assert(bufferSize > 0);
    beg = new Byte[bufferSize];
    cur = beg;
    end = beg + bufferSize;
    this->bufferSize = bufferSize;
  }

  void BinaryReader::DestoryBuffer() {
    delete[] beg;
    beg = cur = end = nullptr;
    bufferSize = 0;
  }
} // AV
