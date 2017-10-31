/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "angular_panning/angular_panning.h"


//==============================================================================
/**
 */
class OctoPanAudioProcessor	:	public AudioProcessor
{
public:
	//==============================================================================
	OctoPanAudioProcessor();
	~OctoPanAudioProcessor();
	
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
	
	//==============================================================================
	

	long    nspeakers;
	
	t_source source;
	t_layout layout;
	
	
private:
	AudioProcessorValueTreeState parameters;
	
	double	previousAzimuth;
	double	previousSpread;
	double	previousshape;
	bool	previousOffset;
	
	double  gains[8];
	double  previousGains[8];
	
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OctoPanAudioProcessor)
};
