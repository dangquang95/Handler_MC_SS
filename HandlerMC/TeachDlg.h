#pragma once
#include "afxwin.h"

#include "ImPanel.h"
#include "ImAdvPanel.h"
#include "afxwin.h"
#include "Mydefine.h"
#include "btnenh.h"
#include "GetNumberDlg.h"
#include "GCharDlg.h"

// TeachDlg dialog

class TeachDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TeachDlg)

public:
	TeachDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~TeachDlg();

// Dialog Data
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEACH_MAIN_FORM };
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

	//Khai bao Mapping
	im::CImAdvPanel m_PictureTeach;
	void Generate();
	void MappingPisition(int numRows, int numColums, int disRows, int disColums);
	void DisplayImage(im::CImAdvPanel & panel, cv::Mat & img);
	//tray loading
	int numRows, numColums, disRows, disColums = 0;
	vector<vector<sPosition>> vPosition;
	int w = 640, h = 480;					//width - hight of picture from load
	cv::Mat mMap = Mat(5000, 5000, CV_8UC3);
	//cv::Mat mShow = mMap.clone();
	cv::Mat mShow = mMap;
	//
	void checkPosition(cv::Point point, int & x, int & y);
	void UpdatePosition();
	void AutoSetOnPictureLoading(int m_x, int m_y);

	cv::Mat mMapBufer = Mat(5000, 5000, CV_8UC3);
	void UpdatestStatusMap();
	int m_SlectTray = 0;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnOptionSelect();

	//
	void UpdatePosTarget(int x, int y);

	CBtnEnh m_TargetPosX;
	CBtnEnh m_TargetPosY;
	CBtnEnh m_TargetPosZ;
	CBtnEnh m_TargetPosR;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_EVENTSINK_MAP()
	void ClickAxis1Servo1();

	CBtnEnh m_ServoOnOffX;
	CBtnEnh m_ServoOnOffY;
	void ClickAxis1Servo2();
	void MouseDownJogHead1YFor(short Button, short Shift, long x, long y);
	void MouseUpJogHead1YFor(short Button, short Shift, long x, long y);
	void MouseDownJogHead1YBack(short Button, short Shift, long x, long y);
	void MouseUpJogHead1YBack(short Button, short Shift, long x, long y);
	void MouseDownJogHead1ZUp(short Button, short Shift, long x, long y);
	void MouseUpJogHead1ZUp(short Button, short Shift, long x, long y);
	void MouseDownJogHead1ZDown(short Button, short Shift, long x, long y);
	void MouseUpJogHead1ZDown(short Button, short Shift, long x, long y);

	void SetCurenntpos();
	MotionLBR TeachMotion;
	CBtnEnh m_Current_pos_X;
	CBtnEnh m_Current_pos_Y;
	CBtnEnh m_Current_posAct_X;
	CBtnEnh m_Current_posAct_Y;
	CBtnEnh m_ViewSpeedJog;
	CBtnEnh m_Offset_JogZ1;
	int     m_RatioSpeed = 1;
	CString m_CurentPosX;
	CString m_CurentPosY;
	CString m_ViewSpeed;
	double  CurentPosX;
	double  CurentPosY;
	double  CurentPosActX = 0;
	double  CurentPosACtY = 0;
	void ClickAxis1Point1Down();
	void ClickAxis1Point1Up();
	void ClickAxis2Point1Down();
	void ClickAxis2Point1Up();
	void SavePointTeach();
	void ClickAxis1Point1DownRun();
	void ClickAxis1Point1UpRun();
	void ClickAxis2Point1DownRun();
	void ClickAxis2Point1UpRun();
	
	void ClickJogIncSpeed();
	void ClickJogDec1Speed();
	void ViewRatioSpeed();
	int m_SelectTrayAction = 0;
	void ViewDataSend(CString m_data);

	afx_msg void OnBnClickedRadio3();//
	afx_msg void OnBnClickedRadioTrayUnloadingLeft();//
	afx_msg void OnOptionRunpostool2();
	afx_msg void OnBnClickedRadio2();//

	CListBox m_ActionToo1Loading;
	CListBox m_ActionToo2Loading;
	CListBox m_ActionToo1Unloading;
	CListBox m_ActionToo2Unloading;
	CListBox m_ActionLoadingVision;
	CListBox m_ActionuUnloadingTrayFull;
	CListBox m_ActionToolRobot;
	CListBox m_ActionVaccumRobot;

	void ClickTool1Loading();
	void ClickTool2Loading();	
	void ClickTool1Unloading();
	void ClickTool2Unloading();	
	void ClickLoadingVision();	
	void ClickLoadingTrayZ1();	
	void ClickOffsetJogZ1();
	void SetcaptionZ1Offset();
	void ClickUnloadingTray();
	void ClickAxis2Point2UpRun();
	void ClickAxis2Point2Up();
	void ClickUnloadingTrayFull();

	
	

	CComboBox m_ConnectCom;
	void ClickConnectCom();
	void SetupCOM();
	CComboBox m_BaudRate;
	CBtnEnh m_CaptionConnect;
	void ClickSendDataCom();
	void ClickToolrobotOn();
	void ClickToolrobotOn2();
	void ClickToolrobotOn3();
	void ClickToolrobotOn4();
	CString m_GetDataRobot;
	void ClickTestVisionTool1();
	void ClickTestVisionTool2();
		
	void ClickRobotUp();
	void ClickRobotMedium();
	void ClickRobotLow();
	bool SelectZ[3];
	
	afx_msg void OnBnClickedRadioTrayUnloadingLeft2();
	CBtnEnh m_ViewRobotUpMediumDown[3];
	
};
