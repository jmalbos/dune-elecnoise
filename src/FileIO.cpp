/// ----------------------------------------------------------------------------
/// File     : FileIO.cpp
/// Author   : Justo Martin-Albo
/// Creation : 9 July 2018
/// ----------------------------------------------------------------------------

#include "FileIO.h"

#include <vector>
#include <sstream>
#include <iostream>


////////////////////////////////////////////////////////////////////////////////

FileReader::FileReader(std::string filename)
{
  file_.open(filename, std::fstream::in);
  if (file_.is_open())
    std::cout << "[FileReader] File opened successfully." << std::endl;
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

    samples.push_back(std::move(waveform));

    // Try to read the next line now to check whether we've reached the eof
    std::getline(file_, buffer_);
  }
}

////////////////////////////////////////////////////////////////////////////////

FileWriter::FileWriter(std::string filename)
{
  file_.open(filename, std::fstream::out);
  if (file_.is_open())
    std::cout << "[FileWriter] File opened successfully." << std::endl;
}


FileWriter::~FileWriter()
{
  file_.close();
}


void FileWriter::WriteEvent(std::vector<std::vector<double>>& samples)
{
  // TODO: Consider more than one event per file
  int event_number = 0;

  // Loop through the channels
  int channel_id = 0;
  for (const std::vector<double>& channel: samples) {

    file_ << event_number << " " << channel_id << " ";

    for (double sample: channel) {
      file_ << sample << " ";
    }

    file_ << std::endl;
    ++channel_id;
  }
}

////////////////////////////////////////////////////////////////////////////////
