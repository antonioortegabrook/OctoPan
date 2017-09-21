//
//  angular_panning.c
//  pan.angular
//
//  Created by Antonio Ortega Brook on 8/29/17.
//
//

#include <math.h>

#include "angular_panning.h"



/**
 Compute gain for a given speaker based on source azimuth and width
 */
double speaker_gain(double speaker_angle, double source_azimuth, double source_width, long nspeakers)
{
	double gain;
	
	gain = cos((M_PI * speaker_angle) / source_width - source_azimuth * (nspeakers / 2) * ((2 * M_PI / nspeakers) / source_width));
	
	return gain;
}

/**
 Compute gain for a given speaker based on source azimuth and width
 
 angles in pi radians
 xparam recommended range: 0.5 - 3
 */
double quadratic_gain(double speaker_angle, double source_azimuth, double source_width, double xparam)
{
	double gain = 0;
	
	if (speaker_angle < source_azimuth - M_PI)
		gain = 1 - pow(pow((speaker_angle - source_azimuth + 2 * M_PI) / (source_width / 2), 2), xparam);
	
	else if (speaker_angle > source_azimuth + M_PI)
		gain = 1 - pow(pow((speaker_angle - source_azimuth - 2 * M_PI) / (source_width / 2), 2), xparam);
	
	else if (speaker_angle >= source_azimuth - M_PI && speaker_angle <= source_azimuth + M_PI)
		gain = 1 - pow(pow((speaker_angle - source_azimuth) / (source_width / 2), 2), xparam);
	
	if (gain < 0)
		gain = 0;
	
	return gain;
}

/**
 Normalize gains
 Returns in place
 */
void normalize(double *gains_array, long array_length)
{
	double square_sum = 0;
	
	for (long i = 0; i < array_length; i++)
		square_sum += pow(gains_array[i], 2);
	
	
	/** Sum of squares equal to zero means all gains in the array are zero,
	 so we do nothing.
	 */
	if (!square_sum)
		return;
	
	
	for (long i = 0; i < array_length; i++)
		gains_array[i] *= 1 / sqrt(square_sum);
	
	
	return;
}


/**
 Fill an array with speakers' angles; angles between adjacent speakers are equal
 */
void fill_spk_pos_array(double *array, long nspeakers, double offset)
{
	for (long i = 0; i < nspeakers; i ++)
		array[i] = (i - 1 + fmod(offset, 1)) * (2 * M_PI / nspeakers);
}


/**	- Set data into structs -	**/

/**
 Fill a t_spk_layout struct
 */
void fill_spk_layout(t_layout *layout, long nspeakers, double offset)
{
	layout->nspeakers	= nspeakers;
	layout->offset		= offset;
	
	fill_spk_pos_array(layout->speaker_pos, nspeakers, offset);
	
	layout->spk_diff = maximum_difference(layout->speaker_pos, nspeakers);
}


/**
 Initialize a t_source struct
 */
void init_source(t_source *source, double azimuth_degrees, double spread, double density, double minimum_width)
{
	source->azimuth = deg_to_rad(azimuth_degrees);
	
	source->spread = spread;
	source->density = density;
	
	source->width = spread_to_width(spread, minimum_width);
	source->xparam = density_to_xparam(density);
}


/**
 Set spread and compute width
 */
void set_spread(t_source *source, double new_spread, double minimum_width)
{
        source->spread = new_spread;
        source->width = spread_to_width(new_spread, minimum_width);
}

/**
 Set density and compute xparam
 */
void set_density(t_source *source, double new_density)
{
        source->density = new_density;
        source->xparam = density_to_xparam(new_density);
}





/**
 Fill an array with speakers' angles according to several standard layouts
 */
