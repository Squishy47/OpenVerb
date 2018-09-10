/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SamsPlugin1AudioProcessor::SamsPlugin1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
:
     AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

SamsPlugin1AudioProcessor::~SamsPlugin1AudioProcessor()
{
}

//==============================================================================
const String SamsPlugin1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SamsPlugin1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SamsPlugin1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SamsPlugin1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SamsPlugin1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SamsPlugin1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SamsPlugin1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void SamsPlugin1AudioProcessor::setCurrentProgram (int index)
{
}

const String SamsPlugin1AudioProcessor::getProgramName (int index)
{
    return {};
}

void SamsPlugin1AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SamsPlugin1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	widthMixSmoother.reset	(sampleRate, 0.01);
	wetDrySmoother.reset	(sampleRate, 0.01);
	mixSmoother.reset		(sampleRate, 0.01);
	
	
	dryGainL.setFs(sampleRate);
	dryGainR.setFs(sampleRate);
	
	wetGainL.setFs(sampleRate);
	wetGainR.setFs(sampleRate);
	
	outGainL.setFs(sampleRate);
	outGainR.setFs(sampleRate);

	
	ERL.setFs(sampleRate);
	ERR.setFs(sampleRate);
	
	LRL.setFs(sampleRate);
	LRR.setFs(sampleRate);

    PDL.setFs(sampleRate);
    PDR.setFs(sampleRate);

    //    setLatencySamples(0);
}

void SamsPlugin1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SamsPlugin1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SamsPlugin1AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	wetDrySmoother.getNextValue();
	
	
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // stops feedback on unused output channels. Do Not Delete!
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // Get buffer size
    int bufferSize = buffer.getNumSamples();
	
	// Get channel data
    float* xl = buffer.getWritePointer(0);
	float* xr = buffer.getWritePointer(1);
	
	float 	xl1[bufferSize], xr1[bufferSize],
			xl2[bufferSize], xr2[bufferSize],
			lrrTemp[bufferSize],
			wetL[bufferSize], wetR[bufferSize];
	
	// Set extra variables to the audio data
    for(int i = 0; i < bufferSize; i++){
        xl1[i] = PDL.processSingleSample(buffer.getWritePointer(0)[i]);
        xr1[i] = PDR.processSingleSample(buffer.getWritePointer(1)[i]);
        xl2[i] = xl1[i];
        xr2[i] = xr1[i];
    }

	
	// Process early reflections (ER)
    ERL.process(xl1, bufferSize, 0);
    ERR.process(xr1, bufferSize, 1);

	widthMixSmoother.setValue(widthMix);
	for(int i = 0; i < bufferSize; i++){
		// Feed ER into late reflections (LR)
		xl2[i] = (xl1[i] + xl2[i]) / 2;
		xr2[i] = (xr1[i] + xr2[i]) / 2;
		
		// x-feed the channels
		lrrTemp[i] = widthMixSmoother.getNextValue() * xr2[i];
		xr2[i] 	  += widthMixSmoother.getNextValue() * xl2[i];
		xl2[i]    += lrrTemp[i];
		
		xr2[i] = xr2[i] * (widthMixSmoother.getNextValue() * -1 * 0.4 + 1);
		xl2[i] = xl2[i] * (widthMixSmoother.getNextValue() * -1 * 0.4 + 1);
	}
	
	
	// Process LR
    LRL.process(xl2, bufferSize, 0);
	LRR.process(xr2, bufferSize, 1);
	
	mixSmoother.setValue(erMix);
	// Mix between ER and LR
	for(int i = 0; i < bufferSize; i++){
		// https://www.safaribooksonline.com/library/view/web-audio-api/9781449332679/s03_2.html
		float gain1 = cos(mixSmoother.getNextValue() * 0.5 * M_PI);
		float gain2 = cos((1.0 - mixSmoother.getNextValue()) * 0.5 * M_PI);

		wetL[i] = (gain2 * xl2[i]) + (gain1 * xl1[i]);
		wetR[i] = (gain2 * xr2[i]) + (gain1 * xr1[i]);
	}
	
	
	
	
	// Process output gain
	outGainL.process(wetL, bufferSize);
	outGainR.process(wetR, bufferSize);
	
	wetDrySmoother.setValue(mix);
	// Mix between wet and dry
	for(int i = 0; i < bufferSize; i++){
		// https://www.safaribooksonline.com/library/view/web-audio-api/9781449332679/s03_2.html
		float gain1 = cos(wetDrySmoother.getNextValue() * 0.5 * M_PI);
		float gain2 = cos((1.0 - wetDrySmoother.getNextValue()) * 0.5 * M_PI);
	
		xl[i] = (gain2 * wetL[i]) + (gain1 * xl[i]);
		xr[i] = (gain2 * wetR[i]) + (gain1 * xr[i]);
	}
}

//==============================================================================
bool SamsPlugin1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SamsPlugin1AudioProcessor::createEditor()
{
    return new SamsPlugin1AudioProcessorEditor (*this);
}

//==============================================================================
void SamsPlugin1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SamsPlugin1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SamsPlugin1AudioProcessor();
}
