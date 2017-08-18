
// GetPointDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GetPoint.h"
#include "GetPointDlg.h"
#include "afxdialogex.h"
#include< afxwin.h>
# include <iostream>

#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif













// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()





// CGetPointDlg �Ի���

CGetPointDlg::CGetPointDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGetPointDlg::IDD, pParent)
	, Edit_ObX(_T(""))
	, Edit_ObY(_T(""))
	, Edit_ObZ(_T(""))
	, Edit_ObXR(_T(""))
	, Edit_ObYR(_T(""))
	, Edit_ObZR(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	//���캯�� ��Ӵ���

	
	ipl=NULL;
	
	tag = false;
	tag2 = false;
	
	calm= new CalMatrix(1);
	allnumber = calm->PrintNImages();

	imagenumber = 0;
}

void CGetPointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EditObX, Edit_ObXR);
	DDX_Text(pDX, IDC_EditObY, Edit_ObYR);
	DDX_Text(pDX, IDC_EditObZ, Edit_ObZR);
}

BEGIN_MESSAGE_MAP(CGetPointDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_OpenPic, &CGetPointDlg::OnBnClickedOpenpic)
	ON_BN_CLICKED(ID_FindMatrix, &CGetPointDlg::OnBnClickedFindmatrix)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTONCalculate, &CGetPointDlg::OnBnClickedButtoncalculate)
	ON_BN_CLICKED(IDC_BUTTONCalculateOut, &CGetPointDlg::OnBnClickedButtoncalculateout)
	ON_BN_CLICKED(IDC_ButOutCon, &CGetPointDlg::OnBnClickedButoutcon)
	ON_BN_CLICKED(IDC_BUTTON2D, &CGetPointDlg::OnBnClickedButton2d)
END_MESSAGE_MAP()


// CGetPointDlg ��Ϣ�������

BOOL CGetPointDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��ȡ�Ի��򴴽�ʱ�Ĵ�С
	GetClientRect(&m_rect);

	CButton *RadioButton1 = (CButton*)GetDlgItem(IDC_InRADIO);
	RadioButton1->SetCheck(TRUE);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CGetPointDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGetPointDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
						//  CBitmap bitmap;
				  //bitmap.LoadBitmap(IDC_PicShowS);
				  //BITMAP bit;
				  //bitmap.GetBitmap(&bit);
				  //CDC cdem;
				  //cdem.CreateCompatibleDC(pDC);
				  //cdem.SelectObject(&bitmap);
				  //pDC->StretchBlt(0,0,bit.bmWidth,bit.bmHeight,&cdem,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);

		CDialogEx::OnPaint();




	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGetPointDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}















/***************************/
/*  ����Dialog����ؼ���С*/
/**************************/

void CGetPointDlg::OnSize(UINT nType, int cx, int cy)
{


	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������


	//����Ĭ��Picture�Ĵ�С

  

	//CWnd *pWnd;
	//pWnd = GetDlgItem( IDC_PicShowS ); //��ȡ�ؼ�ָ�룬IDC_BUTTON1Ϊ�ؼ�ID��
	//pWnd->SetWindowPos( NULL,50,50,0,0,SWP_NOZORDER | SWP_NOSIZE ); //�Ѱ�ť�Ƶ����ڵ�(50,80)��
	//pWnd->SetWindowPos( NULL,0,0,300,300,SWP_NOZORDER | SWP_NOMOVE ); //�ѱ༭�ؼ��Ĵ�С��Ϊ(100,80)��λ�ò���
	////pWnd->MoveWindow( CRect(0,0,100,100) ); 




	//����Dialog�Ĺ�� �������е��ڲ��ؼ�һ�����
	//δ�������� �Բ�ȷ��

	//int  IDnumber = 4;
	//CString *IDname=(CString*) malloc (IDnumber);
	//IDname[0]="ID_OpenPic";

	// for (int i=0;i<1;i++)     //��Ϊ�������ؼ���������������ѭ��
	// {
	//	 CWnd *pWnd; 
	//	 pWnd = GetDlgItem(i);     //��ȡIDΪi�Ŀռ�ľ������Ϊ��ȷ�ϡ�IDΪ1����ȡ����IDΪ2
	//	 if(pWnd)  //�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ����
	//	 {
	//		 CRect rect;   //��ȡ�ؼ��仯ǰ�Ĵ�С  
	//		 pWnd->GetWindowRect(&rect);
	//		 ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
	//		 
	//		 //cx/m_rect.Width()Ϊ�Ի����ں���ı仯����
	//		 rect.left=rect.left*cx/m_rect.Width();//�����ؼ���С
	//		 rect.right=rect.right*cx/m_rect.Width();
	//		 rect.top=rect.top*cy/m_rect.Height();
	//		 rect.bottom=rect.bottom*cy/m_rect.Height();
	//		 
	//		 pWnd->MoveWindow(rect);//���ÿؼ���С
	//	 }
	// }
	// 
	// GetClientRect(&m_rect);// ���仯��ĶԻ����С��Ϊ�ɴ�С
 
}











