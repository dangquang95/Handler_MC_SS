#include "StdAfx.h"
#include "ConnectSocket.h"

CConnectSocket::CConnectSocket(void)
	: m_bNewMsg(FALSE)
	, m_strRecvMsg(_T(""))
	, m_bMotionDone(FALSE)
	, m_bConnected(FALSE)
	, m_bResult(FALSE)
{
}


CConnectSocket::~CConnectSocket(void)
{
}

void CConnectSocket::OnClose(int nErrorCode)
{
	ShutDown();
	Close();

	m_bConnected = FALSE;

	CSocket::OnClose(nErrorCode);

	//AfxMessageBox(_T("ERROR: Disconnected from server!"));
}


void CConnectSocket::OnReceive(int nErrorCode)
{
	char szBuf[1024];
	TCHAR wszBuf[1024];
	::ZeroMemory(szBuf, sizeof(szBuf));
	::ZeroMemory(wszBuf, sizeof(wszBuf));

	m_strRecvMsg = _T("");

	if (Receive(szBuf, sizeof(szBuf)) > 0)
	{
		m_bNewMsg = TRUE;
		//MultiByteToWideChar(CP_ACP, 0, szBuf, sizeof(szBuf), LPWSTR(wszBuf), sizeof(wszBuf));
		m_strRecvMsg = szBuf;
		if (m_strRecvMsg.Find(_T("ok")) != -1)
			m_bResult = TRUE;
		else if (m_strRecvMsg.Find(_T("ng")) != -1)
			m_bResult = FALSE;

		if (m_strRecvMsg.Find(_T("done:ok")) != -1)
		{		
		m_bMotionDone = TRUE;
		MotionRobotDone = TRUE;
	     }

		CString cstrLog = CString("RobotGTC_") + m_strRecvMsg;

		ActionRevice = TRUE;
	}

	m_bNewMsg = TRUE;

	CSocket::OnReceive(nErrorCode);
} 

BOOL CConnectSocket::CheckNewMsg(void)
{
	return m_bNewMsg;
}


CString CConnectSocket::GetNewMsg(void)
{
	m_bNewMsg = FALSE;
	return m_strRecvMsg;
}


void CConnectSocket::Connected(BOOL bConnected)
{
	m_bConnected = bConnected;
}