void fill_spk_pos_layout(double *array, long nspeakers, double offset, long layout)
{
	switch (layout) {
			
		case LAYOUT_EQUAL:
			for (long i = 0; i < nspeakers; i ++)
				array[i] = (i - 1 + fmod(offset, 1)) * (2 * M_PI / nspeakers);
			break;
			
		case LAYOUT_STEREO:
			array[0] = deg_to_rad(-30);
			array[1] = deg_to_rad(30);
			break;
			
		case LAYOUT_LCR:
			array[0] = deg_to_rad(-30);
			array[1] = deg_to_rad(0);
			array[2] = deg_to_rad(30);
			break;
			
		case LAYOUT_FIVE_ONE:
			array[0] = deg_to_rad(-30);
			array[1] = deg_to_rad(0);
			array[2] = deg_to_rad(30);
			array[3] = deg_to_rad(110);
			array[4] = deg_to_rad(-110);
			break;
			
		case LAYOUT_SEVEN_ONE:
			array[0] = deg_to_rad(-30);
			array[1] = deg_to_rad(0);
			array[2] = deg_to_rad(30);
			array[3] = deg_to_rad(90);
			array[4] = deg_to_rad(143.5);
			array[5] = deg_to_rad(-143.5);
			array[6] = deg_to_rad(-90);
			break;
			
		case LAYOUT_NINE_ONE:
			array[0] = deg_to_rad(-30);
			array[1] = deg_to_rad(0);
			array[2] = deg_to_rad(30);
			array[3] = deg_to_rad(70);
			array[4] = deg_to_rad(110);
			array[5] = deg_to_rad(150);
			array[6] = deg_to_rad(-150);
			array[7] = deg_to_rad(-110);
			array[8] = deg_to_rad(-70);
			break;
			
		default:
			break;
	}
}








/**	- Angle-related utility functions -	**/

// Calculates maximum angular difference between adjacent speakers
double maximum_difference(double *arr, long len)
{
	double max_diff = 0;
	double tmp_diff;
	double arr_i;
	for (long i = 1; i < len; i++) {
		arr_i = arr[i];
		tmp_diff = diff_angle(arr[i - 1], arr[i]);
		
		max_diff = tmp_diff > max_diff ? tmp_diff : max_diff;
	}
	
	return max_diff;
}

/** Takes an angle in the range +/- inf degrees and converts it to radians
 in the range 0 - 2PI
 */
double deg_to_rad(double degrees)
{
	double wrapped_deg;
	double radians;
	
	wrapped_deg = fmod(degrees, 360);
	
	if(wrapped_deg < 0)
		wrapped_deg += 360;
	
	radians = wrapped_deg * M_PI / 180;
	
	return radians;
}

/** Takes an angle in the range +/- inf radians and wraps it to 0 - 2PI
 */
double wrap_angle(double radians)
{
	double wrapped_rad;
	
	wrapped_rad = fmod(radians, 2 * M_PI);
	
	if (wrapped_rad < 0)
		wrapped_rad += 2 * M_PI;
	
	return wrapped_rad;
}

/**
 Find the difference between two angles in Pi radians
 */
double diff_angle(double angle_a, double angle_b)
{
	double diff_a, diff_b, min_diff;
	
	diff_a = fabs(angle_b - angle_a);
	diff_b = fabs(2 * M_PI - diff_a);
	
	min_diff = diff_a < diff_b ? diff_a : diff_b;
	
	return min_diff;
}


/**	- Other utility functions -	**/

/**
 Maps values in a given range to another
 */
double map_r(double value, double x_min, double x_max, double y_min, double y_max)
{
        double slope, output;
        
        slope = (y_max - y_min) / (x_max - x_min);
        output = y_min + slope * (value - x_min);
        
        return output;
}

/**
 Clips values within in a given range
 */
double clip_r(double value, double min, double max)
{
        double clipped_value;
        
        clipped_value = value < min ? min : value;
        clipped_value = value > max ? max : clipped_value;
        
        return clipped_value;
}


/**	- Convert user-level parameters to low-level parameters -	**/

double spread_to_width(double spread, double minimum_width)
{
	double e;
	double width;
	
	// Clip values between 0 and 100
	spread = spread < 0	? 0	: spread;
	spread = spread > 100	? 100	: spread;
	
	
	e = pow(fabs(spread) / 100, 2 * (1 + fabs(spread) / 200)) * (4 * M_PI - minimum_width);
	
	width = e + minimum_width;
	
	return width;
}

double density_to_xparam(double density)
{
	double xparam;
	
	// Clip values between -10 and 10
	density = density < -10	? -10	: density;
	density = density >  10	?  10	: density;
	
	
	xparam = 0.1 + pow((density + 10) / 10.3, 3.1);
	
	return xparam;
}
