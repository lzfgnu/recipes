#pragma once

#include "BinaryReader.h"
#include <string>
#include <fstream>

class BinaryFileReader : public BinaryReader {
public:
  explicit BinaryFileReader(const std::string& filePath, int bufferSize = DEFAULT_BUFFER_SIZE);
  virtual ~BinaryFileReader();
  
public:
  bool OpenFile(const std::string& filePath);
  void CloseFile();
  std::string GetFilePath() const;
  int GetFileSize() const;

  virtual bool HaveBytes();
  virtual int ReadNByte(Byte* buf, int n);
  virtual int SkipNByte(int n);
  virtual int PeekNByte(Byte* buf, int n);

private:
  void LoadBuffer();
  
private:
  std::string filePath;
  std::ifstream inStream;
  int fileSize;
};
