/// ----------------------------------------------------------------------------
/// File     : PinkNoiseGenerator.cpp
/// Author   : Justo Martin-Albo
/// Creation : 9 July 2018
/// ----------------------------------------------------------------------------

#include "PinkNoiseGenerator.h"
#include "fnoise.h"

#include <iostream>


PinkNoiseGenerator::PinkNoiseGenerator()
{
}


PinkNoiseGenerator::~PinkNoiseGenerator()
{
}


void PinkNoiseGenerator::Generate(std::vector<std::vector<double>>& v)
{
  std::cout << v.size() << std::endl;

  // Loop through channels
  for (int i=0; i<v.size(); ++i) {

    //int n = 4492;
    int n = 9;
    double q_d = 5.0;
    double alpha = 0.00;
    int seed_init = 123456789;

    double *x;

    // Loop through samples
    for (int j=0; j<v[i].size(); ++j) {
      std::cout << v[i][j] << std::endl;

      x = f_alpha ( n, q_d, alpha, &seed_init );

      v[i][j] += x[j];
      std::cout << v[i][j] << std::endl;
    }

    delete [] x;
  }

}
