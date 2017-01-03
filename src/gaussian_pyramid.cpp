/*
 * gaussian_pyramid.cpp
 *
 *  Created on: 2016年12月7日
 *      Author: dengdong
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

#include "filter.h"
#include "gaussian_filter.h"

using namespace std;
using namespace cv;

int main(int argc, char **argv) {

	xfeatures2d::SiftFeatureDetector detector;
}
