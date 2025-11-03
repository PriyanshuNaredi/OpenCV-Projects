'''Read Image '''
# import cv2
# # Read the image from file
# img = cv2.imread('path_to_image.jpg')
# # Display the image in a window
# cv2.imshow('Image', img)
# cv2.waitKey(0)


'''Read Video '''

# import cv2

# frameWidth = 640
# frameHeight = 480

# cap = cv2.VideoCapture('path_to_video.mp4')
# while(True):
# 	success, img = cap.read()
# 	img = cv2.resize(img, (frameWidth, frameHeight))
# 	cv2.imshow('Video', img)
# 	if cv2.waitKey(1) & 0xFF == ord('q'):
# 		break


'''Read Webcam '''

import cv2

frameHeight = 480
frameWidth = 640

cap = cv2.VideoCapture(0) # 0 is usually the default camera
cap.set(3, frameWidth) # 3 is cv2.CAP_PROP_FRAME_WIDTH
cap.set(4, frameHeight) # 4 is cv2.CAP_PROP_FRAME_HEIGHT
cap.set(10, 150) # 10 is cv2.CAP_PROP_BRIGHTNESS. This requests a brightness value of 150 
while(True):
	success, img = cap.read()
	cv2.imshow('Webcam', img)
	if cv2.waitKey(1) & 0xFF == ord('q'):	
		break