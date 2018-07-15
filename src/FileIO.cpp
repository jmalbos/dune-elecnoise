/// ----------------------------------------------------------------------------
/// File     : FileIO.cpp
/// Author   : Justo Martin-Albo
/// Creation : 9 July 2018
/// ----------------------------------------------------------------------------

#include "FileIO.h"

#include <vector>
#include <sstream>
#include <iostream>


FileReader::FileReader(char const * filename)
{
  file_.open(filename, std::fstream::in);
  if (file_.is_open()) std::cout << "File opened successfully!" << std::endl;
}


FileReader::~FileReader()
{
  file_.close();
}


void FileReader::Read()
{
  std::string line, buffer;
  std::vector<std::string> words;

  // Let's read the first line and store it in a string
  // that we'll later split in words
  std::getline(file_, line);
  std::stringstream ss(line);

  while (ss >> buffer) {
    //std::cout << buffer << std::endl;
    words.push_back(buffer);
  }

  std::cout << "Number of words: " << words.size() << std::endl;
}
