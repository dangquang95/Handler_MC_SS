// MEtherNet_AF.cpp: implementation of the MEtherNet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MEtherNet.h"
#include "DefSystem.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
unsigned long g_irecvBytes = 0;

void CALLBACK CompletionRoutine(DWORD error, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverlapped, DWORD flags);

// 할일 : 
// Message Protocol 만들기.. [Message Byte][Message 내용]
// 선택적으로 가능하도록~~~~

MEtherNet::MEtherNet(eMode mode, int iPort, CString strMateIP, HWND hNotify)
{
	//m_eMode = eClientMode;
	m_eMode = mode;
	m_iPort = iPort;
	m_strMateIP[eSingleSessionMate] = strMateIP;
	m_hClientSock = NULL;
	m_bLiveThread = TRUE;
	memset(m_SockArray,NULL,sizeof(m_SockArray));
	memset(m_bConnected,FALSE,sizeof(m_bConnected));
	memset(m_bReceived,FALSE,sizeof(m_bReceived));

	//Add 12/5/2017
	memset(m_eStepRecevie, ERECEVIE_NONE, sizeof(m_eStepRecevie));
	memset(m_eStepSend, ESEND_NONE, sizeof(m_eStepSend));
	//

	//memset(m_SRecevieFile, NULL, sizeof(m_SRecevieFile));
	//memset(m_SSendFile,NULL, sizeof(m_SSendFile));

	m_iMaxClient = 1;


	//Define msg
	
	m_uiConnectMessage = WM_USER + 1000 ;
	//m_uiReceiveMessage = WM_USER + 1001;
	m_uiReceiveMessageFile = WM_USER + 1004;

	m_hNotifyHandle = hNotify;
	m_cEndChar = END_CHARACTER;

	m_bLock = 0;

	m_bThreadSendfile = FALSE;
	/*for (int i = 0; i < 10; i++)
	{
		m_eStepSend[i] = ESEND_NONE;
	}*/

	//memset(m_eStepSend, NULL, sizeof(m_eStepSend));
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		//m_SRecevieFile[i].m_iRecevieAll = FALSE;
	}
	
	memset(m_bIsConnected, FALSE, sizeof(m_bIsConnected));
	/*for (int i = 0; i < MAX_CLIENT; i++)
	{
		m_bIsConnected[i]= FALSE;
	}*/
	
	

	InitializeCommunicationData();

	InitializeCriticalSection(&m_Sync);
}

MEtherNet::~MEtherNet()
{
	if(m_bLiveThread)
	{
		m_bLiveThread = FALSE;
		Sleep(1000);
		if(	m_eMode == eServerMode) closeServerSockets();
		else closeClientSocket();
	}
	else
	{
		if (m_eMode == eServerMode) 
			closeServerSockets();
		else 
			closeClientSocket();
	}

	for(int i=0; i<WSA_MAXIMUM_WAIT_EVENTS; i++)
		m_strQue[i].Reset();

}


int MEtherNet::Initialize()
{
	int iResult = ERR_SUCCESS; 
	strFileName = "";
	iStep = 0;
	if(m_eMode == eServerMode) 
		iResult = startServer();
	else 
		iResult = startClient();
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		m_eStepRecevie[i] = ERECEVIE_NONE;
	}
	for (int i = 0; i < MAX_CLIENT; i++)
	{
		m_eStepSend[i] = ESEND_NONE;
	}

	for (int i = 0; i < MAX_CLIENT; i++)
	{
		sizeOfFileSend[i] = 1;
	}

	m_eOpModeEthernet = E_ETHERNET_RUN_MODE;

	for (int i = 0; i < MAX_CLIENT; i++)
	{
// 		m_SRecevieFile[i].m_iRecevieOK = 0;
// 		m_SRecevieFile[i].iBegin = 0;
// 		m_SRecevieFile[i].cstrFileDataReceive = "";
		m_SRecevieFile[i].m_iEEthernetMode = eEthernetSendMess;
	}

	//m_pEtherNet = new MEtherNet(MEtherNet::eClientMode, 8000, _T(""), GetSafeHwnd());
	
	m_bLockShowLog = TRUE;
	

	return iResult;
}

int MEtherNet::AddClient(CString strClientIP)
{
	if(m_eMode == eClientMode)
		return ERR_NOT_SUPPORTED;

	if(m_iMaxClient >= eClientMax)
		return ERR_CLIENT_NO_OVER;

	m_strMateIP[m_iMaxClient] = strClientIP;
	//Huy
	m_strMateIPStatic[m_iMaxClient] = strClientIP;

	m_iMaxClient++;

	return ERR_SUCCESS;
}


int MEtherNet::initServerSocket()
{
	WSADATA wSaData;
	SOCKET hServSock;
	SOCKADDR_IN servAddr;

	if(WSAStartup(MAKEWORD(2,2), &wSaData) != 0)
		return ERR_WSA_START_UP;

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if(hServSock == INVALID_SOCKET)
		return ERR_SOCKET;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port=htons(u_short(m_iPort));

	//(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr))
	::bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));
		

	WSAEVENT wsaEvent;
	wsaEvent = WSACreateEvent();
	if(WSAEventSelect(hServSock, wsaEvent, FD_ACCEPT) == SOCKET_ERROR)
		return ERR_WSAEVENT_SELECT;
	
	if(listen(hServSock, MAX_CLIENT) == SOCKET_ERROR)
		return ERR_LISTEN;	

	m_iSockNumber = 0;
	m_SockArray[m_iSockNumber] = hServSock;
	m_EventArray[m_iSockNumber] = wsaEvent;
	
	TRACE("m_iSockNumber = %d\n", m_iSockNumber);
	m_iSockNumber++;

	return ERR_SUCCESS;	
}

int MEtherNet::startServer()
{
	int iResult;
	iResult = initServerSocket();
	if(iResult !=  ERR_SUCCESS)
		return iResult;
	startServerSendFile();
	m_pThread = AfxBeginThread(ThreadServer,this);
	::SetThreadPriority(m_pThread->m_hThread, THREAD_PRIORITY_ABOVE_NORMAL);
	m_bLiveThread = TRUE;

	return ERR_SUCCESS;	
}

UINT MEtherNet::ThreadServer(LPVOID param)
{
	MEtherNet* pMain = ( MEtherNet* )param;
	pMain->ThreadMode();
	
	return 0;
	
}

