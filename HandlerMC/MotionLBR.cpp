#include "stdafx.h"
#include "MotionLBR.h"


MotionLBR::MotionLBR()
{
}


MotionLBR::~MotionLBR()
{
}

BOOL MotionLBR::Initiaization()
{
	DWORD m_Result = AxlOpen(7);
	if (m_Result != AXT_RT_SUCCESS) {
		AfxMessageBox("AxlOpen Fail...");
		return FALSE;
	}

	return TRUE;
}

void MotionLBR::ExitingLibrary()
{
	if (AxlClose())
	{

	}
}
CString MotionLBR::AddAxisInfo()
{
	CString	    strData;
	DWORD	    dwModuleID;
	long		m_lAxisCount;
	long		m_lAxisNo;
	DWORD		m_dwModuleID;

	//++ 유효한 전체 모션축수를 반환합니다.
	AxmInfoGetAxisCount(&m_lAxisCount);
	if (m_lAxisCount < 1)	return FALSE;

	m_lAxisNo = 0;
	//++ 지정한 축의 정보를 반환합니다.
	// [INFO] 여러개의 정보를 읽는 함수 사용시 불필요한 정보는 NULL(0)을 입력하면 됩니다.
	AxmInfoGetAxis(m_lAxisNo, NULL, NULL, &m_dwModuleID);

	// 유효한 전체 모션축수의 정보를 읽어 ComboBox에 등록합니다.
	for (int i = 0; i < m_lAxisCount; i++)
	{
		//++ 지정한 축의 정보를 반환합니다.
		// [INFO] 여러개의 정보를 읽는 함수 사용시 불필요한 정보는 NULL(0)을 입력하면 됩니다.
		AxmInfoGetAxis(i, NULL, NULL, &dwModuleID);
		switch (dwModuleID) {

		case AXT_SMC_4V04:				strData.Format("%02ld-[4V04]", i);	break;
		case AXT_SMC_R1V04:				strData.Format("%02ld-[R1V04]", i);	break;
		case AXT_SMC_2V04:				strData.Format("%02ld-[2V04]", i);	break;
		case AXT_SMC_R1V04MLIIPM:		strData.Format("%02ld-[R1V04MLIIPM]", i);	break;
		case AXT_SMC_R1V04PM2Q:			strData.Format("%02ld-[R1V04PM2Q]", i);	break;
		case AXT_SMC_R1V04PM2QE:		strData.Format("%02ld-[R1V04PM2QE]", i);	break;
		case AXT_SMC_R1V04MLIIIPM:		strData.Format("%02ld-[R1V04MLIIIPM]", i);	break;
		case AXT_SMC_R1V04MLIISV:		strData.Format("%02ld-[R1V04MLIISV]", i);	break;
		case AXT_SMC_R1V04A5:			strData.Format("%02ld-[R1V04A5]", i);	break;
		case AXT_SMC_R1V04A4:			strData.Format("%02ld-[R1V04A4]", i);	break;
		case AXT_SMC_R1V04SIIIHMIV:		strData.Format("%02ld-[R1V04SIIIHMIV]", i);	break;
		case AXT_SMC_R1V04SIIIHMIV_R:	strData.Format("%02ld-[R1V04SIIIHMIV_R]", i);	break;
		case AXT_SMC_R1V04MLIIISV:		strData.Format("%02ld-[R1V04MLIIISV]", i);	break;
		case AXT_SMC_R1V04MLIIISV_MD:	strData.Format("%02ld-[R1V04MLIIISV_MD]", i);	break;
		case AXT_SMC_R1V04MLIIIS7S:		strData.Format("%02ld-[R1V04MLIIIS7S]", i);	break;
		case AXT_SMC_R1V04MLIIIS7W:		strData.Format("%02ld-[R1V04MLIIIS7W]", i);	break;
		default:					    strData.Format("%02ld-[Unknown]", i);
		}
	}

	return strData;
}


long MotionLBR::InfoGetAxisCount()
{
	long lAxisCount; 
	AxmInfoGetAxisCount(&lAxisCount);
	return lAxisCount;
}

long MotionLBR::InfoGetFirstAxisNo()
{
	long lBoardNo = 0; 
	long lModulePos = 0; 
	long lFirstAxisNo; 
	AxmInfoGetFirstAxisNo(lBoardNo, lModulePos, &lFirstAxisNo);
	return lFirstAxisNo;
}

long MotionLBR::InfoGetAxis(long lAxisNo)
{
	// Verify board number, module number and module ID of axis 0. 
	//long lAxisNo = 0; 
	long lBoardNo, lModulePos; 
	DWORD dwModuleID; 
	AxmInfoGetAxis(lAxisNo, &lBoardNo, &lModulePos, &dwModuleID);
	return lModulePos;
}

void MotionLBR::MotSetMoveUnitPerPulse(long m_AxisNo, double m_dUnit, long m_lPulse)
{

	/*Unit per Pulse
	- it is a value that sets a unit of ordered value from the command.
	Start / Stop Speed
	- it sets velocity when drive part starts and ends.
	Pulse Out Method
	- it sets type of pulse that outputs from motion controller to servo drive.
	Encoder Input Method
	- it sets method that receives encoder signal sent from servo drive to motion controller.
	// Make an ordered value of axis 0 to be mm unit.

	long lAxisNo = 0;
	long lPulse = 10000; // number of pulse for 1 rotation.
	double dUnit = 10; // movement distance during 1 rotation.
	AxmMotSetMoveUnitPerPulse(lAxisNo, dUnit, lPulse);
	*/

	AxmMotSetMoveUnitPerPulse(m_AxisNo, m_dUnit, m_lPulse);
}

void MotionLBR::StartSpeed(long m_lAxisNo)
{
	//AxmMotSetMinVel(m_lAxisNo, 1);
	//AxmMotSetMaxVel(m_lAxisNo, 900000000);
}


void MotionLBR::Initdata()
{
	// ※ [CAUTION] 아래와 다른 Mot파일(모션 설정파일)을 사용할 경우 경로를 변경하십시요.
	char szFilePath[] = "C:\\DefinneDataHander\\data.mot";

	//++ 지정한 Mot파일의 설정값들로 모션보드의 설정값들을 일괄변경 적용합니다.
	if (AxmMotLoadParaAll(szFilePath) != AXT_RT_SUCCESS)
	{
		AfxMessageBox("Mot File Not Found.");
	}
}

