#ifndef DEFSYSTEM_H
#define DEFSYSTEM_H


#include <sstream>
#include <string>
#include <stdio.h>
#include "stdafx.h"
#include <atlstr.h>
#include "MainFrm.h"


//#include "DefActuator.h"

#if defined(_WIN64)
const CString	DEF_RUNTIME_PATH = _T("C:\\RAP");
#else
//const CString	DEF_RUNTIME_PATH = _T("C:\\RAP_x86");
const CString	DEF_RUNTIME_PATH = _T("C:\\MIS");
#endif

/************************************************************************/
/*  Operation Mode							                            */
/************************************************************************/
enum EOpMode
{
	READY_MODE,
	AUTORUN_MODE,
	STOP_MODE,
};
/************************************************************************/
/*  Operation Status						                            */
/************************************************************************/
enum EOPStatus
{
	INIT_STATUS,
	ERROR_STOP,
	STEP_STOP,
	CYCLE_STOP,
	START_RUN,
	RUN,
	RUN_SAFTY,
};
/************************************************************************/
/* User Group								                            */ 
/************************************************************************/
enum EUserGroup
{
	OPERATOR_GROUP,
	ENGINEER_GROUP,
	MAKER_GROUP
};

/************************************************************************/
/*  Run Mode							                            */
/************************************************************************/
enum ERunMode
{
	NORMAL_RUN_MODE,	// 정상 운전
	PASS_RUN_MODE,		// 통과 운전
	DRY_RUN_MODE,		// 물류 흐름 없는 운전
	STEP_RUN_MODE,		// 
//	UNIT_RUN_MODE,
	LONG_RUN_MODE,
	NORMAL_LONG_RUN_MODE,	// 정상 반복 운전
	REPAIR_RUN_MODE,

	MAX_RUN_MODE,
};
//핸들러 관련 정의
enum ETesterFunction
{			
	eModuleState_None,
	eModuleState_Empty,					//투입대기자재
	eModuleState_Testing,				//검사중인자재
	eModuleState_Pass,					//양품
	eModuleState_NG,					//불량

};
enum eIndex1 {
	INDEX_A,
	INDEX_B
};
enum eIndex2 {
	INDEX_C,
	INDEX_D
};
enum EStep {
	NONE = 0,
	OPEN_APP,		
	OPEN_CAMWIDE,	
	OPEN_CAMTELE,	
	SEND_RES_OK,
	SEND_RES_NG,
	SEND_RES_NG_STAIN,
	SEND_RES_NG_DARKSPOT

};
enum eResult
{
	OK = 1,
	NG_STAIN = 25,
	NG_DARKSPOT = 30,
	NG = 20
};
struct sClient
{
	CString strIP = "";
	int iPort = -1;
	double dTime = 100;

};
struct TesterData_Rpy {
	int				m_iStation = 0;
	int				m_iIndex = 0;
	int				m_iRetrycnt = 0;

	ETesterFunction	m_eModuleState = eModuleState_None;
	int				m_iFailcode = 0;
	CString			m_strFailname = "";
	BOOL			m_bAlarm = FALSE;
	CString			m_strAlarm_msg = "";

	BOOL			m_bSkip = FALSE;

	BOOL			m_bAct = FALSE;
};

#define STR_NONE					 "0"
#define STR_OPEN_APP				 "1"
#define STR_OPEN_CAMWIDE			 "2"
#define STR_OPEN_CAMTELE			 "3"
#define STR_SEND_RES_OK				 "4"
#define STR_SEND_RES_NG_STAIN		 "5"
#define STR_SEND_RES_NG_DARKSPOT	 "6"


#define		NUM_DEVICE		4



#define     START_APPLICATION " shell am start -W -S com.checkdustcam.checkdustcam/com.checkdustcam.checkdustcam.MainActivity"
#define     START_INSPECTION  " shell input tap 1473 980"
//#define		START_INSPECTION	" shell am start -W -S com.sec.android.app.camera/com.sec.android.app.camera.Camera" 

