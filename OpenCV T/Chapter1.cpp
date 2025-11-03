#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Display an image in a window
/*
void main() {

    string path = "Resources/lambo.png";
    Mat img = imread(path);
    imshow("Image", img);
    waitKey(0);

} */

// video 
/*
void main() {

    string path = "Resources/test_video.mp4";
    VideoCapture cap(path); // attempts to open the file at path.
    Mat img;

	// for video we need to capture every single frame 
    // from the video and display it as images

    while (true) {
		cap.read(img); //Grabs the next frame from the video, decodes it and stores it in img
		imshow("Video_Image", img);
		waitKey(1);
    }
}

*/

// webcam

void main() {
	VideoCapture cap(0); // 0 is id no for which webcam to use, 0 is default camera
	Mat img;

    while (1) {
        cap.read(img); //Grabs the next frame from the video, decodes it and stores it in img Matrix
        imshow("Webcam", img);
		waitKey(1);
    }
}