void MotionLBR::SetPulseOutMethod(long m_lAxisNo, DWORD m_uMethod)
{ 
	    //OneHighLowHigh = 0x0,          // 1 pulse method, PULSE(Active High), forward direction(DIR=Low)  / reverse direction(DIR=High)
		//OneHighHighLow = 0x1,           // 1 pulse method, PULSE(Active High), forward direction (DIR=High) / reverse direction (DIR=Low)
		//OneLowLowHigh = 0x2,           // 1 pulse method, PULSE(Active Low), forward direction (DIR=Low)  / reverse direction (DIR=High)
		//OneLowHighLow = 0x3,           // 1 pulse method, PULSE(Active Low), forward direction (DIR=High) / reverse direction (DIR=Low)
		//TwoCcwCwHigh = 0x4,           // 2 pulse method, PULSE(CCW: reverse direction),  DIR(CW: forward direction),  Active High
		//TwoCcwCwLow = 0x5,           // 2 pulse method, PULSE(CCW: reverse direction),  DIR(CW: forward direction),  Active Low
		//TwoCwCcwHigh = 0x6,           // 2 pulse method, PULSE(CW: forward direction),   DIR(CCW: reverse direction), Active High
		//TwoCwCcwLow = 0x7,           // 2 pulse method, PULSE(CW: forward direction),   DIR(CCW: reverse direction), Active Low
		//TwoPhase = 0x8,           // 2 phase (90' phase difference),  PULSE lead DIR(CW: forward direction), PULSE lag DIR(CCW: reverse direction)
		//TwoPhaseReverse = 0x9
	AxmMotSetPulseOutMethod(m_lAxisNo, m_uMethod);
}

CString MotionLBR::GetPulseOutMethod(long m_lAxisNo)
{
	DWORD upMethod;
	AxmMotGetPulseOutMethod(m_lAxisNo,&upMethod);
	switch (upMethod)
	{
	case 0:
		return "OneHighLowHigh";
		break;
	case 1:
		return "OneHighHighLow";
		break;
	case 2:
		return "OneLowLowHigh";
		break;
	case 3:
		return "OneLowHighLow";
		break;
	case 4:
		return "TwoCcwCwHigh";
		break;
	case 5:
		return "TwoCcwCwLow";
		break;
	case 6:
		return "TwoCwCcwHigh";
		break;
	case 7:
		return "TwoCwCcwLow";				
		break;
	case 8:
		return "TwoPhase";
		break;
	case 9:
		return "TwoPhaseReverse";
		break;
	default:
		break;
	}
}

//Encoder Input Method
void MotionLBR::SetEncInputMethod(long m_lAxisNo, DWORD m_uMethod)
{
	 //   m_uMethod
	 //   ObverseUpDownMode           = 0x0,           // Forward direction Up/Down
     //   ObverseSqr1Mode             = 0x1,           // Forward direction 1 multiplication
     //   ObverseSqr2Mode             = 0x2,           // Forward direction 2 multiplication
     //   ObverseSqr4Mode             = 0x3,           // Forward direction 4 multiplication
     //   ReverseUpDownMode           = 0x4,           // Reverse direction Up/Down
     //   ReverseSqr1Mode             = 0x5,           // Reverse direction 1 multiplication
     //   ReverseSqr2Mode             = 0x6,           // Reverse direction 2 multiplication
     //   ReverseSqr4Mode             = 0x7            // Reverse direction 4 multiplication
	AxmMotSetEncInputMethod(m_lAxisNo, m_uMethod);
}

CString MotionLBR::GetEncInputMethod(long m_lAxisNo)
{
	DWORD upMethod;
	AxmMotGetEncInputMethod(m_lAxisNo,&upMethod);
	switch (upMethod)
	{
	case 0:
		return "ObverseUpDownMode";
		break;
	case 1:
		return "ObverseSqr1Mode";
		break;
	case 2:
		return "ObverseSqr2Mode";
		break;
	case 3:
		return "ObverseSqr4Mode";
		break;
	case 4:
		return "ReverseUpDownMode";
		break;
	case 5:
		return "ReverseSqr1Mode";
		break;
	case 6:
		return "ReverseSqr2Mode";
		break;
	case 7:
		return "ReverseSqr4Mode";
		break;
	default:
		return "NoName";
		break;
	}

}
void MotionLBR::SignalSetLimit(long m_lAxisNo, DWORD m_uStopMode, 
	                                DWORD m_uPositiveLevel, DWORD m_uNegativeLevel)
{
	//long m_lAxisNo = 0;
	//DWORD m_uStopMode = [0]Emergency stop, [1]Slowdown stop 
	//DWORD uPositiveLevel = LOW, HIGH, UNUSED, USED
	//DWORD uNegativeLevel = LOW, HIGH, UNUSED, USED
	AxmSignalSetLimit(m_lAxisNo, m_uStopMode, m_uPositiveLevel, m_uNegativeLevel);
}

CString MotionLBR::SignalGetLimit(long m_lAxisNo,CString mode)
{
	DWORD upStopMode;
	DWORD upPositiveLevel;
	DWORD upNegativeLevel;
	AxmSignalGetLimit(m_lAxisNo,&upStopMode,&upPositiveLevel,&upNegativeLevel);
	if (mode == "Positive")
	{
		switch (upPositiveLevel)
		{
		case 0:
			return "Pos LOW";
			break;
		case 1:
			return "Pos HIGH";
			break;
		case 2:
			return "Pos UNUSED";
			break;
		case 3:
			return "Pos USED";
			break;
		default:
			break;
		}
	}
	else
		if (mode == "Negative")
		{
			switch (upNegativeLevel)
			{
			case 0:
				return "Neg LOW";
				break;
			case 1:
				return "Neg HIGH";
				break;
			case 2:
				return "Neg UNUSED";
				break;
			case 3:
				return "Neg USED";
				break;
			default:
				break;
			}
		}
		else
			if (mode == "stop")
			{
				switch (upStopMode)
				{
				case 0:
					return "Stop Emg";
					break;
				case 1:
					return "Stop Slow";
					break;
				}
			}
			else
				return "";
	
}

