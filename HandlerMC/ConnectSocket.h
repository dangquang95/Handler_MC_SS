#pragma once
#include "afxsock.h"
class CConnectSocket :
	public CSocket
{
public:
	CConnectSocket(void);
	~CConnectSocket(void);

	void OnClose(int nErrorCode);
	void OnReceive(int nErrorCode);

protected:
	BOOL m_bNewMsg;
public:
	BOOL CheckNewMsg(void);
//protected:
	CString m_strRecvMsg;
public:
	CString GetNewMsg(void);
	BOOL m_bMotionDone;
	BOOL m_bResult;
	BOOL m_bConnected;
	BOOL ActionRevice;
	BOOL MotionRobotDone;
	void Connected(BOOL bConnected);
};

