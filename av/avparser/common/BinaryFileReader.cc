#include "BinaryFileReader.h"
#include <cassert>
#include <cstring>

namespace AV {
  BinaryFileReader::BinaryFileReader(int bufferSize) :
    BinaryReader(bufferSize) {}
  
  BinaryFileReader::~BinaryFileReader() {
    if (!file.IsOpen()) {
      CloseFile();
    }
  }

  bool BinaryFileReader::OpenFile(const std::string &filePath) {
    bool res = file.Open(filePath, FILE_READ);
    LoadBuffer();
    return res;
  }

  void BinaryFileReader::CloseFile() {
    file.Close();
  }

  std::string BinaryFileReader::GetFilePath() const {
    return file.GetFilePath();
  }

  int BinaryFileReader::GetFileSize() const {
    return file.GetFileSize();
  }

  int BinaryFileReader::ReadNBytes(Byte *buf, int n) {
    assert(file.IsOpen());
    
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
      return nread + ReadNBytes(buf+nread, n-nread);
    }
    return nread;
  }

  int BinaryFileReader::SkipNBytes(int n) {
    assert(file.IsOpen());
    
    if (n < 0) return -1;
  
    int nleft = end - cur;
    if (nleft >= n) {
      cur += n;
      return n;
    }
    else {
      cur = end;
      int nseek = n - nleft;
      int fcur = file.Tell();
      int fleft = file.Seek(0, FILE_END) - fcur;
      nseek = nseek > fleft ? fleft : nseek;
      file.Seek(fcur+nseek, FILE_BEG);
      return nleft + nseek;
    }
  }

  int BinaryFileReader::PeekNBytes(Byte *buf, int n) {
    assert(file.IsOpen());

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
      nread = file.Read(beg + nleft, nread);
      cur = beg;
      end = beg + (nread + nleft);
      n = n > (end-cur) ? (end-cur) : n;
      memmove(buf, cur, n);
      return n;
    }
  }

  void BinaryFileReader::LoadBuffer() {
    int nread = file.Read(beg, bufferSize);
    cur = beg;
    end = beg + nread;
  }


  bool BinaryFileReader::HaveBytes() {
    if (cur < end) return true;
    return !file.Eof();
  }
} // AV
