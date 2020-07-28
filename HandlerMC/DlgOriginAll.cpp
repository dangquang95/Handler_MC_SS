// DlgOriginAll.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "DlgOriginAll.h"
#include "afxdialogex.h"


// DlgOriginAll dialog

IMPLEMENT_DYNAMIC(DlgOriginAll, CDialogEx)

DlgOriginAll::DlgOriginAll(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ORIGINALL, pParent)
{

}

DlgOriginAll::~DlgOriginAll()
{
}

void DlgOriginAll::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CRURRENT_POS_Z1, m_CurrentPosZ1);
	DDX_Control(pDX, IDC_CRURRENT_POS_Z2, m_CurrentPosZ2);
	DDX_Control(pDX, IDB_AXIS1_SERVO_LEFT, m_OnOffServoZ1);
	DDX_Control(pDX, IDB_AXIS1_SERVO_RIGHT, m_OnOffServoZ2);
}


BEGIN_MESSAGE_MAP(DlgOriginAll, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// DlgOriginAll message handlers




BOOL DlgOriginAll::OnInitDialog()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CDialogEx::OnInitDialog();

	SetTimer(1, 50, NULL);
	//pDoc->m_StatusOriginZLoading = false;
	//pDoc->m_StatusOriginZUnloading = false;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
BEGIN_EVENTSINK_MAP(DlgOriginAll, CDialogEx)
	ON_EVENT(DlgOriginAll, IDB_AXIS1_ORIGIN, DISPID_CLICK, DlgOriginAll::ClickAxis1Origin, VTS_NONE)
	ON_EVENT(DlgOriginAll, IDB_AXIS2_ORIGIN, DISPID_CLICK, DlgOriginAll::ClickAxis2Origin, VTS_NONE)
	ON_EVENT(DlgOriginAll, IDB_AXIS1_SERVO_LEFT, DISPID_CLICK, DlgOriginAll::ClickAxis1ServoLeft, VTS_NONE)
	ON_EVENT(DlgOriginAll, IDB_AXIS1_SERVO_RIGHT, DISPID_CLICK, DlgOriginAll::ClickAxis1ServoRight, VTS_NONE)
	ON_EVENT(DlgOriginAll, IDB_StopOrigin, DISPID_CLICK, DlgOriginAll::ClickStoporigin, VTS_NONE)
	ON_EVENT(DlgOriginAll, IDB_INIT_LOADING, DISPID_CLICK, DlgOriginAll::ClickInitLoading, VTS_NONE)
	ON_EVENT(DlgOriginAll, IDB_INIT_UNLOADING, DISPID_CLICK, DlgOriginAll::ClickInitUnloading, VTS_NONE)
	ON_EVENT(DlgOriginAll, IDB_INIT_SOCKET, DISPID_CLICK, DlgOriginAll::ClickInitSocket, VTS_NONE)
	ON_EVENT(DlgOriginAll, IDB_INIT_TOOL_ROBOT, DISPID_CLICK, DlgOriginAll::ClickInitToolRobot, VTS_NONE)
END_EVENTSINK_MAP()


void DlgOriginAll::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		ViewPosition();
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void DlgOriginAll::ClickAxis1Origin()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->ResetVariable();

	double dVelFirst = pDoc->DataMotor.SpeedOriginX;
	double dVelSecond = abs(pDoc->DataMotor.SpeedOriginX )/10;
	double dVelThird = abs(pDoc->DataMotor.SpeedOriginX )/15;
	double dvelLast = abs(pDoc->DataMotor.SpeedOriginX )/20;
	double dAccFirst = pDoc->DataMotor.Acc;
	double dAccSecond = pDoc->DataMotor.Acc;

	pDoc->Motion.HomeSetMethod(AxisX, 0, HomeSensor, 1, 2000, 0.0);
	pDoc->Motion.HomeSetVel(AxisX, dVelFirst, dVelSecond, dVelThird, dvelLast, dAccFirst, dAccSecond);
	pDoc->Motion.HomeSetStart(AxisX);



}


