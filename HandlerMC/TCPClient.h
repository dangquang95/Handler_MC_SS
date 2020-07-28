#pragma once
#include "afxcmn.h"


// TCPClient dialog

class TCPClient : public CDialogEx
{
	DECLARE_DYNAMIC(TCPClient)

public:
	TCPClient(CWnd* pParent = NULL);   // standard constructor
	virtual ~TCPClient();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CLIENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickCloseTcp();
	CString GetDataRobot;
	void ClickSendData();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	void ClickConnectClient();
	void ClickDisconnect();
};
