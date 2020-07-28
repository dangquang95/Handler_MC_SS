// DlgDelayVaccum.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "DlgDelayVaccum.h"
#include "afxdialogex.h"


// DlgDelayVaccum dialog

IMPLEMENT_DYNAMIC(DlgDelayVaccum, CDialogEx)

DlgDelayVaccum::DlgDelayVaccum(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DELAY_VACCUM, pParent)
{

}

DlgDelayVaccum::~DlgDelayVaccum()
{
}

void DlgDelayVaccum::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VACCUM_TOOL_1, m_DataDelayVaccumToolRobot1);
	DDX_Control(pDX, IDC_VACCUM_TOOL_2, m_DataDelayVaccumToolRobot2);
	DDX_Control(pDX, IDC_VACCUM_TOOL_3, m_DataDelayVaccumToolRobot3);
	DDX_Control(pDX, IDC_VACCUM_TOOL_4, m_DataDelayVaccumToolRobot4);
	DDX_Control(pDX, IDC_VACCUM_SOCKET_1, m_DataDelayVaccumSocket1);
	DDX_Control(pDX, IDC_VACCUM_SOCKET_2, m_DataDelayVaccumSocket2);
	DDX_Control(pDX, IDC_VACCUM_SOCKET_3, m_DataDelayVaccumSocket3);
	DDX_Control(pDX, IDC_VACCUM_SOCKET_4, m_DataDelayVaccumSocket4);
	DDX_Control(pDX, IDC_VACCUM_TRAY, m_DataDelayVaccumTray);
}


BEGIN_MESSAGE_MAP(DlgDelayVaccum, CDialogEx)
END_MESSAGE_MAP()


// DlgDelayVaccum message handlers
BEGIN_EVENTSINK_MAP(DlgDelayVaccum, CDialogEx)
	ON_EVENT(DlgDelayVaccum, IDB_EXIT1, DISPID_CLICK, DlgDelayVaccum::ClickExit1, VTS_NONE)
	ON_EVENT(DlgDelayVaccum, IDC_VACCUM_TOOL_1, DISPID_CLICK, DlgDelayVaccum::ClickVaccumTool1, VTS_NONE)
	ON_EVENT(DlgDelayVaccum, IDC_VACCUM_TOOL_2, DISPID_CLICK, DlgDelayVaccum::ClickVaccumTool2, VTS_NONE)
	ON_EVENT(DlgDelayVaccum, IDC_VACCUM_TOOL_3, DISPID_CLICK, DlgDelayVaccum::ClickVaccumTool3, VTS_NONE)
	ON_EVENT(DlgDelayVaccum, IDC_VACCUM_TOOL_4, DISPID_CLICK, DlgDelayVaccum::ClickVaccumTool4, VTS_NONE)
	ON_EVENT(DlgDelayVaccum, IDC_VACCUM_SOCKET_1, DISPID_CLICK, DlgDelayVaccum::ClickVaccumSocket1, VTS_NONE)
	ON_EVENT(DlgDelayVaccum, IDC_VACCUM_SOCKET_2, DISPID_CLICK, DlgDelayVaccum::ClickVaccumSocket2, VTS_NONE)
	ON_EVENT(DlgDelayVaccum, IDC_VACCUM_SOCKET_3, DISPID_CLICK, DlgDelayVaccum::ClickVaccumSocket3, VTS_NONE)
	ON_EVENT(DlgDelayVaccum, IDC_VACCUM_SOCKET_4, DISPID_CLICK, DlgDelayVaccum::ClickVaccumSocket4, VTS_NONE)
	ON_EVENT(DlgDelayVaccum, IDC_VACCUM_TRAY, DISPID_CLICK, DlgDelayVaccum::ClickVaccumTray, VTS_NONE)
	ON_EVENT(DlgDelayVaccum, IDB_SAVE_DATA, DISPID_CLICK, DlgDelayVaccum::ClickSaveData, VTS_NONE)
END_EVENTSINK_MAP()


void DlgDelayVaccum::ClickExit1()
{
	CDialog::OnCancel();
}


void DlgDelayVaccum::ClickVaccumTool1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayVaccumToolRobot1 = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayVaccumToolRobot1);
	m_DataDelayVaccumToolRobot1.SetCaption(m_data);
}


void DlgDelayVaccum::ClickVaccumTool2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayVaccumToolRobot2 = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayVaccumToolRobot2);
	m_DataDelayVaccumToolRobot2.SetCaption(m_data);
}


