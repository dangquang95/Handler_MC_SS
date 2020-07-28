// khoi tao boi do ba quynh ngay 26/2/2019
//day la thu vien motion tong hop lai dung cho cad motion cua hang Ajinextek co,.LTD

#pragma once

//
#include "AXL.h"
#include "AXM.h"
#include "AXHS.h"
#include "AXD.h"


#pragma comment(lib, "AxL.lib")


class MotionLBR
{
public:
	MotionLBR();
	~MotionLBR();
public:

	//******initialization********
	//khoi tao ban dau - bat buoc
	BOOL Initiaization();
	//Exiting Library
	void ExitingLibrary();
	//Get thong tin tong so axis 
	long InfoGetAxisCount();
	//the first axis number on the specific module of specified base board
	long InfoGetFirstAxisNo();
	//
	CString AddAxisInfo();
	//the information of installed axis such as board number, module number and module ID.
	long InfoGetAxis(long lAxisNo);
	//******Motion parameter******
	//Set so xung cho moi vong quay va do dic chuyen cho moi vong quay
	void MotSetMoveUnitPerPulse(long m_AxisNo, double m_dUnit, long m_lPulse);

	//※ Electronic gear Ratio(전자기어비)
	/*Electric gear ratio] =
	[Number of encoder pulse that is generated during 1 rotation of servo motor] /
		[Number of output ordered pulse of motion controller during 1 rotation of servo motor]*/

	//Start Speed
	void StartSpeed(long m_lAxisNo);
	void Initdata();
	//Pulse Out Method
	void SetPulseOutMethod(long m_lAxisNo, DWORD m_uMethod);
	//Get pulse out method
	CString GetPulseOutMethod(long m_lAxisNo);
	//Encoder Input Method
	void SetEncInputMethod(long m_lAxisNo, DWORD m_uMethod);
	//Get  encoder input method
	CString GetEncInputMethod(long m_lAxisNo);
	//Motion Signal
	//AxmSignalSetLimit
	void SignalSetLimit(long m_lAxisNo, DWORD m_uStopMode, 
		                     DWORD m_uPositiveLevel, DWORD m_uNegativeLevel);
	//Get signal limit value setting
	CString SignalGetLimit(long m_lAxisNo, CString mode);
	//Get signal limit value setting
	CString SignalReadLimit(long m_lAxisNo, CString mode);
	//Set Active Level of inposition signal to Active HIGH,
	void SignalSetInpos(long m_lAxisNo, DWORD m_uUse);
	//set Active Level of alarm signal to Active LOW or HIGHT
	void SignalSetServoAlarm(long m_lAxisNo, DWORD m_uUse);
	//Set Active Level of emergency stop signal to Active HIGH or LOW
	void SignalSetStop(long m_lAxisNo, DWORD m_uStopMode, DWORD m_uLevel);
	BOOL HomeReadSignal(long m_lAxisNo);
	//Return current state of End Limit signal to 0 or 1.
	BOOL SignalReadLimit(long m_lAxisNo, BOOL senser);
	//needed to verify whether inposition signal is inputted
	DOUBLE SignalReadInpos(long m_lAxisNo);
	//Servo drive outputs alarm signal to motion controller.
	DOUBLE SignalReadServoAlarm(long m_lAxisNo);
	//Input Verification of Emergency Stop Signal.
	DOUBLE SignalReadStop(long m_lAxisNo);


	/*********Glossary Of Motion Drive***********************/
	//Set level servo on
	void Servo_OnOff_Level(long lAxisNo, DWORD uLevel);
	//Servo on off
	void Servo_OnOff(long lAxisNo, DWORD uLevel);
	//Get status servo ON or OFF
	BOOL Status_OnOff(long lAxisNo);
	//Set kieu tang toc giam toc
	void Set_Mode_AccDcc(long lAxisNo, DWORD uProfileMode);
	//Get kieu tang toc giam toc
	CString Get_Mode_AccDcc(long lAxisNo);
	//set kieu chay tuong doi or tuyet doi
	void SetAbsRelMode(long lAxisNo, DWORD uProfileMode);
	//Get kieu chay tuong doi or tuyet doi
	BOOL GetAbsRelMode(long lAxisNo);
	//Command run position - phai chay den vi tri  -  moi chay lenh tiep theo
	void MovePos(long lAxisNo, double dPosition, double dMaxVelocity, double dMaxAccel, double dMaxDecel);
	//Command run position - chay lenh tiep theo - khi chua den vi tri
	void MoveStartPos(long lAxisNo, double dPosition, double dMaxVelocity, double dMaxAccel, double dMaxDecel);
	//Get busy
	BOOL ReadInMotion(long lAxisNo);
	//Search Up Edge,Down Edge of home,Limit,EncodZPhase sensor moving to - direction and [0]Slowdown Stop or [1]Emergency Stop.
	//Tim tin hieu home ,limit,Z phase
	void MoveSignalSearch(long lAxisNo, double dMaxVelocity, double dMaxAccel, long lDetectSignal, long lSignalEdge, long lSignalMethod);
	//Tim tin hieu home ,limit,Z phase sau do set gia tri vi tri do gia tri bao nhieu :mac dinh set 0
	void MoveSignalCapture(long lAxisNo, double dMaxVelocity, double dMaxAccel, long lDetectSignal, long lSignalEdge, long lSignalMethod);
	//Get gia tri vi tri cua senser sau khi MoveSignalCapture
	double MoveGetCapturePos(long lAxisNo);
	//Reset error
	void ServoAlarmReset(long lAxisNo);



