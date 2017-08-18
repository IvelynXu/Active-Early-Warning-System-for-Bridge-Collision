
// GetPointDlg.h : 头文件
//

#include "Calcoordinate.h"
#include "cv.h"
#include "highgui.h"
#include "atlimage.h"
//#include "DialogCal.h"
#include "CalMatrix.h"

#pragma once


// CGetPointDlg 对话框
class CGetPointDlg : public CDialogEx
{
// 构造
public:

	CRect m_rect;

	CGetPointDlg(CWnd* pParent = NULL);	// 标准构造函数
	void mouseClick( IplImage* src,int event, int x, int y, int flags, void* ustc)  ;
	

// 对话框数据
	enum { IDD = IDD_GETPOINT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void ShowImage( IplImage* img, UINT ID );	// ID 是Picture Control控件的ID号
    IplImage* ResizeImage(IplImage* img,CvSize ImgSize);
	//BOOL PreTranslateMessage(MSG* pMsg);
	//void OnLButtonDown(POINT point);

public:


	afx_msg void OnBnClickedOpenpic();
	afx_msg void OnBnClickedFindmatrix();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtoncalculate();




public:
	//打开的image图像
	IplImage* ipl;

	//标志是否摁下选择位置的按钮
	bool tag,tag2;

	//计算坐标
	Calcoordinate *cood;
	//计算标定
	CalMatrix *calm ;

	//用于计算是否完成内参所需图像
	int imagenumber;
	int allnumber;

	CString Edit_ObX;
	CString Edit_ObY;
	CString Edit_ObZ;
	CString Edit_ObXR;
	CString Edit_ObYR;
	CString Edit_ObZR;

	afx_msg void OnBnClickedButtoncalculateout();
	afx_msg void OnBnClickedButoutcon();
	afx_msg void OnBnClickedButton2d();
};
