/*
 ==============================================================================
 
 PanDialComponent.h
 Created: 13 Sep 2017 2:48:04pm
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PanDialLookAndFeel.h"

//==============================================================================
/*
 */
class PanDialComponent    : public Component
{
public:
	PanDialComponent();
	~PanDialComponent();
	
	Slider dial;
	
	void paint (Graphics&) override;
	void resized() override;
	
	void setAzimuth(float angleInDegrees);
        void setWidth(float angleInRadians);
        void setXparam(float angleInRadians);
	
private:
	
	panDialLookAndFeel panDialLookAndFeel;
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanDialComponent)
};
