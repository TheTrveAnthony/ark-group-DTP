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


/*
void read_csv2(const string& filename, vector<Mat>& images, vector<int>& labels) {
    std::ifstream file(filename.c_str(), ifstream::in);
    Size s(30, 30);
	 int x;
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, ';');
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
		      	x = filtre_h(images[images.size()-1]);
            threshold(images[images.size()-1], images[images.size()-1], x, 1, THRESH_BINARY);
            images[images.size()-1].convertTo(images[images.size()-1], CV_32F);
            resize(images[images.size()-1], images[images.size()-1], s);
            images[images.size()-1].reshape(1, SZ);
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}
*/


void read_csv3(const string& filename, vector<Mat>& images, vector<int>& labels) {

  /* same as read_csv2 but includes the regions of interest */ 
    cout << "loading images..." ;
    std::ifstream file(filename.c_str(), ifstream::in);
   int x;
   //Size s(150, 300);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, ';');
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            
            Mat i = imread(path, 0);

            //Mat i2 = Mat::zeros(1700, 524, CV_8UC1);
            //Mat i2 = zone(i, 0, 23, 1700, 524);
            Mat i2 = i(Rect(103, 0, 537, i.rows));

            //imshow("sdghd", i2);
            //waitKey(0);

            x = filtre_h(i2);
            
           // cout << x << endl ;

            while (x < 200) {x *= 2;}

            threshold(i2, i2, x, 1, THRESH_BINARY);

           // imshow("sdghd", i2*255);
           // waitKey(0);
           
           // Mat i3 = reduz(i2, 500);
            //cout << "chimi chimi yeah" << endl ;
            Size s(i2.cols/DIV, i2.rows/DIV);
            resize(i2, i2, s);

            //imshow("sdghd", i3*255);
            //waitKey(0);
           // cout << i3.rows*i3.cols << endl ;
            i2.reshape(1, i2.rows*i2.cols);
            images.push_back(i2);
          
           
            images[images.size()-1].convertTo(images[images.size()-1], CV_32F);
            //images[images.size()-1].reshape(1, images[images.size()-1].cols*images[images.size()-1].rows);
           
            labels.push_back(atoi(classlabel.c_str()));

            cout << "." ;
          
        }
    }
}


Mat prepro(Mat im, int x){

  int t = filtre_h(im);
  threshold(im, im, t, 1, THRESH_BINARY);

  Mat ip = reduz(im, x);
  //cout << "fsd" << endl ;
  im.reshape(1, im.rows*im.cols);
  //im.convertTo(im, CV_32F);
  //cout << ip.rows << endl ;
  return ip;


}



void fill_csv(ofstream& csv, const vector<Mat> img, const vector<int> lbl)  {

	if(csv) {		// let's fill this shit baby

		int n = img.size();
    int SZ;
		for(int i = 0 ; i < n ; i++) {
      SZ = img[i].rows*img[i].cols;
     // cout << SZ << endl ;
			for(int j = 0; j < SZ ; j++){
        //for(int k = 0; k < img[i].rows ; k++){ 
            if (img[i].at<int>(j) == 0) {csv << img[i].at<int>(j) << ",";}
            else {csv << 1 << ",";}   // it is the only way that works ........ else we get values like 26564216584
          //}

        }	
			   csv << lbl[i] << endl;	// then the label which tells wether there is an (or several) error or not	(1 = error, 0 = clean)
			   //cout << i << endl;

		  
    }
		cout << "csv filled" << endl ;
	 }
	else {cout << "fuck you" << endl;}

}




void fill_csv2(ofstream& csv, const Mat img, const int lbl)  {

  if(csv) {   // let's fill this shit baby

      int SZ = img.rows*img.cols;
      for(int j = 0; j < SZ ; j++){
        if (img.at<float>(j) == 0) {csv << img.at<float>(j) << ",";}
        else {csv << 1 << ",";}
        
        }
         // first the image pixel values
      
      csv << lbl << endl;  // then the label which tells wether there is an (or several) error or not  (1 = error, 0 = clean)
      //cout << "csv filled" << endl ;

    }
    //cout << "csv filled" << endl ;
  
    else {cout << "fuck you" << endl;}
}



int filtre_h(Mat img) {

       
   int histSize = 256;    // bin size
   float range[] = { 0, 255 };
   const float *ranges[] = { range };
 
    // Calculate histogram
   MatND hist;
   calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges);
    //cout << hist << endl << endl << endl;

    /*

     // Draw the histograms for B, G and R
     int hist_w = 512; int hist_h = 400;
   int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

    /// Normalize the result to [ 0, histImage.rows ]
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );


   /// Draw for each channel 
   for( int i = 1; i < histSize; i++ )
   {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );

   }

   /// Display
   namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
   imshow("calcHist Demo", histImage );

   waitKey(0);
    */





   int k(255), m(0);

   while(m < 3) {

           if( k == 255 && hist.at<float>(k) > hist.at<float>(k-1) && hist.at<float>(k-1) > hist.at<float>(k-2)) {m = 2;}

            


        if (m == 0 || m == 2){

            if( hist.at<float>(k) < hist.at<float>(k-1) && hist.at<float>(k-1) < hist.at<float>(k-2)) {m++;}        // going up
        }
                

        if (m == 1){

            if (hist.at<float>(k) > hist.at<float>(k-1) && hist.at<float>(k-1) >= hist.at<float>(k-2)) {m++;}        // going down

            }

        if (m == 2){

            if( hist.at<float>(k) < hist.at<float>(k-1) && hist.at<float>(k-1) <= hist.at<float>(k-2)) {m++;}        // going up
        }

        if (m != 3){k--;}

        



   }

	 return k;
}



Mat zone(const Mat img, int dx, int dy, int lx, int ly){

  /* Regions of interest, dx and dy are the coordinates of the top left pixel
    of the region we are interested in, lx and ly are its mensurations.

  */


  //img.convertTo(img, CV_32F);
  Mat imo = Mat::zeros(lx, ly, CV_8UC1);
  cout << "x" << endl ;
  for (int n = 0; n < lx ; n++) {
    for (int m = 0; m < ly; m++){


      imo.at<int>(n, m) = img.at<int>(n+dx, m+dy);

    }
   // cout << n << endl;
  }
    //cout << format(imo, "numpy") << endl ;
  return imo;
}





Mat reduz(Mat im, int x) {


  Mat i2;
  int y;

  for (int n = 0; n < im.rows ; n++) {
     // cout << "fsd" << endl ;
      y = sommec(im, n);
      //cout << y << endl;
      if (y < x) {i2.push_back(im.row(n));}

    }
  
  //cout << "dfghd" << endl ;
  return i2;
}


int sommec(const Mat i, int k) {

  /* returns the sum of the k -th row of a matrix */

  int s(0);
 // cout << "assassin" << endl;
  for (int n = 0; n < i.cols; n++ ){ 
    if  (i.at<int>(k, n) != 0) {s ++;}
    cout << ""  ;
  }

  return s;

}
    

