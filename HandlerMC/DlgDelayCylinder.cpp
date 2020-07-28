// DlgDelayCylinder.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "DlgDelayCylinder.h"
#include "afxdialogex.h"


// DlgDelayCylinder dialog

IMPLEMENT_DYNAMIC(DlgDelayCylinder, CDialogEx)

DlgDelayCylinder::DlgDelayCylinder(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DELAY_CYLINDER, pParent)
{

}

DlgDelayCylinder::~DlgDelayCylinder()
{
}

void DlgDelayCylinder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CYLINDER_TOOL1_ROBOT, m_Tool1_Robot);
	DDX_Control(pDX, IDC_CYLINDER_TOOL2_ROBOT, m_Tool2_Robot);
	DDX_Control(pDX, IDC_CYLINDER_TOOL3_ROBOT, m_Tool3_Robot);
	DDX_Control(pDX, IDC_CYLINDER_TOOL4_ROBOT, m_Tool4_Robot);
	DDX_Control(pDX, IDC_CYLINDER_SOCKET1_FWRV, m_Socket1_FwRV);
	DDX_Control(pDX, IDC_CYLINDER_SOCKET2_FWRV, m_Socket2_FwRV);
	DDX_Control(pDX, IDC_CYLINDER_SOCKET3_FWRV, m_Socket3_FwRV);
	DDX_Control(pDX, IDC_CYLINDER_SOCKET4_FWRV, m_Socket4_FwRV);
	DDX_Control(pDX, IDC_CYLINDER_SOCKET1_UPDOWN, m_Socket1_UpDown);
	DDX_Control(pDX, IDC_CYLINDER_SOCKET2_UPDOWN, m_Socket2_UpDown);
	DDX_Control(pDX, IDC_CYLINDER_SOCKET3_UPDOWN, m_Socket3_UpDown);
	DDX_Control(pDX, IDC_CYLINDER_SOCKET4_UPDOWN, m_Socket4_UpDown);
	DDX_Control(pDX, IDC_CYLINDER_HANDELER, m_Cylinder_Handler);
	DDX_Control(pDX, IDC_CYLINDER_ALINE, m_Cylinder_Aline);
	DDX_Control(pDX, IDC_CYLINDER_ROTATION, m_Cylinder_Rotation);
	DDX_Control(pDX, IDC_CYLINDER_STACK, m_Cylinder_Stack);
}


BEGIN_MESSAGE_MAP(DlgDelayCylinder, CDialogEx)
END_MESSAGE_MAP()


// DlgDelayCylinder message handlers
BEGIN_EVENTSINK_MAP(DlgDelayCylinder, CDialogEx)
	ON_EVENT(DlgDelayCylinder, IDB_EXIT1, DISPID_CLICK, DlgDelayCylinder::ClickExit1, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDB_SAVE_DATA, DISPID_CLICK, DlgDelayCylinder::ClickSaveData, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_TOOL1_ROBOT, DISPID_CLICK, DlgDelayCylinder::ClickCylinderTool1Robot, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_TOOL2_ROBOT, DISPID_CLICK, DlgDelayCylinder::ClickCylinderTool2Robot, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_TOOL3_ROBOT, DISPID_CLICK, DlgDelayCylinder::ClickCylinderTool3Robot, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_TOOL4_ROBOT, DISPID_CLICK, DlgDelayCylinder::ClickCylinderTool4Robot, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_SOCKET1_FWRV, DISPID_CLICK, DlgDelayCylinder::ClickCylinderSocket1Fwrv, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_SOCKET2_FWRV, DISPID_CLICK, DlgDelayCylinder::ClickCylinderSocket2Fwrv, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_SOCKET3_FWRV, DISPID_CLICK, DlgDelayCylinder::ClickCylinderSocket3Fwrv, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_SOCKET4_FWRV, DISPID_CLICK, DlgDelayCylinder::ClickCylinderSocket4Fwrv, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_SOCKET1_UPDOWN, DISPID_CLICK, DlgDelayCylinder::ClickCylinderSocket1Updown, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_SOCKET2_UPDOWN, DISPID_CLICK, DlgDelayCylinder::ClickCylinderSocket2Updown, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_SOCKET3_UPDOWN, DISPID_CLICK, DlgDelayCylinder::ClickCylinderSocket3Updown, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_SOCKET4_UPDOWN, DISPID_CLICK, DlgDelayCylinder::ClickCylinderSocket4Updown, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_HANDELER, DISPID_CLICK, DlgDelayCylinder::ClickCylinderHandeler, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_ALINE, DISPID_CLICK, DlgDelayCylinder::ClickCylinderAline, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_ROTATION, DISPID_CLICK, DlgDelayCylinder::ClickCylinderRotation, VTS_NONE)
	ON_EVENT(DlgDelayCylinder, IDC_CYLINDER_STACK, DISPID_CLICK, DlgDelayCylinder::ClickCylinderStack, VTS_NONE)
END_EVENTSINK_MAP()


void DlgDelayCylinder::ClickExit1()
{
	CDialog::OnCancel();
}


