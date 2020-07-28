
// HandlerMCDoc.h : interface of the CHandlerMCDoc class
//

//Robot scada

#pragma once

#include <vector>
#include "IniFile.h" 
#include "GTCRobotCtrl2.h"
#include "ClientSocket.h"

#include "DataDefine.h"
#include "MotionLBR.h"
#include "SerialCtrl.h"
#include "savedata.h"
#include "VisionDlg.h"
#include "CameraOmron.h"

#include "RS232COM.h"
using namespace std;
class CHandlerMCDoc : public CDocument
{
protected: // create from serialization only
	CHandlerMCDoc();
	DECLARE_DYNCREATE(CHandlerMCDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	void InitSocketCaoHuy(CString m_IP,int m_port);
	void DisConnectSocket();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CHandlerMCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
	//vision
public:
	CString m_datagettest;
	void				initializeVision();

	//data
	saveDatatsystem		*m_savedata;
	CameraOmron			*pcamOmron;
	Mat					m_Grab;
	//CameraOmron			*m_camOmron; 
	CString				strShowImage;
	
	DataSystem			Data_system;
	VisionPara			visionPara[2];
	//image
	
	cv::Mat				image;
	cv::Rect			b_Rect;
	double				dx_pixcel;
	double				dy_pixcel;
	//Threshold
	double				valueThreshTool_1;
	double				valueThreshTool_2;
	int					checkThresh;
	int					count_value = 0;
	int					count_value_1 = 0;
	int					areaContours;
	int					areaContours_2;

	//blur			
	int					kSize_tool_1 = 1;
	int					kSize_tool_2 = 1;
	int					checkBlur;

	//Morphology
	int					morSize_tool_1 = 1;
	int					morSize_tool_2 = 1;
	int					erode_dilate = 0;
	int					dilate_erode = 0;
	int					erode = 0;
	int					dilate = 0;
	int					checkApplyMorphology;

	//Remove Noise
	int d_minArea = 0;
	int d_maxArea = 0;
	int d_minWidth = 0;
	int d_maxWidth = 0;
	int d_minHeight = 0;
	int d_maxHeight = 0;
	int check_app_remove_noise = 0;

	//Process
	int check_process = 0;
	//function
	void				loopData();
	cv::Mat				filterAndThreshold(cv::Mat image, int th_value, int tool_1, int tool_2);
	void				morphologyP(cv::Mat &image, int tool_1, int tool_2);
	cv::Mat				showProcessImage(int result, int tool_1, int tool_2, int aut_value);
	BOOL				functionResult(double &dx, double &dy, double &dAngle, int tool_1, int tool_2);
	BOOL				resultApply(double &dx, double &dy, double &dAngle, int tool_1, int tool_2);
	CString strResult;
	cv::Point2f	pointCurrent;
	double		angleCurrent;
	

	appVision			*m_vision;
	int					bOnVision = 0;
	double  dX, dY;
	float alpha;
	double deltadX;
	double deltadY;

	//Point
	cv::Point			pointSampleTool_1;
	double				angleSampleTool_1;
	cv::Point			pointSampleTool_2;
	double				angleSampleTool_2;
	float				deltaDx, deltaDy;
	

	
//---------------------888888888888888-8---------------------
	//end
public:
	static UINT					ThreadServo(LPVOID pParam);
	BOOL						bEndThreadServo = FALSE;
	void						StopThreadServo();
	void						StartThreadServo();
	void                        LoopServo();
	void ActionBotton();
	void ActionStop();
	void LoopStop();
	void LoopEMG();
	void LoopWait();
	void InitTrayLoading();
	void LoopStart();
	void ResetVariable();
	void ViewDataList(CString m_data);
	bool m_BufferLoading();
	bool m_RobotLoadingCamMove();
	bool m_RobotLoadingCamMoveTool1();
	bool m_RobotLoadingCamMoveTool2();
	int m_RobotLoadingVision();
	bool CylinderAlineAction();
	bool m_VisionToo1();
	bool m_VisionToo2();
	bool m_AlineToo1();
	bool m_AlineToo2();
	bool m_AlineToo1Pick();
	bool m_AlineToo2Pick();
	int m_NorunAlineTool1 = 0;
	int m_NorunAlineTool2 = 0;
	int m_NorunAlinePickTool1 = 0;
	int m_NorunAlinePickTool2 = 0;
	int m_NorunAlinePickTool = 0;
	int m_RunVisionTool1 = 0;
	int m_RunVisionTool2 = 0;
	int m_CylinderAlineAction = 0;
	CString m_BufferDataVision = "";
	//
	int m_NumberComEvent;
	int m_BaudRateEvent;
	CRS232COM m_PhoneCom;
	static void ReceivePhoneCom(CString m_DataCom);
	void SendPhoneCom(CString Data);
	bool m_StatusConnectCom = false;
    bool m_SignReviceCom;
	CString m_DataComEvent;
	void InitComPhone(int m_ComPort, int m_Baudrate);
	void SaveDataComEvent();
	void ReadDataComEvent();
	void ReadDataDelayVaccum();
	void ReadDataDelayCylinder();
	//
	bool ReadSignalSensor();

	bool UnloadingTray();
	bool ReadyToUnloadingTray();
	bool ReadyToLoadingTray();
	bool SafetyDownZ2UnloadingTien();
	bool SafetyDownZ2UnloadingLui();
	bool ActionDownZUnloading();
	bool SafetyDoor();
	bool NotUseSafety = false;
	int m_NumberButtonSafety = 0;
	int m_NumberButtonVision = 0;
	CString MessengerData;
	//  
	bool m_RobotLoadingtestFirtRun();
	bool m_RobotLoadingtest0();
	bool m_RobotLoadingtest00();
	bool m_RobotLoadingtest1();
	bool m_RobotLoadingtest11();
	bool m_RobotLoadingtest2();
	bool m_RobotLoadingtest22();
	bool m_RobotLoadingtest3();
	bool m_RobotLoadingtest33();
	//
	void m_TestCommand(int m_Socketer);
	bool ActionXilanhSocket1Result();
	bool ActionXilanhSocket2Result();
	bool ActionXilanhSocket3Result();
	bool ActionXilanhSocket4Result();
	bool m_ResultTest();
	bool m_RobotUnloadingAndLoadingTest();
	bool Status_Loading_Unloading = true;
	bool RobotUnloadingLoadingTest0();
	bool RobotUnloadingLoadingTest1();
	bool RobotUnloadingLoadingTest2();
	bool RobotUnloadingLoadingTest3();
	bool ReturnResultUnloadingLoading();
	bool RobotUnloadingTest0();
	bool RobotUnloadingTest1();
	bool RobotUnloadingTest2();
	bool RobotUnloadingTest3();
	bool Safety4ToolRobot();
	bool GetResultTool(int m_Socket);
	bool m_RobotMoveTrayOKNG();
	bool m_RobotMoveTrayOKNG0();
	bool m_RobotMoveTrayOKNG1();
	bool m_Tool1ResulOKUnload();
	bool m_Tool1ResulNGUnload();
	bool m_Tool2ResulOKUnload();
	bool m_Tool2ResulNGUnload();
	bool m_UnloadingTrayOKUpDown( CString m_slecttool);
	bool m_UnloadingTrayNGLeftUpDown(CString m_slecttool);
	bool m_UnloadingTrayNGRightUpDown(CString m_slecttool);
	bool m_CheckTrayLoadFull();
	bool m_CheckTrayUnloadLeftFull();
	bool m_CheckTrayUnloadRightFull();
	bool m_UnloadingTrayLoadingFull();
	bool m_BufferUnloading();
	bool ActionEndTray();
	bool ReturnEndTray();
	//Robot
	void    ReadDataEthernet();
	int     SendDataEthernet(CString m_data);
	bool    MootionDoneRobot();
	bool    MootionVisionDoneRobot();
	bool    ActionReviceEthernet();
	CString ReadDataRobot();
	//End Tray
	int m_NoRunEndTray = 0;
	bool Flag_pick_cam = false;
	//auto
	int m_operation = operation_wait;
	int m_ActionStart = BufferLoading;
	//---Loading tray
	int m_trayLoading = 0;
	int m_countjog = 0;
	int m_countaline = 0;
	bool m_Tool1Loading = false;
	bool m_Tool2Loading = false;
	bool m_FlagThuahang= false;
	//---Robot Loading Cam
	int m_RobotLoadingCAM = 0;
	int m_RobotLoadingCAMTool1 = 0;
	int m_RobotLoadingCAMTool2 = 0;
	bool flagLoadingTool1Error = true;
	bool flagLoadingTool2Error = true;
	//---Loading Vision
	int m_LoadingVision = 0;
	int m_NoVisionToo1 = 0;
	int m_NoVisionToo2 = 0;
	double Dx1 = 0, Dy1 = 0, Dx2 = 0, Dy2 = 0;
	double Dr1 = 0, Dr2 = 0;
	bool flagFirtrun = false;
	bool m_UsingVision = true;
	//Loading Test
	int m_LoadingTest = 0;
	int m_NoLoadingTest = 0;
	int m_SelectToolLoading = 0;
	bool m_flagtoolloading = false;
	//Test Command
	int m_NoTestCommand = 0;
	bool m_flagTestCommand = true;
	int m_NumberTesterAct = 0;
	bool m_StatusRun3Tester = false;
	int m_NoRunLoadingTool2 = 0;
	int m_hehe;
	//Result Test
	int n_ResultTest = 0;
	int m_ResultTestSocket[4];//Ban dau bang 0
	int m_ActionXilanhSocket1Result = 0;
	int m_ActionXilanhSocket2Result = 0;
	int m_ActionXilanhSocket3Result = 0;
	int m_ActionXilanhSocket4Result = 0;
	//Robot Unload test
	int m_NoRobotUnloadTest = 0;
	int m_SocketUnloading = 0;
	bool m_Tool1Unloading = false ;
	bool m_Tool2Unloading = false;
	bool m_flagtoolunloading = false;
	bool m_SaveResultTestTool1 = false;
	bool m_SaveResultTestTool2 = false;
	int m_UnloadingLoading[4];
	//Robot move tray OK/NG
	int m_NorobotmovetrayOKNG = 0;
	int m_NorobotmovetrayOKNG0 = 0;
	int m_NorobotmovetrayOKNG1 = 0;

	int m_UnloadingTrayOK1 = 0;
	int m_UnloadingTrayNGLeft1 = 0;
	int m_UnloadingTrayNGRight1 = 0;

	bool m_ResulttestTool1Unloading = false;
	bool m_ResulttestTool2Unloading = false;
	int  m_ActionTool1Unloading = 0;
	//Check tray OK NG full 
	int  m_ActionDownZUnloading = 0;
	//bool m_CheckTrayOKFull = false;
	bool m_CheckTrayNGLeftFull = false;
	bool m_CheckTrayNGRightFull = false;
	//
	CString m_DataVision;
	CString m_NoLoadingRun;
	int m_iLoading, m_jLoading;
	int i_trayLoading,j_trayLoading;
	int i_trayUnloadingLeft, j_trayUnloadingLeft;
	int i_trayUnloadingRight, j_trayUnloadingRight;
	bool m_OnStatusPictureLoading = false;
	bool m_OnStatusPictureUnloadingLeft = false;
	bool m_OnStatusPictureUnloadingRight = false;
	//---Unloading tray
	int m_trayUnloading = 0;
	bool m_flagDown = false;
	int m_NumberAline = 0;
	//Unloading tray loading full
	int m_NoUnloadingFull = 0;
	//Buffer
	int m_ActionXilanh = 0;
	bool m_FlagListViewLog = false;
	CString m_DataListViewLog;
	//manual
	bool m_manualloading = false;
	bool m_manualunloading = false;
	//
	double   NumberReturn;//////Result Return
	CString  CharReturn;///////Result Return
	bool OriginComplete = false;
	//
	bool m_StatusInitsocket = false;
	bool m_StatusOriginZLoading = false;
	bool m_StatusOriginZUnloading = false;

	CString m_DataBufferVison;
	//Create New model
	vector<CreatNewModel> CNewModel;
	BOOL     CreateModelSuccses = FALSE;
	void     ReadDataModel();
	void     SaveNameDataAll();
	void     DeleteForder(CString m_path);
	void     InitalinePos();
	void     ReadDataPosition(CString m_Path,int m_Picture);
	void     ReadDataStatusUnloading(CString m_Path);
	void     FindXYS(CString m_data, long &mx, long &my, long &mz, BOOL &ms);
	BOOL InitSocket();
	void SetupInitiaization();
	BOOL ReadInput(int m_input);
	BOOL ReadOutput(int m_output);
	void SetOutput(int m_output);
	void ResetOutput(int m_output);
	void ReadInforDataMotion();
	void ReadInforDataIO();
	void PowerAirOn();
	void PowerAirOff();
	void ConveyorLoadingOn();
	void ConveyorLoadingOff();
	void ChanTrayLoadingOn();
	void ChanTrayLoadingOff();
	void XilanhDoTrayLoadingOn();
	void XilanhDoTrayLoadingOff();
	void XilanhAlineTrayLoadingOn();
	void XilanhAlineTrayLoadingOff();
	void XilanhChotTrayLoadingOn();
	void XilanhChotTrayLoadingOff();
	void ConveyorUnloadingOn();
	void ConveyorUnloadingOff();
	void ChanTrayUnloadingOn();
	void ChanTrayUnloadingOff();
	void XilanhDoTrayUnloadingOn();
	void XilanhDoTrayUnloadingOff();
	void XilanhAlineTrayUnloadingOn();
	void XilanhAlineTrayUnloadingOff();
	void XilanhChotTrayUnloadingOn();
	void XilanhChotTrayUnloadingOff();
	void XilanhAlineOn();
	void XilanhAlineOff();
	void OpenDoorAfter();
	void CloseDoorAfter();
	void XilanhTool1On();
	void XilanhTool1Off();
	void XilanhTool2On();
	void XilanhTool2Off();
	void VaccumTool1On();
	void VaccumTool1Off();
	bool GetSignVaccumTool1Unloading();
	void VaccumTool2On();
	void VaccumTool2Off();
	void XilanhTool3On();
	void XilanhTool3Off();
	void VaccumTool3On();
	void VaccumTool3Off();
	void XilanhTool4On();
	void XilanhTool4Off();
	void VaccumTool4On();
	void VaccumTool4Off();
	void VaccumTrayRobotOn();
	void VaccumTrayRobotOff();
	void XilanhTool1RobotLoadingOn();
	void XilanhTool1RobotLoadingOff();
	void VaccumTool1RobotLoadingOn();
	void VaccumTool1RobotLoadingOff();
	void XilanhTool2RobotLoadingOn();
	void XilanhTool2RobotLoadingOff();
	void VaccumTool2RobotLoadingOn();
	void VaccumTool2RobotLoadingOff();
	void XilanhTool1RobotUnloadingOn();
	void XilanhTool1RobotUnloadingOff();
	void VaccumTool1RobotUnloadingOn();
	void VaccumTool1RobotUnloadingOff();
	void XilanhTool2RobotUnloadingOn();
	void XilanhTool2RobotUnloadingOff();
	void VaccumTool2RobotUnloadingOn();
	void VaccumTool2RobotUnloadingOff();
	void XilanhSocket1ForWard();
	void XilanhSocket1BackWard();
	void XilanhSocket1Up();
	void XilanhSocket1Down();
	void VaccumSocket1On();
	void VaccumSocket1Off();
	void XilanhSocket2ForWard();
	void XilanhSocket2BackWard();
	void XilanhSocket2Up();
	void XilanhSocket2Down();
	void VaccumSocket2On();
	void VaccumSocket2Off();
	void XilanhSocket3ForWard();
	void XilanhSocket3BackWard();
	void XilanhSocket3Up();
	void XilanhSocket3Down();
	void VaccumSocket3On();
	void VaccumSocket3Off();
	void XilanhSocket4ForWard();
	void XilanhSocket4BackWard();
	void XilanhSocket4Up();
	void XilanhSocket4Down();
	void VaccumSocket4On();
	void VaccumSocket4Off();
	void OpenDoorFrontLeftOn();
	void OpenDoorFrontLeftOff();
	void OpenDoorFrontRightOn();
	void OpenDoorFrontRightOff();
	void OpenDoorSideRightOn();
	void OpenDoorsideRightOff();
	void OpenDoorSideLeftOn();
	void OpenDoorsideLeftOff();
	void AlarmOn();
	void AlarmOff();
	//Work Tray
	int RowTray = 5;
	int ColumnTray = 5;
	CString NameModelUse = "NoName";
	BOOL StatusLoadingModel = FALSE;
	BOOL StatusLoadingModel2 = FALSE;
	BOOL FlagInOut = FALSE;
	int ModelAction = 0;
	double DistanceTrayX = 100;
	double DistanceTrayY = 100;

	public:
	MotionPositionRun datapos;
	vector<MotionPositionRun> PosY;
	vector<vector<MotionPositionRun>> PosXY[3];
	vector<CString> DataInforCardMotion;
	vector<CString> DataInforCardIO;
	BOOL StatusOpenCard = FALSE;

	//TCP
	ClientSocket* mClient;//Mr.Dang Quang
	GTCRobotCtrl2* m_client;//Mr.Cao Huy
	int ChoiceMethol = 0;
	CString m_IpEthenet;
	int m_PortServer;
	bool FlagConnectEthernet;
//	bool FlagMotionDoneRobot = false;
	bool FlagMotionVisionDoneRobot = false;
	bool FlagRevice = false;
	//Ready
	bool m_ReadySuccess = false;
	//EndTray
	bool m_EndTray = false;
	//Loading
	CString CmRunRobotLoadingTool1Up;
	CString CmRunRobotLoadingTool2Up;
	CString CmRunRobotLoadingTool1Down;
	CString CmRunRobotLoadingTool2Down;
	//Unloading tray NG left
	CString	CmRunRobotUnloadingLeftTool3Up;
	CString	CmRunRobotUnloadingLeftTool4Up;
	CString	CmRunRobotUnloadingLeftTool3Down;
	CString	CmRunRobotUnloadingLeftTool4Down;
	//Unloading tray NG Right
	CString	CmRunRobotUnloadingRightTool3Up;
	CString	CmRunRobotUnloadingRightTool4Up;
	CString	CmRunRobotUnloadingRightTool3Down;
	CString	CmRunRobotUnloadingRightTool4Down;
	//Unloading tray OK
	CString	CmRunRobotUnloadingTrayOKTool3Up;
	CString	CmRunRobotUnloadingTrayOKTool4Up;
	CString	CmRunRobotUnloadingTrayOKTool3Down;
	CString	CmRunRobotUnloadingTrayOKTool4Down;
	//
	CString	CmRunRobotLoadingSocket1Tool1Up;
	CString	CmRunRobotLoadingSocket2Tool1Up;
	CString	CmRunRobotLoadingSocket3Tool1Up;
	CString	CmRunRobotLoadingSocket4Tool1Up;

	CString	CmRunRobotLoadingSocket1Tool1Down;
	CString	CmRunRobotLoadingSocket2Tool1Down;
	CString	CmRunRobotLoadingSocket3Tool1Down;
	CString	CmRunRobotLoadingSocket4Tool1Down;

	CString	CmRunRobotLoadingSocket1Tool2Up;
	CString	CmRunRobotLoadingSocket2Tool2Up;
	CString	CmRunRobotLoadingSocket3Tool2Up;
	CString	CmRunRobotLoadingSocket4Tool2Up;

	CString	CmRunRobotLoadingSocket1Tool2Down;
	CString	CmRunRobotLoadingSocket2Tool2Down;
	CString	CmRunRobotLoadingSocket3Tool2Down;
	CString	CmRunRobotLoadingSocket4Tool2Down;
	//
	CString	CmRunRobotVisionTool1;
	CString	CmRunRobotVisionTool2;
	CString	CmRunRobotAlineTool1;
	CString	CmRunRobotAlineTool2;
	CString	CmRunRobotAlinePickTool1;
	CString	CmRunRobotAlinePickTool2;
	//
	CString	CmRunRobotUnloadingSocket1Tool3Up;
	CString	CmRunRobotUnloadingSocket2Tool3Up;
	CString	CmRunRobotUnloadingSocket3Tool3Up;
	CString	CmRunRobotUnloadingSocket4Tool3Up;
					
	CString	CmRunRobotUnloadingSocket1Tool3Down;
	CString	CmRunRobotUnloadingSocket2Tool3Down;
	CString	CmRunRobotUnloadingSocket3Tool3Down;
	CString	CmRunRobotUnloadingSocket4Tool3Down;
				
	CString	CmRunRobotUnloadingSocket1Tool4Up;
	CString	CmRunRobotUnloadingSocket2Tool4Up;
	CString	CmRunRobotUnloadingSocket3Tool4Up;
	CString	CmRunRobotUnloadingSocket4Tool4Up;
					
	CString	CmRunRobotUnloadingSocket1Tool4Down;
	CString	CmRunRobotUnloadingSocket2Tool4Down;
	CString	CmRunRobotUnloadingSocket3Tool4Down;
	CString	CmRunRobotUnloadingSocket4Tool4Down;

	//
	CString	CmRunRobotUnloadingTrayLoading;
	CString	CmRunRobotUnloadingTrayUnloading;
	//
	CString	CmRunRobotDownMore;
	//Motion
	MotionLBR                 Motion;
	MotionInitial             DataSettup;
	MotionDataMotor           DataMotor;
	MotionPositionRun         DataPosition;
	double m_SpeedJog = 10000;

	double PosZ1Up;
	double PosZ1Down;
	double PosZ2Up;
	double PosZ2Down;
	double PosZ2Medium;
	double PointStopJogLoading;
	double PointStopJogUnloading;
	double OffsetJogLoadingZ1;
	bool RunPosLoading(double mPosition);
	bool RunPosUnloading(double mPosition);
	void ReadDataPointAxisZ();
	void ReadDataPhone();
	void ReadDataMotor();
	//Tester
	DataTester m_DataTester[4];
	bool ActionOne = false;
	//Rs232
	SerialCtrl m_Connect_com;
	CString m_COMConnect;
	CString m_BaudRate;
	CString m_DataReviceCom;
	void m_SendData(CString m_Data);
	CString m_ReviceData(CString m_data);
	BOOL m_ResultConnect =  false;
	//Buffer
	bool m_FlagBuffer;
	//Delay Vaccum
	int DelayVaccumToolRobot1;
	int DelayVaccumToolRobot2;
	int DelayVaccumToolRobot3;
	int DelayVaccumToolRobot4;
	int DelayVaccumSocket1;
	int DelayVaccumSocket2;
	int DelayVaccumSocket3;
	int DelayVaccumSocket4;
	int DelayVaccumTrayRobot;
	//Delay Cylinder
	int DelayCylinderTool1Robot;
	int DelayCylinderTool2Robot;
	int DelayCylinderTool3Robot;
	int DelayCylinderTool4Robot;

	int DelayCylinderSocket1FwRv;
	int DelayCylinderSocket2FwRv;
	int DelayCylinderSocket3FwRv;
	int DelayCylinderSocket4FwRv;

	int DelayCylinderSocket1UpDown;
	int DelayCylinderSocket2UpDown;
	int DelayCylinderSocket3UpDown;
	int DelayCylinderSocket4UpDown;

	int DelayCylinderHandler;
	int DelayCylinderAline;
	int DelayCylinderRotation;
	int DelayCylinderStack;
	//
};
