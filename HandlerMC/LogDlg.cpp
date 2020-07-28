// LogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "LogDlg.h"
#include "afxdialogex.h"


// LogDlg dialog

IMPLEMENT_DYNAMIC(LogDlg, CDialogEx)

LogDlg::LogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOG_MAIN_FORM, pParent)
{

}

LogDlg::~LogDlg()
{
}

void LogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VIEW_LOG, m_ListViewLog);
}


BEGIN_MESSAGE_MAP(LogDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// LogDlg message handlers


BOOL LogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SaveControlPosition();
	InitListLog();
	SetTimer(10, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void LogDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	ChangeControlPosition();
}
void LogDlg::SaveControlPosition()
{
	CRect rect;
	TCHAR sz[256];

	GetClientRect(rect);
	m_PositionArray.Add(rect);

	CWnd* pWnd = GetTopWindow();

	pWnd->GetWindowText(sz, 256);
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);
	m_PositionArray.Add(rect);

	CWnd* tmpWnd = pWnd->GetNextWindow(GW_HWNDNEXT);

	while (tmpWnd != NULL)
	{
		tmpWnd->GetWindowText(sz, 256);
		tmpWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		m_PositionArray.Add(rect);
		tmpWnd = tmpWnd->GetNextWindow(GW_HWNDNEXT);
	}
}

void LogDlg::ChangeControlPosition()
{

	if (m_PositionArray.GetSize() <= 0)
		return;

	CRect rect, rect_org;
	int i = 0;

	rect_org = m_PositionArray.GetAt(i);
	i++;

	GetClientRect(rect);

	double dXRatio = ((double)rect.Width()) / ((double)rect_org.Width());
	double dYRatio = ((double)rect.Height()) / ((double)rect_org.Height());

	CWnd* pWnd = GetTopWindow();

	rect = m_PositionArray.GetAt(i);
	i++;

	pWnd->MoveWindow((int)(rect.left*dXRatio), (int)(rect.top*dYRatio),
		(int)(rect.Width()*dXRatio), (int)(rect.Height()*dYRatio));

	CWnd* tmpWnd = pWnd->GetNextWindow(GW_HWNDNEXT);

	while (tmpWnd != NULL)
	{
		rect = m_PositionArray.GetAt(i);
		i++;
		tmpWnd->MoveWindow((int)(rect.left*dXRatio), (int)(rect.top*dYRatio),
			(int)(rect.Width()*dXRatio), (int)(rect.Height()*dYRatio));

		tmpWnd = tmpWnd->GetNextWindow(GW_HWNDNEXT);
	}
}


void LogDlg::InitListLog()
{
	//Creat table with 2 colum
	m_ListViewLog.InsertColumn(0, "Time", LVCFMT_LEFT, 80);
	m_ListViewLog.InsertColumn(1, "Action", LVCFMT_LEFT, 600);
	AddLog("Start program!");
}
void LogDlg::AddLog(CString content)
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


	m_ListViewLog.InsertItem(0, m_strCurrentTime);
	m_ListViewLog.SetItemText(0, 1, content);

}


void LogDlg::OnTimer(UINT_PTR nIDEvent)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();


	switch (nIDEvent)
	{
	case 10:
	{
		if (pDoc->ReadSignalSensor())
		{
			AddLog(pDoc->MessengerData);
		}
		break;
	}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
BEGIN_EVENTSINK_MAP(LogDlg, CDialogEx)
	ON_EVENT(LogDlg, IDB_STEP_DISP_LOG, DISPID_CLICK, LogDlg::ClickStepDispLog, VTS_NONE)
END_EVENTSINK_MAP()


void LogDlg::ClickStepDispLog()
{
	ViewStepRunDlg ViewDlg;
	ViewDlg.DoModal();
}
