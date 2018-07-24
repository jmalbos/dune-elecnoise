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


void FileReader::ReadEvent(std::vector<std::vector<double>>& samples)
{
  int i=0;

  while (!file_.eof()) {

    std::cout << i << std::endl; ++i;

    std::string line, word;
    std::vector<std::string> words;

    // Read a line from the file and store it in a string
    // that we'll later split in words
    std::getline(file_, line);
    std::stringstream ss(line);

    while (ss >> word) {
      words.push_back(word);
    }

    //std::cout << "Number of words: " << words.size() << std::endl;
  }
}
