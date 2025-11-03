#include <iostream>
#include <sstream>
#include <chrono>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void main() {

	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255)); 
	// 512x512 image, 8 bit unsigned int, 3 channels (RGB); Scalar(B, G, R)

	// draw a circle
	circle(img, Point(256, 256), 155, Scalar(0, 69, 255), -1); 
	// center at (256, 256), radius 155, color (B, G, R), thickness 10 / Filled(-1)

	// draw rectangle
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED); 
	// top-left and bottom-right points

	// draw line
	line(img, Point(130, 296), Point(382, 296), Scalar(0, 0, 0), 2); // thickness 2

	// put text
	putText(img, "OpenCV", Point(135, 275), FONT_HERSHEY_DUPLEX, 2, Scalar(0, 69, 255), 2); // font scale 2, thickness 2

	const string windowName = "Image";
	imshow(windowName, img);

	cout << "Press 's' to save the image, ESC to exit." << endl;

	while (true) {
		int key = waitKey(0); // wait for a key press
		if (key == 27) { // ESC
			break;
		}
		if (key == 's' || key == 'S') {
			// create a timestamped filename to avoid overwriting
			auto now = chrono::system_clock::now();
			auto ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
			ostringstream oss;
			oss << "Resources/generated_image_" << ms << ".png";
			string filename = oss.str();

			bool ok = imwrite(filename, img);
			if (ok) {
				cout << "Image saved to: " << filename << endl;
			} else {
				cerr << "Failed to save image to: " << filename << endl;
			}
		}
	}

	destroyAllWindows();
}