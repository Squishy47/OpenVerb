//
//  PreDelay.hpp
//  PreDelayTest - All
//
//  Created by Squishy on 15/02/2018.
//

#ifndef PreDelay_hpp
#define PreDelay_hpp

#include <stdio.h>

// USER HEADERS
#include "CircularBuffer.hpp"
#include "../JuceLibraryCode/JuceHeader.h"

class PreDelay{
    CircularBuffer buffer{4410};
    float delayLength;
    int Fs;
public:
    PreDelay();
    
    void setFs(int sampleRate);

    void process(float* samples, int bufferSize);

    float processSingleSample(float sample);

    void setDelayLength(float inValue);

    float getDelayLength();
};

#endif /* PreDelay_hpp */
