//
//  SpatializeComponent.cpp
//  ipReverb
//
//  Created by Sam on 14/04/2018.
//  Copyright © 2018 Sam. All rights reserved.
//

#include "SpatializeComponent.hpp"

SpatializeComponent::SpatializeComponent(){
	;
}

void SpatializeComponent::resized(){
	;
}

void SpatializeComponent::setXorigin(int inX){
	xOrigin = inX;
}

void SpatializeComponent::setYorigin(int inY){
	yOrigin = inY;
}

void SpatializeComponent::setWidth(int inWidth){
	width = inWidth;
}

void SpatializeComponent::setHeight(int inHeight){
	height = inHeight;
}

int SpatializeComponent::getMarkerXpos(){
	return markerXpos;
}

int SpatializeComponent::getMarkerYpos(){
	return markerYpos;
}

int SpatializeComponent::getMarkerSize(){
	return markerSize;
}

void SpatializeComponent::setMarkerXpos(int inValue){
	markerXpos = inValue;
}

void SpatializeComponent::setMarkerYpos(int inValue){
	markerYpos = inValue;
}

void SpatializeComponent::setMarkerSize(int inValue){
	markerSize = inValue;
}




void SpatializeComponent::paint(Graphics& g){
	g.setColour(Colour (14, 34, 47));
	g.fillRoundedRectangle(xOrigin, yOrigin, width, height, 5);	//Draw Outline
	g.setColour(Colour (255, 255, 255));
	
	
	
	g.drawFittedText("X", xOrigin + width/2 - labelWidth/2, yOrigin + height - labelHeight, 	labelWidth, labelHeight, Justification::centred, 1);
	g.drawFittedText("Y", xOrigin + width - labelWidth, 	yOrigin + height/2 - labelHeight/2, labelWidth, labelHeight, Justification::centred, 1);
	g.drawFittedText("Z", xOrigin + 5, 						yOrigin + height/2 - labelHeight/2, labelWidth, labelHeight, Justification::centred, 1);

	
	g.drawFittedText("ER Spatializer (m)", xOrigin + width/2 - 50, yOrigin - labelHeight * 2, 100, labelHeight*2, Justification::centred, 1);

	
	g.setColour(Colour(255, 160, 0));
	g.drawEllipse(markerXpos, markerYpos, markerSize, markerSize, 2);
}

void SpatializeComponent::drag(const MouseEvent &event){
	float xPos = event.x;
	float yPos = event.y;

	if(clicked){
		if(setSize){
			markerSize = (((yPos - yOrigin) / height) * 30) + 10;

			if(yPos < yOrigin)
				markerSize = 10;
			if(yPos > yOrigin + height)
				markerSize = 39;
		}
		else{
			markerXpos = xPos - markerSize/2;
			markerYpos = yPos - markerSize/2;
			
			if(markerXpos < xOrigin)
				markerXpos = xOrigin;
			
			if(markerXpos > xOrigin + width - markerSize)
				markerXpos = xOrigin + width - markerSize;
			
			if(markerYpos < yOrigin)
				markerYpos = yOrigin;
			
			if(markerYpos > yOrigin + height - markerSize)
				markerYpos = yOrigin + height - markerSize;
		}
	}
}

void SpatializeComponent::down (const MouseEvent &event){
	int numOfClicks = event.getNumberOfClicks();
	int xPos		= event.getMouseDownX();
	int yPos 		= event.getMouseDownY();
	
	if(xPos > markerXpos &&
	   xPos < markerXpos + markerSize &&
	   yPos > markerYpos &&
	   yPos < markerYpos + markerSize){
		
		if(numOfClicks > 1){
			markerXpos = xOrigin + width/2 - markerSize/2;
			markerYpos = yOrigin + height/2 - markerSize/2;
		}
		else
			clicked = true;
	}
}

void SpatializeComponent::up (const MouseEvent &event){
	clicked = false;
}

void SpatializeComponent::shiftDown(const ModifierKeys &modifiers){
	setSize = modifiers.isShiftDown();
}

void SpatializeComponent::initMarker(){
	markerXpos = xOrigin + width/2 - markerSize/2;
	markerYpos = yOrigin + height/2 - markerSize/2;
}

float SpatializeComponent::getXvalue(){
	return ((markerXpos) - xOrigin) / float(width - markerSize);
}

float SpatializeComponent::getYvalue(){
	return ((markerYpos) - yOrigin) / float(height - markerSize);
}

float SpatializeComponent::getZvalue(){
	return (markerSize - 10) / float(29);
}

int SpatializeComponent::getXOrigin(){
	return xOrigin;
}

int SpatializeComponent::getYOrigin(){
	return yOrigin;
}

int SpatializeComponent::getWidth(){
	return width;
}

int SpatializeComponent::getHeight(){
	return height;
}
