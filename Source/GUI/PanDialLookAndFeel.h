/*
 ==============================================================================
 
 PanDialLookAndFeel.h
 Created: 14 Sep 2017 11:56:43pm
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#pragma once
#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ast_colours.h"



class panDialLookAndFeel : public LookAndFeel_V4
{
private:
	float spreadWidth		/*	= double_Pi * 0.25f	*/;
	float shapeWidth		/*	= double_Pi * 0.125f	*/;
	const float azimuthWidth	= double_Pi * 0.015625f;
public:
	panDialLookAndFeel()
	{
		setWidth(double_Pi * 0.25f);
		setshape(double_Pi * 0.125f);
	}
	
	void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
			       const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
		const float thickness		= 0.5;
		
		const float radius		= jmin(width * 0.5f, height * 0.5f) - 4.0f;
		
		const float centreX		= x + width * 0.5f;
		const float centreY		= y + height * 0.5f;
		
		const float rx			= centreX - radius;
		const float ry			= centreY - radius;
		const float rw			= radius * 2.0f;
		
		const float innerRx		= rx + radius * thickness * 0.5f;
		const float innerRy		= ry + radius * thickness * 0.5f;
		const float innerRw		= radius * (2.0f - thickness);
		
		const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
		
		
		// fill
		g.setColour(GREY_BACKGROUND);
		g.fillEllipse(rx, ry, rw, rw);
		
		// spread --------
		Path s;
		s.addPieSegment(rx, ry, rw, rw, 0.0f, spreadWidth, 0);
		s.applyTransform (AffineTransform::rotation(angle - spreadWidth * 0.5f, centreX, centreY));
		
                g.setColour(BLUE_DETAIL);
                g.fillPath(s);
//                g.setColour(SOLID_WHITE);
//                g.fillPath(s);
//                g.setColour(Colour(0xCf4A90E2));
//                g.fillPath(s);
		
		// shape --------
		Path d;
		d.addPieSegment(rx, ry, rw, rw, 0.0f, shapeWidth, 0);
		d.applyTransform (AffineTransform::rotation(angle - shapeWidth * 0.5f, centreX, centreY));
		
                g.setColour(TRANSPARENT_WHITE);
                g.fillPath(d);
//		g.setColour(Colour(0xff4A90E2));
//		g.fillPath(d);
		
		// azimuth --------
		Path a;
		a.addPieSegment(rx, ry, rw, rw, 0.0f, azimuthWidth, 0);
		a.applyTransform (AffineTransform::rotation(angle - azimuthWidth * 0.5f, centreX, centreY));
		
		g.setColour(SOLID_WHITE);
		g.fillPath(a);
		
		// outline --------
		g.setColour(GREY_DETAIL);
		g.drawEllipse(rx, ry, rw, rw, 1.0f);
		
		// inline ---------
		g.setColour(GREY_FOREGROUND);
		g.fillEllipse(innerRx, innerRy, innerRw, innerRw);
		
		// iner circle ----
		g.setColour(GREY_DETAIL);
		g.drawEllipse(innerRx, innerRy, innerRw, innerRw, 1.0f);
	}
	
	void setWidth(float angleInRadians)
	{
		spreadWidth = angleInRadians;
	}
	
	
	void setshape(float angleInRadians)
	{
		shapeWidth = angleInRadians;
	}
};

#endif  // MAINCOMPONENT_H_INCLUDED
