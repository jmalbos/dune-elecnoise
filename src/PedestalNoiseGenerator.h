/// ----------------------------------------------------------------------------
/// File     : PedestalNoiseGenerator.cpp
/// Author   : Miquel Nebot
/// Creation : 3 Oct 2018
/// ----------------------------------------------------------------------------

#ifndef PEDESTAL_NOISE_GENERATOR
#define PEDESTAL_NOISE_GENERATOR

#include <fstream>
#include <vector>


class PedestalNoiseGenerator
{
public:
  PedestalNoiseGenerator();
  ~PedestalNoiseGenerator();

  void Generate(std::vector<std::vector<double>>&);


};
#endif