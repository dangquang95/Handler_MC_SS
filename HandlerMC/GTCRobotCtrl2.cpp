#include "StdAfx.h"
#include "GTCRobotCtrl2.h"
#include "MyDefine.h"

UINT ThreadRecMsgKuka(LPVOID pParam)
{
	GTCRobotCtrl2 *pSocket = (GTCRobotCtrl2*)pParam;
	TRACE("GTCRobotCtrl2 Thread Run\n");
	while( pSocket->m_bConnected )
	{
		if (!pSocket->IsConnected())
		{
			pSocket->m_bConnected = FALSE;
			return 0;
		}
			
		pSocket->CheckMsg();
		Sleep(10);
	}
	TRACE("GTCRobotCtrl2 Thread Stop\n");
	return 0;
}


GTCRobotCtrl2::GTCRobotCtrl2(CString strIP, int iPortNum)
{
	AfxSocketInit();
	m_bSocketCreated = FALSE;
	m_bConnected = FALSE;
	m_strIP = strIP;
	m_iPortNum = iPortNum;

	m_pThread = NULL;
}


GTCRobotCtrl2::~GTCRobotCtrl2(void)
{
	Disconnect();
	

	TRACE("GTCRobotCtrl2 Class Destruction is Completed.\n");
}


BOOL GTCRobotCtrl2::Connect()
{
	if (m_bConnected == FALSE)
	{
		if (!m_Socket.m_bConnected)
		{
			m_bSocketCreated = m_Socket.Create();
			m_bConnected = m_Socket.Connect(m_strIP, m_iPortNum);

			m_pThread = NULL;
			if (m_bConnected)
			{
				m_pThread = AfxBeginThread(ThreadRecMsgKuka, (LPVOID)this);
				m_Socket.Connected(TRUE);
			}
			else
			{
				Disconnect();
				m_Socket.Connected(FALSE);
			}
		}
		return m_bConnected;
	}
	return FALSE;
}

BOOL GTCRobotCtrl2::Connect(CString strIP, int iPortNum)
{
	m_strIP = strIP;
	m_iPortNum = iPortNum;
	if (!m_Socket.m_bConnected)
	{
		m_bSocketCreated = m_Socket.Create();
		m_bConnected = m_Socket.Connect(m_strIP, m_iPortNum);

		if (m_bConnected)
		{
			m_pThread = AfxBeginThread(ThreadRecMsgKuka, (LPVOID)this);
			m_Socket.Connected(TRUE);
		}
		else
		{
			Disconnect();
			m_Socket.Connected(FALSE);
		}
	}

	return m_bConnected;
}

void GTCRobotCtrl2::ThreadStop()
{
	DWORD exitcode;

	Sleep(100);


	if (m_pThread != NULL)
	{
		exitcode = ::WaitForSingleObject(m_pThread->m_hThread, 3000);
		if (exitcode == WAIT_TIMEOUT)
			::TerminateThread(m_pThread->m_hThread, exitcode);
	}
	
	m_pThread = NULL;
}

int GTCRobotCtrl2::Disconnect()
{
	m_bConnected = FALSE;
	ThreadStop();
	m_Socket.ShutDown();
	m_Socket.Close();

	m_Socket.Connected(FALSE);
	return ERR_GTC_ROBOT_SUCCESS;
}

BOOL GTCRobotCtrl2::IsConnected(void)
{
	return m_Socket.m_bConnected;
}


int GTCRobotCtrl2::SendMsg(CString strMsg)
{
	if (IsConnected())
	{
		m_csSendMsg.Lock();
		CString strData = strMsg;

		char nameBuf[512];
		::WideCharToMultiByte(CP_ACP, 0, CT2W(strData), -1, nameBuf, strData.GetLength() + 1, NULL, NULL);

		m_Socket.Send(nameBuf, strData.GetLength());
		m_Socket.m_bResult = FALSE;
		m_Socket.m_bMotionDone = FALSE;
		m_csSendMsg.Unlock();
	}
	
	return ERR_GTC_ROBOT_SUCCESS;
}


CString GTCRobotCtrl2::GetMsg()
{
	return m_Socket.GetNewMsg();
}


BOOL GTCRobotCtrl2::CheckMsg()
{
	return m_Socket.CheckNewMsg();
}

