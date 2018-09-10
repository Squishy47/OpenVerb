//
//  LateReflections.cpp
//  LRTest
//
//  Created by Squishy on 23/02/2018.
//

#include "LateReflections.hpp"

LateReflections::LateReflections(){
	generateMatrix();
	setLRDelayLength(1.4924);
}

void LateReflections::process(float* inSample, int bufferSize, int channel){
	for(int i = 0; i < bufferSize; i++)
		inSample[i] = processSingleSample(inSample[i], channel);
}

float LateReflections::processSingleSample(float sample, int channel){
	float tempO[32], temp1[32];
	float mod = modulation.read();
	float output = 0.0f;
	
	std::fill_n(tempO, 32, 0.0f);
	
	//FDN. not truely lossless as there is the mix of matricies. Took a long time to get this algorithm to sound decent.
	for(int i = 0; i < numOfTaps; i++){
		temp1[i] = buffers[i].readCubic(tapPoint[i] + mod) * feedback;
		temp1[i] = fixedLowShelf[i].processSingleSampleRaw(temp1[i]);
		temp1[i] = fixedHighShelf[i].processSingleSampleRaw(temp1[i]);
		temp1[i] = fbLowShelfFilter[i].processSingleSampleRaw(temp1[i]);    // processes low shelf filters
		temp1[i] = fbHighShelfFilter[i].processSingleSampleRaw(temp1[i]);   // processes high shelf filters
		temp1[i] = fbPeakFilter[i].processSingleSampleRaw(temp1[i]); 		// processes peak/notch filters
	}

	for(int i = 0; i < numOfTaps; i++){
		for(int l = 0; l < numOfTaps; l++)
			tempO[i] += temp1[l] * (orthogonalMatrix[i][l]);				// multiply each tap with an orthogonal metix
		
		buffers[i].write((sample + tempO[i]));
		output += temp1[i] * mixingMatrix[channel][i];						// multiply each tap with mixing matrix to give greater stereo impression
	}
	
	return output * (feedback * -1 * 0.9 + 1);
}

void LateReflections::setNumOfTaps(int inValue){
	qualitySetting = inValue;
	
	switch(inValue){
		case 0:
			numOfTaps = 16;
			break;
		case 1:
			numOfTaps = 32;
			break;
	}
}

void LateReflections::setLRDelayLength(float inValue){
	feedback = inValue;
	
	switch(qualitySetting){
		case 0:
			for(int i = 0; i < numOfTaps; i++)
				tapPoint[i] = powf(primes[i*2], 1.15f);
			break;
		case 1:
			for(int i = 0; i < numOfTaps; i++)
				tapPoint[i] = powf(primes[i], 1.15f);
			break;
	}
}

void LateReflections::setFs(float sampleRate){
	// recreated sample rate dependant components if the rate changes
	Fs = sampleRate;
	modulation.setFs(Fs);
	
	for(int i = 0; i < 3; i++)
		createFeedbackFilters(i);
}

void LateReflections::setModRate(float inValue){
	modulation.setFreq(inValue);
}

void LateReflections::setModDepth(float inValue){
	amplitude = inValue;
	modulation.setAmplitude(inValue);
}

void LateReflections::setFilterParams(int selector, float Fc, float gain, float Q){
	fFc[selector] = Fc;
	fG[selector] = gain;
	fQ[selector] = Q;
	
	createFeedbackFilters(selector);
}

void LateReflections::createFeedbackFilters(int selector){
	for(int i = 0; i < maxTaps; i++){
		fixedLowShelf[i].setCoefficients(fixedLowShelfCoefs.makeLowShelf(Fs, 30.f, 0.4, juce::Decibels::decibelsToGain(-0.2f)));
		fixedHighShelf[i].setCoefficients(fixedHighShelfCoefs.makeHighShelf(Fs, 14000, 0.4, juce::Decibels::decibelsToGain(-3.f)));
	}
	switch(selector){
		case 0:
			lowShelfCoefs = lowShelfCoefs.makeLowShelf(Fs, fFc[selector], fQ[selector], fG[selector]);
			for(int i = 0; i < maxTaps; i++)
				fbLowShelfFilter[i].setCoefficients(lowShelfCoefs);
			break;
		case 1:
			peakCoefs = peakCoefs.makePeakFilter(Fs, fFc[selector], fQ[selector], fG[selector]);
			for(int i = 0; i < maxTaps; i++)
				fbPeakFilter[i].setCoefficients(peakCoefs);
			break;
		case 2:
			highShelfCoefs = highShelfCoefs.makeHighShelf(Fs, fFc[selector], fQ[selector], fG[selector]);
			for(int i = 0; i < maxTaps; i++)
				fbHighShelfFilter[i].setCoefficients(highShelfCoefs);
			break;
	}
}

void LateReflections::generateMatrix(){
	for(int i = 0; i < maxTaps; i++){
		for(int j = 0; j < maxTaps; j++){
			householderMatrix[i][j] = -1.f;
			orthogonalMatrix[i][j] = 0.f;
			if(j == i){
				householderMatrix[i][j] = 1.f;
				orthogonalMatrix[i][j] = 1.f;
			}
		}
	}
}

void LateReflections::getFilterCoefs(float* coefs, int selector){
	switch(selector){
		case 0:
			for(int i = 0; i < 5; i++)
				coefs[i] = lowShelfCoefs.coefficients[i];
			break;
		case 1:
			for(int i = 0; i < 5; i++)
				coefs[i] = peakCoefs.coefficients[i];
			break;
		case 2:
			for(int i = 0; i < 5; i++)
				coefs[i] = highShelfCoefs.coefficients[i];
			break;
	}
}
