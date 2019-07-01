import numpy as np
import argparse
import time
import cv2



def area(points):
    return (points[1] - points[0]) * (points[3] - points[2])


def parallel_to_img(points):

    point1x = points[0][0]
    point1y = points[0][1]

    point2x = points[1][0]
    point2y = points[1][1]

    point3x = points[2][0]
    point3y = points[2][1]

    point4x = points[3][0]
    point4y = points[3][1]

    min_x = min(point1x, point2x, point3x, point4x)
    max_x = max(point1x, point2x, point3x, point4x)

    min_y = min(point1y, point2y, point3y, point4y)
    max_y = max(point1y, point2y, point3y, point4y)

    newrect = np.array([[max_x, max_y], [min_x, max_y], [min_x, min_y], [max_x, min_y]])

    return newrect


def return_ordered(points):

    point1x = points[0][0]
    point1y = points[0][1]

    point2x = points[1][0]
    point2y = points[1][1]

    point3x = points[2][0]
    point3y = points[2][1]

    point4x = points[3][0]
    point4y = points[3][1]

    min_x = min(point1x, point2x, point3x, point4x)
    max_x = max(point1x, point2x, point3x, point4x)

    min_y = min(point1y, point2y, point3y, point4y)
    max_y = max(point1y, point2y, point3y, point4y)

    newrect = [min_x, max_x, min_y, max_y]

    return newrect


def transf(points, y1, x1):

    point1x = points[0][0] + x1
    point1y = points[0][1] + y1

    point2x = points[1][0] + x1
    point2y = points[1][1] + y1

    point3x = points[2][0] + x1
    point3y = points[2][1] + y1

    point4x = points[3][0] + x1
    point4y = points[3][1] + y1

    newrect = np.array([[point1x, point1y], [point2x, point2y], [point3x, point3y], [point4x, point4y]])

    return newrect




##~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


##[82.0901287553648, 159.05579399141632, 58.80257510729613]

blueLower = np.array([102, 54, 20], dtype = "uint8")
blueUpper = np.array([122, 74, 255], dtype = "uint8")
camera = cv2.VideoCapture(1)

while True:
    
    (grabbed, frame) = camera.read()
	#frame = frame[0:300,0:1200]
    
    frame = cv2.flip(frame, 1) ## mirroring
    
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    if not grabbed:
        break

    blue = cv2.inRange(frame, blueLower, blueUpper)
    blue = cv2.GaussianBlur(blue, (3, 3), 0)

    (cnts, _) = cv2.findContours(blue.copy(), cv2.
									RETR_EXTERNAL,
									cv2.CHAIN_APPROX_SIMPLE)

    if len(cnts) > 0:
	
        cnt = sorted(cnts, key = cv2.contourArea, reverse = True)[0]
		
        rect = np.int32(cv2.boxPoints(cv2.minAreaRect(cnt)))
		
        p_rect = parallel_to_img(rect)
		
        cv2.drawContours(frame, [rect], -1, (0, 255, 0), 2)
        cv2.imshow("Tracking", frame)
        cv2.imshow("Binary", blue)
        
        orderedRect = return_ordered(p_rect)
		
        if area(orderedRect) > 10:
    		
            
            
            center = ((orderedRect[0]+orderedRect[1])/2,(orderedRect[2]+orderedRect[3])/2)
            
            
            print(center)


	