void DlgDelayVaccum::ClickVaccumTool3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayVaccumToolRobot3 = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayVaccumToolRobot3);
	m_DataDelayVaccumToolRobot3.SetCaption(m_data);
}


void DlgDelayVaccum::ClickVaccumTool4()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayVaccumToolRobot4 = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayVaccumToolRobot4);
	m_DataDelayVaccumToolRobot4.SetCaption(m_data);
}


void DlgDelayVaccum::ClickVaccumSocket1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayVaccumSocket1 = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayVaccumSocket1);
	m_DataDelayVaccumSocket1.SetCaption(m_data);
}


void DlgDelayVaccum::ClickVaccumSocket2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayVaccumSocket2 = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayVaccumSocket2);
	m_DataDelayVaccumSocket2.SetCaption(m_data);
}


void DlgDelayVaccum::ClickVaccumSocket3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayVaccumSocket3 = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayVaccumSocket3);
	m_DataDelayVaccumSocket3.SetCaption(m_data);
}


void DlgDelayVaccum::ClickVaccumSocket4()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayVaccumSocket4 = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayVaccumSocket4);
	m_DataDelayVaccumSocket4.SetCaption(m_data);
}


void DlgDelayVaccum::ClickVaccumTray()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayVaccumTrayRobot = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayVaccumTrayRobot);
	m_DataDelayVaccumTray.SetCaption(m_data);
}

void DlgDelayVaccum::SetViewData()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CString m_data;

	m_data.Format("%d", pDoc->DelayVaccumToolRobot1);
	m_DataDelayVaccumToolRobot1.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayVaccumToolRobot2);
	m_DataDelayVaccumToolRobot2.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayVaccumToolRobot3);
	m_DataDelayVaccumToolRobot3.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayVaccumToolRobot4);
	m_DataDelayVaccumToolRobot4.SetCaption(m_data);

	m_data.Format("%d", pDoc->DelayVaccumSocket1);
	m_DataDelayVaccumSocket1.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayVaccumSocket2);
	m_DataDelayVaccumSocket2.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayVaccumSocket3);
	m_DataDelayVaccumSocket3.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayVaccumSocket4);
	m_DataDelayVaccumSocket4.SetCaption(m_data);

	m_data.Format("%d", pDoc->DelayVaccumTrayRobot);
	m_DataDelayVaccumTray.SetCaption(m_data);
}

BOOL DlgDelayVaccum::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetViewData();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void DlgDelayVaccum::ClickSaveData()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CFileFind ffind;
	CString strPath = "DataSystem\\DataDelayVaccum.dat";
	if (ffind.FindFile((LPCTSTR)strPath) == FALSE)
	{
		AfxMessageBox("Not find");
	}
	else
	{
		CStdioFile fn;
		fn.Open(strPath, CFile::modeReadWrite);
		fn.WriteString("[Data]\n\n");
		CString cstr;
		cstr.Format("DelayVaccumTool1Robot			 = %d \n", pDoc->DelayVaccumToolRobot1);
		fn.WriteString(cstr);
		cstr.Format("DelayVaccumTool2Robot			 = %d \n", pDoc->DelayVaccumToolRobot2);
		fn.WriteString(cstr);
		cstr.Format("DelayVaccumTool3Robot			 = %d \n", pDoc->DelayVaccumToolRobot3);
		fn.WriteString(cstr);
		cstr.Format("DelayVaccumTool4Robot			 = %d \n", pDoc->DelayVaccumToolRobot4);
		fn.WriteString(cstr);

		cstr.Format("DelayVaccumSocket1			 = %d \n", pDoc->DelayVaccumSocket1);
		fn.WriteString(cstr);
		cstr.Format("DelayVaccumSocket2			 = %d \n", pDoc->DelayVaccumSocket2);
		fn.WriteString(cstr);
		cstr.Format("DelayVaccumSocket3			 = %d \n", pDoc->DelayVaccumSocket3);
		fn.WriteString(cstr);
		cstr.Format("DelayVaccumSocket4			 = %d \n", pDoc->DelayVaccumSocket4);
		fn.WriteString(cstr);

		cstr.Format("m_DataDelayVaccumTray			 = %d \n", pDoc->DelayVaccumTrayRobot);
		fn.WriteString(cstr);

		fn.Close();
		AfxMessageBox("Save Data Successful");
	}

}
