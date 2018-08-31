// -----------------------------------------------------------------------------
// File     : FileIO.h
// Info     :
// Authors  : Babak Abi, Justo Martin-Albo, Miquel Nebot
// Creation : 9 July 2018
// -----------------------------------------------------------------------------

#ifndef FILE_IO
#define FILE_IO

#include <fstream>
#include <vector>
#include <string>


class FileReader
{
public:
  FileReader(std::string);
  ~FileReader();

  void ReadEvent(std::vector<std::vector<double>>&);

private:
  std::fstream file_;
  std::vector<double> buffer_;
};


class FileWriter
{
public:
  FileWriter(std::string);
  ~FileWriter();

  void WriteEvent(std::vector<std::vector<double>>&);

private:
  std::fstream file_;
};

#endif
