#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include "frcColor.h"

using namespace cv;
using namespace std;
int trackBars() {



}
int main() {

	int thresh = 0;
	VideoCapture cam;
	Mat frame, frameHSV, frameRange, frameDone, frameProc;
	vector<vector<Point> > contours;
	Mat kernel = getStructuringElement(MORPH_CROSS, Size(5, 5), Point(-1, -1));
	cam.set(CAP_PROP_AUTO_EXPOSURE, false);

	cam.open(0);

	//Int Definitions
	int lowH = 0;
	int lowS = 0;
	int lowV = 0;
	int highH = 100;
	int highS = 100;
	int highV = 100;
	int static maxAreaSet = 10000;
	int maxArea = (maxAreaSet / 2);
	int minArea = 0;
	int exposure = 5;

	//Trackbars
	cv::namedWindow("Sliders");
	cv::namedWindow("Contour Sliders");
	cv::createTrackbar("lowH", "Sliders", &lowH, 255);
	cv::createTrackbar("highH", "Sliders", &highH, 255);
	cv::createTrackbar("lowS", "Sliders", &lowS, 255);
	cv::createTrackbar("highS", "Sliders", &highS, 255);
	cv::createTrackbar("lowV", "Sliders", &lowV, 255);
	cv::createTrackbar("highV", "Sliders", &highV, 255);
	cv::createTrackbar("Exposure", "Sliders", &exposure, 10);
	cv::createTrackbar("minArea", "Contour Sliders", &minArea, (maxAreaSet - 1));
	cv::createTrackbar("maxArea", "Contour Sliders", &maxArea, maxAreaSet);

	//Forever loop
	for (;;) {
		cam.set(CAP_PROP_EXPOSURE, exposure);
		cam >> frame;
		cv::imshow("Sad :(", frame);
		if (frame.empty()) {
			cout << "failed to open img.jpg" << endl;
		}

		cvtColor(frame, frameHSV, COLOR_BGR2HSV);
		inRange(frameHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), frameRange);
		morphologyEx(frameRange, frameDone, MORPH_CLOSE, kernel, Point(-1, -1), 1);
		morphologyEx(frameDone, frameDone, MORPH_OPEN, kernel, Point(-1, -1), 1);

		findContours(frameDone, contours, RETR_LIST, CHAIN_APPROX_SIMPLE, Point(0, 0));
		frameProc = frameDone;
		cvtColor(frameProc, frameProc, COLOR_GRAY2RGB);

		//All contour stuff
		for (size_t i = 0; i < contours.size(); i++)
		{

			if (contourArea(contours[i]) < minArea || contourArea(contours[i]) > maxArea) {
				continue;
			}
			Rect boundRect = boundingRect(contours[i]);
			float ratio = contourArea(contours[i]) / (boundRect.width * boundRect.height);
			drawContours(frameProc, contours, i, Scalar(0, 0, 255), 3);
		}
		

		cv::imshow("Hello :)", frameProc);
		char keypress = waitKey(10);
		if (keypress == 'q' || keypress == 27) break;

	}
}