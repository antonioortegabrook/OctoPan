/*
 ==============================================================================
 
 PanLayoutComponent.h
 Created: 13 Sep 2017 3:22:31pm
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 */
class PanLayoutComponent    : public Component
{
public:
	PanLayoutComponent();
	~PanLayoutComponent();
	
	void paint (Graphics&) override;
	void resized() override;
	
	void setOffset(float newOffset);
	
private:
	float spkMagic;
	float offset;
        
        float centreX;
        float centreY;
	
        Path    speaker;
	Path	speakerLayout;
	Label	speakerLabel[8];
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanLayoutComponent)
};