	//******Home Search Drive*****
	//Sets home search method. 
	void HomeSetMethod(long lAxisNo, long nHmDir, DWORD uHomeSignal, DWORD uZphas, double dHomeClrTime, double dHomeOffset);
	//Set toc do luc ve home
	void HomeSetVel(long lAxisNo, double dVelFirst, double dVelSecond, double dVelThird, double dvelLast, double dAccFirst, double dAccSecond);
	//Home
	void HomeSetStart(long lAxisNo);
	//Get rate % when to home
	DWORD HomeGetRate(long lAxisNo);
	//Get result home
	DWORD HomeGetResult(long lAxisNo);


	//******Stop Of Motion Drive******//
	//Dung khan cap
	void MoveEStop(long lAxisNo);
	//Duung truc cham
	void MoveSStop(long lAxisNo);
	//Dung truc voi su giam toc
	void MoveStop(long lAxisNo, double dMaxDecel);

	//******Verification Of Motion Drive State--Tham dinh trang thai cua truc servo*******
	//Get current position Act
	double StatusGetActPos(long lAxisNo);
	//Get current position Cmd
	double StatusGetCmdPos(long lAxisNo);
	//Get error axis khi vi tri theo Cmd va Act khac nhau
	DWORD StatusReadPosError(long lAxisNo);
	//Get Toc do hien tai
	DWORD StatusReadVel(long lAxisNo);
	//Get Status pulse dau ra
	DWORD StatusReadInMotion(long lAxisNo);
	//Get drive state on axis 
	DWORD StatusReadMotion(long lAxisNo);
	//Get state axis stop
	DWORD StatusReadStop(long lAxisNo);
	//********Multi-Axis Drive***********//
	//Chay noi suy 2 truc XY tuyet doi - doi chay den vi tri mong muon roi moi thuc hien lenh tiep theo
	void MoveMultiPosAbsXY(double dPositionX, double dPositionY, 
		double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel);
	//Chay noi suy 2 truc XY tuong doi - doi chay den vi tri mong muon roi moi thuc hien lenh tiep theo
	void MoveMultiPosReXY(double dPositionX, double dPositionY, 
		double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel);
	//Chay noi suy 3 truc XYZ tuyet doi - doi chay den vi tri mong muon roi moi thuc hien lenh tiep theo
	void MoveMultiPosAbsXYZ(double dPositionX, double dPositionY, double dPositionZ, 
		double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel);
	//Chay noi suy 3 truc XYZ tuong doi - doi chay den vi tri mong muon roi moi thuc hien lenh tiep theo
	void MoveMultiPosReXYZ(double dPositionX, double dPositionY, double dPositionZ, 
		double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel);


	// Chay noi suy 2 truc XY tuyet doi - chua chay den vi tri mong muon thi da thuc hien lenh tiep theo
	void MoveStartMultiPosAbsXY(double dPositionX, double dPositionY,
		double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel);
	// Chay noi suy 2 truc XY tuong doi - chua chay den vi tri mong muon thi da thuc hien lenh tiep theo
	void MoveStartMultiPosReXY(double dPositionX, double dPositionY, 
		double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel);
	// Chay noi suy 3 truc XYZ tuyet doi - chua chay den vi tri mong muon thi da thuc hien lenh tiep theo
	void MoveStartMultiPosAbsXYZ(double dPositionX, double dPositionY, double dPositionZ, 
		double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel);
	// Chay noi suy 3 truc XYZ tuong doi - chua chay den vi tri mong muon thi da thuc hien lenh tiep theo
	void MoveStartMultiPosReXYZ(double dPositionX, double dPositionY, double dPositionZ, 
		double m_dMaxVelocity, double m_dMaxAccel, double m_dMaxDecel);
	//Jog run
	void JogRun(long lAxisNo, double dVel, double dAccel, double dDecel);
	//Jog stop
	void JogStop(long lAxisNo);

	//******Interpolation Drive******//
	//Chua viet

	//Input -- Output

	void SetOuput(int m_output);
	void ResetOuput(int m_output);
	BOOL ReadOuput(int m_output);
	BOOL ReadInput(int m_input);

	CString InfoIsDIOModule();
	CString InfoGetModuleNo();

	CString InfoGetModuleCount();
	
};

