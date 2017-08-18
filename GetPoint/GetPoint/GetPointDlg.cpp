
// GetPointDlg.cpp : 实现文件
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













// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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





// CGetPointDlg 对话框

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


	//构造函数 添加代码

	
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


// CGetPointDlg 消息处理程序

BOOL CGetPointDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//获取对话框创建时的大小
	GetClientRect(&m_rect);

	CButton *RadioButton1 = (CButton*)GetDlgItem(IDC_InRADIO);
	RadioButton1->SetCheck(TRUE);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGetPointDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGetPointDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}















/***************************/
/*  更改Dialog及其控件大小*/
/**************************/

void CGetPointDlg::OnSize(UINT nType, int cx, int cy)
{


	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码


	//更改默认Picture的大小

  

	//CWnd *pWnd;
	//pWnd = GetDlgItem( IDC_PicShowS ); //获取控件指针，IDC_BUTTON1为控件ID号
	//pWnd->SetWindowPos( NULL,50,50,0,0,SWP_NOZORDER | SWP_NOSIZE ); //把按钮移到窗口的(50,80)处
	//pWnd->SetWindowPos( NULL,0,0,300,300,SWP_NOZORDER | SWP_NOMOVE ); //把编辑控件的大小设为(100,80)，位置不变
	////pWnd->MoveWindow( CRect(0,0,100,100) ); 




	//更改Dialog的规格 并将其中的内部控件一起更改
	//未经过测试 仍不确定

	//int  IDnumber = 4;
	//CString *IDname=(CString*) malloc (IDnumber);
	//IDname[0]="ID_OpenPic";

	// for (int i=0;i<1;i++)     //因为是两个控件，所以这里用了循环
	// {
	//	 CWnd *pWnd; 
	//	 pWnd = GetDlgItem(i);     //获取ID为i的空间的句柄，因为“确认”ID为1，“取消”ID为2
	//	 if(pWnd)  //判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建
	//	 {
	//		 CRect rect;   //获取控件变化前的大小  
	//		 pWnd->GetWindowRect(&rect);
	//		 ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标
	//		 
	//		 //cx/m_rect.Width()为对话框在横向的变化比例
	//		 rect.left=rect.left*cx/m_rect.Width();//调整控件大小
	//		 rect.right=rect.right*cx/m_rect.Width();
	//		 rect.top=rect.top*cy/m_rect.Height();
	//		 rect.bottom=rect.bottom*cy/m_rect.Height();
	//		 
	//		 pWnd->MoveWindow(rect);//设置控件大小
	//	 }
	// }
	// 
	// GetClientRect(&m_rect);// 将变化后的对话框大小设为旧大小
 
}











