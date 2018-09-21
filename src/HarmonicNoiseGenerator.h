/// ----------------------------------------------------------------------------
/// File     : HarmonicNoiseGenerator.cpp
/// Author   : Miquel Nebot
/// Creation : 3 August 2018
/// ----------------------------------------------------------------------------

#ifndef HARMONIC_NOISE_GENERATOR
#define HARMONIC_NOISE_GENERATOR

#include <fstream>
#include <vector>


class HarmonicNoiseGenerator
{
public:
  HarmonicNoiseGenerator();
  ~HarmonicNoiseGenerator();

  void Generate(std::vector<std::vector<double>>&, double a, double phi, std::pair<int,int> UChannels, std::pair<int,int> VChannels, std::pair<int,int> XChannels);

private:
  std::vector<double> Sinusoidal(double a, double phi);
};
#endif