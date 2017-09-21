//
//  angular_panning.h
//  pan.angular
//
//  Created by Antonio Ortega Brook on 8/29/17.
//
//

#ifndef angular_panning_h
#define angular_panning_h


#define MAX_SPEAKERS 8



/**	- Data types -		**/

typedef struct _source
{
	double azimuth;
	double width;
	double xparam;
	double spread;
	double density;
} t_source;

typedef struct _layout {
	
	long		nspeakers;			// # of speakers
	double		offset;
	long		layout;				// speaker layout
	double		speaker_pos[MAX_SPEAKERS];	// speakers positions
	double		spk_diff;			// maximum angle between adjacent speakers
} t_layout;

/**
 Speaker layouts
 */
enum layouts {
	
	LAYOUT_EQUAL,
	LAYOUT_STEREO,
	LAYOUT_LCR,
	LAYOUT_FIVE_ONE,
	LAYOUT_SEVEN_ONE,
	LAYOUT_NINE_ONE,
	LAYOUT_TEN_TWO
};



/**	- Gain-related functions -		**/

/**
 Compute gain for a given speaker based on source azimuth and width
 */
double speaker_gain(double speaker_angle, double source_azimuth, double source_width, long nspeakers);

/**
 Compute gain for a given speaker based on source azimuth and width
 angles are in Pi radians
 xparam recommended range: 0.5 - 3
 */double quadratic_gain(double speaker_angle, double source_azimuth, double source_width, double xparam);


/**
 Normalize gains
 Returns in place
 */
void normalize(double *gains_array, long array_length);




/**	- Speaker layout-related functions -	**/

/**
 Fill an array with speakers' angles; angles between adjacent speakers are equal
 */
void fill_spk_pos_array(double *array, long nspeakers, double offset);

/**
 Fill an array with speakers' angles according to several standard layouts
 */
void fill_spk_pos_layout(double *array, long nspeakers, double offset, long layout);

/**
 Find maximum angular difference between adjacent speakers
 */
double maximum_difference(double *arr, long len);



/**	- Convert user-level parameters to low-level parameters -	**/

double spread_to_width(double spread, double minimum_width);

double density_to_xparam(double density);



/**	- Set data into structs -	**/

/**
 Fill a t_spk_layout struct
 */
void fill_spk_layout(t_layout *layout, long nspeakers, double offset);

/**
 Initialize a t_source struct
 */
void init_source(t_source *source, double azimuth_degrees, double spread, double density, double minimum_width);

/**
 Set spread and compute width
 */
void set_spread(t_source *source, double new_spread, double minimum_width);

/**
 Set density and compute xparam
 */
void set_density(t_source *source, double new_density);




/**	- Angle-related utility functions -	**/

/**
 Takes an angle in the range +/- inf degrees and converts it to radians
 in the range 0 - 2PI
 */
double deg_to_rad(double degrees);

/**
 Takes an angle in the range +/- inf radians and wraps it to 0 - 2PI
 */
double wrap_angle(double radians);

/**
 Find the difference between two angles in Pi radians
 */
double diff_angle(double angle_a, double angle_b);



/**	- Other utility functions -	**/

/**
 Maps values in a given range to another
 */
double map_r(double value, double x_min, double x_max, double y_min, double y_max);

/**
 Clips values within in a given range
 */
double clip_r(double value, double min, double max);


#endif /* angular_panning_h */