/*******************/
/*���Dialog�е�ͼƬ*/
/******************/
void CGetPointDlg::OnBnClickedOpenpic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�����ͼƬ��ɴ򿪽��
	CFileDialog dlg(
		TRUE, _T("*.bmp"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.jpg) |*.bmp; *.jpg | All Files (*.*) |*.*||"), NULL
		);
	// ���ļ��Ի���ı�����
	dlg.m_ofn.lpstrTitle = _T("Open Image");
	// �ж��Ƿ���ͼƬ
	if( dlg.DoModal() != IDOK )	
		return;
	// ��ȡͼƬ·��	
	CString mPath = dlg.GetPathName();			
	// ��ȡͼƬ�����浽һ���ֲ����� ipl ��

	
	
	////�ַ�������
	//const size_t strsize=(mPath.GetLength()+1)*2; // ���ַ��ĳ���;
	//char * mPath1= new char[strsize]; //����ռ�;
	//size_t sz=0;
	//wcstombs_s(&sz,mPath1,strsize,mPath,_TRUNCATE);

	//int n=atoi((const char*)mPath);

	ipl = cvLoadImage( mPath, 1 );
	// �ж��Ƿ�ɹ���ȡͼƬ	


	if( !ipl )			
	    return;
	// ����һ����ʾ��ͼƬ��������
	
	

	//��ȡ�������
	CRect Rect;
	CStatic *pCtrl2 = (CStatic*)GetDlgItem(IDC_PICContent);
	pCtrl2->GetWindowRect(&Rect);
	ScreenToClient(&Rect);//��Ļ����ת��Ϊ�ͻ�������
	int WidthDest = Rect.right-Rect.left;
	int HightDest =Rect.bottom-Rect.top;


	CvSize ImgSize;
	ImgSize.height = HightDest ;
	ImgSize.width = WidthDest;




	// �Զ����ͼƬ�������ţ��ٸ��Ƶ� TheImage ��
	if(imagenumber>=allnumber){
		ipl=calm->Undistort(ipl);
	}
	ipl=ResizeImage( ipl ,ImgSize);	
	// ������ʾͼƬ����
	ShowImage( ipl, IDC_PICContent );

	if(imagenumber == 0){
		//���ñ궨�е�ͼƬ��С
		calm->SetImageWH(WidthDest,HightDest);
	}
	
	if(imagenumber<allnumber){
		calm->SetImage(ipl);
	}
	else
	{
		
		calm->SetForotherImage(ipl);
	}
	imagenumber++;
	// �ͷ� ipl ռ�õ��ڴ�	
//	cvReleaseImage( &ipl );

}

IplImage* CGetPointDlg::ResizeImage(IplImage* img,CvSize ImgSize)
{
	//����ͼƬSize
	//���ŵ�TheImage��������ı�������
	IplImage* TheImage;
	//CvSize ImgSize;
	

	//// ��ȡͼƬ�Ŀ�͸�
	//int w = img->width;
	//int h = img->height;
 //
	//int nw,nh;

	//if(Signal==true){

	//// ���ź�ͼƬ�Ŀ�͸�
	//	nw = (int)( w/scale );
	//	nh = (int)( h/scale );
	//}
	//else{
	//	//�Ŵ�
	//	nw = (int)( w*scale );
	//	nh = (int)( h*scale );
	//}
	//ImgSize.height = nh;
	//ImgSize.width = nw;
	TheImage = cvCreateImage( ImgSize,  img->depth, img->nChannels);

	// Ϊ�˽����ź��ͼƬ���� TheImage �����в�λ�������ͼƬ�� TheImage ���Ͻǵ���������ֵ
	//int tlx = (nw > nh)? 0: (int)(800-nw)/2;
	//int tly = (nw > nh)? (int)(800-nh)/2: 0;
	//���� TheImage �� ROI ������������ͼƬ img
	//cvSetImageROI( TheImage, cvRect( tlx, tly, nw, nh) );
 
	// ��ͼƬ img �������ţ������뵽 TheImage ��
	cvResize( img, TheImage ,CV_INTER_AREA );
 
	// ���� TheImage �� ROI ׼��������һ��ͼƬ
	
	return TheImage;
	//cvResetImageROI( TheImage );
}
 
