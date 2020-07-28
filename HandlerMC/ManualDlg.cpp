// ManualDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "ManualDlg.h"
#include "afxdialogex.h"

#define SetON				200
#define SetOFF				10
// ManualDlg dialog

IMPLEMENT_DYNAMIC(ManualDlg, CDialogEx)

ManualDlg::ManualDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MANUAL_MAIN_FORM, pParent)
{

}

ManualDlg::~ManualDlg()
{
}

void ManualDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_READY_FORWARD_CHECK, m_ReadyForwardLoading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_READY_BACKWARD_CHECK, m_ReadyBackwardLoading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK, m_AlignForwardLoading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_BACKWARD_CHECK, m_AlignBackwardLoading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK2, m_StackForwardLoading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_BACKWARD_CHECK2, m_StackBackwardLoading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK3, m_RotationForwardLoading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_BACKWARD_CHECK3, m_RotationBackwardLoading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK4, m_ConveyorRunLoading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_READY_FORWARD_CHECK4, m_ReadyForwardLoading2);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_READY_FORWARD_CHECK5, m_ReadyBackwardLoading2);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_READY_FORWARD_CHECK2, m_ReadyForwardUnloading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_READY_BACKWARD_CHECK4, m_ReadForwardUnloading2);////
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_READY_BACKWARD_CHECK2, m_ReadyBackwardUnloading);//
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_READY_BACKWARD_CHECK5, m_ReadBackwardUnloading2);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK5, m_AlingnForwardUnloading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_BACKWARD_CHECK4, m_AlineBackWardUnloading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK6, m_StackForwardUnloading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_BACKWARD_CHECK5, m_StackBackwardUnloading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK7, m_RotationForwardUnloading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_BACKWARD_CHECK6, m_RotationBackwardUnloading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK8, m_ConveyorRunUnloading);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_READY_BACKWARD_CHECK3, m_Tool1RobotUp);      
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK9, m_VaccumTool1RobotOn);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_BACKWARD_CHECK8, m_Tool2RobotUp);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK11, m_VaccumTool2RobotOn);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK13, m_Tool3RobotUp);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK18, m_Tool4RobotUp);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK14, m_VaccumTool3RobotOn);
	DDX_Control(pDX, IDB_WORKTRAY_LOADER_ALIGN_FORWARD_CHECK19, m_VaccumTool4RobotOn);
	DDX_Control(pDX, IDB_SENSOR_FORWARD_1, m_SensorForward1);
	DDX_Control(pDX, IDB_SENSOR_FORWARD_2, m_SensorForward2);
	DDX_Control(pDX, IDB_SENSOR_FORWARD_3, m_SensorForward3);
	DDX_Control(pDX, IDB_SENSOR_FORWARD_4, m_SensorForward4);
	DDX_Control(pDX, IDB_SENSOR_BACKWARD_1, m_SensorBackward1);
	DDX_Control(pDX, IDB_SENSOR_BACKWARD_2, m_SensorBackward2);
	DDX_Control(pDX, IDB_SENSOR_BACKWARD_3, m_SensorBackward3);
	DDX_Control(pDX, IDB_SENSOR_BACKWARD_4, m_SensorBackward4);
	DDX_Control(pDX, IDB_SENSOR_UP_1, m_SensorUp1);
	DDX_Control(pDX, IDB_SENSOR_UP_2, m_SensorUp2);
	DDX_Control(pDX, IDB_SENSOR_UP_3, m_SensorUp3);
	DDX_Control(pDX, IDB_SENSOR_UP_4, m_SensorUp4);
	DDX_Control(pDX, IDB_SENSOR_VACCUM_1, m_SensorVaccum1);
	DDX_Control(pDX, IDB_SENSOR_VACCUM_2, m_SensorVaccum2);
	DDX_Control(pDX, IDB_SENSOR_VACCUM_3, m_SensorVaccum3);
	DDX_Control(pDX, IDB_SENSOR_VACCUM_4, m_SensorVaccum4);
}


