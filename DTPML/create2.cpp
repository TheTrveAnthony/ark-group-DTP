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


/* Here we'll create a ML model for the DTP Alarm and start training it. */


int main() {

	//cout << endl << "csv file to read :" << endl ;
	String nom("/home/hiwi/Documents/MLanthony/DTPML/samples.csv");
	//cin >> nom ;


	// let's read the images and resize em
	vector<Mat> img ;
	vector<int> lbl ;

	CvGBTrees arg = CvGBTrees();
	//CvNormalBayesClassifier arg = CvNormalBayesClassifier()

	read_csv3(nom, img, lbl);

	cout << endl << "starting training process" << endl;

	for (int q = 0; q < img.size(); q++) {


		ofstream csvv("data.csv"); 
		fill_csv2(csvv, img[q], lbl[q]);

		// ML part //////////////////////////////////////////////////////

		int yu = img[q].cols*img[q].rows;
		//cout << yu << endl ;
		CvMLData data = CvMLData();
		int dat = data.read_csv("data.csv");
		data.set_response_idx(yu);

	

		const CvMat* i = data.get_values();
		const CvMat* l = data.get_responses();

		//cout << format(data.get_responses(), "numpy") << endl;
	

		//cout << endl << "starting training" << endl;
		//bool zaq = arg.train(i, l); // for bayes
		bool zaq = arg.train(i, CV_ROW_SAMPLE, l); // for trees
	

		remove("data.csv");
}

	cout << "training done" << endl;
	arg.save("trained.xml");
	cout << "model saved" << endl; 

	cout << endl << "noraj" << endl;

	return 0;
}
