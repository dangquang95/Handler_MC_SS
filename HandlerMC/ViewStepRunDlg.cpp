// ViewStepRunDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "ViewStepRunDlg.h"
#include "afxdialogex.h"


// ViewStepRunDlg dialog

IMPLEMENT_DYNAMIC(ViewStepRunDlg, CDialogEx)

ViewStepRunDlg::ViewStepRunDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIEW_STEP, pParent)
{

}

ViewStepRunDlg::~ViewStepRunDlg()
{
}

void ViewStepRunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDB_NUFFER_LOADING, DataCaption[0]);
	DDX_Control(pDX, IDB_ROBOT_LOADING_CAM, DataCaption[1]);
	DDX_Control(pDX, IDB_ROBOT_LOADING_VISION, DataCaption[2]);
	DDX_Control(pDX, IDB_ROBOT_LOADING_TEST, DataCaption[3]);
	DDX_Control(pDX, IDB_RESULT_TEST, DataCaption[4]);
	DDX_Control(pDX, IDB_ROBOT_UNLOADING_TEST, DataCaption[5]);
	DDX_Control(pDX, IDB_ROBOT_MOVE_TRAY_OKNG, DataCaption[6]);
	DDX_Control(pDX, IDB_CHACK_TRAY_OK_NG_FULL, DataCaption[7]);

	DDX_Control(pDX, IDB_STEP_1, m_Step_1[0]);
	DDX_Control(pDX, IDB_STEP_2, m_Step_1[1]);
	DDX_Control(pDX, IDB_STEP_3, m_Step_1[2]);
	DDX_Control(pDX, IDB_STEP_4, m_Step_1[3]);
	DDX_Control(pDX, IDB_STEP_5, m_Step_1[4]);
	DDX_Control(pDX, IDB_STEP_6, m_Step_1[5]);

	DDX_Control(pDX, IDB_STEP_2_1, m_Step_2[0]);
	DDX_Control(pDX, IDB_STEP_2_2, m_Step_2[1]);
	DDX_Control(pDX, IDB_STEP_2_3, m_Step_2[2]);
	DDX_Control(pDX, IDB_STEP_2_4, m_Step_2[3]);
	DDX_Control(pDX, IDB_STEP_2_5, m_Step_2[4]);
	DDX_Control(pDX, IDB_STEP_2_6, m_Step_2[5]);
	DDX_Control(pDX, IDB_STEP_2_7, m_Step_2[6]);
	DDX_Control(pDX, IDB_STEP_2_8, m_Step_2[7]);
}


BEGIN_MESSAGE_MAP(ViewStepRunDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// ViewStepRunDlg message handlers
BEGIN_EVENTSINK_MAP(ViewStepRunDlg, CDialogEx)
	ON_EVENT(ViewStepRunDlg, IDB_EXIT1, DISPID_CLICK, ViewStepRunDlg::ClickExit1, VTS_NONE)
END_EVENTSINK_MAP()


void ViewStepRunDlg::ClickExit1()
{
	CDialog::OnCancel();
}

BOOL ViewStepRunDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	SetTimer(500, 50, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void ViewStepRunDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case 500:
	{
		SetCaptionMain();
		break;
	}

	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void ViewStepRunDlg::SetCaptionMain()
{
	//RGB(255, 0, 0)); mau do
	//RGB(0, 255, 0)); mau xanh luc
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	SetColorCaptionAll(pDoc->m_ActionStart);
	switch (pDoc->m_ActionStart)
	 {
	     case BufferLoading:
	     {
			ViewDataStep1BufferLoading();
	     	break;
	     }
	     case RobotLoadingCam:
	     {
			ViewDataStep1RobotLoadingCam();
	     	break;
	     }
	     case RobotLoadingVision:
		 {
			 ViewDataStep1RobotLoadingVision();
			 break;
		 }
		 case RobotLoadingfirst:
		 {
			 ViewDataStep1RobotLoadingTesterFirtRun();
			 break;
		 }
		 case UnloadingTrayOKFull:
		 {
			 ViewDataStep1UnloadingTrayOKFull();
			 break;
		 }
		 case RobotUnloadingAndLoadingTest:
		 {
			 ViewDataStep1RobotLoadingAndUnloadingRun();
			 break;
		 }
		 case RobotMoveTrayOKNG:
		 {
			 ViewDataStep1RobotMoveTrayOKNg();
			 break;
		 }
		 case CheckTrayOKNGFull:
		 {
			 ViewDataStep1CheckTrayOKFull();
			 break;
		 }
		 default:
			 break;		  
	}
}

//1.Loading
void ViewStepRunDlg::ViewDataStep1BufferLoading()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_Step_1[0].SetCaption("Z Loading Down");
	m_Step_1[1].SetCaption("Component Input");
	m_Step_1[2].SetCaption("Component Up");
	m_Step_1[3].SetCaption("Complete");
	m_Step_1[4].SetCaption("Not Use");
	m_Step_1[5].SetCaption("Not Use");

	SetColorCaptionStep1(pDoc->m_trayLoading);
	if (pDoc->m_trayLoading == 2)
	{
		ViewDataStep2BufferLoading();
	}
	else
	{
		ReSetCaptionStep2BufferLoading();
	}
}
void ViewStepRunDlg::ViewDataStep2BufferLoading()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	SetCaptionStep2BufferLoading();
	SetColorCaptionStep2(pDoc->m_countjog);
}

