// DialogCal.cpp : 实现文件
//

#include "stdafx.h"
#include "GetPoint.h"
#include "DialogCal.h"
#include "afxdialogex.h"


// DialogCal 对话框

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






//Public传递参数

void  DialogCal::SetAllPoint(double Points[50][2], int number){
	memcpy(AllPoint,Points,sizeof(Points));
	numberAP = number;
	return;
}





// DialogCal 消息处理程序
