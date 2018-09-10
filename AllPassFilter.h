//
//  IIRFilter.h
//  samsPlugin1 - Shared Code
//
//  Created by Sam on 28/12/2017.
//

#ifndef IIRFilter_h
#define IIRFilter_h

// USER HEADERS
#include "CircularBuffer.h"
#include "CoefficientCalc.h"
#include "VecTemplate.h"
#include "GenerateModulation.h"

class AllPassFilter{
    CircularBuffer CB;
    IIRFilter ap;
    IIRCoefficients apCoef;
    GenerateModulation modulationGenerator1, modulationGenerator2, modulationGenerator3;
    Vec_Float modulation;

    float feedback = 0.7;
    float delayLength = 250;
public:
    void init(int inValue, int modOffset, int Fs, int bufferSize){
        delayLength = inValue;
        modulation.resize(bufferSize);
        CB.init(delayLength + 1);
        ap.setCoefficients(apCoef.makeAllPass(Fs, delayLength));
        
        modulationGenerator1.init(Fs, 0.75, modOffset * 1.0, 0.0);
        modulationGenerator2.init(Fs, 0.50, modOffset * 2.0, 7.0);
        modulationGenerator3.init(Fs, 0.25, modOffset * 4.0, 11.0);
    }
    
    void process(float* samples, int bufferSize){
        for(int i = 0; i < bufferSize; i++)
            samples[i] = processSingleSample(samples[i], i);
    }
    
    float processSingleSample(float sample, int index){
        sample += CB.read(delayLength + modulationGenerator1.read() * modulationGenerator2.read() * modulationGenerator3.read()) * feedback;
        sample = ap.processSingleSampleRaw(sample);
        CB.write(sample, 1);
        return sample;
    }

    void setFeedback(float inValue){
        feedback = inValue;
    }
};

#endif /* IIRFilter_h */
