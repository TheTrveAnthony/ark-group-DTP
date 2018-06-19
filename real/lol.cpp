//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "xtra.h"
#include <iostream>


using namespace cv;
using namespace std;


int main(){


	for (int q = 1; q < 12 ; q++) {



	//string nom = "CroppedSamples/Sample_" + to_string(q) + "_400dpi(1).png";
	//string nom = "CroppedSamples/Sample_" + to_string(q) + "_400dpi(2).png";
	//string nom = "CroppedSamples/Sample_" + to_string(q) + "_600dpi(1).png";
	string nom = "CroppedSamples/Sample_" + to_string(q) + "_600dpi(2).png";

	int p = nom.size();


	


	Mat img = imread(nom, 1);
	Mat g = graymin(img);
	//imwrite("grayed.png", g);
	string nom2 = nom.substr(p-14);


	/////////////// both algorithms are written below, just comment the one you won't use //////////////////////////////////////
	////////////// ............ which means you'll have to edit the file & compile the whole thing every time you want to switch to another algorithm /////////////////////////
	/////////////// Enjoy. //////////////////////////////////////////////
	////////////////////////////////////////////// Or die. //////////////
	
	
	


	/////////////////////////////////////////////////// First algorithm : Mean Filter ////////////////////////////////////

	//cout << endl << "Mean filter algorithm" << endl;
	Mat i;
	Mat k = Mat::ones(17, 17, CV_32F)/289;
	Point anchor = Point( -1, -1 );
	filter2D(g, i, -1, k, anchor, 0, BORDER_DEFAULT);
	//imwrite("mean/filtered/Sample_" + to_string(q) + nom2, i);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	

	


/*
	

	///////////////////////////////////////////////// Second algorithm : Gaussian Filter + Kuwahara ////////////////////////

	//cout << endl << "Kuwahara & Gaussian algorithm" << endl;
	Mat i;	
	Size2i sz(103, 103);
	GaussianBlur(g, i, sz, 1.6);
	//imwrite("gaussianed.png", i);
	i = kuwahara(i);
	//imwrite("kuwahara/filtered/Sample_" + to_string(q) + nom2, i);		

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
	

	/////////// Common part //////////////////


	// thresholding

	int t = filtre_h(i);
	Mat t_i; // thresholded image
	threshold(i, t_i, t, 255, THRESH_BINARY);
	//imshow("thresholded.png", t_i);
	//waitKey(0);
	// blob detection

	SimpleBlobDetector::Params params;
	params.filterByInertia = false;
	params.filterByConvexity = true;
	params.maxConvexity = 100;
	params.minConvexity = 0.1;
	params.filterByColor = true;
	params.blobColor = 255;
	params.filterByArea = true;
	params.maxArea = 1000;
	params.minArea = 200;

	#if CV_MAJOR_VERSION < 3   // If you are using OpenCV 2
 
  // Set up detector with params
 	 SimpleBlobDetector detector(params); 
 
	#else
 
  // Set up detector with params
  	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
 

	#endif

  	vector<KeyPoint> keypoints;
	detector.detect(t_i, keypoints);
	Mat i_blob; // output image
	drawKeypoints(img, keypoints, i_blob, Scalar(184, 96, 37), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
	drawKeypoints(t_i, keypoints, t_i, Scalar(184, 96, 37), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
	//imshow("blobs.png", t_i);
	//waitKey(0);
	/////////////
	
	

	//imshow("sdd", i_blob);
	//waitKey(0);
	imwrite("mean/final/Sample_" + to_string(q) + nom2, i_blob);





}
	cout << endl << endl << "noraj." << endl << endl;
	return 0;

}
