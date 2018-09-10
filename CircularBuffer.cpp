//
//  CircularBuffer.cpp
//
//  Created by Squishy on 14/02/2018.
//
//  If you use this, please credit me :)

#include "CircularBuffer.hpp"

CircularBuffer::CircularBuffer(float inValue){
	setBufferLength(inValue);
	head = 0;
	tail = 0;
}

float CircularBuffer::readCubic(float index){
	float y0, y1, y2, y3, mu;

	y0 = floor(index - 1);
	y1 = floor(index);
	y2 = floor(index);
	y3 = floor(index + 1);
	mu = index - y1;
	
	return cubicInterpolation(getSample(y0), getSample(y1), getSample(y2), getSample(y3), mu);
}

float CircularBuffer::readLinear(float index){
	float upper, lower, interpAmount;

	upper = floor(index);
	lower = floor(index);
	interpAmount = index - lower;
	
	return (getSample(upper) * interpAmount + (1.0 - interpAmount) * getSample(lower));
}

float CircularBuffer::read(float index, InterType inValue){
	// this was my origional read function, decided to make it more efficient by making seperate fucntions removing the need for the switch.
	// (efficiency due to it being called multiple times every sample.)
	// has not been removed as i wanted to get into the habit of making code others may use, so trying not to break other ppls code by changing foundation workings.
	
	float y0, y1, y2, y3, mu, upper, lower, interpAmount;
	
	switch(inValue){
		case cubic:{
			y0 = floor(index - 1);
			y1 = floor(index);
			y2 = floor(index);
			y3 = floor(index + 1);
			mu = index - y1;
			return cubicInterpolation(getSample(y0), getSample(y1), getSample(y2), getSample(y3), mu);
		break;
		}
		case linear:{
				upper = floor(index);
				lower = floor(index);
				interpAmount = index - lower;
				return (getSample(upper) * interpAmount + (1.0 - interpAmount) * getSample(lower));
			break;
		}
		default:
			return 0.0;
		break;
	}
}

void CircularBuffer::write(float inValue){
    head = (head + 1) % bufferLength;
    buffer[head] = inValue;
}

float CircularBuffer::getSample(float inValue){
    tail = head - inValue;
	
	//using if statement as modulo wasn't working and i don't know how to inversly modulo e.g (tail < 0)
	if (tail > bufferLength - 1)
		tail -= bufferLength;
	else if (tail < 0)
		tail += bufferLength;
	
	return buffer[tail];
}

void CircularBuffer::setBufferLength(float inValue){
    bufferLength = inValue;
    buffer.resize(inValue);
}

int CircularBuffer::getBufferLength(){
    return (int)buffer.size();
}

float CircularBuffer::cubicInterpolation(double y0, double y1, double y2, double y3, double mu){
    //Cubic interp (this algorithm) taken from: http://paulbourke.net/miscellaneous/interpolation/
    double a0, a1, a2, a3, mu2;
    
    mu2 = mu * mu;
	a0 = -0.5 * y0 + 1.5 * y1 - 1.5 * y2 + 0.5 * y3;
	a1 = y0 - 2.5 * y1 + 2 * y2 - 0.5 * y3;
	a2 = -0.5 * y0 + 0.5 * y2;
	a3 = y1;
//    a0 = y3 - y2 - y0 + y1;
//    a1 = y0 - y1 - a0;
//    a2 = y2 - y0;
//    a3 = y1;
    
    return(a0 * mu * mu2 + a1 * mu2 + a2 * mu + a3);
}
