#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>
#include <stdio.h>

#pragma once


using namespace cv;
using namespace std;

class Stabilition
{
	vector<Point2f> stabilitionFeatures;
    Mat             prevGray;
public:
    bool            freshStart;
    Mat_<float>     rigidTransform;

	Stabilition(void);
	~Stabilition(void);
	void processImage(Mat& img);
	
};

