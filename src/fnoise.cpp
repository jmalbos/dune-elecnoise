# include <cstdlib>
# include <cmath>
# include <ctime>
# include <cstring>
# include <iostream>
# include <iomanip>

using namespace std;

# include "fnoise.h"


/*
   Purpose:
     F_ALPHA generates a 1/F^ALPHA noise sequence.
   Discussion:
     Thanks to Miro Stoyanov for pointing out that the second half of
     the data returned by the inverse Fourier transform should be
     discarded, 24 August 2010.
   Reference:

     Jeremy Kasdin,
     Discrete Simulation of Colored Noise and Stochastic Processes
     and 1/f^a Power Law Noise Generation,
     Proceedings of the IEEE,
     Volume 83, Number 5, 1995, pages 802-827.

   Parameters:

     Input, int N, the number of samples of the noise to generate.

     Input, double Q_D, the variance of the noise.

     Input, double ALPHA, the exponent for the noise.

     Input/output, int *SEED, a seed for the random number generator.

     Output, double F_ALPHA[N], a sequence sampled with the given
     power law. */


double *f_alpha ( int n, double q_d, double alpha, int *seed ) {
  double *h_a;
  double h_azero;
  double *h_b;
  double *hfa;
  int i;
  double *w_a;
  double w_azero;
  double *w_b;
  double *wfa;
  double wi;
  double wr;
  double *x;
  double *x2;
//
//  Set the deviation of the noise.
//
  q_d = sqrt ( q_d );
//
//  Generate the coefficients Hk.
//
  hfa = new double[2*n];
  hfa[0] = 1.0;
  for ( i = 1; i < n; i++ )
  {
    hfa[i] = hfa[i-1]
      * ( 0.5 * alpha + ( double ) ( i - 1 ) ) / ( ( double ) ( i ) );
  }
  for ( i = n; i < 2 * n; i++ )
  {
    hfa[i] = 0.0;
  }
//
//  Fill Wk with white noise.
//
  wfa = new double[2*n];

  for ( i = 0; i < n; i++ )
  {
    wfa[i] = q_d * r8_normal_01 ( seed );
  }
  for ( i = n; i < 2 * n; i++ )
  {
    wfa[i] = 0.0;
  }
//
//  Perform the discrete Fourier transforms of Hk and Wk.
//
  h_a = new double[n];
  h_b = new double[n];

  r8vec_sftf ( 2 * n, hfa, &h_azero, h_a, h_b );

  w_a = new double[n];
  w_b = new double[n];

  r8vec_sftf (  2 * n, wfa, &w_azero, w_a, w_b );
//
//  Multiply the two complex vectors.
//
  w_azero = w_azero * h_azero;

  for ( i = 0; i < n; i++ )
  {
    wr = w_a[i];
    wi = w_b[i];
    w_a[i] = wr * h_a[i] - wi * h_b[i];
    w_b[i] = wi * h_a[i] + wr * h_b[i];
  }
//
//  This scaling is introduced only to match the behavior
//  of the Numerical Recipes code...
//
  w_azero = w_azero * 2 * n;
  for ( i = 0; i < n - 1; i++ )
  {
    w_a[i] = w_a[i] * n;
    w_b[i] = w_b[i] * n;
  }
  i = n - 1;
  w_a[i] = w_a[i] * 2 * n;
  w_b[i] = w_b[i] * 2 * n;
//
//  Take the inverse Fourier transform of the result.
//
  x2 = r8vec_sftb ( 2 * n, w_azero, w_a, w_b );
//
//  Only return the first N inverse Fourier transform values.
//
  x = new double[n];
  for ( i = 0; i < n; i++ )
  {
    x[i] = x2[i];
  }

  delete [] h_a;
  delete [] h_b;
  delete [] hfa;
  delete [] w_a;
  delete [] w_b;
  delete [] wfa;
  delete [] x2;

  return x;
}
//****************************************************************************80

double r8_normal_01 ( int *seed )

