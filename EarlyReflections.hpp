//
//  EarlyReflections.hpp
//  ERTest
//
//  Created by Squishy on 17/02/2018.
//  Copyright © 2018 Squishy. All rights reserved.
//

#ifndef EarlyReflections_hpp
#define EarlyReflections_hpp

//USER HEADERS
#include "CircularBuffer.hpp"
#include "VecTemplate.hpp"
#include "../JuceLibraryCode/JuceHeader.h"

class EarlyReflections{
	Vec_IIR HShelf;
	std::vector<IIRCoefficients> HShelfCoefs;

	
	CircularBuffer buffers[6] = {	CircularBuffer(51000), CircularBuffer(51000), CircularBuffer(51000),
									CircularBuffer(51000), CircularBuffer(51000), CircularBuffer(51000)};
	Random randomNum;
	
	float roomDimensions [6][3] = {
		//L		  W	      H
		{2.4f,   3.1f,   2.0f},  //W: 2.4,   L: 3.1,    H: 2.0,
		{3.2f,   4.5f,   2.4f},  //W: 3.2,   L: 4.5,    H: 2.4,
		{12.0f,  17.0f,  9.5f},  //W: 12.0,  L: 17.0,   H: 9.5,
		{16.53f, 34.2f,  13.5f}, //W: 16.53, L: 34.23,  H: 13.47,
		{23.0f,  390.0f, 25.0f}, //W: 23.0,  L: 390.0,  H: 25.0,
		{0.0f,   0.0f,   0.0f},  // Random
	};
	
	float mixingMatrix[2][8] = {
		{1, 1.01, 0.99, -1, -1, -0.99, 1.01, -1},
		{-1, -0.99, 1.01, -1, 1, 1.01, 0.99, -1}
	};
	
	float movementMatrix[2][8];
	
	
	
	float taps[6] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	
	float roomMovement[3] = {0.5f, 0.5f, 0.5f};

	int currentSelection = 0,
		numOfTaps = 6,
	 	runOnce = 0,
		Fs = 44100;
public:
    EarlyReflections();
    
    void process				(float* samples, int bufferSize, int channel);
    float processSingleSample	(float sample, int channel);
    void setSize				(int selector);
    void setFs					(int inValue);
	void setRandomSeed			(int inValue);
	void setRoomPosition		(float inValue, int selector);
	void createFilters			();
	
	float getRoomDimensions		(int selector);
	
	
};

#endif /* EarlyReflections_hpp */
