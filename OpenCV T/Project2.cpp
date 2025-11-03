#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Display an image in a window
Mat imgOrg, imgGray, imgBlur, imgCanny, imgDil, imgErode, imgThreshold, imgWarp, imageCrop;

vector<Point> initialPoints, docPoints, finalPoints;

float w = 420, h = 596; // A4 size in pixels at 72 PPI

Mat prepreocessImg(Mat img, bool print) {
	/* Pre-Processes the image,
	converts image to grayscale => gauusian blur => canny edge detection => dialatio */

	// convert to gray scale
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	// apply Gaussian Blur
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);

	// Canny Edge Detection
	Canny(imgBlur, imgCanny, 25, 75); // threshold1, threshold2

	// Dilation - to increase the white region in the image or size of foreground object
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); // get structuring element is numpy 
	dilate(imgCanny, imgDil, kernel);


	while (print) {
		imshow("Image", img);
		imshow("Image Gray", imgGray);
		imshow("Image Blur", imgBlur);
		imshow("Image Canny", imgCanny);
		imshow("Image Dilation", imgDil);
	}

	return imgDil;
}

vector<Point> getContours(Mat imgDil) {

	//  Find Contours
	vector<vector<Point>> contours; // { {Point(a,b)}, Point(c,d)}, {}, {} }
	vector<Vec4i> hierarchy; // Vec4i is a vector of 4 integers
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); // find external contours, Draw Contours

	vector<vector<Point>> conPoly(contours.size()); // to store approximated polygonal curves
	vector<Rect> boundRect(contours.size()); // to store bounding rectangles

	vector<Point> biggest;
	int maxArea = 0;

	// Calculate Area of Contours
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);


		if (area > 1000) {

			float peri = arcLength(contours[i], true); // calculate perimeter

			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); // approximate polygonal curves

			if (area > maxArea && conPoly[i].size() == 4) { // find the biggest quadrilateral
				biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
				maxArea = area;
				// Draw Contours
				//drawContours(imgOrg, conPoly, i, Scalar(255, 0, 255), 5); // -1 means draw all contours

			}

			// Draw Bounding Rectangle i.e. rectangle around the object
			//boundRect[i] = boundingRect(conPoly[i]); // get bounding rectangle
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5); // draw rectangle
			 
		}
	}
	return biggest;
}

void drawPoints(vector<Point> points, Scalar color) {

	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOrg, points[i], 10, color, FILLED);
		putText(imgOrg, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
	}

}

vector<Point> reorder(vector<Point> points) {

	vector<Point> newPoints;
	vector<int> sumPoints, subPoints; // sum of x and y coordinates, subtraction of x and y coordinates

	for (int i = 0; i < 4; i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}
	//min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin(); // top-left point
	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // top-left point
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // top-right point
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // bottom-left point
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // bottom-right point

	return newPoints;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h) {

	Point2f src[4] = { points[0], points[1], points[2], points[3]};
	Point2f des[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };

	// get the perspective transform matrix
	Mat matrix = getPerspectiveTransform(src, des); // get transformation matrix
	warpPerspective(img, imgWarp, matrix, Point(w, h)); // apply perspective transformation

	return imgWarp;
}

void main() {

    string path = "Resources/paper.jpg";
    imgOrg = imread(path);

	//resize(imgOrg, imgOrg, Size(), 0.5, 0.5);

	// Preprocess the image
	imgThreshold = prepreocessImg(imgOrg, false);

	// contours
	initialPoints = getContours(imgThreshold);
	//drawPoints(initialPoints, Scalar(0, 0, 255));
	docPoints = reorder(initialPoints);
	//drawPoints(docPoints, Scalar(0, 255, 0));


	// warp
	imgWarp = getWarp(imgOrg, docPoints, w, h);

	// Crop
	int cropVal = 5;
	Rect roi(cropVal, cropVal, w - (2*cropVal), h - (2*cropVal));
	imageCrop = imgWarp(roi);



    imshow("Image", imgOrg);
	imshow("Image Threshold", imgThreshold);
	imshow("Image Warp", imgWarp);
	imshow("Image Crop", imageCrop);
    waitKey(0);
}