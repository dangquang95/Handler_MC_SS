#pragma once
#include "connectsocket.h"



const int ERR_GTC_ROBOT_SUCCESS = 0;
const int ERR_GTC_ROBOT_FAIL = 1;

class GTCRobotCtrl2 :
	public CConnectSocket
{
public:
	GTCRobotCtrl2(CString strIP, int iPortNum);
	~GTCRobotCtrl2(void);

	CConnectSocket m_Socket;
	/** Thread Handle */
	CWinThread* m_pThread;

	BOOL Connect(); 
	BOOL Connect(CString strIP, int iPortNum);
	void ThreadStop();
	int Disconnect();
	BOOL IsConnected(void);
	int SendMsg(CString strMsg);
	CString GetMsg();
	BOOL CheckMsg();

	BOOL GetResult();

	BOOL m_bSocketCreated;
	BOOL m_bConnected;

	CCriticalSection m_csSendMsg;

	CString m_strIP;
	int m_iPortNum;

	CString m_strMsg;
	CString m_SendMsg;

	// robot command
	int MoveTeachingPos(CString strName, int movespeed);

	BOOL Align(void);
	BOOL MotionDone();
	void Ready();
	void Pick();
	void InPut_MFT(int iMachine, int iPos, double P1_X=0, double P1_Y=0, double P1_Z=0);
	void OutPut_MFT(int iMachine, int iPos, double P1_X=0, double P1_Y=0, double P1_Z=0);
	void NGBufferPlace(int iGrip, int iJig);
	void NGBufferPick();
	void NGConveyorPlace(int iGrip);
	void OKPlace(int iGrip);
	void PlaceAfterOutPut(int iJob1, int iJob2);
	void ExecuteJob(int iJob);
	int MoveAbs(double x, double y, double z, double rx, double ry, double rz);
	int MoveRel(double x, double y=0.0, double z=0.0, double rx=0.0, double ry=0.0, double rz=0.0, double speed=0.1);

	void ResetRobotCmd(void);
	BOOL CheckConnection(void);

	// ¼öÁ¤
	int StatusReturn();
	int MoveHome();
	

};

