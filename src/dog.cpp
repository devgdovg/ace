/*
 * batch.cpp
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
#include "gaussian_filter.h"

using namespace std;
using namespace cv;

#define LAYER 5

bool isPeak(int layer, int row, int col, Mat* dog) {
	int flag = 0;
	uchar v = dog[layer].at< Vec<uchar, 1> >(row, col)[0];
	for (int l = layer - 1; l <= layer + 1; l++) {
		for (int i = row - 1; i <= row + 1; i++) {
			for (int j = col - 1; j <= col + 1; j++) {
				if (i < 0 || i >= dog[l].rows || j < 0 || j >= dog[l].cols) {
					continue;
				}
				if (l == layer && i == row && j == col) {
					continue;
				}
				uchar u = dog[l].at< Vec<uchar, 1> >(i, j)[0];
				if (v > u) {
					if (flag < 0) {
						return false;
					} else {
						flag = 1;
					}
				} else if (v < u) {
					if (flag > 0) {
						return false;
					} else {
						flag = -1;
					}
				}
			}
		}
	}
	return (flag != 0);
};

int main1(int argc, char **argv) {
	for (int i = 1; i < argc; i++) {
		char* fileName = argv[i];
		Mat image = imread(fileName, IMREAD_COLOR);
		if (image.empty()) {
			cout << "image is empty: " << fileName << endl;
			continue;
		}

		Mat grayImage;
		cvtColor(image, grayImage, CV_BGR2GRAY);

		double sigma = 0.5;

		Mat blur[LAYER];
		Mat dog[LAYER - 1];

		for (int i = 0; i < LAYER; i++) {
			GaussianBlur(grayImage, blur[i], Size(17, 17), sigma, sigma,
					BORDER_DEFAULT);
//			stringstream name;
//			name << "gaussian" << (i + 1);
//			imshow(name.str().c_str(), blur[i]);
			if (i > 0) {
				stringstream dogName;
				dog[i] = blur[i] - blur[i - 1];
				normalize(dog[i], dog[i], 0, 255, CV_MINMAX);
//				dog[i] = Scalar::all(255) - dog[i];
				dogName << "dog" << (i + 1);
				imshow(dogName.str().c_str(), dog[i]);
			}
			sigma += 0.1;
		}

		Mat interest = Mat::zeros(grayImage.size(), CV_8U);

		for (int l = 1; l < LAYER - 1; l++) {
			for (int i = 0; i < dog[l].rows; i++) {
				for (int j = 0; j < dog[l].cols; j++) {
					if (isPeak(l, i, j, dog)) {
						uchar v = interest.at< Vec<uchar, 1> >(i, j)[0];
						uchar u = dog[l].at< Vec<uchar, 1> >(i, j)[0];
						if (u > v) {
							interest.at< Vec<uchar, 1> >(i, j) = Vec<uchar, 1>(u);
						}
					} else {
						interest.at< Vec<uchar, 1> >(i, j) = Vec<uchar, 1>((uchar)0);
					}
				}
			}
			Vec<uchar, 1> p = dog[l].at<Vec<uchar, 1> >();
		}

		normalize(interest, interest, 0, 255, CV_MINMAX);
		interest = Scalar::all(255) - interest;
		imshow("interest", interest);


//		stringstream ori, ftr;
//		ori << "original" << i;
//		ftr << "filtered" << i;
//
//		imshow(ori.str(), image);
//
//		imshow(ftr.str(), filtered);
//
//		stringstream output;
//		output << fileName << "_output.jpg";
//		vector<int> compression_params;
//		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
//		compression_params.push_back(100);
//		imwrite(output.str().c_str(), filtered, compression_params);

	}
	waitKey(0);
	return 0;
}
