#include "convolusion.h"

#define loop_optimization

void convolusion(int image[image_rows][image_cols],
		float kernel[kernel_rows][kernel_cols],
		int res[image_rows][image_cols])
{

	const int dx = kernel_rows / 2;
	const int dy = kernel_cols / 2;

#ifdef loop_optimization
IR: for (int i = 0; i<image_rows; i++) {

#pragma HLS PIPELINE II=1
		for (int j = 0; j<image_cols; j++) {
			float tmp = 0.0;
			for (int k = 0; k<kernel_rows; k++) {
				for (int l = 0; l<kernel_cols; l++) {
					int x = i - dx + k;
					int y = j - dy + l;
					if (x >= 0 && x < image_rows && y >= 0 && y < image_cols) {
						tmp += float(image[x][y]) * float(kernel[k][l]);
					}
				}
			}
			//temp is float, multiply with 1000 (to minimize loss from the subsequent int casting)
			//then cast to int (aka truncate), then transform to [0,127] range of ints
			res[i][j] = ((int) (tmp*1000))%128;
		}
	}
#else
	for (int i = 0; i<image_rows; i++) {
		for (int j = 0; j<image_cols; j++) {
			float tmp = 0.0;
			for (int k = 0; k<kernel_rows; k++) {
				for (int l = 0; l<kernel_cols; l++) {
					int x = i - dx + k;
					int y = j - dy + l;
					if (x >= 0 && x < image_rows && y >= 0 && y < image_cols) {
						tmp += float(image[x][y]) * float(kernel[k][l]);
					}
				}
			}
			//temp is float, multiply with 1000 (to minimize loss from the subsequent int casting)
			//then cast to int (aka truncate), then transform to [0,127] range of ints
			res[i][j] = ((int) (tmp*1000))%128;
		}
	}
#endif
}
