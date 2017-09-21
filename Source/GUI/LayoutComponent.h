/*
 ==============================================================================
 
 LayoutComponent.h
 Created: 13 Sep 2017 3:29:40pm
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SectionTitleComponent.h"
#include "CheckBoxLookAndFeel.h"

//==============================================================================
/*
 */
class LayoutComponent    : public Component
{
public:
	LayoutComponent();
	~LayoutComponent();
	
	void paint (Graphics&) override;
	void resized() override;
	
	ToggleButton    offsetButton;
	
private:
	SectionTitleComponent	sectionTitle;
	
	CheckBoxLookAndFeel	checkBoxLookAndFeel;
	
	Label			offsetLabel;
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LayoutComponent)
};