void MEtherNet::ThreadMode()
{
	
	SOCKADDR_IN clntAddr;
	int clntAddrSize;

	WSAEVENT wsaEvent, dummyEvent;
	WSANETWORKEVENTS netEvents;
	SOCKET hClntSock;

	int index, nResult, i;
	char message[MAX_ETHERNET_BUFFER_SIZE-1];
	CString strBuf;
	BOOL	bReceiveAll = FALSE;


	unsigned long flags = 0;
	WSAOVERLAPPED overlapped;


	dummyEvent = WSACreateEvent();
	MydummyEvent = dummyEvent;


	

	while (m_bLiveThread)
	{
		switch (m_eOpModeEthernet)
		{
		case E_ETHERNET_RUN_MODE:
			
			nResult = WSAWaitForMultipleEvents(m_iSockNumber, m_EventArray, FALSE, 1000, FALSE);
			if (nResult == WSA_WAIT_TIMEOUT) continue;
			if (nResult == WSA_WAIT_FAILED) break;

			index = nResult - WSA_WAIT_EVENT_0;

			for (i = index; i < m_iSockNumber; i++)
			{
				m_SockArrayTemp[i] = m_SockArray[i];
				nResult = WSAWaitForMultipleEvents(1, &(m_EventArray[i]), TRUE, 0, FALSE);
				if (nResult == WSA_WAIT_TIMEOUT || nResult == WSA_WAIT_FAILED) continue;

				WSAEnumNetworkEvents(m_SockArray[i], m_EventArray[i], &netEvents);

				if (netEvents.lNetworkEvents & FD_ACCEPT) // 연결 요청의 경우
				{
					if (netEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
					{
						nResult = ERR_ACCEPT;
						break;
					}

					clntAddrSize = sizeof(clntAddr);
					
					hClntSock = accept(m_SockArray[i], (SOCKADDR*)&clntAddr, &clntAddrSize);
					
					
					if (hClntSock == INVALID_SOCKET)
					{
						nResult = ERR_ACCEPT;
						break;
					}


					//Get ip from Socket
					CString cstrAddr = "";

					cstrAddr.Format("%d.%d.%d.%d",
						int(clntAddr.sin_addr.s_addr & 0xFF),
						int((clntAddr.sin_addr.s_addr & 0xFF00) >> 8),
						int((clntAddr.sin_addr.s_addr & 0xFF0000) >> 16),
						int((clntAddr.sin_addr.s_addr & 0xFF000000) >> 24));

					TRACE("ip: %s\n", cstrAddr);
					m_strMateIP[m_iSockNumber] = cstrAddr;
					//m_strMateIP[m_iSockNumber] = "192.168.1.201";
					
					int i = GetMateIDStatic(m_strMateIP[m_iSockNumber]);

					::PostMessage(m_hNotifyHandle, m_uiConnectMessage, GetMateIDStatic(m_strMateIP[m_iSockNumber]) - 1, (LPARAM)(1));//Turn on Socket
					//
					wsaEvent = WSACreateEvent();
					WSAEventSelect(hClntSock, wsaEvent, FD_READ | FD_CLOSE);

					m_SockArray[m_iSockNumber] = hClntSock;
					m_EventArray[m_iSockNumber] = wsaEvent;
					m_bConnected[m_iSockNumber] = TRUE;

					m_iSockNumber++;

					TRACE("Connected :%d \n", hClntSock);


					sprintf_s(message, sizeof(message), "%s", m_strMateIP[i + 1].GetBuffer());
					TRACE("Connected + message = %s \n", message);
					if (m_hNotifyHandle != NULL)
						//::PostMessage(pMain->m_hNotifyHandle, pMain->m_uiConnectMessage, i+1, (LPARAM)(message));
						//::PostMessage(m_hNotifyHandle, m_uiConnectMessage, i + 1, (LPARAM)(1));

					if (m_iSockNumber > m_iMaxClient) // Client갯수를 초과하면 Accept를 허용하지 않는다.
					{
						WSAEventSelect(m_SockArray[0], m_EventArray[0], 0);
					}

				}

				if (netEvents.lNetworkEvents & FD_READ) // 데이터 전송의 경우
				{
					if (netEvents.iErrorCode[FD_READ_BIT] != 0)
					{
						nResult = ERR_READ;
						break;
					}

					bReceiveAll = FALSE;
					flags = 0;
					memset(message, 0, sizeof(message));
					memset(&overlapped, 0, sizeof(overlapped));
					//m_dataBufRev.len = MAX_ETHERNET_BUFFER_SIZE;
					m_dataBufRev.len = 1024 ;
					m_dataBufRev.buf = message;
					if (WSARecv(m_SockArray[i], &m_dataBufRev, 1, &g_irecvBytes, &flags, &overlapped, CompletionRoutine) == SOCKET_ERROR)
					{
						nResult = ERR_READ;
						break;
					}
					cstrDataBufRev = m_dataBufRev.buf;
					TRACE("Data reciever %s\n", cstrDataBufRev);


					if (m_SRecevieFile[GetMateIDStatic(m_strMateIP[i]) - 1].m_iEEthernetMode == eEthernetSendMess)
					{
						//log data input
						//TRACE("Data reciever %s\n", cstrDataBufRev);

						//Read data All
						if (m_bLockShowLog == FALSE)
						{
							if (cstrDataBufRev.GetLength() > 0 && cstrDataBufRev.GetLength() < 40)
							{
								//m_SRecevieFile[GetMateIDStatic(m_strMateIP[i]) - 1].cstrFileDataReceiveAll = cstrDataBufRev;
								//m_SRecevieFile[GetMateIDStatic(m_strMateIP[i]) - 1].m_iRecevieAll = TRUE;
							}
						}


						if (cstrDataBufRev.Find("a_\\") != -1)
						{
							m_eStepRecevie[GetMateIDStatic(m_strMateIP[i]) - 1] = ERECEVIE_INIT;
// 							if (m_bLockShowLog == FALSE)
// 								AddLog(cstrDataBufRev, GetMateIDStatic(m_strMateIP[i]) - 1);
// 							//::SendMessage(m_hNotifyHandle, m_uiConnectMessage, 3, (LPARAM)(LPCTSTR)cstrDataBufRev);
// 							//m_SRecevieFile[GetMateIDStatic(m_strMateIP[i]) - 1].cstrFileDataReceive = cstrDataBufRev;
// 							m_SRecevieFile[GetMateIDStatic(m_strMateIP[i]) - 1].m_iRecevieOK = TRUE;
						}
// 						else if (cstrDataBufRev.Find("a_\\") != -1)        //Start receive
// 						{
// 							m_eStepRecevie[GetMateIDStatic(m_strMateIP[i]) - 1] = ERECEVIE_INIT;
// 						}
// 						else if (cstrDataBufRev.Find("ping") != -1)
// 						{
// 							SendData("alive\n", m_strMateIP[i]);
// 						}
						
						RecevieFileLoop(GetMateIDStatic(m_strMateIP[i]));          //ReceiveFile
					}
					else if(m_SRecevieFile[GetMateIDStatic(m_strMateIP[i]) - 1].m_iEEthernetMode == eEthernetSendFile)
					{
						RecevieFileLoop(GetMateIDStatic(m_strMateIP[i]));          //ReceiveFile
					}
					

					if (m_hNotifyHandle != NULL)
					{
						TRACE(_T("Print test = %s\n"), test);

						//::PostMessage(pMain->m_hNotifyHandle, pMain->m_uiReceiveMessage, i+1, (LPARAM)(message));
						//::SendMessage(m_hNotifyHandle, m_uiReceiveMessage, i, (LPARAM)(pMain));  // client Port, LPARAM
					}

					break;
				}

				if (netEvents.lNetworkEvents & FD_CLOSE)
				{
					//if (netEvents.iErrorCode[FD_CLOSE_BIT] != 0)
					//{
					//	nResult = ERR_CLOSE;
					//	//break;
					//}
					::PostMessage(m_hNotifyHandle, m_uiConnectMessage, GetMateIDStatic(m_strMateIP[i]) - 1, (LPARAM)(0));  //Send Msg connected to MainFrame

					
					WSACloseEvent(m_EventArray[i]);
						closesocket(m_SockArray[i]);
						m_bIsConnected[i] = FALSE;
					TRACE("Close Client :%d \n", m_SockArray[i]);

					

					m_bConnected[i] = FALSE;
					m_bReceived[i] = FALSE;
					m_iSockNumber--;
					for (int j = i; j < m_iSockNumber; j++)
					{
						m_SockArray[j] = m_SockArray[j + 1];
						m_EventArray[j] = m_EventArray[j + 1];
						m_bConnected[j] = m_bConnected[j + 1];
						m_bReceived[j] = m_bReceived[j + 1];
						m_strMateIP[j] = m_strMateIP[j + 1];

						m_strQue[j].Reset();
						for (;;)
						{
							if (m_strQue[j + 1].IsEmpty()) break;
							strBuf = m_strQue[j + 1].Pop();
							m_strQue[j].Push(strBuf);
						}
					}

					sprintf_s(message, sizeof(message), "%s", m_strMateIP[i].GetBuffer());
					TRACE("mess = %s", message);
					/*	if (m_hNotifyHandle != NULL)
					::PostMessage(m_hNotifyHandle, m_uiCloseMessage, i, (LPARAM)(pMain));*/

					if (m_iSockNumber == m_iMaxClient) // Client갯수를 넘지 않으면 Accept를 허용한다.
					{
						WSAEventSelect(m_SockArray[0], m_EventArray[0], FD_ACCEPT);
					}
				}
			}
			break;
		case E_ETHERNET_RECEVIE_MODE:
			break;
		case E_ETHERNET_SENFILE_MODE:
			break;
		}
		Sleep(1);
	}
	//m_bLiveThread = FALSE; -> move to end

	TRACE("Call Close socket...");

	closeServerSockets();
	m_bLiveThread = FALSE;
}

void MEtherNet::StopThreadServerSockets()
{
	m_bLiveThread = FALSE;
	Sleep(100);
}

int MEtherNet::closeServerSockets()
{
	for(int i=0; i<m_iSockNumber; i++)
	{
		//TRACE("m_iSockNumber  %d", m_iSockNumber);
		if(m_SockArray[i] != NULL)
		{
			TRACE("i = %d\n", i);
			closesocket(m_SockArray[i]);
			m_SockArray[i] = NULL;

			TRACE("Close socket server =  %d\n", m_iSockNumber);
		}
	}

	WSACleanup();	
	//memset(m_bConnected,FALSE,sizeof(m_bConnected));

	return ERR_SUCCESS;
}


int MEtherNet::initClientSocket()
{
	int iResult;
	WSADATA wSaData;

	if(WSAStartup(MAKEWORD(2,2), &wSaData) != 0)
		return ERR_WSA_START_UP;

	m_hClientSock = socket(PF_INET, SOCK_STREAM, 0);
	if(m_hClientSock == INVALID_SOCKET)
		return ERR_SOCKET;

	memset(&m_ServAddr, 0, sizeof(m_ServAddr));
	m_ServAddr.sin_family = AF_INET;
	m_ServAddr.sin_addr.s_addr = inet_addr(m_strMateIP[eSingleSessionMate]);
	m_ServAddr.sin_port=htons(m_iPort);

	iResult = connectClientSocket();
	if(iResult != ERR_SUCCESS) return iResult;

	m_hClinetEvent = WSACreateEvent();
	WSAEventSelect(m_hClientSock, m_hClinetEvent, FD_READ|FD_CLOSE);


	return ERR_SUCCESS;
}


int MEtherNet::startClient()
{

	m_pThread = AfxBeginThread(ThreadClient,this);
	m_bLiveThread = TRUE;
	
	return ERR_SUCCESS;
}

UINT MEtherNet::ThreadClient(LPVOID param)
{
	MEtherNet* pMain = ( MEtherNet* )param;
	WSANETWORKEVENTS netEvents;
	WSAEVENT dummyEvent;

	int nResult;
	BOOL bReceiveAll;
	char message[MAX_ETHERNET_BUFFER_SIZE];
	CString strBuf;

	unsigned long flags = 0;
	WSAOVERLAPPED overlapped;

	dummyEvent = WSACreateEvent();

	int iResultx = 0;

	pMain->initClientSocket();

	while(pMain->m_bLiveThread)
	{
		nResult = WSAWaitForMultipleEvents(1, &pMain->m_hClinetEvent, FALSE, 1000, FALSE);  
		if(nResult == WSA_WAIT_TIMEOUT || nResult == WSA_WAIT_FAILED) continue;

		nResult = WSAWaitForMultipleEvents(1, &pMain->m_hClinetEvent, TRUE, 0, FALSE);
		if(nResult == WSA_WAIT_TIMEOUT || nResult == WSA_WAIT_FAILED) continue;
		
		WSAEnumNetworkEvents(pMain->m_hClientSock, pMain->m_hClinetEvent, &netEvents);
		
		if(netEvents.lNetworkEvents & FD_READ) // 데이터 전송의 경우
		{
			if(netEvents.iErrorCode[FD_READ_BIT] != 0)
			{
				nResult = ERR_READ;
				break;
			}
			
			bReceiveAll = FALSE;
			flags = 0;
			memset(message,0, sizeof(message));
			memset(&overlapped, 0, sizeof(overlapped));
			pMain->m_dataBuf.len = MAX_ETHERNET_BUFFER_SIZE -1;
			pMain->m_dataBuf.buf = message;
			
			if(iResultx = WSARecv(pMain->m_hClientSock, &pMain->m_dataBuf, 1, &g_irecvBytes, &flags, &overlapped, CompletionRoutine)==SOCKET_ERROR)
			{
				nResult = ERR_READ;
				break;
			}
			
			nResult = WSAWaitForMultipleEvents(1, &dummyEvent, FALSE, WSA_INFINITE, TRUE);
			if(nResult != WAIT_IO_COMPLETION)
			{
				nResult = ERR_READ;
				break;				
			}
			
			if(g_irecvBytes > 0)
			{
				if(message[g_irecvBytes-1] == pMain->m_cEndChar)
				{
					message[g_irecvBytes-1] = 0x00;
					bReceiveAll = TRUE;

				}
				
				strBuf.Format("%s",message);
				pMain->m_strQue[eSingleSessionMate].Push(strBuf);
				
				if(bReceiveAll)
				{
					pMain->m_bReceived[eSingleSessionMate] = TRUE;
					sprintf_s(message, sizeof(message), "%s", pMain->m_strMateIP[eSingleSessionMate].GetBuffer());
					if(pMain->m_hNotifyHandle != NULL)
					{
						::PostMessage(pMain->m_hNotifyHandle, pMain->m_uiReceiveMessage, eSingleSessionMate, (LPARAM)(message));  // client id, LPARAM
					}
				}				
			}
			
		}
		
		if(netEvents.lNetworkEvents & FD_CLOSE)
		{
//			if(netEvents.iErrorCode[FD_CLOSE_BIT] != 0)
//			{
//				nResult = ERR_CLOSE;
//				//break;
//			}
			pMain->closeClientSocket();
			TRACE("Socket 종료 \n");
			
			sprintf_s(message, sizeof(message), "%s", pMain->m_strMateIP[eSingleSessionMate].GetBuffer());
			if(pMain->m_hNotifyHandle != NULL)
				::PostMessage(pMain->m_hNotifyHandle, pMain->m_uiCloseMessage, 1, (LPARAM)(message));  // client id, LPARAM
			
			
			pMain->initClientSocket();	// 다시 연결~~			
		}
		
		Sleep(1);
	}
	
	pMain->m_bLiveThread = FALSE;
	pMain->closeServerSockets();
	
	return 0;
}

int MEtherNet::connectClientSocket()
{
	int nResult;
	
	while(m_bLiveThread)
	{
		nResult = connect(m_hClientSock, (SOCKADDR*)&(m_ServAddr),sizeof(m_ServAddr));
		if(nResult != SOCKET_ERROR) break;
		Sleep(500);
	}

	m_bConnected[eSingleSessionMate] = TRUE;
	TRACE("Socket 연결 \n");
	
	char message[256];
	sprintf_s(message, sizeof(message), "%s", m_strMateIP[eSingleSessionMate].GetBuffer());
	if(m_hNotifyHandle != NULL)
		::PostMessage(m_hNotifyHandle, m_uiConnectMessage, 1, (LPARAM)(message));  // client id, LPARAM


	return ERR_SUCCESS;
}


int MEtherNet::closeClientSocket()
{
	if(m_hClientSock != NULL) 
	{
		WSACloseEvent(m_hClinetEvent);
		closesocket(m_hClientSock);
		m_hClientSock = NULL;
		WSACleanup();
		m_bConnected[eSingleSessionMate] = FALSE;		
	}
	return ERR_SUCCESS;	
}

int MEtherNet::SendData(CString str, CString strMateIP)
{
	
	::EnterCriticalSection(&m_Sync);
	if (!IsMateConnected(strMateIP))
	{
		::LeaveCriticalSection(&m_Sync);
		return ERR_NOT_CONNECTED;
	}
		

	int iResult = ERR_SUCCESS;
	SOCKET sock;

	if(m_eMode == eClientMode)
	{
		sock = m_hClientSock;
	}
	else
	{
		int isock = GetMateID(strMateIP);
		sock = m_SockArray[isock];
	}
	
	unsigned long flags = 0;
	WSAOVERLAPPED overlapped;

	memset(&overlapped, 0, sizeof(overlapped));
	WSAEVENT eVent = WSACreateEvent();
	overlapped.hEvent = eVent;

	//str += m_cEndChar;

	m_dataBuf.len = str.GetLength();
	m_dataBuf.buf = (PCHAR)(LPCTSTR)str;
				
	iResult = WSASend(sock, &m_dataBuf, 1, &g_irecvBytes, 0, &overlapped, CompletionRoutine);
	if(iResult == SOCKET_ERROR )
	{
		::LeaveCriticalSection(&m_Sync);
		return ERR_SENDED;
	}


	iResult = WSAWaitForMultipleEvents(1, &eVent, FALSE, WSA_INFINITE, TRUE);
	::LeaveCriticalSection(&m_Sync);
	if(iResult != WAIT_IO_COMPLETION)
		return ERR_SENDED;

	return iResult;
}

int MEtherNet::SendCharacter(char* pchar, int nLength, CString strMateIP)
{
	if(!IsMateConnected(strMateIP))
		return ERR_NOT_CONNECTED;

	int iResult = ERR_SUCCESS;
	SOCKET sock;

	if(m_eMode == eClientMode)
	{
		sock = m_hClientSock;
	}
	else
	{
		sock = m_SockArray[GetMateID(strMateIP)];
	}

	//일단 4byte Message길이 보냄. 
//	char cHead[4];
//	int2byte(nLength, cHead);
//
//	iResult = send(sock, cHead, 4, 0);
//	if(iResult == SOCKET_ERROR )
//		iResult = ERR_SENDED;
	

	char * pBuf = NULL;

	try
	{
		pBuf = new char[nLength+1];
		memcpy(pBuf,pchar,nLength);
		pBuf[nLength] = m_cEndChar;
			
		unsigned long flags = 0;
		WSAOVERLAPPED overlapped;
		
		memset(&overlapped, 0, sizeof(overlapped));
		WSAEVENT eVent = WSACreateEvent();
		overlapped.hEvent = eVent;
		
		m_dataBuf.len = nLength+1;
		m_dataBuf.buf = pBuf;
		
		iResult = WSASend(sock, &m_dataBuf, 1, &g_irecvBytes, 0, &overlapped, CompletionRoutine);
		
		if(iResult == SOCKET_ERROR ) throw ERR_SENDED;
		
		iResult = WSAWaitForMultipleEvents(1, &eVent, FALSE, WSA_INFINITE, TRUE);
		if(iResult != WAIT_IO_COMPLETION) throw ERR_SENDED;
	}
	catch(int iError)
	{
		delete [] pBuf;	
		return iError;
	}

//	iResult = send(sock, &m_cEndChar, 1, 0);
//	if(iResult == SOCKET_ERROR )
//		iResult = ERR_SENDED;
	delete [] pBuf;	
	return ERR_SUCCESS;

}

int MEtherNet::ReadData(CString& str, CString strMateIP)
{
	::EnterCriticalSection(&m_Sync);
	if (!IsMateConnected(strMateIP))
	{
		::LeaveCriticalSection(&m_Sync);
		return ERR_NOT_CONNECTED;
	}
		

	int nClntID = GetMateID(strMateIP);
	CString strBuf;

	str.Empty();
	
	for(;;)
	{
		if(m_strQue[nClntID].IsEmpty()) break;
		strBuf = m_strQue[nClntID].Pop();

		str += strBuf;
	}

	m_bReceived[nClntID] = FALSE;
	::LeaveCriticalSection(&m_Sync);
	return ERR_SUCCESS;
}

int MEtherNet::ReadData(WSABUF& Wsa, CString strMateIP)
{
	if (!IsMateConnected(strMateIP))
		return ERR_NOT_CONNECTED;

	int nClntID = GetMateID(strMateIP);
	WSABUF WsaBufr;
	
	//WsaBufr.len = 4096-1;

	for (;;)
	{
		if (m_WsaufQue[nClntID].IsEmpty()) break;
		WsaBufr = m_WsaufQue[nClntID].Pop();

	}

	m_bReceived[nClntID] = FALSE;

	return ERR_SUCCESS;
}
int MEtherNet::ReadDataServer(CString& str, CString strMateIP)
{
	if (!IsMateConnected(strMateIP))
		return ERR_NOT_CONNECTED;

	int nClntID = GetMateID(strMateIP);
	CString strBuf;

	str.Empty();

	
	//str = m_MyDataBuf[nClntID].buf;
	
	str = test;
	
	//test = "";


	//m_bReceived[nClntID] = FALSE;

	return ERR_SUCCESS;
}


BOOL  MEtherNet::IsMateConnected(CString strMateIP)
{
	
	int nClntID;

	nClntID = GetMateID(strMateIP);
	if (nClntID == eInvidClient)
	{
		return FALSE;
		
	}
		
	return m_bConnected[nClntID]; 
}

BOOL MEtherNet::IsMateMsgReceived(CString strMateIP)
{
	int nClntID;

	if(!IsMateConnected(strMateIP))
		return FALSE;

	nClntID = GetMateID(strMateIP);
	if(nClntID == eInvidClient)
		return FALSE;
	
	return m_bReceived[nClntID]; 
}

int MEtherNet::GetMateID(CString strMateIP)
{
	int nID = eInvidClient;

	if(m_eMode == eClientMode || strMateIP == "")
		return eSingleSessionMate;
	else
	{
		//for(int i=0; i<=m_iMaxClient; i++)
		for (int i = 0; i < m_iSockNumber; i++)
		{
			if(m_strMateIP[i] == strMateIP)
			{
				nID = i;
				break;
			}
		}
	}

	return nID;
}

int MEtherNet::GetMateIDStatic(CString strMateIP)
{
	int nID = eInvidClient;

	if (m_eMode == eClientMode || strMateIP == "")
		return eSingleSessionMate;
	else
	{
		for (int i = 0; i <= m_iMaxClient; i++)
		{
			if (m_strMateIPStatic[i] == strMateIP)
			{
				nID = i;
				break;
			}
		}
	}

	return nID;
}

void CALLBACK CompletionRoutine(DWORD error, DWORD szRecvBytes, LPWSAOVERLAPPED lpOverlapped, DWORD flags)
{
	g_irecvBytes = szRecvBytes;
}


int MEtherNet::InitializeCommunicationData()
{
	int iResult = ERR_SUCCESS;

	m_eMESServerMessage				= eMESIF_None;
	m_bFlag_ServerConnect			= FALSE;
	m_bFlag_ServerReceiveCNData		= FALSE;
	m_bFlag_ServerError				= FALSE;	
	m_bFlag_ServerTrayUnloading		= FALSE;
	m_bFlag_ServerMovingOrder		= FALSE;

	return iResult;
}


/************************************************************************/
/*       To. Server												    	*/
/************************************************************************/

int MEtherNet::ConnectServer()
{
	int iResult = ERR_SUCCESS;

	m_bFlag_ServerConnect = FALSE;

	CString strMsg;
	strMsg.Format(_T("%s%s"), eMESIF_Client_ConnectSocket, DELIMITER_CHARACTER);
	iResult = SendCharacter((PCHAR)(LPCTSTR)strMsg, strMsg.GetLength());
	return iResult;
}

int MEtherNet::SendCNData(CString strCN, BOOL bFirstData)
{
	int iResult = ERR_SUCCESS;

	m_bFlag_ServerReceiveCNData = FALSE;

	CString strMsg;

	// JB^CN0000001^
	//strMsg.Format(_T("%s%s%s%s"), eMESIF_Client_SendCNData, DELIMITER_CHARACTER, strCN, DELIMITER_CHARACTER);
	strMsg.Format("%s%c%s%c", NAME_MESIF_PROTOCOL[eMESIF_Client_SendCNData], DELIMITER_CHARACTER, strCN, DELIMITER_CHARACTER);

	if (bFirstData)
	{
		// JB^CN0000001^FST^
		CString strtmp;
		//strtmp.Format(_T("%s%s"), eMESIF_Client_SendCNData_1st_Tail, DELIMITER_CHARACTER);
		strtmp.Format("%s%s", NAME_MESIF_PROTOCOL[eMESIF_Client_SendCNData_1st_Tail], DELIMITER_CHARACTER);
		strMsg += strtmp;
	}

	iResult = SendCharacter((PCHAR)(LPCTSTR)strMsg, strMsg.GetLength());
	return iResult;
}

int MEtherNet::MachineEStop()
{
	int iResult = ERR_SUCCESS;

	CString strMsg;
	strMsg.Format(_T("%s%s"), eMESIF_Client_MachineEStop, DELIMITER_CHARACTER);
	iResult = SendCharacter((PCHAR)(LPCTSTR)strMsg, strMsg.GetLength());
	return iResult;
}


/************************************************************************/
/*       From. Server												    */
/************************************************************************/

int MEtherNet::HandlingServerMessage(CString strServerMsg)
{
	int iResult = ERR_SUCCESS;

	int i = 0; 
	// find Server command Type

	m_eMESServerMessage = eMESIF_None;

	for (i = 0; i < eMESIFItem_Max; i++)
	{
		int iSearch = -1;
		iSearch = strServerMsg.Find(_T(NAME_MESIF_PROTOCOL[(EMESIF_ITEM)i]));
		if (iSearch != -1)
		{
			m_eMESServerMessage = (EMESIF_ITEM)i;
			break;
		}
	}

	switch (m_eMESServerMessage)
	{
	case eMESIF_Server_InitSocket:
		// Init client Socket
		iResult = InitializeClientSocket();
		break;

	case eMESIF_Server_SuccessConnecting:
		iResult = SetServerConnectingCompete();
		break;

	case eMESIF_Server_ReceiveCNData:
		iResult = SetServerReceiveCNData();
		break;

	case eMESIF_Server_MESError:
		m_bFlag_ServerError = TRUE;
		break;

	case eMESIF_Server_TrayUnloading:
		m_bFlag_ServerTrayUnloading = TRUE;
		break;

	case eMESIF_Server_MovingOrder:
		m_bFlag_ServerMovingOrder = TRUE;
		break;

	case eMESIF_None:
		// eMESIF_Client_ConnectSocket,		// Connecing Server
		// eMESIF_Client_SendCNData,			// CN 스캔 정보 전송
		// eMESIF_Client_SendCNData_1st_Tail,		// 첫번째거는 알려줘야한다.
		// eMESIF_Client_MachineEStop,			// 설비측 비상 정지
		break;
	default:
		break;
	}

	return iResult;
}

int MEtherNet::InitializeClientSocket()
{
	int iResult = ERR_SUCCESS;

	return iResult;
}

int MEtherNet::SetServerConnectingCompete()
{
	int iResult = ERR_SUCCESS;
	m_bFlag_ServerConnect = TRUE;
	return iResult;
}

BOOL MEtherNet::IsServerConnectingComplete()
{
	return m_bFlag_ServerConnect;
}

int MEtherNet::SetServerReceiveCNData()
{
	int iResult = ERR_SUCCESS;
	m_bFlag_ServerReceiveCNData = TRUE;
	return iResult;
}

BOOL MEtherNet::IsServerReceiveCNData()
{
	return m_bFlag_ServerReceiveCNData;
}



int MEtherNet::fileRecevie(CString cstrPath, CString strMateIP)
{
	if (!IsMateConnected(strMateIP))
		return ERR_NOT_CONNECTED;

	int iResult = ERR_SUCCESS;
	SOCKET sock;

	if (m_eMode == eClientMode)
	{
		sock = m_hClientSock;
	}
	else
	{
		sock = m_SockArray[GetMateID(strMateIP)];
	}


	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (m_eStepRecevie[i] != ERECEVIE_NONE)
			return ERR_CLIENT_IS_NOT_READY;
	}

	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (m_eStepSend[i] != ESEND_NONE)
			return ERR_CLIENT_IS_NOT_READY;
	}

	//m_SRecevieFile[GetMateIDStatic(strMateIP)-1].cstrFilePath = cstrPath;
	SendData("getpic\n", strMateIP);
	
	/*CMyProgressWnd ProgWnd(NULL, _T("Recevie file"));
	ProgWnd.SetRange(0, 1000);
	MTickTimer m_timeprocess;
	m_timeprocess.StartTimer();
	while ((g_irecvBytes==1024)|| m_timeprocess.LessThan(0.2))
	{
		ProgWnd.StepIt();
		ProgWnd.SetText(_T("Recevie file is Running"));
	}
	ProgWnd.StepIt();
	TRACE(_T("Finish"));*/
	return 1;
}

