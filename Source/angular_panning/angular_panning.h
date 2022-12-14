//
//  angular_panning.h
//  pan.angular
//
//  Created by Antonio Ortega Brook on 8/29/17.
//
//

#ifndef angular_panning_h
#define angular_panning_h

#include <math.h>

/** Useful macros to deal with angles, in addition to the POSIX ones defined in math.h.
	Like the POSIX macros, they're all double-precission literals. Maybe we should
	define them as long-doubles too?
 */
#define M_180_PI        57.29577951308232286464772187173366546630859375			/* 180 / pi	*/
#define M_PI_180        0.0174532925199432954743716805978692718781530857086181640625	/* pi / 180	*/
#define M_TWO_PI	6.28318530717958623199592693708837032318115234375		/* 2 * pi	*/

/** Some POSIX macros not defined in Windows' math.h
 */
#ifndef M_PI

#define M_PI        3.14159265358979323846264338327950288   /* pi             */
#define M_PI_2      1.57079632679489661923132169163975144   /* pi/2           */
#define M_PI_4      0.785398163397448309615660845819875721  /* pi/4           */
#define M_1_PI      0.318309886183790671537767526745028724  /* 1/pi           */
#define M_2_PI      0.636619772367581343075535053490057448  /* 2/pi           */

#endif /* M_PI */



/** Maximum number of speakers
 */
#define MAX_SPEAKERS 8



/**	- Data types -		**/

typedef struct _source
{
	double azimuth;
	double width;
	double xparam;
	double spread;
	double shape;
} t_source;

typedef struct _layout
{
	
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
 */
double quadratic_gain(double speaker_angle, double source_azimuth, double source_width, double xparam);

/**
 Compute gains for a given set of speakers based on source azimuth and width
 (this is a more optimized version of the previous function)
 
 angles in pi radians
 xparam recommended range: 0.5 - 3
 */
void quadratic_gain_array(double *gains_array, double *speaker_positions_array, long nspeakers, double source_azimuth, double source_width, double xparam);


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

double shape_to_xparam(double shape);



/**	- Set data into structs -	**/

/**
 Fill a t_spk_layout struct
 */
void fill_spk_layout(t_layout *layout, long nspeakers, double offset);

/**
 Initialize a t_source struct
 */
void init_source(t_source *source, double azimuth_degrees, double spread, double shape, double minimum_width);

/**
 Set spread and compute width
 */
void set_spread(t_source *source, double new_spread, double minimum_width);

/**
 Set shape and compute xparam
 */
void set_shape(t_source *source, double new_shape);

/**
 Compute gains from a t_source and a t_layout (old version)
 */
void compute_gains_old(double *gains, t_source *source, t_layout *layout);

/**
 Compute gains from a t_source and a t_layout
 */
void compute_gains(double *gains, t_source *source, t_layout *layout);




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
