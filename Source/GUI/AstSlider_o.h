/*
  ==============================================================================

    AstSlider_o.h
    Created: 15 Sep 2017 8:58:13pm
    Author:  Antonio Ortega Brook

  ==============================================================================
*/

#pragma once


class AstSlider_o		: public Slider
{
public:
        String getTextFromValue(double v) override
        {
                return String (v, 2) + getTextValueSuffix();
        }
        
};
