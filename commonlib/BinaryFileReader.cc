#include "BinaryFileReader.h"
#include <cassert>
#include <cstring>

BinaryFileReader::BinaryFileReader(const std::string& filePath, int bufferSize) :
  BinaryReader(bufferSize),
  filePath(filePath) {
  
  OpenFile(filePath);
}

BinaryFileReader::~BinaryFileReader() {
  CloseFile();
}

bool BinaryFileReader::OpenFile(const std::string &filePath) {
  assert(!inStream.is_open());
  this->filePath = filePath;
  inStream.open(filePath);
  fileSize = inStream.seekg(0, std::ios::end).tellg();
  inStream.seekg(0, std::ios::beg);
  LoadBuffer();
  return inStream.is_open() && inStream.good();
}

void BinaryFileReader::CloseFile() {
  if (inStream.is_open()) {
    inStream.close();
    fileSize = 0;
    filePath.clear();
  }
}

std::string BinaryFileReader::GetFilePath() const {
  return filePath;
}

int BinaryFileReader::GetFileSize() const {
  return fileSize;
}

int BinaryFileReader::ReadNByte(Byte *buf, int n) {
  assert(inStream.is_open());
  if (n < 0) { return -1; }
  if (!HaveBytes()) { return 0; }
  
  int nleft = end-cur;
  int nread = 0;
  if (nleft >= n) {
    memmove(buf, cur, n);
    cur += n;
    nread = n;
  }
  else {
    nread = nleft;
    memmove(buf, cur, nleft);
    LoadBuffer();
    return nread + ReadNByte(buf+nread, n-nread);
  }
  return nread;
}

int BinaryFileReader::SkipNByte(int n) {
  assert(inStream.is_open());
  if (n < 0) return -1;
  
  int nleft = end - cur;
  if (nleft >= n) {
    cur += n;
    return n;
  }
  else {
    cur = end;
    int nseek = n - nleft;
    auto fcur = inStream.tellg();
    auto fleft = inStream.seekg(0, inStream.end).tellg() - fcur;
    nseek = nseek > fleft ? fleft : nseek;
    inStream.seekg((int)fcur+nseek, inStream.beg);
    return nleft + nseek;
  }
}

int BinaryFileReader::PeekNByte(Byte *buf, int n) {
  assert(inStream.is_open());
  if (n < 0) return -1;
  n = n > bufferSize ? bufferSize : n;
  
  int nleft = end - cur;
  if (nleft >= n) {
    memmove(buf, cur, n);
    return n;
  }
  else {
    // fill buffer
    int nread = cur-beg;
    memmove(beg, cur, nleft);
    inStream.read((char*)beg + nleft, nread);
    nread = inStream.gcount();
    cur = beg;
    end = beg + (nread + nleft);
    n = n > (end-cur) ? (end-cur) : n;
    memmove(buf, cur, n);
    return n;
  }
}

void BinaryFileReader::LoadBuffer() {
  inStream.read((char*)beg, bufferSize);
  cur = beg;
  end = beg + inStream.gcount();
}


bool BinaryFileReader::HaveBytes() {
  if (cur < end) return true;
  inStream.peek();
  return !inStream.eof();
}
