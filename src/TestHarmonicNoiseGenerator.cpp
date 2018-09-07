#include "HarmonicNoiseGenerator.h"

#include <iostream>


/*void PrintUsage(std::vector< std::vector<double> >& samples, double a, double phi)
{
  std::cerr << "\n   Usage: " << samples << " <vector of vectors>\n" << a << 'amplitude\n' << std::endl;
  std::exit(EXIT_FAILURE);
}
*/

int main(int argc, char const *argv[])
{
  std::cout << "Start TestHarmonicNoiseGenerator" << std::endl;
  //std::vector<std::vector<double>> v;
  std::vector<std::vector<double> > v(2, std::vector<double>(4492));
  //v[0] = [0.,0.,0.,0.];  //[1.,1.,1.,1.];
  HarmonicNoiseGenerator generator;
  double a=1.1, phi=0.86;
  generator.Generate(v, a, phi);

  return 0;
}
/*}(std::vector< std::vector<double> >& samples, double a, double phi)
{
  //if (argc < 2) PrintUsage(argc, argv);

  // We'll assume that the second command-line parameter is a valid input file
  FileReader reader(argv[1]);
  std::vector<std::vector<double>> v;
  reader.ReadEvent(v);

  FileWriter writer("test.txt");
  writer.WriteEvent(v);
  
  HarmonicNoiseGenerator generator;
  double a=1.1, phi=0.86;
  generator.Generate(v, a, phi);
  

  return EXIT_SUCCESS;
}*/