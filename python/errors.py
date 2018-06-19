#coding "utf-8"

import cv2 as cv 
import numpy as np 
import time
#from matplotlib import pyplot as plt
from xtra import *



def detect1(img):

	"""implementation of first algorithm : img is the name of the image"""

	d = time.time()
	im = cv.imread(img, 1)

	###################### grayscle min(r, g, b) convertion #####################################

	
	im2 = graymin(im)



	######################  Mean Filter & Thresholding############################################

	

	
	kernel = np.ones((5, 5),np.float32)/25
	im3 = cv.filter2D(im2, -1, kernel)
	t = filtre_h(im3)
	print(t)
	th, dst = cv.threshold(im3, t, 255, cv.THRESH_TOZERO)



	######################## Blob Detection ####################################



	pts = blbz(dst)
	im_blb = cv.drawKeypoints(im, pts, np.array([]), (255,25,29), cv.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
	print "Number of errors : {} \n".format(len(pts))



	######################
	
	f = time.time()
	temps = f - d
	print"execution time: {} ".format(temps)

	#cv.imwrite("detect1" + img, dst)
	cv.imshow("voilaaaa", im_blb)
	cv.waitKey(0)




def detect2(img):

	"""Second algorithm"""

	d = time.time()
	im = cv.imread(img, 1)

	###################### grayscle min(r, g, b) convertion #####################################


	im2 = graymin(im)


	####################### Gaussian Blur & Kuwahara Filtering + Thresholding ####################


	blur = cv.GaussianBlur(im2, (7, 7), 1.41)
	ku = kuwahara(blur)
	t = filtre_h(ku)
	print(t)
	th, dst = cv.threshold(ku, t, 255, cv.THRESH_TOZERO)



	######################## Blob Detection ####################################



	pts = blbz(dst)
	im_blb = cv.drawKeypoints(im, pts, np.array([]), (255,24,29), cv.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
	print "Number of errors : {} \n".format(len(pts))


	######################
	


	f = time.time()
	temps = f - d
	print"execution time: {} ".format(temps)
	cv.imshow("voilaaaa", im_blb)
	cv.waitKey(0)
	#cv.imwrite("detect2" + img , dst)






	


