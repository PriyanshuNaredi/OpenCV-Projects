#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void main() {
	string path = "Resources/test.png";
	Mat img = imread(path);

	// convert to gray scale
	Mat img_to_grayScale;
	cvtColor(img, img_to_grayScale, COLOR_BGR2GRAY);

	// apply Gaussian Blur
	Mat img_blur;
	GaussianBlur(img_to_grayScale, img_blur, Size(3,3), 3, 0);

	// Canny Edge Detection
	Mat img_canny;
	Canny(img_blur, img_canny, 50, 150);

	// Dilation - to increase the white region in the image or size of foreground object
	Mat img_dilation;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); // get structuring element is numpy 
	dilate(img_canny, img_dilation, kernel);

	// Erosion - to erode away the boundaries of foreground object
	Mat img_erosion;
	erode(img_dilation, img_erosion, kernel); 

	imshow("Image", img);
	imshow("Image Gray", img_to_grayScale);
	imshow("Image Blur", img_blur);
	imshow("Image Canny", img_canny);
	imshow("Image Dilation", img_dilation);
	imshow("Image Erosion", img_erosion);
	waitKey(0);
}