#pragma once


// DialogCal 对话框

class DialogCal : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCal)

public:
	DialogCal(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogCal();

	void SetAllPoint(double Points[50][2], int number);

// 对话框数据
	enum { IDD = IDD_GETPOINT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:

	double AllPoint[50][2];
	int numberAP;

};
