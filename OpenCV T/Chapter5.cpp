#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

float w = 250, h = 350;
Mat matrix, imgWarp;

void main() {
	string path = "Resources/cards.jpg";
	Mat img = imread(path);

	Point2f src[4] = { {529, 142}, {771, 190}, {405, 395}, {674,457} };
	Point2f des[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };

	// get the perspective transform matrix
	matrix = getPerspectiveTransform(src, des); // get transformation matrix
	warpPerspective(img, imgWarp, matrix, Point(w, h)); // apply perspective transformation

	for (int i = 0; i < 4; i++)
	{
		circle(img, src[i], 4, Scalar(0, 0, 255), FILLED);
	}


	imshow("Image", img);
	imshow("Warped Image", imgWarp);
	waitKey(0);

}