import numpy as np
import argparse
import time
import cv2

from sklearn.cluster import KMeans
from collections import Counter


def get_dominant_color(image, k=4, image_processing_size=None):
	"""
    takes an image as input
    returns the dominant color of the image as a list

    dominant color is found by running k means on the
    pixels & returning the centroid of the largest cluster

    processing time is sped up by working with a smaller image;
    this resizing can be done with the image_processing_size param
    which takes a tuple of image dims as input

    >>> get_dominant_color(my_image, k=4, image_processing_size = (25, 25))
    [56.2423442, 34.0834233, 70.1234123]
    """
	# resize image if new dims provided
	if image_processing_size is not None:
		image = cv2.resize(image, image_processing_size,
						   interpolation=cv2.INTER_AREA)

	# reshape the image to be a list of pixels
	image = image.reshape((image.shape[0] * image.shape[1], 3))

	# cluster and assign labels to the pixels
	clt = KMeans(n_clusters=k)
	labels = clt.fit_predict(image)

	# count labels to find most popular
	label_counts = Counter(labels)

	# subset out most popular centroid
	dominant_color = clt.cluster_centers_[label_counts.most_common(4)[0][0]]

	return list(dominant_color)




ap = argparse.ArgumentParser()
ap.add_argument("-i", "--image", required = True, help = "Path to the image")
args = vars(ap.parse_args())



blueLower = np.array([30, 30, 10], dtype = "uint8")
blueUpper = np.array([150, 150, 150], dtype = "uint8")


orangeLower = np.array([40, 40, 70], dtype = "uint8")
orangeUpper = np.array([80, 80, 120], dtype = "uint8")

redLower = np.array([23, 20, 35], dtype = "uint8")
redUpper = np.array([30, 25, 44], dtype = "uint8")


frame =  cv2.imread(args["image"])
frame =  cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
print(get_dominant_color(frame))




