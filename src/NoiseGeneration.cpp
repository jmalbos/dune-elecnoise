// -----------------------------------------------------------------------------
// File     : NoiseGeneration.cpp
// Info     :
// Authors  : Babak Abi, Justo Martin-Albo, Miquel Nebot
// Creation : Oct 2018
// -----------------------------------------------------------------------------

#include "FileIO.h" //file handling

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

  //Obtain the number of APAs, number of Channels, number of samples
  int NAPA=1;
  int NCh=2560;
  int NSmpl=4492;
 
  //Loop per APA
  //for (int i=0, i<NAPA,i++){
  //Generate noise vector of vector per APA
  VectorNoiseGenerator generator;
  //Add the vector noise to the waveform readed
  v = v + generator.Generate(NCh,NSmpl);
  //}
  

  // Write new waveforms to disk
  FileWriter writer(argv[2]);
  writer.WriteEvent(v);

  return EXIT_SUCCESS;
}
