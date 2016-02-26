
// Bison鼠标连击器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BisonClicker.h"
#include "BisonClickerDlg.h"
#include "afxdialogex.h"
#include "EXIT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL flag = false;
BOOL TimeFlag = false;

struct WorkParam {
public:
	long ClickTimes;
	long ClickInterval ;
	int MouseFlag;
	BOOL HaveTimes;
};

WorkParam wp;




// CBisonClickerDlg 对话框



CBisonClickerDlg::CBisonClickerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBisonClickerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_WorkIcon = AfxGetApp()->LoadIcon(IDI_WORKING);
	m_WaitIcon = AfxGetApp()->LoadIcon(IDI_WAITING);
}

void CBisonClickerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MOUSE, m_Mouse);
}

BEGIN_MESSAGE_MAP(CBisonClickerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_MESSAGE(UM_ICONNOTIFY, (LRESULT(__thiscall CWnd::*)(WPARAM, LPARAM))OnIconNotify)
	ON_MESSAGE(WM_DELETE_NOTIFY, DeleteNotify)
	ON_MESSAGE(WM_HIDE_WINDOWS, HideWindows)
	ON_MESSAGE(WM_STOP_CLICK,StopClick)
	ON_BN_CLICKED(IDC_CHECK_CLICK, &CBisonClickerDlg::OnBnClickedCheckClick)
	//ON_BN_CLICKED(IDC_BUTTON1, &CBisonClickerDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CBisonClickerDlg 消息处理程序

BOOL CBisonClickerDlg::OnInitDialog()
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

	RegisterHotKey(GetSafeHwnd(), 0x3333, NULL, VK_HOME); //

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	SkinH_Attach();

	::SkinH_AttachEx("skinh.she", NULL);
	//::SkinH_AttachEx("Aero.she", NULL);

	GetDlgItem(IDC_EDIT_TIMES)->SetWindowText("0");// 设置点击次数
	GetDlgItem(IDC_EDIT_TIMES)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_INTERVAL)->SetWindowText("0");//设置点击间隔
	this->SetComboBox();
	// TODO:  在此添加额外的初始化代码

	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;           //父窗口
	nid.uID = IDR_MAINFRAME;     //icon  ID
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;   //托盘所拥有的状态
	nid.uCallbackMessage = UM_ICONNOTIFY;            //回调消息
	nid.hIcon = m_hIcon;                            //icon 变量
	CString str = "Bison_Click 1.0";       //气泡提示
	lstrcpyn(nid.szTip, (LPCSTR)str, sizeof(nid.szTip) / sizeof(nid.szTip[0]));
	Shell_NotifyIcon(NIM_ADD, &nid);   //显示托盘


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

/*void CBisonClickerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
}*/

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBisonClickerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBisonClickerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBisonClickerDlg::SetComboBox()
{
	m_Mouse.InsertString(0, "左键");
	m_Mouse.InsertString(1, "右键");
	m_Mouse.SetCurSel(0);
}

void CBisonClickerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	switch (nType)
	{
	case SIZE_MINIMIZED:
		ShowWindow(SW_HIDE);
		break;
	}
}

void CBisonClickerDlg::OnBnClickedStart()
{
	// TODO:  在此添加控件通知处理程序代码
	
	CString GetTimes;
	wp.ClickTimes = 0; wp.ClickInterval = 1;
	wp.MouseFlag = m_Mouse.GetCurSel();
	wp.HaveTimes = TimeFlag;
	CButton *pBtn = NULL;
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_CLICK);
	if (pBtn->GetCheck() == TRUE)                           //判断是否有设置点击次数
	{
		GetDlgItem(IDC_EDIT_TIMES)->GetWindowText(GetTimes);//获取点击次数
		wp.ClickTimes = atoi(GetTimes);
	}
	GetDlgItem(IDC_EDIT_INTERVAL)->GetWindowText(GetTimes);//获取点击间隔
	wp.ClickInterval = atoi(GetTimes);
	if (wp.ClickInterval < 5){ wp.ClickInterval = 1; }
	Work = CreateThread(NULL, 0, WorkThread, &wp, NULL, NULL);
}

