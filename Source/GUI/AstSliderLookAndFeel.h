/*
 ==============================================================================
 
 LinearSliderLookAndFeel.h
 Created: 15 Sep 2017 4:35:09am
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#pragma once

#include "ast_colours.h"

class AstSliderLookAndFeel : public LookAndFeel_V4
{
private:
	const float thumbRadius			= 4;
	const float thumbLineThickness		= 1;
	const float trackLineThickness		= 2;
public:
	AstSliderLookAndFeel()
	{
	}
	
	void drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float 	minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider& slider) override
	{
		const int startX			= x;
		const int endX				= x + width;
		const int startY			= height / 2;
		const int endY				= height / 2;
		
		const int thumbX			= sliderPos - thumbRadius;
		const int thumbY			= height / 2 - thumbRadius;
		const int thumbWidth			= thumbRadius * 2;
		const int thumbHeight			= thumbRadius * 2;
		
		const int zero				= slider.getPositionOfValue(0);

		
		// track ---------
		g.setColour(LIGHT_GREY_DETAIL);
		g.drawLine(startX, startY, endX, endY, trackLineThickness);
		
		// over track ----
		g.setColour(BLUE_DETAIL);
		g.drawLine(zero, startY, sliderPos, endY, trackLineThickness);
		
		// thumb ---------
		g.setColour(SOLID_WHITE);
		g.fillEllipse(thumbX, thumbY, thumbWidth, thumbHeight);
		
		// thumb line ----
		g.setColour(LIGHT_GREY_DETAIL);
		g.drawEllipse(thumbX, thumbY, thumbWidth, thumbHeight, thumbLineThickness);

	}
        
        
	Label* createSliderTextBox(Slider& slider) override
        {
                Label *label = LookAndFeel_V4::createSliderTextBox (slider);
                
                label->setFont(Font::Font("Arial Narrow", "Regular", 13));
                label->setBorderSize(BorderSize<int> (0));
                label->setJustificationType(Justification::centredLeft);
                
                label->Component::setColour(Label::textColourId, WHITE_TEXT_1);
                label->Component::setColour(Label::textWhenEditingColourId, WHITE_TEXT_1);
                
                label->Component::setColour(Label::outlineColourId, Colours::transparentWhite);
                label->Component::setColour(Label::outlineWhenEditingColourId, Colours::transparentWhite);
                
                label->Component::setColour(Label::backgroundColourId, Colours::transparentWhite);
                label->Component::setColour(Label::backgroundWhenEditingColourId, Colours::transparentWhite);
                
                label->Component::setColour(TextEditor::outlineColourId, Colours::transparentWhite);
                
                label->Component::setColour(TextEditor::highlightColourId, BLUE_DETAIL);
                label->Component::setColour(CaretComponent::caretColourId, BLUE_DETAIL);
                
                return label;
        }

};
