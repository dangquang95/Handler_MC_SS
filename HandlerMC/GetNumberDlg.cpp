// GetNumberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "GetNumberDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
// GetNumberDlg dialog

IMPLEMENT_DYNAMIC(GetNumberDlg, CDialogEx)

GetNumberDlg::GetNumberDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GET_NUMBER, pParent)
{

}

GetNumberDlg::~GetNumberDlg()
{
}

void GetNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KEY_TEXT_RESULT, m_tText_result);
}


BEGIN_MESSAGE_MAP(GetNumberDlg, CDialogEx)
END_MESSAGE_MAP()


// GetNumberDlg message handlers


void GetNumberDlg::DisplayText()
{
	m_tText_result.SetCaption(m_strText);
}

void GetNumberDlg::ClickKeyBtnReset()
{
	m_strText = _T("");
	DisplayText();
}
void GetNumberDlg::ClickKeyBtnDelete()
{
	int iLen = m_strText.GetLength();
	m_strText.Delete(iLen - 1, 1);
	DisplayText();
}
void GetNumberDlg::ClickKeyBtnEsc()
{
	CDialog::OnCancel();
}
void GetNumberDlg::ClickKeyBtnOk()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	dbKeyBoad = atof(m_strText);
	if (m_strText == "")
	{
		m_strText = "0";
	}
	pDoc->NumberReturn = dbKeyBoad;

	CDialog::OnOK();
}

void GetNumberDlg::ClickKeyBtnNum1()
{
	m_strText = m_strText + '1';
	DisplayText();
}
void GetNumberDlg::ClickKeyBtnNum2()
{
	m_strText = m_strText + '2';
	DisplayText();
}
void GetNumberDlg::ClickKeyBtnNum3()
{
	m_strText = m_strText + '3';
	DisplayText();
}
void GetNumberDlg::ClickKeyBtnNum4()
{
	m_strText = m_strText + '4';
	DisplayText();
}
void GetNumberDlg::ClickKeyBtnNum5()
{
	m_strText = m_strText + '5';
	DisplayText();
}
void GetNumberDlg::ClickKeyBtnNum6()
{
	m_strText = m_strText + '6';
	DisplayText();
}
void GetNumberDlg::ClickKeyBtnNum7()
{
	m_strText = m_strText + '7';
	DisplayText();
}
void GetNumberDlg::ClickKeyBtnNum8()
{
	m_strText = m_strText + '8';
	DisplayText();
}
void GetNumberDlg::ClickKeyBtnNum9()
{
	m_strText = m_strText + '9';
	DisplayText();
}
void GetNumberDlg::ClickKeyBtnNum0()
{
	m_strText = m_strText + '0';
	DisplayText();
}
void GetNumberDlg::ClickKeyBtn_()
{
	m_strText = m_strText + _T("-");
	DisplayText();
}
void GetNumberDlg::ClickKeyBtnDot()
{
	//	m_strText = m_strText + '.';
	//	DisplayText();
}





BOOL GetNumberDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_strText = _T("");
	pDoc->NumberReturn = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL GetNumberDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:

		if (pMsg->wParam == VK_BACK || pMsg->wParam == VK_DELETE)
		{
			int iLen = m_strText.GetLength();
			m_strText.Delete(iLen - 1, 1);
			DisplayText();
		}
		else if (pMsg->wParam == VK_ESCAPE)
		{
			CDialog::OnCancel();

			return FALSE;
		}
		else if (pMsg->wParam == VK_RETURN)
		{
			CDialog::OnOK();

			return FALSE;
		}

		else if (pMsg->wParam == '0' || pMsg->wParam == VK_NUMPAD0)
		{
			m_strText = m_strText + '0';
			DisplayText();
		}
		else if (pMsg->wParam == '1' || pMsg->wParam == VK_NUMPAD1)
		{
			m_strText = m_strText + '1';
			DisplayText();
		}
		else if (pMsg->wParam == '2' || pMsg->wParam == VK_NUMPAD2)
		{
			m_strText = m_strText + '2';
			DisplayText();
		}
		else if (pMsg->wParam == '3' || pMsg->wParam == VK_NUMPAD3)
		{
			m_strText = m_strText + '3';
			DisplayText();
		}
		else if (pMsg->wParam == '4' || pMsg->wParam == VK_NUMPAD4)
		{
			m_strText = m_strText + '4';
			DisplayText();
		}
		else if (pMsg->wParam == '5' || pMsg->wParam == VK_NUMPAD5)
		{
			m_strText = m_strText + '5';
			DisplayText();
		}
		else if (pMsg->wParam == '6' || pMsg->wParam == VK_NUMPAD6)
		{
			m_strText = m_strText + '6';
			DisplayText();
		}
		else if (pMsg->wParam == '7' || pMsg->wParam == VK_NUMPAD7)
		{
			m_strText = m_strText + '7';
			DisplayText();
		}
		else if (pMsg->wParam == '8' || pMsg->wParam == VK_NUMPAD8)
		{
			m_strText = m_strText + '8';
			DisplayText();
		}
		else if (pMsg->wParam == '9' || pMsg->wParam == VK_NUMPAD9)
		{
			m_strText = m_strText + '9';
			DisplayText();
		}
		else if (pMsg->wParam == VK_OEM_PERIOD || pMsg->wParam == VK_DECIMAL)
		{
			m_strText = m_strText + '.';
			DisplayText();
		}


	default:
		break;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
BEGIN_EVENTSINK_MAP(GetNumberDlg, CDialogEx)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_RESET, DISPID_CLICK, GetNumberDlg::ClickKeyBtnReset, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_DELETE, DISPID_CLICK,GetNumberDlg::ClickKeyBtnDelete, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_ESC, DISPID_CLICK,   GetNumberDlg::ClickKeyBtnEsc, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_OK, DISPID_CLICK,    GetNumberDlg::ClickKeyBtnOk, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_NUM_1, DISPID_CLICK, GetNumberDlg::ClickKeyBtnNum1, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_NUM_2, DISPID_CLICK, GetNumberDlg::ClickKeyBtnNum2, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_NUM_3, DISPID_CLICK, GetNumberDlg::ClickKeyBtnNum3, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_NUM_4, DISPID_CLICK, GetNumberDlg::ClickKeyBtnNum4, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_NUM_5, DISPID_CLICK, GetNumberDlg::ClickKeyBtnNum5, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_NUM_6, DISPID_CLICK, GetNumberDlg::ClickKeyBtnNum6, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_NUM_7, DISPID_CLICK, GetNumberDlg::ClickKeyBtnNum7, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_NUM_8, DISPID_CLICK, GetNumberDlg::ClickKeyBtnNum8, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_NUM_9, DISPID_CLICK, GetNumberDlg::ClickKeyBtnNum9, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_NUM_0, DISPID_CLICK, GetNumberDlg::ClickKeyBtnNum0, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_, DISPID_CLICK,      GetNumberDlg::ClickKeyBtn_, VTS_NONE)
	ON_EVENT(GetNumberDlg, IDC_KEY_BTN_DOT, DISPID_CLICK,   GetNumberDlg::ClickKeyBtnDot, VTS_NONE)
	
	END_EVENTSINK_MAP()

