#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

#include "filter.h"
#include "saturation_filter.h"

using namespace cv;
using namespace std;

//Filter* getFilter() {
//	return new SaturationFilter;
//}

Mat SaturationFilter::filter(Mat& bgrImage) {
	Mat retImage;
	cvtColor(bgrImage, retImage, CV_BGR2HSV);

	Mat hsv[3];
	split(retImage, hsv);

	for (int i = 0; i < hsv[1].rows; i++) {
		for (int j = 0; j < hsv[1].cols; j++) {
			uchar s = hsv[1].at< Vec<uchar, 1> >(i, j)[0];
			s = 1.8 * s;
			hsv[1].at< Vec<uchar, 1> >(i, j) = Vec<uchar, 1>(s);
		}
	}

	merge(hsv, 3, retImage);

	cvtColor(retImage, retImage, CV_HSV2BGR);
	return retImage;

}
