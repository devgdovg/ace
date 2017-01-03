/*
 * gaussian_filter.cpp
 *
 *  Created on: 2016年12月6日
 *      Author: dengdong
 */
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

#include "filter.h"
#include "gaussian_filter.h"

using namespace cv;
using namespace std;

Mat GaussianFilter::filter(Mat & bgrImage) {
	Mat dst;

	GaussianBlur(bgrImage, dst,  Size(41, 41), 8.0, 8.0, BORDER_DEFAULT);

	return dst;
}
