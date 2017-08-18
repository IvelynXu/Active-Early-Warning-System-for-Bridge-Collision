#include "stdafx.h"
#include "CalMatrix.h"

/*初始化*/
CalMatrix::CalMatrix(int i)
{

	numberIP=0;
	numberOP=0;
	numberImage=0;
	Provided=false;

	ChessBoardSize = cvSize(ChessBoardSize_w,ChessBoardSize_h);


	


	intrinsics = cvCreateMat(3,3,CV_32FC1);
	distortion_coeff = cvCreateMat(1,4,CV_32FC1);
	rotation_vectors = cvCreateMat(NImages,3,CV_32FC1);
	translation_vectors = cvCreateMat(NImages,3,CV_32FC1);
	point_counts = cvCreateMat(NImages,1,CV_32SC1);
	object_points = cvCreateMat(NImages*NPoints,3,CV_32FC1);
	image_points = cvCreateMat(NImages*NPoints,2,CV_32FC1);
	
	memset(intr, 0.0, sizeof(intr));
	memset(intr, 0.0, sizeof(dist));
	memset(intr, 0.0, sizeof(tranv));
	memset(intr, 0.0, sizeof(rotv));


	memset(corner_count, 0, sizeof(corner_count));//将corner_count元素全置为0
	SquareWidth = 10; //棋盘格子的边长，可任意设定，不影响内参数

}

int  CalMatrix::SetImageWH(int Width,int Height)
{
	image_width =Width;
	image_height = Height;//待标定图片的大小
	return 1;
}

int CalMatrix::SetImage(IplImage* ipl)
{
	NowImage[numberImage] =cvCreateImage(cvSize(image_width, image_height), IPL_DEPTH_8U, 3);
	cvCopy(ipl,NowImage[numberImage]);
	//NowImage[numberImage]=ipl;
	numberImage++;
	numberIP=0;
	return 1;
}

int CalMatrix::SetForotherImage(IplImage* ipl)
{
	ForotherImage =cvCreateImage(cvSize(image_width, image_height), IPL_DEPTH_8U, 3);
	cvCopy(ipl,ForotherImage);

	return 1;
}

int CalMatrix::SetProvided(bool f)
{
	Provided=f;
	return 1;
}













/*校正图像因相机镜头引起的变形*/
IplImage * CalMatrix::Undistort(IplImage * rightimage)
{
	IplImage     *ResultImage = cvCreateImage(cvSize(image_width, image_height), IPL_DEPTH_8U, 3);
	IplImage     *Image = cvCreateImage(cvSize(image_width, image_height), IPL_DEPTH_8U, 3);
	cvCopy(NowImage[numberImage-1],Image);
	cvUndistort2( Image, ResultImage, intrinsics, distortion_coeff);  
	return ResultImage;
}















/*将图片二维坐标传递*/
int CalMatrix::SetInPoint(double x, double y)
{
	InPoint[numberImage-1][numberIP][0]=x;
	InPoint[numberImage-1][numberIP][1]=y;
	numberIP++;
	return 0;
}
int CalMatrix::SetOutPoint(double x, double y)
{
	OutPoint[numberOP][0]=x;
	OutPoint[numberOP][1]=y;
	
	return 0;
}
int CalMatrix::SetOutObjectPoint(CString x,CString y,CString z)
{
	TempObjectPoints[numberOP*3+0]= _ttol(x);
	TempObjectPoints[numberOP*3+1]= _ttol(y);
	TempObjectPoints[numberOP*3+2]= _ttol(z);
	numberOP++;
	return 0;
}
int CalMatrix::SetPoint2Dto3D(double x, double y)
{
	Point2Dto3D[0]=x;
	Point2Dto3D[1]=y;
	return 1;
}












