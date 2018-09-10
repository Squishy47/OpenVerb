//
//  SliderWrapper.hpp
//  ipReverb
//
//  Created by Sam on 23/03/2018.
//  Copyright © 2018 Sam. All rights reserved.
//

#ifndef SliderWrapper_hpp
#define SliderWrapper_hpp

#include <stdio.h>
#include "VecTemplate.hpp"

class sliderWrapper{
public:
	Slider slider;
	String name, suffix;
	float maxValue, minValue, stepSize, initValue, xPos, yPos;
	
	sliderWrapper(String inName, String inSuffix, float inMax, float inMin, float inStepSize, float inInitial, float inXpos, float inYpos);
};

#endif /* SliderWrapper_hpp */
