#pragma once
#include "afxstr.h"
#include "AXHS.h"

#define IMAGE_WIDTH			1920
#define IMAGE_HEIGHT		1080

#define AxisX				0
#define	AxisY				1
#define	AxisZ				2

#define   TrayLoading 0
#define   TrayNgLeft  1
#define   TrayNgRight 2


#define	DangQuang			0
#define	CaoHuy				1

#define operation_stop	    1
#define operation_start	    2
#define operation_wait	    3
#define operation_EMG	    4

//Action Start
#define BufferLoading	                    1
#define RobotLoadingCam	                    2
#define RobotLoadingVision	                3
#define RobotLoadingfirst	                4
#define UnloadingTrayOKFull	                5
#define RobotUnloadingAndLoadingTest	    6
#define RobotMoveTrayOKNG	                7
#define CheckTrayOKNGFull	                8
#define RobotActionEndTray	                9

//Output
#define    ButtonStart                    0
#define    ButtonStop					  1
#define    ButtonHome					  2
#define    ButtonReset				      3
#define    PowerAir					      4
#define    Open_Door_Side_Left			  5
#define    Open_Door_Font_Left			  6
#define    Open_Door_Font_Right			  7
#define    Open_Door_Side_Right			  8
#define    LampRed					      9
#define    LampYellow					  10
#define    LampGreen					  11
#define    Alarm						  12
#define    Socket_UP_3					  13
#define    Socket_UP_4  				  14
#define    XL_Aline_CAM 				  15
#define    Socket_Vaccum_1				  16
#define    Socket_Vaccum_2				  17
#define    XL_Aline_Loading_Fw			  18
#define    XL_Aline_Loading_Rv			  19
#define    XL_Do_Tray_Loading_Fw		  20
#define    XL_Do_Tray_Loading_Rv		  21
#define    Socket_Vaccum_3				  22
#define    Socket_Vaccum_4				  23
#define    Output24					      24
#define    XL_Chan_Tray_Loading_Dung	  25
#define    XL_Chan_Tray_Loading_Nam	      26
#define    Conveyor_Loading			      27
#define    Conveyor_Loading_Rv			  28
#define    Look_After					   29
#define    Output30					      30
#define    Output31					      31
#define    Vaccum_Robot_4				  32
#define    Blow_Robot_3 				  33
#define    XL_Aline_Unloading_Fw		  34
#define    XL_Aline_Unloading_Rv		  35
#define    XL_Do_Tray_Unloading_Fw		  36
#define    XL_Do_Tray_Unloading_Rv		  37
#define    XL_Tool_Robot_4				  38
#define    XL_Tool_Robot_3				  39
#define    Socket_UP_2					  40
#define    XL_Chan_Tray_Unloading_Dung	  41
#define    XL_Chan_Tray_Unloading_Nam	  42
#define    Conveyor_Unloading			  43
#define    Conveyor_Unloading_Rv		  44
#define    Vaccum_Robot_3			      45
#define    Blow_Robot_4			          46
#define    Socket_FW_1					  47
#define    Socket_FW_2					  48
#define    XL_Chot_Stack_Loading_Fw	      49
#define    XL_Chot_Stack_Loading_Rv	      50
#define    Socket_FW_3					  51
#define    Socket_FW_4					  52
#define    XL_Chot_Stack_Unloading_Fw	  53
#define    XL_Chot_Stack_Unloading_Rv	  54
#define    Socket_UP_1			          55
#define    XL_Tool_Robot_1				  56
#define    Vaccum_Robot_1				  57
#define    Blow_Robot_1				      58
#define    XL_Tool_Robot_2				  59
#define    Vaccum_Robot_2				  60
#define    Blow_Robot_2					  61
#define    Robot_Vaccum_Tray			  62
#define    Output63					      63

//Input

#define    Button_Start                       0
#define    Button_Stop						  1
#define    Button_Home						  2
#define    Button_Reset						  3
#define    Socket1_Fw						  4
#define    Safety_Door_Side_Left			  5
#define    Safety_Door_Front_Left			  6
#define    Safety_Door_Front_Right			  7
#define    Safety_Door_Side_Right		   	  8
#define    Socket2_Up						  9
#define    Socket3_Fw						  10
#define    Socket3_Rv						  11
#define    Socket3_Up						  12
#define    Vaccum_Tool3_Robot				  13
#define    EMG     							  14
#define    Vaccum_Socket_1					  15
#define    Safety_Left						  16
#define    Detech_Tray_Up_Loading			  17
#define    SSXL_AlineTray_Loading_Out		  18
#define    SSXL_AlineTray_Loading_In		  19
#define    SSXL_Do_Tray_Loading_Out_Trai	  20
#define    SSXL_Do_Tray_Loading_In_Trai		  21
#define    SSXL_Do_Tray_Loading_Out_Phai	  22
#define    SSXL_Do_Tray_Loading_In_Phai	      23
#define    DetechTrayInput					  24
#define    SSXL_Chan_Tray_Loading_Dung		  25
#define    SSXL_Chan_Tray_Loading_Nam		  26
#define    Detech_Tray_On_Z_Loading			  27
#define    Detech_Tray_In_Loading			  28
#define    Vaccum_Socket_2					  29
#define    Vaccum_Socket_3					  30
#define    Vaccum_Socket_4					  31
#define    SafetyRight						  32
#define    Detech_Tray_Up_Unloading			  33
#define    SSXL_AlineTray_Unloading_Out	      34
#define    SSXL_AlineTray_Unloading_In		  35
#define    Socket2_Rv                         36
#define    Socket2_Fw                         37
#define    Socket1_Up                         38
#define    Socket1_Rv                         39
#define    Detech_Tray_On_Z_Unloading_Out	  40
#define    SSXL_Chan_Tray_Unloading_Dung	  41
#define    SSXL_Chan_Tray_Unloading_Nam		  42
#define    Detech_Tray_On_Z_Unloading		  43
#define    Detech_Tray_In_Unloading			  44
#define    SSXL_Tool3_RobotUp				  45
#define    SSXL_Tool4_RobotUp				  46
#define    Socket4_Up						  47
#define    Detech_Stack_Left				  48
#define    SSXL_Aline_FW		              49
#define    SSXL_Aline_BW            		  50
#define    Detech_Tray_Left_On				  51
#define    Detech_Stack_Right				  52
#define    SSXL_Chot_Stack_Unloading_Out	  53
#define    Safety_Door_After		          54
#define    Detech_Tray_Righ_On				  55
#define    SSXL_Tool2_RobotUp				  56
#define    Vaccum_Tool1_Robot				  57
#define    Vaccum_Tool4_Robot				  58
#define    SSXL_Tool1_RobotUp				  59
#define    Vaccum_Tool2_Robot				  60
#define    Socket4_Fw						  61
#define    Socket4_Rv						  62
#define    Vaccum_Tray_Robot				  63









