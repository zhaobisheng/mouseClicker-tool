
// Bison鼠标连击器Dlg.h : 头文件
//



#pragma once
DWORD WINAPI WorkThread(LPVOID lpParameter);

// CBisonClickerDlg 对话框
class CBisonClickerDlg : public CDialogEx
{
// 构造
public:
	CBisonClickerDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual BOOL PreTranslateMessage(MSG* pMsg);
// 对话框数据
	enum { IDD = IDD_BISON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	HICON m_WorkIcon, m_WaitIcon;
	NOTIFYICONDATA nid;
	HANDLE Work;
	CComboBox m_Mouse;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnIconNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg BOOL SetNotifyIcon(HICON);
	afx_msg void SetComboBox();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedCheckClick();
	afx_msg LRESULT HideWindows(WPARAM, LPARAM);
	afx_msg LRESULT StopClick(WPARAM, LPARAM);
	afx_msg LRESULT DeleteNotify(WPARAM, LPARAM);
};
