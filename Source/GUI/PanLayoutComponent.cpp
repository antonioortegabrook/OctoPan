/*
 ==============================================================================
 
 PanLayoutComponent.cpp
 Created: 13 Sep 2017 3:22:31pm
 Author:  Antonio Ortega Brook
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "PanLayoutComponent.h"
#include "ast_colours.h"


//==============================================================================
PanLayoutComponent::PanLayoutComponent()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.
	
	spkMagic	= 3;
	offset		= 0;
	
	for (int i = 0; i < 8; i++) {
		speakerLabel[i].setFont(Font::Font("Arial Narrow", "Regular", 10));
		speakerLabel[i].setBorderSize(BorderSize<int> (0));
		speakerLabel[i].setJustificationType(Justification::centred);
		speakerLabel[i].Component::setColour(Label::textColourId, WHITE_TEXT_2);
		speakerLabel[i].Component::setColour(Label::outlineColourId, Colours::transparentWhite);
		addAndMakeVisible(&speakerLabel[i]);
	}
}

PanLayoutComponent::~PanLayoutComponent()
{
}

void PanLayoutComponent::paint (Graphics& g)
{
	/* This demo code just fills the component's background and
	 draws some placeholder text to get you started.
	 
	 You should replace everything in this method with your own
	 drawing code..
	 */
	float speakerReduce     = 20;
	float labelReduce       = 10;
	
	Rectangle<int> speakerArea = getLocalBounds().reduced(speakerReduce);
	Rectangle<int> labelArea = getLocalBounds().reduced(labelReduce);
	
	Point<int> centre = getLocalBounds().getCentre();
	
	centreX = speakerArea.getCentreX();
	centreY = speakerArea.getCentreY();


	speaker.clear();
	speakerLayout.clear();
	
	float rectX1_X4, rectY1_Y2, rectX2_X3, rectY3_Y4;
	float trapezoidX1, trapezoidY1_Y2, trapezoidX2, trapezoidX3, trapezoidY3_Y4, trapezoidX4;
	
	rectX1_X4 = centreX	- spkMagic;
	rectY1_Y2 = speakerArea.getY();
	rectX2_X3 = centreX	+ spkMagic;
	rectY3_Y4 = speakerArea.getY()	+ spkMagic;
	
	trapezoidX1 = centreX	- spkMagic;
	trapezoidY1_Y2 = speakerArea.getY()		+ spkMagic * 1.5;
	trapezoidX2 = centreX	+ spkMagic;
	trapezoidX3 = centreX	+ spkMagic * 2;
	trapezoidY3_Y4 = speakerArea.getY()		+ spkMagic * 2.5;
	trapezoidX4 = centreX	- spkMagic * 2;
	
	
	// rectangle
	speaker.addQuadrilateral(rectX1_X4,
				 rectY1_Y2,
				 rectX2_X3,
				 rectY1_Y2,
				 rectX2_X3,
				 rectY3_Y4,
				 rectX1_X4,
				 rectY3_Y4);
	// trapezoid
	speaker.addQuadrilateral(trapezoidX1,
				 trapezoidY1_Y2,
				 trapezoidX2,
				 trapezoidY1_Y2,
				 trapezoidX3,
				 trapezoidY3_Y4,
				 trapezoidX4,
				 trapezoidY3_Y4);
	
	// arrange in a circle
	const float pi_4 = float_Pi * 0.25f;
	
	speaker.applyTransform(AffineTransform::rotation(pi_4 * offset, centreX, centreY));
	
	for (int i = 0; i < 8; i++) {
		float angle = i * pi_4;
		
		speaker.applyTransform(AffineTransform::rotation(pi_4, centreX, centreY));
		speakerLayout.addPath(speaker);
		
		speakerLabel[i].setBounds(speaker.getBounds().toNearestInt());
		speakerLabel[i].setCentrePosition(centre.getPointOnCircumference(63, angle + pi_4 * offset).toInt());
		speakerLabel[i].setText(String((i + 1) % 8 + 1), NotificationType::dontSendNotification);
	}
	

	
	g.setColour(GREY_DETAIL);
	g.fillPath(speakerLayout);
	
}

void PanLayoutComponent::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
}

void PanLayoutComponent::setOffset(float newOffset)
{
	offset = newOffset;
	PanLayoutComponent::repaint();
}
