//
//  EarlyReflections.cpp
//  ERTest
//
//  Created by Squishy on 17/02/2018.
//  Copyright © 2018 Squishy. All rights reserved.
//

#include "EarlyReflections.hpp"

EarlyReflections::EarlyReflections(){
	randomNum.setSeed(0);
}

void EarlyReflections::process(float* samples, int bufferSize, int channel){
    for(int i = 0; i < bufferSize; i++)
        samples[i] = processSingleSample(samples[i], channel);
}

float EarlyReflections::processSingleSample(float sample, int channel){
	float temp1[numOfTaps];
    float output = 0;
	
	for(int i = 0; i < numOfTaps; i++){
		temp1[i] = buffers[i].readCubic(taps[i]) * 0.5f;
		HShelf[i].processSingleSampleRaw(temp1[i]);
		buffers[i].write(sample + temp1[i]);
		output += temp1[i] * movementMatrix[channel][i]; // movement matrix add movement around room.
	}
	
    return output * 0.6;
}

void EarlyReflections::setSize(int selector){
	currentSelection = selector;
	
	//multiplies each room dimension by a val between 0 and 1, allowing for the user to change placement within room.
	taps[0] = roomDimensions[currentSelection][0] * (roomMovement[0]);
	taps[1] = roomDimensions[currentSelection][0] * (1 - roomMovement[0]);
	taps[2] = roomDimensions[currentSelection][1] * (roomMovement[1]);
	taps[3] = roomDimensions[currentSelection][1] * (1 - roomMovement[1]);
	taps[4] = roomDimensions[currentSelection][2] * (roomMovement[2]);
	taps[5] = roomDimensions[currentSelection][2] * (1 - roomMovement[2]);
	
	// adds some volume change to the taps to give greater sense of movement within room
	//Left
	movementMatrix[0][0] = 1 - roomMovement[0]; 	//W
	movementMatrix[0][1] = roomMovement[0]; 		//W
	movementMatrix[0][2] = 1 - roomMovement[1]; 	//L
	movementMatrix[0][3] = roomMovement[1]; 		//L
	movementMatrix[0][4] = 1 - roomMovement[2]; 	//H
	movementMatrix[0][5] = roomMovement[2]; 		//H
	
	//Right
	movementMatrix[1][0] = roomMovement[0]; 		//W
	movementMatrix[1][1] = 1 - roomMovement[0]; 	//W
	movementMatrix[1][2] = roomMovement[1]; 		//L
	movementMatrix[1][3] = 1 - roomMovement[1]; 	//L
	movementMatrix[1][4] = roomMovement[2]; 		//H
	movementMatrix[1][5] = 1 - roomMovement[2]; 	//H




	for(int i = 0; i < numOfTaps; i++)
		taps[i] = (taps[i] / 340) * Fs; // convert meters to samples.
}

void EarlyReflections::setFs(int inValue){
    Fs = inValue;
	for(int i = 0; i < numOfTaps; i++)
		buffers[i].setBufferLength(Fs / 4);
	createFilters();
	setSize(currentSelection);
}

void EarlyReflections::setRandomSeed(int inValue){
	randomNum.setSeed(inValue);
	for(int i = 0; i < 3; i++)
		roomDimensions[5][i] = (1 + randomNum.nextFloat()) * 20;
	if(currentSelection == 5)
		setSize(currentSelection);
}

void EarlyReflections::setRoomPosition(float inValue, int selector){
	roomMovement[selector] = inValue;
	
	setSize(currentSelection);
}

void EarlyReflections::createFilters(){
	HShelf.resize(numOfTaps);
	HShelfCoefs.resize(numOfTaps);
	
	// as tap number increases it gets a lower cut-off to simulate high frequency loss due to air.
	for (int i = 0; i < numOfTaps; i++){
		HShelfCoefs[i] = HShelfCoefs[i].makeHighShelf(Fs, 12500 - (i * 500), 0.707, juce::Decibels::gainToDecibels(0.707));
		HShelf[i].setCoefficients(HShelfCoefs[i]);
	}
}


float EarlyReflections::getRoomDimensions(int selector){
	return (taps[selector] * 340) / Fs;
}





