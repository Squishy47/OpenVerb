//
//  PreDelay.cpp
//  PreDelayTest - All
//
//  Created by Squishy on 15/02/2018.
//

#include "PreDelay.hpp"

// USER HEADERS
#include "CircularBuffer.hpp"

PreDelay::PreDelay(){
    setDelayLength(25);
	Fs = 44100;
}

void PreDelay::process(float* samples, int bufferSize){
    for(int i = 0; i < bufferSize; i++)
        samples[i] = processSingleSample(samples[i]);
}

float PreDelay::processSingleSample(float sample){
    buffer.write(sample);
    return buffer.readCubic(delayLength - 1);
}

void PreDelay::setDelayLength(float inValue){
    inValue = (inValue / 1000) * Fs;
	
    if(inValue > buffer.getBufferLength())
        delayLength = buffer.getBufferLength();
    else if (inValue < 1.0)
        delayLength = 1.0;
    else
        delayLength = inValue;
}

float PreDelay::getDelayLength(){
    return delayLength;
}

void PreDelay::setFs(int sampleRate){
    Fs = sampleRate;
	setDelayLength(delayLength);
}
