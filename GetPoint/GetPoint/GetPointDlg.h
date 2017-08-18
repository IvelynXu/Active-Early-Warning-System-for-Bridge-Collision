
// GetPointDlg.h : ͷ�ļ�
//

#include "Calcoordinate.h"
#include "cv.h"
#include "highgui.h"
#include "atlimage.h"
//#include "DialogCal.h"
#include "CalMatrix.h"

#pragma once


// CGetPointDlg �Ի���
class CGetPointDlg : public CDialogEx
{
// ����
public:

	CRect m_rect;

	CGetPointDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void mouseClick( IplImage* src,int event, int x, int y, int flags, void* ustc)  ;
	

// �Ի�������
	enum { IDD = IDD_GETPOINT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void ShowImage( IplImage* img, UINT ID );	// ID ��Picture Control�ؼ���ID��
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
	//�򿪵�imageͼ��
	IplImage* ipl;

	//��־�Ƿ�����ѡ��λ�õİ�ť
	bool tag,tag2;

	//��������
	Calcoordinate *cood;
	//����궨
	CalMatrix *calm ;

	//���ڼ����Ƿ�����ڲ�����ͼ��
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
