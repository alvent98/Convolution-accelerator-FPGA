#include <iostream>
#include "convolusion.h"

int main(int argc, char **argv)
{
	int image[128][128];
	float kernel[8][8];
	int res[128][128];
	//Create kernel
	std::cout << "kernel" << std::endl;
	for (int i = 0;i < kernel_rows; i++) {
		for (int j = 0;j < kernel_cols; j++) {
			//All values of kernel must be 1/(NxM)
			//where n and m are the image dimensions
			kernel[i][j] = float(1)/float(kernel_rows*kernel_cols);
			std::cout << kernel[i][j] << " ";
		}
		std::cout << std::endl;
	}

	//Create image
	std::cout << "image" << std::endl;
	for (int i = 0;i < image_rows; i++) {
		for (int j = 0;j < image_cols; j++) {
			//get some pseudo-random numbers
			image[i][j] = ((i+1)*(i+1)*(j+1)*(j+1)*(j+1))%128;
			std::cout << image[i][j] << " ";
		}
		std::cout << std::endl;
	}

	int hw_result[image_rows][image_cols];
	int sw_result[image_rows][image_cols];

	const int dx = kernel_rows / 2;
	const int dy = kernel_cols / 2;

	// Generate the expected result
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
			sw_result[i][j] = ((int) (tmp*1000))%128;
		}
	}

#ifdef HW_COSIM
	convolusion(image, kernel, hw_result);
#endif

	std::cout << "result:" << std::endl;
	// Print result matrix
	for (int i = 0; i < image_rows; i++) {
		for (int j = 0; j < image_cols; j++) {
#ifdef HW_COSIM
			std::cout << hw_result[i][j];
#else
			std::cout << sw_result[i][j];
#endif
			if (j == image_cols - 1)
				std::cout << std::endl;
			else
				std::cout << " ";
		}
	}
	std::cout << std::endl;

	return 0;
}

