#include "stdafx.h"
#include "EXIT.h"
#include "BisonClicker.h"
#include "afxdialogex.h"

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


CEXIT::CEXIT() : CDialogEx(CEXIT::IDD)
{
	
}

void CEXIT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CEXIT, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SURE, &CEXIT::OnBnClickedSure)
	ON_BN_CLICKED(IDC_ABOUT,&CEXIT::AboutBox)
END_MESSAGE_MAP()

BOOL CEXIT::OnInitDialog()
{
	CDialog::OnInitDialog();
	pBtn = (CButton*)GetDlgItem(IDC_RADIO_MIN);
	pBtn->SetCheck(1);
	return true;
}


void CEXIT::OnBnClickedSure()
{
	// TODO:  在此添加控件通知处理程序代码
	HWND hwnd = ::FindWindow("Bison_Click", NULL);
	UINT Action[] = { IDC_RADIO_MIN, IDC_RADIO_EXIT };

		pBtn = (CButton*)GetDlgItem(Action[0]);
		if (pBtn->GetCheck()==TRUE)
		{
			 ::PostMessage(hwnd, WM_HIDE_WINDOWS, NULL, NULL);
			 PostMessage(WM_CLOSE);		
		}
		pBtn = (CButton*)GetDlgItem(Action[1]);
		if (pBtn->GetCheck() == TRUE)
		{
			if (IDYES == MessageBox("你确定退出Bison鼠标连击器吗？", "温馨提示", MB_YESNO))
			{	
				::PostMessage(hwnd, WM_DELETE_NOTIFY, NULL, NULL);
			}
		}
	
}

void CEXIT::AboutBox()
{
	CAboutDlg About;
	About.DoModal();
}

