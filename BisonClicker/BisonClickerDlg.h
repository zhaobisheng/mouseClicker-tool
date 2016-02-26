
// Bison���������Dlg.h : ͷ�ļ�
//



#pragma once
DWORD WINAPI WorkThread(LPVOID lpParameter);

// CBisonClickerDlg �Ի���
class CBisonClickerDlg : public CDialogEx
{
// ����
public:
	CBisonClickerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual BOOL PreTranslateMessage(MSG* pMsg);
// �Ի�������
	enum { IDD = IDD_BISON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	HICON m_WorkIcon, m_WaitIcon;
	NOTIFYICONDATA nid;
	HANDLE Work;
	CComboBox m_Mouse;
	// ���ɵ���Ϣӳ�亯��
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
