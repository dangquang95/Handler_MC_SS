#pragma once

#include "MEthernet.h"
#include "MIEthernet.h"
#include "DefSystem.h"
#include <vector>
#include "stdafx.h"
#include "MTickTimer.h"
class ClientSocket
{
public:
	ClientSocket(sClient client);
	~ClientSocket();


	static UINT					ThreadSocket(LPVOID pParam);
	BOOL						bEndSocket;
	void						LoopSocket();
	void						StartTest(BOOL bSkip = FALSE);
	BOOL						isConnected();

	void						StartThread();
	void						StopThread();

	ETesterFunction				GetStatus();
	int							GetIndex();
	void						SetIris();
	BOOL						GetIris();
private:

	MEtherNet*					m_pObjEthernet;

	sClient                     m_Client;
	TesterData_Rpy				eResTest;
	
	BOOL			            bIris = FALSE;
	
//Quynh Add
public:
	void ReadDataClient(CString m_IP,int m_Port, double m_time);
};

