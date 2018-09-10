//
//  SliderWrapper.cpp
//  ipReverb
//
//  Created by Sam on 23/03/2018.
//  Copyright © 2018 Sam. All rights reserved.
//

#include "SliderWrapper.hpp"

sliderWrapper::sliderWrapper(String inName, String inSuffix, float inMax, float inMin, float inStepSize, float inInitial, float inXpos, float inYpos){
	name = inName;
	suffix = inSuffix;
	maxValue = inMax;
	minValue = inMin;
	stepSize = inStepSize;
	initValue = inInitial;
	xPos = inXpos;
	yPos = inYpos;
}