BOOL GTCRobotCtrl2::GetResult()
{
	return m_Socket.m_bResult;
}


int GTCRobotCtrl2::MoveTeachingPos(CString strName, int movespeed)
{
	/*CString strMsg;
	strMsg.Format(_T("<Vision><id>%d</id><no_send>0</no_send><function_name>move_pos</function_name><position_name>%s</position_name><velPTP>%d</velPTP></Vision>"), MOVE_VISION_POS, strName, movespeed);
	SendMsg(strMsg);*/

	m_Socket.m_bMotionDone = FALSE;
	return ERR_GTC_ROBOT_SUCCESS;
}


int GTCRobotCtrl2::MoveAbs(double x, double y, double z, double rx, double ry, double rz)
{
	return ERR_GTC_ROBOT_SUCCESS;
}


int GTCRobotCtrl2::MoveRel(double x, double y, double z, double rx, double ry, double rz, double speed)
{
	//MakeGTCFunction(MOVE_REL, x, y, z, rx, ry, rz, speed);
	return ERR_GTC_ROBOT_SUCCESS;
}

int GTCRobotCtrl2::StatusReturn()
{
	int iResult;
	CString strMsg;
	strMsg.Format(_T("Status_Return()"));
	iResult = SendMsg(strMsg);
	if (iResult)
	{
		//WriteErrorLog(_T("Log"));
		return iResult;
	}
	return ERR_GTC_ROBOT_SUCCESS;
}

int GTCRobotCtrl2::MoveHome()
{
	int iResult;
	CString strMsg;
	strMsg.Format(_T("Home_Pos()"));
	iResult = SendMsg(strMsg);
	if (iResult)
	{
		//WriteErrorLog(_T("Log"));
		return iResult;
	}
	return ERR_GTC_ROBOT_SUCCESS;
}

BOOL GTCRobotCtrl2::Align(void)
{
	return 0;
}


BOOL GTCRobotCtrl2::MotionDone()
{
	if(m_Socket.m_bMotionDone)
	{
		Sleep(10);
		return TRUE;
	}
	return FALSE;
}

void GTCRobotCtrl2::Ready()
{
	
	CString strMsg;
	strMsg.Format(_T("READY()"));
	SendMsg(strMsg);
}

void GTCRobotCtrl2::Pick()
{
	
	CString strMsg;
	strMsg.Format(_T("PICK()"));
	SendMsg(strMsg);
}

void GTCRobotCtrl2::InPut_MFT(int iMachine, int iPos, double P1_X, double P1_Y, double P1_Z)
{
	CString strMsg;
	strMsg.Format(_T("INPUT_%d_%d(%.1f,%.1f,%.1f)"), iMachine, iPos, P1_X, P1_Y, P1_Z);
	SendMsg(strMsg);
}

void GTCRobotCtrl2::OutPut_MFT(int iMachine, int iPos, double P1_X, double P1_Y, double P1_Z)
{
	CString strMsg;
	strMsg.Format(_T("OUTPUT_%d_%d(%.1f,%.1f,%.1f)"), iMachine, iPos, P1_X, P1_Y, P1_Z);
	SendMsg(strMsg);
}

void GTCRobotCtrl2::NGBufferPlace(int iGrip, int iJig)
{
	CString strMsg;
	strMsg.Format(_T("NG_%d_%d"), iGrip, iJig);
	SendMsg(strMsg);
}

void GTCRobotCtrl2::NGBufferPick()
{
	CString strMsg;
	strMsg.Format(_T("BUFFER()"));
	SendMsg(strMsg);
}

void GTCRobotCtrl2::NGConveyorPlace(int iGrip)
{
	CString strMsg;
	strMsg.Format(_T("NG_PLACE%d"), iGrip);
	SendMsg(strMsg);
}

void GTCRobotCtrl2::OKPlace(int iGrip)
{
	CString strMsg;
	strMsg.Format(_T("OK_PLACE%d"), iGrip);
	SendMsg(strMsg);
}

void GTCRobotCtrl2::PlaceAfterOutPut(int iJob1, int iJob2)
{
	CString strMsg;
	strMsg.Format(("PLACE(%d,%d"), iJob1, iJob2);
	strMsg = strMsg + ")";
	SendMsg(strMsg);
}

void GTCRobotCtrl2::ExecuteJob(int iJob)
{

}

