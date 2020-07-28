#include "StdAfx.h"
#include "ClientSocket.h"


ClientSocket::ClientSocket(sClient client)
{
	m_Client.strIP = client.strIP;
	m_Client.iPort = client.iPort;
	m_Client.dTime = client.dTime;
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	HWND hWnd = NULL;

	m_pObjEthernet = new MEtherNet(MEtherNet::eClientMode, m_Client.iPort, m_Client.strIP, pFrm->GetSafeHwnd());
	m_pObjEthernet->Define_ConnectMsg(WM_ETHERNET_CONNECT);
	m_pObjEthernet->Initialize();
	bEndSocket = FALSE;
	bIris = FALSE;
}


ClientSocket::~ClientSocket()
{
	m_pObjEthernet->closeClientSocket();
	if (m_pObjEthernet) delete m_pObjEthernet;
}

UINT ClientSocket::ThreadSocket(LPVOID pParam)
{
	ClientSocket *pThis;
	pThis = (ClientSocket *)pParam;
	
	while (!pThis->bEndSocket)
	{
		pThis->LoopSocket();

		Sleep(pThis->m_Client.dTime);
	}
	pThis->bEndSocket = TRUE;
	return 0;
}

void ClientSocket::LoopSocket()
{
	CString strData = "";
	CString strbuf;
	CString strTemp[10];
	m_pObjEthernet->SendData(CHECK_READY, m_Client.strIP);
	if (m_pObjEthernet->ReadData(strData, m_Client.strIP) == ERR_SUCCESS) {
		int iLen = 0;
		iLen = strData.GetLength();
		if (iLen < 9) {
			return;
		}
		int iOut = 0;
		int i = 0;
		while (AfxExtractSubString(strbuf, strData, i, _T(' ')))
		{
			if (i > 9)
			{
				break;
			}

			if (strbuf.Find(_T("="), 0) == -1)
			{
				i++;
				continue;
			}

			i++;
			strTemp[iOut++] = strbuf;
		}
		if (strTemp[0].Find(_T("FUNCTION_RPY"), 0) != -1)
		{
			if (AfxExtractSubString(strbuf, strTemp[0], 1, _T('=')) == 0)
				return;
			strbuf.TrimLeft();
			strbuf.TrimRight();

			if (strbuf == _T("TESTER_READY")) {


				if (strTemp[4].Find(_T("RESULT"), 0) != -1)
				{
					if (AfxExtractSubString(strbuf, strTemp[4], 1, _T('=')) == 0)
						return ;
					strbuf.TrimLeft();
					strbuf.TrimRight();

					if (strbuf == _T("NONE")){
						eResTest.m_eModuleState = eModuleState_None;
					}
					else if (strbuf == _T("TESTING")){
						eResTest.m_eModuleState = eModuleState_Testing;
					}
					else if (strbuf == _T("OK") || strbuf == _T("PASS")) {
						eResTest.m_eModuleState = eModuleState_Pass;
					}
					else if (strbuf == _T("NG")) {
						eResTest.m_eModuleState = eModuleState_NG;
					}
				}
				if (strTemp[2].Find(_T("INDEX"), 0) != -1)
				{
					if (AfxExtractSubString(strbuf, strTemp[2], 1, _T('=')) == 0)
						return;
					strbuf.TrimLeft();
					strbuf.TrimRight();

					eResTest.m_iIndex = _tstoi(strbuf);
				}
				if (strTemp[5].Find(_T("FAILCODE"), 0) != -1)
				{
					if (AfxExtractSubString(strbuf, strTemp[5], 1, _T('=')) == 0)
						return ;
					strbuf.TrimLeft();
					strbuf.TrimRight();
					eResTest.m_iFailcode = _tstoi(strbuf);
					if (eResTest.m_iFailcode == ERR_IRIS) {
						bIris = TRUE;
					}
					
				}
				
			}
			
		}

		
	}
}

void ClientSocket::StartTest(BOOL bSkip)
{
	if (bSkip) {
		m_pObjEthernet->SendData(TEST_SKIP, m_Client.strIP);
	}
	else {
		m_pObjEthernet->SendData(TEST_CAM, m_Client.strIP);

	}
}


BOOL ClientSocket::isConnected()
{
	if (m_pObjEthernet != NULL) {
		if (m_pObjEthernet->IsMateConnected() == TRUE) {
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	else {
		return FALSE;
	}
}


void ClientSocket::StartThread()
{
	bEndSocket = FALSE;
	AfxBeginThread(ThreadSocket, this);
}
void ClientSocket::StopThread()
{
	bEndSocket = TRUE;
}

ETesterFunction ClientSocket::GetStatus()
{
	return eResTest.m_eModuleState;
}

int ClientSocket::GetIndex()
{
	return eResTest.m_iIndex;
}

BOOL ClientSocket::GetIris()
{
	return bIris;
}

void ClientSocket::SetIris()
{
	bIris = FALSE;
}

void ClientSocket::ReadDataClient(CString m_IP, int m_Port, double m_time)
{
	m_Client.strIP = m_IP;
	m_Client.iPort = m_Port;
	m_Client.dTime = m_time;

}
