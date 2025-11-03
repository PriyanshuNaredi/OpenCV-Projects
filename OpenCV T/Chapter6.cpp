#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat imgHSV, mask;
int hmin = 0, smin = 110, vmin = 153;
int hmax = 19, smax = 240, vmax = 255;

void main() {
	string path = "Resources/lambo.png";
	Mat img = imread(path);

	cvtColor(img, imgHSV, COLOR_BGR2HSV); // convert to grayscale	

	namedWindow("Trackbars", (640, 200)); // create a window for trackbars 
	createTrackbar("Hue Min", "Trackbars", &hmin, 179); // create trackbars
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);


	while (true) {
		
		Scalar lower(hmin, smin, vmin); // create the upper and lower thresholded values
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask); // create the mask 


		imshow("Image", img);
		imshow("Image HSV", imgHSV);
		imshow("Mask", mask);
		waitKey(1);
	}
}