void CGetPointDlg::ShowImage( IplImage* img, UINT ID )	// ID ��Picture Control�ؼ���ID��
{
	//��ʾͼƬ
	// �����ʾ�ؼ��� DC
	CDC* pDC = GetDlgItem( ID ) ->GetDC();
	// ��ȡ HDC(�豸���) �����л�ͼ����		
	HDC hDC = pDC ->GetSafeHdc();				
 
	CRect rect;
	GetDlgItem(ID) ->GetClientRect( &rect );
	// ���ͼƬ�ؼ��Ŀ�͸�
	int rw = rect.right - rect.left;			
	int rh = rect.bottom - rect.top;
	// ��ȡͼƬ�Ŀ�͸�
	int iw = img->width;	
	int ih = img->height;
	// ʹͼƬ����ʾλ�������ڿؼ�������
	int tx = (int)(rw - iw)/2;	
	int ty = (int)(rh - ih)/2;
	SetRect( rect, tx, ty, tx+iw, ty+ih );
	//// ����ͼƬ
	CvvImage cimg;
	cimg.CopyOf( img );
	// ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������	
	cimg.DrawToHDC( hDC, &rect );	
 
	ReleaseDC( pDC );
}








/*******************/
/* ��ȡͼƬ���� */
/******************/
void CGetPointDlg::OnBnClickedFindmatrix()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	tag =true;
}

