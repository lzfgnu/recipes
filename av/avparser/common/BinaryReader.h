#pragma once

#include <cstdint>

namespace AV {
  using Byte = uint8_t;
  class BinaryReader {
  public:
    explicit BinaryReader(int bufferSize = DEFAULT_BUFFER_SIZE);
    explicit BinaryReader(Byte* buf, int bufferSize);
    BinaryReader(const BinaryReader&) = delete;
    BinaryReader& operator=(const BinaryReader&) = delete;
    virtual ~BinaryReader();

    int GetBufferSize() const;
  
    virtual bool HaveBytes();
    virtual int ReadNBytes(Byte* buf, int n);
    virtual int SkipNBytes(int n);
    virtual int PeekNBytes(Byte* buf, int n);

  protected:
    void CreateBuffer(int bufferSize);
    void DestoryBuffer();


  public:
    const static int DEFAULT_BUFFER_SIZE;
  protected:
    Byte* beg;
    Byte* cur;
    Byte* end;
    int bufferSize;
  };
}; // AV