BOOL CBisonClickerDlg::PreTranslateMessage(MSG* pMsg)		// 消息预处理
{

	if (GetAsyncKeyState(VK_HOME))		// 判断是否所要设置的快捷键
	{
		if (flag){
			flag = false;
			MessageBeep(0);
			TerminateThread(Work,NULL);
			this->SetNotifyIcon(m_WaitIcon);
			CloseHandle(Work);
		}
		else{
			flag = true;
			MessageBeep(0);
			OnBnClickedStart();
			this->SetNotifyIcon(m_WorkIcon);
					// 执行快捷键要处理的函数
		}
		return  TRUE;				// 返回
	}
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CBisonClickerDlg::SetNotifyIcon(HICON NewIcon)
{
	nid.hIcon = NewIcon;
	BOOL Result = Shell_NotifyIconA(NIM_MODIFY, &nid);
	UpdateWindow();
	UpdateData();
	return Result;
}

void CBisonClickerDlg::OnClose()
{
	CEXIT CExitDlg;
	CExitDlg.DoModal();
}

void CBisonClickerDlg::OnIconNotify(WPARAM wParam, LPARAM lParam)
{

	switch ((UINT)lParam)
	{
	case WM_LBUTTONDOWN: // click or dbclick left button on icon
	case WM_LBUTTONDBLCLK: // should show desktop
		if (!IsWindowVisible())
		{
			this->ShowWindow(SW_SHOWNORMAL);
			this->SetActiveWindow();
			this->SetForegroundWindow();
			this->BringWindowToTop();
		}
		else
			ShowWindow(SW_HIDE);
		break;
	}
}

DWORD WINAPI WorkThread(LPVOID lpParameter)
{
	WorkParam *wParam = (WorkParam *)lpParameter;
	HWND hWnd = FindWindow("Bison_Click", NULL);
	unsigned long TempTimes = 1;
	if (wParam->MouseFlag == 0){
		while (true)
		{
			mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, NULL, NULL);			
			if (TempTimes == wParam->ClickTimes){
				::PostMessage(hWnd, WM_STOP_CLICK, NULL, NULL); break;
			}
			Sleep(wParam->ClickInterval);
			TempTimes+=wParam->HaveTimes;
		}
	}
	else if (wParam->MouseFlag == 1)
	{
		while (true)
		{
			mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, NULL, NULL);
			if (TempTimes == wParam->ClickTimes){
				::PostMessage(hWnd, WM_STOP_CLICK, NULL, NULL); break;
			}
			Sleep(wParam->ClickInterval);
			TempTimes += wParam->HaveTimes;
		}
	}
	return 0;
}



void CBisonClickerDlg::OnBnClickedCheckClick()
{
	// TODO:  在此添加控件通知处理程序代码
	if (TimeFlag){
		TimeFlag = false;
	}
	else{
		TimeFlag = true;
	}
	GetDlgItem(IDC_EDIT_TIMES)->EnableWindow(TimeFlag);
}



LRESULT CBisonClickerDlg::HideWindows(WPARAM wParam, LPARAM lParam)
{
	ShowWindow(SW_HIDE);
	return 1;
}

LRESULT CBisonClickerDlg::DeleteNotify(WPARAM wParam, LPARAM lParam)
{
	Shell_NotifyIcon(NIM_DELETE, &nid); //在托盘区删除图标 
	UpdateWindow();
	UpdateData();
	exit(0);
	return 1;
}

LRESULT CBisonClickerDlg::StopClick(WPARAM wParam, LPARAM lParam)
{
	MessageBeep(0);
	this->SetNotifyIcon(m_WaitIcon);
	return 1;
}