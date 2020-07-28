
// HandlerMCView.cpp : implementation of the CHandlerMCView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HandlerMC.h"
#endif

#include "HandlerMCDoc.h"
#include "HandlerMCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHandlerMCView

IMPLEMENT_DYNCREATE(CHandlerMCView, CFormView)

BEGIN_MESSAGE_MAP(CHandlerMCView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CHandlerMCView construction/destruction

CHandlerMCView::CHandlerMCView()
	: CFormView(IDD_HANDLERMC_FORM)
{
	// TODO: add construction code here

}

CHandlerMCView::~CHandlerMCView()
{

	if (AUTODLG)
	{
		delete AUTODLG;
	}
	if (MANUDLG)
	{
		delete MANUDLG;
	}
	if (DATADLG)
	{
		delete DATADLG;
	}

	if (TEACHDLG)
	{
		delete TEACHDLG;
	}
	if (LOGDLG)
	{
		delete LOGDLG;
	}

}

void CHandlerMCView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIEW_ERROR_STATUS, m_ViewErrorStatus);
}

BOOL CHandlerMCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CHandlerMCView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();


	GetDlgItem(IDC_AREADLG)->GetWindowRect(&m_rtDlgArea);
	this->ScreenToClient(&m_rtDlgArea);

	m_rtDlgArea.left += 2;
	m_rtDlgArea.right -= 1;
	m_rtDlgArea.top += 2;
	m_rtDlgArea.bottom -= 1;

	CreateDlg();
	SelectDlg(AUTO_DLG);


	SaveControlPosition();

	SetTimer(12, 1000, NULL);

}

void CHandlerMCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHandlerMCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHandlerMCView diagnostics

#ifdef _DEBUG
void CHandlerMCView::AssertValid() const
{
	CFormView::AssertValid();
}

void CHandlerMCView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CHandlerMCDoc* CHandlerMCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHandlerMCDoc)));
	return (CHandlerMCDoc*)m_pDocument;
}
#endif //_DEBUG


// CHandlerMCView message handlers

void CHandlerMCView::CreateDlg()
{
	AUTODLG = new AutoDlg;
	AUTODLG->Create(AutoDlg::IDD, this);
	AUTODLG->MoveWindow(m_rtDlgArea);

	MANUDLG = new ManualDlg;
	MANUDLG->Create(ManualDlg::IDD, this);
	MANUDLG->MoveWindow(m_rtDlgArea);

	DATADLG = new DataDlg;
	DATADLG->Create(DataDlg::IDD, this);
	DATADLG->MoveWindow(m_rtDlgArea);

	TEACHDLG = new TeachDlg;
	TEACHDLG->Create(TeachDlg::IDD, this);
	TEACHDLG->MoveWindow(m_rtDlgArea);

	LOGDLG = new LogDlg;
	LOGDLG->Create(LogDlg::IDD, this);
	LOGDLG->MoveWindow(m_rtDlgArea);
	

}


void CHandlerMCView::SelectDlg(int DlgNo)
{
	switch (DlgNo)
	{
	case AUTO_DLG:
		AUTODLG->ShowWindow(TRUE);
		MANUDLG->ShowWindow(FALSE);
		TEACHDLG->ShowWindow(FALSE);
		DATADLG->ShowWindow(FALSE);
		LOGDLG->ShowWindow(FALSE);

		break;
	case MANUAL_DLG:
		AUTODLG->ShowWindow(FALSE);
		MANUDLG->ShowWindow(TRUE);
		TEACHDLG->ShowWindow(FALSE);
		DATADLG->ShowWindow(FALSE);
		LOGDLG->ShowWindow(FALSE);
		break;
	case TEACH_DLG:
		AUTODLG->ShowWindow(FALSE);
		MANUDLG->ShowWindow(FALSE);
		TEACHDLG->ShowWindow(TRUE);
		DATADLG->ShowWindow(FALSE);
		LOGDLG->ShowWindow(FALSE);
		break;
	case DATA_DLG:
		AUTODLG->ShowWindow(FALSE);
		MANUDLG->ShowWindow(FALSE);
		TEACHDLG->ShowWindow(FALSE);
		DATADLG->ShowWindow(TRUE);
		LOGDLG->ShowWindow(FALSE);
		break;
	case LOG_DLG:
		AUTODLG->ShowWindow(FALSE);
		MANUDLG->ShowWindow(FALSE);
		TEACHDLG->ShowWindow(FALSE);
		DATADLG->ShowWindow(FALSE);
		LOGDLG->ShowWindow(TRUE);
		break;
	default:
		break;
	}
}

void CHandlerMCView::SaveControlPosition()
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

void CHandlerMCView::ChangeControlPosition()
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
BEGIN_EVENTSINK_MAP(CHandlerMCView, CFormView)
	ON_EVENT(CHandlerMCView, IDC_BTN_AUTO, DISPID_CLICK, CHandlerMCView::ClickBtnAuto, VTS_NONE)
	
	ON_EVENT(CHandlerMCView, IDC_BTNE_MANUAL, DISPID_CLICK, CHandlerMCView::ClickBtneManual, VTS_NONE)
	ON_EVENT(CHandlerMCView, IDC_BTN_TEACH, DISPID_CLICK, CHandlerMCView::ClickBtnTeach, VTS_NONE)
	ON_EVENT(CHandlerMCView, IDC_BTN_DATA, DISPID_CLICK, CHandlerMCView::ClickBtnData, VTS_NONE)
	ON_EVENT(CHandlerMCView, IDC_BTN_LOG, DISPID_CLICK, CHandlerMCView::ClickBtnLog, VTS_NONE)
END_EVENTSINK_MAP()


void CHandlerMCView::ClickBtnAuto()
{
	SelectDlg(AUTO_DLG);
}


void CHandlerMCView::ClickBtneManual()
{

	SelectDlg(MANUAL_DLG);
}


void CHandlerMCView::ClickBtnTeach()
{
	SelectDlg(TEACH_DLG);
}


void CHandlerMCView::ClickBtnData()
{
	SelectDlg(DATA_DLG);
}


void CHandlerMCView::ClickBtnLog()
{
	SelectDlg(LOG_DLG);
}


void CHandlerMCView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	ChangeControlPosition();
}

void CHandlerMCView::SetDataError(CString m_data)
{
	m_ViewErrorStatus.SetCaption(m_data);
}

void CHandlerMCView::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 12:
	{
		if (this->GetDocument()->ReadSignalSensor())
		{
			m_numberInc++;
			SetDataError(this->GetDocument()->MessengerData);
			if ((m_numberInc % 2) == 1)
			{
				if (m_numberInc == 100)	{ m_numberInc = 1;}
				m_ViewErrorStatus.SetBackColor(200);//Mau do
			}
			else
			{
				m_ViewErrorStatus.SetBackColor(RGB(224, 224, 224));
			}
			
		}
		else
		{
			m_ViewErrorStatus.SetBackColor(RGB(224, 224, 224));
			SetDataError("");
		}
		break;
	}
	default:
		break;
	}

	CFormView::OnTimer(nIDEvent);
}
