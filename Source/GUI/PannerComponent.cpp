/*
 ==============================================================================
 
 PannerComponent.cpp
 Created: 13 Sep 2017 2:59:41pm
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"

#include "PannerComponent.h"
#include "ast_colours.h"
#include "dims.h"


//==============================================================================
PannerComponent::PannerComponent()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.
	
	addAndMakeVisible(panLayout);
	addAndMakeVisible(dialComponent);
}

PannerComponent::~PannerComponent()
{
}

void PannerComponent::paint (Graphics& g)
{
	/* This demo code just fills the component's background and
	 draws some placeholder text to get you started.
	 
	 You should replace everything in this method with your own
	 drawing code..
	 */
	
	Rectangle<float> background(getLocalBounds().toFloat());
	
	g.setColour(GREY_FOREGROUND);
	g.fillRoundedRectangle(background, ROUNDNESS);
}

void PannerComponent::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
	
	panLayout.setBounds(getLocalBounds());
	dialComponent.setBounds(getLocalBounds());
}

void PannerComponent::setAzimuth(float angleInDegrees)
{
	dialComponent.setAzimuth(angleInDegrees);
}

float PannerComponent::getAzimuth()
{
	float azimuthInDegrees = dialComponent.dial.getValue();
	
	return azimuthInDegrees;
}

void PannerComponent::setWidth(float angleInRadians)
{
        dialComponent.setWidth(angleInRadians);
}

void PannerComponent::setXparam(float angleInRadians)
{
        dialComponent.setXparam(angleInRadians);
}
