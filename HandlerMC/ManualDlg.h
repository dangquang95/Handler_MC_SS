#pragma once
#include "DlgInput.h"
#include "btnenh.h"
// ManualDlg dialog

class ManualDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ManualDlg)

public:
	ManualDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ManualDlg();

// Dialog Data
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANUAL_MAIN_FORM };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CArray<CRect, CRect> m_PositionArray;
	void SaveControlPosition();
	void ChangeControlPosition();
	DECLARE_EVENTSINK_MAP()

	void ClickInputCheck();
	void ClickOutputCheck();
	void ClickWorktrayLoaderReadyForward();
	void ClickWorktrayLoaderReadyBackward();
	void ClickWorktrayLoaderAlignForward();
	void ClickWorktrayLoaderAlignBackward();
	void ClickWorktrayLoaderStackForward();
	void ClickWorktrayLoaderStackBackward2();
	void ClickWorktrayLoaderRotationForward();
	void ClickWorktrayLoaderRotationBackward();
	void ClickWorktrayLoaderConveyorRun();
	void ClickWorktrayLoaderConveyorStop();
	void ClickWorktrayLoaderReadyForward2();
	void ClickWorktrayLoaderReadyBackward2();
	void ClickWorktrayLoaderAlignForward2();
	void ClickWorktrayLoaderAlignBackward3();
	void ClickWorktrayLoaderStackForward2();
	void ClickWorktrayLoaderStackBackward3();
	void ClickWorktrayLoaderRotationForward2();
	void ClickWorktrayLoaderRotationBackward3();
	void ClickWorktrayLoaderConveyorRun2();
	void ClickWorktrayLoaderConveyorStop2();
	void ClickOpenDoorFontRight();
	void ClickCloseDoorFrontRight();
	void ClickOpenDoorFrontLeft();
	void ClickCloseDoorFrontLeft();
	void ClickOpenDoorSideRight();
	void ClickCloseDoorSideRight();
	void ClickOpenDoorSideLeft();
	void ClickCloseDoorSideLeft();
	void ClickTool1RobotDown();
	void ClickTool1RobotUp();
	void ClickVaccumTool1RobotOn();
	void ClickVaccumTool1RobotOff();
	void ClickTool2RobotDown();
	void ClickTool2RobotUp();
	void ClickVaccumTool2RobotOn();
	void ClickVaccumTool2RobotOff();

	CBtnEnh m_ReadyForwardLoading;
	CBtnEnh m_ReadyBackwardLoading;
	CBtnEnh m_ReadyForwardLoading2;
	CBtnEnh m_ReadyBackwardLoading2;
	CBtnEnh m_AlignForwardLoading;
	CBtnEnh m_AlignBackwardLoading;
	CBtnEnh m_StackForwardLoading;
	CBtnEnh m_StackBackwardLoading;
	CBtnEnh m_RotationForwardLoading;
	CBtnEnh m_RotationBackwardLoading;
	CBtnEnh m_ConveyorRunLoading;
	
	CBtnEnh m_ReadyForwardUnloading;
	CBtnEnh m_ReadForwardUnloading2;
	CBtnEnh m_ReadyBackwardUnloading;
	CBtnEnh m_ReadBackwardUnloading2;
	CBtnEnh m_AlingnForwardUnloading;
	CBtnEnh m_AlineBackWardUnloading;
	CBtnEnh m_StackForwardUnloading;
	CBtnEnh m_StackBackwardUnloading;
	CBtnEnh m_RotationForwardUnloading;
	CBtnEnh m_RotationBackwardUnloading;
	CBtnEnh m_ConveyorRunUnloading;

	CBtnEnh m_Tool1RobotDown;
	CBtnEnh m_Tool1RobotUp;
	CBtnEnh m_VaccumTool1RobotOn;
	CBtnEnh m_Tool2RobotDown;
	CBtnEnh m_Tool2RobotUp;
	CBtnEnh m_VaccumTool2RobotOn;
	CBtnEnh m_Tool3RobotUp;
	CBtnEnh m_Tool4RobotUp;
	CBtnEnh m_VaccumTool3RobotOn;
	CBtnEnh m_VaccumTool4RobotOn;

	CBtnEnh m_SensorForward1;
	CBtnEnh m_SensorForward2;
	CBtnEnh m_SensorForward3;
	CBtnEnh m_SensorForward4;
	CBtnEnh m_SensorBackward1;
	CBtnEnh m_SensorBackward2;
	CBtnEnh m_SensorBackward3;
	CBtnEnh m_SensorBackward4;
	CBtnEnh m_SensorUp1;
	CBtnEnh m_SensorUp2;
	CBtnEnh m_SensorUp3;
	CBtnEnh m_SensorUp4;
	CBtnEnh m_SensorVaccum1;
	CBtnEnh m_SensorVaccum2;
	CBtnEnh m_SensorVaccum3;
	CBtnEnh m_SensorVaccum4;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ViewSensor();
	void ClickTool3RobotDown();
	void ClickTool3RobotUp();
	void ClickVaccumTool3RobotOn();
	void ClickVaccumTool3RobotOff();
	void ClickTool4RobotDown();
	void ClickTool4RobotUp();
	void ClickVaccumTool4RobotOn();
	void ClickVaccumTool4RobotOff();


	void ClickSocketForward1();
	void ClickSocketBackward1();
	void ClickSocketUp1();
	void ClickSocketDown1();
	void ClickSocketVaccumOn1();
	void ClickSocketVaccumOff1();
	void ClickSocketForward2();
	void ClickSocketBackward2();
	void ClickSocketUp2();
	void ClickSocketDown2();
	void ClickSocketVaccumOn2();
	void ClickSocketVaccumOff2();
	void ClickSocketForward3();
	void ClickSocketBackward3();
	void ClickSocketUp3();
	void ClickSocketDown3();
	void ClickSocketVaccumOn3();
	void ClickSocketVaccumOff3();
	void ClickSocketForward4();
	void ClickSocketBackward4();
	void ClickSocketUp4();
	void ClickSocketDown4();
	void ClickSocketVaccumOn4();
	void ClickSocketVaccumOff4();

	void ClickOpenDoorAfter();
	void ClickCloseDoorAfter();
	void ClickAlineForward();
	void ClickAlineBackward();
};