#define     ADB			      "adb -s " 
#define     TAKE_PICTURE	  " shell input tap 540 1915"
#define		CHECK_CAM		" shell input tap 930 1200"
#define		REBOOT			" shell am reboot"
#define		PULL_IMAGE_OK		" -a pull /storage/emulated/0/CheckDustCam/OK C:\\"
#define		PULL_IMAGE_NG		" -a pull /storage/emulated/0/CheckDustCam/NG C:\\"
#define		ADB_CHECK_CONNECT		"adb devices"   
#define		CHECK_LIST_SOCKET       "netstat -ano"
#define		FIND_PID_SOCKET			"netstat -ano | findstr :"
#define		STATUS_SOCKET			"\tLISTENING"
#define     CHECK_READY				"FUNCTION=TESTER_READY STATION_NO=0 LAST_MODULE=NO"
#define     TEST_CAM				"FUNCTION=TESTER_START STATION_NO=0 SKIP=NO RETRY_CNT=0"
#define     TEST_SKIP				"FUNCTION=TESTER_START STATION_NO=0 SKIP=YES RETRY_CNT=0"
#define     ERR_IRIS				23

	

#define     TIME_RECHECK		1000
#define		TIME_DELAY			2


	


const	int	SUCCESS						= 0;

const	int DEF_TEST_RESULT_NONE		= -1;
const	int	DEF_TEST_RESULT_PASS		= 0;
const	int DEF_TEST_RESULT_FAIL		= 1;
const	int DEF_TEST_RESULT_ERROR		= 2;
const	int DEF_TEST_RESULT_SKIP		= 3;
const	int DEF_TEST_RESULT_NO_DATA		= 4;
const	int DEF_TEST_RESULT_INIT		= 5;
const	int DEF_TEST_RESULT_WAIT		= 6;

/************************************************************************/
/* Robot Error -							                            */
/************************************************************************/
enum ERobotError
{
	ROBOT_ERROR_NONE = 0,
	ROBOT_ERROR_RETRY = 100,
	ROBOT_ERROR_RESET = 200,
};

/************************************************************************/
/*  System 관련								                            */
/************************************************************************/

enum EGUIID
{
	eGUIID_None = -1,
	eGUIID_AutoManager = 0,
	eGUIID_Robot,
	eGUIID_InputCV,
	eGUIID_TraySupplier,
	eGUIID_TrayReceiver,
	eGUIID_RouterIF,
//	eGUIID_Shuttle,

	eGUIID_Max_Num,
	eGUIID_All,
};
enum ePhone
{
	PHONE_1 = 0,
	PHONE_2,
	PHONE_3,
	PHONE_4

};

//const int DEF_MAX_FUNCTION_TEST		= 24;

const int DEF_MAX_MODEL					= 255;	// Number of SYSTEM MODEL

const int DEF_WS_EX_LAYERED				= 0x00080000;
const int DEF_LWA_COLORKEY				= 0x00000001;
const int DEF_LWA_ALPHA					= 0x00000002;
const int DEF_ULW_COLORKEY				= 0x00000001;
const int DEF_ULW_ALPHA					= 0x00000002;
const int DEF_ULW_OPAQUE				= 0x00000004;

const int DEF_STEP_DISP_MAX_COUNT		= 10000;

/************************************************************************/
/*  system									                            */
/************************************************************************/

/************************************************************************/
/*  Jog										                            */
/************************************************************************/
const	int DEF_MAX_JOG_LIST			= 5;

const	int	DEF_JOG_SCARA_ROBOT			= 0;
const	int	DEF_JOG_INPUTCV				= 1;
const	int	DEF_JOG_TRAY_SUPPLIER		= 2;
const	int	DEF_JOG_TRAY_RECEIVER		= 3;
const	int	DEF_JOG_SHUTTLE				= 4;



/************************************************************************/
/*  Ethernet Communication					                            */
/************************************************************************/
#define		DEF_SOCKET_IP_VISION		"127.0.0.1"
#define		DEF_SOCKET_PORT_VISION		9999
#define		WM_ETHERNET_CONNECT			WM_USER+1000
#define		WM_ETHERNET_CONNECT2		WM_USER+1001
#define		WM_ETHERNET_RECEIVE			WM_USER+1002
#define		WM_ETHERNET_CLOSE			WM_USER+1003

#define		WM_ETHERNET_RUNNING			WM_USER+1004
#define		WM_ETHERNET_RECEIVE_FILE	WM_USER+1005
#define		WM_ETHERNET_RECEIVE_FILE2	WM_USER+1006




