// SelectAction.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "SelectAction.h"
#include "afxdialogex.h"
#include "HandlerMC.h"
#include "MainFrm.h"

// SelectAction dialog

IMPLEMENT_DYNAMIC(SelectAction, CDialogEx)

SelectAction::SelectAction(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SELECT_ACTION, pParent)
{

}

SelectAction::~SelectAction()
{
}

void SelectAction::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PHONE_TEST1, m_StatusPhone[0]);
	DDX_Control(pDX, IDC_PHONE_TEST2, m_StatusPhone[1]);
	DDX_Control(pDX, IDC_PHONE_TEST3, m_StatusPhone[2]);
	DDX_Control(pDX, IDC_PHONE_TEST4, m_StatusPhone[3]);
}


BEGIN_MESSAGE_MAP(SelectAction, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// SelectAction message handlers
BEGIN_EVENTSINK_MAP(SelectAction, CDialogEx)
	ON_EVENT(SelectAction, IDB_EXIT1, DISPID_CLICK, SelectAction::ClickExit1, VTS_NONE)
	ON_EVENT(SelectAction, IDC_PHONE_TEST1, DISPID_CLICK, SelectAction::ClickPhoneTest1, VTS_NONE)
	ON_EVENT(SelectAction, IDC_PHONE_TEST2, DISPID_CLICK, SelectAction::ClickPhoneTest2, VTS_NONE)
	ON_EVENT(SelectAction, IDC_PHONE_TEST3, DISPID_CLICK, SelectAction::ClickPhoneTest3, VTS_NONE)
	ON_EVENT(SelectAction, IDC_PHONE_TEST4, DISPID_CLICK, SelectAction::ClickPhoneTest4, VTS_NONE)
	ON_EVENT(SelectAction, IDB_SAVE_DATA, DISPID_CLICK, SelectAction::ClickSaveData, VTS_NONE)
END_EVENTSINK_MAP()


void SelectAction::ClickExit1()
{
	CDialog::OnCancel();
}


BOOL SelectAction::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	ViewData();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void SelectAction::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnTimer(nIDEvent);
}


void SelectAction::ClickPhoneTest1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	if (pDoc->m_DataTester[0].Action)
	{
		pDoc->m_DataTester[0].Action = false;
	}
	else
	{
		pDoc->m_DataTester[0].Action = true;
	}

	pDoc->m_NumberTesterAct = 0;
	for (int i = 0; i < 4; i++)
	{
		if (pDoc->m_DataTester[i].Action)
		{
			pDoc->m_NumberTesterAct++;
		}
	}
	ViewData();
}


void SelectAction::ClickPhoneTest2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (pDoc->m_DataTester[1].Action)
	{
		pDoc->m_DataTester[1].Action = false;
	}
	else
	{
		pDoc->m_DataTester[1].Action = true;
	}
	pDoc->m_NumberTesterAct = 0;
	for (int i = 0; i < 4; i++)
	{
		if (pDoc->m_DataTester[i].Action)
		{
			pDoc->m_NumberTesterAct++;
		}
	}
	ViewData();
}


void SelectAction::ClickPhoneTest3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (pDoc->m_DataTester[2].Action)
	{
		pDoc->m_DataTester[2].Action = false;
	}
	else
	{
		pDoc->m_DataTester[2].Action = true;
	}
	pDoc->m_NumberTesterAct = 0;
	for (int i = 0; i < 4; i++)
	{
		if (pDoc->m_DataTester[i].Action)
		{
			pDoc->m_NumberTesterAct++;
		}
	}
	ViewData();
}


void SelectAction::ClickPhoneTest4()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	if (pDoc->m_DataTester[3].Action)
	{
		pDoc->m_DataTester[3].Action = false;
	}
	else
	{
		pDoc->m_DataTester[3].Action = true;
	}
	pDoc->m_NumberTesterAct = 0;
	for (int i = 0; i < 4; i++)
	{
		if (pDoc->m_DataTester[i].Action)
		{
			pDoc->m_NumberTesterAct++;
		}
	}
	ViewData();
}

void SelectAction::ViewData()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	CString data;
	for (int i = 0; i < 4; i++)
	{
		if (pDoc->m_DataTester[i].Action)
		{
			data.Format("Phone %d On", i + 1);
			m_StatusPhone[i].SetCaption(data);
		}
		else
		{
			data.Format("Phone %d Off", i + 1);
			m_StatusPhone[i].SetCaption(data);
		}
	}
	pDoc->ActionOne = true;
}

void SelectAction::ClickSaveData()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CFileFind ffind;
	CString strPath = "DataSystem\\SelectPhone.dat";
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
		cstr.Format("Phone1			= %d \n", (int)pDoc->m_DataTester[0].Action);
		fn.WriteString(cstr);
		cstr.Format("Phone2			= %d \n", (int)pDoc->m_DataTester[1].Action);
		fn.WriteString(cstr);
		cstr.Format("Phone3			= %d \n", (int)pDoc->m_DataTester[2].Action);
		fn.WriteString(cstr);
		cstr.Format("Phone4			= %d \n", (int)pDoc->m_DataTester[3].Action);
		fn.WriteString(cstr);
		fn.Close();
	}

	AfxMessageBox("Save File Success");
}
