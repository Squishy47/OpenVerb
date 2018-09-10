//
//  nestedAllPass.h
//  ipReverb - Shared Code
//
//  Created by Sam on 24/01/2018.
//

#ifndef nestedAllPass_h
#define nestedAllPass_h

class NestedAllPassFilter{
    CircularBuffer CB1, CB2;
    IIRFilter ap1, ap2;
    IIRCoefficients apCoef;
    GenerateModulation modulationGenerator1, modulationGenerator2, modulationGenerator3;
    Vec_Float modulation;
    
    float feedback = 0.4;
    float delayLength = 5000;
public:
    void init(int inValue, int Fs, int bufferSize){
        delayLength = inValue;
        modulation.resize(bufferSize);

        CB1.init(delayLength + 1);
        ap1.setCoefficients(apCoef.makeAllPass(Fs, 10000));
        
        CB2.init(delayLength + 1);
        ap2.setCoefficients(apCoef.makeAllPass(Fs, 20000));
        
        modulationGenerator1.init(Fs, 1, 2, 20.0);
        modulationGenerator2.init(Fs, 2, 3, 0.0);

    }
    
    void process(float* samples, int bufferSize){
        for(int i = 0; i < bufferSize; i++)
            samples[i] = processSingleSample(samples[i], i);
    }
    
    float processSingleSample(float sample, int index){
        sample += processNestedSingleSample(CB1.read(delayLength + modulationGenerator1.read() * modulationGenerator2.read()), index) * feedback;
        sample = ap1.processSingleSampleRaw(sample);
        CB1.write(sample, 1);
        return sample;
    }
    
    float processNestedSingleSample(float sample, int index){
        sample += CB2.read(delayLength + modulationGenerator1.read() + modulationGenerator2.read()) * feedback;
        sample = ap2.processSingleSampleRaw(sample);
        CB2.write(sample, 1);
        return sample;
    }
    
    void setFeedback(float inValue){
        feedback = inValue;
    }
};

#endif /* nestedAllPass_h */