int MEtherNet::fileRecevie(CString strMateIP)
{
	if (!IsMateConnected(strMateIP))
		return ERR_NOT_CONNECTED;

	int iResultE = ERR_SUCCESS;
	SOCKET sock;

	if (m_eMode == eClientMode)
	{
		sock = m_hClientSock;
	}
	else
	{
		sock = m_SockArray[GetMateID(strMateIP)];
	}

	SendData("getpic\n", strMateIP);
	return 1;
	return iResultE;
}



bool MEtherNet::readfile(WSABUF wsaTmp, FILE *f)
{
	return true;
}



void MEtherNet::RecevieFileLoop(int iSocket)
{	
	if (iSocket == 0)
		return;
	int iRecevie;
	iRecevie = iSocket-1;
	switch (m_eStepRecevie[iRecevie])
	{
	case ERECEVIE_NONE:
		
		break;
	case ERECEVIE_INIT:
	{

		m_SRecevieFile[iRecevie].cstrFileInfor.Format("%s", m_dataBufRev.buf);
		m_SRecevieFile[iRecevie].cstrFileInfor.Delete(0, 1);


		AfxExtractSubString(m_SRecevieFile[iRecevie].cstrDeviceName, m_SRecevieFile[iRecevie].cstrFileInfor, 1, '_');
		AfxExtractSubString(m_SRecevieFile[iRecevie].cstrDeviceStep, m_SRecevieFile[iRecevie].cstrFileInfor, 2, '_');
		

		m_eStepRecevie[iRecevie] = ERECEVIE_NONE;

		//m_SRecevieFile[iRecevie].iBegin = 0;
		
		//SendData("begin\n", m_strMateIPStatic[iRecevie + 1]);
		//ManagerSocket pSocket;
		//pSocket.tTakepicture1.StartTimer();

		//m_SRecevieFile[iRecevie].m_iEEthernetMode = eEthernetSendFile;
	}
		break;
// 	case ERECEVIE_RUN:
// 		//g_irecvBytes = cstrDataBufRev.GetLength();
// 		if (m_timeProcessRecevieFile[iRecevie].MoreThan(8))
// 		{
// 			m_eStepRecevie[iRecevie] = ERECEVIE_NONE;
// 			fclose(m_SRecevieFile[iRecevie].fw);
// 			::PostMessage(m_hNotifyHandle, m_uiReceiveMessageFile, iRecevie, (LPARAM)(3));  //if receive file Ng
// 			m_SRecevieFile[iRecevie].m_iEEthernetMode = eEthernetSendMess;
// 			break;
// 		}
// 		m_SRecevieFile[iRecevie].iBegin = m_SRecevieFile[iRecevie].iBegin + g_irecvBytes;		
// 		if(g_irecvBytes>=1024)
// 		{
// 
// 			fwrite(m_dataBufRev.buf, 1024, 1, m_SRecevieFile[iRecevie].fw);
// 			//SendData("OK", m_strMateIPStatic[iRecevie + 1]);
// 		}
// 		else 
// 		{
// 			//finish receive file
// 
// 			m_dataBufRev.buf[g_irecvBytes] = '\0';
// 			fwrite(m_dataBufRev.buf, g_irecvBytes, 1, m_SRecevieFile[iRecevie].fw);
// 			//MyMessageBox("Successful Receive " + m_SRecevieFile[iRecevie].cstrFileName, "MSG", MB_ICONINFORMATION, "Yes");
// 			//SendData("abc\n", m_strMateIPStatic[iRecevie + 1]);
// 		}
// 		if (m_SRecevieFile[iRecevie].iBegin == atoi(m_SRecevieFile[iRecevie].cstrFIleSize))
// 		{
// 					
// 			fclose(m_SRecevieFile[iRecevie].fw);
// 			//Sleep(100);
// 			//strFileName = m_SRecevieFile[iRecevie].cstrFilePath;
// 			SendData("finish\n", m_strMateIPStatic[iRecevie + 1]);
// 			::PostMessage(m_hNotifyHandle, m_uiReceiveMessageFile, iRecevie, (LPARAM)(2));   //if receive file ok
// 			m_SRecevieFile[iRecevie].m_iEEthernetMode = eEthernetSendMess;
// 			m_SRecevieFile[iRecevie].cstrFileInfor = "\n";
// 			m_eStepRecevie[iRecevie] = ERECEVIE_NONE;
// 		}
// 			
// 		break;
	case ERECEVIE_FINISH:
			
		break;

	case ERECEVIE_START:
		break;
	case ERECEVIE_NEXT_STEP:
		break;

	}
}