CString MotionLBR::SignalReadLimit(long m_lAxisNo, CString mode)
{
	DWORD upPositiveStatus;
	DWORD upNegativeStatus;
	CString data1,data2;
	AxmSignalReadLimit(m_lAxisNo, &upPositiveStatus, &upNegativeStatus);
	data1.Format("%lf", upPositiveStatus);
	data2.Format("%lf", upNegativeStatus);

	if (mode == "Positive") 
		switch (upPositiveStatus)
	{
	case 0:
		return "Pos OFF";
		break;
	case 1:
		return "Pos ON";
		break;
	default:
		break;
	}
	else
			if (mode == "Negative")
			{
				switch (upNegativeStatus)
				{
				case 0:
					return "Neg OFF";
					break;
				case 1:
					return "Neg ON";
					break;
				}
			}
			else
				return "";

}
void  MotionLBR::SignalSetInpos(long m_lAxisNo, DWORD m_uUse )
{
	// Set input level of inposition signal on axis 0. Default : HIGH. 
	//long lAxisNo = 0; 
	//DWORD uUse = HIGH; 
	AxmSignalSetInpos(m_lAxisNo, m_uUse);
}
void MotionLBR::SignalSetServoAlarm(long m_lAxisNo, DWORD m_uUse)
{
	// Set input level of alarm signal on axis 0. Default : HIGH. 
	//long lAxisNo = 0; 
	//DWORD uUse = LOW; 
	AxmSignalSetServoAlarm(m_lAxisNo, m_uUse);
}
void MotionLBR::SignalSetStop(long m_lAxisNo, DWORD m_uStopMode, DWORD m_uLevel)
{
	// Set input level of ESTOP on axis 0. 
	//long lAxisNo = 0; 
	//DWORD uStopMode = 0; // [0] Emergency stop, [1] Slow-Down stop 
	//DWORD uLevel = HIGH; 
	AxmSignalSetStop(m_lAxisNo, m_uStopMode, m_uLevel);
}


BOOL MotionLBR::HomeReadSignal(long m_lAxisNo)
{
	DWORD upStatus;
	AxmHomeReadSignal(m_lAxisNo, &upStatus);
	return upStatus;
	
}


BOOL  MotionLBR::SignalReadLimit(long m_lAxisNo,BOOL senser)
{
	// Verify End Limit signal on axis 0. 
	//long lAxisNo = 0; 
	DWORD uPositiveStatus, uNegativeStatus; 
	AxmSignalReadLimit(m_lAxisNo, &uPositiveStatus, &uNegativeStatus);
	if (senser) return uPositiveStatus;
	else return uNegativeStatus;
}

DOUBLE MotionLBR::SignalReadInpos(long m_lAxisNo)
{
	// Use when verifying whether inposition signal is inputted or not. 
	//long lAxisNo = 0; 
	DWORD uStatus; 
	AxmSignalReadInpos(m_lAxisNo, &uStatus);
	return uStatus;
}

DOUBLE MotionLBR::SignalReadServoAlarm(long m_lAxisNo)
{
	//long lAxisNo = 0; 
	DWORD uStatus;
	AxmSignalReadServoAlarm(m_lAxisNo, &uStatus);
	return uStatus;
}
DOUBLE MotionLBR::SignalReadStop(long m_lAxisNo)
{
	//long lAxisNo = 0; 
	DWORD uStatus; 
	AxmSignalReadStop(m_lAxisNo, &uStatus);
	return uStatus;
}

void MotionLBR::Servo_OnOff_Level(long lAxisNo, DWORD uLevel)
{
	AxmSignalSetServoOnLevel(lAxisNo, uLevel);
}

void MotionLBR::Servo_OnOff(long lAxisNo, DWORD uLevel)
{
	//long lAxisNo = 0; 
	//DWORD uLevel = HIGH; 
	//AxmSignalSetServoOnLevel(lAxisNo, uLevel);
	AxmSignalServoOn(lAxisNo, uLevel);//ENABLE  DISABLE
}

BOOL MotionLBR::Status_OnOff(long lAxisNo)
{
	DWORD uUse; 
	AxmSignalIsServoOn(lAxisNo, &uUse); 
	if (uUse) return TRUE;
	else return FALSE;
}
void MotionLBR::Set_Mode_AccDcc(long lAxisNo, DWORD uProfileMode)
{
	// Make velocity profile on axis 0 to the symmetrical S curve ac/deceleration. 
	//Symmetrical trapezoid ac / deceleration
	//	[0] SYM_TRAPEZOIDE_MODE
	//	Asymmetrical trapezoid ac / deceleration
	//	[1] ASYM_TRAPEZOIDE_MODE
	//	Symmetrical Quasi - S Curve
	//	[2] QUASI_S_CURVE_MODE
	//	Symmetrical S curve ac / deceleration
	//	[3] SYM_S_CURVE_MODE
	//	Asymmetrical S curve ac / deceleration
	//	[4] ASYM_S_CURVE_MODE
	AxmMotSetProfileMode(lAxisNo, uProfileMode);
}
CString MotionLBR::Get_Mode_AccDcc(long lAxisNo)
{

	DWORD uProfileMode; 
	CString m_mode;
	  
	AxmMotGetProfileMode(lAxisNo,&uProfileMode);
	switch (uProfileMode)
	{
	case 0: m_mode = "symmetrical trapezoid ac / deceleration"; break;
	case 1: m_mode = "asymmetrical trapezoid ac / deceleration"; break;
	case 2: m_mode = "symmetrical Quasi - S Curve"; break;
	case 3: m_mode = "symmetrical S curve ac / deceleration"; break;
	case 4: m_mode = "asymmetrical S curve ac / deceleration"; break;
	}
		return m_mode;
}

