# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
# include <string>
# include <fstream>
# include <ctime>

using namespace std;

# include "fnoise.h"

int main ( );
void test01 ( int n, double q_d, double alpha, int seed );


int main ( ){
  double alpha;
  int i;
  int n;
  double q_d;
  int seed_init;

  timestamp ( );
  cout << "\n";
  cout << "hey Babak this is noise you like \n";
  cout << "  C++ version\n";
  cout << "  Test the fnoise library.\n";

  n = 128;
  q_d = 1.0;
  alpha = 0.00;
  seed_init = 123456789;

  for ( i = 0; i <= 8; i++ )
  {
    alpha = 0.25 * i;
    test01 ( n, q_d, alpha, seed_init );
  }
//
//  finished.
//
  cout << "\n";
  cout << "1/f noise :\n";
  cout << "  Normal end of execution.\n";
  cout << "\n";
  timestamp ( );

  return 0;
}
//****************************************************************************80
//****************************************************************************80
 /*
 for Babak use as bellow :
   Purpose:
     TEST01 calls F_ALPHA with particular parameters.
   Parameters:
     Input, int N, the number of elements of the sequence to generate.
     Input, double Q_D, the variance of the sequence.
     Input, double ALPHA, the exponent of the power law.
     Input, int SEED_INIT, the initial seed for the random number generator.
 */
void test01 ( int n, double q_d, double alpha, int seed_init ) {
  int i;
  string output_filename;
  ofstream output_unit;
  int seed;
  double *x;

  output_filename = "alpha_" + r8_to_string ( alpha, "%4.2f"  ) + ".txt";
//
//  Report parameters.
//
  cout << "\n";
  cout << "TEST01:\n";
  cout << "  Generating " << n << " sample points.\n";
  cout << "  1/F^ALPHA noise has ALPHA = " << alpha << "\n";
  cout << "  Variance is " << q_d << "\n";
  cout << "  Initial random number seed = " << seed_init << "\n";

  seed = seed_init;

  x = f_alpha ( n, q_d, alpha, &seed );
//
//  Print no more than 10 entries of the data.
//
  r8vec_print_part ( n, x, 10, "  Noise sample:" );
//
//  Write the data to a file.
//
  output_unit.open ( output_filename.c_str ( ) );

  for ( i = 0; i < n; i++ )
  {
    output_unit << x[i] << "\n";
  }
  output_unit.close ( );

  cout << "  Data written to file \"" << output_filename << "\"\n";

  delete [] x;

  return;
}
