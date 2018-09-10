//
//  filterObject.cpp
//  ipReverb
//
//  Created by Sam on 03/04/2018.
//  Copyright © 2018 Sam. All rights reserved.
//

#include "FilterObject.hpp"

FilterObject::FilterObject(float initFc, float initGain, float initQ){
	initialFc = initFc;
	initialQ = initQ;
	if(initGain < 0)
		initialGain = initGain;
}

void FilterObject::setMarkerPos(int xPos, int yPos){
	markerPos[0] = xPos;
	markerPos[1] = yPos;
}

void FilterObject::setMarkerSize(int size){
	markerSize = size;
}

void FilterObject::setFilterCoefs(float* filterCoefs){
	for(int i = 0; i < 5; i++)
		coefs[i] = filterCoefs[i];
}

void FilterObject::setFilterParams(float inFc, float inGain, float inQ){
	Fc = inFc;

	if(inGain < 0)
		gain = inGain;
	
	Q = inQ;
}

void FilterObject::setInitVals(float inFc, float inG, float inQ){
	initialFc = inFc;
	initialQ = inQ;
	initialGain = inG;
}


void FilterObject::setSelected(bool inSelection){
	currentlySelected = inSelection;
}

void FilterObject::setInitialState(){
	Fc = initialFc;
	Q = initialQ;
	gain = initialGain;
}

void FilterObject::setFc(float inFc){
	Fc = inFc;
}

void FilterObject::setGain(float inGain){
	gain = inGain;
}

void FilterObject::setQ(float inQ){
	Q = inQ;
}





int FilterObject::getMarkerPos(Axis selector){
	switch (selector) {
		case x:
			return markerPos[0];
			break;
		case y:
			return markerPos[1];
		default:
			return markerPos[0];
			break;
	}
}

int FilterObject::getMarkerSize(){
	return markerSize;
}

void FilterObject::getFilterCoefs(float* inFilterCoefs){
	for(int i = 0; i < 5; i++)
		inFilterCoefs[i] = coefs[i];
}

float FilterObject::getFilterFc(){
	return Fc;
}

float FilterObject::getFilterQ(){
	return Q;
}

float FilterObject::getFilterGain(){
	return gain;
}

bool FilterObject::isSelected(){
	return currentlySelected;
};

float FilterObject::getInitialFc(){
	return initialFc;
}

float FilterObject::getInitialQ(){
	return initialQ;
}

float FilterObject::getInitialGain(){
	return initialGain;
}