int MEtherNet::fileSend(const char *fpath, CString strMateIP,int iType )
{

	// Extract only filename from given path.
	//EnterCriticalSection(&m_Sync);
	if (m_bLock == 1)
	{
		//LeaveCriticalSection(&m_Sync);
		return 3;
	}
		
	m_bLock = 1;
	if (!IsMateConnected(strMateIP))
	{
		//LeaveCriticalSection(&m_Sync);
		m_bLock = 0;
		//LeaveCriticalSection(&m_Sync);
		return ERR_NOT_CONNECTED;
	}

	MTickTimer m_timeprocess;		

	int iResult = ERR_SUCCESS;
	SOCKET sock;

	if (m_eMode == eClientMode)
	{
		sock = m_hClientSock;
	}
	else
	{
		sock = m_SockArray[GetMateID(strMateIP)];
	}


	if (GetMateID(strMateIP) == 0)
	{
		m_bLock = 0;
		//LeaveCriticalSection(&m_Sync);
		return 3;
	}
		
	char filename[50];
	int i = strlen(fpath);
	for (; i>0; i--)if (fpath[i - 1] == '\\')break;
	for (int j = 0; i <= (int)strlen(fpath); i++)filename[j++] = fpath[i];
	/////////////////////////////////////////////////////////////////////

	ifstream myFile(fpath, ios::in | ios::binary | ios::ate);
	int size = (int)myFile.tellg();
	myFile.close();

	char filesize[10]; itoa(size, filesize, 10);


	CString cstrTmp;
	if (iType == 0)
	{
		cstrTmp = ">@" + (CString)"Setting.xml" + "_" + (CString)filesize + "\n";
	}
	else if (iType == 1 )
	{
		cstrTmp = ">@Pattern.jpg_" + (CString)filesize + "\n";
	}

	SendData(cstrTmp, strMateIP);

	m_timeprocess.StartTimer();
	while (m_timeprocess.LessThan(0.7))
	{

	}


	FILE *fr = fopen(fpath, "rb");

	char *temp = new char[size];

	fread(temp, size, 1, fr);

	send(sock, temp, size, 0);

	fclose(fr);
	delete[] temp;

	m_timeprocess.StartTimer();
	while (m_timeprocess.LessThan(2.5))
	{
	
	}

	

	m_bLock = 0;
	//LeaveCriticalSection(&m_Sync);
	return 1;
}