BEGIN_MESSAGE_MAP(ManualDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// ManualDlg message handlers


BOOL ManualDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SaveControlPosition();
	SetTimer(1, 50, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void ManualDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	ChangeControlPosition();
}
void ManualDlg::SaveControlPosition()
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

void ManualDlg::ChangeControlPosition()
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
}BEGIN_EVENTSINK_MAP(ManualDlg, CDialogEx)
ON_EVENT(ManualDlg, IDB_INPUT_CHECK, DISPID_CLICK, ManualDlg::ClickInputCheck, VTS_NONE)
ON_EVENT(ManualDlg, IDB_OUTPUT_CHECK, DISPID_CLICK, ManualDlg::ClickOutputCheck, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_READY_FORWARD, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderReadyForward, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_READY_BACKWARD, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderReadyBackward, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_ALIGN_FORWARD, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderAlignForward, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_ALIGN_BACKWARD, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderAlignBackward, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_STACK_FORWARD, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderStackForward, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_STACK_BACKWARD2, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderStackBackward2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_ROTATION_FORWARD, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderRotationForward, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_ROTATION_BACKWARD, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderRotationBackward, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_CONVEYOR_RUN, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderConveyorRun, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_CONVEYOR_STOP, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderConveyorStop, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_READY_FORWARD2, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderReadyForward2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_READY_BACKWARD2, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderReadyBackward2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_ALIGN_FORWARD2, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderAlignForward2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_ALIGN_BACKWARD3, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderAlignBackward3, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_STACK_FORWARD2, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderStackForward2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_STACK_BACKWARD3, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderStackBackward3, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_ROTATION_FORWARD2, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderRotationForward2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_ROTATION_BACKWARD3, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderRotationBackward3, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_CONVEYOR_RUN2, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderConveyorRun2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_WORKTRAY_LOADER_CONVEYOR_STOP2, DISPID_CLICK, ManualDlg::ClickWorktrayLoaderConveyorStop2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_OPEN_DOOR_FONT_RIGHT, DISPID_CLICK, ManualDlg::ClickOpenDoorFontRight, VTS_NONE)
ON_EVENT(ManualDlg, IDB_CLOSE_DOOR_FRONT_RIGHT, DISPID_CLICK, ManualDlg::ClickCloseDoorFrontRight, VTS_NONE)
ON_EVENT(ManualDlg, IDB_OPEN_DOOR_FRONT_LEFT, DISPID_CLICK, ManualDlg::ClickOpenDoorFrontLeft, VTS_NONE)
ON_EVENT(ManualDlg, IDB_CLOSE_DOOR_FRONT_LEFT, DISPID_CLICK, ManualDlg::ClickCloseDoorFrontLeft, VTS_NONE)
ON_EVENT(ManualDlg, IDB_OPEN_DOOR_SIDE_RIGHT, DISPID_CLICK, ManualDlg::ClickOpenDoorSideRight, VTS_NONE)
ON_EVENT(ManualDlg, IDB_CLOSE_DOOR_SIDE_RIGHT, DISPID_CLICK, ManualDlg::ClickCloseDoorSideRight, VTS_NONE)
ON_EVENT(ManualDlg, IDB_OPEN_DOOR_SIDE_LEFT, DISPID_CLICK, ManualDlg::ClickOpenDoorSideLeft, VTS_NONE)
ON_EVENT(ManualDlg, IDB_CLOSE_DOOR_SIDE_LEFT, DISPID_CLICK, ManualDlg::ClickCloseDoorSideLeft, VTS_NONE)
ON_EVENT(ManualDlg, IDB_TOOL1_ROBOT_DOWN, DISPID_CLICK, ManualDlg::ClickTool1RobotDown, VTS_NONE)
ON_EVENT(ManualDlg, IDB_TOOL1_ROBOT_UP, DISPID_CLICK, ManualDlg::ClickTool1RobotUp, VTS_NONE)
ON_EVENT(ManualDlg, IDB_VACCUM_TOOL1_ROBOT_ON, DISPID_CLICK, ManualDlg::ClickVaccumTool1RobotOn, VTS_NONE)
ON_EVENT(ManualDlg, IDB_VACCUM_TOOL1_ROBOT_OFF, DISPID_CLICK, ManualDlg::ClickVaccumTool1RobotOff, VTS_NONE)
ON_EVENT(ManualDlg, IDB_TOOL2_ROBOT_DOWN, DISPID_CLICK, ManualDlg::ClickTool2RobotDown, VTS_NONE)
ON_EVENT(ManualDlg, IDB_TOOL2_ROBOT_UP, DISPID_CLICK, ManualDlg::ClickTool2RobotUp, VTS_NONE)
ON_EVENT(ManualDlg, IDB_VACCUM_TOOL2_ROBOT_ON, DISPID_CLICK, ManualDlg::ClickVaccumTool2RobotOn, VTS_NONE)
ON_EVENT(ManualDlg, IDB_VACCUM_TOOL2_ROBOT_OFF, DISPID_CLICK, ManualDlg::ClickVaccumTool2RobotOff, VTS_NONE)
ON_EVENT(ManualDlg, IDB_TOOL3_ROBOT_DOWN, DISPID_CLICK, ManualDlg::ClickTool3RobotDown, VTS_NONE)
ON_EVENT(ManualDlg, IDB_TOOL3_ROBOT_UP, DISPID_CLICK, ManualDlg::ClickTool3RobotUp, VTS_NONE)
ON_EVENT(ManualDlg, IDB_VACCUM_TOOL3_ROBOT_ON, DISPID_CLICK, ManualDlg::ClickVaccumTool3RobotOn, VTS_NONE)
ON_EVENT(ManualDlg, IDB_VACCUM_TOOL3_ROBOT_OFF, DISPID_CLICK, ManualDlg::ClickVaccumTool3RobotOff, VTS_NONE)
ON_EVENT(ManualDlg, IDB_TOOL4_ROBOT_DOWN, DISPID_CLICK, ManualDlg::ClickTool4RobotDown, VTS_NONE)
ON_EVENT(ManualDlg, IDB_TOOL4_ROBOT_UP, DISPID_CLICK, ManualDlg::ClickTool4RobotUp, VTS_NONE)
ON_EVENT(ManualDlg, IDB_VACCUM_TOOL4_ROBOT_ON, DISPID_CLICK, ManualDlg::ClickVaccumTool4RobotOn, VTS_NONE)
ON_EVENT(ManualDlg, IDB_VACCUM_TOOL4_ROBOT_OFF, DISPID_CLICK, ManualDlg::ClickVaccumTool4RobotOff, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_FORWARD_1, DISPID_CLICK, ManualDlg::ClickSocketForward1, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_BACKWARD_1, DISPID_CLICK, ManualDlg::ClickSocketBackward1, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_UP_1, DISPID_CLICK, ManualDlg::ClickSocketUp1, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_DOWN_1, DISPID_CLICK, ManualDlg::ClickSocketDown1, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_VACCUM_ON_1, DISPID_CLICK, ManualDlg::ClickSocketVaccumOn1, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_VACCUM_OFF_1, DISPID_CLICK, ManualDlg::ClickSocketVaccumOff1, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_FORWARD_2, DISPID_CLICK, ManualDlg::ClickSocketForward2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_BACKWARD_2, DISPID_CLICK, ManualDlg::ClickSocketBackward2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_UP_2, DISPID_CLICK, ManualDlg::ClickSocketUp2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_DOWN_2, DISPID_CLICK, ManualDlg::ClickSocketDown2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_VACCUM_ON_2, DISPID_CLICK, ManualDlg::ClickSocketVaccumOn2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_VACCUM_OFF_2, DISPID_CLICK, ManualDlg::ClickSocketVaccumOff2, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_FORWARD_3, DISPID_CLICK, ManualDlg::ClickSocketForward3, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_BACKWARD_3, DISPID_CLICK, ManualDlg::ClickSocketBackward3, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_UP_3, DISPID_CLICK, ManualDlg::ClickSocketUp3, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_DOWN_3, DISPID_CLICK, ManualDlg::ClickSocketDown3, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_VACCUM_ON_3, DISPID_CLICK, ManualDlg::ClickSocketVaccumOn3, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_VACCUM_OFF_3, DISPID_CLICK, ManualDlg::ClickSocketVaccumOff3, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_FORWARD_4, DISPID_CLICK, ManualDlg::ClickSocketForward4, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_BACKWARD_4, DISPID_CLICK, ManualDlg::ClickSocketBackward4, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_UP_4, DISPID_CLICK, ManualDlg::ClickSocketUp4, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_DOWN_4, DISPID_CLICK, ManualDlg::ClickSocketDown4, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_VACCUM_ON_4, DISPID_CLICK, ManualDlg::ClickSocketVaccumOn4, VTS_NONE)
ON_EVENT(ManualDlg, IDB_SOCKET_VACCUM_OFF_4, DISPID_CLICK, ManualDlg::ClickSocketVaccumOff4, VTS_NONE)
ON_EVENT(ManualDlg, IDB_OPEN_DOOR_AFTER, DISPID_CLICK, ManualDlg::ClickOpenDoorAfter, VTS_NONE)
ON_EVENT(ManualDlg, IDB_CLOSE_DOOR_AFTER, DISPID_CLICK, ManualDlg::ClickCloseDoorAfter, VTS_NONE)
ON_EVENT(ManualDlg, IDB_ALINE_FORWARD, DISPID_CLICK, ManualDlg::ClickAlineForward, VTS_NONE)
ON_EVENT(ManualDlg, IDB_ALINE_BACKWARD, DISPID_CLICK, ManualDlg::ClickAlineBackward, VTS_NONE)
END_EVENTSINK_MAP()


void ManualDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		ViewSensor();
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void ManualDlg::ViewSensor()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	//Loading
	if (pDoc->ReadInput(SSXL_Do_Tray_Loading_Out_Trai)) m_ReadyForwardLoading.SetBackColor(SetON); else m_ReadyForwardLoading.SetBackColor(SetOFF);
	if (pDoc->ReadInput(SSXL_Do_Tray_Loading_In_Trai)) m_ReadyBackwardLoading.SetBackColor(SetON); else m_ReadyBackwardLoading.SetBackColor(SetOFF);
	if (pDoc->ReadInput(SSXL_Do_Tray_Loading_In_Phai)) m_ReadyBackwardLoading2.SetBackColor(SetON); else m_ReadyBackwardLoading2.SetBackColor(SetOFF);
	if (pDoc->ReadInput(SSXL_Do_Tray_Loading_Out_Phai)) m_ReadyForwardLoading2.SetBackColor(SetON); else m_ReadyForwardLoading2.SetBackColor(SetOFF);

	if (pDoc->ReadInput(SSXL_AlineTray_Loading_Out)) m_AlignForwardLoading.SetBackColor(SetON); else m_AlignForwardLoading.SetBackColor(SetOFF);
	if (pDoc->ReadInput(SSXL_AlineTray_Loading_In)) m_AlignBackwardLoading.SetBackColor(SetON); else m_AlignBackwardLoading.SetBackColor(SetOFF);

	if (pDoc->ReadInput(SSXL_Chan_Tray_Loading_Nam)) m_RotationForwardLoading.SetBackColor(SetON); else m_RotationForwardLoading.SetBackColor(SetOFF);
	if (pDoc->ReadInput(SSXL_Chan_Tray_Loading_Dung)) m_RotationBackwardLoading.SetBackColor(SetON); else m_RotationBackwardLoading.SetBackColor(SetOFF);

	if (pDoc->ReadInput(SSXL_Aline_FW)) m_StackForwardLoading.SetBackColor(SetON); else m_StackForwardLoading.SetBackColor(SetOFF);
	if (pDoc->ReadInput(SSXL_Aline_BW)) m_StackBackwardLoading.SetBackColor(SetON); else m_StackBackwardLoading.SetBackColor(SetOFF);

	if (pDoc->ReadOutput(Conveyor_Loading)) m_ConveyorRunLoading.SetBackColor(SetON); else m_ConveyorRunLoading.SetBackColor(SetOFF);

	//Unloading
	//if (pDoc->ReadInput(SSXL_Do_Tray_Unloading_Out_Trai)) m_ReadyForwardUnloading.SetBackColor(SetON); else m_ReadyForwardUnloading.SetBackColor(SetOFF);
	// (pDoc->ReadInput(SSXL_Do_Tray_Unloading_In_Trai)) m_ReadyBackwardUnloading.SetBackColor(SetON); else m_ReadyBackwardUnloading.SetBackColor(SetOFF);
	//if (pDoc->ReadInput(SSXL_Do_Tray_Unloading_In_Phai)) m_ReadBackwardUnloading2.SetBackColor(SetON); else m_ReadBackwardUnloading2.SetBackColor(SetOFF);
	//if (pDoc->ReadInput(SSXL_Do_Tray_Unloading_Out_Phai)) m_ReadForwardUnloading2.SetBackColor(SetON); else m_ReadForwardUnloading2.SetBackColor(SetOFF);

	if (pDoc->ReadInput(SSXL_AlineTray_Unloading_Out)) m_AlingnForwardUnloading.SetBackColor(SetON); else m_AlingnForwardUnloading.SetBackColor(SetOFF);
	if (pDoc->ReadInput(SSXL_AlineTray_Unloading_In)) m_AlineBackWardUnloading.SetBackColor(SetON); else m_AlineBackWardUnloading.SetBackColor(SetOFF);

	if (pDoc->ReadInput(SSXL_Chan_Tray_Unloading_Nam)) m_RotationForwardUnloading.SetBackColor(SetON); else m_RotationForwardUnloading.SetBackColor(SetOFF);
	if (pDoc->ReadInput(SSXL_Chan_Tray_Unloading_Dung)) m_RotationBackwardUnloading.SetBackColor(SetON); else m_RotationBackwardUnloading.SetBackColor(SetOFF);

	if (pDoc->ReadInput(SSXL_Chot_Stack_Unloading_Out)) m_StackForwardUnloading.SetBackColor(SetON); else m_StackForwardUnloading.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Safety_Door_After)) m_StackBackwardUnloading.SetBackColor(SetON); else m_StackBackwardUnloading.SetBackColor(SetOFF);

	if (pDoc->ReadOutput(Conveyor_Unloading)) m_ConveyorRunUnloading.SetBackColor(SetON); else m_ConveyorRunUnloading.SetBackColor(SetOFF);

	//Robot
	if (pDoc->ReadInput(SSXL_Tool1_RobotUp)) m_Tool1RobotUp.SetBackColor(SetON); else m_Tool1RobotUp.SetBackColor(SetOFF);
	if (pDoc->ReadInput(SSXL_Tool2_RobotUp)) m_Tool2RobotUp.SetBackColor(SetON); else m_Tool2RobotUp.SetBackColor(SetOFF);
	if (pDoc->ReadInput(SSXL_Tool3_RobotUp)) m_Tool3RobotUp.SetBackColor(SetON); else m_Tool3RobotUp.SetBackColor(SetOFF);
	if (pDoc->ReadInput(SSXL_Tool4_RobotUp)) m_Tool4RobotUp.SetBackColor(SetON); else m_Tool4RobotUp.SetBackColor(SetOFF);

	if (pDoc->ReadInput(Vaccum_Tool1_Robot)) m_VaccumTool1RobotOn.SetBackColor(SetON); else m_VaccumTool1RobotOn.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Vaccum_Tool2_Robot)) m_VaccumTool2RobotOn.SetBackColor(SetON); else m_VaccumTool2RobotOn.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Vaccum_Tool3_Robot)) m_VaccumTool3RobotOn.SetBackColor(SetON); else m_VaccumTool3RobotOn.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Vaccum_Tool4_Robot)) m_VaccumTool4RobotOn.SetBackColor(SetON); else m_VaccumTool4RobotOn.SetBackColor(SetOFF);

	//Socket
	if (pDoc->ReadInput(Socket1_Fw)) m_SensorForward1.SetBackColor(SetON); else m_SensorForward1.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Socket2_Fw)) m_SensorForward2.SetBackColor(SetON); else m_SensorForward2.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Socket3_Fw)) m_SensorForward3.SetBackColor(SetON); else m_SensorForward3.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Socket4_Fw)) m_SensorForward4.SetBackColor(SetON); else m_SensorForward4.SetBackColor(SetOFF);

	if (pDoc->ReadInput(Socket1_Rv)) m_SensorBackward1.SetBackColor(SetON); else  m_SensorBackward1.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Socket2_Rv)) m_SensorBackward2.SetBackColor(SetON); else  m_SensorBackward2.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Socket3_Rv)) m_SensorBackward3.SetBackColor(SetON); else  m_SensorBackward3.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Socket4_Rv)) m_SensorBackward4.SetBackColor(SetON); else  m_SensorBackward4.SetBackColor(SetOFF);

	if (pDoc->ReadInput(Socket1_Up)) m_SensorUp1.SetBackColor(SetON); else  m_SensorUp1.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Socket2_Up)) m_SensorUp2.SetBackColor(SetON); else  m_SensorUp2.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Socket3_Up)) m_SensorUp3.SetBackColor(SetON); else  m_SensorUp3.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Socket4_Up)) m_SensorUp4.SetBackColor(SetON); else  m_SensorUp4.SetBackColor(SetOFF);

	if (pDoc->ReadInput(Vaccum_Socket_1)) m_SensorVaccum1.SetBackColor(SetON); else  m_SensorVaccum1.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Vaccum_Socket_2)) m_SensorVaccum2.SetBackColor(SetON); else  m_SensorVaccum2.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Vaccum_Socket_3)) m_SensorVaccum3.SetBackColor(SetON); else  m_SensorVaccum3.SetBackColor(SetOFF);
	if (pDoc->ReadInput(Vaccum_Socket_4)) m_SensorVaccum4.SetBackColor(SetON); else  m_SensorVaccum4.SetBackColor(SetOFF);

}

