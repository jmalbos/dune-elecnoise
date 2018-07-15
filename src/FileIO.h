/// ----------------------------------------------------------------------------
/// File     : FileIO.h
/// Info     :
/// Author   : Justo Martin-Albo
/// Creation : 9 July 2018
/// ----------------------------------------------------------------------------

#ifndef FILE_IO
#define FILE_IO

#include <fstream>


class FileReader
{
public:
  FileReader(char const *);
  ~FileReader();

  void Read();

private:
  std::fstream file_;
};


class FileWriter
{
public:
  FileWriter() {}
  ~FileWriter() {}

private:
  std::fstream ofile;
};

#endif
