#include "stdafx.h"
#include "Calcoordinate.h"
#include <math.h>

//Calcoordinate::Calcoordinate(void)
//{
//
//}

Calcoordinate::Calcoordinate(CRect MainRect1, CRect SmallRect1, CPoint MainPoint1, CPoint SmallPoint1)
{
	MainRect=MainRect1;
	SmallRect=SmallRect1;
	MainPoint=MainPoint1;
	SmallPoint=SmallPoint1;
}


//Calcoordinate::~Calcoordinate(void)
//{
//}


CPoint Calcoordinate::CalMainCoord(void)
{
	CPoint ChangePoint;
	ChangePoint.x=-1;
	ChangePoint.y=-1;
	if(MainRect.PtInRect(MainPoint)){
		if((MainPoint.x>=MainRect.left && MainPoint.x<=MainRect.right) && (MainPoint.y>=MainRect.top && MainPoint.y<=MainRect.bottom))
		{
			//  通过对point的处理，获得实际在picture控件中的点击位置（坐标），完成。


			MainPoint.x-=MainRect.left;
			MainPoint.y-=MainRect.top;

			int height= MainRect.bottom-MainRect.top;
			int width = MainRect.right-MainRect.left;
			if(MainPoint.x<=width  && MainPoint.y<=height)
				ChangePoint=MainPoint;
		}
	}
	return ChangePoint;
}



void Calcoordinate::CalAllCoord(void)
{

	double radio=((double)Mainlength)/((double)(Smalllength));

	allx =	MainPoint.x - (double)Mainlength/2 +  SmallPoint.x *radio;
	ally =	MainPoint.y - (double)Mainlength/2 +  SmallPoint.y *radio;
	InPoint.x = allx;
	InPoint.y = ally;

}


CPoint Calcoordinate::CalSmallCoord(void)
{
	CPoint ChangePoint;
	ChangePoint.x=-1;
	ChangePoint.y=-1;
	if(SmallRect.PtInRect(SmallPoint)){
		if((SmallPoint.x>=SmallRect.left && SmallPoint.x<=SmallRect.right) && (SmallPoint.y>=SmallRect.top && SmallPoint.y<=SmallRect.bottom))
		{
			//  通过对point的处理，获得实际在picture控件中的点击位置（坐标），完成。


			SmallPoint.x-=SmallRect.left;
			SmallPoint.y-=SmallRect.top;
			
			ChangePoint=SmallPoint;
		}
	}
	return ChangePoint;
}


CString Calcoordinate::PrintCoord(CPoint point)
{
	CString str1="(";
	CString str2;
	str2.Format(_T("%d"),point.x);

	CString str3=",";
	CString str4;
	str4.Format(_T("%d"),point.y);
	CString str5=")";
	CString str;
	str.Format(_T("%s %s %s %s %s"), str1, str2, str3, str4,str5);

	return str;
}


CString Calcoordinate::PrintCoord(void)
{

	CString str1="(";
	CString str2;
	str2.Format(_T("%.1f"),allx);

	CString str3=",";
	CString str4;
	str4.Format(_T("%.1f"),ally);
	CString str5=")";
	CString str;
	str.Format(_T("%s %s %s %s %s"), str1, str2, str3, str4,str5);

	return str;
}



void Calcoordinate::InputSmallPoint(CPoint spoint)
{
	SmallPoint=spoint;
}


void Calcoordinate::InputMainlength(int length)
{
	Mainlength = length;
}

void Calcoordinate::InputSmalllength(int length)
{
	Smalllength = length;
}



double Calcoordinate::ReadAllx()
{
	return allx;
}
double Calcoordinate::ReadAlly()
{
	return ally;
}