int MEtherNet::fileSend2(const char *fpath, CString strMateIP, int iType)
{

	// Extract only filename from given path.
	//EnterCriticalSection(&m_Sync);
	if (!IsMateConnected(strMateIP))
	{
		return ERR_NOT_CONNECTED;
	}

	//MTickTimer m_timeprocess;

	int iResult = ERR_SUCCESS;
	SOCKET sock;

	if (m_eMode == eClientMode)
	{
		sock = m_hClientSock;
	}
	else
	{
		sock = m_SockArray[GetMateID(strMateIP)];
	}


	if (GetMateID(strMateIP) == 0)
	{
		//m_bLock = 0;
		//LeaveCriticalSection(&m_Sync);
		return 3;
	}

	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (m_eStepRecevie[i] != ERECEVIE_NONE)
			return ERR_CLIENT_IS_NOT_READY;
	}

	for (int i = 0; i < MAX_CLIENT; i++)
	{
		if (m_eStepSend[i] != ESEND_NONE)
			return ERR_CLIENT_IS_NOT_READY;
	}

	char filename[50];
	int i = strlen(fpath);
	for (; i>0; i--)if (fpath[i - 1] == '\\')break;
	for (int j = 0; i <= (int)strlen(fpath); i++)filename[j++] = fpath[i];
	/////////////////////////////////////////////////////////////////////

	ifstream myFile(fpath, ios::in | ios::binary | ios::ate);
	int size = (int)myFile.tellg();
	myFile.close();

	char filesize[10]; itoa(size, filesize, 10);


	CString cstrTmp;
	if (iType == 0)
	{
		//cstrTmp = ">@" + (CString)"Setting.xml" + "_" + (CString)filesize + "\n";
		cstrTmp = "@" + (CString)"Setting.xml" + "_" + (CString)filesize + "\n";
	}
	else if (iType == 1)
	{
		//cstrTmp = ">@Pattern.jpg_" + (CString)filesize + "\n";
		cstrTmp = "@Pattern.jpg_" + (CString)filesize + "\n";
	}

	//SendData(cstrTmp, strMateIP);
	m_SSendFile[GetMateIDStatic(strMateIP) - 1].cstrFilePath = fpath;

	m_SSendFile[GetMateIDStatic(strMateIP) - 1].iSizeFileSend = size;
	m_SSendFile[GetMateIDStatic(strMateIP) - 1].cstrFileInfor = cstrTmp;
	m_eStepSend[GetMateIDStatic(strMateIP) - 1] = ESEND_INIT;

	return 1;
}


