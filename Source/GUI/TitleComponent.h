/*
 ==============================================================================
 
 TitleComponent.h
 Created: 13 Sep 2017 3:45:54pm
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 */
class TitleComponent    : public Component
{
public:
	TitleComponent();
	~TitleComponent();
	
	void paint (Graphics&) override;
	void resized() override;
	
private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TitleComponent)
};
