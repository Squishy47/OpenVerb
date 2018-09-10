//
//  Gain.hpp
//  ipReverb - All
//
//  Created by Squishy on 17/02/2018.
//  Copyright © 2018 Squishy. All rights reserved.
//

#ifndef Gain_hpp
#define Gain_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"

class Gain{
    float gain;
	LinearSmoothedValue<float> wetDrySmoother;

public:
	Gain(float inValue);
	
    void setGain(float inValue);
	
	void setFs(int Fs);

    float getGain();
    
    void process(float* samples, int bufferSize);
    
    float processSingleSample(float sample);
};

#endif /* Gain_hpp */
