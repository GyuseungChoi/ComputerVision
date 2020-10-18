#include "cv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {

	Mat frame, canny, canny_left, canny_right;
	VideoCapture road;
	Rect left_roi(200, 400, 400, 200);
	Rect right_roi(600, 400, 400, 200);

	float rho, theta, a, b, x0, y0;
	
	float rho_avg_left, theta_avg_left, rho_avg_right, theta_avg_right;
	float rho_sum_left, theta_sum_left, rho_sum_right, theta_sum_right;

	rho_sum_left = 0;
	theta_sum_left = 0;
	rho_sum_right = 0;
	theta_sum_right = 0;

	float count_left = 0;
	float count_right = 0;

	Point p1, p2;
	vector<Vec2f> lines;
	
	double fps, time_in_msec;
	time_in_msec = 0;

	if (road.open("Road.mp4") == 0) {
		cout << "no such file!" << endl;
		waitKey(0);
	}



	while (time_in_msec < 20000) {
		road >> frame;
		time_in_msec = road.get(CAP_PROP_POS_MSEC);

		cvtColor(frame, canny, CV_BGR2GRAY);
		blur(canny, canny, Size(5, 5));
		Canny(canny, canny, 10, 60, 3);
		canny_left = canny(left_roi);
		canny_right = canny(right_roi);

		HoughLines(canny_left, lines, 1, CV_PI / 180, 135);

		for (int i = 0; i < lines.size(); i++) {
			rho = lines[i][0];
			theta = lines[i][1];

			if (theta >= (CV_PI / 6) && theta <= (CV_PI / 3)) {
				rho_sum_left = rho_sum_left + rho;
				theta_sum_left = theta_sum_left + theta;
				count_left++;
			}
		}
		theta_avg_left = theta_sum_left / count_left;
		rho_avg_left = rho_sum_left / count_left;

		a = cos(theta_avg_left);
		b = sin(theta_avg_left);
		x0 = a * rho_avg_left + 200; // result
		y0 = b * rho_avg_left + 400;
		p1 = Point(cvRound(x0 + 2000 * (-b)), cvRound(y0 + 2000 * a));
		p2 = Point(cvRound(x0 - 2000 * (-b)), cvRound(y0 - 2000 * a));
		line(frame, p1, p2, Scalar(0, 0, 255), 3, 8);

		HoughLines(canny_right, lines, 1, CV_PI / 180, 120);

		for (int i = 0; i < lines.size(); i++) {
			rho = lines[i][0];
			theta = lines[i][1];

			if (theta >= (CV_PI/3*2) && theta <= (CV_PI/6*5)) {
				rho_sum_right = rho_sum_right + rho;
				theta_sum_right = theta_sum_right + theta;
				count_right++;
			}
		}
		theta_avg_right = theta_sum_right / count_right;
		rho_avg_right = rho_sum_right / count_right;

		a = cos(theta_avg_right);
		b = sin(theta_avg_right);
		x0 = a * rho_avg_right + 600; // result
		y0 = b * rho_avg_right + 400;
		p1 = Point(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * a));
		p2 = Point(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * a));
		line(frame, p1, p2, Scalar(0, 0, 255), 3, 8);

		fps = road.get(CAP_PROP_FPS);
		imshow("Frame", frame);
	
		waitKey(1000 / fps);
	}
	return 0;
}