void MEtherNet::SendFileLoop(int iUnit)
{
	/*char buffer[1030];*/
	
	//int iSendfile;
	//iSendfile = iUnit;
	
	switch (m_eStepSend[iUnit])
	{
	case ESEND_NONE:
		break;
	case ESEND_INIT:
	{
		CString cstrTmp = "";
		ReadDataAll(cstrTmp, iUnit);
		SendData(m_SSendFile[iUnit].cstrFileInfor, m_strMateIPStatic[iUnit + 1]);
		m_SSendFile[iUnit].fr = fopen(m_SSendFile[iUnit].cstrFilePath, "rb");
		//FILE *fr = fopen(fpath, "rb");
		m_timeProcessSendFile[iUnit].StartTimer();

		m_eStepSend[iUnit] = ESEND_SENDFILESIZE;
		break;
	}
	case ESEND_SENDFILESIZE:
	{
		if (m_timeProcessSendFile[iUnit].LessThan(0.3))
			break;
		if (m_timeProcessSendFile[iUnit].MoreThan(5))
		{
			SendData("timeout\n", m_strMateIPStatic[iUnit + 1]);
			m_eStepSend[iUnit] = ESEND_NONE;
			break;
		}

		if (!IsSendedAll(iUnit))
			break;

		CString cstrTmp = "";
		ReadDataAll(cstrTmp, iUnit);
		if (cstrTmp.Find("@") != -1)
		{
			m_eStepSend[iUnit] = ESEND_STARTSEND;
		}
		else
		{
			m_eStepSend[iUnit] = ESEND_NONE;
		}
		m_timeProcessSendFile[iUnit].StartTimer();

		break;
	}
		
	case ESEND_STARTSEND:
		//Ver1
		if (m_timeProcessSendFile[iUnit].LessThan(0.2))
			break;

		char *temp;
		temp = new char[m_SSendFile[iUnit].iSizeFileSend];

		fread(temp, m_SSendFile[iUnit].iSizeFileSend, 1, m_SSendFile[iUnit].fr);

		//SendData(temp, m_strMateIPStatic[iSendfile + 1]);
		send(m_SockArray[GetMateID(m_strMateIPStatic[iUnit + 1])], temp, m_SSendFile[iUnit].iSizeFileSend, 0);

		fclose(m_SSendFile[iUnit].fr);
		delete[] temp;
		m_eStepSend[iUnit] = ESEND_FINISH;
		m_timeProcessSendFile[iUnit].StartTimer();

		break;

		//Ver2

		//if (m_SSendFile[iSendfile].iSizeFileSend <= 0)
		//{
		//	fclose(m_SSendFile[iSendfile].fr);
		//	m_timeProcessSendFile[iSendfile].StartTimer();
		//	m_eStepSend[iSendfile] = ESEND_FINISH;
		//	break;
		//}

		//if (m_SSendFile[iSendfile].iSizeFileSend >= 1024)
		//{
		//	fread(buffer, 1024, 1, m_SSendFile[iSendfile].fr);
		//	//send(m_SockArray[GetMateID(m_strMateIP[iSendfile + 1])], buffer, 1024, 0);
		//	SendData(buffer, m_strMateIPStatic[iSendfile + 1]);
		//}
		//else
		//{
		//	fread(buffer, m_SSendFile[iSendfile].iSizeFileSend, 1, m_SSendFile[iSendfile].fr); //finish
		//	buffer[m_SSendFile[iSendfile].iSizeFileSend] = '\0';
		//	SendData(buffer, m_strMateIPStatic[iSendfile + 1]);

		//}

		//m_SSendFile[iSendfile].iSizeFileSend -= 1024;

		//break;
	case ESEND_FINISH:
	{
		if (m_timeProcessSendFile[iUnit].LessThan(0.5))
			break;
		if (m_timeProcessSendFile[iUnit].MoreThan(5))
		{
			m_eStepSend[iUnit] = ESEND_NONE;
			SendData("timeout\n", m_strMateIPStatic[iUnit + 1]);
			break;
		}
		if (!IsSendedAll(iUnit))
			break;

		CString cstrTmp = "";
		ReadDataAll(cstrTmp, iUnit);
		if (cstrTmp.Find("#_result_get_file") != -1)
		{
			m_eStepSend[iUnit] = ESEND_NONE;
		}
		else
		{
			m_eStepSend[iUnit] = ESEND_NONE;
		}

		m_eStepSend[iUnit] = ESEND_NONE;
		break;
	}
	case ESEND_NEXT_STEP:
		break;
	case ESEND_RUN:
		break;
	}
}


