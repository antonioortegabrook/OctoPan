/*
 ==============================================================================
 
 SourceComponent.cpp
 Created: 13 Sep 2017 3:30:36pm
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"

#include "SourceComponent.h"
#include "AstSliderLookAndFeel.h"
#include "ast_colours.h"
#include "dims.h"


//==============================================================================
SourceComponent::SourceComponent()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.
	
//	getLookAndFeel().setDefaultSansSerifTypefaceName("Arial Narrow");
	
	sectionTitle.setTitle("Source");
	addAndMakeVisible(sectionTitle);
	
	//-----------

	azimuthSlider.setSliderStyle (Slider::LinearHorizontal);
	azimuthSlider.setLookAndFeel(&sliderLookAndFeel);
	azimuthSlider.setTextBoxStyle (Slider::TextBoxRight, false, 32, 20);

	azimuthSlider.setRange(-180, 180);

        addAndMakeVisible(azimuthSlider);
	
	azimuthLabel.setText("Azimuth", dontSendNotification);
	azimuthLabel.setJustificationType(Justification::centredRight);
	azimuthLabel.attachToComponent(&azimuthSlider, true);
	azimuthLabel.setFont(Font::Font("Arial Narrow", "Regular", 13));
        azimuthLabel.Component::setColour(Label::textColourId, WHITE_TEXT_1);
	azimuthLabel.setBorderSize(BorderSize<int> (0));
	addAndMakeVisible(azimuthLabel);

	//-----------
	
	spreadSlider.setSliderStyle (Slider::LinearHorizontal);
	spreadSlider.setLookAndFeel(&sliderLookAndFeel);
	spreadSlider.setTextBoxStyle (Slider::TextBoxRight, false, 32, 20);

	spreadSlider.setRange(0, 100);
	addAndMakeVisible(spreadSlider);
	
	spreadLabel.setText("Spread", dontSendNotification);
	spreadLabel.setJustificationType(Justification::centredRight);
	spreadLabel.attachToComponent(&spreadSlider, true);
	spreadLabel.setFont(Font::Font("Arial Narrow", "Regular", 13));
        spreadLabel.Component::setColour(Label::textColourId, WHITE_TEXT_1);
	spreadLabel.setBorderSize(BorderSize<int> (0));
	addAndMakeVisible(spreadLabel);
	
	//-----------
	
	densitySlider.setSliderStyle (Slider::LinearHorizontal);
	densitySlider.setLookAndFeel(&sliderLookAndFeel);
	densitySlider.setTextBoxStyle (Slider::TextBoxRight, false, 32, 20);
	
	densitySlider.setRange(-10, 10);
	addAndMakeVisible(densitySlider);
	
	densityLabel.setText("Density", dontSendNotification);
	densityLabel.setJustificationType(Justification::centredRight);
	densityLabel.attachToComponent(&densitySlider, true);
	densityLabel.setFont(Font::Font("Arial Narrow", "Regular", 13));
        densityLabel.Component::setColour(Label::textColourId, WHITE_TEXT_1);
	densityLabel.setBorderSize(BorderSize<int> (0));
	addAndMakeVisible(densityLabel);
	
}

SourceComponent::~SourceComponent()
{
}

void SourceComponent::paint (Graphics& g)
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

void SourceComponent::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
	Rectangle<int> area (getLocalBounds().reduced(ST_SPACING));
	
	sectionTitle.setBounds(area.removeFromTop(ST_HEIGHT));
	
	area = area.reduced(4).withTrimmedTop(2).withTrimmedLeft(40);
	int sliderHeight = area.getHeight() / 3;
	
	azimuthSlider.setBounds(area.removeFromTop(sliderHeight));
	spreadSlider.setBounds(area.removeFromTop(sliderHeight));
	densitySlider.setBounds(area.removeFromTop(sliderHeight));
}
