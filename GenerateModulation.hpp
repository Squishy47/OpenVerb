//
//  GenerateModulation.hpp
//  ModulationGenerationTest
//
//  Created by Squishy on 25/02/2018.
//  Copyright © 2018 Squishy. All rights reserved.
//

#ifndef GenerateModulation_hpp
#define GenerateModulation_hpp

#include <stdio.h>
#include <math.h>

// USER HEADERS
#include "VecTemplate.hpp"

class GenerateModulation{
	Vec_Float buffer{44100};
	
	float 	amplitude,
			phase;
	
	int	  	readHead = 0,
			writeHead = 0,
			bufferLength,
			frequency;
	
public:
	GenerateModulation(int inFs, float inamplitude, float infrequency, float inphase);
	
	float sineCalc(float index);
		
	float read();
	
	void write(float inValue);
	
	void reCalc();
	
	void setFreq(float inFreq);
	
	void setAmplitude(float inA);
	
	void setFs(float inFs);
};

#endif /* GenerateModulation_hpp */
