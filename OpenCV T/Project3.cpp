#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;


void main() {


	VideoCapture cap(0); // 0 is id no for which webcam to use, 0 is default camera
	Mat img;

	CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml"); // Load the pre-trained Haar Cascade XML file for face detection

	if (plateCascade.empty())
	{
		cout << "XML File not loaded." << endl;
	}


	vector<Rect> plates; // Vector of rectangles to hold the detected plates

	while (1) {
		cap.read(img); //Grabs the next frame from the video, decodes it and stores it in img Matrix


		plateCascade.detectMultiScale(img, plates, 1.1, 10); // Detect plates

		for (int i = 0; i < plates.size(); i++)
		{
			Mat imgCrop = img(plates[i]);
			imshow(to_string(i), imgCrop);
			//imwrite("Resources/plate_" + to_string(i) + ".jpg", imgCrop);
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
		}

		imshow("Webcam", img);
		waitKey(1);
	}

}
