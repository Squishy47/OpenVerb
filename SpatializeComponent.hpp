//
//  SpatializeComponent.hpp
//  ipReverb
//
//  Created by Sam on 14/04/2018.
//  Copyright © 2018 Sam. All rights reserved.
//

#ifndef SpatializeComponent_hpp
#define SpatializeComponent_hpp

#include <stdio.h>
#include "VecTemplate.hpp"

class SpatializeComponent: public Component{
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpatializeComponent)

	int xOrigin = 0;
	int yOrigin = 0;
	int width = 0;
	int height = 0;
	
	int markerXpos = 0;
	int markerYpos = 0;
	int markerSize = 20;
	
	float labelHeight = 15.f;
	float labelWidth = 10.f;
	
	
	
	float xVal = 0.f;
	float yVal = 0.f;
	float zVal = 0.f;
	
	bool clicked = false;
	bool setSize = false;
public:
	
	SpatializeComponent();
	//	~SpatializeComponent();

	void paint 				(Graphics&) override;
	void resized			() override;
	
	void setXorigin			(int inX);
	void setYorigin			(int inY);
	void setWidth			(int inWidth);
	void setHeight			(int inHeight);
	
	void setXvalue			(float inValue);
	void setYvalue			(float inValue);
	void setZvalue			(float inValue);
	
	void setMarkerXpos		(int inValue);
	void setMarkerYpos		(int inValue);
	void setMarkerSize		(int inValue);
	
	float getXvalue			();
	float getYvalue			();
	float getZvalue			();
	
	int getXOrigin			();
	int getYOrigin			();
	int getWidth			();
	int getHeight			();

	int getMarkerXpos		();
	int getMarkerYpos		();
	int getMarkerSize		();
	
	
	bool getState			();
	
	void initMarker			();
	void up 				(const MouseEvent &event);
	void down 				(const MouseEvent &event);
	void drag 				(const MouseEvent &event);
	void shiftDown			(const ModifierKeys &modifiers);
};

#endif /* SpatializeComponent_hpp */