int MEtherNet::convertArraySocktoIp(int iSockarray)
{

	return 1;
}

CString MEtherNet::GetIp(const char *cstrMsg)
{
	CString cstrInfor = "";
	cstrInfor.Format("%s",cstrMsg);
	CString cstrIp;
	cstrInfor.Delete(0, 1);
	AfxExtractSubString(cstrIp, cstrInfor, 1, '_');
	return cstrIp;
}


int MEtherNet::recvData(char *recvbuf, int size, CString strMateIP)
{
	if (!IsMateConnected(strMateIP))
		return ERR_NOT_CONNECTED;

	int iResult = ERR_SUCCESS;
	SOCKET sock;

	if (m_eMode == eClientMode)
	{
		sock = m_hClientSock;
	}
	else
	{
		int isock = GetMateID(strMateIP);
		sock = m_SockArray[isock];
	}
	
	int sz = recv(sock, recvbuf, size, 0);
	if(sz>=0) recvbuf[sz] = '\0';
	return sz;
}

int MEtherNet::sendData(char *sendbuf, CString strMateIP)
{
	if (!IsMateConnected(strMateIP))
		return ERR_NOT_CONNECTED;

	int iResult = ERR_SUCCESS;
	SOCKET sock;

	if (m_eMode == eClientMode)
	{
		sock = m_hClientSock;
	}
	else
	{
		int isock = GetMateID(strMateIP);
		sock = m_SockArray[isock];
	}
	return send(sock, sendbuf, strlen(sendbuf), 0);
}