void ViewStepRunDlg::SetCaptionStep2BufferLoading()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	m_Step_2[0].SetCaption("Jog Up 1");
	m_Step_2[1].SetCaption("Jog Down 1");
	m_Step_2[2].SetCaption("Offset Up");
	m_Step_2[3].SetCaption("Z Loading Down");
	m_Step_2[4].SetCaption("Aline");
	m_Step_2[5].SetCaption("Not Use");
	m_Step_2[6].SetCaption("Not Use");
	m_Step_2[7].SetCaption("Not Use");
	SetColorCaptionStep2(pDoc->m_countjog);
}

//2.Robot loading Cam
void ViewStepRunDlg::ViewDataStep1RobotLoadingCam()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_Step_1[0].SetCaption("Tool 1 Loading Vision");
	m_Step_1[1].SetCaption("Tool 2 Loading Vision");
	m_Step_1[2].SetCaption("Complete");
	m_Step_1[3].SetCaption("Not Use");
	m_Step_1[4].SetCaption("Not Use");
	m_Step_1[5].SetCaption("Not Use");

	SetColorCaptionStep1(pDoc->m_RobotLoadingCAM);
	ViewDataStep2RobotLoadingCam();
}

void ViewStepRunDlg::ViewDataStep2RobotLoadingCam()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	m_Step_2[0].SetCaption("Search Point");
	m_Step_2[1].SetCaption("Send Data To Robot Up");
	m_Step_2[2].SetCaption("Wait Done Up");
	m_Step_2[3].SetCaption("Vaccum On");
	m_Step_2[4].SetCaption("Complete");
	m_Step_2[5].SetCaption("Cylinder Down");
	m_Step_2[6].SetCaption("Send Data To Robot Down");
	m_Step_2[7].SetCaption("Wait Done Down");

	if(pDoc->m_RobotLoadingCAM == 0)
	{
		SetColorCaptionStep2(pDoc->m_RobotLoadingCAMTool1);
	}
	if (pDoc->m_RobotLoadingCAM == 1)
	{
		SetColorCaptionStep2(pDoc->m_RobotLoadingCAMTool2);
	}
}

//3.Robot Loading Vision
void ViewStepRunDlg::ViewDataStep1RobotLoadingVision()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_Step_1[0].SetCaption("Run To Vision Tool1");
	m_Step_1[1].SetCaption("Run To Vision Tool2");
	m_Step_1[2].SetCaption("Send Data To Robot");
	m_Step_1[3].SetCaption("Wait Vision Done");
	m_Step_1[4].SetCaption("Complete");
	m_Step_1[5].SetCaption("Not Use");

	SetColorCaptionStep1(pDoc->m_LoadingVision);
	ReSetCaptionStep2BufferLoading();
}
//4.Robot Loading Tester Firt Run
void ViewStepRunDlg::ViewDataStep1RobotLoadingTesterFirtRun()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_Step_1[0].SetCaption("Loading Tester 1");
	m_Step_1[1].SetCaption("Loading Tester 2");
	m_Step_1[2].SetCaption("Loading Tester 3");
	m_Step_1[3].SetCaption("Loading Tester 4");
	m_Step_1[4].SetCaption("Complete");
	m_Step_1[5].SetCaption("Not Use");

	SetColorCaptionStep1(pDoc->m_LoadingTest);

	if (pDoc->m_NoLoadingTest == 2)
	{
		ViewDataStep2RobotLoadingTester();
	}
	else
	{
		ReSetCaptionStep2BufferLoading();
	}
}