#define		DEF_STATUS_READY			0
#define		DEF_STATUS_TESTING			1
#define		DEF_STATUS_PASS				2
#define		DEF_STATUS_FAIL				3


#define		DEF_SOCKET_RETRY			3

// Camera
#define	WM_BUSRESET			( WM_USER + 2100 )
#define	WM_LOSTBUSRESET		( WM_USER + 2101 )
#define	WM_POWERUP			( WM_USER + 2112 )

enum EEthernet
{
	SOCKET_SEND,
	SOCKET_RECIEVE
};


/************************************************************************/
/*  Dialog & View							                            */
/************************************************************************/
const int DEF_FIX_MODE					= 0;
const int DEF_MODEL_MODE				= 1;

/************************************************************************/
/*  Error Info									                        */
/************************************************************************/


/** Mark Name 설정을 위한 Macro Define*/
#define	DEF_MARK_NAME(x)				#x

/** Time Out 설정*/
#define ITI_TIMEOUT						100
#define	M2M_TIMEOUT						5

/************************************************************************/
/*  Timer ID									                        */
/************************************************************************/

#define UPDATE_TIMER_AUTOMAIN			1
#define UPDATE_TIMER_MANUALDLG			8
#define UPDATE_TIMER_MANUALTESTDLG		9
#define UPDATE_TIMER_TEACHINGDLG		10
#define UPDATE_TIMER_STEP_DISP_DLG		11
#define UPDATE_TIMER_GRAPHRUMBADLG		12
#define UPDATE_TIMER_ROBOTJOG			13

#define UPDATE_TIMER_SENDFILE_XML		14
#define UPDATE_TIMER_SENDFILE_JPG		15
#define UPDATE_TIMER_GETFILE_JPG		16

#define UPDATE_TIMER_DISPlAYSOCKET		17


#define	UPDATE_TIMER_PERIOD				500
#define UPDATE_TIMER_PERIOD_ROBOTJOG	100				


/************************************************************************/
/*  Color										                        */
/************************************************************************/

 ////////////////////////////////////////////////
    #define	MY_DEFAULT		0x00C8D0D4
    		
    #define	MY_BLACK		0X00000000	
    #define	MY_BLUE			0x00FF0000
    #define	MY_BROWN		0X002A2AA5
    #define	MY_DARK_BLUE	0x008B0000	
    #define MY_DARK_BROWN	0x00000040		
    #define	MY_DARK_CYAN	0X008B8B00		
    #define	MY_DARK_GRAY	0x00808080		
    #define	MY_DARK_GREEN	0X00006400		
    #define	MY_DARK_MAGENTA	0X008B008B		
    #define	MY_DARK_ORANGE	0X000060FF		
    #define	MY_DARK_RED		0X0000008B	
    #define MY_DARK_SLATEGRAY	0x002F4F4F
    #define	MY_DARK_VIOLET	0X009400D3		
    #define	MY_FIREBRICK	0X003030FF		
    #define	MY_GOLD			0X000EADFF
    #define	MY_GRAY			0x00C0C0C0
    #define	MY_GREEN		0x0000FF00	
    #define	MY_LIGHT_GRAY	0X00D3D3D3		
    #define	MY_LIGHT_GREEN	0X0090EE90		
    #define	MY_LIGHT_YELLOW	0x00D2FFFF		
    #define	MY_MAGENTA		0X00FF00FF	
    #define	MY_ORANGE		0X0000A5FF	
    #define	MY_ORANGERED	0X000045FF		
    #define	MY_ORCHID		0X00DA70D6	
    #define	MY_RED			0x000000FF
    #define	MY_VIOLET		0X00EE82EE	
    #define	MY_WHITE		0X00FFFFFF	
    #define	MY_YELLOW		0x0000FFFF	
	#define MY_BUTTON_BACK	0x008A8A8A


struct dPOS
{
	double x;
	double y;
};
class dROI 
{
public:
	dROI(){ Clear(); };
	~dROI(){ Clear(); };

	void Clear()
	{
		LeftTop.x		= 0;
		LeftTop.y		= 0;
		RightBottom.x	= 0;
		RightBottom.y	= 0;
		Center.x		= 0;
		Center.y		= 0;
		Size.x			= 0;
		Size.y			= 0;
	};

public:
	dPOS LeftTop;
	dPOS RightBottom;
	dPOS Center;
	dPOS Size;
};