void MEtherNet::RequestUnitbox2(int iUnit)
{
	::EnterCriticalSection(&m_Sync);
	SendData("run_vision\n", m_strMateIPStatic[iUnit+1]);
	::LeaveCriticalSection(&m_Sync);
}

void MEtherNet::RequesStartRunVisionUnitbox2(int iUnit)
{
	::EnterCriticalSection(&m_Sync);
	SendData("start_vision\n", m_strMateIPStatic[iUnit + 1]);
	::LeaveCriticalSection(&m_Sync);
}

void MEtherNet::RequesFocus(int iUnit)
{
	::EnterCriticalSection(&m_Sync);
	SendData("focus\n", m_strMateIPStatic[iUnit + 1]);
	::LeaveCriticalSection(&m_Sync);
}

BOOL MEtherNet::IsAllConnected()
{
	BOOL m_bResult = TRUE;

	for (int i = 0; i < MAX_CLIENT; i++)
	{
		m_bResult = m_bResult && IsMateConnected(m_strMateIPStatic[i +1]);
	}

	return m_bResult;
}

BOOL MEtherNet::IsSended(int iUnit)
{
	BOOL m_bResult = TRUE;

	//m_bResult = m_SRecevieFile[iUnit].m_iRecevieOK;
	
	return m_bResult;
}

BOOL MEtherNet::IsSendedAll(int iUnit)
{
	BOOL m_bResult = TRUE;

	//m_bResult = m_SRecevieFile[iUnit ].m_iRecevieAll;

	return m_bResult;
}

int MEtherNet::ReadDataAll(CString& str, int iUnit)
{
	//EnterCriticalSection(&m_Sync);

	int iTmp = 0;
	iTmp = GetMateID(m_strMateIPStatic[iUnit + 1]);

	if (!m_bConnected[iTmp])
	{
		//LeaveCriticalSection(&m_Sync);
		return ERR_NOT_CONNECTED;
	}

	CString strBuf;

	str.Empty();
// 	str = m_SRecevieFile[iUnit].cstrFileDataReceiveAll;
// 	m_SRecevieFile[iUnit].cstrFileDataReceiveAll = "";
// 
// 	m_SRecevieFile[iUnit].m_iRecevieAll = FALSE;

	//LeaveCriticalSection(&m_Sync);
	return ERR_SUCCESS;
}


int MEtherNet::ReadData(CString& str,int iUnit)
{
	EnterCriticalSection(&m_Sync);

	/*if(!IsSended(iUnit))
		return ERR_NOT_CONNECTED;*/
	
	int iTmp = 0;
	iTmp = GetMateID(m_strMateIPStatic[iUnit + 1]);

	if (!m_bConnected[iTmp])
	{
		LeaveCriticalSection(&m_Sync);
		return ERR_NOT_CONNECTED;
	}
		
	CString strBuf;

	str.Empty();
// 	str = m_SRecevieFile[iUnit ].cstrFileDataReceive;
// 	m_SRecevieFile[iUnit  ].cstrFileDataReceive = "";
// 
// 	m_SRecevieFile[iUnit ].m_iRecevieOK = FALSE;

	LeaveCriticalSection(&m_Sync);
	return ERR_SUCCESS;
}


void MEtherNet::AddLog(CString& str,int iUnit)
{
	//EnterCriticalSection(&m_Sync);
	if (m_bLockShowLog == TRUE)
		return;
// 	CMainFrame* pFrm;
// 	if (AfxGetApp()->GetMainWnd() != NULL)
// 	{
// 		pFrm = (CMainFrame*)(AfxGetApp()->GetMainWnd());
// 		if (pFrm == NULL)
// 			return;
// 		CString cstrUnit;
// 		CString cstrLine;
// 		cstrUnit.Format("UNIT%d_%d ", iUnit % 5, iUnit / 5);
// 		pFrm->m_pTeachMainForm->m_strQue.Push(cstrUnit + str);
// 	}
	::PostMessage(m_hNotifyHandle, m_uiReceiveMessageFile, NULL, (LPARAM)(4));  //AddLog
	//LeaveCriticalSection(&m_Sync);
}

UINT MEtherNet::ThreadSendFileSerVer(LPVOID param)
{

	MEtherNet* pMain = (MEtherNet*)param;
	pMain->ThreadModeSendFile();

	return 1;
}

void MEtherNet::ThreadModeSendFile()
{
	while (m_bThreadSendfile)
	{
		for (int i = 0; i < MAX_CLIENT; i++)
		{
			SendFileLoop(i);
		}
		Sleep(100);
	}
	m_bThreadSendfile = FALSE;
}

int MEtherNet::startServerSendFile()
{
	if (m_bThreadSendfile == FALSE)
	{
		AfxBeginThread(ThreadSendFileSerVer, this);
		m_bThreadSendfile = TRUE;
	}
	
	return ERR_SUCCESS;
}

void MEtherNet::ThreadModeSendFileStop()
{
	if (m_bThreadSendfile == TRUE)
		m_bThreadSendfile = FALSE;
	Sleep(100);
}
