#include "cv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat drawHistogram(Mat src) {
	Mat hist, histImage;

	int i, hist_w, hist_h,  bin_w, histSize;
	float range[] = { 0, 256 };
	const float* histRange = { range };

	hist_w = 512;
	hist_h = 512;
	histSize = 16;
	bin_w = cvRound((double)hist_w / histSize);

	histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

	calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (i = 0; i < histSize; i++) {
		rectangle(histImage, Point(bin_w * i, hist_h), Point(bin_w * i + hist_w / histSize, hist_h - cvRound(hist.at<float>(i))), Scalar(0, 0, 0), -1);
	}
	return histImage;
}

void writeText(Mat src) {
	float hist_w, hist_h, bin_w;
	hist_w = src.rows;
	hist_h = src.cols;
	int histSize = 8;
	bin_w = (double)hist_w / histSize;

	float range[] = { 0, 256 };
	const float* histRange = { range };

	Mat hist;
	calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);
	
	for (int i = 0; i < histSize; i++) {
		float x = (cvRound(hist.at<float>(i)) / (hist_w * hist_h));
		putText(src, format("bin %d: %f", i+1, x), Point(10, 25 + i*25), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
	}
}

int main() {

	Mat moon_before, moon_after;
	Mat hist_before, hist_after;

	moon_before = imread("moon.png", 0);
	
	equalizeHist(moon_before, moon_after);


	hist_before = drawHistogram(moon_before);
	hist_after = drawHistogram(moon_after);

	writeText(moon_before);
	writeText(moon_after);

	imshow("before", moon_before);
	imshow("after", moon_after);
	imshow("h1", hist_before);
	imshow("h2", hist_after);

	waitKey(0);
	return 0;
}