void MotionLBR::SetAbsRelMode(long lAxisNo, DWORD uAbsRelMode)
{
	 // Set to absolute position drive. 
    // [0] Absolute coordination, [1] Relative coordination 
	AxmMotSetAbsRelMode(lAxisNo, uAbsRelMode);
	
}
BOOL MotionLBR::GetAbsRelMode(long lAxisNo)
{
	DWORD uAbsRelMode; 
	AxmMotGetAbsRelMode(lAxisNo, &uAbsRelMode); 
	if (uAbsRelMode == 0) return TRUE;
	else if(uAbsRelMode == 1) return FALSE;
}

void MotionLBR::MovePos(long lAxisNo, double dPosition, double dMaxVelocity, double dMaxAccel, double dMaxDecel)
{
	// Move axis 0 to 100 position on the absolute coordination with symmetrical S curve drive // mode (velocity 100, acceleration 200). 
	//long lAxisNo = 0; 
	//DWORD uAbsRelMode = 0; 
	//DWORD uProfileMode = 3; 
	//AxmMotSetAbsRelMode(lAxisNo, uAbsRelMode); 
	//AxmMotSetProfileMode(lAxisNo, uProfileMode); 
	AxmMovePos(lAxisNo, dPosition, dMaxVelocity, dMaxAccel, dMaxDecel);
}
void MotionLBR::MoveStartPos(long lAxisNo, double dPosition, double dMaxVelocity, double dMaxAccel, double dMaxDecel)
{
	// Move axis 0 to 100 position on the absolute coordination with asymmetrical S curve drive 
	// mode (velocity 100, acceleration 200, deceleration 100). 
	//long lAxisNo = 0; 
	//DWORD uAbsRelMode = 1; 
	//DWORD uProfileMode = 4; 
	//AxmMotSetAbsRelMode(lAxisNo, uAbsRelMode);
	//AxmMotSetProfileMode(lAxisNo, uProfileMode);
	AxmMoveStartPos(lAxisNo, dPosition, dMaxVelocity, dMaxAccel, dMaxDecel);
	/*DWORD uStatus;
	while (uStatus) 
	{ 
		AxmStatusReadInMotion(lAxisNo, &uStatus); 
	}*/
}

BOOL MotionLBR::ReadInMotion(long lAxisNo)
{
	DWORD uStatus; 
	AxmStatusReadInMotion(lAxisNo, &uStatus); 
	return uStatus;
}

void MotionLBR::MoveSignalSearch(long lAxisNo, double dMaxVelocity, double dMaxAccel, 
	long lDetectSignal, long lSignalEdge, long lSignalMethod)
{
	// Search Up Edge of home sensor moving to - direction. 
	//long lAxisNo = 0; 
	//double dMaxVelocity = -100; 
	//double dMaxAccel = 200; 
	/*long lDetectSignal = HomeSensor; 
	                       PosEndLimit
		                   NegEndLimit
		                   PosSloLimit
		                   NegSloLimit
		                   HomeSensor
		                   EncodZPhase
		                   UniInput02
		                   UniInput03
		                   UniInput04
		                   UniInput05*/
	/*long lSignalEdge = DOWN_EDGE,
		               UP_EDGE*/
	//long lSignalMethod = 0; // [0]Slowdown Stop, [1]Emergency Stop. 
	AxmMoveSignalSearch(lAxisNo, dMaxVelocity, dMaxAccel, lDetectSignal, 
		lSignalEdge, lSignalMethod);
}

void MotionLBR::MoveSignalCapture(long lAxisNo, double dMaxVelocity, double dMaxAccel,
	long lDetectSignal, long lSignalEdge, long lSignalMethod)
{
	// Search Up Edge of +ELM moving to + direction. 
	//long lAxisNo = 0; 
	//double dMaxVelocity = -100; 
	//double dMaxAccel = 200; 
	/*long lDetectSignal = HomeSensor;
	                       PosEndLimit
	                       NegEndLimit
	                       PosSloLimit
	                       NegSloLimit
	                       HomeSensor
	                       EncodZPhase
	                       UniInput02
	                       UniInput03
	                       UniInput04
	                       UniInput05*/
	/*long lSignalEdge   = DOWN_EDGE,
	                       UP_EDGE*/
	long lTarget = 0; // [0] Command Position, [1] Actual Position
	//long lSignalMethod = 0; // [0]Slowdown Stop, [1]Emergency Stop. 
	AxmMoveSignalCapture(lAxisNo, dMaxVelocity, dMaxAccel, lDetectSignal, lSignalEdge, lTarget, lSignalMethod);
}
double MotionLBR:: MoveGetCapturePos(long lAxisNo)
{
	double dCapPotition;
	AxmMoveGetCapturePos(lAxisNo, &dCapPotition);
	return dCapPotition;
}

void MotionLBR::ServoAlarmReset(long lAxisNo)
{
	AxmSignalServoAlarmReset( lAxisNo, ENABLE);
}

void MotionLBR::HomeSetMethod(long lAxisNo, long nHmDir, DWORD uHomeSignal, DWORD uZphas, double dHomeClrTime, double dHomeOffset)
{
	// API that sets home search method. 
	//long lAxisNo = 0; // Axis number that home search will be carried out. 
	//long nHmDir = 0; // Moving direction of home search 1st, input (-)direction.
	//DWORD uHomeSignal = HomeSensor; // Use signals from signal search drive. 
	//DWORD uZphas = 1; // Whether Z phase detected, detect if 1, do not if 0. 
	//double dHomeClrTime = 2000.0; // Waiting time to set home search Enc value double. 
	//double dHomeOffset = 0.0; // Additional movement by offset value after home. 
	AxmHomeSetMethod(lAxisNo,nHmDir,uHomeSignal,uZphas,dHomeClrTime,dHomeOffset);
}
void MotionLBR::HomeSetVel(long lAxisNo, double dVelFirst, double dVelSecond, double dVelThird,
	double dvelLast, double dAccFirst, double dAccSecond)
{
	// Set velocity that will be used during home search 
	//double dVelFirst = 100; // Velocity in 1st stage. 
	//double dVelSecond = 20; // Velocity in 2nd stage. 
	//double dVelThird = 10; // Velocity in 3rd stage. 
	//double dvelLast = 10; // Velocity for index search and accurate search (apply when // Offset value moves). 
	//double dAccFirst = 200; // Acceleration in 1st stage. 
	//double dAccSecond = 40; // Acceleration in 2nd stage. 
	AxmHomeSetVel(lAxisNo, dVelFirst, dVelSecond, dVelThird, dvelLast, dAccFirst, dAccSecond);
}
void MotionLBR::HomeSetStart(long lAxisNo)
{
	AxmHomeSetStart(lAxisNo);
}
DWORD MotionLBR::HomeGetRate(long lAxisNo)
{
	// Verify progress rate of home search on axis . 
	DWORD uHomeMainStepNumber, uHomeStepNumber;
	AxmHomeGetRate(lAxisNo, &uHomeMainStepNumber , &uHomeStepNumber);
	return uHomeStepNumber;
}