void ManualDlg::ClickInputCheck()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->FlagInOut = TRUE;
	DlgInput ViewDlg;
	ViewDlg.DoModal();
}


void ManualDlg::ClickOutputCheck()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->FlagInOut = FALSE;
	DlgInput ViewDlg;
	ViewDlg.DoModal();
}


void ManualDlg::ClickWorktrayLoaderReadyForward()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhDoTrayLoadingOn();
}


void ManualDlg::ClickWorktrayLoaderReadyBackward()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhDoTrayLoadingOff();
}


void ManualDlg::ClickWorktrayLoaderAlignForward()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhAlineTrayLoadingOn();
}


void ManualDlg::ClickWorktrayLoaderAlignBackward()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhAlineTrayLoadingOff();
}


void ManualDlg::ClickWorktrayLoaderStackForward()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhChotTrayLoadingOn();
}


void ManualDlg::ClickWorktrayLoaderStackBackward2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhChotTrayLoadingOff();
}


void ManualDlg::ClickWorktrayLoaderRotationForward()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->ChanTrayLoadingOn();
}


void ManualDlg::ClickWorktrayLoaderRotationBackward()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->ChanTrayLoadingOff();
}


void ManualDlg::ClickWorktrayLoaderConveyorRun()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->ConveyorLoadingOn();
}


