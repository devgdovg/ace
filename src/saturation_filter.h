
#ifndef SATURATION_FILTER_H_
#define SATURATION_FILTER_H_

#include "filter.h"

class SaturationFilter : public Filter {
public:
	SaturationFilter(){};
	virtual Mat filter(Mat& bgrImage);
	virtual ~SaturationFilter(){};
};

#endif
