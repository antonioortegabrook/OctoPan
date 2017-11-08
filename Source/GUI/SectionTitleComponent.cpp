/*
 ==============================================================================
 
 SectionTitleComponent.cpp
 Created: 15 Sep 2017 1:26:28am
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "SectionTitleComponent.h"
#include "ast_colours.h"
#include "dims.h"

//==============================================================================
SectionTitleComponent::SectionTitleComponent()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.
	
    titleFont = Font(Typeface::createSystemTypefaceFor(BinaryData::ITCFranklinGothicStdBook_otf,
						       BinaryData::ITCFranklinGothicStdBook_otfSize));
    titleFont.setHeight(13);
}

SectionTitleComponent::~SectionTitleComponent()
{
//	title = "";
	title.setText("");
}

void SectionTitleComponent::paint (Graphics& g)
{
	/* This demo code just fills the component's background and
	 draws some placeholder text to get you started.
	 
	 You should replace everything in this method with your own
	 drawing code..
	 */
	
	Rectangle<float> area(getLocalBounds().toFloat());
	
	g.setColour(GREY_BACKGROUND);
	g.fillRoundedRectangle(area, ROUNDNESS);
	
	title.setFont(titleFont);
	title.setJustification(Justification::centredLeft);
	title.setWordWrap(juce::AttributedString::none);
	title.setColour(WHITE_TEXT_1);
	
	title.draw(g, area.reduced(SPACING, 0));
}

void SectionTitleComponent::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
	
}

void SectionTitleComponent::setTitle(juce::String newTitle)
{
//	title = newTitle;
	title.setText(newTitle);
}
