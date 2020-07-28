// DlgOutput.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "DlgOutput.h"
#include "afxdialogex.h"


// DlgOutput dialog

IMPLEMENT_DYNAMIC(DlgOutput, CDialogEx)

DlgOutput::DlgOutput(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_OUTPUT, pParent)
{

}

DlgOutput::~DlgOutput()
{
}

void DlgOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 32; i++)
	{
		DDX_Control(pDX, IDB_IO_0, m_Output[i]);
	}
	
}


BEGIN_MESSAGE_MAP(DlgOutput, CDialogEx)
END_MESSAGE_MAP()


// DlgOutput message handlers
BEGIN_EVENTSINK_MAP(DlgOutput, CDialogEx)
	ON_EVENT(DlgOutput, IDB_EXIT1, DISPID_CLICK, DlgOutput::ClickExit1, VTS_NONE)
END_EVENTSINK_MAP()


void DlgOutput::ClickExit1()
{
	CDialog::OnCancel();
}


BOOL DlgOutput::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
void DlgOutput::SetNameCaption()
{
	CString m_Data;
	for (int i = 0; i < 32; i++)
	{
		m_Data.Format("Output %d", i);
		m_Output[i].SetCaption(m_Data);
	}
}