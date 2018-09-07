/// ----------------------------------------------------------------------------
/// File     : HarmonicNoiseGenerator.cpp
/// Author   : Miquel Nebot
/// Creation : 3 August 2018
/// ----------------------------------------------------------------------------

#include "HarmonicNoiseGenerator.h"

#include <iostream>
#include <vector>
#include <math.h>



HarmonicNoiseGenerator::HarmonicNoiseGenerator(){}

HarmonicNoiseGenerator::~HarmonicNoiseGenerator(){}

void HarmonicNoiseGenerator::Generate(std::vector< std::vector<double> >& samples, double a, double phi)
{	
std::cout << "Begin HarmonicNoiseGenerator module" << std::endl;
std::vector<double> v_noise(4492, 0);

/*std::cout << "TEST THE v_noise" << std::endl;
for ( std::vector<std::vector<int>>::size_type i = 0; i < v_noise.size(); i++ )
	{
	std::cout << v_noise[i] << ' ';
   	}
   	std::cout << std::endl;

std::cout << "Call Sinusoidal" << std::endl;
v_noise = Sinusoidal(a,phi);


std::cout << "Check v_noise" << std::endl;
for ( std::vector<std::vector<int>>::size_type i = 0; i < v_noise.size(); i++ )
	{
	std::cout << v_noise[i] << ' ';
   	}
   	std::cout << std::endl;
*/
//for (int i = 0; i < samples.size(); i++){std::cout << samples[i] << std::endl;}//channel loop//

for (std::vector<std::vector<double>>::iterator it = samples.begin() ; it != samples.end(); ++it)	
	{
		std::cout << "Begin channel loop" << std::endl;
		if (std::distance(samples.begin(), it) <1600) 	//UChannels [0,799] + VChannels [800,1599] 40 channesl per FEMB//
	 	{
	 		std::cout << "UChannels + VChannels"<< std::endl;
	 		if (std::distance(samples.begin(), it) % 40 ==0)
	 		{
	 		std::cout << "Generate Sinusoidal"<< std::endl;
		 	v_noise = Sinusoidal(a,phi);
		 		/*for ( std::vector<std::vector<int>>::size_type i = 0; i < v_noise.size(); i++ )
					{
					std::cout << v_noise[i] << ' ';
   					}
   				std::cout << std::endl;*/

	 		}
	 		
	 		for (int i = 0; i < 4492; i++) //4492
	 			{
	 			//std::cout << "Add the harmonic noise in channel: " << std::endl;
	 			samples[std::distance(samples.begin(), it)][i]=	 samples[std::distance(samples.begin(), it)][i] + v_noise[i];
	 			}
	 	}
	 	else 			//XChannels [1600,2560] 48 channesl per FEMB//
	 	{
	 		std::cout << "XChannels"<< std::endl;
			if (std::distance(samples.begin(), it)-1600 % 48 ==0)
	 		{
		 	v_noise = Sinusoidal(a,phi);
	 		}
	 		
	 		for (int i = 0; i < 4492; i++)
	 		samples[std::distance(samples.begin(), it)][i]=	 samples[std::distance(samples.begin(), it)][i] + v_noise[i];

	 	}

	}

//std::cout << v_noise << std::endl;
//for(std::vector< std::vector<int> >::iterator row = v_noise.begin(); row != v.end(); ++row) {
    //for(std::vector<int>::iterator col = row->begin(); col != row->end(); ++col) {
  //      std::cout << *row; *col;
  //  }

//TEST THE OUTPUT  
/*for ( std::vector<std::vector<int>>::size_type i = 0; i < samples.size(); i++ )
{
   for ( std::vector<int>::size_type j = 0; j < samples[i].size(); j++ )
   {
      std::cout << samples[i][j] << ' ';
   }
   std::cout << std::endl;
}
*/

}	



std::vector<double> HarmonicNoiseGenerator::Sinusoidal(double a, double phi)
{
	//std::vector<double> v;

    //v.reserve(samples[0].size());
    std::vector<double> v(4492,0);
    //v.reserve(10);
        //v.reserve(4492);
    double x,y;
	std::cout << v.size() << std::endl;
    for (int i =0; i < v.size(); i++)
	{
		//std::cout << v[i] << std::endl; 
		x = rand() % 4492; //4492 == vector.size(); // ADC number of samples or number of time ticks //
		y = a * sin(x + phi);
		//std::cout << "noise value: " << y << std::endl; 
		v[i]= y;
	}
    
	return v;

}
