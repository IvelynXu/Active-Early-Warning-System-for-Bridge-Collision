// DialogCal.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GetPoint.h"
#include "DialogCal.h"
#include "afxdialogex.h"


// DialogCal �Ի���

IMPLEMENT_DYNAMIC(DialogCal, CDialogEx)

DialogCal::DialogCal(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogCal::IDD, pParent)
{

}

DialogCal::~DialogCal()
{
}

void DialogCal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogCal, CDialogEx)
END_MESSAGE_MAP()






//Public���ݲ���

void  DialogCal::SetAllPoint(double Points[50][2], int number){
	memcpy(AllPoint,Points,sizeof(Points));
	numberAP = number;
	return;
}





// DialogCal ��Ϣ�������
