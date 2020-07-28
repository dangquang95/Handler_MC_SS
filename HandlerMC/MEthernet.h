// MEtherNet_AF.h: interface for the MEtherNet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_METHERNET_H__AE44A0F4_D563_44DE_B6F0_3220EB3E657D__INCLUDED_)
#define AFX_METHERNET_H__AE44A0F4_D563_44DE_B6F0_3220EB3E657D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// inet_ntoa, inet_addr 함수 사용시 경고 발생으로 Disable 시킴
#pragma warning (disable:4996)


#include <WINSOCK2.H>
#include "safequeue.h"
#include "DefSystem.h"
#include "MTickTimer.h"

//Huy
#include <stdio.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "MIEthernet.h"
#include "stdafx.h"








using namespace std;

#define MAX_ETHERNET_BUFFER_SIZE		8192
#define MAX_CLIENT			4
#define END_CHARACTER		0x03
#define DELIMITER_CHARACTER	'^'

#ifndef ERR_SUCCESS
#define ERR_SUCCESS	0
#endif

// Read Que
#pragma comment (lib, "ws2_32")

//
enum ERECEVIE_STEP
{
	ERECEVIE_NONE = 0,
	ERECEVIE_INIT = 1,
	ERECEVIE_START,
	ERECEVIE_NEXT_STEP,
	ERECEVIE_FINISH,
	ERECEVIE_RUN,
};

enum ESEND_STEP
{
	ESEND_NONE = 0,
	ESEND_INIT = 1,
	ESEND_SENDFILESIZE,
	ESEND_STARTSEND,
	ESEND_FINISH,
	ESEND_START,
	ESEND_NEXT_STEP,
	ESEND_RUN,
};

enum EETHERNETMODE
{
	eEthernetSendFile = 0,
	eEthernetSendMess
};

/**
 * Ethernet 통신을 위한 Class 로서 Server 모드와 Client 모드 공용으로 사용할수 있다.
 * Server모드로 실행시 Default는 1개의 Client와 통신되며, 최대 63개까지 접속이 가능하다.
 * 단, Cleint를 등록할때는 	int AddClient(CString strClientIP)를 호출한다.
 * 
 * 비동기 Notification방식으로 Server를 구현함. 
 *
 * @author 최광혁 (zery.choi@samsung.com)
 */
typedef struct tagSSendFile
{
	CString cstrFileName;
	CString cstrFIleSize;

	CString cstrFileInfor;
	CString cstrFilePath;
	int iSizeFileSend;
	char *temp;
	FILE *fr;
} SSendFile;

typedef struct tagSRecevieFile
{
	CString cstrDeviceName;
	CString cstrDeviceStep;
	

	CString cstrFileInfor;
	
	FILE *fw;
	EETHERNETMODE m_iEEthernetMode;
} SRecevieFile;


class MEtherNet :public IMEthernet
{
public:
	enum eClient
	{
		eInvidClient =-1,
		eSingleSessionMate = 1,				

		eClientMax = WSA_MAXIMUM_WAIT_EVENTS-1
	};

	
	enum eMode
	{
		eServerMode,
		eClientMode
	};

	enum eError
	{
		//ERR_SUCCESS,
		ERR_NOT_SUPPORTED = 1,
		ERR_WSA_START_UP,
		ERR_CREATE_MUTEX,
		ERR_SOCKET,
		ERR_BIND,
		ERR_LISTEN,
		ERR_ACCEPT,
		ERR_WSAEVENT_SELECT,
		ERR_READ,
		ERR_CLOSE,
		ERR_CONNECT,
		ERR_NOT_CONNECTED,
		ERR_SENDED,
		ERR_CLIENT_NO_OVER,
		ERR_CLIENT_IS_NOT_READY,
		ERR_NOT_RECEVIED,
	};

	/** 생성자 
	  * @param mode : eServerMode, eClientMode
	  * @param iPort : 사용할 Port번호
	  * @param strMateIP : 짝이 되는 IP No (ClientMode시에는 Server의 IP, ServerMode시에는 첫번째 Client가 될 IP)
	  * @param hNotify : 메시지르 Notify할  Window Handle 
	  */	
	MEtherNet(eMode mode, int iPort, CString strMateIP, HWND hNotify = NULL);
	