BOOL CGetPointDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	// MFC��Ϣ�����������ɫ�ĵط���CWnd������⺯��PreTranslateMessage()��ͨ������������������Ըı�MFC����Ϣ�������̣�����������һ��ȫ�µĿ�����������
  
	//ClientToScreen(&(pMsg->pt));
	//CRect rc;  
	//this->GetClientRect(rc);
	ScreenToClient(&(pMsg->pt));//��Ļ����ת��Ϊ�ͻ�������

	if(pMsg->message == WM_LBUTTONDOWN && GetDlgItem(IDC_PICContent)->GetSafeHwnd() == pMsg->hwnd  && tag==true &&ipl!=NULL)//��ȡ��Ӧ�ؼ��ľ��
	{
		OnLButtonDown( 1 ,pMsg->pt);   //�ڴ˴��ݵ����λ�ڶԻ����е�����
		tag=false;
		tag2=true;//�ڶ���
		return CDialogEx::PreTranslateMessage(pMsg);
	}

	if(pMsg->message == WM_LBUTTONDOWN && GetDlgItem(IDC_PicShowS)->GetSafeHwnd() == pMsg->hwnd  && tag2==true)//��ȡ��Ӧ�ؼ��ľ��
	{
		OnLButtonDown( 2 ,pMsg->pt);   //�ڴ˴��ݵ����λ�ڶԻ����е�����
		tag2=false;
		return CDialogEx::PreTranslateMessage(pMsg);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CGetPointDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nFlags==1){

		GetDlgItem(IDC_TestAll)->SetWindowText("(    ,    )");
		GetDlgItem(IDC_Test)->SetWindowText("(    ,    )");
		GetDlgItem(IDC_TestSmall)->SetWindowText("(    ,    )");




		//CDialogEx::OnLButtonDown(nFlags, point);
		if(tag==true){
			//CRect Rect;
			CRect lRect;
			CStatic *pCtrl = (CStatic*)GetDlgItem(IDC_PICContent);
		
			pCtrl->GetWindowRect(&lRect); 
			ScreenToClient(&lRect);//��Ļ����ת��Ϊ�ͻ�������

			//int Bottom = lRect.bottom;
			//int Top =lRect.top;

			//int x=point.x;
			//int y=point.y;

			//pCtrl->ClientToScreen(&lRect); //PrintRect("static:ClientToScreen", ctrlRectScreen1);


			//CRect lRect;
			//this->GetDlgItem(IDC_PICContent) ->GetClientRect( &lRect );//�ͻ����Ĵ�С
			//this->GetDlgItem(IDC_PICContent) ->ClientToScreen( &lRect );

			//��ȡС����
			CRect sRect;
			CStatic *pCtrl2 = (CStatic*)GetDlgItem(IDC_PicShowS);
		
			pCtrl2->GetWindowRect(&sRect);
			ScreenToClient(&sRect);//��Ļ����ת��Ϊ�ͻ�������



			cood = new Calcoordinate(lRect,sRect,point,NULL);
		
			//��һ��ѡ��� �ж��Ƿ��ڴ������
			CPoint point2 = cood->CalMainCoord();

			//��ӡ�����IDC_Test��
			if(point2.x>=0){

				UpdateData(TRUE);
				CString str=cood->PrintCoord(point2);
				GetDlgItem(IDC_Test)->SetWindowText(str);
				tag=false;





				//����ͼ��
				//RectDest Ŀ�����
				//RectSrc  Դ����

				CRect RectDest,RectSrc;

				RectDest = sRect;
				int WidthDest = sRect.right-sRect.left;
				int HightDest =sRect.bottom-sRect.top;//175

				
				int length =5; //12.5;

				cood->InputMainlength(length);
				cood->InputSmalllength(WidthDest);
				
				RectSrc.left = point2.x - length;
				RectSrc.top = point2.y - length;
				RectSrc.right = point2.x + length;
				RectSrc.bottom = point2.y + length;

				CvSize ImgSize;	
				ImgSize.height = HightDest ;
				ImgSize.width = WidthDest;



				CvSize size= cvSize(2*length, 2*length);//�����С
				cvSetImageROI(ipl,cvRect(RectSrc.left, RectSrc.top,size.width, size.height));//����Դͼ��ROI
				IplImage* pDest = cvCreateImage(size,ipl->depth,ipl->nChannels);//����Ŀ��ͼ��
				cvCopy(ipl,pDest); //����ͼ��

				pDest=ResizeImage( pDest ,ImgSize);		// ������ʾͼƬ����
				ShowImage( pDest, IDC_PicShowS );

				//CDC* pDC = GetDlgItem( IDC_PICContent ) ->GetDC();

				//CDC cdem;

				//cdem.CreateCompatibleDC(pDC);
				//cdem.SelectObject(ipl);

				//CDC* pDC2 = GetDlgItem( IDC_PicShowS ) ->GetDC();
				////CDC * pDC = GetDC();
				////OnPrepareDC(pDC);

				//pDC2->BitBlt(RectDest.left,RectDest.top,WidthDest,WidthDest,&cdem,RectDest.left,RectDest.top,SRCCOPY);//��ԭ����
				//pDC2->StretchBlt(RectDest.left,RectDest.top,RectDest.Width(),RectDest.Height(),&cdem,RectSrc.left,	RectSrc.top,RectSrc.Width(),RectSrc.Height(),SRCCOPY);
				  // // �����ʾ�ؼ��� DC
				  //CDC* pDC = GetDlgItem( IDC_PicShowS ) ->GetDC();
				  //// ��ȡ HDC(�豸���) �����л�ͼ����
				  ////HDC hDC = pDC ->GetSafeHdc();	
				  //CDC *dc = new CDC;
				  //dc->CreateCompatibleDC(pDC);
				  //dc->SelectObject(ipl);
				  //
				  //

				  ////pDC- >StretchBlt(drect.left,drect.top,drect.Width(),drect.Height(),m_pdcMem,srect.left,srect.top,srect.Width(),srect.Height(),SRCCOPY);
				  //pDC->BitBlt(RectDest.left,RectDest.top,WidthDest,HightDest,dc,RectSrc.left,RectSrc.top,SRCCOPY);
				  ////����Ŵ�
				  //pDC->SetStretchBltMode(STRETCH_HALFTONE);
				  //pDC->StretchBlt(RectDest.left,RectDest.top,RectDest.Width(),RectDest.Height(),pDC,RectSrc.left,RectSrc.top,RectSrc.Width(),RectSrc.Height(),SRCCOPY);
				  ////���浱ǰ���λ�ñ���
				  ////oldx = point.x; oldy = point.y;
				  ////�ͷ��豸�������
				  //ReleaseDC(pDC);



			}
			else{
				INT_PTR nRes;     
				// ��ʾ��Ϣ�Ի���   
				nRes = 	MessageBox(_T("��ѡ������򳬹���Ҫ��"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION);   
				return;   
			}

		}
	}




	//�ڶ���ͼ������


	else if(nFlags==2){

		//�ڶ���ѡ��� �ж��Ƿ���С������

		cood->InputSmallPoint(point);

		CPoint point2 = cood->CalSmallCoord();
			//��ӡ�����IDC_Test��
			if(point2.x>=0){
				UpdateData(TRUE);
				CString str=cood->PrintCoord(point2);
				GetDlgItem(IDC_TestSmall)->SetWindowText(str);
				tag=false;
			}
			else{
				INT_PTR nRes;     
				// ��ʾ��Ϣ�Ի���   
				nRes = 	MessageBox(_T("��ѡ������򳬹���Ҫ��"), _T("����"), MB_OKCANCEL | MB_ICONQUESTION);   
				return;   
			}





			//������������
			cood->CalAllCoord();
			CString str=cood->PrintCoord();
			GetDlgItem(IDC_TestAll)->SetWindowText(str);


			//ScreenToClient(&point2);//��Ļ����ת��Ϊ�ͻ�������
			//CDC* pDC = GetWindowDC();
			//// ��ȡ HDC(�豸���) �����л�ͼ����
			//HDC hDC = pDC ->GetSafeHdc();
			//
			//SetPixel(hDC,point2.x,point2.y,RGB(255,0,0));

			////CPoint point3;
			////int diff = 2;
			////point3.x=point2.x-diff;
			////point3.y=point2.y-diff;
			////
			////for (int i=0;i<2*diff+1;i++){
			////	ScreenToClient(&(point3));//��Ļ����ת��Ϊ�ͻ�������
			////	SetPixel(hDC,point3.x,point3.y,RGB(255,0,0));
			////	point3.x++;
			////	point3.y++;
			////}

			if(IsDlgButtonChecked(IDC_InRADIO)==BST_CHECKED)
				calm->SetInPoint(cood->ReadAllx(), cood->ReadAlly());
			else if(IsDlgButtonChecked(IDC_OutRADIO)==BST_CHECKED)
				calm->SetOutPoint(cood->ReadAllx(), cood->ReadAlly());
			else if(IsDlgButtonChecked(IDC_2DRADIO)==BST_CHECKED )
				calm->SetPoint2Dto3D(cood->ReadAllx(), cood->ReadAlly());
			else
				;

	}
}


