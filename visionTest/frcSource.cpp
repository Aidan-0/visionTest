/*
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	int thresh = 0;
	VideoCapture cam;
	Mat frame, frameGray, frameInvert, frameBin;
	cam.open(0);

	for (;;) {

		cam >> frame;

		cvtColor(frame, frameGray, COLOR_BGR2GRAY);
		threshold(frameGray, frameBin, thresh, 255, THRESH_BINARY);
		bitwise_not(frameBin, frameInvert);

		namedWindow("SliderBois");
		createTrackbar("Value Guy", "SliderBois", &thresh, 254);
		imshow("raw", frame);
		imshow("Gray", frameGray);
		imshow("invert", frameInvert);
		imshow("binary", frameBin);

		char keypress = waitKey(10);
		if (keypress == 'q' || keypress == 27) break;

	}
}
*/