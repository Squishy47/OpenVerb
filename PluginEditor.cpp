/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamsPlugin1AudioProcessorEditor::SamsPlugin1AudioProcessorEditor (SamsPlugin1AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p){
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize (windowWidth, windowHeight);


		
	textXPos.resize(numOfParams);
	textYPos.resize(numOfParams);
		
	for(int i = 0; i < numOfFilters; i++)
		for(int j = 0; j < 3; j++)
			labels.push_back(new Label);
		
		
	for(int i = 0; i < 6; i++)
		spatialLabels.push_back(new Label);
		
		
	feedbackEQ.setXorigin(spacer);
	feedbackEQ.setYorigin(spacer);
	feedbackEQ.setWidth(int(windowWidth*0.75 - spacer*2));
	feedbackEQ.setHeight(120);
		
	spatializer.setXorigin((windowWidth - spacer - 150));
	spatializer.setYorigin(spacer);
	spatializer.setWidth(150);
	spatializer.setHeight(150);
	spatializer.initMarker();
		
		
	Colour  white	   	(255, 255, 255),
			black	   	(0,   0,   0),
			orange	   	(255, 160, 0),
			lightGrey  	(170, 170, 170),
			darkGrey   	(85,  85,  85),
			transparent	(0x00000000),
			darkBlue	(14, 34, 47);
		
		
	for(auto dial: dials){
		addAndMakeVisible              			(dial->slider);
		dial->slider.setRange          			(dial->minValue, dial->maxValue, dial->stepSize);
		dial->slider.setValue          			(dial->initValue);
		dial->slider.setSliderStyle    			(Slider::RotaryVerticalDrag);
		dial->slider.setTextValueSuffix			(dial->suffix);
		dial->slider.setTextBoxStyle   			(Slider::TextBoxBelow, false, textWidth, textHeight);
		dial->slider.setColour         			(Slider::backgroundColourId, 		 	white);
		dial->slider.setColour         			(Slider::thumbColourId, 			  	transparent);
		dial->slider.setDoubleClickReturnValue	(true, dial->initValue);
		dial->slider.setColour 	       			(Slider::rotarySliderFillColourId,   	orange);
		dial->slider.setColour         			(Slider::rotarySliderOutlineColourId,	black);
		dial->slider.setColour         			(Slider::textBoxTextColourId, 		 	white);
		dial->slider.setColour         			(Slider::textBoxBackgroundColourId,   	transparent);
		dial->slider.setColour 	       			(Slider::textBoxOutlineColourId, 	 	transparent);
		dial->slider.addListener       			(this);
	}
		
	addAndMakeVisible (ERSizeSelector);
	ERSizeSelector.setEditableText (false);
	ERSizeSelector.setJustificationType (Justification::centred);
	ERSizeSelector.setTextWhenNothingSelected (String());
	ERSizeSelector.setColour(ComboBox::backgroundColourId, Colour (14, 34, 47));
	ERSizeSelector.setColour(ComboBox::outlineColourId, Colour (transparent));

	ERSizeSelector.addItem (TRANS("Bathroom"), 1);
	ERSizeSelector.addItem (TRANS("Room"), 2);
	ERSizeSelector.addItem (TRANS("Hall"), 3);
	ERSizeSelector.addItem (TRANS("Church"), 4);
	ERSizeSelector.addItem (TRANS("Cathedral"), 5);
	ERSizeSelector.addItem (TRANS("Random"), 6);
	ERSizeSelector.setSelectedItemIndex(processor.uiDropDownValues[0]);
	ERSizeSelector.addListener (this);
	ERSizeSelector.setBounds (feedbackEQ.getXorigin(), feedbackEQ.getYorigin() + feedbackEQ.getHeight() + spacer*3 + spacer / 2 + dialHeight + 25, dialWidth * 2, 25);
		
		
		
	addAndMakeVisible (Quality);
	Quality.setEditableText (false);
	Quality.setJustificationType (Justification::centred);
	Quality.setTextWhenNothingSelected (String());
	Quality.setColour(ComboBox::backgroundColourId, Colour (14, 34, 47));
	Quality.setColour(ComboBox::outlineColourId, Colour (transparent));
	Quality.addItem (TRANS("Low"), 1);
	Quality.addItem (TRANS("High"), 2);
	Quality.setSelectedItemIndex(processor.uiDropDownValues[1]);
	Quality.addListener (this);
	Quality.setBounds (feedbackEQ.getXorigin(), feedbackEQ.getYorigin() + feedbackEQ.getHeight() + spacer*3 + dialHeight, dialWidth * 2, 25);

		
	float labelWidth = (feedbackEQ.getWidth() / 9);
		
	for(int i = 0; i < labels.size(); i++){
		addAndMakeVisible 				(labels[i]);
		labels[i]->setFont 				(Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
		labels[i]->setJustificationType (Justification::centred);
		labels[i]->setEditable 			(false, false, false);
		labels[i]->setColour 			(Label::backgroundColourId, 		transparent);
		labels[i]->setColour 			(Label::outlineColourId, 			transparent);
		labels[i]->setColour 			(TextEditor::textColourId, 			white);
		labels[i]->setColour 			(TextEditor::backgroundColourId, 	darkGrey);
		labels[i]->setColour 			(TextEditor::highlightColourId, 	Colour (0xffffb600));
		labels[i]->setBounds			(feedbackEQ.getXorigin() + (i * labelWidth), feedbackEQ.getYorigin() + feedbackEQ.getHeight(), labelWidth, 25);
	}
		
	for(int i = 0; i < spatialLabels.size(); i++){
		addAndMakeVisible 						(spatialLabels[i]);
		spatialLabels[i]->setFont 				(Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
		spatialLabels[i]->setJustificationType 	(Justification::centred);
		spatialLabels[i]->setEditable 			(false, false, false);
		spatialLabels[i]->setColour 			(Label::backgroundColourId, 		transparent);
		spatialLabels[i]->setColour 			(Label::outlineColourId, 			transparent);
		spatialLabels[i]->setColour 			(TextEditor::textColourId, 			white);
		spatialLabels[i]->setColour 			(TextEditor::backgroundColourId, 	darkGrey);
		spatialLabels[i]->setColour 			(TextEditor::highlightColourId, 	Colour (0xffffb600));
	}
		
		
	int spatialLabelWidth = 40;
	int spatialLabelHeight = 25;
	spatialLabels[0]->setBounds	(spatializer.getXOrigin(),
								 spatializer.getYOrigin() + spatializer.getHeight(),
								 spatialLabelWidth, spatialLabelHeight);
		
	spatialLabels[1]->setBounds	(spatializer.getXOrigin() + spatializer.getWidth() - spatialLabelWidth,
								 spatializer.getYOrigin() + spatializer.getHeight(),
								 spatialLabelWidth, spatialLabelHeight);
		
	spatialLabels[2]->setBounds	(spatializer.getXOrigin() + spatializer.getWidth(),
								 spatializer.getYOrigin(),
								 spatialLabelWidth, spatialLabelHeight);
		
	spatialLabels[3]->setBounds	(spatializer.getXOrigin() + spatializer.getWidth(),
								 spatializer.getYOrigin() + spatializer.getHeight() - spatialLabelHeight,
								 spatialLabelWidth, spatialLabelHeight);
		
	spatialLabels[4]->setBounds	(spatializer.getXOrigin() - spatialLabelWidth,
								 spatializer.getYOrigin(),
								 spatialLabelWidth, spatialLabelHeight);
		
	spatialLabels[5]->setBounds	(spatializer.getXOrigin() - spatialLabelWidth,
								 spatializer.getYOrigin() + spatializer.getHeight() - spatialLabelHeight,
								 spatialLabelWidth, spatialLabelHeight);


		
	for(int i = 0; i < numOfParams; i++){
		textXPos[i] = (textWidth * i) + (spacer / 2) + spacer + ((spacer / 2) * i);
		textYPos[i] = (spacer * 2) + feedbackEQ.getHeight() + feedbackEQ.getYorigin() - textHeight;
		
		dials[i]->xPos = (dialWidth * i) + (spacer / 2) + spacer + ((spacer / 2) * i);
		dials[i]->yPos = (spacer * 2) + feedbackEQ.getHeight() + feedbackEQ.getYorigin();
		
		if(i > 6){
			textXPos[i] = windowWidth - spacer - (textWidth * (9 - i)) - + ((spacer / 2) * (9 - i));
			textYPos[i] = (spacer * 3) + feedbackEQ.getHeight() + feedbackEQ.getYorigin() + dialHeight;
			
			dials[i]->xPos = windowWidth - spacer - (dialWidth * (9 - i)) - + ((spacer / 2) * (9 - i));
			dials[i]->yPos = (spacer * 3) + feedbackEQ.getHeight() + feedbackEQ.getYorigin() + dialHeight + textHeight;
		}
		
		dials[i]->slider.setBounds(dials[i]->xPos, dials[i]->yPos, dialWidth, dialHeight);
	}
	
	// Filter setup
	float initGain 	= 0.f;
	float initQ = 0.707;
		
	setFilterParams(0, processor.uiFilterValues[0], processor.uiFilterValues[1], processor.uiFilterValues[2]);
	setFilterParams(1, processor.uiFilterValues[3], processor.uiFilterValues[4], processor.uiFilterValues[5]);
	setFilterParams(2, processor.uiFilterValues[6], processor.uiFilterValues[7], processor.uiFilterValues[8]);

	setLabelText(processor.uiFilterValues[0], "Hz", 0);
	setLabelText(processor.uiFilterValues[1], "dB", 1);
	setLabelText(processor.uiFilterValues[2], "",   2);
		
	setLabelText(processor.uiFilterValues[3], "Hz", 3);
	setLabelText(processor.uiFilterValues[4], "dB", 4);
	setLabelText(processor.uiFilterValues[5], "",   5);
		
	setLabelText(processor.uiFilterValues[6], "Hz", 6);
	setLabelText(processor.uiFilterValues[7], "dB", 7);
	setLabelText(processor.uiFilterValues[8], "",   8);
		
	feedbackEQ.setInitVals(0, 20, 		initGain, initQ);
	feedbackEQ.setInitVals(1, 1000, 	initGain, initQ);
	feedbackEQ.setInitVals(2, 20000, 	initGain, initQ);

	feedbackEQ.updateMarkerPos();

	for(int i = 0; i < dials.size(); i++)
		dials[i]->slider.setValue(processor.uiDialValues[i]);
}

SamsPlugin1AudioProcessorEditor::~SamsPlugin1AudioProcessorEditor(){}

//==============================================================================
void SamsPlugin1AudioProcessorEditor::paint (Graphics& g){
	g.fillAll (Colour (0xff4B4B4B)); // background fill colour
	
	// background for the dials
	g.setColour (Colour (14, 34, 47));
	g.fillRoundedRectangle(spacer, feedbackEQ.getXorigin() + feedbackEQ.getHeight() + spacer + spacer/2,
						   windowWidth - spacer*2, textHeight+dialHeight, 5);
	
	// background for bottom row dials
	g.fillRoundedRectangle(windowWidth - (spacer *2) - (dialWidth * 2) - spacer/2,
						   feedbackEQ.getXorigin() + feedbackEQ.getHeight() + spacer*2 + spacer/2+textHeight+dialHeight,
						   dialWidth * 2 + spacer * 2 - spacer/2,
						   textHeight+dialHeight, 5);

	
	g.setColour (Colour (255, 255, 255));
	g.setFont (15.0f);
	for(int i = 0; i < numOfParams; i++){
		if(ERSizeSelector.getSelectedItemIndex() != 5){
			if(i == 6)
				g.setColour (Colour (170, 170, 170));
			else
				g.setColour (Colour (255, 255, 255));
		}
		else
			g.setColour (Colour (255, 255, 255));

		g.drawFittedText(dials[i]->name, textXPos[i], textYPos[i], textWidth, textHeight, Justification::centred, 1);
	}
	
	feedbackEQ.paint(g);
	spatializer.paint(g);
}

void SamsPlugin1AudioProcessorEditor::resized(){
	;
}

void SamsPlugin1AudioProcessorEditor::sliderValueChanged (Slider* slider){
	float sliderValue = 0.f;
	
	if(slider == &dials[0]->slider){
		processor.uiDialValues[0] = dials[0]->slider.getValue();
		
		float dialVal = dials[0]->slider.getValue();
		
		int lower = floor(dialVal);
		int upper = lower + 1;
		
		double interpAmount = dialVal - lower;
		
		double output = (LUT[upper - 1] * interpAmount) + (LUT[lower - 1] * (1 - interpAmount));
		processor.LRL.setLRDelayLength(output);
		processor.LRR.setLRDelayLength(output);
	}
	if(slider == &dials[1]->slider){
		processor.uiDialValues[1] = dials[1]->slider.getValue();
		sliderValue = dials[1]->slider.getValue();					// predelay
		processor.PDL.setDelayLength(sliderValue);
		processor.PDR.setDelayLength(sliderValue);
	}

	if(slider == &dials[2]->slider)	{								// er/lr mix
		processor.uiDialValues[2] = dials[2]->slider.getValue();
		processor.erMix = dials[2]->slider.getValue() / 100;
	}
	if(slider == &dials[3]->slider){								// Width
		processor.uiDialValues[3] = dials[3]->slider.getValue();

		sliderValue = dials[3]->slider.getValue() / 100;
		processor.widthMix = sliderValue;
		processor.widthMix = sliderValue;
	}

	if(slider == &dials[4]->slider){								// mod rate
		processor.uiDialValues[4] = dials[4]->slider.getValue();
		sliderValue = dials[4]->slider.getValue();
		processor.LRR.setModRate(sliderValue);
		processor.LRL.setModRate(sliderValue);
	}
	if(slider == &dials[5]->slider){								// Mod depth
		processor.uiDialValues[5] = dials[5]->slider.getValue();

		sliderValue = dials[5]->slider.getValue() * 0.25;
		processor.LRL.setModDepth(sliderValue);
		processor.LRR.setModDepth(sliderValue);
	}

	if(slider == &dials[6]->slider){								// Rand Seed
		processor.uiDialValues[6] = dials[6]->slider.getValue();

		sliderValue = dials[6]->slider.getValue();
		processor.ERL.setRandomSeed(sliderValue);
		processor.ERR.setRandomSeed(sliderValue);
	}
	
	if(slider == &dials[7]->slider){									//wetdry
		processor.uiDialValues[7] = dials[7]->slider.getValue();
		processor.mix = dials[7]->slider.getValue() / 100;
	}
	if(slider == &dials[8]->slider){								// wet gain
		processor.uiDialValues[8] = dials[8]->slider.getValue();

		sliderValue = pow(10, dials[8]->slider.getValue() / 20);
		processor.outGainL.setGain(sliderValue);
		processor.outGainR.setGain(sliderValue);
	}//Vs = Vn * 10dB/20
}

void SamsPlugin1AudioProcessorEditor::setLabelText(float inValue, String appendedText, int selector){
	inValue = floor(inValue * 100.0) / 100.0;
	
	labels[selector]->setText(String(inValue) + appendedText, dontSendNotification);
}

void SamsPlugin1AudioProcessorEditor::setFilterParams(int selector, float Fc, float gain, float Q){
	gain = juce::Decibels::decibelsToGain(gain);
	
	switch(selector){
		case 0:
			processor.uiFilterValues[0] = Fc;
			processor.uiFilterValues[1] = juce::Decibels::gainToDecibels(gain);
			processor.uiFilterValues[2] = Q;
			break;
		case 1:
			processor.uiFilterValues[3] = Fc;
			processor.uiFilterValues[4] = juce::Decibels::gainToDecibels(gain);
			processor.uiFilterValues[5] = Q;
			break;
		case 2:
			processor.uiFilterValues[6] = Fc;
			processor.uiFilterValues[7] = juce::Decibels::gainToDecibels(gain);
			processor.uiFilterValues[8] = Q;
			break;
	}
	

	processor.LRL.setFilterParams(selector, Fc, gain, Q);
	processor.LRR.setFilterParams(selector, Fc, gain, Q);
	
	processor.LRL.getFilterCoefs(coefs, selector);
	
	feedbackEQ.setFilterCoefs(coefs, selector);
	feedbackEQ.setFilterParams(selector, Fc, gain, Q);

	setLabelText(Fc, "Hz", (selector * 3));
	setLabelText(juce::Decibels::gainToDecibels(gain), "dB", (selector * 3) + 1);
	setLabelText(Q, "", (selector * 3) + 2);
	repaint();
}

void SamsPlugin1AudioProcessorEditor::comboBoxChanged (ComboBox* comboBox){
	if(comboBox == &ERSizeSelector){
		processor.uiDropDownValues[0] = ERSizeSelector.getSelectedItemIndex();

		processor.ERL.setSize(ERSizeSelector.getSelectedItemIndex());
		processor.ERR.setSize(ERSizeSelector.getSelectedItemIndex());
		
		if(ERSizeSelector.getSelectedItemIndex() != 5){
			dials[6]->slider.setColour         			(Slider::backgroundColourId, 		 	Colour(170, 170, 170));
			dials[6]->slider.setColour 	       			(Slider::rotarySliderFillColourId,   	Colour(170, 75, 0));
			dials[6]->slider.setColour         			(Slider::rotarySliderOutlineColourId,	Colour(0,   0,   0));
			dials[6]->slider.setColour         			(Slider::textBoxTextColourId, 		 	Colour(170, 170, 170));
		}
		else{
			dials[6]->slider.setColour         			(Slider::backgroundColourId, 		 	Colour(255, 255, 255));
			dials[6]->slider.setColour 	       			(Slider::rotarySliderFillColourId,   	Colour(255, 160, 0));
			dials[6]->slider.setColour         			(Slider::textBoxTextColourId, 		 	Colour(255, 255, 255));
		}
		
		processor.ERL.setRoomPosition(spatializer.getXvalue(), 0); // x
		processor.ERR.setRoomPosition(spatializer.getXvalue(), 0); // x
		processor.ERL.setRoomPosition(spatializer.getYvalue(), 1); // y
		processor.ERR.setRoomPosition(spatializer.getYvalue(), 1); // y
		processor.ERL.setRoomPosition(spatializer.getZvalue(), 2); // z
		processor.ERR.setRoomPosition(spatializer.getZvalue(), 2); // z
		
		for(int i = 0; i < spatialLabels.size(); i++)
			spatialLabels[i]->setText(String((floorf(processor.ERL.getRoomDimensions(i) * 100) / 100)), dontSendNotification);
	}
	if(comboBox == &Quality){
		processor.uiDropDownValues[1] = Quality.getSelectedItemIndex();

		processor.LRL.setNumOfTaps(Quality.getSelectedItemIndex());
		processor.LRR.setNumOfTaps(Quality.getSelectedItemIndex());
	}
}

void SamsPlugin1AudioProcessorEditor::mouseDown(const MouseEvent &event){
	feedbackEQ.down(event);
	spatializer.down(event);
}

void SamsPlugin1AudioProcessorEditor::mouseUp(const MouseEvent &event){
	feedbackEQ.up(event);
	spatializer.up(event);
}

void SamsPlugin1AudioProcessorEditor::mouseDrag(const MouseEvent &event){
	feedbackEQ.drag(event);
	spatializer.drag(event);
	
	for(int i = 0; i < numOfFilters; i++)
		setFilterParams(i, 	feedbackEQ.getFilterParams(EQComponent::Fc, 	i),
							feedbackEQ.getFilterParams(EQComponent::Gain, 	i),
							feedbackEQ.getFilterParams(EQComponent::Q, 		i));
	
	processor.uiSpatialValues[0] = spatializer.getMarkerXpos();
	processor.uiSpatialValues[1] = spatializer.getMarkerYpos();
	processor.uiSpatialValues[2] = spatializer.getMarkerSize();

	processor.ERL.setRoomPosition(spatializer.getXvalue(), 0); // x
	processor.ERR.setRoomPosition(spatializer.getXvalue(), 0); // x
	processor.ERL.setRoomPosition(spatializer.getYvalue(), 1); // y
	processor.ERR.setRoomPosition(spatializer.getYvalue(), 1); // y
	processor.ERL.setRoomPosition(spatializer.getZvalue(), 2); // z
	processor.ERR.setRoomPosition(spatializer.getZvalue(), 2); // z
		
	for(int i = 0; i < spatialLabels.size(); i++)
		spatialLabels[i]->setText(String((floorf(processor.ERL.getRoomDimensions(i) * 100) / 100)), dontSendNotification);

	repaint();
}

void SamsPlugin1AudioProcessorEditor::modifierKeysChanged(const ModifierKeys &modifiers){
	feedbackEQ.shiftDown(modifiers);
	spatializer.shiftDown(modifiers);
}

