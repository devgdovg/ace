//============================================================================
// Name        : ace.cpp
// Author      : ddwinterdd
// Version     :
// Copyright   : ddwinterdd
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

#include "filter.h"

using namespace cv;
using namespace std;

class GraySketchFilter : public Filter {
public:
	GraySketchFilter(){};
	virtual Mat filter(Mat& image);
	virtual ~GraySketchFilter(){};
private:
	Vec<uchar, 1> calc(Mat& image, int row, int col);
};

Filter* getFilter() {
	return new GraySketchFilter;
}

Mat GraySketchFilter::filter(Mat& image) {
    Mat filtered = Mat(image.rows, image.cols, CV_8U);
    for (int i = 0; i < image.rows; i++) {
    	for (int j = 0; j < image.cols; j++) {
    		filtered.at< Vec<uchar, 1> >(i, j) = calc(image, i, j);
    	}
	}
    normalize(filtered, filtered, 0, 255, CV_MINMAX);
    return filtered;
};


Vec<uchar, 1> GraySketchFilter::calc(Mat& image, int row, int col) {
	double dx, dy;
	if (row == 0) {
		dx = 0.0;
	} else {
		dx = abs(image.at< Vec<uchar, 1> >(row, col)[0] - image.at< Vec<uchar, 1> >(row - 1, col)[0]);
	}
	if (col == 0) {
		dy = 0.0;
	} else {
		dy = abs(image.at< Vec<uchar, 1> >(row, col)[0] - image.at< Vec<uchar, 1> >(row, col - 1)[0]);
	}
//	cout << dx << "," << dy << endl;
	double gradient = sqrt((dx * dx + dy * dy) / 2.0); // definition of gradient
	gradient = (256.0 - (double)(image.at< Vec<uchar, 1> >(row, col)[0]) + 3.0 * gradient) / 4.0;  // consider the gray scale of the original image
	gradient = 16.0 * sqrt(gradient); // enhance by doing sqrt
	if (gradient > 128.0) {
		gradient = sqrt(gradient - 128.0) * sqrt(128.0) + 128.0;
	} else {
		gradient = gradient * gradient / 128.0;
	}
//	return Vec<uchar, 1>((uchar)255 - (uchar)gradient); // reverse black & white
	gradient = 256.0 - gradient;
	return Vec<uchar, 1>((uchar)gradient); // reverse black & white
};
