#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>


using namespace std;
using namespace cv;

Mat prepreocessImg(Mat img, bool print) {
	/* Pre-Processes the image, 
	converts image to grayscale => gauusian blur => canny edge detection => dialatio */

	// convert to gray scale
	Mat img_to_grayScale;
	cvtColor(img, img_to_grayScale, COLOR_BGR2GRAY);

	// apply Gaussian Blur
	Mat img_blur;
	GaussianBlur(img_to_grayScale, img_blur, Size(3, 3), 3, 0);

	// Canny Edge Detection
	Mat img_canny;
	Canny(img_blur, img_canny, 25, 75); // threshold1, threshold2

	// Dilation - to increase the white region in the image or size of foreground object
	Mat img_dilation;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); // get structuring element is numpy 
	dilate(img_canny, img_dilation, kernel);


	while (print) {
		imshow("Image", img);
		imshow("Image Gray", img_to_grayScale);
		imshow("Image Blur", img_blur);
		imshow("Image Canny", img_canny);
		imshow("Image Dilation", img_dilation);
	}

	return img_dilation;
}

static void getContours(Mat imgDil, Mat img) {

	//  Find Contours
	vector<vector<Point>> contours; // { {Point(a,b)}, Point(c,d)}, {}, {} }
	vector<Vec4i> hierarchy; // Vec4i is a vector of 4 integers
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); // find external contours, Draw Contours

	vector<vector<Point>> conPoly(contours.size()); // to store approximated polygonal curves
	vector<Rect> boundRect(contours.size()); // to store bounding rectangles

	string objectType;

	// Calculate Area of Contours
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << "Area of Contour " << i << ": " << area << endl;


		if (area > 1000) {

			float peri = arcLength(contours[i], true); // calculate perimeter

			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); // approximate polygonal curves

			// Draw Contours
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2); // -1 means draw all contours

			cout << "Number of sides: " << conPoly[i].size() << endl;

			// Draw Bounding Rectangle i.e. rectangle around the object
			boundRect[i] = boundingRect(conPoly[i]); // get bounding rectangle
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5); // draw rectangle

			// Object Type Detection
			int objCorner = (int)conPoly[i].size();
			if (objCorner == 3)
			{
				objectType = "Triangle";
			}
			else if (objCorner == 4)
			{
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				if(aspRatio > 0.95 && aspRatio < 1.05) {
					objectType = "Square";
				}
				else {
					objectType = "Rectangle";
				}
			}
			else {
				objectType = "Circle";
			}
			// Put Text
			putText(img, objectType, { boundRect[i].x, boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
		}
	}

	imshow("Contours", img);
}

void main() {
	string path = "Resources/shapes.png";
	Mat img = imread(path);

	Mat imgDil = prepreocessImg(img, false);
	getContours(imgDil, img);

	waitKey(0);
}