/************************************************************************/
/* Stage State                                                           */
/************************************************************************/
enum EStageState //enumStageState
{
	STAGE_STATE_NOINIT = -2,
	STAGE_STATE_NOUSE = -1,
	STAGE_STATE_STOP	 = 0,
	STAGE_STATE_READY,	
	STAGE_STATE_TEST,
	STAGE_STATE_PASS,
	STAGE_STATE_FAIL,
	STAGE_STATE_ERROR,	
	STAGE_STAGE_BLOCKING,
	STAGE_STAGE_EP_BLOCKING,
	STAGE_STATE_DEV_FAIL,
};

/************************************************************************/
/* Head State                                                           */
/************************************************************************/

enum EHeadState//enumHeadState
{
	HEAD_STATE_NOINIT = -2,
	HEAD_STATE_STOP	 = -1,
	HEAD_STATE_READY = 0,	
	HEAD_STATE_WORKING,
	HEAD_STATE_TESTWAIT,
	HEAD_STATE_COMPLETE,
	HEAD_STATE_SAFTY,
	HEAD_STATE_ERROR,	
};

/************************************************************************/
/* Fail Handling Method	                                                */
/************************************************************************/
enum EFailHandlingMethod//enumFailHandlingMethod
{
	eFailHandling_Stop = 0,
	eFailHandling_Continue = 1,
};

/************************************************************************/
/*                         Stage Teaching Pos                           */
/************************************************************************/

enum ECoordinateType
{
	COORDINATE_TYPE_REAL = 0,
	COORDINATE_TYPE_CURRENT,
	COORDINATE_TYPE_MAX,
};

enum EAxisTitle
{
	AXIS_TITLE_R = 0,
	AXIS_TITLE_MAX,
};

/** Working Position Index Define */
const	int	DEF_NONE_POS					= -1;

//Unitbox//
enum EStepUnitBoxProcess
{
	STEP_UNIT_BOX_NONE = -1,
	STEP_UNIT_INIT = 0,
	STEP_UNIT_RESET_BUFFER_SOCKET,
	STEP_UNIT_WAIT_SS_CV_PREV,
	STEP_UNIT_WAIT_SS_CV_PREV2,
	STEP_UNIT_WAIT_STOP_CV_PRE,
	STEP_UNIT_WAIT_DETECT,
	STEP_UNIT_WAIT_DETECT2,
	STEP_UNIT_ALIGHT_OK,
	STEP_UNIT_WAIT_STOP_CV,
	STEP_UNIT_REQUEST_VISON,
	STEP_UNIT_REQUEST_VISON2,

	STEP_UNIT_RUN_VISON_0,
	STEP_UNIT_RUN_VISON_1,
	STEP_UNIT_RUN_VISON_2,
	STEP_UNIT_RUN_VISON_3,
	STEP_UNIT_RUN_VISON_4,

	STEP_UNIT_WAIT_RESULT_VISON_0,
	STEP_UNIT_WAIT_RESULT_VISON_1,
	STEP_UNIT_WAIT_RESULT_VISON_2,
	STEP_UNIT_WAIT_RESULT_VISON_3,
	STEP_UNIT_WAIT_RESULT_VISON_4,
	STEP_UNIT_WAIT_RESULT_SHOW,
	STEP_UNIT_UP_CL,
	STEP_UNIT_WAIT_UP,
	STEP_UNIT_WAIT_CYLINDOR_RETURN,
	STEP_UNIT_WAIT_CYLINDOR_RETURN2,
	STEP_UNIT_WAIT_UNIT_OUT,
	STEP_UNIT_FINISH,
	STEP_UNIT_BYPASS_INIT,
	STEP_UNIT_BYPASS_WAIT_DETECT_UNIT,
	STEP_UNIT_BYPASS_WAIT_DETECT_UNIT2,
	STEP_UNIT_BYPASS_WAIT_DETECT_IN_CV,
	STEP_UNIT_BYPASS_WAIT_UNITBOX_IS_PASS,
	STEP_UNIT_NG,
	STEP_UNIT_WAIT_RESET,
	STEP_UNIT_WAIT_RESET2,
	STEP_UNIT_INIT_TEACH,
	STEP_UNIT_INIT_TEACH2,
	STEP_UNIT_WAIT_DETECT_TEACH,
	STEP_UNIT_WAIT_DETECT2_TEACH,
	STEP_UNIT_WAIT_STOP_CV_TEACH,
	STEP_UNIT_WAIT_FOCUS_TEACH,
	STEP_UNIT_WAIT_FINISH_TEACH,

