
// guiDlg.h : ͷ�ļ�
//

#pragma once
#include"si_global.h"

UINT ThreadFunc(LPVOID lpParam);
struct ThreadInfo
{
//	CoreApplication *app;
//	HWND hWnd;
	SI::Query* pQ;
};

// CguiDlg �Ի���
class CguiDlg : public CDialogEx
{
// ����
public:
	CguiDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEcsearchinput();
	afx_msg void OnBnClickedBtshowpage();
	CString searchInput;
//	CString idInput;
	CString searchRes;
	CString pageInfo;
	afx_msg void OnBnClickedBtavlsearch();
	afx_msg void OnBnClickedBthashsearch();
	int idInput;

	CWinThread* pThread;
};