void ManualDlg::ClickWorktrayLoaderConveyorStop()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->ConveyorLoadingOff();
}

//
void ManualDlg::ClickWorktrayLoaderReadyForward2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhDoTrayUnloadingOn();
}


void ManualDlg::ClickWorktrayLoaderReadyBackward2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhDoTrayUnloadingOff();
}


void ManualDlg::ClickWorktrayLoaderAlignForward2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhAlineTrayUnloadingOn();
}


void ManualDlg::ClickWorktrayLoaderAlignBackward3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhAlineTrayUnloadingOff();
}


void ManualDlg::ClickWorktrayLoaderStackForward2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhChotTrayUnloadingOn();
}


void ManualDlg::ClickWorktrayLoaderStackBackward3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhChotTrayUnloadingOff();
}


void ManualDlg::ClickWorktrayLoaderRotationForward2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->ChanTrayUnloadingOn();
}


void ManualDlg::ClickWorktrayLoaderRotationBackward3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->ChanTrayUnloadingOff();
}


void ManualDlg::ClickWorktrayLoaderConveyorRun2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->ConveyorUnloadingOn();
}


void ManualDlg::ClickWorktrayLoaderConveyorStop2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->ConveyorUnloadingOff();
}


void ManualDlg::ClickOpenDoorFontRight()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->OpenDoorFrontRightOn();
}


