#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include "frcColor.h"

using namespace cv;
using namespace std;

int main() {

	int thresh = 0;
	VideoCapture cam;
	Mat frame, frameHSV, frameRange, frameDone;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	cam.open(1);

	int lowH = 0;
	int lowS = 0;
	int lowV = 0;
	int highH = 0;
	int highS = 0;
	int highV = 0;
	int maxArea = 0;
	int minArea = 0;


	for (;;) {
		cam >> frame;

		if (frame.empty()) {
			cout << "failed to open img.jpg" << endl;
		}

		cvtColor(frame, frameHSV, COLOR_BGR2HSV);
		inRange(frameHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), frameRange);
		morphologyEx(frameRange, frameDone, MORPH_OPEN, kernel, Point(-1, -1), 1);
		
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(frameDone, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
		for (size_t i = 0; i < contours.size(); i++)
		{
			drawContours(draw, contours, i, Scalar(255, 0, 255), 3, 8, hierarchy, 0, Point());
		}
		
		namedWindow("Sliders");
		createTrackbar("lowH", "Sliders", &lowH, 255);
		createTrackbar("highH", "Sliders", &highH, 255);
		createTrackbar("lowS", "Sliders", &lowS, 255);
		createTrackbar("highS", "Sliders", &highS, 255);
		createTrackbar("lowV", "Sliders", &lowV, 255);
		createTrackbar("highV", "Sliders", &highV, 255);
		imshow("Hello :)", frameDone);
		char keypress = waitKey(10);
		if (keypress == 'q' || keypress == 27) break;

	}
}