/// ----------------------------------------------------------------------------
/// File     : VectorNoiseGenerator.cpp
/// Author   : Miquel Nebot
/// Creation : Oct 2018
/// ----------------------------------------------------------------------------

#ifndef VECTOR_NOISE_GENERATOR
#define VECTOR_NOISE_GENERATOR

#include <fstream>
#include <vector>


class VectorNoiseGenerator
{
public:
  VectorNoiseGenerator();
  ~VectorNoiseGenerator();

  std::vector<std::vector<double>> Generate(int NCh,int NSmpl);


};
#endif