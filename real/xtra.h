#ifndef PLUS_H_INCLUDED
#define PLUS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


using namespace cv;

int filtre_h(Mat img);
Mat kuwahara(Mat img);
Mat graymin(Mat img);
int moyenne(Vec4b tab);	// computes the mean of an array
int e_type(Vec4b tab);	// computes the standart deviation of an array
string to_string(int i);
	





#endif