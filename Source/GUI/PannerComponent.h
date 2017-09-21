/*
 ==============================================================================
 
 PannerComponent.h
 Created: 13 Sep 2017 2:59:41pm
 Author:  Antonio Ortega Brook
 
 
 PannerComponent: contiene los componentes PanDial y PanLayout
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "PanDialComponent.h"
#include "PanLayoutComponent.h"

//==============================================================================
/*
 */
class PannerComponent    : public Component
{
public:
	PannerComponent();
	~PannerComponent();
	
	PanDialComponent        dialComponent;
	PanLayoutComponent      panLayout;
	
	void paint (Graphics&) override;
	void resized() override;
	
	void	setAzimuth(float angleInDegrees);
	float	getAzimuth();
	
	void	setWidth(float angleInRadians);
	void	setXparam(float angleInRadians);        // revisar
	
private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PannerComponent)
};