void ViewStepRunDlg::ViewDataStep2RobotLoadingTester()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_Step_2[0].SetCaption("Tool 1 Robot Loading Socket Up");
	m_Step_2[1].SetCaption("Tool 2 Robot Loading Socket Up");
	m_Step_2[2].SetCaption("Wait Done Up");
	m_Step_2[3].SetCaption("Complete");
	m_Step_2[4].SetCaption("Tool And Robot Down");
	m_Step_2[5].SetCaption("Wait Done Down");
	m_Step_2[6].SetCaption("Action Socket");
	m_Step_2[7].SetCaption("Not Use");

	SetColorCaptionStep2(pDoc->m_SelectToolLoading);
	
}

void ViewStepRunDlg::ViewDataStep2RobotUnloadingTester()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_Step_2[0].SetCaption("Wait Result Test");
	m_Step_2[1].SetCaption("Tool 3 Robot Unloading Socket Up");
	m_Step_2[2].SetCaption("Tool 4 Robot Unloading Socket Up");
	m_Step_2[3].SetCaption("Done Down Complete");
	m_Step_2[4].SetCaption("Complete");
	m_Step_2[5].SetCaption("Wait Done Up");
	m_Step_2[6].SetCaption("Wait Done Down");
	m_Step_2[7].SetCaption("Not Use");

	SetColorCaptionStep2(pDoc->m_SocketUnloading);

}