//判断内参是否为空
int CalMatrix::IfInMatrixNull()
{
	FILE *infile = fopen("D:\\WorkSpace\\WorkSpaceVS\\NewWarningSystem\\intr.txt", "rb");
	if(infile == NULL)
		return 0;
	memset(intr,0,sizeof(intr));
    fread(intr, sizeof(intr), 9, infile);
	fclose(infile);//把文件写入后要关闭文件句柄


	

	if(intr[0][0] == 0)
		return 0;
	
	else
	{
		CvMat *Temp=cvCreateMat(3,3,CV_32FC1);
		for ( int i = 0; i < 3; i++)
		{
			for ( int j = 0; j < 3; j++)
			{
				cvmSet(Temp,i,j,double(intr[i][j]));
				// ((float*)(intrinsics->data.ptr + intrinsics->step*i))[j] =intr[i][j];
			}

		}

		intrinsics=cvCloneMat(Temp);
		cvReleaseMat(&Temp);
		return 1;
	}
	
}
//判断形变参数
int CalMatrix::IfDistMatrixNull()
{
	FILE *infile = fopen("D:\\WorkSpace\\WorkSpaceVS\\NewWarningSystem\\dist.txt", "rb");
	if(infile == NULL)
		return 0;
	memset(dist,0,sizeof(dist));
    fread(dist, sizeof(dist), 9, infile);
	fclose(infile);//把文件写入后要关闭文件句柄
	if(dist[0] == 0)
		return 0;
	else
	{
		for ( int i = 0; i < 4; i++)
		{
			cvmSet(distortion_coeff,0,i,double(dist[i] ));
			//(distortion_coeff->data.ptr)[i] =dist[i] ;
			//tranv[i] = ((float*)(translation_vectors->data.ptr))[i];
			//rotv[i] = ((float*)(rotation_vectors->data.ptr))[i];
		}
		return 1;
	}
	
}
//判断外部参数
int CalMatrix::IfOutMatrixNull()
{
	FILE *infile = fopen("D:\\WorkSpace\\WorkSpaceVS\\NewWarningSystem\\tranv.txt", "rb");
	if(infile == NULL)
		return 0;
	memset(tranv,0,sizeof(tranv));
    fread(tranv, sizeof(tranv), 9, infile);
	
	fclose(infile);//把文件写入后要关闭文件句柄


	FILE *infile2 = fopen("D:\\WorkSpace\\WorkSpaceVS\\NewWarningSystem\\rotv.txt", "rb");
	if(infile2 == NULL)
		return 0;
	memset(rotv,0,sizeof(rotv));
    fread(rotv, sizeof(rotv), 9, infile2);
	fclose(infile2);//把文件写入后要关闭文件句柄


	if(tranv[0] == 0 || rotv[0]==0)//可能有误
		return 0;
	else
	{
		for ( int i = 0; i < 3; i++)
		{
			(translation_vectors->data.ptr)[i] =tranv[i] ;
			//tranv[i] = ((float*)(translation_vectors->data.ptr))[i];
			//rotv[i] = ((float*)(rotation_vectors->data.ptr))[i];
		}
		return 1;
	}
	
}














/*计算内参*/
int CalMatrix::CalInMatrix(bool flag,bool ifnew)
{
	if(ifnew == false){
		for(int i=0 ; i<NImages;i++)
		{
			PreCalInMatrix(i,flag);
		}
	}
	else
	{

	}
	//把2维点转化成三维点（object_points输出量）

	InitCorners3D(object_points, ChessBoardSize, NImages, SquareWidth);
	cvSetData( image_points, corners, sizeof(CvPoint2D32f));
	cvSetData( point_counts, &corner_count, sizeof(int));


	cvCalibrateCamera2( object_points,image_points,point_counts,cvSize(image_width,image_height),intrinsics,distortion_coeff,rotation_vectors,translation_vectors,0);
	

	
	for ( int i = 0; i < 3; i++)
	{
		for ( int j = 0; j < 3; j++)
		{
			intr[i][j] = ((float*)(intrinsics->data.ptr + intrinsics->step*i))[j];
		}
		dist[i] = ((float*)(distortion_coeff->data.ptr))[i];
		//tranv[i] = ((float*)(translation_vectors->data.ptr))[i];
		//rotv[i] = ((float*)(rotation_vectors->data.ptr))[i];
	}
    
	dist[3] = ((float*)(distortion_coeff->data.ptr))[3];
	
	


	//为外参做准备
	cvReleaseMat(&object_points);
	cvReleaseMat(&image_points);
	cvReleaseMat(&rotation_vectors);
	cvReleaseMat(&translation_vectors);   

	Provided=true;
	return 1;
}

