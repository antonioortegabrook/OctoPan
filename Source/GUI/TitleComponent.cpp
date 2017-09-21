/*
 ==============================================================================
 
 TitleComponent.cpp
 Created: 13 Sep 2017 3:45:54pm
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "TitleComponent.h"
#include "ast_colours.h"

//==============================================================================
TitleComponent::TitleComponent()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.
	
}

TitleComponent::~TitleComponent()
{
}

void TitleComponent::paint (Graphics& g)
{
	/* This demo code just fills the component's background and
	 draws some placeholder text to get you started.
	 
	 You should replace everything in this method with your own
	 drawing code..
	 */
	
        Rectangle<float> area(getLocalBounds().toFloat());
        
        g.setColour(GREY_FOREGROUND);
        g.drawText("OctoPan", area, Justification::bottomRight);
        
}

void TitleComponent::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
	
}
