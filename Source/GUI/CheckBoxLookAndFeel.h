/*
  ==============================================================================

    CheckBoxLookAndFeel.h
    Created: 16 Sep 2017 3:12:10pm
    Author:  Antonio Ortega Brook

  ==============================================================================
*/

#pragma once



#include "../JuceLibraryCode/JuceHeader.h"
#include "ast_colours.h"
#include "dims.h"



class CheckBoxLookAndFeel : public LookAndFeel_V4
{
private:

public:
        CheckBoxLookAndFeel()
        {
        }
        
        void drawTickBox (Graphics &g, Component &c, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
	{
		Rectangle<float> buttonArea (x, y, w, h);
		
		if (ticked) {
			g.setColour(BLUE_DETAIL);
			g.fillRoundedRectangle(buttonArea,      2);
			
			buttonArea = buttonArea.reduced(2);
			
			g.setColour(SOLID_WHITE);

			g.drawLine(buttonArea.getX(),
				   buttonArea.getHeight() / 2 + buttonArea.getY(),
				   buttonArea.getWidth() / 2 + buttonArea.getX(),
				   buttonArea.getHeight() + buttonArea.getY(),		2);

			g.drawLine(buttonArea.getWidth() / 2 + buttonArea.getX(),
				   buttonArea.getHeight() + buttonArea.getY(),
				   buttonArea.getWidth() + buttonArea.getX(),
				   buttonArea.getY(),					2);
		}
		else {
			g.setColour(SOLID_WHITE);
			g.fillRoundedRectangle(buttonArea,      2);
			
			g.setColour(BLUE_DETAIL);
			g.drawRoundedRectangle(buttonArea,      2,   1);
		}
		
	}

};