//内参数据准备
int  CalMatrix::PreCalInMatrix(int i,bool flag)
{
	if(flag==true)
	{
		IplImage *Image;
		Image =cvCreateImage(cvSize(image_width, image_height), IPL_DEPTH_8U, 3);
		current_frame_gray = cvCreateImage(cvSize(image_width, image_height), IPL_DEPTH_8U, 1);
		current_frame_rgb = cvCreateImage(cvSize(image_width, image_height), IPL_DEPTH_8U, 3);
		//Image=NowImage[i];
		cvCopy(NowImage[i],Image);


		//利用函数获得2维参数
		cvCvtColor(Image, current_frame_gray, CV_BGR2GRAY);
        cvCopy(Image,current_frame_rgb);
		
		int find_corners_result;
		//寻找棋盘图的内角点位置
		find_corners_result = cvFindChessboardCorners(current_frame_gray, ChessBoardSize,&corners[i*NPoints],&corner_count[i],CV_CALIB_CB_ADAPTIVE_THRESH );
		//检测出来的角点的基础上，能够将角点位置精确到亚像素级精度
		cvFindCornerSubPix( current_frame_gray, &corners[i*NPoints],NPoints, cvSize(11,11),cvSize(-1,-1),cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.01) );
		//标定摄像机时绘制被成功标定的角点
		cvDrawChessboardCorners(current_frame_rgb, ChessBoardSize, &corners[i*NPoints], NPoints, find_corners_result);


		char fulfilename[80];
		strcpy(fulfilename,"D:\\WorkSpace\\WorkSpaceVS\\GetPoint\\Image\\An");
		char endname[] = "00.bmp";
		endname[1]=(char)(i+49);
		strcat(fulfilename,endname);
		cvSaveImage(fulfilename,current_frame_rgb);


	}
	else
	{
		//直接选择获得参数
		corner_count[i] = NPoints;
		for(int j=0;j<NPoints;j++)
		{
			corners[i*NPoints+j].x = InPoint[i][j][0];
			corners[i*NPoints+j].y = InPoint[i][j][1];
		}
	}
	return 1;
}

void CalMatrix::InitCorners3D(CvMat *Corners3D, CvSize ChessBoardSize, int NImages, float SquareSize)
{
	int CurrentImage = 0;
	int CurrentRow = 0;
	int CurrentColumn = 0;
	int NPoints = ChessBoardSize.height*ChessBoardSize.width;
	float * temppoints = new float[NImages*NPoints*3];
	

	for (CurrentImage = 0 ; CurrentImage < NImages ; CurrentImage++)
	{
		for (CurrentRow = 0; CurrentRow < ChessBoardSize.height; CurrentRow++)
		{
			for (CurrentColumn = 0; CurrentColumn < ChessBoardSize.width; CurrentColumn++)
			{
				temppoints[(CurrentImage*NPoints*3)+(CurrentRow*ChessBoardSize.width + 
					CurrentColumn)*3]=(float)CurrentRow*SquareSize;
				temppoints[(CurrentImage*NPoints*3)+(CurrentRow*ChessBoardSize.width + 
					CurrentColumn)*3+1]=(float)CurrentColumn*SquareSize;
				temppoints[(CurrentImage*NPoints*3)+(CurrentRow*ChessBoardSize.width + 
					CurrentColumn)*3+2]=0.f;
			}
		}
	}
	(*Corners3D) = cvMat(NImages*NPoints,3,CV_32FC1, temppoints);
}














/*计算外参*/

