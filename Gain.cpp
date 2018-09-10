//
//  Gain.cpp
//  ipReverb - All
//
//  Created by Squishy on 17/02/2018.
//  Copyright © 2018 Squishy. All rights reserved.
//

#include "Gain.hpp"


Gain::Gain(float inValue){
	gain = inValue;
}

void Gain::setGain(float inValue){
	gain = inValue;
}

void Gain::setFs(int Fs){
	wetDrySmoother.reset(Fs, 0.01);
}

float Gain::getGain(){
    return wetDrySmoother.getNextValue();
}

void Gain::process(float* samples, int bufferSize){
    for(int i = 0; i < bufferSize; i++)
        samples[i] = processSingleSample(samples[i]);
}

float Gain::processSingleSample(float sample){
	wetDrySmoother.setValue(gain);
    return sample * wetDrySmoother.getNextValue();
}