	STEP_UNIT_TESTVISION_INIT,
	STEP_UNIT_TESTVISION_REQUEST_VISION

};

enum ERobotPos
{
	eRobotPos_None = -1,

	// System : 0 ~ 9
	eRobotPos_Home = 0,
	eRobotPos_ArmChange,
	eRobotPos_Ready1,		// Router Complete wait Pos
	eRobotPos_Ready2,		// PCB Input Wait Pos
	eRobotPos_Ready3,		// Tray


	eRobotPos_TrayPick,
	eRobotPos_TrayPlace,
	eRobotPos_ScrapTrash,
	eRobotPos_NG1,
	eRobotPos_NG2,

	// InputCV, Router, Buffer : 10 ~ 19
	eRobotPos_RouterJig1_1,
	eRobotPos_RouterJig1_2,
	eRobotPos_RouterJig2_1,
	eRobotPos_RouterJig2_2,

	eRobotPos_PCBBuffer1_1,
	eRobotPos_PCBBuffer1_2,
	eRobotPos_PCBBuffer2_1,
	eRobotPos_PCBBuffer2_2,

	eRobotPos_PCBPickUp,
	eRobotPos_NG_READY,

	// Array Place On Tray : 20 ~ 29
	eRobotPos_ArrayPlace_1,
	eRobotPos_ArrayPlace_2,
	eRobotPos_ArrayPlace_3,
	eRobotPos_ArrayPlace_4,
	eRobotPos_ArrayPlace_5,
	eRobotPos_ArrayPlace_6,
	eRobotPos_ArrayPlace_7,
	eRobotPos_ArrayPlace_8,
	eRobotPos_ArrayPlace_9,
	eRobotPos_ArrayPlace_10,

	// BCR - Buffer1 : 30 ~ 39
	eRobotPos_BCR_Buffer1_Array1,
	eRobotPos_BCR_Buffer1_Array2,
	eRobotPos_BCR_Buffer1_Array3,
	eRobotPos_BCR_Buffer1_Array4,
	eRobotPos_BCR_Buffer1_Array5,
	eRobotPos_BCR_Buffer1_Array6,
	eRobotPos_BCR_Buffer1_Array7,
	eRobotPos_BCR_Buffer1_Array8,
	eRobotPos_BCR_Buffer1_Array9,
	eRobotPos_BCR_Buffer1_Array10,

	// BCR - Buffer2 : 40 ~ 49
	eRobotPos_BCR_Buffer2_Array1,
	eRobotPos_BCR_Buffer2_Array2,
	eRobotPos_BCR_Buffer2_Array3,
	eRobotPos_BCR_Buffer2_Array4,
	eRobotPos_BCR_Buffer2_Array5,
	eRobotPos_BCR_Buffer2_Array6,
	eRobotPos_BCR_Buffer2_Array7,
	eRobotPos_BCR_Buffer2_Array8,
	eRobotPos_BCR_Buffer2_Array9,
	eRobotPos_BCR_Buffer2_Array10,

	eRobotPos_Max_Num,
};
const	int DEF_ROBOT_MAX_POSITION				= 50;


const	int DEF_CVLIFTER_MAX_POSITION			 = 5;

// Input Conveyor PCB Guide
const	int DEF_INPUTCV_PCBGUIDE_MAX_POSITION	= 2;
const	int DEF_POS_INPUTCV_HOME				= 0;
const	int DEF_POS_INPUTCV_PCBGUIDE			= 1;

// Tray Supplier Position
const	int DEF_TRAYSUPPLIER_MAX_POSITION		= 3;

const	int DEF_POS_TRAYSUPPLIER_RECEIVE		= 0;
const	int DEF_POS_TRAYSUPPLIER_LIMIT			= 1;
const	int DEF_POS_TRAYSUPPLIER_SHORTAGE		= 2;

