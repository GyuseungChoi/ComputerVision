#include "cv.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

int main() {

	Mat image; //basic
	Mat negative_img; //Negative 
	Mat f_img, log_img; //Log
	Mat gamma_img; // gamma
	
	image = imread("Lena.png", 0);

	//Negative transformation
	negative_img = image.clone();
	for (int j = 0; j < image.rows; j++) {
		for (int i = 0; i < image.cols; i++) {
			negative_img.at<uchar>(j, i) = 255 - negative_img.at<uchar>(j, i);
		}
	}

	//Log transformation 
	double c = 1.5f;
	image.convertTo(f_img, CV_32F); //covert to float type
	f_img = abs(f_img) + 1;
	log(f_img, f_img);
	f_img = f_img * c; // output = c * log(1 + input);

	normalize(f_img, f_img, 0, 255, NORM_MINMAX); //normalize image to (0~255)
	convertScaleAbs(f_img, log_img); //scaling by c, conversion to an unsigned 8-bit type

	//Gamma transformation
	MatIterator_<uchar> it, end;
	float gamma = 0.5f;
	unsigned char pix[256]; //pixel type

	for (int i = 0; i < 256; i++)
		pix[i] = (uchar)(pow((float)(i / 255.0), gamma) * 255.0f); //pre compute possible case

	gamma_img = image.clone();

	for (it = gamma_img.begin<uchar>(), end = gamma_img.end<uchar>(); it != end; it++)
		*it = pix[(*it)];

	imshow("gray image", image);
	imshow("negative image", negative_img);
	imshow("log image", log_img);
	imshow("gamma image", gamma_img);

	waitKey(0);
	return 0;
}