/*
 ==============================================================================
 
 PanDialComponent.cpp
 Created: 13 Sep 2017 2:48:04pm
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "PanDialComponent.h"

//==============================================================================
PanDialComponent::PanDialComponent()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.

        dial.setSliderStyle (Slider::Rotary);
        dial.setLookAndFeel(&panDialLookAndFeel);
        dial.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        
        dial.setRotaryParameters(float_Pi, 3 * float_Pi, false);
        dial.setRange(-180, 180);
        addAndMakeVisible (dial);
}

PanDialComponent::~PanDialComponent()
{
}

void PanDialComponent::paint (Graphics& g)
{
	/* This demo code just fills the component's background and
	 draws some placeholder text to get you started.
	 
	 You should replace everything in this method with your own
	 drawing code..
	 */
}

void PanDialComponent::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
	const int border = 30;
	
	Rectangle<int> area = getLocalBounds().reduced(border);
	dial.setBounds (area);
}

void PanDialComponent::setAzimuth(float angleInDegrees)
{
        dial.setValue(angleInDegrees);
}

void PanDialComponent::setWidth(float angleInRadians)
{
        panDialLookAndFeel.setWidth(angleInRadians);
        PanDialComponent::repaint();
}

void PanDialComponent::setXparam(float angleInRadians)
{
        panDialLookAndFeel.setshape(angleInRadians);
        PanDialComponent::repaint();
}