// Tray Receiver Position
const	int DEF_TRAYRECEIVER_MAX_POSITION			= 3;
const	int DEF_POS_TRAYRECEIVER_EMPTY_TOP			= 0;
const	int DEF_POS_TRAYRECEIVER_STACKFULL_BOTTOM	= 1;
const	int DEF_POS_TRAYRECEIVER_UNLOADING			= 2;

// Shuttle 
const	int DEF_SHUTTLE_MAX_POSITION				= 4;
const	int DEF_POS_SHUTTLE_MOVING_RECEIVE			= 0;
const	int DEF_POS_SHUTTLE_MOVING_SUPPLY			= 1;
const	int DEF_POS_SHUTTLE_PCBGGUIDE_HOME			= 2;
const	int DEF_POS_SHUTTLE_PCBGUIDE_PCBGUIDE		= 3;

/*
// Shuttle PCB Guide
const	int DEF_SHUTTLE_PCBGUIDE_MAX_POSITION		= 2;
const	int DEF_POS_SHUTTLE_PCBGGUIDE_HOME			= 0;
const	int DEF_POS_SHUTTLE_PCBGUIDE_PCBGUIDE		= 1;

// Shuttle Moving
const	int DEF_SHUTTLE_MOVING_MAX_POSITION			= 2;
const	int DEF_POS_SHUTTLE_MOVING_RECEIVE			= 0;
const	int DEF_POS_SHUTTLE_MOVING_SUPPLY			= 1;
*/

const int DEF_NGBUFFER_MAX_POSITION_NUM				= 2;

const int DEF_MAX_JIGNUM_ON_ROUTER					= 2;
const int DEF_MAX_PCBNUM_ON_JIG						= 2;
const int DEF_MAX_ARRAYNNUM_ON_PCB					= 4;
const int DEF_MAX_PCBFLOATING_SENSOR_NUM			= 4;


/************************************************************************/
/*        MES Interface				                                   */
/************************************************************************/


enum EMESIF_ITEM
{
	eMESIF_None = -1,

	eMESIF_Server_InitSocket = 0,
	eMESIF_Client_ConnectSocket,		// Connecing Server
	eMESIF_Server_SuccessConnecting,

	eMESIF_Client_SendCNData,			// CN 스캔 정보 전송
	eMESIF_Client_SendCNData_1st_Tail,		// 첫번째거는 알려줘야한다.
	eMESIF_Server_ReceiveCNData,

	eMESIF_Server_MESError,				// 장비 Stop
	eMESIF_Server_TrayUnloading,		// 매거진 구성 완료, Tray 배출

	eMESIF_Client_MachineEStop,			// 설비측 비상 정지

	eMESIF_Server_MovingOrder,			// 이동지시 가능 시간 신호

	eMESIFItem_Max,
};

static const CString NAME_MESIF_PROTOCOL[eMESIFItem_Max] =
{
	_T("MA"),	// eMESIF_Server_InitSocket
	_T("JA"),	// eMESIF_Client_ConnectSocket,		// Connecing Server
	_T("MB"),	// eMESIF_Server_SuccessConnecting,
	_T("JB"),	// eMESIF_Client_SendCNData,			// CN 스캔 정보 전송
	_T("FST"),	// eMESIF_Client_SendCNData_1st,		// 첫번째거는 알려줘야한다.
	_T("MC"),	// eMESIF_Server_ReceiveCNData,
	_T("MD"),	// eMESIF_Server_MESError,				// 장비 Stop
	_T("ME"),	// eMESIF_Server_TrayUnloading,		// 매거진 구성 완료, Tray 배출

	_T("JC"),	// eMESIF_Client_MachineEStop,			// 설비측 비상 정지
	_T("MF"),	// eMESIF_Server_MovingOrder,
};


/************************************************************************/
/*  Router 관련					                            */
/************************************************************************/

enum ERouterJigID
{
	eRouterJig_None = -1,
	eRouterJig_1 = 0,
	eRouterJig_2 = 1,
	eRouterJig_Max_Num,
};

enum ERouterJigPCBID
{
	eRouterJigPCB_None = -1,
	eRouterJigPCB_1 = 0,
	eRouterJigPCB_2 = 1,
	eRouterJigPCB_Max_Num,
};

