/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin editor.

==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "VecTemplate.hpp"
#include "EQComponent.hpp"
#include "SliderWrapper.hpp"
#include "SpatializeComponent.hpp"

//==============================================================================
/**
*/
class SamsPlugin1AudioProcessorEditor:  public AudioProcessorEditor,
                                        public Slider::Listener,
                                        public ComboBox::Listener{
    
    SamsPlugin1AudioProcessor& processor;
        
	SpatializeComponent spatializer{};

    int numOfFilters = 3;
        
    EQComponent feedbackEQ{numOfFilters};
        
    ComboBox ERSizeSelector, Quality;
															//max,	min,	step,	init,	xPos,  yPos
	sliderWrapper LRDelayLength {"Decay Length",   " s",   5.000f,  0.200f, 0.100f, 1.000f, 0.00f, 0.00f};
    sliderWrapper preDelayTime	{"Pre-Delay", 	   " ms",  50.00f,  0.000f, 0.500f, 25.00f, 0.00f, 0.00f};
    sliderWrapper erlrMix		{"ER/LR Mix", 	   " %",   100.0f,  0.000f, 1.000f, 50.00f, 0.00f, 0.00f};
	sliderWrapper width			{"Crossfeed", 	   " %",   100.0f,  0.000f, 1.000f, 0.000f, 0.00f, 0.00f};
    sliderWrapper modRate		{"Mod Rate", 	   " Hz",  10.00f,  0.000f, 1.000f, 0.000f, 0.00f, 0.00f};
    sliderWrapper modDepth		{"Mod Depth", 	   " %",   100.0f,  0.000f, 1.000f, 50.00f, 0.00f, 0.00f};
	sliderWrapper randVariation	{"Rand Variation", "",     100.0f,  0.000f, 1.000f, 50.00f, 0.00f, 0.00f};
	sliderWrapper wetDryMix		{"Wet / Dry", 	   " %",   100.0f,  0.000f, 1.000f, 50.00f, 0.00f, 0.00f};
	sliderWrapper outGain		{"Output Gain",    " dB",  6.000f, -60.00f, 0.100f, 0.000f, 0.00f, 0.00f};


    std::vector<sliderWrapper *> dials {
		&LRDelayLength,	//0
        &preDelayTime,	//1
        &erlrMix,		//2
		&width,			//3
        &modRate,		//4
        &modDepth,		//5
        &randVariation, //6
		&wetDryMix,		//7
		&outGain,		//8
    };
        

	std::vector<Label *> labels;
	std::vector<Label *> spatialLabels;
											
				
	float LUT[10] = {0.92, 0.93, 0.94, 0.95, 0.96,
					0.97, 0.99, 0.999, 0.9999, 0.99999};

											
											
											
	float coefs[5];
								
    int numOfParams 	= int(dials.size()),
        dialWidth   	= 80,
        dialHeight  	= 80,
        textWidth   	= 80,
        textHeight  	= 20,
        spacer      	= 40,
        windowWidth 	= 800,
		windowHeight	= 500;
											
	Vec_Float textXPos, textYPos;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamsPlugin1AudioProcessorEditor)
public:
    SamsPlugin1AudioProcessorEditor (SamsPlugin1AudioProcessor&);
    ~SamsPlugin1AudioProcessorEditor();


    void sliderValueChanged (Slider* slider) override;
    void comboBoxChanged 	(ComboBox* comboBoxThatHasChanged) override;
    void setFilterParams	(int selector, float Fc, float gain, float Q);
    void setLabelText		(float inValue, String appendedText, int selector);
    void resized			() override;
    void paint				(Graphics&) override;
    void mouseDown 			(const MouseEvent &event) override;
    void mouseUp 			(const MouseEvent &event) override;
    void mouseDrag 			(const MouseEvent &event) override;
    void modifierKeysChanged(const ModifierKeys &modifiers) override;
};














