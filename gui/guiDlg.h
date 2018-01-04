
// guiDlg.h : 头文件
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

// CguiDlg 对话框
class CguiDlg : public CDialogEx
{
// 构造
public:
	CguiDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
