//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "xtraml.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


using namespace cv;
using namespace std; 


/* Here we'll load a ML model for the DTP Alarm to train it even more. */


int main() {

	cout << endl << "csv file to read :" << endl ;
	String nom;
	cin >> nom ;


	// let's read the images and resize em
	vector<Mat> img ;
	vector<int> lbl ;
	cout << "ok" << endl ;
	read_csv3(nom, img, lbl);

	cout << endl << endl;
	// let's create a new csv with what will be used for ML

	ofstream csvv("data.csv"); 
	fill_csv(csvv, img, lbl);
	int yu = img[0].cols*img[0].rows;

	// ML part //////////////////////////////////////////////////////

	CvMLData data = CvMLData();
	int dat = data.read_csv("data.csv");
	data.set_response_idx(yu);



	const CvMat* i = data.get_values();
	const CvMat* l = data.get_responses();

	
	

	//CvGBTrees arg = CvGBTrees();
	//CvRTrees arg = CvRTrees();
	CvNormalBayesClassifier arg = CvNormalBayesClassifier();
	
	cout << endl << "loading model...." << endl ;
	arg.load("trained.xml");
	cout << "loaded" << endl ;
	
	cout << endl << "starting training" << endl;
	bool zaq = arg.train(i, l, 0, 0, true);
	cout << "training done" << endl;
	arg.save("trained.xml");
	cout << "model saved" << endl; 

	remove("data.csv");
	cout << endl << "noraj" << endl;

	return 0;
}
