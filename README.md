# OpenCV C++ Computer Vision Course & Projects

This repository contains the source code for a comprehensive, hands-on guide to computer vision using OpenCV with C++. The code covers fundamental concepts, from basic image processing to building three complete, real-world projects.

## 📚 Core Concepts Covered

The course is structured chapter-by-chapter, building from foundational knowledge to more advanced techniques.

### Chapter 1: Import Images, Videos, & Webcams

* **Images**: Learn to load an image from a file into a `cv::Mat` object using `cv::imread()`.
* **Videos**: Use `cv::VideoCapture` to open and read video files. This involves creating a `while` loop to read the video frame by frame.
* **Webcam**: Extend the `cv::VideoCapture` logic to open a live camera feed by passing a device ID (e.g., 0) instead of a file path.
* **Display**: Use `cv::imshow()` to display `Mat` objects (images or video frames) in a window and `cv::waitKey()` to control the display time and handle user input.

### Chapter 2: Basic Image Processing Functions

This chapter covers the most essential functions for image manipulation and analysis.
* **Grayscale Conversion**: Use `cv::cvtColor()` with the `COLOR_BGR2GRAY` flag to convert a 3-channel (Blue, Green, Red) image into a single-channel grayscale image.
* **Gaussian Blur**: Apply `cv::GaussianBlur()` to reduce image noise and detail, which is a common preprocessing step for tasks like edge detection.
* **Canny Edge Detection**: Use `cv::Canny()` to identify and extract the edges from an image. It highlights sharp changes in intensity.
* **Dilation & Erosion**: These are morphological operations.
    * `cv::dilate()`: Increases the thickness or size of the white (foreground) pixels, useful for joining broken edges.
    * `cv::erode()`: Decreases the thickness of foreground pixels, useful for removing small noise.

### Chapter 3: Resize & Crop

* **Resize**: Use `cv::resize()` to change the dimensions of an image. This can be done by specifying an exact output size (`cv::Size`) or by providing scaling factors for the X and Y axes.
* **Crop (Region of Interest)**: Learn to extract a specific part of an image. This is achieved by defining a `cv::Rect` (Rectangle) that specifies the starting (x, y) coordinates, width, and height of the desired area. This `Rect` is then used to select a "Region of Interest" (ROI) from the main image `Mat`.

### Chapter 4: Drawing Shapes & Text

* **Blank Images**: Learn to create a new, blank `Mat` object from scratch, specifying its size (height, width) and type (e.g., `CV_8UC3` for a 3-channel 8-bit image).
* **Shapes**: Use built-in functions to draw on an image:
    * `cv::circle()`
    * `cv::rectangle()`
    * `cv::line()`
* **Text**: Use `cv::putText()` to overlay text onto an image, specifying the text, font, position, color, and thickness.

### Chapter 5: Warp Images (Perspective Transform)

This chapter covers how to get a "bird's-eye view" of an object in an image.
1.  **Define Points**: Identify the four corner points of the object in the source image (e.g., the corners of a book on a table). These are stored as `cv::Point2f`.
2.  **Define Destination**: Define the four destination points that you want the source points to map to (e.g., the corners of a flat, rectangular image).
3.  **Get Transform Matrix**: Use `cv::getPerspectiveTransform()` with the source and destination points to calculate the 3x3 transformation matrix.
4.  **Apply Warp**: Use `cv::warpPerspective()` with the original image and the calculated matrix to produce the final, warped image.

### Chapter 6: Color Detection

* **HSV Color Space**: Learn why the BGR color space is difficult for color detection (due to lighting) and how the HSV (Hue, Saturation, Value) space is superior. Hue represents the color, Saturation the purity, and Value the brightness.
* **Masking**: Use `cv::inRange()` to isolate a specific range of HSV values. This function creates a binary "mask" (a black and white image) where white pixels represent the color that falls within your specified range.
* **Trackbars**: Learn to use `cv::createTrackbar()` to add sliders to your display window. This allows you to dynamically adjust the min/max HSV values in real-time, making it easy to find the perfect values for the color you want to detect.

### Chapter 7: Shape Detection (Contours)