enum ERouterType
{
	eRouterType_None = -1,
	eRouterType_1PlateMoving = 0,
	eRouterType_2PlateMoving,
};


enum ERouterState
{
	eRouterState_None = -1,
	eRouterState_Ready = 0,
	eRouterState_Start,
	eRouterState_Running,
	eRouterState_Complete,
	eRouterState_Stop,
	eRouterState_Error,
};


//enum ERouterJigState
//{
//	eRouterJigState_NotUse = -1,
//	eRouterJigState_Empty = 0,
//	eRouterJigState_Loading,
//	eRouterJigState_BCRScan,
//	eRouterJigState_Running,
//	eRouterJigState_Complete,
//};

enum EPCBState
{
	ePCBState_NotUse = -1,
	ePCBState_Empty = 0,
	ePCBState_Loading,
	ePCBState_BCRScan,
	ePCBState_Running,
	ePCBState_Complete,
};

enum EArrayState
{
	eArrayState_None = -1,
	eArrayState_Loading,
	eArrayState_Pass,
	eArrayState_NG,
	eArrayState_Fail,
};

//Ethernet mode
enum EOpModeEthernet
{
	E_ETHERNET_RUN_MODE = 0,
	E_ETHERNET_SENFILE_MODE,
	E_ETHERNET_RECEVIE_MODE
};

//Mode Run
const	int DEF_LONG_RUN = 0;
const	int DEF_BYPASS = 1;
const	int DEF_TEST_VISION = 2;


struct SArrayData
{
	EArrayState eState;
	CString		strCode;
};

struct SPCBData
{
	EPCBState			eState;
	int					iArrayNumber;
	SArrayData			sArrayData[DEF_MAX_ARRAYNNUM_ON_PCB];
};

/************************************************************************/
/*  Tray에 Array Stack 관련  				                            */
/************************************************************************/
const int DEF_MAX_TRAY_COLUMN_NUM = 2;
const int DEF_MAX_TRAY_ROW_NUM = 4;
const int DEF_MAX_TRAY_ARRAYSTACK_NUM = DEF_MAX_TRAY_COLUMN_NUM*DEF_MAX_TRAY_ROW_NUM;
const int DEF_MAX_TRAY_STACK_NUM = 50;

class MArrayStackInfo
{
public:
	MArrayStackInfo() { Clear(); };
	~MArrayStackInfo() { Clear(); };

	void Clear()
	{
		bFill = FALSE;
		strCode = _T("");
	};

	void SetFill(CString str)
	{
		bFill = TRUE;
		strCode = str;
	};

	BOOL	bFill;
	CString strCode;
};

class MTrayStackInfo
{
public:
	MTrayStackInfo() { Clear(); };
	~MTrayStackInfo() { Clear(); };

	void Clear()
	{
		int iCol = 0, iRow = 0;
		for (iCol = 0; iCol < DEF_MAX_TRAY_COLUMN_NUM; iCol++)
			for (iRow = 0; iRow < DEF_MAX_TRAY_ROW_NUM; iRow++)
				m_ArrayFillData[iCol][iRow].Clear();

		m_iMaxColumnNum = 0;
		m_iMaxRowNum = 0;
	};

	void SetTrayMatrixData(int iCol, int iRow)
	{
		m_iMaxColumnNum = iCol;
		m_iMaxRowNum = iRow;
	};

	BOOL FillArray(int iCol, int iRow, CString str)
	{
		if (m_ArrayFillData[iCol][iRow].bFill == TRUE)
			return FALSE;

		m_ArrayFillData[iCol][iRow].SetFill(str);
		return TRUE;
	}

	BOOL ClearArray(int iCol, int iRow)
	{
		m_ArrayFillData[iCol][iRow].Clear();
		return TRUE;
	}


public:
	MArrayStackInfo m_ArrayFillData[DEF_MAX_TRAY_COLUMN_NUM][DEF_MAX_TRAY_ROW_NUM];

	int		m_iMaxColumnNum;
	int		m_iMaxRowNum;
};


//Mline
const int DEF_NO_LINE = 2;
const int DEF_NO_INIT = 5;
#endif // DEFSYSTEM_H

