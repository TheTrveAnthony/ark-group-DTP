//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "xtraml.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>


using namespace cv;
using namespace std; 


/* Here we'll test an image and send it in our model to see if it's got an error or not. Works only with csv containing one image for now.. */


int main() {


	// samples to test

	//String nom("/home/hiwi/Documents/MLanthony/DTPML/old/p.csv");
	String nom("/home/hiwi/Documents/MLanthony/DTPML/m.csv");
//	cin >> nom ;


	// let's read the images 
	vector<Mat> img ;
	vector<int> lbl ;
	cout << "boom boom pow" << endl ;
	//read_csv3(nom, img, lbl);


	// let's create a new csv with what will be used for ML
	

	


	// choose the classifier here, make sure it is the same in the others files before compiling 

	CvGBTrees arg = CvGBTrees();
	//CvRTrees arg = CvRTrees();
	//CvNormalBayesClassifier arg = CvNormalBayesClassifier();

	cout << endl << "loading model...." << endl ;
	arg.load("trained.xml");
	cout << "loaded" << endl ;
	
	read_csv3(nom, img, lbl);
	int siz = img.size();
	
	cout << endl << "starting predictions" << endl;
	int yu = img[0].cols*img[0].rows;
	double tm(0);
	for (int k = 0 ; k < siz ; k++) {
	
		clock_t tp;

		tp = clock();
		ofstream csvv("data.csv"); 
		fill_csv2(csvv, img[k], lbl[k]);

		// ML part //////////////////////////////////////////////////////


		CvMLData data = CvMLData();
		int dat = data.read_csv("data.csv");
		//data.set_response_idx(yu);


		const CvMat* i = data.get_values();
	
		//cout << endl << "starting prediction" << endl;
	
		float rep = arg.predict(i);
		tp = clock() - tp;
	
		ofstream rz("results", ios::app); 	// to store the results in a file
	
		if(rep == 1) {rz << endl << "one or several error found." << endl;}
		else {rz << endl << "No error." << endl;}
	
		rz << "prediction time : " << (double)tp/CLOCKS_PER_SEC << endl ;

		tm += (double)tp/CLOCKS_PER_SEC;
 
	}
	remove("data.csv");
	tm /= siz;
	cout << tm << endl;
	cout << endl << "noraj" << endl;

	return 0;
}
