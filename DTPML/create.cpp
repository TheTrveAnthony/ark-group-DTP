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

	read_csv3(nom, img, lbl);
	//vector<Mat> im ;
	//cout << "enter loop" << endl;
	/*for (int i = 0; i < img.size(); i++){

		Mat iii = prepro(img[i], 180);
		im.push_back(iii);
		//cout << iii << endl ;
	} */

	//cout << format(img[0], "numpy") << endl ;
	//cout << img[0].cols << img[0].rows << endl;
	// let's create a new csv with what will be used for ML
	cout << endl <<endl ;
	ofstream csvv("data.csv"); 
	fill_csv(csvv, img, lbl);

	// ML part //////////////////////////////////////////////////////

	int yu = img[0].cols*img[0].rows;
	cout << yu << endl ;
	CvMLData data = CvMLData();
	int dat = data.read_csv("data.csv");
	data.set_response_idx(yu);

	

	const CvMat* i = data.get_values();
	const CvMat* l = data.get_responses();

	//cout << format(data.get_responses(), "numpy") << endl;
	
	//CvRTrees arg = CvRTrees();
	CvGBTrees arg = CvGBTrees();
	//CvNormalBayesClassifier arg = CvNormalBayesClassifier();

	cout << endl << "starting training" << endl;
	//bool zaq = arg.train(i, l); // for bayes
	bool zaq = arg.train(i, CV_ROW_SAMPLE, l); // for trees
	cout << "training done" << endl;
	arg.save("trained.xml");
	cout << "model saved" << endl; 


	remove("data.csv");

	cout << endl << "noraj" << endl;

	return 0;
}