	/** 소멸자*/
	virtual ~MEtherNet();

	/** 통신을 시작한다. 생성한 후 반드시 호출해야 통신이 시작된다.
	  * Client모드일 경우에는 1초를 주기로 계속 Connect를 시도함.
	  */
	int Initialize();	

	/** Data를 Send한다.
	  * @param str : 보낼 Date
	  * @param strMateIP : 보낼 IP주소 (Default의 경우, ClientMode시에는 Server의 IP, ServerMode시에는 첫번째 Client가 될 IP)
	  * @return : 성공 - 0, 실패 - ERR_NOT_CONNECTED
	  */
	virtual int SendData(CString str, CString strMateIP = _T(""));

	/** Data를 Send한다.
	  * @param str : 보낼 Date
	  * @param strMateIP : 보낼 IP주소 (Default의 경우, ClientMode시에는 Server의 IP, ServerMode시에는 첫번째 Client가 될 IP)
	  * @return : 성공 - 0, 실패 - ERR_NOT_CONNECTED
	  */
	virtual int SendCharacter(char* pChar, int nLength, CString strMateIP = "");

	/** Data를 Read한다.
	  * @param str : 읽으려는 Data
	  * @param strMateIP : 받을 IP주소 (Default의 경우, ClientMode시에는 Server의 IP, ServerMode시에는 첫번째 Client가 될 IP)
	  * @return : 성공 - 0, 실패 - ERR_NOT_CONNECTED
	  */
	virtual int ReadData(CString& str, CString strMateIP = "");
	int ReadData(WSABUF & Wsa, CString strMateIP);
	int ReadDataServer(CString& str, CString strMateIP = "");
	
	/** 상대방이 접속되어 있는지 체크한다..
	  * @param strMateIP : 상대방 IP주소 (Default의 경우, ClientMode시에는 Server의 IP, ServerMode시에는 첫번째 Client가 될 IP)
	  * @return : TRUE , FALSE
	  */
	virtual BOOL IsMateConnected(CString strMateIP = "") ;

	/** Client를 추가한다. 단, 최대 63개까지만 추가 가능하다.
	  * @param strClientIP : 상대방 IP주소 (ClientMode시에는 지원하지 않는다.)
	  * @return : 성공 - 0, 실패 - ERR_CLIENT_NO_OVER
	  */
	virtual int AddClient(CString strClientIP);

	/** 상대방에서 메시지가 도착했는지 체크한다..
	  * @param strMateIP : 상대방 IP주소 (Default의 경우, ClientMode시에는 Server의 IP, ServerMode시에는 첫번째 Client가 될 IP)
	  * @return : TRUE , FALSE
	  */
	virtual BOOL IsMateMsgReceived(CString strMateIP = "") ;


	/** 상위로 보낼 메시지를 정의한다.
	  * Connecting, Receive, Close에 대해서 정의하면 됨.
	  */
	virtual void Define_ConnectMsg(int nMessageID) {m_uiConnectMessage = nMessageID;};
	virtual void Define_ReceiveMsg(int nMessageID){m_uiReceiveMessage = nMessageID;};
	virtual void Define_ReceiveMsgFile(int nMessageID) { m_uiReceiveMessageFile = nMessageID; };
	virtual void Define_CloseMsg(int nMessageID){m_uiCloseMessage = nMessageID;};

	/** 메시지전송의 끝을 가르키는 END CHARACTER를 정의한다.
	  * @param cEnd : END Character (default : 0x03)
	  */
	void Define_EndCharacter(char cEnd){m_cEndChar = cEnd;};

	int GetMaxClient() { return m_iMaxClient; };
	int GetPortIP() { return m_iPort; };
	eMode GetMode() { return m_eMode; };

	/** 상위로 보낼 메시지의 윈도 Handle을 Get/Set한다.	  */
	void SetNotifyHandle(HWND hWnd) {m_hNotifyHandle = hWnd;};
	HWND GetNotifyHandle() {return m_hNotifyHandle;};

