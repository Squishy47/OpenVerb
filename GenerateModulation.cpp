//
//  GenerateModulation.cpp
//  ModulationGenerationTest
//
//  Created by Squishy on 25/02/2018.
//  Copyright © 2018 Squishy. All rights reserved.
//

#include "GenerateModulation.hpp"
#include <iostream>
GenerateModulation::GenerateModulation(int inFs, float inA, float inFreq, float inQ){
	readHead = inFreq * -1;
	bufferLength = inFs;
	frequency = inFreq;
	amplitude = inA;
	phase = inQ;
	
	buffer.resize(bufferLength);

	reCalc();
}

float GenerateModulation::sineCalc(float index){
	return sin(2 * M_PI * index + phase);
}

float GenerateModulation::read(){
	if (readHead > bufferLength - 1)
		readHead -= bufferLength;
	else if (readHead < 0)
		readHead += bufferLength;
	
	readHead += frequency;
	return (buffer[readHead - 1] * amplitude);
}

void GenerateModulation::write(float inValue){
	if(writeHead > bufferLength - 1)
		writeHead -= bufferLength;
	else if(writeHead < 0)
		readHead += bufferLength;
	
	buffer[writeHead] = inValue;
	writeHead++;
}

void GenerateModulation::reCalc(){
	for(int i = 0; i < bufferLength; i++)
		write(sineCalc(i / float(bufferLength)));
}

void GenerateModulation::setFreq(float inFreq){
	frequency = int(inFreq);
}

void GenerateModulation::setAmplitude(float inA){
	amplitude = inA;
}

void GenerateModulation::setFs(float inFs){
	bufferLength = inFs;
	buffer.clear();
	buffer.resize(bufferLength);
	reCalc();
}
