//
//  EQComponent.cpp
//  ipReverb
//
//  Created by Squishy on 23/03/2018.
//  Copyright © 2018 Squishy. All rights reserved.
//
//  The following functions were written by Alex Harker:
//  - amplitudeCalc()
//  - freq2x()
//  - x2freq()
//  - gain2y()
//  - y2gain()

#include "EQComponent.hpp"


EQComponent::EQComponent(int inValue){
	for(int i = 0; i < inValue; i++)
		filterObjects.push_back(new FilterObject{20.f, 0.f, 0.707f});
	
	
	numOfFilters = inValue;
}

float EQComponent::amplitudeCalc(float freq){
	float coefs1[5], coefs2[5], coefs3[5];
	
	filterObjects[0]->getFilterCoefs(coefs1);
	filterObjects[1]->getFilterCoefs(coefs2);
	filterObjects[2]->getFilterCoefs(coefs3);

	
	float a_coeff[9] = {1.0, coefs1[3], coefs1[4],
				  		1.0, coefs2[3], coefs2[4],
				  		1.0, coefs3[3], coefs3[4]};
	
	float b_coeff[9] = {coefs1[0], coefs1[1], coefs1[2],
				  		coefs2[0], coefs2[1], coefs2[2],
				  		coefs3[0], coefs3[1], coefs3[2]};

	float freq_val = 2 * M_PI * freq / Fs;
	float 	pow = 1,
			A 	= 0,
			B 	= 0,
			C 	= 0,
			D 	= 0,
			cos1 = cos(freq_val),
			sin1 = sin(freq_val),
			cos2 = cos(freq_val * 2),
			sin2 = sin(freq_val * 2);
	
	// Accumulate the power response of the filterObjects at a given input frequency
	for (int i = 0; i < 3; i++){
		A = b_coeff[i * 3] + b_coeff[i * 3 + 1] * cos1 + b_coeff[i * 3 + 2] * cos2;
		B = b_coeff[i * 3 + 1] * sin1 + b_coeff[i * 3 + 2] * sin2;
		
		C = a_coeff[i * 3] + a_coeff[i * 3 + 1] * cos1 + a_coeff[i * 3 + 2] * cos2;
		D = a_coeff[i * 3 + 1] * sin1 + a_coeff[i * 3 + 2] * sin2;
		
		float denominator = 1. / (C * C + D * D);
		float real = (A * C + B * D) * denominator;
		float imag = (B * C - A * D) * denominator;
		
		pow *= (real * real + imag * imag);
	}
	
	// Return the linear amplitude response
	return (10. * log(pow)) / log(10);
}

float EQComponent::freq2x(float freq){
	return width * (log(freq) - log(20)) / (log(20000) - log(20));
}

float EQComponent::x2freq(float inX){
	return exp((inX / width) * (log(20000) - log(20)) + log(20));
}

float EQComponent::gain2y(float gain){
	return ((gain / gain_range) - 1) * -((height + yOrigin) / 2);
}

float EQComponent::y2gain(float inY){
	return (inY / -((height + yOrigin) / 2.) + 1.) * gain_range;
}

void EQComponent::setFs(int sampleRate){
	Fs = sampleRate;
}

int EQComponent::getXorigin(){
	return xOrigin;
}

int EQComponent::getYorigin(){
	return yOrigin;
}

int EQComponent::getWidth(){
	return width;
}

int EQComponent::getHeight(){
	return height;
}

int EQComponent::getFcMarkerSize(int selector){
	return filterObjects[selector]->getMarkerSize();
}

int EQComponent::getFcMarkerXpos(int selector){
	return filterObjects[selector]->getMarkerPos(FilterObject::x);
}

int EQComponent::getFcMarkerYpos(int selector){
	return filterObjects[selector]->getMarkerPos(FilterObject::y);
}

float EQComponent::getFilterParams(filterParam param, int selector){
	switch(param){
		case Fc:
			return filterObjects[selector]->getFilterFc();
			break;
		case Gain:
			return filterObjects[selector]->getFilterGain();
			break;
		case Q:
			return filterObjects[selector]->getFilterQ();
			break;
		default:
			return filterObjects[selector]->getFilterFc();
			break;
	}
}

void EQComponent::setXorigin(int inX){
	xOrigin = inX;
}

void EQComponent::setYorigin(int inY){
	yOrigin = inY;
}

void EQComponent::setWidth(int inWidth){
	width = inWidth;
	labelWidth = float(float(width) / 9);
}

void EQComponent::setHeight(int inHeight){
	height = inHeight;
}

void EQComponent::setFilterCoefs(float* inCoefs, int selector){
	filterObjects[selector]->setFilterCoefs(inCoefs);
}

void EQComponent::setfcMarkerPos(int inX, int inY, int selector){
	filterObjects[selector]->setMarkerPos(inX, inY);
}

