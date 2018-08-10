/// ----------------------------------------------------------------------------
/// File     : HarmonicNoiseGenerator.cpp
/// Author   : Miquel Nebot
/// Creation : 3 August 2018
/// ----------------------------------------------------------------------------

#include "HarmonicNoiseGenerator.h"

#include <vector>
#include <math.h>


HarmonicNoiseGenerator::HarmonicNoiseGenerator(){}

HarmonicNoiseGenerator::~HarmonicNoiseGenerator(){}

void HarmonicNoiseGenerator::Generate(std::vector< std::vector<double> >& samples, double a, double phi)
{	

std::vector<double> v_noise;

	//for (int i = 0; i < samples.size(); i++){ //channel loop//
	for (std::vector<std::vector<double>>::iterator it = samples.begin() ; it != samples.end(); ++it)
		
	{
		 if (std::distance(samples.begin(), it) <1600) 	//UChannels [0,799] + VChannels [800,1599] 40 channesl per FEMB//
	 	{
	 		if (std::distance(samples.begin(), it) % 40 ==0)
	 		{
		 	v_noise = Sinusoidal(a,phi);
	 		}
	 		
	 		for (int i = 0; i < 4492; i++)
	 		samples[std::distance(samples.begin(), it)][i]=	 samples[std::distance(samples.begin(), it)][i] + v_noise[i];
	 	
	 	}
	 	else 			//XChannels [1600,2560] 48 channesl per FEMB//
	 	{
			if (std::distance(samples.begin(), it)-1600 % 48 ==0)
	 		{
		 	v_noise = Sinusoidal(a,phi);
	 		}
	 		
	 		for (int i = 0; i < 4492; i++)
	 		samples[std::distance(samples.begin(), it)][i]=	 samples[std::distance(samples.begin(), it)][i] + v_noise[i];

	 	}

	}

	
}	


std::vector<double> HarmonicNoiseGenerator::Sinusoidal(double a, double phi)
{
	std::vector<double> v;
    //v.reserve(samples[0].size());
    v.reserve(4492);
    double x,y;
    for (std::vector<double>::iterator it = v.begin() ; it != v.end(); ++it){
		x = rand() % 4492; //4492 == vector.size(); // ADC number of samples or number of time ticks //
		y = a * sin(x + phi);
		v.push_back(y);
	}
	return v;

}
