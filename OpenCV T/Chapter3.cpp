#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void main() {
	string path = "Resources/test.png"; // 768 x 559
	Mat img = imread(path);

	cout << img.size();

	// Resize Image
	Mat img_resize;
	resize(img, img_resize, Size(640, 480));

	// Resize Image with scale factors
	Mat img_resize2;
	resize(img, img_resize2, Size(), 0.5, 0.5); // fx = 0.5, fy = 0.5

	// Crop Image
	Mat img_croped = img(Rect(200, 100, 300, 300)); // x, y, width, height


	imshow("Image", img);
	imshow("Image Resize", img_resize);
	imshow("Image Resize 2", img_resize2);
	imshow("Image Croped", img_croped);
	waitKey(0);
}