/*******************/
/*添加Dialog中的图片*/
/******************/
void CGetPointDlg::OnBnClickedOpenpic()
{
	// TODO: 在此添加控件通知处理程序代码
	//点击打开图片完成打开结果
	CFileDialog dlg(
		TRUE, _T("*.bmp"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.jpg) |*.bmp; *.jpg | All Files (*.*) |*.*||"), NULL
		);
	// 打开文件对话框的标题名
	dlg.m_ofn.lpstrTitle = _T("Open Image");
	// 判断是否获得图片
	if( dlg.DoModal() != IDOK )	
		return;
	// 获取图片路径	
	CString mPath = dlg.GetPathName();			
	// 读取图片、缓存到一个局部变量 ipl 中

	
	
	////字符集问题
	//const size_t strsize=(mPath.GetLength()+1)*2; // 宽字符的长度;
	//char * mPath1= new char[strsize]; //分配空间;
	//size_t sz=0;
	//wcstombs_s(&sz,mPath1,strsize,mPath,_TRUNCATE);

	//int n=atoi((const char*)mPath);

	ipl = cvLoadImage( mPath, 1 );
	// 判断是否成功读取图片	


	if( !ipl )			
	    return;
	// 对上一幅显示的图片数据清零
	
	

	//获取大矩阵宽度
	CRect Rect;
	CStatic *pCtrl2 = (CStatic*)GetDlgItem(IDC_PICContent);
	pCtrl2->GetWindowRect(&Rect);
	ScreenToClient(&Rect);//屏幕坐标转化为客户区坐标
	int WidthDest = Rect.right-Rect.left;
	int HightDest =Rect.bottom-Rect.top;


	CvSize ImgSize;
	ImgSize.height = HightDest ;
	ImgSize.width = WidthDest;




	// 对读入的图片进行缩放，再复制到 TheImage 中
	if(imagenumber>=allnumber){
		ipl=calm->Undistort(ipl);
	}
	ipl=ResizeImage( ipl ,ImgSize);	
	// 调用显示图片函数
	ShowImage( ipl, IDC_PICContent );

	if(imagenumber == 0){
		//设置标定中的图片大小
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
	// 释放 ipl 占用的内存	
//	cvReleaseImage( &ipl );

}

IplImage* CGetPointDlg::ResizeImage(IplImage* img,CvSize ImgSize)
{
	//更改图片Size
	//缩放到TheImage区域所需的比例因子
	IplImage* TheImage;
	//CvSize ImgSize;
	

	//// 读取图片的宽和高
	//int w = img->width;
	//int h = img->height;
 //
	//int nw,nh;

	//if(Signal==true){

	//// 缩放后图片的宽和高
	//	nw = (int)( w/scale );
	//	nh = (int)( h/scale );
	//}
	//else{
	//	//放大
	//	nw = (int)( w*scale );
	//	nh = (int)( h*scale );
	//}
	//ImgSize.height = nh;
	//ImgSize.width = nw;
	TheImage = cvCreateImage( ImgSize,  img->depth, img->nChannels);

	// 为了将缩放后的图片存入 TheImage 的正中部位，需计算图片在 TheImage 左上角的期望坐标值
	//int tlx = (nw > nh)? 0: (int)(800-nw)/2;
	//int tly = (nw > nh)? (int)(800-nh)/2: 0;
	//设置 TheImage 的 ROI 区域，用来存入图片 img
	//cvSetImageROI( TheImage, cvRect( tlx, tly, nw, nh) );
 
	// 对图片 img 进行缩放，并存入到 TheImage 中
	cvResize( img, TheImage ,CV_INTER_AREA );
 
	// 重置 TheImage 的 ROI 准备读入下一幅图片
	
	return TheImage;
	//cvResetImageROI( TheImage );
}
 
void CGetPointDlg::ShowImage( IplImage* img, UINT ID )	// ID 是Picture Control控件的ID号
{
	//显示图片
	// 获得显示控件的 DC
	CDC* pDC = GetDlgItem( ID ) ->GetDC();
	// 获取 HDC(设备句柄) 来进行绘图操作		
	HDC hDC = pDC ->GetSafeHdc();				
 
	CRect rect;
	GetDlgItem(ID) ->GetClientRect( &rect );
	// 求出图片控件的宽和高
	int rw = rect.right - rect.left;			
	int rh = rect.bottom - rect.top;
	// 读取图片的宽和高
	int iw = img->width;	
	int ih = img->height;
	// 使图片的显示位置正好在控件的正中
	int tx = (int)(rw - iw)/2;	
	int ty = (int)(rh - ih)/2;
	SetRect( rect, tx, ty, tx+iw, ty+ih );
	//// 复制图片
	CvvImage cimg;
	cimg.CopyOf( img );
	// 将图片绘制到显示控件的指定区域内	
	cimg.DrawToHDC( hDC, &rect );	
 
	ReleaseDC( pDC );
}








/*******************/
/* 获取图片坐标 */
/******************/
void CGetPointDlg::OnBnClickedFindmatrix()
{
	// TODO: 在此添加控件通知处理程序代码
	tag =true;
}

BOOL CGetPointDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	// MFC消息控制流最具特色的地方是CWnd类的虚拟函数PreTranslateMessage()，通过重载这个函数，可以改变MFC的消息控制流程，甚至可以作一个全新的控制流出来。
  
	//ClientToScreen(&(pMsg->pt));
	//CRect rc;  
	//this->GetClientRect(rc);
	ScreenToClient(&(pMsg->pt));//屏幕坐标转化为客户区坐标

	if(pMsg->message == WM_LBUTTONDOWN && GetDlgItem(IDC_PICContent)->GetSafeHwnd() == pMsg->hwnd  && tag==true &&ipl!=NULL)//获取相应控件的句柄
	{
		OnLButtonDown( 1 ,pMsg->pt);   //在此传递点击部位在对话框中的坐标
		tag=false;
		tag2=true;//第二步
		return CDialogEx::PreTranslateMessage(pMsg);
	}

	if(pMsg->message == WM_LBUTTONDOWN && GetDlgItem(IDC_PicShowS)->GetSafeHwnd() == pMsg->hwnd  && tag2==true)//获取相应控件的句柄
	{
		OnLButtonDown( 2 ,pMsg->pt);   //在此传递点击部位在对话框中的坐标
		tag2=false;
		return CDialogEx::PreTranslateMessage(pMsg);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CGetPointDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
			ScreenToClient(&lRect);//屏幕坐标转化为客户区坐标

			//int Bottom = lRect.bottom;
			//int Top =lRect.top;

			//int x=point.x;
			//int y=point.y;

			//pCtrl->ClientToScreen(&lRect); //PrintRect("static:ClientToScreen", ctrlRectScreen1);


			//CRect lRect;
			//this->GetDlgItem(IDC_PICContent) ->GetClientRect( &lRect );//客户区的大小
			//this->GetDlgItem(IDC_PICContent) ->ClientToScreen( &lRect );

			//获取小矩阵
			CRect sRect;
			CStatic *pCtrl2 = (CStatic*)GetDlgItem(IDC_PicShowS);
		
			pCtrl2->GetWindowRect(&sRect);
			ScreenToClient(&sRect);//屏幕坐标转化为客户区坐标



			cood = new Calcoordinate(lRect,sRect,point,NULL);
		
			//第一次选择点 判断是否在大矩形中
			CPoint point2 = cood->CalMainCoord();

			//打印结果在IDC_Test中
			if(point2.x>=0){

				UpdateData(TRUE);
				CString str=cood->PrintCoord(point2);
				GetDlgItem(IDC_Test)->SetWindowText(str);
				tag=false;





				//处理图像
				//RectDest 目标矩形
				//RectSrc  源矩形

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



				CvSize size= cvSize(2*length, 2*length);//区域大小
				cvSetImageROI(ipl,cvRect(RectSrc.left, RectSrc.top,size.width, size.height));//设置源图像ROI
				IplImage* pDest = cvCreateImage(size,ipl->depth,ipl->nChannels);//创建目标图像
				cvCopy(ipl,pDest); //复制图像

				pDest=ResizeImage( pDest ,ImgSize);		// 调用显示图片函数
				ShowImage( pDest, IDC_PicShowS );

				//CDC* pDC = GetDlgItem( IDC_PICContent ) ->GetDC();

				//CDC cdem;

				//cdem.CreateCompatibleDC(pDC);
				//cdem.SelectObject(ipl);

				//CDC* pDC2 = GetDlgItem( IDC_PicShowS ) ->GetDC();
				////CDC * pDC = GetDC();
				////OnPrepareDC(pDC);

				//pDC2->BitBlt(RectDest.left,RectDest.top,WidthDest,WidthDest,&cdem,RectDest.left,RectDest.top,SRCCOPY);//复原操作
				//pDC2->StretchBlt(RectDest.left,RectDest.top,RectDest.Width(),RectDest.Height(),&cdem,RectSrc.left,	RectSrc.top,RectSrc.Width(),RectSrc.Height(),SRCCOPY);
				  // // 获得显示控件的 DC
				  //CDC* pDC = GetDlgItem( IDC_PicShowS ) ->GetDC();
				  //// 获取 HDC(设备句柄) 来进行绘图操作
				  ////HDC hDC = pDC ->GetSafeHdc();	
				  //CDC *dc = new CDC;
				  //dc->CreateCompatibleDC(pDC);
				  //dc->SelectObject(ipl);
				  //
				  //

				  ////pDC- >StretchBlt(drect.left,drect.top,drect.Width(),drect.Height(),m_pdcMem,srect.left,srect.top,srect.Width(),srect.Height(),SRCCOPY);
				  //pDC->BitBlt(RectDest.left,RectDest.top,WidthDest,HightDest,dc,RectSrc.left,RectSrc.top,SRCCOPY);
				  ////拉伸放大
				  //pDC->SetStretchBltMode(STRETCH_HALFTONE);
				  //pDC->StretchBlt(RectDest.left,RectDest.top,RectDest.Width(),RectDest.Height(),pDC,RectSrc.left,RectSrc.top,RectSrc.Width(),RectSrc.Height(),SRCCOPY);
				  ////保存当前鼠标位置备用
				  ////oldx = point.x; oldy = point.y;
				  ////释放设备环境句柄
				  //ReleaseDC(pDC);



			}
			else{
				INT_PTR nRes;     
				// 显示消息对话框   
				nRes = 	MessageBox(_T("您选择的区域超过了要求"), _T("警告"), MB_OKCANCEL | MB_ICONQUESTION);   
				return;   
			}

		}
	}




	//第二个图的坐标


	else if(nFlags==2){

		//第二次选择点 判断是否在小矩形中

		cood->InputSmallPoint(point);

		CPoint point2 = cood->CalSmallCoord();
			//打印结果在IDC_Test中
			if(point2.x>=0){
				UpdateData(TRUE);
				CString str=cood->PrintCoord(point2);
				GetDlgItem(IDC_TestSmall)->SetWindowText(str);
				tag=false;
			}
			else{
				INT_PTR nRes;     
				// 显示消息对话框   
				nRes = 	MessageBox(_T("您选择的区域超过了要求"), _T("警告"), MB_OKCANCEL | MB_ICONQUESTION);   
				return;   
			}





			//计算最终坐标
			cood->CalAllCoord();
			CString str=cood->PrintCoord();
			GetDlgItem(IDC_TestAll)->SetWindowText(str);


			//ScreenToClient(&point2);//屏幕坐标转化为客户区坐标
			//CDC* pDC = GetWindowDC();
			//// 获取 HDC(设备句柄) 来进行绘图操作
			//HDC hDC = pDC ->GetSafeHdc();
			//
			//SetPixel(hDC,point2.x,point2.y,RGB(255,0,0));

			////CPoint point3;
			////int diff = 2;
			////point3.x=point2.x-diff;
			////point3.y=point2.y-diff;
			////
			////for (int i=0;i<2*diff+1;i++){
			////	ScreenToClient(&(point3));//屏幕坐标转化为客户区坐标
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
/* 标定——获取三维数据*/
/***********************/
void CGetPointDlg::OnBnClickedButoutcon()
{
	// TODO: 在此添加控件通知处理程序代码	
	CEdit* XOne;
    XOne = (CEdit*) GetDlgItem(IDC_EditObX);
    
	//取值
    CString Xstr;
	XOne-> GetWindowText(Xstr);

	CEdit* YOne;
    YOne = (CEdit*) GetDlgItem(IDC_EditObY);
    
	//取值
    CString Ystr;
	YOne-> GetWindowText(Ystr);

	CEdit* ZOne;
    ZOne = (CEdit*) GetDlgItem(IDC_EditObZ);
    
	//取值
    CString Zstr;
	ZOne-> GetWindowText(Zstr);


	calm->SetOutObjectPoint(Xstr,Ystr,Zstr);
}























/*******************/
/* 标定——获取内参*/
/******************/
void CGetPointDlg::OnBnClickedButtoncalculate()
{
	// TODO: 在此添加控件通知处理程序代码
	int iresult2 =calm->IfDistMatrixNull();
	int iresult =calm->IfInMatrixNull();
	
	if(iresult == 0 || iresult2 ==0){
		calm->CalInMatrix(false,false);
		//保存内参结果
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
/* 标定——获取外参*/
/******************/

void CGetPointDlg::OnBnClickedButtoncalculateout()
{
	// TODO: 在此添加控件通知处理程序代码

	int iresult =calm->IfOutMatrixNull();
	
	if(iresult == 0 ){
		calm->SetProvided(true);
		calm->CalOutMatrix();
		//保存外参结果
		calm->SaveOutMatrix();
	}
	
	UpdateData(TRUE);
	CString str=calm->PrintTraMatrix();
	GetDlgItem(IDC_TraMatrix)->SetWindowText(str);
	str=calm->PrintRotMatrix();
	GetDlgItem(IDC_RotMatrix)->SetWindowText(str);
}



/*******************/
/* 标定——2D转3D*/
/******************/
void CGetPointDlg::OnBnClickedButton2d()
{
	// TODO: 在此添加控件通知处理程序代码
	//IplImage * newImage = calm->Undistort();
	//ShowImage(newImage,IDC_PICContent);
	calm->Cal2Dto3D();
	CString str=calm->PrintPoint3D();
	GetDlgItem(IDC_3DMatrix)->SetWindowText(str);
}