/************************/
/* �궨������ȡ��ά����*/
/***********************/
void CGetPointDlg::OnBnClickedButoutcon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	CEdit* XOne;
    XOne = (CEdit*) GetDlgItem(IDC_EditObX);
    
	//ȡֵ
    CString Xstr;
	XOne-> GetWindowText(Xstr);

	CEdit* YOne;
    YOne = (CEdit*) GetDlgItem(IDC_EditObY);
    
	//ȡֵ
    CString Ystr;
	YOne-> GetWindowText(Ystr);

	CEdit* ZOne;
    ZOne = (CEdit*) GetDlgItem(IDC_EditObZ);
    
	//ȡֵ
    CString Zstr;
	ZOne-> GetWindowText(Zstr);


	calm->SetOutObjectPoint(Xstr,Ystr,Zstr);
}























/*******************/
/* �궨������ȡ�ڲ�*/
/******************/
void CGetPointDlg::OnBnClickedButtoncalculate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iresult2 =calm->IfDistMatrixNull();
	int iresult =calm->IfInMatrixNull();
	
	if(iresult == 0 || iresult2 ==0){
		calm->CalInMatrix(false,false);
		//�����ڲν��
		calm->SaveInMatrix();
		calm->SaveDistMatrix();
	}
	UpdateData(TRUE);
	CString str=calm->PrintInMatrix();
	GetDlgItem(IDC_InMatrix)->SetWindowText(str);
	str=calm->PrintDisMatrix();
	GetDlgItem(IDC_DisMatrix)->SetWindowText(str);


}


/*******************/
/* �궨������ȡ���*/
/******************/

void CGetPointDlg::OnBnClickedButtoncalculateout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int iresult =calm->IfOutMatrixNull();
	
	if(iresult == 0 ){
		calm->SetProvided(true);
		calm->CalOutMatrix();
		//������ν��
		calm->SaveOutMatrix();
	}
	
	UpdateData(TRUE);
	CString str=calm->PrintTraMatrix();
	GetDlgItem(IDC_TraMatrix)->SetWindowText(str);
	str=calm->PrintRotMatrix();
	GetDlgItem(IDC_RotMatrix)->SetWindowText(str);
}



/*******************/
/* �궨����2Dת3D*/
/******************/
void CGetPointDlg::OnBnClickedButton2d()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//IplImage * newImage = calm->Undistort();
	//ShowImage(newImage,IDC_PICContent);
	calm->Cal2Dto3D();
	CString str=calm->PrintPoint3D();
	GetDlgItem(IDC_3DMatrix)->SetWindowText(str);
}
