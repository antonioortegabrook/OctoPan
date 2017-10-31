/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

// our own headers
#include "GUI/ast_colours.h"
#include "GUI/dims.h"

#include "angular_panning/angular_panning.c"



//==============================================================================
OctoPanAudioProcessorEditor::OctoPanAudioProcessorEditor (OctoPanAudioProcessor& p, AudioProcessorValueTreeState& vts)
		:	AudioProcessorEditor (&p),
			processor (p),
			valueTreeState (vts)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(400, 154);
	
	vts.addParameterListener ("spread", this);
	vts.addParameterListener ("shape", this);
	vts.addParameterListener ("offset", this);
	
	
	addAndMakeVisible(source);
	azimuthAttachment = new SliderAttachment (valueTreeState, "azimuth", source.azimuthSlider);
	spreadAttachment  = new SliderAttachment (valueTreeState, "spread",  source.spreadSlider);
	shapeAttachment = new SliderAttachment (valueTreeState, "shape", source.shapeSlider);
	
	addAndMakeVisible(layout);
	offsetAttachment = new ButtonAttachment (valueTreeState, "offset", layout.offsetButton);

	addAndMakeVisible(panner);
	pannerAzimuthAttachment = new SliderAttachment (valueTreeState, "azimuth", panner.dialComponent.dial);
	panner.setWidth(processor.source.width);
	panner.setXparam(clip_r(processor.source.width * map_r(processor.source.shape, -10, 10, 0.2, 0.8),
				processor.layout.spk_diff,
				processor.source.width - processor.layout.spk_diff));
	
	panner.panLayout.setOffset(processor.layout.offset);
	
	addAndMakeVisible(title);
	
}

OctoPanAudioProcessorEditor::~OctoPanAudioProcessorEditor()
{
	valueTreeState.removeParameterListener("spread", this);
	valueTreeState.removeParameterListener("shape", this);
	valueTreeState.removeParameterListener("offset", this);
}

//==============================================================================
void OctoPanAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll(GREY_BACKGROUND);
}

void OctoPanAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	
	Rectangle<int> area (getLocalBounds());
	
	panner.setBounds(area.removeFromLeft(area.getHeight()).reduced(SPACING));
	
	const int sourceHeight = area.getHeight() / 3 * 2;
	source.setBounds(area.removeFromTop(sourceHeight).withTrimmedTop(SPACING).withTrimmedRight(SPACING));
	
	const int layoutWidth = area.getWidth() / 2;
	layout.setBounds(area.removeFromLeft(layoutWidth).reduced(0, SPACING).withTrimmedRight(SPACING));
	
	title.setBounds(area.reduced(0, SPACING).withTrimmedRight(SPACING));
}




/**
 We use this callback to update width and xparam in panner dial and offset in panner layout
 We need to use a mmLock to make sure GUI update is thread-safe when parameters are changed
 via automation.
 */
void OctoPanAudioProcessorEditor::parameterChanged (const String& parameterID, float newValue)
{
	if (!parameterID.compare("spread")) {
		
		double width = spread_to_width(newValue, 2 * processor.layout.spk_diff);
		double tmpxParamWidth = width * map_r(processor.source.shape, -10, 10, 0.2, 0.8);
		double xParamWidth = clip_r(tmpxParamWidth,
					   processor.layout.spk_diff,
					   width - processor.layout.spk_diff);
		
		const MessageManagerLock mmLock;
		panner.setWidth(width);
		panner.setXparam(xParamWidth);
	}
	
	else if (!parameterID.compare("shape")) {
		
		double tmpxParamWidth = processor.source.width * map_r(newValue, -10, 10, 0.2, 0.8);
		double xParamWidth = clip_r(tmpxParamWidth,
					   processor.layout.spk_diff,
					   processor.source.width - processor.layout.spk_diff);
		
		const MessageManagerLock mmLock;
		panner.setXparam(xParamWidth);
	}
	
	else if (!parameterID.compare("offset")) {
		
		const MessageManagerLock mmLock;
		panner.panLayout.setOffset(newValue >= 0.5 ? 0.5 : 0);
	}
}
