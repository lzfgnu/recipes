#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string>
namespace AV {
  const int FILE_READ = O_RDONLY;
  const int FILE_WRITE = O_WRONLY;
  const int FILE_RDWR = O_RDWR;
  const int FILE_BEG = SEEK_SET;
  const int FILE_CUR = SEEK_CUR;
  const int FILE_END = SEEK_END;
  
  class File {
  public:
    File();
    bool Open(const std::string&, int flags);
    bool IsOpen() const;
    void Close();
    int Read(void* buf, int n);
    int Seek(int n, int whence);
    int Tell();
    bool Eof();

    std::string GetFilePath() const;
    int GetFileSize() const;
  private:
    std::string filePath;
    int fd;
    int fileSize;
  };
}