void DlgDelayCylinder::ClickSaveData()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CFileFind ffind;
	CString strPath = "DataSystem\\DataDelayCylinder.dat";
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
		cstr.Format("DelayCylinderTool1Robot			 = %d \n", pDoc->DelayCylinderTool1Robot);
		fn.WriteString(cstr);
		cstr.Format("DelayCylinderTool2Robot			 = %d \n", pDoc->DelayCylinderTool2Robot);
		fn.WriteString(cstr);
		cstr.Format("DelayCylinderTool3Robot			 = %d \n", pDoc->DelayCylinderTool3Robot);
		fn.WriteString(cstr);
		cstr.Format("DelayCylinderTool4Robot			 = %d \n", pDoc->DelayCylinderTool4Robot);
		fn.WriteString(cstr);

		cstr.Format("DelayCylinderSocket1FwRv			 = %d \n", pDoc->DelayCylinderSocket1FwRv);
		fn.WriteString(cstr);
		cstr.Format("DelayCylinderSocket2FwRv			 = %d \n", pDoc->DelayCylinderSocket2FwRv);
		fn.WriteString(cstr);
		cstr.Format("DelayCylinderSocket3FwRv			 = %d \n", pDoc->DelayCylinderSocket3FwRv);
		fn.WriteString(cstr);
		cstr.Format("DelayCylinderSocket4FwRv			 = %d \n", pDoc->DelayCylinderSocket4FwRv);
		fn.WriteString(cstr);

		cstr.Format("DelayCylinderSocket1UpDown			 = %d \n", pDoc->DelayCylinderSocket1UpDown);
		fn.WriteString(cstr);
		cstr.Format("DelayCylinderSocket2UpDown			 = %d \n", pDoc->DelayCylinderSocket2UpDown);
		fn.WriteString(cstr);
		cstr.Format("DelayCylinderSocket3UpDown			 = %d \n", pDoc->DelayCylinderSocket3UpDown);
		fn.WriteString(cstr);
		cstr.Format("DelayCylinderSocket4UpDown			 = %d \n", pDoc->DelayCylinderSocket4UpDown);
		fn.WriteString(cstr);

		cstr.Format("DelayCylinderHandler			     = %d \n", pDoc->DelayCylinderHandler);
		fn.WriteString(cstr);
		cstr.Format("DelayCylinderAline			         = %d \n", pDoc->DelayCylinderAline);
		fn.WriteString(cstr);
		cstr.Format("DelayCylinderRotation			     = %d \n", pDoc->DelayCylinderRotation);
		fn.WriteString(cstr);
		cstr.Format("DelayCylinderStack			         = %d \n", pDoc->DelayCylinderStack);
		fn.WriteString(cstr);

		fn.Close();
		AfxMessageBox("Save Data Successful");
	}

}

void DlgDelayCylinder::ViewDataDelay()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();


	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderTool1Robot);
	m_Tool1_Robot.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderTool2Robot);
	m_Tool2_Robot.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderTool3Robot);
	m_Tool3_Robot.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderTool4Robot);
	m_Tool4_Robot.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderSocket1FwRv);
	m_Socket1_FwRV.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderSocket2FwRv);
	m_Socket2_FwRV.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderSocket3FwRv);
	m_Socket3_FwRV.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderSocket4FwRv);
	m_Socket4_FwRV.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderSocket1UpDown);
	m_Socket1_UpDown.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderSocket2UpDown);
	m_Socket2_UpDown.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderSocket3UpDown);
	m_Socket3_UpDown.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderSocket4UpDown);
	m_Socket4_UpDown.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderHandler);
	m_Cylinder_Handler.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderAline);
	m_Cylinder_Aline.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderRotation);
	m_Cylinder_Rotation.SetCaption(m_data);
	m_data.Format("%d", pDoc->DelayCylinderStack);
	m_Cylinder_Stack.SetCaption(m_data);
}

void DlgDelayCylinder::ClickCylinderTool1Robot()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderTool1Robot = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderTool1Robot);
	m_Tool1_Robot.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderTool2Robot()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderTool2Robot = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderTool2Robot);
	m_Tool2_Robot.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderTool3Robot()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderTool3Robot = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderTool3Robot);
	m_Tool3_Robot.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderTool4Robot()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderTool4Robot = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderTool4Robot);
	m_Tool4_Robot.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderSocket1Fwrv()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderSocket1FwRv = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderSocket1FwRv);
	m_Socket1_FwRV.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderSocket2Fwrv()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderSocket2FwRv = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderSocket2FwRv);
	m_Socket2_FwRV.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderSocket3Fwrv()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderSocket3FwRv = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderSocket3FwRv);
	m_Socket3_FwRV.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderSocket4Fwrv()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderSocket4FwRv = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderSocket4FwRv);
	m_Socket4_FwRV.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderSocket1Updown()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderSocket1UpDown = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderSocket1UpDown);
	m_Socket1_UpDown.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderSocket2Updown()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderSocket2UpDown = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderSocket2UpDown);
	m_Socket2_UpDown.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderSocket3Updown()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderSocket3UpDown = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderSocket3UpDown);
	m_Socket3_UpDown.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderSocket4Updown()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderSocket4UpDown = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderSocket4UpDown);
	m_Socket4_UpDown.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderHandeler()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderHandler = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderHandler);
	m_Cylinder_Handler.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderAline()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderAline = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderAline);
	m_Cylinder_Aline.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderRotation()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderRotation = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderRotation);
	m_Cylinder_Rotation.SetCaption(m_data);
}


void DlgDelayCylinder::ClickCylinderStack()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->DelayCylinderStack = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", pDoc->DelayCylinderStack);
	m_Cylinder_Stack.SetCaption(m_data);
}


BOOL DlgDelayCylinder::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ViewDataDelay();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