DWORD MotionLBR::HomeGetResult(long lAxisNo)
{
	// Return the result of home search. 
	DWORD uHomeResult; 
	AxmHomeGetResult(lAxisNo, &uHomeResult);
	return uHomeResult;
	    //HOME_ERR_UNKNOWN;
		//When home search is started with an unknown axis number
	    //HOME_ERR_GNT_RANGE;
		//If home search result of master and slave axis of gantry drive axis is off OffsetRange that is set
		//HOME_ERR_USER_BREAK
		//If user carried out stop command during home search
		//HOME_ERR_VELOCITY
		//If home search velocity setting is not set
		//HOME_ERR_AMP_FAULT
		//If servo pack alarm is occurred during home search
		//HOME_ERR_NEG_LIMIT
		//If(-) limit sensor is detected during home sensor search with(+) direction
		//HOME_ERR_POS_LIMIT
		//If(+) limit sensor is detected during home sensor search with(-) direction
		//HOME_ERR_NOT_DETECT
		//If home sensor is not detected
		//HOME_SEARCHING
		//If home search is in progress currently
		//HOME_SUCCESS
		//If home search is exited successfully				
}

void MotionLBR::MoveEStop(long lAxisNo)
{
	// Make an emergency stop of motion drive on axis . 
	AxmMoveEStop(lAxisNo);
}

void MotionLBR::MoveSStop(long lAxisNo)
{
	// Make slow down stop of motion drive on axis.
	AxmMoveSStop(lAxisNo);
}

void MotionLBR::MoveStop(long lAxisNo, double dMaxDecel)
{
	// Stop motion drive with deceleration of 100 on axis. 
	//double dMaxDecel = 100; 
	AxmMoveStop(lAxisNo, dMaxDecel);
}

double MotionLBR::StatusGetActPos(long lAxisNo)
{
	// Verify current position on axis   
	double dPosition; 
	AxmStatusGetActPos(lAxisNo, &dPosition); 
	return dPosition;
}

double MotionLBR::StatusGetCmdPos(long lAxisNo)
{
	// Verify ordered position on axis . 
	double dPosition; 
	AxmStatusGetCmdPos(lAxisNo, &dPosition); 
	return dPosition;
}


DWORD MotionLBR::StatusReadPosError(long lAxisNo)
{
	// Verify difference between ordered position and actual position on axis 
	double dError; 
	AxmStatusReadPosError(lAxisNo, &dError); 
	return dError;
}

DWORD MotionLBR::StatusReadVel(long lAxisNo)
{
	// Verify current velocity on axis  
	double dVelocity; 
	AxmStatusReadVel(lAxisNo, &dVelocity); 
	return dVelocity;
}

DWORD MotionLBR::StatusReadInMotion(long lAxisNo)
{
	// Verify if axis drives. 
	DWORD uStatus; 
	AxmStatusReadInMotion(lAxisNo, &uStatus);
	return uStatus;
}

DWORD MotionLBR::StatusReadMotion(long lAxisNo)
{
	// Read drive state on axis .  
	DWORD uStatus; 
	AxmStatusReadMotion(lAxisNo, &uStatus);
	return uStatus;
	
		 /*  uStatus =  QIDRIVE_STATUS_0	BUSY(in DRIVE)
					    QIDRIVE_STATUS_1    DOWN(in deceleration DRIVE)
					    QIDRIVE_STATUS_2    CONST(in constant velocity DRIVE)
					    QIDRIVE_STATUS_3    Up(in acceleration DRIVE)
					    QIDRIVE_STATUS_4    In continuous drive
					    QIDRIVE_STATUS_5    In specified distance drive
					    QIDRIVE_STATUS_6    In MPG drive				  
		 */
}
DWORD MotionLBR::StatusReadStop(long lAxisNo)
{
	// Verify exit state on axis . 
	DWORD uStatus; 
	AxmStatusReadStop(lAxisNo, &uStatus);
	return uStatus;

	/*  uStatus       = QIEND_STATUS_0      Exit by forward direction limit signal (PELM)
                        QIEND_STATUS_1      Exit by reverse direction limit signal (NELM)
                        QIEND_STATUS_4      Drive exit by forward direction soft limit emergency stop function
                        QIEND_STATUS_5      Drive exit by reverse direction soft limit emergency stop function
                        QIEND_STATUS_6      Drive exit by forward direction soft limit deceleration stop function
						QIEND_STATUS_7      Drive exit by reverse direction soft limit deceleration stop function
                        QIEND_STATUS_8      Drive exit by servo alarm function
                        QIEND_STATUS_9      Drive exit by emergency stop signal input
                        QIEND_STATUS_10     Drive exit by emergency stop command
                        QIEND_STATUS_11     Drive exit by deceleration stop command					    					    					    					    								    
   */
}

void MotionLBR::MoveMultiPosAbsXY(double dPositionX, double dPositionY, double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel)
{
	// With axis 0 as a relative coordination.
	// S-curve drive mode (velocity 100, acceleration 200). 
	DWORD uAbsRelMode = 0;   //0 chay tuyet doi -- 1 chay duong doi
	DWORD uProfileMode = 0; // kieu tang toc giam toc

	AxmMotSetAbsRelMode(0, uAbsRelMode); 
	AxmMotSetProfileMode(0, uProfileMode); 

	AxmMotSetAbsRelMode(1, uAbsRelMode);
	AxmMotSetProfileMode(1, uProfileMode);

	long lArraySize = 2; 
	long lAxisNo[2] = {0,1}; 

	double dPosition[2] = { dPositionX,dPositionY };
	double dMaxVelocity[2] = { m_dMaxVelocity,m_dMaxVelocity };
	double dMaxAccel[2]    = { m_dMaxAccel,m_dMaxAccel };
	double dMaxDecel[2]    = { m_dMaxDecel,m_dMaxDecel };
	AxmMoveMultiPos(lArraySize,lAxisNo,dPosition,dMaxVelocity,dMaxAccel,dMaxDecel);
	
}