int CalMatrix::CalOutMatrix()
{
	
	if(Provided ==true)//判断是否获取了内参
	{
		object_points = cvCreateMat(numberOP,3,CV_32FC1);
		image_points = cvCreateMat(numberOP,2,CV_32FC1);
		rotation_vectors = cvCreateMat(NImages,3,CV_32FC1);
		translation_vectors = cvCreateMat(NImages,3,CV_32FC1);
		
		PreCalOutMatrix();

		float a[3][3];
		float b[4];
			for ( int i = 0; i < 3; i++)
			{
				for ( int j = 0; j < 3; j++)
				{
					a[i][j] = ((float*)(intrinsics->data.ptr + intrinsics->step*i))[j];
				}
				b[i] = ((float*)(distortion_coeff->data.ptr))[i];
				//tranv[i] = ((float*)(translation_vectors->data.ptr))[i];
				//rotv[i] = ((float*)(rotation_vectors->data.ptr))[i];
			}
			b[3] = ((float*)(distortion_coeff->data.ptr))[3];



		cvFindExtrinsicCameraParams2(object_points, image_points,intrinsics, distortion_coeff,  rotation_vectors, translation_vectors );

		for ( int i = 0; i < 3; i++)
		{
			tranv[i] = ((float*)(translation_vectors->data.ptr))[i];
			rotv[i] = ((float*)(rotation_vectors->data.ptr))[i];
		}
		return 1;
	}
	else{
		return -1;
	}
	
}

int  CalMatrix::PreCalOutMatrix()
{
	//直接选择获得参数

	CvPoint2D32f *now = new  CvPoint2D32f[numberOP];
	for(int j=0;j<numberOP;j++)
	{
		now[j].x = OutPoint[j][0];
		now[j].y = OutPoint[j][1];
	}

	cvSetData( image_points, now, sizeof(CvPoint2D32f));
	(*object_points) = cvMat(numberOP,3,CV_32FC1, TempObjectPoints);

	return 1;
}












/*计算2D转3D*/

int CalMatrix::Cal2Dto3D()
{
	CvMat *Temp1= cvCreateMat(3,3,CV_32FC1);
	CvMat *ResultMatrix=cvCreateMat(3,3,CV_32FC1);
	for(int i=0;i<3;i++)
	{
		cvmSet( Temp1, i, 0, rotv[0] );
		cvmSet( Temp1, i, 1, rotv[1] );
		cvmSet( Temp1, i, 2, tranv[i] );
	}
	//cvCrossProduct(intrinsics,Temp1,ResultMatrix);
	cvMul(intrinsics,Temp1,ResultMatrix,1);
	CvMat *ResultMatrixinv=cvCreateMat(3,3,CV_32FC1);
	cvInvert(ResultMatrix,ResultMatrixinv,CV_LU);


	double Tempd[9];
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			Tempd[i*3+j]=cvmGet(ResultMatrixinv,i,j);
		}
	}




	double xe,ye;
	xe = Point2Dto3D[0];
	ye = Point2Dto3D[1];

	Point3D[0] = (Tempd[0]*xe + Tempd[1]*ye + Tempd[2]) / (Tempd[6]*xe + Tempd[7]*ye + Tempd[8]);//世界坐标中x值
	
	Point3D[1] = (Tempd[3]*xe + Tempd[4]*ye + Tempd[5]) / (Tempd[6]*xe + Tempd[7]*ye + Tempd[8]);//世界坐标中Y值


	Point3D[2] =0;


	return 1;
}












/*输出内参*/
CString CalMatrix::PrintInMatrix()
{
	CString La0="|";
	CString La1=",";
	CString strall=NULL;
	for(int i=0;i<=2;i++){
		
		CString str1;
		str1.Format(_T("%.1f"),intr[i][0]);

		
		CString str2;
		str2.Format(_T("%.1f"),intr[i][1]);


		CString str3;
		str3.Format(_T("%.1f"),intr[i][2]);


		CString strpart;
		strpart.Format(_T("%s %s %s %s %s %s %s"), La0,str1,La1, str2, La1,str3,La0);

		if(i==0)
		{
			strall=strpart;
		}
		else{
			CString strcon;
			strcon.Format(_T("%s %s "), strall,strpart);
			strall=strcon;
		}
	}
	return strall;
}

//输出形变系数
CString CalMatrix::PrintDisMatrix()
{
	CString La0="|";
	CString La1=",";
	CString strall=NULL;
	
	CString str1;
	str1.Format(_T("%.1f"),dist[0]);

	CString str2;
	str2.Format(_T("%.1f"),dist[1]);
	
	CString str3;
	str3.Format(_T("%.1f"),dist[2]);

	CString str4;
	str4.Format(_T("%.1f"),dist[3]);

	
	strall.Format(_T("%s %s %s %s %s %s %s %s %s"), La0,str1,La1, str2, La1,str3, La1,str4,La0);


	return strall;
}