	/** 상대방의 IP주소로 Client ID를 찾는다. (접속순서대로 1,2..)
	  * @param strMateIP : 상대 IP주소
	  * @return : ID
	  */
	int GetMateID(CString strMateIP);

	int GetMateIDStatic(CString strMateIP);

public:
//protected:
	CRITICAL_SECTION	m_Sync;

	CWinThread* m_pThread;						//Thread Handle
	HWND	m_hNotifyHandle;					//Notify Window Handle
	BOOL m_bLiveThread;							//Thread Live Flag
	eMode m_eMode;
	BOOL m_bConnected[WSA_MAXIMUM_WAIT_EVENTS];		//접속 여부 Array
	BOOL m_bIsConnected[WSA_MAXIMUM_WAIT_EVENTS];		//접속 여부 Array
	CString m_strMateIP[WSA_MAXIMUM_WAIT_EVENTS];	//상대 IP 주소 Array
	CString m_strMateIPStatic[WSA_MAXIMUM_WAIT_EVENTS];
	CString cstrDataBufRev;
	int		m_iPort;
	int		m_iMaxClient;

	UINT m_uiReceiveMessageFile;
	UINT m_uiConnectMessage;
	UINT m_uiReceiveMessage;
	UINT m_uiCloseMessage;

	// Read Queue
	CString				m_strBuf;
	
	SafeQueue<CString> m_strQue[WSA_MAXIMUM_WAIT_EVENTS];
	
	BOOL				m_bReceived[WSA_MAXIMUM_WAIT_EVENTS];
	char	m_cEndChar;

	char test[MAX_ETHERNET_BUFFER_SIZE];

public:
	//int fileSend(const char *fpath, CString strMateIP);
	int fileRecevie(CString cstrPath, CString strMateIP);

	int fileRecevie(CString strMateIP);

public:
//protected:
	
	//--- Server 용  ----------------------------------//

	/** Socket 초기화*/
	int initServerSocket();
	
	/** Server로 통신을 시작한다. */
	int startServer();
	
	/** Socket을 닫는다 */
	int closeServerSockets();

	/** Client의 Accept, Receive, Close를 감시한다. */
	static UINT ThreadServer(LPVOID param);
	static UINT ThreadSendFileSerVer(LPVOID param);
	void ThreadModeSendFile();
	virtual int startServerSendFile();
	virtual void ThreadModeSendFileStop();

	
	
	BOOL m_bThreadSendfile;
	
	
	BOOL m_bLiveThreadReceie;
//	static UINT ThreadRecevieSerVer(LPVOID param);

	

	void StopThreadServerSockets();

	SOCKET m_SockArray[WSA_MAXIMUM_WAIT_EVENTS];			//첫번째 : Server Socket, 그외 : Client Socket
	SOCKET m_SockArrayTemp[WSA_MAXIMUM_WAIT_EVENTS];			//첫번째 : Server Socket, 그외 : Client Socket
	WSAEVENT m_EventArray[WSA_MAXIMUM_WAIT_EVENTS];			//첫번째 : Server Event, 그외 : Client Event
	int m_iSockNumber;//=0;										//현재 접속되어 있는 전체 소켓
	WSABUF	m_dataBuf;
	WSABUF  m_dataBufRev;
	WSABUF	m_MyDataBuf[WSA_MAXIMUM_WAIT_EVENTS];
	SafeQueue<WSABUF> m_WsaufQue[WSA_MAXIMUM_WAIT_EVENTS];
	unsigned long	m_irecvBytes;

	//--- Server 용  ----------------------------------//


	//--- Client 용  ----------------------------------//

	/** Socket 초기화*/
	int initClientSocket();
	
	/** Server로 통신을 시작한다. */
	int startClient();
	
	/** Socket을 닫는다 */
	int closeClientSocket();
	
	/** Server에게 접속한다. Server가 준비가 되어 있지 않으면 1초간격으로 connect를 요구한다. */
	int connectClientSocket();
	
	static UINT ThreadClient(LPVOID param);
	
