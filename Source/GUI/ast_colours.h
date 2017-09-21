/*
  ==============================================================================

    ast_colours.h
    Created: 12 Sep 2017 9:06:28pm
    Author:  Antonio Ortega Brook

  ==============================================================================
*/

#pragma once

#ifndef ast_colours_h
#define ast_colours_h

/*
//-------------------------------------------
//        hex colours
//-------------------------------------------
uint32_t grey_background	= 0xff545454;	// 0xff605F5F
uint32_t grey_foreground	= 0xff6B6B6B;
uint32_t grey_detail		= 0xff4A4A4A;
 
uint32_t light_grey_detail	= 0xff9B9B9B;

uint32_t blue_detail		= 0xff4A90E2;

uint32_t solid_white		= 0xffffffff;
uint32_t transparent_white	= 0x55ffffff;



//-------------------------------------------
//        Juce colours
//-------------------------------------------
Colour colour_grey_background		= Colour(grey_background);
Colour colour_grey_foreground		= Colour(grey_foreground);
Colour colour_grey_detail		= Colour(grey_detail);

Colour colour_light_grey_detail		= Colour(light_grey_detail);

Colour colour_blue_detail		= Colour(blue_detail);

Colour colour_solid_white		= Colour(solid_white);
Colour colour_transparent_white		= Colour(transparent_white);
*/

#define GREY_BACKGROUND		Colour(0xff545454)
#define GREY_FOREGROUND		Colour(0xff6B6B6B)
#define GREY_DETAIL		Colour(0xff4A4A4A)

#define LIGHT_GREY_DETAIL       Colour(0xff9B9B9B)

#define BLUE_DETAIL		Colour(0xff4A90E2)

#define SOLID_WHITE		Colour(0xffffffff)
#define TRANSPARENT_WHITE       Colour(0x55ffffff)


#define WHITE_TEXT_1            Colour(0xffeeeeee)
#define WHITE_TEXT_2            Colour(0xffcccccc)

#endif /* ast_colours_h */
