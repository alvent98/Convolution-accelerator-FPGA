#ifndef __CONVOLUSION_H__
#define __CONVOLUSION_H__

#include <cmath>

// Uncomment this line to compare TB vs HW C-model and/or RTL
#define HW_COSIM

#define	image_rows 128
#define image_cols 128
#define kernel_rows 8
#define kernel_cols 8

// Prototype of top level function for C-synthesis
void convolusion(
		int image[image_rows][image_cols],
		float kernel[kernel_rows][kernel_cols],
		int res[image_rows][image_cols]);

#endif // __CONVOLUSION_H__ not defined