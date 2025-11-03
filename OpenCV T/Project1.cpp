#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat img;
vector<vector<int>> newPoints; // {x, y, colorId}

// hmin, smin, vmin hmax, smax, vmax
vector<vector<int>> myColors{ {124,48,117,143,170,255}, // Purple
								{68,72,156,102,126,255}, // Green
                                {101, 97, 94, 179, 255, 255} };// Red


vector<Scalar> myColorValues{ {255,0,255},	// Purple
								{0,255,0},  // Green
                                {0,0,255} };// Red


Point getContours(Mat imgDil) {

	//  Find Contours
	vector<vector<Point>> contours; // { {Point(a,b)}, Point(c,d)}, {}, {} }
	vector<Vec4i> hierarchy; // Vec4i is a vector of 4 integers
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); // find external contours, Draw Contours

	vector<vector<Point>> conPoly(contours.size()); // to store approximated polygonal curves
	vector<Rect> boundRect(contours.size()); // to store bounding rectangles

	Point myPoint(0, 0);

	// Calculate Area of Contours
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		//cout << "Area of Contour " << i << ": " << area << endl;


		if (area > 1000) {

			float peri = arcLength(contours[i], true); // calculate perimeter

			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); // approximate polygonal curves

			// Draw Contours
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2); // -1 means draw all contours

			cout << "Number of sides: " << conPoly[i].size() << endl;

			// Draw Bounding Rectangle i.e. rectangle around the object
			boundRect[i] = boundingRect(conPoly[i]); // get bounding rectangle
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5); // draw rectangle

			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;


		}
	}
		return myPoint;
}

vector<vector<int>> findColor(Mat img) {

	Mat imgHSV;

    cvtColor(img, imgHSV, COLOR_BGR2HSV); // convert to grayscale	

	// loop through each color
    for(int i=0; i< myColors.size(); i++) {

        Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]); // create the upper and lower thresholded values
        Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
        Mat mask;
        inRange(imgHSV, lower, upper, mask); // create the mask
		//imshow(to_string(i), mask);

		Point myPoint = getContours(mask);
		if (myPoint.x != 0 && myPoint.y != 0)
			newPoints.push_back({ myPoint.x, myPoint.y, i });


	}

    //Scalar lower(hmin, smin, vmin); // create the upper and lower thresholded values
    //Scalar upper(hmax, smax, vmax);
    //inRange(imgHSV, lower, upper, mask); // create the mask 

	return newPoints;
}

void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues) {
	// Draw circles on the canvas
	for (int i = 0; i < newPoints.size(); i++) {
		circle(img, Point(newPoints[i][0], newPoints[i][1]), 10, myColorValues[newPoints[i][2]], FILLED);
	}
}

void main() {
    VideoCapture cap(0); // 0 is id no for which webcam to use, 0 is default camera

    while (1) {
        cap.read(img); //Grabs the next frame from the video, decodes it and stores it in img Matrix

        newPoints = findColor(img);
		drawOnCanvas(newPoints, myColorValues);

        imshow("Webcam", img);
        waitKey(1);
    }
}