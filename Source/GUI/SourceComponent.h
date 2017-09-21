/*
 ==============================================================================
 
 SourceComponent.h
 Created: 13 Sep 2017 3:30:36pm
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SectionTitleComponent.h"
#include "AstSliderLookAndFeel.h"
#include "AstSlider_o.h"

//==============================================================================
/*
 */
class SourceComponent    : public Component
{
public:
	SourceComponent();
	~SourceComponent();
	
	AstSlider_o azimuthSlider;
	AstSlider_o spreadSlider;
	AstSlider_o densitySlider;
	
	void paint (Graphics&) override;
	void resized() override;
	
private:
	SectionTitleComponent sectionTitle;
	AstSliderLookAndFeel sliderLookAndFeel;
	
	Label azimuthLabel;
	Label spreadLabel;
	Label densityLabel;
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceComponent)
};
