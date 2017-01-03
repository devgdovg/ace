/*
 * gray_filter.cpp
 *
 *  Created on: 2016年11月27日
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
#include "gray_filter.h"

using namespace cv;
using namespace std;

//Filter* getFilter() {
//	return new GrayFilter;
//}

Mat GrayFilter::filter(Mat& image) {
	Mat grayImage;
	cvtColor(image, grayImage, CV_BGR2GRAY);
	return grayImage;
}


