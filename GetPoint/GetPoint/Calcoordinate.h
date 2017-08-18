#pragma once


//确定坐标情况
//提供两个长方形

class Calcoordinate
{

private:
	CRect MainRect;
	CRect SmallRect;
	CPoint MainPoint;
	CPoint SmallPoint;

	CPoint InPoint;

	int Mainlength;
	int Smalllength;

	double allx;
	double ally;
public:
	//Calcoordinate(void);
	//~Calcoordinate(void);
	CPoint CalMainCoord(void);
	CPoint CalSmallCoord(void);
	void CalAllCoord(void);
	CString PrintCoord(CPoint point);
	CString Calcoordinate::PrintCoord(void);

	Calcoordinate(CRect MainRect1, CRect SmallRect1, CPoint MainPoint1, CPoint SmallPoint1);
	void InputSmallPoint(CPoint spoint);

	void InputMainlength(int length);
	void InputSmalllength(int length);

	double ReadAllx();
	double ReadAlly();
	
};

