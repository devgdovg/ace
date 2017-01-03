/*
 * fft.cpp
 *
 *  Created on: 2016年11月27日
 *      Author: dengdong
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "filter.h"

class FftFilter : public Filter {
public:
	FftFilter(){};
	virtual Mat filter(Mat& image);
	virtual ~FftFilter(){};
private:
	static const int SQUARE_DFT_SIZE = 1024;
};

//Filter* getFilter() {
//	return new FftFilter;
//}

Mat FftFilter::filter(Mat& image) {

	Mat squared = Mat(SQUARE_DFT_SIZE, SQUARE_DFT_SIZE, CV_8U);

	resize(image, squared, squared.size(), 0.0, 0.0, INTER_LANCZOS4);

	Mat squaredGray;
	cvtColor(squared, squaredGray, CV_BGR2GRAY);

	std::cout << "here" << std::endl;

//	Mat padded;                            //expand input image to optimal size
//	int m = getOptimalDFTSize(squared.rows);
//	int n = getOptimalDFTSize(squared.cols); // on the border add zero values

//	std::cout << "optimal size: " << m << ", " << n << std::endl;
//
//	copyMakeBorder(image, padded, 0, m - image.rows, 0, n - image.cols, BORDER_CONSTANT,
//			Scalar::all(0));

	Mat planes[] = { Mat_<float>(squaredGray), Mat::zeros(squaredGray.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);  // Add to the expanded another plane with zeros

	dft(complexI, complexI); // this way the result may fit in the source matrix

	// compute the magnitude and switch to logarithmic scale
	split(complexI, planes);    // planes[0] = Re(DFT(image), planes[1] = Im(DFT(image))
	magnitude(planes[0], planes[1], planes[0]);         // planes[0] = magnitude

	// => log(1 + sqrt(Re(DFT(image))^2 + Im(DFT(image))^2))
	Mat magFft = planes[0];
//	magFft += Scalar::all(1);                    // switch to logarithmic scale
//	log(magFft, magFft);


	// crop the spectrum, if it has an odd number of rows or columns
	magFft = magFft(Rect(0, 0, magFft.cols & -2, magFft.rows & -2));

	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magFft.cols / 2;
	int cy = magFft.rows / 2;

	Mat q0(magFft, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(magFft, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(magFft, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(magFft, Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp;                      // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magFft, magFft, 0, 255, CV_MINMAX); // Transform the matrix with float values into a
											// viewable image form (float between values 0 and 1).

//	imshow("Input Image", image);    // Show the result
//	imshow("spectrum magnitude", magFft);
//	waitKey(0);

	return magFft;
};



