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
        azimuthSlider.setTextValueSuffix (CharPointer_UTF8 (" \xc2\xb0"));       // (UTF8 degree sign)

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
        spreadSlider.setTextValueSuffix (" %");

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
	
	shapeSlider.setSliderStyle (Slider::LinearHorizontal);
	shapeSlider.setLookAndFeel(&sliderLookAndFeel);
	shapeSlider.setTextBoxStyle (Slider::TextBoxRight, false, 32, 20);
	
	shapeSlider.setRange(-10, 10);
	addAndMakeVisible(shapeSlider);
	
	shapeLabel.setText("Shape", dontSendNotification);
	shapeLabel.setJustificationType(Justification::centredRight);
	shapeLabel.attachToComponent(&shapeSlider, true);
	shapeLabel.setFont(Font::Font("Arial Narrow", "Regular", 13));
	shapeLabel.Component::setColour(Label::textColourId, WHITE_TEXT_1);
	shapeLabel.setBorderSize(BorderSize<int> (0));
	addAndMakeVisible(shapeLabel);
	
}

SourceComponent::~SourceComponent()
{
	azimuthSlider.setLookAndFeel(nullptr);    // <-revisar
	spreadSlider.setLookAndFeel(nullptr);    // <-revisar
	shapeSlider.setLookAndFeel(nullptr);    // <-revisar
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
	shapeSlider.setBounds(area.removeFromTop(sliderHeight));
}