//****************************************************************************80
//
//  Purpose:
//
//    R8_NORMAL_01 returns a unit pseudonormal R8.
//
//    The standard normal probability distribution function (PDF) has
//    mean 0 and standard deviation 1.
//
//    Because this routine uses the Box Muller method, it requires pairs
//    of uniform random values to generate a pair of normal random values.
//    This means that on every other call, the code can use the second
//    value that it calculated.
//
//    However, if the user has changed the SEED value between calls,
//    the routine automatically resets itself and discards the saved data.
//  Parameters:
//
//    Input/output, int *SEED, a seed for the random number generator.
//
//    Output, double R8_NORMAL_01, a normally distributed random value.
//
{
# define PI 3.141592653589793

  double r1;
  double r2;
  static int seed1 = 0;
  static int seed2 = 0;
  static int seed3 = 0;
  static int used = 0;
  double v1;
  static double v2 = 0.0;
//
//  If USED is odd, but the input SEED does not match
//  the output SEED on the previous call, then the user has changed
//  the seed.  Wipe out internal memory.
//
  if ( ( used % 2 ) == 1 )
  {
    if ( *seed != seed2 )
    {
      used = 0;
      seed1 = 0;
      seed2 = 0;
      seed3 = 0;
      v2 = 0.0;
    }
  }
//
//  If USED is even, generate two uniforms, create two normals,
//  return the first normal and its corresponding seed.
//
  if ( ( used % 2 ) == 0 )
  {
    seed1 = *seed;

    r1 = r8_uniform_01 ( seed );

    if ( r1 == 0.0 )
    {
      cerr << "\n";
      cerr << "R8_NORMAL_01 - Fatal error!\n";
      cerr << "  R8_UNIFORM_01 returned a value of 0.\n";
      exit ( 1 );
    }

    seed2 = *seed;
    r2 = r8_uniform_01 ( seed );
    seed3 = *seed;
    *seed = seed2;

    v1 = sqrt ( - 2.0 * log ( r1 ) ) * cos ( 2.0 * PI * r2 );
    v2 = sqrt ( - 2.0 * log ( r1 ) ) * sin ( 2.0 * PI * r2 );
  }
//
//  If USED is odd (and the input SEED matched the output value from
//  the previous call), return the second normal and its corresponding seed.
//
  else
  {
    v1 = v2;
    *seed = seed3;
  }

  used = used + 1;

  return v1;
# undef PI
}
//****************************************************************************80

string r8_to_string ( double r8, string format )

//****************************************************************************80
//    R8_TO_STRING converts an R8 to a C++ string.
//
//  Parameters:
//
//    Input, double R8, a double.
//
//    Input, string FORMAT, the format string.
//
//    Output, string R8_TO_STRING, the string.
//
{
  char r8_char[80];
  string r8_string;

  sprintf ( r8_char, format.c_str ( ), r8 );

  r8_string = string ( r8_char );

  return r8_string;
}

//****************************************************************************80

double r8_uniform_01 ( int *seed )

//****************************************************************************80
//    This routine implements the recursion
//
//      seed = ( 16807 * seed ) mod ( 2^31 - 1 )
//      u = seed / ( 2^31 - 1 )
//
//    The integer arithmetic never requires more than 32 bits,
//    including a sign bit.
//
//    If the initial seed is 12345, then the first three computations are
//
//      Input     Output      R8_UNIFORM_01
//      SEED      SEED
//
//         12345   207482415  0.096616
//     207482415  1790989824  0.833995
//    1790989824  2035175616  0.947702
 //  Parameters:
//
//    Input/output, int *SEED, the "seed" value.  Normally, this
//    value should not be 0.  On output, SEED has been updated.
//
//    Output, double R8_UNIFORM_01, a new pseudorandom variate,
//    strictly between 0 and 1.
//
{
  int i4_huge = 2147483647;
  int k;
  double r;

  if ( *seed == 0 )
  {
    cerr << "\n";
    cerr << "R8_UNIFORM_01 - Fatal error!\n";
    cerr << "  Input value of SEED = 0.\n";
    exit ( 1 );
  }

  k = *seed / 127773;

  *seed = 16807 * ( *seed - k * 127773 ) - k * 2836;

  if ( *seed < 0 )
  {
    *seed = *seed + i4_huge;
  }
//
//  Although SEED can be represented exactly as a 32 bit integer,
//  it generally cannot be represented exactly as a 32 bit real number.
//
  r = ( double ) ( *seed ) * 4.656612875E-10;

  return r;
}
//****************************************************************************80

void r8vec_print ( int n, double a[], string title )

//****************************************************************************80
//
//
//    R8VEC_PRINT prints an R8VEC.
//
//
//    An R8VEC is a vector of R8's.
//
//  Parameters:
//
//    Input, int N, the number of components of the vector.
//
//    Input, double A[N], the vector to be printed.
//
//    Input, string TITLE, a title.
//
{
  int i;

  cout << "\n";
  cout << title << "\n";
  cout << "\n";
  for ( i = 0; i < n; i++ )
  {
    cout << "  " << setw(8)  << i
         << ": " << setw(14) << a[i]  << "\n";
  }

  return;
}
//****************************************************************************80

void r8vec_print_part ( int n, double a[], int max_print, string title )

