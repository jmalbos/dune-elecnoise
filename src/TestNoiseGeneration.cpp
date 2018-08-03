// -----------------------------------------------------------------------------
// File     : TestNoiseGeneration.cpp
// Info     :
// Authors  : Babak Abi, Justo Martin-Albo, Miquel Nebot
// Creation : 3 Aug 2018
// -----------------------------------------------------------------------------

#include "fnoise.h"
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
  std::vector<std::vector<double>> v;
  reader.ReadEvent(v);

  // Create here a noise generator object
  // NoiseGenerator generator;

  // generator.Generate(v);

  // NoiseGenerator generator;
  // generator.Do(v);

  // NoiseGenerator generator;
  // generator.Do(v);


  // Write new waveforms to disk
  // FileWriter writer;
  // writer.WriteEvent(v);

  return EXIT_SUCCESS;
}
