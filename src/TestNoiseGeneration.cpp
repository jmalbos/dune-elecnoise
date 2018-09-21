// -----------------------------------------------------------------------------
// File     : TestNoiseGeneration.cpp
// Info     :
// Authors  : Babak Abi, Justo Martin-Albo, Miquel Nebot
// Creation : 3 Aug 2018
// -----------------------------------------------------------------------------

#include "FileIO.h" //file handling
#include "fnoise.h" //generate the colored noise. To be repalced by PinkNoiseGenerator
#include "HarmonicNoiseGenerator.h" //generate the harmonic noise

#include "PinkNoiseGenerator.h"

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

  std::pair<int,int> UChannels (800,40); //Channel arrangement in FEB
  std::pair<int,int> VChannels (800,40);
  std::pair<int,int> XChannels (960,48);

  // Create here a noise generator object
  // PinkNoiseGenerator
  //PinkNoiseGenerator generator;
  //generator.Generate(v);

  // HarmonicNoiseGenerator
  HarmonicNoiseGenerator generator;
  double a=1.1, phi=0.86;
  generator.Generate(v, a, phi, UChannels, VChannels, XChannels);



  // NoiseGenerator generator;
  // generator.Do(v);


  // Write new waveforms to disk
  FileWriter writer(argv[2]);
  writer.WriteEvent(v);

  return EXIT_SUCCESS;
}
