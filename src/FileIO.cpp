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
  // Start reading a line from the file storing it in the string buffer
  std::string buffer_;
  std::getline(file_, buffer_);

  while (!file_.eof()) {

    // We'll split now the line in words using a stream
    std::stringstream ss(buffer_);

    // The first two elements in every line are the event number
    // and the channel number
    int event_number, channel_number;
    ss >> event_number >> channel_number;

    // The remaining elements are the waveform samples
    double sample;
    std::vector<double> waveform;

    while (ss >> sample) waveform.push_back(sample);

    // Try to read the next line now to check whether we've reached the eof
    std::getline(file_, buffer_);
  }
}
