// -----------------------------------------------------------------------------
// File     : BaseNoiseGenerator.h
// Info     :
// Authors  : Babak Abi, Justo Martin-Albo, Miquel Nebot
// Creation : 15 July 2018
// -----------------------------------------------------------------------------

#ifndef BASE_NOISE_GENERATOR_H
#define BASE_NOISE_GENERATOR_H


class BaseNoiseGenerator
{
public:
  BaseNoiseGenerator();
  virtual ~BaseNoiseGenerator();

  virtual Generate(std::vector<std::vector<double>>&) = 0;
};


#endif
