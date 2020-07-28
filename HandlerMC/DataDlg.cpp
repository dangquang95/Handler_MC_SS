// DataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "DataDlg.h"
#include "afxdialogex.h"
#include "TCPClient.h"
#include "DlgDelayVaccum.h"
#include "DlgDelayCylinder.h"
// DataDlg dialog

IMPLEMENT_DYNAMIC(DataDlg, CDialogEx)

DataDlg::DataDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DATA_MAIN_FORM, pParent)
{

}

DataDlg::~DataDlg()
{
}

void DataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DataDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// DataDlg message handlers


BOOL DataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SaveControlPosition();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void DataDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	ChangeControlPosition();
}
void DataDlg::SaveControlPosition()
{
	CRect rect;
	TCHAR sz[256];

	GetClientRect(rect);
	m_PositionArray.Add(rect);

	CWnd* pWnd = GetTopWindow();

	pWnd->GetWindowText(sz, 256);
	pWnd->GetWindowRect(rect);
	ScreenToClient(rect);
	m_PositionArray.Add(rect);

	CWnd* tmpWnd = pWnd->GetNextWindow(GW_HWNDNEXT);

	while (tmpWnd != NULL)
	{
		tmpWnd->GetWindowText(sz, 256);
		tmpWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		m_PositionArray.Add(rect);
		tmpWnd = tmpWnd->GetNextWindow(GW_HWNDNEXT);
	}
}

void DataDlg::ChangeControlPosition()
{

	if (m_PositionArray.GetSize() <= 0)
		return;

	CRect rect, rect_org;
	int i = 0;

	rect_org = m_PositionArray.GetAt(i);
	i++;

	GetClientRect(rect);

	double dXRatio = ((double)rect.Width()) / ((double)rect_org.Width());
	double dYRatio = ((double)rect.Height()) / ((double)rect_org.Height());

	CWnd* pWnd = GetTopWindow();

	rect = m_PositionArray.GetAt(i);
	i++;

	pWnd->MoveWindow((int)(rect.left*dXRatio), (int)(rect.top*dYRatio),
		(int)(rect.Width()*dXRatio), (int)(rect.Height()*dYRatio));

	CWnd* tmpWnd = pWnd->GetNextWindow(GW_HWNDNEXT);

	while (tmpWnd != NULL)
	{
		rect = m_PositionArray.GetAt(i);
		i++;
		tmpWnd->MoveWindow((int)(rect.left*dXRatio), (int)(rect.top*dYRatio),
			(int)(rect.Width()*dXRatio), (int)(rect.Height()*dYRatio));

		tmpWnd = tmpWnd->GetNextWindow(GW_HWNDNEXT);
	}
}
BEGIN_EVENTSINK_MAP(DataDlg, CDialogEx)
	ON_EVENT(DataDlg, IDB_MODEL_DATA, DISPID_CLICK, DataDlg::ClickModelData, VTS_NONE)
	ON_EVENT(DataDlg, IDB_TCP_CLIENT, DISPID_CLICK, DataDlg::ClickTcpClient, VTS_NONE)
	ON_EVENT(DataDlg, IDB_LOAD_DATA, DISPID_CLICK, DataDlg::ClickLoadData, VTS_NONE)
	ON_EVENT(DataDlg, IDB_RUN_VELOCITY, DISPID_CLICK, DataDlg::ClickRunVelocity, VTS_NONE)
	ON_EVENT(DataDlg, IDB_SELECT_PHONE_TEST, DISPID_CLICK, DataDlg::ClickSelectPhoneTest, VTS_NONE)
	ON_EVENT(DataDlg, IDB_VISION_SETTING, DISPID_CLICK, DataDlg::ClickVisionSetting, VTS_NONE)
	ON_EVENT(DataDlg, IDB_SAVE_DATA, DISPID_CLICK, DataDlg::ClickSaveData, VTS_NONE)
	ON_EVENT(DataDlg, IDB_VACUUM_DELAY, DISPID_CLICK, DataDlg::ClickVacuumDelay, VTS_NONE)
	ON_EVENT(DataDlg, IDB_CYLINDER_DELAY, DISPID_CLICK, DataDlg::ClickCylinderDelay, VTS_NONE)
END_EVENTSINK_MAP()





void DataDlg::ClickModelData()
{
	ChangeModelDlg ShowDlg;
	ShowDlg.DoModal();
}


void DataDlg::ClickTcpClient()
{
	TCPClient ShowDlg;
	ShowDlg.DoModal();
	
}


void DataDlg::ClickLoadData()
{
	ReadDataMotion ShowDialog;
	ShowDialog.DoModal();
}


void DataDlg::ClickRunVelocity()
{
	DataMotorDlg ShowDlg;
	ShowDlg.DoModal();
}


void DataDlg::ClickSelectPhoneTest()
{
	SelectAction ShowDlg;
	ShowDlg.DoModal();
}


void DataDlg::ClickVisionSetting()
{
	VisionDlg ShowDlg;
	ShowDlg.DoModal();
}


void DataDlg::ClickSaveData()
{
	SaveDataModel ShowDlg;
	ShowDlg.DoModal();
}


void DataDlg::ClickVacuumDelay()
{
	DlgDelayVaccum ShowDlg;
	ShowDlg.DoModal();
}


void DataDlg::ClickCylinderDelay()
{
	DlgDelayCylinder ShowDlg;
	ShowDlg.DoModal();
}