void EQComponent::setFilterParams(int selector, float inFc, float inG, float inQ){
	filterObjects[selector]->setFilterParams(inFc, inG, inQ);
}


void EQComponent::paint(Graphics& g){
	g.setColour(Colour (14, 34, 47));
	g.fillRoundedRectangle(xOrigin, yOrigin, width, height + 25, 5);	//Draw EQ background
	
	g.setColour(Colour (255, 255, 255));
	g.drawFittedText("Damping EQ", xOrigin + width/2 - 50, yOrigin - 15 * 2, 100, 15*2, Justification::centred, 1);

	g.setColour(Colour (19, 39, 52)); // draw labels outline
	for(int i = 0; i < 9; i++)
		g.drawRoundedRectangle(1 + xOrigin + (i * labelWidth), yOrigin + height, labelWidth, 24, 5, 2);
	
	drawEQCurve(g);
	updateMarkerPos();
}

void EQComponent::drawEQCurve(Graphics& g){
	g.setColour(Colour(255, 160, 0));
	float plot_y[2];
	
	for (int i = 1; i <= width; i++){
		plot_y[1] = plot_y[0];
		
		float damp_plot = amplitudeCalc(x2freq(i));
		plot_y[0] = gain2y(damp_plot);
		
		if(plot_y[0] < yOrigin + height){
			if (i != 1)
				g.drawLine(xOrigin + i - 1, plot_y[1], xOrigin + i, plot_y[0], 2);
		}
	}
	
	for(auto filter: filterObjects)
		g.drawEllipse(filter->getMarkerPos(FilterObject::x), filter->getMarkerPos(FilterObject::y), filter->getMarkerSize(), filter->getMarkerSize(), 2);
}

void EQComponent::resized(){
	;
}

void EQComponent::drag(const MouseEvent &event){
	float xPos = event.x;
	float yPos = event.y;

	for(int i = 0; i < numOfFilters; i++){
		if(filterObjects[i]->isSelected()){
			float Fc = x2freq(xPos - getXorigin());
			float gain = y2gain(yPos);
			
			if(gain > 0.f)
				gain = 0.f;
			if(gain < -24.f)
				gain = -24.f;
			
			if(setQ){
				filterObjects[i]->setQ(((yPos - getYorigin()) / getHeight()));
				
				if(filterObjects[i]->getFilterQ() < 0.25f)
					filterObjects[i]->setQ(0.25f);
				if(filterObjects[i]->getFilterQ() > 1.f)
					filterObjects[i]->setQ(1.f);
			}
			else{
				filterObjects[i]->setFc(Fc);
				filterObjects[i]->setGain(gain);
				if(i == 0){
					if(filterObjects[i]->getFilterFc() < 20.f)
						filterObjects[i]->setFc(20.f);
					if(filterObjects[i]->getFilterFc() > 500.f)
						filterObjects[i]->setFc(500.f);
				}
				if(i == 1){
					if(filterObjects[i]->getFilterFc() < 500.f)
						filterObjects[i]->setFc(500.f);
					if(filterObjects[i]->getFilterFc() > 5000.f)
						filterObjects[i]->setFc(5000.f);
				}
				if(i == 2){
					if(filterObjects[i]->getFilterFc() < 5000.f)
						filterObjects[i]->setFc(5000.f);
					if(filterObjects[i]->getFilterFc() > 20000.f)
						filterObjects[i]->setFc(20000.f);
				}
			}
		}
	}
}

void EQComponent::down (const MouseEvent &event){
	int numOfClicks = event.getNumberOfClicks();
	int xPos		= event.getMouseDownX();
	int yPos 		= event.getMouseDownY();
	
	for(auto filter: filterObjects){
		int markerSize = filter->getMarkerSize();
		int markerXpos = filter->getMarkerPos(FilterObject::x);
		int markerYpos = filter->getMarkerPos(FilterObject::y);
		if(xPos > (markerXpos - markerSize) && xPos < (markerXpos + markerSize) && yPos > (markerYpos - markerSize) && yPos < (markerYpos + markerSize)){
			if(numOfClicks < 2)
				filter->setSelected(true);
			else{
				filter->setInitialState();
				updateMarkerPos();
			}
		}
	}
}

void EQComponent::up (const MouseEvent &event){
	for(auto filter: filterObjects)
		filter->setSelected(false);
}

void EQComponent::shiftDown(const ModifierKeys &modifiers){
	setQ = modifiers.isShiftDown();
}

void EQComponent::updateMarkerPos(){
	int x, y;
	
	for(auto filter: filterObjects){
		x = freq2x(filter->getFilterFc()) + getXorigin() - (filter->getMarkerSize() / 2);
		y = gain2y(filter->getFilterGain()) - (filter->getMarkerSize() / 2);
	
		filter->setMarkerPos(x, y);
	}
}

void EQComponent::setInitVals(int selector, float inFc, float inG, float inQ){
	filterObjects[selector]->setInitVals(inFc, inG, inQ);
}





