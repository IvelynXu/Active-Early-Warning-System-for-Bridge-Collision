#pragma once


// DialogCal �Ի���

class DialogCal : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCal)

public:
	DialogCal(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogCal();

	void SetAllPoint(double Points[50][2], int number);

// �Ի�������
	enum { IDD = IDD_GETPOINT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:

	double AllPoint[50][2];
	int numberAP;

};
