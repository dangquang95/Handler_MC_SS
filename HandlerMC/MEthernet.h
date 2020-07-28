// MEtherNet_AF.h: interface for the MEtherNet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_METHERNET_H__AE44A0F4_D563_44DE_B6F0_3220EB3E657D__INCLUDED_)
#define AFX_METHERNET_H__AE44A0F4_D563_44DE_B6F0_3220EB3E657D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// inet_ntoa, inet_addr �Լ� ���� ��� �߻����� Disable ��Ŵ
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
 * Ethernet ����� ���� Class �μ� Server ���� Client ��� �������� ����Ҽ� �ִ�.
 * Server���� ����� Default�� 1���� Client�� ��ŵǸ�, �ִ� 63������ ������ �����ϴ�.
 * ��, Cleint�� ����Ҷ��� 	int AddClient(CString strClientIP)�� ȣ���Ѵ�.
 * 
 * �񵿱� Notification������� Server�� ������. 
 *
 * @author �ֱ��� (zery.choi@samsung.com)
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

	/** ������ 
	  * @param mode : eServerMode, eClientMode
	  * @param iPort : ����� Port��ȣ
	  * @param strMateIP : ¦�� �Ǵ� IP No (ClientMode�ÿ��� Server�� IP, ServerMode�ÿ��� ù��° Client�� �� IP)
	  * @param hNotify : �޽����� Notify��  Window Handle 
	  */	
	MEtherNet(eMode mode, int iPort, CString strMateIP, HWND hNotify = NULL);
	
	/** �Ҹ���*/
	virtual ~MEtherNet();

	/** ����� �����Ѵ�. ������ �� �ݵ�� ȣ���ؾ� ����� ���۵ȴ�.
	  * Client����� ��쿡�� 1�ʸ� �ֱ�� ��� Connect�� �õ���.
	  */
	int Initialize();	

	/** Data�� Send�Ѵ�.
	  * @param str : ���� Date
	  * @param strMateIP : ���� IP�ּ� (Default�� ���, ClientMode�ÿ��� Server�� IP, ServerMode�ÿ��� ù��° Client�� �� IP)
	  * @return : ���� - 0, ���� - ERR_NOT_CONNECTED
	  */
	virtual int SendData(CString str, CString strMateIP = _T(""));

	/** Data�� Send�Ѵ�.
	  * @param str : ���� Date
	  * @param strMateIP : ���� IP�ּ� (Default�� ���, ClientMode�ÿ��� Server�� IP, ServerMode�ÿ��� ù��° Client�� �� IP)
	  * @return : ���� - 0, ���� - ERR_NOT_CONNECTED
	  */
	virtual int SendCharacter(char* pChar, int nLength, CString strMateIP = "");

	/** Data�� Read�Ѵ�.
	  * @param str : �������� Data
	  * @param strMateIP : ���� IP�ּ� (Default�� ���, ClientMode�ÿ��� Server�� IP, ServerMode�ÿ��� ù��° Client�� �� IP)
	  * @return : ���� - 0, ���� - ERR_NOT_CONNECTED
	  */
	virtual int ReadData(CString& str, CString strMateIP = "");
	int ReadData(WSABUF & Wsa, CString strMateIP);
	int ReadDataServer(CString& str, CString strMateIP = "");
	
	/** ������ ���ӵǾ� �ִ��� üũ�Ѵ�..
	  * @param strMateIP : ���� IP�ּ� (Default�� ���, ClientMode�ÿ��� Server�� IP, ServerMode�ÿ��� ù��° Client�� �� IP)
	  * @return : TRUE , FALSE
	  */
	virtual BOOL IsMateConnected(CString strMateIP = "") ;

	/** Client�� �߰��Ѵ�. ��, �ִ� 63�������� �߰� �����ϴ�.
	  * @param strClientIP : ���� IP�ּ� (ClientMode�ÿ��� �������� �ʴ´�.)
	  * @return : ���� - 0, ���� - ERR_CLIENT_NO_OVER
	  */
	virtual int AddClient(CString strClientIP);

	/** ���濡�� �޽����� �����ߴ��� üũ�Ѵ�..
	  * @param strMateIP : ���� IP�ּ� (Default�� ���, ClientMode�ÿ��� Server�� IP, ServerMode�ÿ��� ù��° Client�� �� IP)
	  * @return : TRUE , FALSE
	  */
	virtual BOOL IsMateMsgReceived(CString strMateIP = "") ;


	/** ������ ���� �޽����� �����Ѵ�.
	  * Connecting, Receive, Close�� ���ؼ� �����ϸ� ��.
	  */
	virtual void Define_ConnectMsg(int nMessageID) {m_uiConnectMessage = nMessageID;};
	virtual void Define_ReceiveMsg(int nMessageID){m_uiReceiveMessage = nMessageID;};
	virtual void Define_ReceiveMsgFile(int nMessageID) { m_uiReceiveMessageFile = nMessageID; };
	virtual void Define_CloseMsg(int nMessageID){m_uiCloseMessage = nMessageID;};

	/** �޽��������� ���� ����Ű�� END CHARACTER�� �����Ѵ�.
	  * @param cEnd : END Character (default : 0x03)
	  */
	void Define_EndCharacter(char cEnd){m_cEndChar = cEnd;};

	int GetMaxClient() { return m_iMaxClient; };
	int GetPortIP() { return m_iPort; };
	eMode GetMode() { return m_eMode; };

	/** ������ ���� �޽����� ���� Handle�� Get/Set�Ѵ�.	  */
	void SetNotifyHandle(HWND hWnd) {m_hNotifyHandle = hWnd;};
	HWND GetNotifyHandle() {return m_hNotifyHandle;};

	/** ������ IP�ּҷ� Client ID�� ã�´�. (���Ӽ������ 1,2..)
	  * @param strMateIP : ��� IP�ּ�
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
	BOOL m_bConnected[WSA_MAXIMUM_WAIT_EVENTS];		//���� ���� Array
	BOOL m_bIsConnected[WSA_MAXIMUM_WAIT_EVENTS];		//���� ���� Array
	CString m_strMateIP[WSA_MAXIMUM_WAIT_EVENTS];	//��� IP �ּ� Array
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
	
	//--- Server ��  ----------------------------------//

	/** Socket �ʱ�ȭ*/
	int initServerSocket();
	
	/** Server�� ����� �����Ѵ�. */
	int startServer();
	
	/** Socket�� �ݴ´� */
	int closeServerSockets();

	/** Client�� Accept, Receive, Close�� �����Ѵ�. */
	static UINT ThreadServer(LPVOID param);
	static UINT ThreadSendFileSerVer(LPVOID param);
	void ThreadModeSendFile();
	virtual int startServerSendFile();
	virtual void ThreadModeSendFileStop();

	
	
	BOOL m_bThreadSendfile;
	
	
	BOOL m_bLiveThreadReceie;
