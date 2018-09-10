//
//  LateReflections.hpp
//  LRTest
//
//  Created by Squishy on 23/02/2018.
//

#ifndef LateReflections_hpp
#define LateReflections_hpp

#include <stdio.h>
#include <iostream>
#include "../JuceLibraryCode/JuceHeader.h"

//USER HEADERS
#include "VecTemplate.hpp"
#include "CircularBuffer.hpp"
#include "GenerateModulation.hpp"

class LateReflections{
	
	int bufferSize = 2000;
	
	
	//initialise the circular buffers, 1 for each tap. couldn't figure out a way to create initialise objects inside arrays without doing it this way. Pleaseeeee could you tell me a better way to do this!?
	CircularBuffer buffers[32] = {	CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize),
									CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize),
									CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize),
									CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize),
									CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize),
									CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize),
									CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize),
									CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize), CircularBuffer(bufferSize)};
	
	IIRFilter fbLowShelfFilter[32], fbHighShelfFilter[32], fbPeakFilter[32], fixedLowShelf[32], fixedHighShelf[32];
	
	
	IIRCoefficients lowShelfCoefs, highShelfCoefs, peakCoefs, fixedLowShelfCoefs, fixedHighShelfCoefs;
	GenerateModulation modulation{44100, 1.0f, 1.0f, 0.0f};
	
	
	
	
	
	float fFc[3] = {20.f, 20.f, 20.f}, fG[3] = {1.f, 1.f, 1.f}, fQ[3] = {1.f, 1.f, 1.f};
	
	float feedback   	= 0.5f,
	
		  f1Fc 			= 1.0f,
		  f1Q 			= 1.0f,
	      f1Gain 		= 1.0f,
	
		  f2Fc 			= 1.0f,
		  f2Q 			= 1.0f,
		  f2Gain 		= 1.0f,
	
		  f3Fc 			= 1.0f,
		  f3Q 			= 1.0f,
		  f3Gain 		= 1.0f,
		  amplitude = 0;
	
	int numOfTaps = 32,
		maxTaps = 32,
	 	Fs = 44100,
		qualitySetting = 1;
	
	
	
	float	tapPoint[32],
	 		householderMatrix[32][32],
			orthogonalMatrix[32][32],
			dialSmoothing[3];
	
	
	
	//prime nums used for tap positions. 
	float primes[32] = {	353,359,367,373,379,383,389,397,
		401,409,419,421,431,433,439,443,
		449,457,461,463,467,479,487,491,
		499,503,509,521,523,541,547,557};
	
	
	float mixingMatrix[2][32] = {
		{1.f, 1.05f, -1/1.05f, -1.f, 1.f, -1/1.05f, 1.05f, -1.f,  // 8
		 1.f, -1/1.05f, 1.05f, -1.f, 1.f, 1.05f, -1/1.05f, -1.f,  // 16
		 1.f, 1.05f, -1/1.05f, -1.f, 1.f, -1/1.05f, 1.05f, -1.f,  // 24
		 1.f, -1/1.05f, 1.05f, -1.f, 1.f, 1.05f, -1/1.05f, -1.f}, // 32
		
		{1.f, -1/1.05f, 1.05f, -1.f, 1.f, 1.05f, -1/1.05f, -1.f,  // 8
		 1.f, 1.05f, -1/1.05f, -1.f, 1.f, -1/1.05f, 1.05f, -1.f,  // 16
		 1.f, -1/1.05f, 1.05f, -1.f, 1.f, 1.05f, -1/1.05f, -1.f,  // 24
		 1.f, 1.05f, -1/1.05f, -1.f, 1.f, -1/1.05f, 1.05f, -1.f}  // 32
	};

public:
	enum filterType{LowShelf, HighShelf, Peak, Notch};
	
	LateReflections();
	
	void process(float* inSample, int bufferSize, int channel);
	
	float processSingleSample(float sample, int channel);
	
	void generateMatrix();
	
	void setAPFeedback(float inValue);
	
	void setMatrixMix(float inValue);
	
	void setNumOfTaps(int inValue);
		
	void setFs(float inValue);
	
	void setFilterParams(int selector, float Fc, float gain, float Q);
	
	void createFeedbackFilters(int selector);
	
	void setLRDelayLength(float inValue);
	
	void setModRate(float inValue);
	
	void setModDepth(float inValue);
	
	void getFilterCoefs(float* coefs, int selector);
};
#endif /* LateReflections_hpp */
