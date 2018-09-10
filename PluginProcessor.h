/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//USER CLASSES=====================================================================
#include "VecTemplate.hpp"
#include "Gain.hpp"
#include "EarlyReflections.hpp"
#include "LateReflections.hpp"
#include "PreDelay.hpp"

//==============================================================================
/**
*/
class SamsPlugin1AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SamsPlugin1AudioProcessor();
    ~SamsPlugin1AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //USER VARIABLES================================================================
	EarlyReflections ERL{}, ERR{};
	LateReflections  LRL{}, LRR{};
	PreDelay 		 PDL{}, PDR{};
	
	LinearSmoothedValue<float> wetDrySmoother;
	LinearSmoothedValue<float> mixSmoother;
	LinearSmoothedValue<float> widthMixSmoother;
	
	float uiDropDownValues[2] 	= {0.f, 1.f};
	float uiSpatialValues[3] 	= {675, 105, 20};
	
	
	
	float uiFilterValues[9] 	= {20, 0.f, 0.707, 1000, 0.f, 0.707, 20000, 0.f, 0.707};
	float uiDialValues[9] 		= {1.000f, 25.00f, 50.00f, 0.000f, 0.000f, 50.00f, 50.00f, 50.00f, 0.000f};
	
	Gain 	dryGainL{1.0f}, dryGainR{1.0f},
			wetGainL{1.0f}, wetGainR{1.0f},
			outGainL{1.0f}, outGainR{1.0f};
	
    float 	mix 	 = 0.5f,
			erMix 	 = 0.5f,
			widthMix = 0.0f;

	
	
	
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamsPlugin1AudioProcessor)
};
