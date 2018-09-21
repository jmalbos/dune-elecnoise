// -----------------------------------------------------------------------------
// File     : PinkNoiseGenerator.h
// Info     :
// Authors  : Babak Abi, Justo Martin-Albo, Miquel Nebot
// Creation : 15 July 2018
// -----------------------------------------------------------------------------

#ifndef PINK_NOISE_GENERATOR_H
#define PINK_NOISE_GENERATOR_H

#include "BaseNoiseGenerator.h"


class PinkNoiseGenerator: public BaseNoiseGenerator
{
public:
  PinkNoiseGenerator();
  virtual ~PinkNoiseGenerator();

  virtual void Generate(std::vector<std::vector<double>>&);

};

#endif