//输出平移系数
CString CalMatrix::PrintTraMatrix()
{
	CString La0="|";
	CString La1=",";
	CString strall=NULL;
	
	CString str1;
	str1.Format(_T("%.1f"),tranv[0]);

	CString str2;
	str2.Format(_T("%.1f"),tranv[1]);
	
	CString str3;
	str3.Format(_T("%.1f"),tranv[2]);



	
	strall.Format(_T("%s %s %s %s %s %s %s "), La0,str1,La1, str2, La1,str3, La0);


	return strall;
}

//输出旋转系数
CString CalMatrix::PrintRotMatrix()
{
	CString La0="|";
	CString La1=",";
	CString strall=NULL;
	
	CString str1;
	str1.Format(_T("%.1f"),rotv[0]);

	CString str2;
	str2.Format(_T("%.1f"),rotv[1]);
	
	CString str3;
	str3.Format(_T("%.1f"),rotv[2]);
	
	strall.Format(_T("%s %s %s %s %s %s %s"), La0,str1,La1, str2, La1,str3, La0);


	return strall;
}

//输出Point3D
CString CalMatrix::PrintPoint3D()
{
	CString La0="|";
	CString La1=",";
	CString strall=NULL;
	
	CString str1;
	str1.Format(_T("%.1f"),Point3D[0]);

	CString str2;
	str2.Format(_T("%.1f"),Point3D[1]);
	
	CString str3;
	str3.Format(_T("%.1f"),Point3D[2]);



	
	strall.Format(_T("%s %s %s %s %s %s %s"), La0,str1,La1, str2, La1,str3, La0);


	return strall;

}

//输出NImages
int CalMatrix::PrintNImages()
{
	return NImages;
}

//输出numberImage
int CalMatrix::PrintnumberImage()
{
	return numberImage;
}









/*保存内参*/
int CalMatrix::SaveInMatrix()
{
	FILE *fp;//定义一个文件指针
	fp=fopen("D:\\WorkSpace\\WorkSpaceVS\\NewWarningSystem\\intr.txt","wb");//打开文件成功,反回文件句柄,否刚反回NULL,这个文件可以不存在,将会自动创建
	
	//for(int i=0;i<=2;i++)
	//	for(int j=0;j<=2;j++)
	//		fprintf(fp, "%f", intr[i][j]);
	fwrite(intr,sizeof(intr),9,fp);//把数组写入到文件里面
	fclose(fp);//把文件写入后要关闭文件句柄
	return 1;
}
int CalMatrix::SaveDistMatrix()
{
	FILE *fp;//定义一个文件指针
	fp=fopen("D:\\WorkSpace\\WorkSpaceVS\\NewWarningSystem\\dist.txt","wb");//打开文件成功,反回文件句柄,否刚反回NULL,这个文件可以不存在,将会自动创建
	fwrite(dist,sizeof(dist),9,fp);//把数组写入到文件里面
	fclose(fp);//把文件写入后要关闭文件句柄
	return 1;
}

int CalMatrix::SaveOutMatrix()
{
	FILE *fp;//定义一个文件指针
	fp=fopen("D:\\WorkSpace\\WorkSpaceVS\\NewWarningSystem\\tranv.txt","wb");//打开文件成功,反回文件句柄,否刚反回NULL,这个文件可以不存在,将会自动创建
	fwrite(tranv,sizeof(tranv),9,fp);//把数组写入到文件里面

	fp=fopen("D:\\WorkSpace\\WorkSpaceVS\\NewWarningSystem\\rotv.txt","wb");//打开文件成功,反回文件句柄,否刚反回NULL,这个文件可以不存在,将会自动创建
	fwrite(rotv,sizeof(rotv),9,fp);//把数组写入到文件里面

	fclose(fp);//把文件写入后要关闭文件句柄


	return 1;
}
















CalMatrix::~CalMatrix(void)
{
	cvReleaseMat(&intrinsics);       
	cvReleaseMat(&distortion_coeff); 
	cvReleaseMat(&rotation_vectors);
	cvReleaseMat(&translation_vectors);   
	cvReleaseMat(&point_counts);
	cvReleaseMat(&object_points);
	cvReleaseMat(&image_points);
}