void DlgOriginAll::ClickAxis2Origin()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	//pDoc->ResetVariable();

	double dVelFirst = pDoc->DataMotor.SpeedOriginX;
	double dVelSecond = abs(pDoc->DataMotor.SpeedOriginX )/10;
	double dVelThird = abs(pDoc->DataMotor.SpeedOriginX )/15;
	double dvelLast = abs(pDoc->DataMotor.SpeedOriginX )/20;
	double dAccFirst = pDoc->DataMotor.Acc;
	double dAccSecond = pDoc->DataMotor.Acc;

	pDoc->Motion.HomeSetMethod(AxisY, 0, HomeSensor, 1, 2000, 0.0);
	pDoc->Motion.HomeSetVel(AxisY, dVelFirst, dVelSecond, dVelThird, dvelLast, dAccFirst, dAccSecond);
	pDoc->Motion.HomeSetStart(AxisY);

	

}


void DlgOriginAll::ClickAxis1ServoLeft()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	if (pDoc->Motion.Status_OnOff(AxisX))
	{
		pDoc->Motion.Servo_OnOff(AxisX, DISABLE);
		m_OnOffServoZ1.SetCaption("Servo Off");
	}

	else
	{
		pDoc->Motion.Servo_OnOff(AxisX, ENABLE);
		m_OnOffServoZ1.SetCaption("Servo On");
	}
}



void DlgOriginAll::ClickAxis1ServoRight()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (pDoc->Motion.Status_OnOff(AxisY))
	{
		pDoc->Motion.Servo_OnOff(AxisY, DISABLE);
		m_OnOffServoZ2.SetCaption("Servo Off");
	}

	else
	{
		pDoc->Motion.Servo_OnOff(AxisY, ENABLE);
		m_OnOffServoZ2.SetCaption("Servo On");
	}
}

void DlgOriginAll::ViewPosition()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CurentPosX = pDoc->Motion.StatusGetActPos(AxisX);
	CurentPosY = pDoc->Motion.StatusGetActPos(AxisY);

	m_ViewCurrentPosZ1.Format("%lf", CurentPosX);
	m_ViewCurrentPosZ2.Format("%lf", CurentPosY);

	m_CurrentPosZ1.SetCaption(m_ViewCurrentPosZ1);
	m_CurrentPosZ2.SetCaption(m_ViewCurrentPosZ2);

	if (CurentPosX == 0 && !pDoc->m_StatusOriginZLoading)
	{
		pDoc->m_StatusOriginZLoading = true;
	}
	if (CurentPosY == 0 && !pDoc->m_StatusOriginZUnloading)
	{
		pDoc->m_StatusOriginZUnloading = true;
	}
	if (pDoc->m_StatusOriginZUnloading && pDoc->m_StatusOriginZLoading)
	{
		pDoc->OriginComplete = true;
	}

}


void DlgOriginAll::ClickStoporigin()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->Motion.MoveSStop(AxisX);
	pDoc->Motion.MoveSStop(AxisY);
}


void DlgOriginAll::ClickInitLoading()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->ConveyorLoadingOff();
	pDoc->ChanTrayLoadingOff();
	if (pDoc->ReadInput(Detech_Tray_Up_Loading))
	{
		pDoc->XilanhDoTrayLoadingOff();
		pDoc->XilanhAlineTrayLoadingOff();

	}
	else
	{
		pDoc->XilanhDoTrayLoadingOn();
		pDoc->XilanhAlineTrayLoadingOn();
	}
	pDoc->XilanhChotTrayLoadingOn();

	Sleep(1000);

	if (pDoc->m_StatusOriginZLoading)
	{
		pDoc->RunPosLoading(pDoc->PosZ1Down);
	}
	else
	{
		AfxMessageBox("Don't Origin Z Loading");
	}
}