void ManualDlg::ClickCloseDoorFrontRight()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->OpenDoorFrontRightOff();
}


void ManualDlg::ClickOpenDoorFrontLeft()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->OpenDoorFrontLeftOn();
}


void ManualDlg::ClickCloseDoorFrontLeft()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->OpenDoorFrontLeftOff();
}


void ManualDlg::ClickOpenDoorSideRight()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->OpenDoorSideRightOn();
}


void ManualDlg::ClickCloseDoorSideRight()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->OpenDoorsideRightOff();   
}


void ManualDlg::ClickOpenDoorSideLeft()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->OpenDoorSideLeftOn();
}


void ManualDlg::ClickCloseDoorSideLeft()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->OpenDoorsideLeftOff();
}

//Tool Robot
//Tool 1
void ManualDlg::ClickTool1RobotDown()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhTool1On();
}


void ManualDlg::ClickTool1RobotUp()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhTool1Off();
}


void ManualDlg::ClickVaccumTool1RobotOn()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumTool1On();
}


void ManualDlg::ClickVaccumTool1RobotOff()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumTool1Off();
}

//Tool 2
void ManualDlg::ClickTool2RobotDown()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhTool2On();
}


void ManualDlg::ClickTool2RobotUp()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhTool2Off();
}


void ManualDlg::ClickVaccumTool2RobotOn()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumTool2On();
}


void ManualDlg::ClickVaccumTool2RobotOff()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumTool2Off();
}

