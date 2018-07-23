/// ----------------------------------------------------------------------------
/// File     : TestFileIO.cpp
/// Author   : Justo Martin-Albo
/// Creation : 9 July 2018
/// ----------------------------------------------------------------------------

#include "FileIO.h"

#include <iostream>


void PrintUsage(int argc, char const *argv[])
{
  std::cerr << "\n   Usage: " << argv[0] << " <input_file>\n" << std::endl;
  std::exit(EXIT_FAILURE);
}


int main(int argc, char const *argv[])
{
  if (argc < 2) PrintUsage(argc, argv);

  // We'll assume that the second command-line parameter is a valid input file
  FileReader reader(argv[1]);

  for (int i=0; i<100; ++i) reader.ReadEvent();

  return EXIT_SUCCESS;
}
