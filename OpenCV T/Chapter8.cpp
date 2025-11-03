#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;


void main() {

    string path = "Resources/test.png";
    Mat img = imread(path);

	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml"); // Load the pre-trained Haar Cascade XML file for face detection

	if (faceCascade.empty())
	{
		cout << "XML File not loaded." << endl;
	}

	vector<Rect> faces; // Vector of rectangles to hold the detected faces
	faceCascade.detectMultiScale(img, faces, 1.1, 4); // Detect faces

	for (int i = 0; i < faces.size(); i++)
	{
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
	}

    imshow("Image", img);
    waitKey(0);

}