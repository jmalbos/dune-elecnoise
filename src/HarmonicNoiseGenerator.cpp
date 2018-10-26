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

void HarmonicNoiseGenerator::Generate(std::vector< std::vector<double> >& samples, std::pair<int,int> UChannels, std::pair<int,int> VChannels, std::pair<int,int> XChannels)
{	

std::cout << "Tick samples " << samples[0].size() << std::endl;
int chanelSamples_size = samples[0].size();
std::vector<double> v_noise(chanelSamples_size, 0); // init empty vector of tick samples size (4492)

std::vector<std::vector<int>> AmpFreqPh(6,std::vector<int> (3)); //number of sin (amplitude, frequency, phase)
AmpFreqPh[0][0] = 4, AmpFreqPh[0][1] = 5000, AmpFreqPh[0][2] = 1;
AmpFreqPh[1][0] = 3, AmpFreqPh[1][1] = 24000, AmpFreqPh[1][2] = 2;
AmpFreqPh[2][0] = 3, AmpFreqPh[2][1] = 110000, AmpFreqPh[2][2] = 3;
AmpFreqPh[3][0] = 2, AmpFreqPh[3][1] = 30000, AmpFreqPh[3][2] = 4;
AmpFreqPh[4][0] = 3, AmpFreqPh[4][1] = 45000, AmpFreqPh[4][2] = 5; 
AmpFreqPh[5][0] = 3, AmpFreqPh[5][1] = 55000, AmpFreqPh[5][2] = 6;
//`CohPhaseoffset = (b-a).*rand(6,1) + a`  where `b=2*pi ;  a=0 ;`



std::cout << "Begin channel loop of "<< samples.size() << " channels"<< std::endl; 
for (std::vector<std::vector<double>>::iterator it = samples.begin() ; it != samples.end(); ++it)	
	{
		if (std::distance(samples.begin(), it) < UChannels.first + VChannels.first) 	//UChannels [0,799] + VChannels [800,1599] 40 channels per FEMB//
	 	{
	 		//std::cout << "UChannels + VChannels"<< std::endl;
	 		if (std::distance(samples.begin(), it) % UChannels.second ==0)
	 		{
	 		//std::cout << "Generate Sinusoidal"<< std::endl;
		 	v_noise = Sinusoidal(chanelSamples_size, AmpFreqPh);
		 		
	 		}
	 		
	 		for (int i = 0; i < chanelSamples_size; i++) //4492
	 			{
	 			//std::cout << "Add the harmonic noise in channel: " << i << std::endl;
	 			samples[std::distance(samples.begin(), it)][i]=	 samples[std::distance(samples.begin(), it)][i] + v_noise[i]; //*1.2 80% UV over the X Channel
	 			}
	 	}
	 	else 											//XChannels [1600,2560] 48 channels per FEMB//
	 	{
	 		//std::cout << "XChannels"<< std::endl;
			if (std::distance(samples.begin(), it)-(UChannels.first + VChannels.first) % XChannels.second ==0)
	 		{
		 	v_noise = Sinusoidal(chanelSamples_size, AmpFreqPh);
	 		}
	 		
	 		for (int i = 0; i < chanelSamples_size; i++)
	 		samples[std::distance(samples.begin(), it)][i]=	 samples[std::distance(samples.begin(), it)][i] + v_noise[i];
	 	}
	}
}	


std::vector<double> HarmonicNoiseGenerator::Sinusoidal(int chanelSamples_size, std::vector< std::vector<int> > AmpFreqPh)

{

    //v.reserve(samples[0].size());
    std::vector<double> v(chanelSamples_size,0);
    //v.reserve(4492);
    double x,y;
	//std::cout << v.size() << std::endl;
    for (int s =0; s < v.size(); s++)
	{
		//std::cout <<"S "<< s << std::endl; 
		//x = rand() % 4492; //4492 == vector.size(); // ADC number of samples or number of time ticks //
		//y = a * sin(x + phi);
		
		for (int i = 0; i < AmpFreqPh.size(); ++i)
		{
		v[s]+= AmpFreqPh[i][0]* sin(double(AmpFreqPh[i][1]* i + AmpFreqPh[i][2]));
		
		//std::cout << "noise value: " << v[s]<< std::endl; 
		}
		
	}
    
	return v;

}
