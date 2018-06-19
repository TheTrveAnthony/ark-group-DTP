#coding "utf-8"

import cv2 as cv 
import numpy as np
from matplotlib import pyplot as plt


"""extra functions for the algorithms"""




def filtre_h(img):

	""" Filters the histogram of a grayscale image """


	hist = cv.calcHist([img],[0],None,[256],[0,256])
	#plt.hist(img.ravel(),256,[0,256])#; plt.show()
	k = 255
	
	m = 0

	while m < 3:

		if k == 255 and hist[k] > hist[k - 1] and hist[k - 1] > hist[k - 2]:

			m = 2

		if m == 0 or m == 2:

			if hist[k] < hist[k - 1] and hist[k - 1] < hist[k - 2]:		# going up

				m += 1

		if m == 1:

			if hist[k] > hist[k - 1] and hist[k - 1] > hist[k - 2]:		# going down

				m += 1

		if m != 3:

			k -= 1

	plt.show()

	return k 



def kuwahara(img):

	"""kuwahara filter 3*3, not avaiable in opencv so I gotta do it here """

	n = len(img)
	m = len(img[0])
	


	#### output image creation, the borders are the same as the input image ones (I guess)

	kuwa = np.zeros((n, m), dtype = "uint8")
	kuwa[0, :] = img[0, :]
	kuwa[:, 0] = img[:, 0]
	kuwa[n-1, :] = img[n-1, :]
	kuwa[:, m-1] = img[:, m-1]



	for i, vi in enumerate(img):
		for j, vj in enumerate(vi):



			try:

				#Kuwahara areas
				a0 = [img[i][j], img[i-1][j], img[i][j-1], img[i-1][j-1]]
				a1 = [img[i][j], img[i+1][j], img[i][j-1], img[i+1][j-1]]
				a2 = [img[i][j], img[i-1][j], img[i][j+1], img[i-1][j+1]]
				a3 = [img[i][j], img[i+1][j], img[i][j+1], img[i+1][j+1]]
				a = np.array([a0, a1, a2, a3])

				#mean and standart deviation of each area
				
				d = np.zeros(4)

				for k in range(0, 4):
					
					d[k] = np.std(a[k])

				# finding the lowest deviation and its index

				mini = np.argmin(d)

				kuwa[i][j] = np.mean(a[mini])

			except:

				s = 1	# don't pay attention to this

	return kuwa



def blbz(img):

	"""Blob Detection """

	# Setup SimpleBlobDetector parameters.
	params = cv.SimpleBlobDetector_Params()
 
	# detector paramters

	params.filterByInertia = False
	params.filterByConvexity = False
	params.filterByColor = False
	params.blobColor = 255
	params.filterByArea = True
	params.maxArea = 1000
	
	ver = (cv.__version__).split('.')
	if int(ver[0]) < 3 :
		detector = cv.SimpleBlobDetector(params)

 		
	else :
		detector = cv.SimpleBlobDetector_create(params)

	
	pts = detector.detect(img)
	#print(pts)
	#im_blb = cv.drawKeypoints(img, pts, np.array([]), (255,6,29), cv.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
	#cv.imshow("voilaaa", im_blb)
	#cv.waitKey(0)


	return pts



def graymin(im):

	""" Converts a color image into min(rgb) grayscale"""

	k = (len(im),len(im[0]))
	im2 = np.zeros(k, dtype = 'uint8')

	for i, vi in enumerate(im2):

		for j, vj in enumerate(vi):

			im2[i][j] = np.amin(im[i][j])

	return im2


def rofl(i):
	#cv.imread(i, 1)
	i2 = graymin(i)
	t = filtre_h(i2)
	print(t)
	th, dst = cv.threshold(i2, t, 255, cv.THRESH_TOZERO)
	cv.imshow("fdp", dst)
	cv.waitKey(0)


def thresh(img, t):

	for i, vi in enumerate(img):
		for j, vj in enumerate(vi):

			if vj < t:
				img[i][j] = 0
			else:
				img[i][j] = 1


def zone(img, lx, ly, dx, dy):

	i2 = np.zeros((lx, ly), dtype = "uint8")

	for i in range(0, lx):
		for j in range(0, ly):

			i2[i][j] = img[i+dx][j+dy] # x = hauteur, y = largeur

	return i2


def cprs(img, x):
	i = []
	s = 0
	"""
	for k, vk in enumerate(img):

		s += np.sum(vk)

	s /= len(img)"""

	for k, vk in enumerate(img):
		if np.sum(vk) < x:
			i.append(vk)

	i = np.array(i)
	
	return i


#def prepro(img):
