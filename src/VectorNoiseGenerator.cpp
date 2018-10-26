// -----------------------------------------------------------------------------
// File     : VectorNoiseGenerator.cpp
// Info     :
// Authors  : Babak Abi, Justo Martin-Albo, Miquel Nebot
// Creation : Oct 2018
// -----------------------------------------------------------------------------
//Generates a virtual vector of noise per APA

#include "fnoise.h" //generate the colored noise. To be repalced by PinkNoiseGenerator
#include "HarmonicNoiseGenerator.h" //generate the harmonic noise
#include "PedestalNoiseGenerator.h"
#include "PinkNoiseGenerator.h"

VectorNoiseGenerator::VectorNoiseGenerator()
{
	std::cout << "Begin VectorNoiseGenerator module" << std::endl;
}

VectorNoiseGenerator::~VectorNoiseGenerator()
{
	
}

std::vector<std::vector<double>> VectorNoiseGenerator::Generate(int NCh,int NSmpl)
{
	// Create the container with the proper size (NCh, NSampl)/APA 
	std::vector<std::vector<double>> v(NCh,(NSampl,0));
	std::pair<int,int> UChannels (800,40); //Channel arrangement in FEB
	std::pair<int,int> VChannels (800,40);
	std::pair<int,int> XChannels (960,48);
	// Create here the noise generator 


	//PedestalNoiseGenerator
	PedestalNoiseGenerator generatorP;
	generatorP.Generate(v);

	// PinkNoiseGenerator
	PinkNoiseGenerator generator;
	generator.Generate(v);

	// HarmonicNoiseGenerator
	HarmonicNoiseGenerator generatorH;
	generatorH.Generate(v, UChannels, VChannels, XChannels);

	
	return v;
}