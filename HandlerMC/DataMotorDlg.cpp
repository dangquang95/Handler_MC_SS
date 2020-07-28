// DataMotorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "DataMotorDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"

// DataMotorDlg dialog

IMPLEMENT_DYNAMIC(DataMotorDlg, CDialogEx)

DataMotorDlg::DataMotorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DATA_MOTOR, pParent)
{

}

DataMotorDlg::~DataMotorDlg()
{
}

void DataMotorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACC_DEC, m_AccDec);
	DDX_Control(pDX, IDC_SPEED_JOG1, m_SpeedJog1);
	DDX_Control(pDX, IDC_SPEED_JOG2, m_SpeedJog2);
	DDX_Control(pDX, IDC_SPEED_JOG3, m_SpeedJog3);
	DDX_Control(pDX, IDC_SPEED_ORIGIN_Z1, m_SpeedOriginZ1);
	DDX_Control(pDX, IDC_SPEED_ORIGIN_Z2, m_SpeedOriginZ2);
	DDX_Control(pDX, IDC_SPEED_RUN_Z1, m_SpeedRunZ1);
	DDX_Control(pDX, IDC_SPEED_RUN_Z2, m_SpeedRunZ2);
}


BEGIN_MESSAGE_MAP(DataMotorDlg, CDialogEx)
END_MESSAGE_MAP()


// DataMotorDlg message handlers


void DataMotorDlg::ViewDataMotor()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CString DataView;

	DataView.Format("%lf", pDoc->DataMotor.Acc);
	m_AccDec.SetCaption(DataView);

	DataView.Format("%lf", pDoc->DataMotor.SpeedJog1);
	m_SpeedJog1.SetCaption(DataView);

	DataView.Format("%lf", pDoc->DataMotor.SpeedJog2);
	m_SpeedJog2.SetCaption(DataView);

	DataView.Format("%lf", pDoc->DataMotor.SpeedJog3);
	m_SpeedJog3.SetCaption(DataView);

	DataView.Format("%lf", pDoc->DataMotor.SpeedOriginX);
	m_SpeedOriginZ1.SetCaption(DataView);

	DataView.Format("%lf", pDoc->DataMotor.SpeedOriginY);
	m_SpeedOriginZ2.SetCaption(DataView);

	DataView.Format("%lf", pDoc->DataMotor.SpeedRunAxisX);
	m_SpeedRunZ1.SetCaption(DataView);

	DataView.Format("%lf", pDoc->DataMotor.SpeedRunAxisY);
	m_SpeedRunZ2.SetCaption(DataView);
}

BOOL DataMotorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ViewDataMotor();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
BEGIN_EVENTSINK_MAP(DataMotorDlg, CDialogEx)
	ON_EVENT(DataMotorDlg, IDC_ACC_DEC, DISPID_CLICK, DataMotorDlg::ClickAccDec, VTS_NONE)
	ON_EVENT(DataMotorDlg, IDC_SPEED_JOG1, DISPID_CLICK, DataMotorDlg::ClickSpeedJog1, VTS_NONE)
	ON_EVENT(DataMotorDlg, IDC_SPEED_JOG2, DISPID_CLICK, DataMotorDlg::ClickSpeedJog2, VTS_NONE)
	ON_EVENT(DataMotorDlg, IDC_SPEED_JOG3, DISPID_CLICK, DataMotorDlg::ClickSpeedJog3, VTS_NONE)
	ON_EVENT(DataMotorDlg, IDC_SPEED_ORIGIN_Z1, DISPID_CLICK, DataMotorDlg::ClickSpeedOriginZ1, VTS_NONE)
	ON_EVENT(DataMotorDlg, IDC_SPEED_ORIGIN_Z2, DISPID_CLICK, DataMotorDlg::ClickSpeedOriginZ2, VTS_NONE)
	ON_EVENT(DataMotorDlg, IDC_SPEED_RUN_Z1, DISPID_CLICK, DataMotorDlg::ClickSpeedRunZ1, VTS_NONE)
	ON_EVENT(DataMotorDlg, IDC_SPEED_RUN_Z2, DISPID_CLICK, DataMotorDlg::ClickSpeedRunZ2, VTS_NONE)
	ON_EVENT(DataMotorDlg, IDB_EXIT1, DISPID_CLICK, DataMotorDlg::ClickExit1, VTS_NONE)
	ON_EVENT(DataMotorDlg, IDB_SAVE_DATA, DISPID_CLICK, DataMotorDlg::ClickSaveData, VTS_NONE)
END_EVENTSINK_MAP()


void DataMotorDlg::ClickAccDec()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();
	pDoc->DataMotor.Acc = (int)pDoc->NumberReturn;
	ViewDataMotor();
}


void DataMotorDlg::ClickSpeedJog1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();
	pDoc->DataMotor.SpeedJog1 = (int)pDoc->NumberReturn;
	ViewDataMotor();

}


void DataMotorDlg::ClickSpeedJog2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();
	pDoc->DataMotor.SpeedJog2 = (int)pDoc->NumberReturn;
	ViewDataMotor();
}


void DataMotorDlg::ClickSpeedJog3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();
	pDoc->DataMotor.SpeedJog3 = (int)pDoc->NumberReturn;
	ViewDataMotor();
}


void DataMotorDlg::ClickSpeedOriginZ1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();
	pDoc->DataMotor.SpeedOriginX = (int)pDoc->NumberReturn;
	ViewDataMotor();
}


void DataMotorDlg::ClickSpeedOriginZ2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();
	pDoc->DataMotor.SpeedOriginY = (int)pDoc->NumberReturn;
	ViewDataMotor();
}


void DataMotorDlg::ClickSpeedRunZ1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();
	pDoc->DataMotor.SpeedRunAxisX = (int)pDoc->NumberReturn;
	ViewDataMotor();
}


void DataMotorDlg::ClickSpeedRunZ2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();
	pDoc->DataMotor.SpeedRunAxisY = (int)pDoc->NumberReturn;
	ViewDataMotor();
}


void DataMotorDlg::ClickExit1()
{
	CDialog::OnCancel();
}


void DataMotorDlg::ClickSaveData()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CFileFind ffind;
	CString strPath = "DataSystem\\DataMotor.dat";
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
		cstr.Format("AccDec				= %d \n", (int)pDoc->DataMotor.Acc);
		fn.WriteString(cstr);
		cstr.Format("SpeedJog1			= %d \n", (int)pDoc->DataMotor.SpeedJog1);
		fn.WriteString(cstr);
		cstr.Format("SpeedJog2			= %d \n", (int)pDoc->DataMotor.SpeedJog2);
		fn.WriteString(cstr);
		cstr.Format("SpeedJog3			= %d \n", (int)pDoc->DataMotor.SpeedJog3);
		fn.WriteString(cstr);
		cstr.Format("SpeedOriginZ1	    = %d \n", (int)pDoc->DataMotor.SpeedOriginX);
		fn.WriteString(cstr);
		cstr.Format("SpeedOriginZ2		= %d \n", (int)pDoc->DataMotor.SpeedOriginY);
		fn.WriteString(cstr);
		cstr.Format("SpeedRunZ1			= %d \n", (int)pDoc->DataMotor.SpeedRunAxisX);
		fn.WriteString(cstr);
		cstr.Format("SpeedRunZ2			= %d \n", (int)pDoc->DataMotor.SpeedRunAxisY);
		fn.WriteString(cstr);
		fn.Close();
	}

	AfxMessageBox("Save File Success");
}
