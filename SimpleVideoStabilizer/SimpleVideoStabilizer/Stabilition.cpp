#include "Stabilition.h"




Stabilition::~Stabilition(void)
{
}

Stabilition::Stabilition():freshStart(true) 
{
	rigidTransform = Mat::eye(3,3,CV_32FC1); //affine 2x3 in a 3x3 matrix
}

void Stabilition::processImage(Mat& img) 
{
	Mat gray;
	Mat Cannygray;
	cvtColor(img,gray,CV_BGR2GRAY);
	
	vector<Point2f> corners;
	
	if(stabilitionFeatures.size() < 200) {
		
		//Canny(gray, Cannygray, 100, 100 * 3, 3); 
		
		



		goodFeaturesToTrack(gray,corners,300,0.01,10);
		//cout << "found " << corners.size() << " features\n";
		
		for (int i = 0; i < corners.size(); ++i) 
		{
			stabilitionFeatures.push_back(corners[i]);
		}
	}

	if(!prevGray.empty()) 
	{
		vector<uchar> status; 
		vector<float> errors;
		
		calcOpticalFlowPyrLK(prevGray,gray,stabilitionFeatures,corners,status,errors,Size(10,10));

		if(countNonZero(status) < status.size() * 0.8) 
		{
			//cout << "cataclysmic error \n";
			
			rigidTransform = Mat::eye(3,3,CV_32FC1);
			stabilitionFeatures.clear();
			prevGray.release();
			freshStart = true;
			return;
		} 
		else
			freshStart = false;
		
		Mat_<float> newRigidTransform = estimateRigidTransform(stabilitionFeatures,corners,false);
		
		Mat_<float> nrt33 = Mat_<float>::eye(3,3);
		newRigidTransform.copyTo(nrt33.rowRange(0,2));
		
		rigidTransform *= nrt33;

		stabilitionFeatures.clear();
		
		for (int i = 0; i < status.size(); ++i) 
		{
			if(status[i]) 
			{
				stabilitionFeatures.push_back(corners[i]);
			}
		}
	}

	for (int i = 0; i < stabilitionFeatures.size(); ++i) 
	{
		circle(img,stabilitionFeatures[i],3,Scalar(0,0,255),CV_FILLED);
	}

	gray.copyTo(prevGray);

}