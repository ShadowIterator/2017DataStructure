
// guiDlg.cpp : ʵ���ļ�
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


// CguiDlg �Ի���
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


// CguiDlg ��Ϣ�������

BOOL CguiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CguiDlg::OnPaint()
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
HCURSOR CguiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CguiDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CguiDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CguiDlg::OnEnChangeEcsearchinput()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CguiDlg::OnBnClickedBtshowpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	SIString sistr;
	SIString temp;
	PageInfo* pages;
	sistr.clear();
	if (idInput > 4000 || idInput <= 0) sistr = "No Result";
	else
	{
		pages = Q.getPage(idInput);
		
		sistr += "[����ID]   ";
		itoa(pages->nid, cs, 10);
		temp.fromCstr(cs);
		sistr += temp;
		sistr += "\r\n";

		sistr += "[���]     ";
		itoa(pages->id, cs, 10);
		temp.fromCstr(cs);
		sistr += temp;
		sistr += "\r\n";

		sistr += "[��ַ]     ";
		sistr += pages->url;
		sistr += "\r\n";
		sistr += "[��������] ";
		sistr += pages->genType;
		sistr += "\r\n";
		sistr += "[����С��] ";
		sistr += pages->spcType;
		sistr += "\r\n";
		sistr += "[��������] ";
		sistr += pages->title;
		sistr += "\r\n";
		sistr += "\r\n";
		sistr += "[��������] ";
		sistr += pages->date;
		sistr += "\r\n";
		sistr += "[������]   ";
		sistr += pages->author;
		sistr += "\r\n";
		sistr += "[��������] ";
		sistr += pages->pref;
		sistr += "\r\n";
		sistr += "[��������] ";
		sistr += pages->contents;
	}
	sistr += '\0';
	sistr.txUnicode();

	pageInfo.Format(_T("%s"), sistr.getdata());

	UpdateData(FALSE);

}


void CguiDlg::OnBnClickedBtavlsearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	sprintf(cs, "���ҵ�%4d��ҳ��,��ʱ%4dms", res.size(), SI::Max(clk, 0));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	sprintf(cs, "���ҵ�%4d��ҳ��,��ʱ%4dms", res.size(), SI::Max(clk, 0));
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