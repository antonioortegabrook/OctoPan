/*
 ==============================================================================
 
 SectionTitleComponent.h
 Created: 15 Sep 2017 1:26:28am
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 */
class SectionTitleComponent    : public Component
{
public:
	SectionTitleComponent();
	~SectionTitleComponent();
	
	void paint (Graphics&) override;
	void resized() override;
	
	void setTitle(String);
	
private:
	Font    titleFont;
//	String  title;
	AttributedString title;
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SectionTitleComponent)
};
