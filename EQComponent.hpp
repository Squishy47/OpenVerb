//
//  EQComponent.hpp
//  ipReverb
//
//  Created by Sam on 23/03/2018.
//  Copyright © 2018 Sam. All rights reserved.
//

#ifndef EQWrapper_hpp
#define EQWrapper_hpp

#include <stdio.h>
#include "VecTemplate.hpp"
#include "FilterObject.hpp"

class EQComponent: public Component{
//	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EQComponent)

	std::vector<FilterObject*> filterObjects;
	
	int xOrigin,
		yOrigin,
		width,
		height,
		numOfFilters = 0,
		Fs			= 44100,
		gain_range  = 24,
		labelWidth = 0;
	
	
	bool setQ = false;

public:
	enum filterParam{Fc, Gain, Q};
	
	EQComponent(int inValue);
//	~EQComponent();
	
	void paint (Graphics&) override;
	void resized() override;
	
	int getXorigin			();
	int getYorigin			();
	int getWidth			();
	int getHeight			();
	int getFcMarkerSize		(int selector);
	int getFcMarkerXpos		(int selector);
	int getFcMarkerYpos		(int selector);
	float getFilterParams	(filterParam param, int selector);
	
	void setXorigin			(int inX);
	void setYorigin			(int inY);
	void setWidth			(int inWidth);
	void setHeight			(int inHeight);
	void setFs				(int sampleRate);
	void setFilterCoefs 	(float* coefs, int selector);
	void setFilterParams	(int selector, float inFc, float inG, float inQ);
	void drawEQCurve		(Graphics&);
	void getFilterCoefs		(int selector, float* coefs);
	void setfcMarkerPos		(int inX, int inY, int filterSelector);
	void drag 				(const MouseEvent &event);
	void down 				(const MouseEvent &event);
	void up 				(const MouseEvent &event);
	void shiftDown			(const ModifierKeys &modifiers);

	void updateMarkerPos();
	void setInitVals		(int selector, float inFc, float inG, float inQ);
	
	float amplitudeCalc 	(float freq);
	float gain2y			(float gain);
	float freq2x			(float freq);
	float x2freq			(float inX);
	float y2gain			(float inY);
};

#endif /* EQWrapper_hpp */