void DlgOriginAll::ClickInitUnloading()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->ConveyorUnloadingOff();
	pDoc->ChanTrayUnloadingOff();
	pDoc->XilanhDoTrayUnloadingOff();
	pDoc->XilanhAlineTrayUnloadingOff();
	pDoc->XilanhChotTrayUnloadingOn();

	Sleep(1000);
	int m_stepRun = 0;

	if (!pDoc->m_StatusOriginZUnloading)
	{
		AfxMessageBox("Don't Origin Z Unloading");
		return;
	}

	if (pDoc->m_StatusOriginZUnloading &&
		pDoc->ReadInput(Detech_Tray_Up_Unloading) &&
		//->ReadInput(SSXL_Do_Tray_Unloading_In_Trai) && 
		//->ReadInput(SSXL_Do_Tray_Unloading_In_Phai) &&
		pDoc->ReadInput(SSXL_AlineTray_Unloading_In)
		)  
	{
		while (true)
		{
			switch (m_stepRun)
			{
			case 0:
			{
				if (pDoc->Motion.Status_OnOff(AxisY) && pDoc->ReadInput(Detech_Tray_Up_Unloading))
				{
					pDoc->Motion.JogRun(AxisY, pDoc->DataMotor.SpeedRunAxisY, pDoc->DataMotor.Acc, pDoc->DataMotor.Dec);
				}
				else
				{
					pDoc->Motion.JogStop(AxisY);
					return;
				}
				break;
			}
			default:
				break;
			}
			
			if (pDoc->ReadInput(Button_Stop))
			{
				pDoc->ActionStop();
				break;
			}

		}
	}
	if (!pDoc->ReadInput(SSXL_AlineTray_Unloading_In))
	{
		AfxMessageBox("Error Safety Sensor");
	}

}


bool DlgOriginAll::ClickInitSocket()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->XilanhSocket1Down();
	pDoc->XilanhSocket2Down();
	pDoc->XilanhSocket3Down();
	pDoc->XilanhSocket4Down();

	pDoc->VaccumSocket1Off();
	pDoc->VaccumSocket2Off();
	pDoc->VaccumSocket3Off();
	pDoc->VaccumSocket4Off();
	while (true)
	{
		if (pDoc->ReadInput(Socket1_Up) && pDoc->ReadInput(Socket2_Up) &&
			pDoc->ReadInput(Socket3_Up) && pDoc->ReadInput(Socket4_Up))
		{
			break;
		}
		if (pDoc->ReadInput(Button_Stop))
		{
			return false;
		}

	}

	
	while (pDoc->ReadInput(Socket1_Up))
	{
	
		pDoc->XilanhSocket1ForWard();
		if (pDoc->ReadInput(Socket1_Rv) && !pDoc->ReadInput(Socket1_Fw))
		{
			break;
		}
		if (pDoc->ReadInput(Button_Stop))
		{
			return false;
		}
	}
	while (pDoc->ReadInput(Socket2_Up))
	{
		Sleep(1000);
		pDoc->XilanhSocket2ForWard();
		if (pDoc->ReadInput(Socket2_Rv) && !pDoc->ReadInput(Socket2_Fw))
		{
			break;
		}
		if (pDoc->ReadInput(Button_Stop))
		{
			return false;
		}
	}
	while (pDoc->ReadInput(Socket3_Up) )
	{
		pDoc->XilanhSocket3ForWard();
		if (pDoc->ReadInput(Socket3_Rv) && !pDoc->ReadInput(Socket3_Fw))
		{
			break;
		}
		if (pDoc->ReadInput(Button_Stop))
		{
			return false;
		}
	}
	while (pDoc->ReadInput(Socket4_Up))
	{
		pDoc->XilanhSocket4ForWard();
		if (pDoc->ReadInput(Socket4_Rv) && !pDoc->ReadInput(Socket4_Fw))
		{
			break;
		}
		if (pDoc->ReadInput(Button_Stop))
		{
			return false;
		}
	}
	pDoc->m_StatusInitsocket = true;
	return true;
}


void DlgOriginAll::ClickInitToolRobot()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	
	pDoc->XilanhTool1RobotLoadingOff();
	pDoc->XilanhTool2RobotLoadingOff();
	pDoc->XilanhTool1RobotUnloadingOff();
	pDoc->XilanhTool2RobotUnloadingOff();

	pDoc->VaccumTool1RobotLoadingOff();
	pDoc->VaccumTool2RobotLoadingOff();
	pDoc->VaccumTool1RobotUnloadingOff();
	pDoc->VaccumTool2RobotUnloadingOff();

	pDoc->VaccumTool2RobotUnloadingOff();
	pDoc->SendDataEthernet("Ready()");

}