	SOCKET m_hClientSock;
	WSAEVENT m_hClinetEvent;
	SOCKADDR_IN m_ServAddr;

	//------------------ Server 관련 데이타  ----------------------------------//
	EMESIF_ITEM			m_eMESServerMessage;

	BOOL m_bFlag_ServerConnect;
	BOOL m_bFlag_ServerReceiveCNData;

	BOOL m_bFlag_ServerError;
	BOOL m_bFlag_ServerTrayUnloading;
	BOOL m_bFlag_ServerMovingOrder;
	
	int InitializeCommunicationData();

	// to. Server ------------------------------------------------------------
	
	// Socket 연결 요청
	int ConnectServer();

	// CN Data 전송
	int SendCNData(CString strCN, BOOL bFirstData = FALSE);

	// Machien E-Stop
	int MachineEStop();


	// from. Server ----------------------------------------------------------
	int HandlingServerMessage(CString strServerMsg);

	// Socket 초기화
	BOOL InitializeClientSocket();
	
	// Socket 연결 완료
	int	 SetServerConnectingCompete();
	BOOL IsServerConnectingComplete();

	// CN 처리 완료
	int	 SetServerReceiveCNData();
	BOOL IsServerReceiveCNData();


	//Huy funtion
	
	int recvData(char *recvbuf, int size, CString strMateIP);
	int sendData(char *sendbuf, CString strMateIP);

	virtual void RequestUnitbox2(int iUnit);
	virtual void RequesStartRunVisionUnitbox2(int iUnit);
	virtual void RequesFocus(int iUnit);
	virtual BOOL IsAllConnected();
	
	virtual BOOL IsSended(int iUnit);
	BOOL IsSendedAll(int iUnit);
	
	virtual int ReadData(CString & str, int iUnit);
	int ReadDataAll(CString & str,int iUnit);
	void AddLog(CString & str, int iUnit);
	BOOL m_bLockShowLog;
	//void AddLog(CString & str, int iUnit, int iLine);
	//void AddLog(CString & str);
	bool readfile(WSABUF wsaTmp, FILE * f);

	void RecevieFileLoop(int iSocket);
	int fileSend(const char * fpath, CString strMateIP, int iType = 0);
	int fileSend2(const char * fpath, CString strMateIP, int iType = 0);
	BOOL m_bLock;

	void SendFileLoop(int iUnit);

	MTickTimer m_timeProcessSendFile[MAX_CLIENT];
	MTickTimer m_timeProcessRecevieFile[MAX_CLIENT];
	
	int convertArraySocktoIp(int iSockarray);
	CString GetIp(const char* cstrMsg);

	CString strFileName;
	CString strSNold;
	CString strSNcur;
	int iStatusLabel;

	
protected:
	void ThreadMode();
public:
	int iStep ;
	
	//bool readfile(WSABUF filesize, FILE * f);
	//bool readfile(SOCKET sock, FILE * f);
	// MES Error
//	BOOL 

	ERECEVIE_STEP m_eStepRecevie[MAX_CLIENT];
	ESEND_STEP m_eStepSend[MAX_CLIENT];

	int sizeOfFileSend[MAX_CLIENT];
	char buffer[1030];

	SRecevieFile m_SRecevieFile[MAX_CLIENT];
	SSendFile m_SSendFile[MAX_CLIENT];

	char filename0[50];
	char filename1[50];
	char filename2[50];
	char filename3[50];
	char filename4[50];

	char filesize0[MAX_CLIENT];
	char filesize1[MAX_CLIENT];
	char filesize2[MAX_CLIENT];
	char filesize3[MAX_CLIENT];
	char filesize4[MAX_CLIENT];

	//char buffer[1030];

	//Ethernet thread
	EOpModeEthernet m_eOpModeEthernet;
	WSAEVENT MydummyEvent;

	
	//MLine
	//MLINE m_plnkLine;

	void AddLog(CString & str);

};

#endif // !defined(AFX_METHERNET_H__AE44A0F4_D563_44DE_B6F0_3220EB3E657D__INCLUDED_)