//5.Unload Tray OK Full
void ViewStepRunDlg::ViewDataStep1UnloadingTrayOKFull()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_Step_1[0].SetCaption("Move To Tray");
	m_Step_1[1].SetCaption("Done - Vaccum On");
	m_Step_1[2].SetCaption("Move To Place");
	m_Step_1[3].SetCaption("Done - Vaccum Off");
	m_Step_1[4].SetCaption("Complete");
	m_Step_1[5].SetCaption("Not Use");

	SetColorCaptionStep1(pDoc->m_NoUnloadingFull);
	ReSetCaptionStep2BufferLoading();
}
//6.Robot Loading And Unloading Run
void ViewStepRunDlg::ViewDataStep1RobotLoadingAndUnloadingRun()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	switch (pDoc->m_NoRobotUnloadTest)
	{
	case 0:
	{
		m_Step_1[0].SetCaption("Unloading Socket 1");
		m_Step_1[1].SetCaption("Loading Soket 1");
		m_Step_1[2].SetCaption("Next Socket");
		m_Step_1[3].SetCaption("Not Use");
		m_Step_1[4].SetCaption("Not Use");
		m_Step_1[5].SetCaption("Not Use"); 

		SetColorCaptionStep1(pDoc->m_UnloadingLoading[0]);
		if (pDoc->m_UnloadingLoading[0] == 1)
		{
			ViewDataStep2RobotUnloadingTester();
		}
		if (pDoc->m_UnloadingLoading[0] == 2)
		{
			ViewDataStep2RobotLoadingTester();
		}
		break;
	}
	case 1:
	{
		m_Step_1[0].SetCaption("Unloading Socket 2");
		m_Step_1[1].SetCaption("Loading Soket 2");
		m_Step_1[2].SetCaption("Next Socket");
		m_Step_1[3].SetCaption("Not Use");
		m_Step_1[4].SetCaption("Not Use");
		m_Step_1[5].SetCaption("Not Use");

		SetColorCaptionStep1(pDoc->m_UnloadingLoading[1]);
		if (pDoc->m_UnloadingLoading[1] == 1)
		{
			ViewDataStep2RobotUnloadingTester();
		}
		if (pDoc->m_UnloadingLoading[1] == 2)
		{
			ViewDataStep2RobotLoadingTester();
		}
		break;
	}
	case 2:
	{
		m_Step_1[0].SetCaption("Unloading Socket 3");
		m_Step_1[1].SetCaption("Loading Soket 3");
		m_Step_1[2].SetCaption("Next Socket");
		m_Step_1[3].SetCaption("Not Use");
		m_Step_1[4].SetCaption("Not Use");
		m_Step_1[5].SetCaption("Not Use");

		SetColorCaptionStep1(pDoc->m_UnloadingLoading[2]);
		if (pDoc->m_UnloadingLoading[2] == 1)
		{
			ViewDataStep2RobotUnloadingTester();
		}
		if (pDoc->m_UnloadingLoading[2] == 2)
		{
			ViewDataStep2RobotLoadingTester();
		}
		break;
	}
	case 3:
	{
		m_Step_1[0].SetCaption("Unloading Socket 4");
		m_Step_1[1].SetCaption("Loading Soket 4");
		m_Step_1[2].SetCaption("Next Socket");
		m_Step_1[3].SetCaption("Not Use");
		m_Step_1[4].SetCaption("Not Use");
		m_Step_1[5].SetCaption("Not Use");

		SetColorCaptionStep1(pDoc->m_UnloadingLoading[3]);
		if (pDoc->m_UnloadingLoading[3] == 1)
		{
			ViewDataStep2RobotUnloadingTester();
		}
		if (pDoc->m_UnloadingLoading[3] == 2)
		{
			ViewDataStep2RobotLoadingTester();
		}
		break;
	}
	default:
		break;
	}

}
//7.Robot Move Tray OK NG
void ViewStepRunDlg::ViewDataStep1RobotMoveTrayOKNg()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_Step_1[0].SetCaption("Tool1 Unloading");
	m_Step_1[1].SetCaption("Tool2 Unloading");
	m_Step_1[2].SetCaption("Complete");
	m_Step_1[3].SetCaption("Not Use");
	m_Step_1[4].SetCaption("Not Use");
	m_Step_1[5].SetCaption("Not Use");

	SetColorCaptionStep1(pDoc->m_NorobotmovetrayOKNG);
	ReSetCaptionStep2BufferLoading();
}
//8.Check Tray OK Full
void ViewStepRunDlg::ViewDataStep1CheckTrayOKFull()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_Step_1[0].SetCaption("Not Use");
	m_Step_1[1].SetCaption("Not Use");
	m_Step_1[2].SetCaption("Not Use");
	m_Step_1[3].SetCaption("Not Use");
	m_Step_1[4].SetCaption("Not Use");
	m_Step_1[5].SetCaption("Not Use");

	ReSetCaptionStep2BufferLoading();
	//SetColorCaptionStep1(pDoc->m_NorobotmovetrayOKNG);
}
//
void ViewStepRunDlg::SetColorCaptionStep2(int m_data)
{
	for (int i = 0; i < 8; i++)
	{
		if (m_data == (i))
		{
			m_Step_2[i].SetBackColor(RGB(255, 0, 0));
		}
		else
		{
			m_Step_2[i].SetBackColor(RGB(0, 0, 255));
		}
	}
}
//
void ViewStepRunDlg::SetColorCaptionStep1(int m_data)
{
	for (int i = 0; i < 6; i++)
	{
		if (m_data == (i))
		{
			m_Step_1[i].SetBackColor(RGB(255, 0, 0));
		}
		else
		{
			m_Step_1[i].SetBackColor(RGB(0, 0, 255));
		}
	}
}
//
void ViewStepRunDlg::SetColorCaptionAll(int m_data)
{
	for (int i = 0; i < 8; i++)
	{
		if (m_data == (i + 1))
		{
			DataCaption[i].SetBackColor(RGB(255, 0, 0));
		}
		else
		{
			DataCaption[i].SetBackColor(RGB(0, 0, 255));
		}
	}
}
//
void ViewStepRunDlg::ReSetCaptionStep2BufferLoading()
{
	m_Step_2[0].SetCaption("Not Use");
	m_Step_2[1].SetCaption("Not Use");
	m_Step_2[2].SetCaption("Not Use");
	m_Step_2[3].SetCaption("Not Use");
	m_Step_2[4].SetCaption("Not Use");
	m_Step_2[5].SetCaption("Not Use");
	m_Step_2[6].SetCaption("Not Use");
	m_Step_2[7].SetCaption("Not Use");
	for (int i = 0; i < 8; i++)
	{
		m_Step_2[i].SetBackColor(RGB(0, 0, 255));
	}
}