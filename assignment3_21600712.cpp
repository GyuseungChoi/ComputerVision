#include "cv.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

int main() {

	//Average filtering
	Mat lena, lena_filtered;
	lena = imread("Lena.png");
	imshow("lena", lena);
	Rect rect1(0, 0, lena.rows/2, lena.cols);
	lena_filtered = lena(rect1);
	blur(lena_filtered, lena_filtered, Size(7, 7));
	lena_filtered = lena.clone();
	imshow("lena_filtered", lena_filtered);

	//Sharpening
	Mat moon, moon_lap, moon_filtered, moon_left1, moon_left2;
	moon = imread("moon.jpg");

	Laplacian(moon, moon_lap, CV_16S);
	convertScaleAbs(moon_lap, moon_lap);
	moon_lap.convertTo(moon_lap, CV_8U);
	add(moon, moon_lap, moon_filtered);
	imshow("moon", moon);

	Rect rect2(0, 0, moon.rows / 2, moon.cols);
	moon_left1 = moon_filtered(rect2);
	moon_left2 = moon(rect2);
	moon_left2.copyTo(moon_left1);

	imshow("moon_filtered", moon_filtered);
	
	//median filtereing
	Mat saltnpepper, saltnpepper_filtered;
	saltnpepper = imread("saltnpepper.png");
	imshow("saltnpepper", saltnpepper);
	medianBlur(saltnpepper, saltnpepper_filtered, 9);
	imshow("saltnpepper_filtered", saltnpepper_filtered);

	waitKey(0);
	return 0;
}