//Tool 3
void ManualDlg::ClickTool3RobotDown()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhTool3On();
}


void ManualDlg::ClickTool3RobotUp()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhTool3Off();
}


void ManualDlg::ClickVaccumTool3RobotOn()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumTool3On();
}


void ManualDlg::ClickVaccumTool3RobotOff()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumTool3Off();
}

//Tool 4
void ManualDlg::ClickTool4RobotDown()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhTool4On();
}


void ManualDlg::ClickTool4RobotUp()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhTool4Off();
}


void ManualDlg::ClickVaccumTool4RobotOn()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumTool4On();
}


void ManualDlg::ClickVaccumTool4RobotOff()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumTool4Off();
}

//Socket 1
void ManualDlg::ClickSocketForward1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (pDoc->Motion.ReadOuput(Socket_UP_1))
	{
		AfxMessageBox("Cylinder Up 1 On");
		return;
	}
	pDoc->XilanhSocket1ForWard();
}


void ManualDlg::ClickSocketBackward1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (pDoc->Motion.ReadOuput(Socket_UP_1))
	{
		AfxMessageBox("Cylinder Up 1 On");
		return;
	}
	pDoc->XilanhSocket1BackWard();
}


void ManualDlg::ClickSocketUp1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhSocket1Up();
}


void ManualDlg::ClickSocketDown1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhSocket1Down();
}


void ManualDlg::ClickSocketVaccumOn1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumSocket1On();
}


void ManualDlg::ClickSocketVaccumOff1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumSocket1Off();
}

//Socket 2
void ManualDlg::ClickSocketForward2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (pDoc->Motion.ReadOuput(Socket_UP_2))
	{
		AfxMessageBox("Cylinder Up 2 On");
		return;
	}
	pDoc->XilanhSocket2ForWard();
}


void ManualDlg::ClickSocketBackward2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (pDoc->Motion.ReadOuput(Socket_UP_2))
	{
		AfxMessageBox("Cylinder Up 2 On");
		return;
	}
	pDoc->XilanhSocket2BackWard();
}


void ManualDlg::ClickSocketUp2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhSocket2Up();
}


void ManualDlg::ClickSocketDown2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhSocket2Down();
}


void ManualDlg::ClickSocketVaccumOn2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumSocket2On();
}


void ManualDlg::ClickSocketVaccumOff2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumSocket2Off();
}

//Socket 3
void ManualDlg::ClickSocketForward3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (pDoc->Motion.ReadOuput(Socket_UP_3))
	{
		AfxMessageBox("Cylinder Up 3 On");
		return;
	}
	pDoc->XilanhSocket3ForWard();
}


void ManualDlg::ClickSocketBackward3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (pDoc->Motion.ReadOuput(Socket_UP_3))
	{
		AfxMessageBox("Cylinder Up 3 On");
		return;
	}
	pDoc->XilanhSocket3BackWard();
}


void ManualDlg::ClickSocketUp3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhSocket3Up();
}


void ManualDlg::ClickSocketDown3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhSocket3Down();
}


void ManualDlg::ClickSocketVaccumOn3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumSocket3On();
}


void ManualDlg::ClickSocketVaccumOff3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumSocket3Off();
}


//Socket 4
void ManualDlg::ClickSocketForward4()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (pDoc->Motion.ReadOuput(Socket_UP_4))
	{
		AfxMessageBox("Cylinder Up 4 On");
		return;
	}
	pDoc->XilanhSocket4ForWard();
}


void ManualDlg::ClickSocketBackward4()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (pDoc->Motion.ReadOuput(Socket_UP_4))
	{
		AfxMessageBox("Cylinder Up 4 On");
		return;
	}
	pDoc->XilanhSocket4BackWard();
}


void ManualDlg::ClickSocketUp4()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhSocket4Up();
}


void ManualDlg::ClickSocketDown4()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhSocket4Down();
}


void ManualDlg::ClickSocketVaccumOn4()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumSocket4On();
}


void ManualDlg::ClickSocketVaccumOff4()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->VaccumSocket4Off();
}


void ManualDlg::ClickOpenDoorAfter()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->OpenDoorAfter();
}


void ManualDlg::ClickCloseDoorAfter()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->CloseDoorAfter();

}

void ManualDlg::ClickAlineForward()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhAlineOn();

}


void ManualDlg::ClickAlineBackward()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->XilanhAlineOff();
}
