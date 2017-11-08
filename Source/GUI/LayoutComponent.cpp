/*
 ==============================================================================
 
 LayoutComponent.cpp
 Created: 13 Sep 2017 3:29:40pm
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "LayoutComponent.h"
#include "ast_colours.h"
#include "dims.h"

//==============================================================================
LayoutComponent::LayoutComponent()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.
        
        sectionTitle.setTitle("Layout");
        addAndMakeVisible(sectionTitle);
        
        offsetButton.setLookAndFeel(&checkBoxLookAndFeel);
        addAndMakeVisible(offsetButton);
	
	Font franklinGothicCondensed = Font(Typeface::createSystemTypefaceFor(BinaryData::ITCFranklinGothicStdBkCd_otf, BinaryData::ITCFranklinGothicStdBkCd_otfSize));
	franklinGothicCondensed.setHeight(12);
	
        offsetLabel.setText("Offset", dontSendNotification);
        offsetLabel.setJustificationType(Justification::centredRight);
        offsetLabel.attachToComponent(&offsetButton, true);
	offsetLabel.setFont(franklinGothicCondensed);
        offsetLabel.Component::setColour(Label::textColourId, WHITE_TEXT_1);
        offsetLabel.setBorderSize(BorderSize<int> (0));
        addAndMakeVisible(offsetLabel);
}

LayoutComponent::~LayoutComponent()
{
	offsetButton.setLookAndFeel(nullptr);    // <-revisar
}

void LayoutComponent::paint (Graphics& g)
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

void LayoutComponent::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
        Rectangle<int> area (getLocalBounds().reduced(ST_SPACING));
        
        sectionTitle.setBounds(area.removeFromTop(ST_HEIGHT));
        
        area = area.reduced(4).withTrimmedTop(2).withTrimmedLeft(40);
        
        offsetButton.setBounds(area.removeFromTop(30));
}
