//
//  filterObject.hpp
//  ipReverb
//
//  Created by Sam on 03/04/2018.
//  Copyright © 2018 Sam. All rights reserved.
//

#ifndef filterObject_hpp
#define filterObject_hpp

#include <stdio.h>

class FilterObject{
	int markerPos[2] = {0, 0};
	int markerSize = 15;
	
	float coefs[5] = {0.f, 0.f, 0.f, 0.f, 0.f};
	
	float initialFc = 0.f;
	float initialQ = 0.f;
	float initialGain = 0.f;
	
	float Fc = 1000;
	float Q = 0.707;
	float gain = 0.f;
	
	bool currentlySelected = false;
	
public:
	enum Axis{x, y};
	
	FilterObject(float initFc, float initGain, float initQ);
	
	void setMarkerPos		(int xPos, int yPos);
	void setMarkerSize		(int size);
	void setFilterCoefs		(float* filterCoefs);
	void setFilterParams	(float inFc, float inGain, float inQ);
	void setInitVals		(float inFc, float inG, float inQ);
	void setSelected		(bool inSelection);
	void setInitialState	();
	void setFc				(float inFc);
	void setGain 			(float inGain);
	void setQ				(float inQ);
	
	
	
	
	
	int getMarkerPos		(Axis selector);
	int getMarkerSize		();
	void getFilterCoefs		(float* inFilterCoefs);
	float getFilterFc		();
	float getFilterQ		();
	float getFilterGain		();
	bool isSelected			();
	
	float getInitialFc		();
	float getInitialQ		();
	float getInitialGain	();
};






#endif /* filterObject_hpp */
