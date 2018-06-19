#ifndef PLUS_H_INCLUDED
#define PLUS_H_INCLUDED


#define DIV 30


using namespace cv;
using namespace std;


void read_csv2(const string& filename, vector<Mat>& images, vector<int>& labels);
void read_csv3(const string& filename, vector<Mat>& images, vector<int>& labels);
Mat prepro(Mat im, int x);
void fill_csv(ofstream& csv, const vector<Mat> img, const vector<int> lbl);
void fill_csv2(ofstream& csv, const Mat img, const int lbl);
int filtre_h(Mat img);
Mat zone(const Mat img, int dx, int dy, int lx, int ly);
Mat reduz(Mat im, int x);
int sommec(const Mat i, int k);


#endif
