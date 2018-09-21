/// ----------------------------------------------------------------------------
/// File     : HarmonicNoiseGenerator.cpp
/// Author   : Miquel Nebot
/// Creation : 3 August 2018
/// ----------------------------------------------------------------------------

#include "HarmonicNoiseGenerator.h"

#include <iostream>
#include <vector>
#include <math.h>



HarmonicNoiseGenerator::HarmonicNoiseGenerator()
{
	std::cout << "Begin HarmonicNoiseGenerator module" << std::endl;
}

HarmonicNoiseGenerator::~HarmonicNoiseGenerator()
{

}

void HarmonicNoiseGenerator::Generate(std::vector< std::vector<double> >& samples, double a, double phi, std::pair<int,int> UChannels, std::pair<int,int> VChannels, std::pair<int,int> XChannels)
{	

std::cout << "Tick samples " << samples[0].size() << std::endl;
int chanelSamples_size = samples[0].size();
std::vector<double> v_noise(chanelSamples_size, 0); // init empty vector of tick samples size (4492)



std::cout << "Begin channel loop of "<< samples.size() << " channels"<< std::endl; 
for (std::vector<std::vector<double>>::iterator it = samples.begin() ; it != samples.end(); ++it)	
	{
		if (std::distance(samples.begin(), it) < UChannels.first + VChannels.first) 	//UChannels [0,799] + VChannels [800,1599] 40 channels per FEMB//
	 	{
	 		//std::cout << "UChannels + VChannels"<< std::endl;
	 		if (std::distance(samples.begin(), it) % UChannels.second ==0)
	 		{
	 		//std::cout << "Generate Sinusoidal"<< std::endl;
		 	v_noise = Sinusoidal(a,phi);
		 		
	 		}
	 		
	 		for (int i = 0; i < chanelSamples_size; i++) //4492
	 			{
	 			//std::cout << "Add the harmonic noise in channel: " << std::endl;
	 			samples[std::distance(samples.begin(), it)][i]=	 samples[std::distance(samples.begin(), it)][i] + v_noise[i];
	 			}
	 	}
	 	else 											//XChannels [1600,2560] 48 channels per FEMB//
	 	{
	 		//std::cout << "XChannels"<< std::endl;
			if (std::distance(samples.begin(), it)-(UChannels.first + VChannels.first) % XChannels.second ==0)
	 		{
		 	v_noise = Sinusoidal(a,phi);
	 		}
	 		
	 		for (int i = 0; i < chanelSamples_size; i++)
	 		samples[std::distance(samples.begin(), it)][i]=	 samples[std::distance(samples.begin(), it)][i] + v_noise[i];
	 	}
	}
}	


std::vector<double> HarmonicNoiseGenerator::Sinusoidal(double a, double phi)
{
    //v.reserve(samples[0].size());
    std::vector<double> v(4492,0);
    //v.reserve(4492);
    double x,y;
	//std::cout << v.size() << std::endl;
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
