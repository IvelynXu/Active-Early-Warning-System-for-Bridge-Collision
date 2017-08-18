#pragma once

#include <stdio.h>
#include <cxcore.h>
#include <cv.h>
#include <highgui.h>
#include <cvaux.h>
#include <opencv2/calib3d/calib3d.hpp>
#include <iomanip>  
#include <fstream>

//���ڲ�ͬ�Ĵ�����Ҫ�ı䣺
//ChessBoardSize_w��ChessBoardSize_h��NImages


class CalMatrix
{
private:


	

	/*�����ڲα���*/

	//�Ƿ�����ڲ�
	bool Provided;

	//��������
	int image_width;
	int image_height;//���궨ͼƬ�Ĵ�С
	
	static const int ChessBoardSize_w = 4;
	static const int ChessBoardSize_h = 4;//ͼƬ�пɱ궨�Ľ���

	CvSize  ChessBoardSize ;

	static const int NPoints = ChessBoardSize_w*ChessBoardSize_h;//�ǵ����

	static const int NImages = 1;//���궨��ͼƬ��

	float    SquareWidth; //���̸��ӵı߳����������趨����Ӱ���ڲ���
	
	//�ڲλ���ͼ��
	IplImage     *NowImage[NImages];
	int numberImage;
	//��εȻ���ͼ��
	IplImage     *ForotherImage;


	//����ͼƬ��2ά����
	int corner_count[NImages];//ÿһ��ͼƬ�Ľǵ�����
	CvPoint2D32f corners[NPoints*NImages];//����ǵ�����//��InPointֱ�����
	
	
	/*ͼƬ��2ά��ȡ������ �ڲ� */
	double InPoint[NImages][NPoints][2];
	int numberIP;

	/*ͼƬ��2ά��ȡ������ ��� */
	double OutPoint[100][2];
	float TempObjectPoints[100*3];
	int numberOP;

	/*ͼƬ��2ά��ȡ������ 2άת3ά */
	double Point2Dto3D[2];
	double Point3D[3];

	//���ҽ�������OPencv���ͼ������Ż��õ�
	IplImage     *current_frame_rgb; 
	IplImage     *current_frame_gray;
	
	
	//��Ҫ����

	CvMat *intrinsics;/*������ڲ������� 3*3*/
	CvMat *distortion_coeff;/*�α��������*/


	CvMat *rotation_vectors;/*��ת����*/
	CvMat *translation_vectors;/*ƽ�ƾ���*/



	CvMat *object_points;/*���������꣬Ϊ3xN����Nx3�ľ������N����ͼ�е��������е����Ŀ*/

	CvMat *point_counts;
	CvMat *image_points;/*������飬�洢ͼ������ꡣ��СΪ2xN����Nx2�����N����ͼ�е����е����Ŀ��*/

	float intr[3][3] ;//���ڴ�ӡ���ڲ�
	float dist[4] ;
	float tranv[3] ;
	float rotv[3];

public:




	//��ʼ������
	CalMatrix(void);
	CalMatrix::CalMatrix(int i);
	int  SetImageWH(int Width,int Height);
	int SetImage(IplImage* ipl);
	int SetForotherImage(IplImage* ipl);

	//��������
	IplImage * Undistort(IplImage * rightimage);

	//���ò���
	int SetInPoint(double x, double y);
	int SetOutPoint(double x, double y);
	int SetPoint2Dto3D(double x, double y);
	int SetOutObjectPoint(CString x,CString y,CString z);
	int SetProvided(bool f);

	
	//�жϲ����Ƿ񱣴�
	int IfInMatrixNull();
	int IfDistMatrixNull();
	int IfOutMatrixNull();

	//�����ڲ����
	int CalInMatrix(bool flag,bool ifnew);
	int CalOutMatrix();
	int Cal2Dto3D();//2dת3d

	//�����ڲ����躯��
	int PreCalInMatrix(int i,bool flag);
	void InitCorners3D(CvMat *Corners3D, CvSize ChessBoardSize, int Nimages, float SquareSize);
	
	//����������躯��
	int  PreCalOutMatrix();


	
	//�������
	CString PrintInMatrix();
	CString PrintDisMatrix();
	CString PrintRotMatrix();
	CString PrintTraMatrix();
	CString PrintPoint3D();
	int PrintNImages();
	int PrintnumberImage();


	//�������
	int SaveInMatrix();
	int SaveDistMatrix();
	int SaveOutMatrix();


	~CalMatrix(void);
};

