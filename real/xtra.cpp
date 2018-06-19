#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "xtra.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>

using namespace cv;
using namespace std;




int filtre_h(Mat img) {

	   
   int histSize = 256;    // bin size
   float range[] = { 0, 255 };
   const float *ranges[] = { range };
 
    // Calculate histogram
   MatND hist;
   calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges);
   // cout << hist << endl;

   int k(255), m(0);

   while(m < 3) {

   		if( k == 255 && hist.at<float>(k) > hist.at<float>(k-1) && hist.at<float>(k-1) > hist.at<float>(k-2)) {m = 2;}

			


		if (m == 0 || m == 2){

			if( hist.at<float>(k) < hist.at<float>(k-1) && hist.at<float>(k-1) < hist.at<float>(k-2)) {m++;}		// going up
		}
				

		if (m == 1){

			if (hist.at<float>(k) > hist.at<float>(k-1) && hist.at<float>(k-1) > hist.at<float>(k-2)) {m++;}		// going down

			}

		if (m != 3){k--;}

		



   }




	return k;
}



Mat kuwahara(Mat img) {

	int c = img.cols;
	int r = img.rows;
	img.convertTo(img, CV_64F);
	Mat kuwa = Mat::zeros(r, c, CV_64F);
	kuwa.row(0) += img.row(0);
	kuwa.col(0) += img.col(0);
	kuwa.row(r-1) += img.row(r-1);
	kuwa.col(c-1) += img.col(c-1);


	for(int i = 1; i < r-1; i++ ) {
		for(int j = 1; j < c-1; j++) {

			// Kuwahara areas

			
			Vec4b a0(img.at<double>(i, j), img.at<double>(i-1, j), img.at<double>(i, j-1), img.at<double>(i-1, j-1));
			Vec4b a1(img.at<double>(i, j), img.at<double>(i+1, j), img.at<double>(i, j-1), img.at<double>(i+1, j-1));
			Vec4b a2(img.at<double>(i, j), img.at<double>(i-1, j), img.at<double>(i, j+1), img.at<double>(i-1, j+1));
			Vec4b a3(img.at<double>(i, j), img.at<double>(i+1, j), img.at<double>(i, j+1), img.at<double>(i+1, j+1));
			
			// mean and standart deviation of each area

			vector<int> moy;
			vector<int> sdev;
			
			

			int m0 = moyenne(a0);
			int m1 = moyenne(a1);
			int m2 = moyenne(a2);
			int m3 = moyenne(a3);

			int d0 = e_type(a0);
			int d1 = e_type(a1);
			int d2 = e_type(a2);
			int d3 = e_type(a3);
			
			sdev.push_back(d0);
			sdev.push_back(d1);
			sdev.push_back(d2);
			sdev.push_back(d3);

			moy.push_back(m0);
			moy.push_back(m1);
			moy.push_back(m2);
			moy.push_back(m3);

			int mini = 0;

			for (int k = 1; k < 4; k++){

				if(sdev[k] < sdev[k - 1]){mini = k;}

			}

			kuwa.at<double>(i, j) = moy[mini];
			

		}
	}
	
	kuwa.convertTo(kuwa, CV_8UC1);
	return kuwa;
}



Mat graymin(Mat img) {



	int c = img.cols;
	int r = img.rows;
	Mat im2 = Mat::zeros(r, c, CV_64F);
	
	for (int i = 0; i <  r; i++) {//r
		
		for (int j = 0; j < c ; j++) {//c		
			Vec3d pix = img.at<Vec3b>(i, j);
			double a;
			if( pix(0) <= pix(1) && pix(0) <= pix(2)) { a = pix(0);}
			if( pix(1) <= pix(0) && pix(1) <= pix(2)) { a = pix(1);}
			if( pix(2) <= pix(1) && pix(0) >= pix(2)) { a = pix(2);}


			im2.at<double>(i, j) += a;
			//cout << "I(" << i << ", " << j << ") ="<< im2.at<int>(i, j) << endl;
		}

	}


	//cout << format(im2, "python") << endl;
	im2.convertTo(im2, CV_8UC1);
	return im2;

}





int moyenne(Vec4b tab){

	int a = (tab(0)+tab(1)+tab(2)+tab(3))/4;
	return a;

}

int e_type(Vec4b tab) {


	int s = 0;
	int m = moyenne(tab);
	for (int k = 0; k < 4; k++) {

		s += pow((tab(k)-m), 2);
	}

	s /= 4;
	s = sqrt(s);
	return s;



}


string to_string(int i) {
     std::ostringstream oss;
     oss << i;
     return oss.str();
}