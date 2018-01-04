
// guiDlg.cpp : 实现文件
//

//#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "gui.h"
#include "guiDlg.h"
#include "afxdialogex.h"

#include"si_global.h"
#include"AVL.h"
#include"linklist.h"
#include"sistring.h"
#include"pageinfo.h"
#include"docindex.h"
#include"indexlistnode.h"
#include"hash.h"
#include"query.h"
#include"interface.h"
#include"segmentationer.h"
#include<ctime>


using SI::linklist;
using SI::SIchar_t;
using SI::SIsize_t;
using SI::SIString;
using SI::SIStringList;
using SI::Element;
using SI::ACAuto;
using SI::AVL;
using SI::AVL_Node;
using SI::DocIndex;
using SI::PageInfo;
using SI::IndexListNode;
using SI::Segmentationer;
using SI::HASH;
using SI::Query;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CguiDlg 对话框
#define DOHASH
#define DOAVL

char cs[SI::DEFULT_BUFFER_SIZE];
Query Q;
ThreadInfo threadInfo;

CguiDlg::CguiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GUI_DIALOG, pParent)
	, searchInput(_T(""))
	, searchRes(_T(""))
	, pageInfo(_T(""))
	, idInput(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	threadInfo.pQ = &Q;
	pThread = AfxBeginThread(ThreadFunc, &threadInfo);
}

void CguiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, ECsearchInput, searchInput);
	DDX_Text(pDX, ECsearchRes, searchRes);
	DDX_Text(pDX, ECpageInfo, pageInfo);
	DDX_Text(pDX, ECidInput, idInput);
	DDV_MinMaxInt(pDX, idInput, 0, 99999);
}

BEGIN_MESSAGE_MAP(CguiDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(ECsearchInput, &CguiDlg::OnEnChangeEcsearchinput)
	ON_BN_CLICKED(BTshowPage, &CguiDlg::OnBnClickedBtshowpage)
	ON_BN_CLICKED(BTAVLSearch, &CguiDlg::OnBnClickedBtavlsearch)
	ON_BN_CLICKED(BTHASHSearch, &CguiDlg::OnBnClickedBthashsearch)
END_MESSAGE_MAP()


// CguiDlg 消息处理程序

BOOL CguiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CguiDlg::OnPaint()
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
HCURSOR CguiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CguiDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CguiDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CguiDlg::OnEnChangeEcsearchinput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CguiDlg::OnBnClickedBtshowpage()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	SIString sistr;
	SIString temp;
	PageInfo* pages;
	sistr.clear();
	if (idInput > 4000 || idInput <= 0) sistr = "No Result";
	else
	{
		pages = Q.getPage(idInput);
		
		sistr += "[索引ID]   ";
		itoa(pages->nid, cs, 10);
		temp.fromCstr(cs);
		sistr += temp;
		sistr += "\r\n";

		sistr += "[序号]     ";
		itoa(pages->id, cs, 10);
		temp.fromCstr(cs);
		sistr += temp;
		sistr += "\r\n";

		sistr += "[网址]     ";
		sistr += pages->url;
		sistr += "\r\n";
		sistr += "[发帖大类] ";
		sistr += pages->genType;
		sistr += "\r\n";
		sistr += "[发帖小类] ";
		sistr += pages->spcType;
		sistr += "\r\n";
		sistr += "[发帖标题] ";
		sistr += pages->title;
		sistr += "\r\n";
		sistr += "\r\n";
		sistr += "[发帖日期] ";
		sistr += pages->date;
		sistr += "\r\n";
		sistr += "[发帖人]   ";
		sistr += pages->author;
		sistr += "\r\n";
		sistr += "[发帖类型] ";
		sistr += pages->pref;
		sistr += "\r\n";
		sistr += "[发帖内容] ";
		sistr += pages->contents;
	}
	sistr += '\0';
	sistr.txUnicode();

	pageInfo.Format(_T("%s"), sistr.getdata());

	UpdateData(FALSE);

}


void CguiDlg::OnBnClickedBtavlsearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	SIString sistr;
	sistr.fromCString(searchInput);
	sistr.txGBK();
	SIStringList slist = sistr.split(' ');
	SIStringList queryList;
	SIString temp;
	linklist<IndexListNode> res;
	queryList._clear();
	sistr.clear();
	int clk = clock();
	for (SIStringList::Iterator it = slist.begin(); it != slist.end(); ++it)
	{
		queryList.push_back(Segmentationer::doSegmentation(*it));
	}
	Q.batquery_AVL(queryList, res);
	clk -= clock();
	sprintf(cs, "共找到%4d个页面,用时%4dms", res.size(), SI::Max(clk, 0));
	temp.fromCstr(cs);
	sistr += temp;
	sistr += "\r\n";
	int NN = 0;
	for (linklist<IndexListNode>::Iterator it = res.begin(); it != res.end(); ++it)
	{
		itoa((*it).ppage->nid,cs,10);
		temp.fromCstr(cs);
		for (int k = 4 - temp.getsize(); k; --k) sistr += ' ';
		sistr += temp;
		sistr += "   ";
		sistr += (*it).ppage->title;
		sistr += " [";
		itoa((*it).ocr, cs, 10);
		temp.fromCstr(cs);
		sistr += temp;
		sistr += "]\r\n";
	}
	sistr += '\0';
	sistr.txUnicode();

	searchRes.Format(_T("%s"), sistr.getdata());
	UpdateData(FALSE);
}


void CguiDlg::OnBnClickedBthashsearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	SIString sistr;
	sistr.fromCString(searchInput);
	sistr.txGBK();
	SIStringList slist = sistr.split(' ');
	SIStringList queryList;
	SIString temp;
	linklist<IndexListNode> res;
	queryList._clear();
	sistr.clear();
	int clk = clock();
	for (SIStringList::Iterator it = slist.begin(); it != slist.end(); ++it)
	{
		queryList.push_back(Segmentationer::doSegmentation(*it));
	}
	Q.batquery_HASH(queryList, res);
	clk -= clock();
	sprintf(cs, "共找到%4d个页面,用时%4dms", res.size(), SI::Max(clk, 0));
	temp.fromCstr(cs);
	sistr += temp;
	sistr += "\r\n";
	int NN = 0;
	for (linklist<IndexListNode>::Iterator it = res.begin(); it != res.end(); ++it)
	{
		itoa((*it).ppage->nid, cs, 10);
		temp.fromCstr(cs);
		for (int k = 4 - temp.getsize(); k; --k) sistr += ' ';
		sistr += temp;
		sistr += "   ";
		sistr += (*it).ppage->title;
		sistr += " [";
		itoa((*it).ocr, cs, 10);
		temp.fromCstr(cs);
		sistr += temp;
		sistr += "]\r\n";
	}
	sistr += '\0';
	sistr.txUnicode();

	searchRes.Format(_T("%s"), sistr.getdata());
	UpdateData(FALSE);
}

UINT ThreadFunc(LPVOID lpParam)
{
	ThreadInfo* pinfo = (ThreadInfo*)lpParam;
	
	SI::initDictionary();
	
	#ifdef DOAVL
		pinfo->pQ->_init_AVL("info.csv");
	#endif
	#ifdef DOHASH
		pinfo->pQ->_init_HASH("info.csv");
	#endif
	
	return 0;
}