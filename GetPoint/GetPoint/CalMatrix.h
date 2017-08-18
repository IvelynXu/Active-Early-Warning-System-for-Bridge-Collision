#pragma once

#include <stdio.h>
#include <cxcore.h>
#include <cv.h>
#include <highgui.h>
#include <cvaux.h>
#include <opencv2/calib3d/calib3d.hpp>
#include <iomanip>  
#include <fstream>

//对于不同的代码需要改变：
//ChessBoardSize_w、ChessBoardSize_h、NImages


class CalMatrix
{
private:


	

	/*计算内参变量*/

	//是否计算内参
	bool Provided;

	//基本参数
	int image_width;
	int image_height;//待标定图片的大小
	
	static const int ChessBoardSize_w = 4;
	static const int ChessBoardSize_h = 4;//图片中可标定的角数

	CvSize  ChessBoardSize ;

	static const int NPoints = ChessBoardSize_w*ChessBoardSize_h;//角点个数

	static const int NImages = 1;//待标定的图片数

	float    SquareWidth; //棋盘格子的边长，可任意设定，不影响内参数
	
	//内参基本图像
	IplImage     *NowImage[NImages];
	int numberImage;
	//外参等基本图像
	IplImage     *ForotherImage;


	//设置图片的2维坐标
	int corner_count[NImages];//每一张图片的角点总数
	CvPoint2D32f corners[NPoints*NImages];//保存角点坐标//与InPoint直接相关
	
	
	/*图片上2维获取的坐标 内参 */
	double InPoint[NImages][NPoints][2];
	int numberIP;

	/*图片上2维获取的坐标 外参 */
	double OutPoint[100][2];
	float TempObjectPoints[100*3];
	int numberOP;

	/*图片上2维获取的坐标 2维转3维 */
	double Point2Dto3D[2];
	double Point3D[3];

	//当且仅当利用OPencv获得图像坐标才会用到
	IplImage     *current_frame_rgb; 
	IplImage     *current_frame_gray;
	
	
	//重要参数

	CvMat *intrinsics;/*摄像机内参数矩阵 3*3*/
	CvMat *distortion_coeff;/*形变参数向量*/


	CvMat *rotation_vectors;/*旋转矩阵*/
	CvMat *translation_vectors;/*平移矩阵*/



	CvMat *object_points;/*物体点的坐标，为3xN或者Nx3的矩阵，这儿N是视图中的所有所有点的数目*/

	CvMat *point_counts;
	CvMat *image_points;/*输出数组，存储图像点坐标。大小为2xN或者Nx2，这儿N是视图中的所有点的数目。*/

	float intr[3][3] ;//用于打印的内参
	float dist[4] ;
	float tranv[3] ;
	float rotv[3];

public:




	//初始化设置
	CalMatrix(void);
	CalMatrix::CalMatrix(int i);
	int  SetImageWH(int Width,int Height);
	int SetImage(IplImage* ipl);
	int SetForotherImage(IplImage* ipl);

	//矫正变形
	IplImage * Undistort(IplImage * rightimage);

	//设置参数
	int SetInPoint(double x, double y);
	int SetOutPoint(double x, double y);
	int SetPoint2Dto3D(double x, double y);
	int SetOutObjectPoint(CString x,CString y,CString z);
	int SetProvided(bool f);

	
	//判断参数是否保存
	int IfInMatrixNull();
	int IfDistMatrixNull();
	int IfOutMatrixNull();

	//计算内参外参
	int CalInMatrix(bool flag,bool ifnew);
	int CalOutMatrix();
	int Cal2Dto3D();//2d转3d

	//计算内参所需函数
	int PreCalInMatrix(int i,bool flag);
	void InitCorners3D(CvMat *Corners3D, CvSize ChessBoardSize, int Nimages, float SquareSize);
	
	//计算外参所需函数
	int  PreCalOutMatrix();


	
	//输出参数
	CString PrintInMatrix();
	CString PrintDisMatrix();
	CString PrintRotMatrix();
	CString PrintTraMatrix();
	CString PrintPoint3D();
	int PrintNImages();
	int PrintnumberImage();


	//保存参数
	int SaveInMatrix();
	int SaveDistMatrix();
	int SaveOutMatrix();


	~CalMatrix(void);
};

