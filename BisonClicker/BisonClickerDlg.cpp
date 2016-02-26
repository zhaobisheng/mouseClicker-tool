
// Bison���������Dlg.cpp : ʵ���ļ�
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




// CBisonClickerDlg �Ի���



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


// CBisonClickerDlg ��Ϣ�������

BOOL CBisonClickerDlg::OnInitDialog()
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

	RegisterHotKey(GetSafeHwnd(), 0x3333, NULL, VK_HOME); //

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	SkinH_Attach();

	::SkinH_AttachEx("skinh.she", NULL);
	//::SkinH_AttachEx("Aero.she", NULL);

	GetDlgItem(IDC_EDIT_TIMES)->SetWindowText("0");// ���õ������
	GetDlgItem(IDC_EDIT_TIMES)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_INTERVAL)->SetWindowText("0");//���õ�����
	this->SetComboBox();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;           //������
	nid.uID = IDR_MAINFRAME;     //icon  ID
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;   //������ӵ�е�״̬
	nid.uCallbackMessage = UM_ICONNOTIFY;            //�ص���Ϣ
	nid.hIcon = m_hIcon;                            //icon ����
	CString str = "Bison_Click 1.0";       //������ʾ
	lstrcpyn(nid.szTip, (LPCSTR)str, sizeof(nid.szTip) / sizeof(nid.szTip[0]));
	Shell_NotifyIcon(NIM_ADD, &nid);   //��ʾ����


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBisonClickerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBisonClickerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBisonClickerDlg::SetComboBox()
{
	m_Mouse.InsertString(0, "���");
	m_Mouse.InsertString(1, "�Ҽ�");
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	CString GetTimes;
	wp.ClickTimes = 0; wp.ClickInterval = 1;
	wp.MouseFlag = m_Mouse.GetCurSel();
	wp.HaveTimes = TimeFlag;
	CButton *pBtn = NULL;
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_CLICK);
	if (pBtn->GetCheck() == TRUE)                           //�ж��Ƿ������õ������
	{
		GetDlgItem(IDC_EDIT_TIMES)->GetWindowText(GetTimes);//��ȡ�������
		wp.ClickTimes = atoi(GetTimes);
	}
	GetDlgItem(IDC_EDIT_INTERVAL)->GetWindowText(GetTimes);//��ȡ������
	wp.ClickInterval = atoi(GetTimes);
	if (wp.ClickInterval < 5){ wp.ClickInterval = 1; }
	Work = CreateThread(NULL, 0, WorkThread, &wp, NULL, NULL);
}

BOOL CBisonClickerDlg::PreTranslateMessage(MSG* pMsg)		// ��ϢԤ����
{

	if (GetAsyncKeyState(VK_HOME))		// �ж��Ƿ���Ҫ���õĿ�ݼ�
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
					// ִ�п�ݼ�Ҫ����ĺ���
		}
		return  TRUE;				// ����
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	Shell_NotifyIcon(NIM_DELETE, &nid); //��������ɾ��ͼ�� 
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