/*
 * filter.h
 *
 *  Created on: 2016年11月27日
 *      Author: dengdong
 */

#ifndef FILTER_H_
#define FILTER_H_

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Filter {
public:
	Filter(){};
	virtual Mat filter(Mat& image) = 0;
	virtual ~Filter(){};
};

Filter* getFilter();

#endif /* FILTER_H_ */