//	static UINT ThreadRecevieSerVer(LPVOID param);

	

	void StopThreadServerSockets();

	SOCKET m_SockArray[WSA_MAXIMUM_WAIT_EVENTS];			//ù��° : Server Socket, �׿� : Client Socket
	SOCKET m_SockArrayTemp[WSA_MAXIMUM_WAIT_EVENTS];			//ù��° : Server Socket, �׿� : Client Socket
	WSAEVENT m_EventArray[WSA_MAXIMUM_WAIT_EVENTS];			//ù��° : Server Event, �׿� : Client Event
	int m_iSockNumber;//=0;										//���� ���ӵǾ� �ִ� ��ü ����
	WSABUF	m_dataBuf;
	WSABUF  m_dataBufRev;
	WSABUF	m_MyDataBuf[WSA_MAXIMUM_WAIT_EVENTS];
	SafeQueue<WSABUF> m_WsaufQue[WSA_MAXIMUM_WAIT_EVENTS];
	unsigned long	m_irecvBytes;

	//--- Server ��  ----------------------------------//


	//--- Client ��  ----------------------------------//

	/** Socket �ʱ�ȭ*/
	int initClientSocket();
	
	/** Server�� ����� �����Ѵ�. */
	int startClient();
	
	/** Socket�� �ݴ´� */
	int closeClientSocket();
	
	/** Server���� �����Ѵ�. Server�� �غ� �Ǿ� ���� ������ 1�ʰ������� connect�� �䱸�Ѵ�. */
	int connectClientSocket();
	
	static UINT ThreadClient(LPVOID param);
	
	SOCKET m_hClientSock;
	WSAEVENT m_hClinetEvent;
	SOCKADDR_IN m_ServAddr;

	//------------------ Server ���� ����Ÿ  ----------------------------------//
	EMESIF_ITEM			m_eMESServerMessage;

	BOOL m_bFlag_ServerConnect;
	BOOL m_bFlag_ServerReceiveCNData;

	BOOL m_bFlag_ServerError;
	BOOL m_bFlag_ServerTrayUnloading;
	BOOL m_bFlag_ServerMovingOrder;
	
	int InitializeCommunicationData();

	// to. Server ------------------------------------------------------------
	
	// Socket ���� ��û
	int ConnectServer();

	// CN Data ����
	int SendCNData(CString strCN, BOOL bFirstData = FALSE);

	// Machien E-Stop
	int MachineEStop();


	// from. Server ----------------------------------------------------------
	int HandlingServerMessage(CString strServerMsg);

	// Socket �ʱ�ȭ
	BOOL InitializeClientSocket();
	
	// Socket ���� �Ϸ�
	int	 SetServerConnectingCompete();
	BOOL IsServerConnectingComplete();

	// CN ó�� �Ϸ�
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
