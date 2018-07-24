/// ----------------------------------------------------------------------------
/// File     : FileIO.h
/// Info     :
/// Authors  : Babak Abi, Justo Martin-Albo, Miquel Nebot
/// Creation : 9 July 2018
/// ----------------------------------------------------------------------------

#ifndef FILE_IO
#define FILE_IO

#include <fstream>
#include <vector>


class Event
{
public:
};


class FileReader
{
public:
  FileReader(char const *);
  ~FileReader();

  void ReadEvent(std::vector<std::vector<double>>&);

private:
  std::fstream file_;
  std::vector<double> buffer_;
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
