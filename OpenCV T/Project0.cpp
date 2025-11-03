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
    // Create VideoCapture object to access webcam (0 = default camera)
    VideoCapture cap(0);

    // Check if webcam opened successfully
    if (!cap.isOpened()) {
        cout << "ERROR: Could not open webcam" << endl;
        return;
    }

    Mat img;

    // Create window for trackbars
    namedWindow("Trackbars", WINDOW_AUTOSIZE);
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);

    while (true) {
        // Capture frame-by-frame from webcam
        cap >> img;

        // If frame is empty, break immediately
        if (img.empty()) {
            cout << "ERROR: Blank frame grabbed" << endl;
            break;
        }

        // Convert BGR to HSV
        cvtColor(img, imgHSV, COLOR_BGR2HSV);

        // Create lower and upper threshold values
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);

        // Create mask based on HSV range
        inRange(imgHSV, lower, upper, mask);

        // Display windows
        imshow("Webcam", img);
        imshow("Image HSV", imgHSV);
        imshow("Mask", mask);

		// Apply mask to original image
        Mat result;
        bitwise_and(img, img, result, mask);
        imshow("Result", result);

        // Press ESC (27) to exit
        if (waitKey(1) == 27) {
            break;
        }
    }



    // Release webcam and close windows
    cap.release();
    destroyAllWindows();
}