void MotionLBR::MoveMultiPosReXY(double dPositionX, double dPositionY, double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel)
{
	// With axis 0 as a relative coordination.
	// S-curve drive mode (velocity 100, acceleration 200). 
	DWORD uAbsRelMode = 1;   //0 chay tuyet doi -- 1 chay duong doi
	DWORD uProfileMode = 3; // kieu tang toc giam toc

	AxmMotSetAbsRelMode(0, uAbsRelMode);
	AxmMotSetProfileMode(0, uProfileMode);

	AxmMotSetAbsRelMode(1, uAbsRelMode);
	AxmMotSetProfileMode(1, uProfileMode);

	long lArraySize = 2;
	long lAxisNo[2] = { 0,1 };

	double dPosition[2] = { dPositionX,dPositionY };
	double dMaxVelocity[2] = { m_dMaxVelocity,m_dMaxVelocity };
	double dMaxAccel[2] = { m_dMaxAccel,m_dMaxAccel };
	double dMaxDecel[2] = { m_dMaxDecel,m_dMaxDecel };
	AxmMoveMultiPos(lArraySize, lAxisNo, dPosition, dMaxVelocity, dMaxAccel, dMaxDecel);

}
void MotionLBR::MoveMultiPosAbsXYZ(double dPositionX, double dPositionY, double dPositionZ, double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel)
{
	// With axis 0 as a relative coordination.
	// S-curve drive mode (velocity 100, acceleration 200). 
	DWORD uAbsRelMode = 0;   //0 chay tuyet doi -- 1 chay duong doi
	DWORD uProfileMode = 3; // kieu tang toc giam toc

	AxmMotSetAbsRelMode(0, uAbsRelMode);
	AxmMotSetProfileMode(0, uProfileMode);

	AxmMotSetAbsRelMode(1, uAbsRelMode);
	AxmMotSetProfileMode(1, uProfileMode);

	AxmMotSetAbsRelMode(2, uAbsRelMode);
	AxmMotSetProfileMode(2, uProfileMode);

	long lArraySize = 3;
	long lAxisNo[3] = { 0,1,2 };

	double dPosition[3] = { dPositionX,dPositionY,dPositionZ };
	double dMaxVelocity[3] = { m_dMaxVelocity,m_dMaxVelocity,m_dMaxVelocity };
	double dMaxAccel[3] = { m_dMaxAccel,m_dMaxAccel,m_dMaxAccel };
	double dMaxDecel[3] = { m_dMaxDecel,m_dMaxDecel,m_dMaxDecel };
	AxmMoveMultiPos(lArraySize, lAxisNo, dPosition, dMaxVelocity, dMaxAccel, dMaxDecel);

}
void MotionLBR::MoveMultiPosReXYZ(double dPositionX, double dPositionY, double dPositionZ, double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel)
{
	// With axis 0 as a relative coordination.
	// S-curve drive mode (velocity 100, acceleration 200). 
	DWORD uAbsRelMode = 1;   //0 chay tuyet doi -- 1 chay duong doi
	DWORD uProfileMode = 3; // kieu tang toc giam toc

	AxmMotSetAbsRelMode(0, uAbsRelMode);
	AxmMotSetProfileMode(0, uProfileMode);

	AxmMotSetAbsRelMode(1, uAbsRelMode);
	AxmMotSetProfileMode(1, uProfileMode);

	AxmMotSetAbsRelMode(2, uAbsRelMode);
	AxmMotSetProfileMode(2, uProfileMode);

	long lArraySize = 3;
	long lAxisNo[3] = { 0,1,2 };

	double dPosition[3] = { dPositionX,dPositionY,dPositionZ };
	double dMaxVelocity[3] = { m_dMaxVelocity,m_dMaxVelocity,m_dMaxVelocity };
	double dMaxAccel[3] = { m_dMaxAccel,m_dMaxAccel,m_dMaxAccel };
	double dMaxDecel[3] = { m_dMaxDecel,m_dMaxDecel,m_dMaxDecel };
	AxmMoveMultiPos(lArraySize, lAxisNo, dPosition, dMaxVelocity, dMaxAccel, dMaxDecel);

}

void MotionLBR::MoveStartMultiPosAbsXY(double dPositionX, double dPositionY, double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel)
{
	// With axis 0 as a relative coordination.
	// S-curve drive mode (velocity 100, acceleration 200). 
	DWORD uAbsRelMode = 0;   //0 chay tuyet doi -- 1 chay duong doi
	DWORD uProfileMode = 0; // kieu tang toc giam toc

	AxmMotSetAbsRelMode(0, uAbsRelMode);
	AxmMotSetProfileMode(0, uProfileMode);

	AxmMotSetAbsRelMode(1, uAbsRelMode);
	AxmMotSetProfileMode(1, uProfileMode);

	long lArraySize = 2;
	long lAxisNo[2] = { 0,1 };

	double dPosition[2] = { dPositionX,dPositionY };
	double dMaxVelocity[2] = { m_dMaxVelocity,m_dMaxVelocity };
	double dMaxAccel[2] = { m_dMaxAccel,m_dMaxAccel };
	double dMaxDecel[2] = { m_dMaxDecel,m_dMaxDecel };
	AxmMoveStartMultiPos(lArraySize, lAxisNo, dPosition, dMaxVelocity, dMaxAccel, dMaxDecel);
}
void MotionLBR::MoveStartMultiPosReXY(double dPositionX, double dPositionY, double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel)
{
	// With axis 0 as a relative coordination.
	// S-curve drive mode (velocity 100, acceleration 200). 
	DWORD uAbsRelMode = 1;   //0 chay tuyet doi -- 1 chay duong doi
	DWORD uProfileMode = 3; // kieu tang toc giam toc

	AxmMotSetAbsRelMode(0, uAbsRelMode);
	AxmMotSetProfileMode(0, uProfileMode);

	AxmMotSetAbsRelMode(1, uAbsRelMode);
	AxmMotSetProfileMode(1, uProfileMode);

	long lArraySize = 2;
	long lAxisNo[2] = { 0,1 };

	double dPosition[2] = { dPositionX,dPositionY };
	double dMaxVelocity[2] = { m_dMaxVelocity,m_dMaxVelocity };
	double dMaxAccel[2] = { m_dMaxAccel,m_dMaxAccel };
	double dMaxDecel[2] = { m_dMaxDecel,m_dMaxDecel };
	AxmMoveStartMultiPos(lArraySize, lAxisNo, dPosition, dMaxVelocity, dMaxAccel, dMaxDecel);
	
}