//****************************************************************************80
//
//
//    R8VEC_PRINT_PART prints "part" of an R8VEC.
//
//
//    The user specifies MAX_PRINT, the maximum number of lines to print.
//
//    If N, the size of the vector, is no more than MAX_PRINT, then
//    the entire vector is printed, one entry per line.
//
//    Otherwise, if possible, the first MAX_PRINT-2 entries are printed,
//    followed by a line of periods suggesting an omission,
//    and the last entry.
//
//  Parameters:
//
//    Input, int N, the number of entries of the vector.
//
//    Input, double A[N], the vector to be printed.
//
//    Input, int MAX_PRINT, the maximum number of lines
//    to print.
//
//    Input, string TITLE, a title.
//
{
  int i;

  if ( max_print <= 0 )
  {
    return;
  }

  if ( n <= 0 )
  {
    return;
  }

  cout << "\n";
  cout << title << "\n";
  cout << "\n";

  if ( n <= max_print )
  {
    for ( i = 0; i < n; i++ )
    {
      cout << "  " << setw(8) << i
           << "  " << setw(14) << a[i] << "\n";
    }
  }
  else if ( 3 <= max_print )
  {
    for ( i = 0; i < max_print - 2; i++ )
    {
      cout << "  " << setw(8) << i
           << ": " << setw(14) << a[i] << "\n";
    }
    cout << "  ......  ..............\n";
    i = n - 1;
    cout << "  " << setw(8) << i
         << ": " << setw(14) << a[i] << "\n";
  }
  else
  {
    for ( i= 0; i < max_print - 1; i++ )
    {
      cout << "  " << setw(8) << i
           << ": " << setw(14) << a[i] << "\n";
    }
    i = max_print - 1;
    cout << "  " << setw(8) << i
         << ": " << setw(14) << a[i]
         << "  " << "...more entries...\n";
  }

  return;
}
//****************************************************************************80

double *r8vec_sftb ( int n, double azero, double a[], double b[] )

//****************************************************************************80
//
//
//    R8VEC_SFTB computes a "slow" backward Fourier transform of real data.
//
//
//    SFTB and SFTF are inverses of each other.  If we begin with data
//    AZERO, A, and B, and apply SFTB to it, and then apply SFTF to the
//    resulting R vector, we should get back the original AZERO, A and B.
//
//
//  Parameters:
//
//    Input, int N, the number of data values.
//
//    Input, double AZERO, the constant Fourier coefficient.
//
//    Input, double A[N/2], B[N/2], the Fourier coefficients.
//
//    Output, double SFTB[N], the reconstructed data sequence.
//
{
  int i;
  int k;
  double pi = 3.141592653589793;
  double *r;
  double theta;

  r = new double[n];

  for ( i = 0; i < n; i++ )
  {
    r[i] = azero;
    for ( k = 0; k < ( n / 2 ); k++ )
    {
      theta = ( double ) ( ( k + 1 ) * i * 2 ) * pi / ( double ) ( n );
      r[i] = r[i] + a[k] * cos ( theta ) + b[k] * sin ( theta );
    }
  }

  return r;
}
//****************************************************************************80

void r8vec_sftf ( int n, double r[], double *azero, double a[], double b[] )

//****************************************************************************80
//
//    R8VEC_SFTF computes a "slow" forward Fourier transform of real data.
//
//
//    SFTF and SFTB are inverses of each other.  If we begin with data
//    R and apply SFTB to it, and then apply SFTB to the resulting AZERO,
//    A, and B, we should get back the original R.
//
//  Parameters:
//
//    Input, int N, the number of data values.
//
//    Input, double R[N], the data to be transformed.
//
//    Output, double *AZERO, = sum ( 1 <= I <= N ) R(I) / N.
//
//    Output, double A[N/2], B[N/2], the Fourier coefficients.
//
{
  int i;
  int j;
  double pi = 3.141592653589793;
  double theta;

  *azero = 0.0;
  for ( i = 0; i < n; i++ )
  {
    *azero = *azero + r[i];
  }
  *azero = *azero / ( double ) ( n );

  for ( i = 0; i < ( n / 2 ); i++ )
  {
    a[i] = 0.0;
    b[i] = 0.0;

    for ( j = 0; j < n; j++ )
    {
      theta = ( double ) ( 2 * ( i + 1 ) * j ) * pi / ( double ) ( n );
      a[i] = a[i] + r[j] * cos ( theta );
      b[i] = b[i] + r[j] * sin ( theta );
    }

    a[i] = a[i] / ( double ) ( n );
    b[i] = b[i] / ( double ) ( n );

    if ( ( n % 2 ) == 1 || i != ( n / 2 - 1 ) )
    {
      a[i] = 2.0 * a[i];
      b[i] = 2.0 * b[i];
    }
  }
  return;
}
//****************************************************************************80

void timestamp ( )
{
//****************************************************************************80
//
//
//    TIMESTAMP prints the current YMDHMS date as a time stamp.
//
  return;
# undef TIME_SIZE
}
