#include "HarmonicNoiseGenerator.h"

#include <iostream>


/*
To debug the harmonic noise generator
*/

int main(int argc, char const *argv[])
{
  std::cout << "Start TestHarmonicNoiseGenerator" << std::endl;
 
  std::vector<std::vector<double> > v(2, std::vector<double>(4492));
  
  HarmonicNoiseGenerator generator;
  double a=1.1, phi=0.86;
  std::pair<int,int> UChannels (800,40); //Channel arrangement in FEB
  std::pair<int,int> VChannels (800,40);
  std::pair<int,int> XChannels (960,48);
  generator.Generate(v, a, phi, UChannels, VChannels, XChannels);

  return 0;
}
