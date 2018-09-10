//
//  CircularBuffer.hpp
//
//  Created by Squishy on 14/02/2018.
//
//  If you use this, please credit me :)

#ifndef CircularBuffer_hpp
#define CircularBuffer_hpp

#include <cmath>
#include <vector>

typedef std::vector<float> Vec_Float;
enum Selector{upperBound, lowerBound};
enum InterType{cubic, linear};

class CircularBuffer{
    Vec_Float buffer;
    int bufferLength, head, tail;
	
public:
    CircularBuffer(float inValue);
    
    float read(float numElementsToRead, InterType inValue);
	
	float readCubic(float numElementsToRead);

	float readLinear(float numElementsToRead);

    void write(float inValue);
    
    float cubicInterpolation(double y0, double y1, double y2, double y3, double mu);
    
    float getSample(float inValue);
        
    void setBufferLength(float inValue);
    
    int getBufferLength();
};

#endif /* CircularBuffer_hpp */

