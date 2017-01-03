/*
 * gray_filter.h
 *
 *  Created on: 2016年12月6日
 *      Author: dengdong
 */

#ifndef GRAY_FILTER_H_
#define GRAY_FILTER_H_

#include "filter.h"

class GrayFilter : public Filter {
public:
	GrayFilter(){};
	virtual Mat filter(Mat& image);
	virtual ~GrayFilter(){};
};



#endif /* GRAY_FILTER_H_ */