void MotionLBR::MoveStartMultiPosAbsXYZ(double dPositionX, double dPositionY, double dPositionZ, double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel)
{
	// With axis 0 as a relative coordination.
	// S-curve drive mode (velocity 100, acceleration 200). 
	DWORD uAbsRelMode = 0;   //0 chay tuyet doi -- 1 chay duong doi
	DWORD uProfileMode = 3; // kieu tang toc giam toc

	AxmMotSetAbsRelMode(0, uAbsRelMode);
	AxmMotSetProfileMode(0, uProfileMode);

	AxmMotSetAbsRelMode(1, uAbsRelMode);
	AxmMotSetProfileMode(1, uProfileMode);

	AxmMotSetAbsRelMode(2, uAbsRelMode);
	AxmMotSetProfileMode(2, uProfileMode);

	long lArraySize = 3;
	long lAxisNo[3] = { 0,1,2 };

	double dPosition[3] = { dPositionX,dPositionY,dPositionZ };
	double dMaxVelocity[3] = { m_dMaxVelocity,m_dMaxVelocity,m_dMaxVelocity };
	double dMaxAccel[3] = { m_dMaxAccel,m_dMaxAccel,m_dMaxAccel };
	double dMaxDecel[3] = { m_dMaxDecel,m_dMaxDecel,m_dMaxDecel };
	AxmMoveStartMultiPos(lArraySize, lAxisNo, dPosition, dMaxVelocity, dMaxAccel, dMaxDecel);

}

void MotionLBR::MoveStartMultiPosReXYZ(double dPositionX, double dPositionY, double dPositionZ, double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel)
{
	// With axis 0 as a relative coordination.
	// S-curve drive mode (velocity 100, acceleration 200). 
	DWORD uAbsRelMode = 1;   //0 chay tuyet doi -- 1 chay duong doi
	DWORD uProfileMode = 3; // kieu tang toc giam toc

	AxmMotSetAbsRelMode(0, uAbsRelMode);
	AxmMotSetProfileMode(0, uProfileMode);

	AxmMotSetAbsRelMode(1, uAbsRelMode);
	AxmMotSetProfileMode(1, uProfileMode);

	AxmMotSetAbsRelMode(2, uAbsRelMode);
	AxmMotSetProfileMode(2, uProfileMode);

	long lArraySize = 3;
	long lAxisNo[3] = { 0,1,2 };

	double dPosition[3] = { dPositionX,dPositionY,dPositionZ };
	double dMaxVelocity[3] = { m_dMaxVelocity,m_dMaxVelocity,m_dMaxVelocity };
	double dMaxAccel[3] = { m_dMaxAccel,m_dMaxAccel,m_dMaxAccel };
	double dMaxDecel[3] = { m_dMaxDecel,m_dMaxDecel,m_dMaxDecel };
	AxmMoveStartMultiPos(lArraySize, lAxisNo, dPosition, dMaxVelocity, dMaxAccel, dMaxDecel);

}
void MotionLBR::JogRun(long lAxisNo, double dVel, double dAccel, double dDecel)
{
	AxmMoveVel(lAxisNo, dVel, dAccel, dDecel);
}
void MotionLBR::JogStop(long lAxisNo)
{
	//AxmMoveSStop(lAxisNo);

	//double dMaxDecel = 100;
	//AxmMoveStop(lAxisNo, dMaxDecel);

	AxmMoveEStop(lAxisNo);
}

void MotionLBR::SetOuput(int m_output)
{
	long IModuleCounts;
	AxdInfoGetModuleCount(&IModuleCounts);

	if (IModuleCounts > 0)
	{
		long	IBoardNo;
		long	IModulePos;
		DWORD	dwModuleID;
		CString strMessage;
		short	nIndex;
		BOOL    bState;
		long  ModuleInfo = m_output / 16;
		if (AxdInfoGetModule(ModuleInfo, &IBoardNo, &IModulePos, &dwModuleID) == AXT_RT_SUCCESS)
		{
			switch (dwModuleID)
			{
			case AXT_SIO_RDB32MLIII:
			case AXT_SIO_RDB32PMLIII:
			case AXT_SIO_RDB128MLIIIAI:
			case AXT_SIO_RDB96MLII:
			case AXT_SIO_RDB32RTEX:
			case AXT_SIO_RDB128MLII:
			case AXT_SIO_DB32P:
			case AXT_SIO_RDB32T:
			case AXT_SIO_DB32T:
			case AXT_SIO_UNDEFINEMLIII:
			case AXT_SIO_RSIMPLEIOMLII:
				nIndex = m_output % 16;
				bState = 1;
				AxdoWriteOutportBit(ModuleInfo, nIndex, bState);
				break;
			case AXT_SIO_RDO32MLIII:
			case AXT_SIO_RDO32AMSMLIII:
			case AXT_SIO_RDO32PMLIII:
			case AXT_SIO_RDO16AMLII:
			case AXT_SIO_RDO16BMLII:
			case AXT_SIO_RDO32RTEX:
			case AXT_SIO_DO32T_P:
			case AXT_SIO_RDO32:
			case AXT_SIO_DO32P:
			case AXT_SIO_DO32T:

				nIndex = m_output % 16;
				bState = 1;
				AxdoWriteOutportBit(ModuleInfo, nIndex , bState);
				break;
			}
		}
	}
}