This chapter details the full pipeline for finding, filtering, and identifying shapes.
1.  **Pre-processing**: Prepare the image using blur, Canny edge detection, and dilation (from Ch 2).
2.  **Find Contours**: Use `cv::findContours()` on the pre-processed image to get a list (a `std::vector`) of all detected shapes. Each contour is itself a vector of points.
3.  **Filter Contours**: Loop through the list of contours and use `cv::contourArea()` to calculate the area of each shape. This allows you to filter out shapes that are too small (likely noise).
4.  **Approximate Shape**: For the remaining contours, use `cv::approxPolyDP()` to approximate the shape and reduce the number of points. This simplifies the shape to its essential corners.
5.  **Classify Shape**: By checking the number of corners (the size of the `approxPolyDP` output vector), you can classify the shape:
    * 3 corners = Triangle
    * 4 corners = Rectangle or Square
    * More than 4 corners = Circle (or other polygon)
6.  **Bounding Box**: Use `cv::boundingRect()` to get the simple, upright bounding rectangle for a shape, which is useful for drawing boxes and finding coordinates.

### Chapter 8: Face Detection (Haar Cascades)

* **Cascade Classifier**: Learn to use `cv::CascadeClassifier` to load pre-trained XML files. These files contain data (features) that allow the classifier to recognize specific objects.
* **Haar Cascades**: Use a pre-trained Haar Cascade file specifically for detecting frontal faces.
* **Detect Objects**: Use the `detectMultiScale()` method of the classifier. This function scans the image at multiple scales and returns a `std::vector<cv::Rect>`, where each `Rect` is the bounding box for a detected face.

---

## 🚀 Projects

These three projects combine the core concepts into practical applications.

### 1. Project 1: Virtual Painter

This project uses a colored marker (like a pen cap) to draw on the screen.

* **Logic**:
    1.  Read the webcam feed frame by frame.
    2.  Use Color Detection (Ch 6) to find the specific color of the marker tip. This creates a binary mask.
    3.  Find the contours of the white blob in the mask (Ch 7).
    4.  Get the bounding box (`cv::boundingRect`) of the largest contour to find its coordinates.
    5.  Calculate the top-center point of this bounding box; this will be our "pen tip."
    6.  Store this point in a list.
    7.  Loop through the list of stored points and draw a circle (Ch 4) at each point's coordinates, using the color that was detected. This creates the drawing effect.

### 2. Project 2: Document Scanner

This application finds a document (like a piece of paper) in an image and transforms it into a flat, "scanned" image.

* **Logic**:
    1.  Pre-process the input image using Blur, Canny, and Dilation (Ch 2) to get a clear outline of the document.
    2.  Find all contours and identify the largest one (Ch 7), assuming this is the paper.
    3.  Approximate the contour using `approxPolyDP` to get the four corner points of the document.
    4.  **Reorder Points**: The four points found may not be in a consistent order (e.g., top-left might not be the first point). A custom function is implemented to sort these points into a reliable [top-left, top-right, bottom-left, bottom-right] order.
    5.  **Warp**: Use these four sorted points as the *source* points for a Perspective Warp (Ch 5).
    6.  Define the *destination* points as a flat rectangle (e.g., the size of an A4 paper).
    7.  Apply `cv::warpPerspective()` to get the final, top-down scanned image.

### 3. Project 3: Number Plate Detection

This project uses a webcam feed to detect vehicle number plates in real-time, crop them, and save them as new image files.

* **Logic**:
    1.  Load a pre-trained Haar Cascade XML file for number plate detection (instead of faces, as in Ch 8).
    2.  In a `while` loop, read frames from the webcam.
    3.  Use `detectMultiScale()` on each frame to get a list of `cv::Rect` objects, each representing a detected number plate.
    4.  Loop through each `Rect` (each detected plate).
    5.  Use the `Rect` as a Region of Interest (ROI) to crop that section from the original frame (Ch 3).
    6.  Save the cropped `Mat` object to a new file using `cv::imwrite()`.

---
*This code is based on the "LEARN OPENCV C++ in 4 HOURS" tutorial by Murtaza's Workshop.*
