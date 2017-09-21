/*
  ==============================================================================

    AstColours.h
    Created: 13 Sep 2017 9:10:39pm
    Author:  Antonio Ortega Brook

  ==============================================================================
*/

#pragma once

//#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class AstColours
{
public:
	
	//-------------------------------------------
	//        hex colours
	//-------------------------------------------
	const uint32_t grey_background		= 0xff545454;	// 0xff605F5F
	const uint32_t grey_foreground		= 0xff6B6B6B;
	const uint32_t grey_detail		= 0xff4A4A4A;
	
	const uint32_t blue_detail		= 0xff4A90E2;
	
	const uint32_t solid_white		= 0xffffffff;
	const uint32_t transparent_white	= 0x55ffffff;
	
	
	
	//-------------------------------------------
	//        Juce colours
	//-------------------------------------------
	static JUCE_API const Colour colour_grey_background		= Colour(grey_background);
	const Colour colour_grey_foreground		= Colour(grey_foreground);
	const Colour colour_grey_detail			= Colour(grey_detail);
	
	const Colour colour_blue_detail			= Colour(blue_detail);
	
	const Colour colour_solid_white			= Colour(solid_white);
	const Colour colour_transparent_white		= Colour(transparent_white);
	
	
private:
	AstColours();
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AstColours)
};
