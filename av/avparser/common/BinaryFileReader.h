#pragma once

#ifdef __linux__
#include "FileLinux.h"
#endif

#include "BinaryReader.h"
#include <string>
#include <fstream>

namespace AV {
  class BinaryFileReader : public BinaryReader {
  public:
    explicit BinaryFileReader(int bufferSize = DEFAULT_BUFFER_SIZE);
    virtual ~BinaryFileReader();

  public:
    bool OpenFile(const std::string& filePath);
    void CloseFile();
    std::string GetFilePath() const;
    int GetFileSize() const;

    virtual bool HaveBytes();
    virtual int ReadNBytes(Byte* buf, int n);
    virtual int SkipNBytes(int n);
    virtual int PeekNBytes(Byte* buf, int n);

  private:
    void LoadBuffer();
  
  private:
    File file;
  };
} // AV
