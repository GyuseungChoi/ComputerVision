#include "cv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {

	Mat frame, canny, canny_left, canny_right;
	VideoCapture road;
	Rect left_roi(200, 400, 400, 200);
	Rect right_roi(600, 400, 400, 200);
	double fps;

	if (road.open("Road.mp4") == 0) {
		cout << "no such file!" << endl;
		waitKey(0);
	}

	while (1) {
		road >> frame;
		cvtColor(frame, frame, CV_BGR2GRAY);
		blur(frame, frame, Size(5, 5));
		Canny(frame, canny, 10, 60, 3);
		canny_left = canny(left_roi);
		canny_right = canny(right_roi);

		namedWindow("Left canny");
		moveWindow("Left canny", 200, 0);
		namedWindow("Right canny");
		moveWindow("Right canny", 600, 0);

		fps = road.get(CAP_PROP_FPS);
		imshow("Left canny", canny_left);
		imshow("Right canny", canny_right);
		waitKey(1000 / fps);
	}
}