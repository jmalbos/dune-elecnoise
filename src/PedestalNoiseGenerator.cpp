/// ----------------------------------------------------------------------------
/// File     : PedestalNoiseGenerator.cpp
/// Author   : Miquel Nebot
/// Creation : 3 Oct 2018
/// ----------------------------------------------------------------------------

#include "PedestalNoiseGenerator.h"

#include <iostream>
#include <vector>


PedestalNoiseGenerator::PedestalNoiseGenerator()
{
	std::cout << "Begin PedestalNoiseGenerator module" << std::endl;
}

PedestalNoiseGenerator::~PedestalNoiseGenerator()
{

}

void PedestalNoiseGenerator::Generate(std::vector< std::vector<double> >& samples)
{	

//std::cout << "Tick samples " << samples[0].size() << std::endl;
int chanelSamples_size = samples[0].size();
//std::vector<double> v_pedestal(chanelSamples_size, 0); // init empty vector of tick samples size (4492)

//pedestal has to be implemented as colored noise alpha = 2 
//This works for 1APA input, a unique identifier of U,V or X channel better than number has to be defined

std::cout << "Begin channel loop of "<< samples.size() << " channels"<< std::endl; 
for (std::vector<std::vector<double>>::iterator it = samples.begin() ; it != samples.end(); ++it)	
	{
		if (std::distance(samples.begin(), it) <1600 ) //+1800ADC UVCh
	 	{
	 		
	 		for (int i = 0; i < chanelSamples_size; i++) //4492
	 			{
	 			
	 			samples[std::distance(samples.begin(), it)][i]=	 samples[std::distance(samples.begin(), it)][i] + 1800.;
	 			}
	 	}
	 	else if (std::distance(samples.begin(), it) <2560 )//+500ADC XCh
	 	{
	 		for (int i = 0; i < chanelSamples_size; i++) //4492
	 			{
	 			
	 			samples[std::distance(samples.begin(), it)][i]=	 samples[std::distance(samples.begin(), it)][i] + 500.;
	 			}
	 	}
	 	else
	 	{
	 		break;
	 	}
	}
}