enum TYPE_CHECK_COLOR
{
	COLOR_RED = 0,
	COLOR_BLUE,
	COLOR_YELLOW,
	COLOR_GREEN
};

typedef struct m_MotionInitial
{
	long  lPulse = 10000; // number of pulse for 1 rotation.
	double dUnit = 10; // movement distance during 1 rotation.

	DWORD MethodPulse0 = OneHighLowHigh;//method output pulse
	DWORD MethodPulse1 = OneHighHighLow;
	DWORD MethodPulse2 = OneLowLowHigh;
	DWORD MethodPulse3 = OneLowHighLow;
	DWORD MethodPulse4 = TwoCcwCwHigh;
	DWORD MethodPulse5 = TwoCcwCwLow;
	DWORD MethodPulse6 = TwoCwCcwHigh;
	DWORD MethodPulse7 = TwoCwCcwLow;
	DWORD MethodPulse8 = TwoPhase;
	DWORD MethodPulse9 = TwoPhaseReverse;


	DWORD MethodEncoderInput0 = ObverseUpDownMode;//Encoder Input Method
	DWORD MethodEncoderInput1 = ObverseSqr1Mode;
	DWORD MethodEncoderInput2 = ObverseSqr2Mode;
	DWORD MethodEncoderInput3 = ObverseSqr4Mode;//ok
	DWORD MethodEncoderInput4 = ReverseUpDownMode;
	DWORD MethodEncoderInput5 = ReverseSqr1Mode;
	DWORD MethodEncoderInput6 = ReverseSqr2Mode;
	DWORD MethodEncoderInput7 = ReverseSqr4Mode;

	DWORD EmergencyStop = 0;
	DWORD SlowdownStop = 1;

	DWORD   LOW = 0;
	DWORD	HIGH = 1;
	DWORD	UNUSED = 2;
	DWORD	USED = 3;

	DWORD uPositiveLevel0 = LOW;//Method linit+
	DWORD uPositiveLevel1 = HIGH;
	DWORD uPositiveLevel2 = UNUSED;
	DWORD uPositiveLevel3 = USED;

	DWORD uNegativeLevel0 = LOW;//Method linit-
	DWORD uNegativeLevel1 = HIGH;
	DWORD uNegativeLevel2 = UNUSED;
	DWORD uNegativeLevel3 = USED;

} MotionInitial;

typedef struct m_DataMotor
{
	double   Acc = 50;//Tang to - giam toc
	double   Dec = 50;
	double   defireSpeedJog = 1;
	double   SpeedJog = 1;//Speed Jog

	double   SpeedJog1 = 1; 
	double   SpeedJog2 = 1; 
	double   SpeedJog3 = 1; 

	double   SpeedOriginX = 40;
	double   SpeedOriginY = 40;
	double   SpeedOriginZ = 50;

	double   SpeedRunAxisXY = 40;
	double   SpeedRunAxisXYZ = 40;
	double   SpeedRunAxisX = 40;
	double   SpeedRunAxisY = 40;

	double   SpeedRunAxisZ1 = 40;
	double   SpeedRunAxisZ2 = 40;

} MotionDataMotor;

typedef struct m_PositionRun
{
	double dPositionX = 5;
	double dPositionY = 5;
	double dPositionZ = 5;
	BOOL   status = TRUE;
	BOOL   unloading = FALSE;

} MotionPositionRun;

typedef struct NewModel
{
	int Row = 5;
	int Column = 5;
	CString NameModel = "Quynhtuti";

} CreatNewModel;

typedef struct TesterInfo
{
	int TotalCount = 0;
	int GoodCount = 0;
	int NGCount = 0;
	int TactTime = 0;
	CString Status = "Empty";
	bool Action = true;//Khoa khong su dung
	bool Loading = true;//Da load CAM vao hay chua  true: chua co CAM trong socket, false :Da co CAM trong soc ket
	bool StatusTester = true;//Da ra lenh test hay chua True :la chua ra lenh test, false:Da ra lenh test
} DataTester;

