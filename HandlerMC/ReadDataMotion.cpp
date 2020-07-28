// ReadDataMotion.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "ReadDataMotion.h"
#include "afxdialogex.h"

#include "HandlerMCDoc.h"

// ReadDataMotion dialog

IMPLEMENT_DYNAMIC(ReadDataMotion, CDialogEx)

ReadDataMotion::ReadDataMotion(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_READ_DATA_MOTION, pParent)
{

}

ReadDataMotion::~ReadDataMotion()
{
}

void ReadDataMotion::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ViewData);
}


BEGIN_MESSAGE_MAP(ReadDataMotion, CDialogEx)
	
END_MESSAGE_MAP()


// ReadDataMotion message handlers
BOOL ReadDataMotion::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	InitListLog();

	if (pDoc->StatusOpenCard)//khoi tao cad
	{
		pDoc->ReadInforDataMotion();
		pDoc->ReadInforDataIO();
		LoadingDataMotion();		
	}


	
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void ReadDataMotion::InitListLog()
{
	//Creat table with 2 colum
	m_ViewData.InsertColumn(0, "Time", LVCFMT_LEFT, 80);
	m_ViewData.InsertColumn(1, "Action", LVCFMT_LEFT, 340);
	//AddLog("Start program!");
}
void ReadDataMotion::AddLog(CString content)
{
	SYSTEMTIME	st;
	GetLocalTime(&st);
	CString strHours, strMin, strSec;
	if (st.wHour < 10)
	{
		strHours.Format("0%d", st.wHour);
	}
	else {
		strHours.Format("%d", st.wHour);
	}
	if (st.wMinute < 10)
	{
		strMin.Format("0%d", st.wMinute);
	}
	else {
		strMin.Format("%d", st.wMinute);
	}
	if (st.wSecond < 10)
	{
		strSec.Format("0%d", st.wSecond);
	}
	else {
		strSec.Format("%d", st.wSecond);
	}
	CString m_strCurrentTime = "[" + strHours + ":" + strMin + ":" + strSec + "]";


	m_ViewData.InsertItem(0, m_strCurrentTime);
	m_ViewData.SetItemText(0, 1, content);

}
void ReadDataMotion::LoadingDataMotion()
{
	int k;
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	for (int i = 0; i < pDoc->DataInforCardMotion.size(); i++)
	{
		k = pDoc->DataInforCardMotion.size() - 1 - i;
		AddLog(pDoc->DataInforCardMotion.at(k));
	}
}

void ReadDataMotion::LoadingDataIO()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	for (int i = 0; i < pDoc->DataInforCardIO.size(); i++)
	{
		AddLog(pDoc->DataInforCardIO.at(i));
	}
}

BEGIN_EVENTSINK_MAP(ReadDataMotion, CDialogEx)
	ON_EVENT(ReadDataMotion, IDB_LOAD_DATA_MOTION, DISPID_CLICK, ReadDataMotion::ClickLoadDataMotion, VTS_NONE)
	ON_EVENT(ReadDataMotion, IDB_LOAD_DATA_IO, DISPID_CLICK, ReadDataMotion::ClickLoadDataIo, VTS_NONE)
END_EVENTSINK_MAP()


void ReadDataMotion::ClickLoadDataMotion()
{
	m_ViewData.DeleteAllItems();	
	LoadingDataMotion();
}


void ReadDataMotion::ClickLoadDataIo()
{
	m_ViewData.DeleteAllItems();
	LoadingDataIO();

}


