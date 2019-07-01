import numpy as np
import argparse
import time
import cv2



##[82.0901287553648, 159.05579399141632, 58.80257510729613]

blueLower = np.array([90, 100, 20], dtype = "uint8")
blueUpper = np.array([120, 200, 150], dtype = "uint8")
camera = cv2.VideoCapture(1)

while True:
	(grabbed, frame) = camera.read()
	#frame = frame[0:300,0:1200]
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
		cv2.drawContours(frame, [rect], -1, (0, 255, 0), 2)

	cv2.imshow("Tracking", frame)
	cv2.imshow("Binary", blue)
	time.sleep(0.025)
	if cv2.waitKey(1) and 0xFF == ord("q"):
		break

camera.release()
cv2.destroyAllWindows()