void MotionLBR::ResetOuput(int m_output)
{
	long IModuleCounts;
	AxdInfoGetModuleCount(&IModuleCounts);

	if (IModuleCounts > 0)
	{
		long	IBoardNo;
		long	IModulePos;
		DWORD	dwModuleID;
		CString strMessage;
		short	nIndex;
		BOOL    bState;
		long  ModuleInfo = m_output / 16;
		if (AxdInfoGetModule(ModuleInfo, &IBoardNo, &IModulePos, &dwModuleID) == AXT_RT_SUCCESS)
		{
			switch (dwModuleID)
			{
			case AXT_SIO_RDB32MLIII:
			case AXT_SIO_RDB32PMLIII:
			case AXT_SIO_RDB128MLIIIAI:
			case AXT_SIO_RDB96MLII:
			case AXT_SIO_RDB32RTEX:
			case AXT_SIO_RDB128MLII:
			case AXT_SIO_DB32P:
			case AXT_SIO_RDB32T:
			case AXT_SIO_DB32T:
			case AXT_SIO_UNDEFINEMLIII:
			case AXT_SIO_RSIMPLEIOMLII:
				nIndex = m_output % 16;
				bState = 0;
				AxdoWriteOutportBit(ModuleInfo, nIndex, bState);
				break;
			case AXT_SIO_RDO32MLIII:
			case AXT_SIO_RDO32AMSMLIII:
			case AXT_SIO_RDO32PMLIII:
			case AXT_SIO_RDO16AMLII:
			case AXT_SIO_RDO16BMLII:
			case AXT_SIO_RDO32RTEX:
			case AXT_SIO_DO32T_P:
			case AXT_SIO_RDO32:
			case AXT_SIO_DO32P:
			case AXT_SIO_DO32T:

				nIndex = m_output % 16;
				bState = 0;
				AxdoWriteOutportBit(ModuleInfo, nIndex + 16, bState);
				break;
			}
		}
	}
}

BOOL MotionLBR::ReadOuput(int m_output)
{
	short		nIndex;
	DWORD		dwDataHigh = 0;
	DWORD		dwDataLow;
	BOOL		bFlagHigh;
	BOOL		bFlagLow;
	long		lBoardNo;
	long		lModulePos;
	DWORD		dwModuleID;
	long  ModuleInfo = m_output / 16;
	nIndex = m_output % 16;

	AxdInfoGetModule(ModuleInfo, &lBoardNo, &lModulePos, &dwModuleID);

	switch (dwModuleID)
	{

	case AXT_SIO_RDI32MLIII:
	case AXT_SIO_RDI32MSMLIII:
	case AXT_SIO_RDI32PMLIII:
	case AXT_SIO_RDI32RTEX:
	case AXT_SIO_DI32_P:
	case AXT_SIO_RDI32:
	case AXT_SIO_DI32:

		//++
		// Read inputting signal in Bit
		AxdoReadOutportBit(ModuleInfo, nIndex, &dwDataHigh);
		break;
	case AXT_SIO_RDB32MLIII:
	case AXT_SIO_RDB32PMLIII:
	case AXT_SIO_RDB128MLIIIAI:
	case AXT_SIO_RDB96MLII:
	case AXT_SIO_RDB32RTEX:
	case AXT_SIO_RDB128MLII:
	case AXT_SIO_DB32P:
	case AXT_SIO_RDB32T:
	case AXT_SIO_DB32T:
	case AXT_SIO_UNDEFINEMLIII:
	case AXT_SIO_RSIMPLEIOMLII:
		//++
		// Read inputting signal in Bit
		AxdoReadOutportBit(ModuleInfo, nIndex, &dwDataHigh);
		break;
	}

	if (dwDataHigh)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

BOOL MotionLBR::ReadInput(int m_input)
{
	short		nIndex;
	DWORD		dwDataHigh = 0;
	DWORD		dwDataLow;
	BOOL		bFlagHigh;
	BOOL		bFlagLow;
	long		lBoardNo;
	long		lModulePos;
	DWORD		dwModuleID;
	long  ModuleInfo = m_input / 16;
    nIndex = m_input % 16;

		AxdInfoGetModule(ModuleInfo, &lBoardNo, &lModulePos, &dwModuleID);

		switch (dwModuleID)
		{

		case AXT_SIO_RDI32MLIII:
		case AXT_SIO_RDI32MSMLIII:
		case AXT_SIO_RDI32PMLIII:
		case AXT_SIO_RDI32RTEX:
		case AXT_SIO_DI32_P:
		case AXT_SIO_RDI32:
		case AXT_SIO_DI32:

			//++
			// Read inputting signal in Bit
			AxdiReadInportBit(ModuleInfo, nIndex, &dwDataHigh);
			break;
		case AXT_SIO_RDB32MLIII:
		case AXT_SIO_RDB32PMLIII:
		case AXT_SIO_RDB128MLIIIAI:
		case AXT_SIO_RDB96MLII:
		case AXT_SIO_RDB32RTEX:
		case AXT_SIO_RDB128MLII:
		case AXT_SIO_DB32P:
		case AXT_SIO_RDB32T:
		case AXT_SIO_DB32T:
		case AXT_SIO_UNDEFINEMLIII:
		case AXT_SIO_RSIMPLEIOMLII:
			//++
			// Read inputting signal in Bit
			AxdiReadInportBit(ModuleInfo, nIndex, &dwDataHigh);
			break;
		}

		if (dwDataHigh)
		{
			return 1;
		}
		else
		{
			return 0;
		}
}

CString MotionLBR::InfoGetModuleCount()//
{
	long m_data;
	CString data;
	AxdInfoGetModuleCount(&m_data);
	data.Format("%d", m_data);
	return data;
}


CString MotionLBR::InfoIsDIOModule()
{
	DWORD m_data;
	CString data;
	AxdInfoIsDIOModule(&m_data);
	data.Format("%d", m_data);
	return data;
}

CString MotionLBR::InfoGetModuleNo()//
{
	DWORD m_data;
	CString data;
	AxdInfoIsDIOModule(&m_data);
	data.Format("%d", m_data);
	return data;
}


