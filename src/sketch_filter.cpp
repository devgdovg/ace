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

class SketchFilter : public Filter {
public:
	SketchFilter(){};
	virtual Mat filter(Mat& image);
	virtual ~SketchFilter(){};
private:
	double gray(Mat& image, int row, int col);
	double hue(Mat& image, int row, int col);
	Vec<uchar, 1> calc(Mat& image, int row, int col);
};

//Filter* getFilter() {
//	return new SketchFilter;
//}

Mat SketchFilter::filter(Mat& image) {
    Mat filtered = Mat(image.rows, image.cols, CV_8U);
    for (int i = 0; i < image.rows; i++) {
    	for (int j = 0; j < image.cols; j++) {
    		filtered.at< Vec<uchar, 1> >(i, j) = calc(image, i, j);
    	}
	}
    normalize(filtered, filtered, 0, 255, CV_MINMAX);
    return filtered;
};

double SketchFilter::gray(Mat& image, int row, int col) {
	Vec3b color = image.at<Vec3b>(row, col);
    return (color[0] + color[1] + color[2]) / 3.0;
};

double SketchFilter::hue(Mat& image, int row, int col) {
	Vec3b color = image.at<Vec3b>(row, col);
	double rr = color[0] / 255.0;
	double gg = color[1] / 255.0;
	double bb = color[2] / 255.0;
	double maxV = max(rr, max(gg, bb));
	double minV = min(rr, min(gg, bb));
	double delta = maxV - minV;

//	double l = (maxV + minV) / 2.0;
//	double s = delta == 0.0 ? 0.0 : delta / (1.0 - abs(2.0 * l - 1.0));
	double h;
	if (delta == 0.0) {
		h = 0.0;
	} else if (maxV == rr) {
		h = (gg - bb) / delta;
	} else if (maxV == gg) {
		h = (bb - rr) / delta + 2.0;
	} else {
		h = (rr - gg) / delta + 4.0;
	}

	h = h >= 0.0 ? h / 6.0 : h / 6.0 + 1.0;
	return h * 256.0;
};

Vec<uchar, 1> SketchFilter::calc(Mat& image, int row, int col) {
	double dx, dy;
	if (row == 0) {
		dx = 0.0;
	} else {
		double dxgray = abs(gray(image, row, col) - gray(image, row - 1, col));
		double dxhue = abs(hue(image, row, col) - hue(image, row - 1, col));
		dxhue = min(dxhue, 256.0 - dxhue); // because hue is periodical
//		dx = (dxgray + dxhue) / 2.0;
//		dx = dxgray;
//		dx = max(dxgray, dxhue);
		dx = (dxgray * 8.0 + dxhue) / 9.0;
	}
	if (col == 0) {
		dy = 0.0;
	} else {
		double dygray = abs(gray(image, row, col) - gray(image, row, col - 1));
		double dyhue = abs(hue(image, row, col) - hue(image, row, col - 1));
		dyhue = min(dyhue, 256.0 - dyhue);
//		dy = (dygray + dyhue) / 2.0;
//		dy = dygray;
//		dy = max(dygray, dyhue);
		dy = (dygray * 8.0 + dyhue) / 9.0;
	}
//	cout << dx << "," << dy << endl;
	double gradient = sqrt((dx * dx + dy * dy) / 2.0); // definition of gradient
	gradient = (256.0 - gray(image, row, col) + 2.3 * gradient) / 3.3;  // consider the gray scale of the original image
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
