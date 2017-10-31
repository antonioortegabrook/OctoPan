/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

// our own headers
#include "angular_panning/angular_panning.h"

#include "GUI/PannerComponent.h"
#include "GUI/SourceComponent.h"
#include "GUI/LayoutComponent.h"
#include "GUI/TitleComponent.h"


//==============================================================================
/**
 */
class OctoPanAudioProcessorEditor	:	public AudioProcessorEditor,
						private AudioProcessorValueTreeState::Listener
{
public:
	OctoPanAudioProcessorEditor (OctoPanAudioProcessor&, AudioProcessorValueTreeState&);
	~OctoPanAudioProcessorEditor();
	
	//==============================================================================
	void paint (Graphics&) override;
	void resized() override;
	
private:
	PannerComponent panner;
	SourceComponent source;
	LayoutComponent layout;
	TitleComponent  title;
        
        typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
        typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
        
        
        ScopedPointer<SliderAttachment> pannerAzimuthAttachment;
        ScopedPointer<SliderAttachment> azimuthAttachment;
        ScopedPointer<SliderAttachment> spreadAttachment;
        ScopedPointer<SliderAttachment> shapeAttachment;
        ScopedPointer<ButtonAttachment> offsetAttachment;

	
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	OctoPanAudioProcessor& processor;
        
        AudioProcessorValueTreeState& valueTreeState;
	
	
	void parameterChanged (const String& parameterID, float newValue) override;
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OctoPanAudioProcessorEditor)
};
