#include "cv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(){

	Mat frame;
	VideoCapture cap;

	double time_in_msec;
	double fps;
	int total_frames;
	int frameNum;

	if (cap.open("background.mp4") == 0) {
		cout << "no such file!" << endl;
		waitKey(0);
	}

	while (1) {
		cap >> frame;
		time_in_msec = cap.get(CAP_PROP_POS_MSEC);
		frameNum = cap.get(CAP_PROP_POS_FRAMES);
		total_frames = cap.get(CAP_PROP_FRAME_COUNT);
		fps = cap.get(CAP_PROP_FPS);
		if (time_in_msec == 3000.0) {
			cout << "end of video" << endl;
			break;
		}
		imshow("video", frame);
		waitKey(1000/fps);
		cout << "frame:" << frameNum << " / " << total_frames << endl;
	}
}