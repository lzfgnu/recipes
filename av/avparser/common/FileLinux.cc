#include "FileLinux.h"
#include <cassert>

namespace AV {

  File::File() : fd(-1), fileSize(0) {}
  bool File::Open(const std::string& filePath, int flags) {
    assert(!IsOpen());
    fd = ::open(filePath.c_str(), flags);
    if (fd >= 0) {
      this->filePath = filePath;
      fileSize = Seek(0, FILE_END);
      Seek(0, FILE_BEG);
      return true;
    }
    return false;
  }

  void File::Close() {
    if (IsOpen()) {
      ::close(fd);
      fd = -1;
      fileSize = 0;
      filePath.clear();
    }
  }

  bool File::IsOpen() const {
    return fd != -1 && fd >= 0;
  }

  int File::Read(void *buf, int n) {
    return ::read(fd, buf, n);
  }

  int File::Seek(int n, int whence) {
    return ::lseek(fd, n, whence);
  }

  int File::Tell() {
    return Seek(0, FILE_CUR);
  }
  
  std::string File::GetFilePath() const {
    return filePath;
  }

  int File::GetFileSize() const {
    return fileSize;
  }

  bool File::Eof() {
    return Seek(0, FILE_CUR) == fileSize;
  }
}
