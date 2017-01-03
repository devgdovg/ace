/*
 * gaussian_filter.h
 *
 *  Created on: 2016年12月6日
 *      Author: dengdong
 */

#ifndef GAUSSIAN_FILTER_H_
#define GAUSSIAN_FILTER_H_

#include "filter.h"

class GaussianFilter : public Filter {
public:
	GaussianFilter(){};
	virtual Mat filter(Mat& bgrImage);
	virtual ~GaussianFilter(){};
};

#endif /* GAUSSIAN_FILTER_H_ */
