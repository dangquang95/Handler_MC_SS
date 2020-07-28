// TCPClient.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "TCPClient.h"
#include "afxdialogex.h"


// TCPClient dialog

IMPLEMENT_DYNAMIC(TCPClient, CDialogEx)

TCPClient::TCPClient(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_CLIENT, pParent)
{

}

TCPClient::~TCPClient()
{
}

void TCPClient::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TCPClient, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// TCPClient message handlers
BEGIN_EVENTSINK_MAP(TCPClient, CDialogEx)
	ON_EVENT(TCPClient, IDB_CLOSE_TCP, DISPID_CLICK, TCPClient::ClickCloseTcp, VTS_NONE)
	ON_EVENT(TCPClient, IDB_SEND_DATA, DISPID_CLICK, TCPClient::ClickSendData, VTS_NONE)
	ON_EVENT(TCPClient, IDB_CONNECT_CLIENT, DISPID_CLICK, TCPClient::ClickConnectClient, VTS_NONE)
	ON_EVENT(TCPClient, IDB_DISCONNECT, DISPID_CLICK, TCPClient::ClickDisconnect, VTS_NONE)
END_EVENTSINK_MAP()


void TCPClient::ClickCloseTcp()
{
	KillTimer(1);
	CDialog::OnCancel();
}




void TCPClient::ClickSendData()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	CString data;
	GetDlgItemText(IDC_SEND_INFO_DATA, data);
	pDoc->SendDataEthernet(data);
}


void TCPClient::OnTimer(UINT_PTR nIDEvent)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	switch (nIDEvent)
	{
	case 1:
		
		if (pDoc->m_client->m_Socket.ActionRevice)
		{
			GetDataRobot = pDoc->ReadDataRobot();
			SetDlgItemText(IDC_RESULT_DATA, GetDataRobot);
			pDoc->m_client->m_Socket.ActionRevice = false;
			//pDoc->FlagRevice = false;
		}		
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


BOOL TCPClient::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	
	SetTimer(1, 50, NULL);
	//
	CString CsPort;
	CsPort.Format("%d", pDoc->m_PortServer);
	SetDlgItemTextA(IDC_CLIENT_IP, pDoc->m_IpEthenet);
	SetDlgItemTextA(IDC_CLIENT_PORT, CsPort);
	//
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void TCPClient::ClickConnectClient()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	CString m_Ip;
	int m_port;
	GetDlgItemTextA(IDC_CLIENT_IP, m_Ip);
	GetDlgItemInt(IDC_CLIENT_PORT, &m_port);
	pDoc->InitSocketCaoHuy(m_Ip, m_port);
}


void TCPClient::ClickDisconnect()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->DisConnectSocket();
}
