// AutoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "AutoDlg.h"
#include "afxdialogex.h"
#include "DlgOriginAll.h"

#include "HandlerMCView.h"

// AutoDlg dialog

IMPLEMENT_DYNAMIC(AutoDlg, CDialogEx)

AutoDlg::AutoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTO_MAIN_FORM, pParent)
{

}

AutoDlg::~AutoDlg()
{
}

void AutoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAP_CONTROL, mPictureMap[0]);
	DDX_Control(pDX, IDC_MAP_CONTROL2, mPictureMap[1]);
	DDX_Control(pDX, IDC_MAP_CONTROL3, mPictureMap[2]);
	DDX_Control(pDX, IDC_TOTAL_COUNT1, m_TotalCount[0]);
	DDX_Control(pDX, IDC_TOTAL_COUNT2, m_TotalCount[1]);
	DDX_Control(pDX, IDC_TOTAL_COUNT3, m_TotalCount[2]);
	DDX_Control(pDX, IDC_TOTAL_COUNT4, m_TotalCount[3]);
	DDX_Control(pDX, IDC_GOOD_COUNT1, m_GoodCount[0]);
	DDX_Control(pDX, IDC_GOOD_COUNT2, m_GoodCount[1]);
	DDX_Control(pDX, IDC_GOOD_COUNT3, m_GoodCount[2]);
	DDX_Control(pDX, IDC_GOOD_COUNT4, m_GoodCount[3]);
	DDX_Control(pDX, IDC_NG_COUNT1, m_NGCount[0]);
	DDX_Control(pDX, IDC_NG_COUNT2, m_NGCount[1]);
	DDX_Control(pDX, IDC_NG_COUNT3, m_NGCount[2]);
	DDX_Control(pDX, IDC_NG_COUNT4, m_NGCount[3]);
	DDX_Control(pDX, IDC_YIELD_COUNT1, m_TactTimer[0]);
	DDX_Control(pDX, IDC_YIELD_COUNT2, m_TactTimer[1]);
	DDX_Control(pDX, IDC_YIELD_COUNT3, m_TactTimer[2]);
	DDX_Control(pDX, IDC_YIELD_COUNT4, m_TactTimer[3]);
	DDX_Control(pDX, IDC_TESTER_RESULT1, m_Status[0]);
	DDX_Control(pDX, IDC_TESTER_RESULT2, m_Status[1]);
	DDX_Control(pDX, IDC_TESTER_RESULT3, m_Status[2]);
	DDX_Control(pDX, IDC_TESTER_RESULT4, m_Status[3]);
	DDX_Control(pDX, IDC_LIST_VIEW_STEP, m_listViewStep);
	DDX_Control(pDX, IDB_RESULT_TESTER_1, m_simotion_result_tester[0]);
	DDX_Control(pDX, IDB_RESULT_TESTER_2, m_simotion_result_tester[1]);
	DDX_Control(pDX, IDB_RESULT_TESTER_3, m_simotion_result_tester[2]);
	DDX_Control(pDX, IDB_RESULT_TESTER_4, m_simotion_result_tester[3]);
	DDX_Control(pDX, IDB_RESULT_TESTER_5, m_StatusTool1Loading);
	DDX_Control(pDX, IDB_RESULT_TESTER_6, m_StatusTool2Loading);
	DDX_Control(pDX, IDB_RESULT_TESTER_7, m_StatusTool1Unloading);
	DDX_Control(pDX, IDB_RESULT_TESTER_8, m_StatusTool2Unloading);
	DDX_Control(pDX, IDB_NG_COUNT3, m_CommandTest[0]);
	DDX_Control(pDX, IDB_NG_COUNT4, m_CommandTest[1]);
	DDX_Control(pDX, IDB_NG_COUNT7, m_CommandTest[2]);
	DDX_Control(pDX, IDB_NG_COUNT10, m_CommandTest[3]);
	DDX_Control(pDX, IDB_ON_OFF_LEFT, m_OnOffLeft);
	DDX_Control(pDX, IDB_ON_OFF_RIGHT, m_OnOffRight);
	DDX_Control(pDX, IDB_ON_OFF_LOADING, m_OnOffLoading);
	DDX_Control(pDX, IDB_SAFETY, m_Using_Safety_Door);
	DDX_Control(pDX, IDB_USING_VISION, m_Using_Vision);
	DDX_Control(pDX, IDC_READY, m_PictureRready);
	DDX_Control(pDX, IDB_END_TRAY, m_End_Tray);
}


BEGIN_MESSAGE_MAP(AutoDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_OPTION_ON, &AutoDlg::OnOptionOn)
	ON_COMMAND(ID_OPTION_OFF, &AutoDlg::OnOptionOff)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// AutoDlg message handlers


BOOL AutoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	//CHandlerMCView * pView = (CHandlerMCView *)pFrm->GetActiveView();

	SaveControlPosition();
	
	//Loading data form file .dat
	CString PathLoading[4];
    PathLoading[0] = "Model\\" + pDoc->NameModelUse + "\\PositionTrayLoading.dat";
	PathLoading[1] = "Model\\" + pDoc->NameModelUse + "\\PositionTrayNgLeft.dat";
	PathLoading[2] = "Model\\" + pDoc->NameModelUse + "\\PositionTrayNgRight.dat";
	PathLoading[3] = "Model\\" + pDoc->NameModelUse + "\\StatusUnloading.dat";

	pDoc->InitalinePos();
	pDoc->ReadDataPosition(PathLoading[TrayLoading], TrayLoading);
	pDoc->ReadDataPosition(PathLoading[TrayNgLeft], TrayNgLeft);
	pDoc->ReadDataPosition(PathLoading[TrayNgRight], TrayNgRight);
	pDoc->ReadDataStatusUnloading(PathLoading[3]);
	pDoc->StatusLoadingModel = TRUE;
	SetTimer(1, 50, NULL);
	SetTimer(10, 5000, NULL);
	//vision
	//tray loading
	mShow = mMapBufer.clone();
	mMap = mMapBufer.clone();
	mMap.setTo(128);//	mMap.setTo(RGB(255,0,0));
	for (int i = 0; i < 3; i++)
	{
		mPictureMap[i].SetStretchToScreen();
		//mPictureMap.SetDisplayCursor(TRUE, _T("(X,Y)"));
		mPictureMap[i].UpdateDisplay();
		DisplayImage(mPictureMap[i], mMap);
	} 

	ViewDataTester();
	InitListLog();
	//
	if (pDoc->NotUseSafety)
	{		
		m_Using_Safety_Door.SetCaption("Not Using Safety Door");
	}
	else
	{		
		m_Using_Safety_Door.SetCaption("Using Safety Door");
	}
	
	if (pDoc->m_UsingVision)
	{
		m_Using_Vision.SetCaption("Using Vision");
	}
	else
	{
		m_Using_Vision.SetCaption("Not Using Vision");
	}
	//End Tray
	if (pDoc->m_EndTray)
	{
		m_End_Tray.SetCaption("End Tray On");
	}
	else
	{
		m_End_Tray.SetCaption("End Tray Off");
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void AutoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	ChangeControlPosition();
	
}

void AutoDlg::SaveControlPosition()
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

void AutoDlg::ChangeControlPosition()
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


void AutoDlg::OnTimer(UINT_PTR nIDEvent)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	switch (nIDEvent)
	{
	case 1:
	{
		if (pDoc->StatusLoadingModel)
		{
			Generate();
			for (int i = 0; i < 3; i++)
			{
				m_Picture = i;
				UpdatestStatusMap();//firt Run
			}

			pDoc->StatusLoadingModel = FALSE;
		}
		//if (pDoc->ActionOne)
		{
			ViewDataTester();
			//	pDoc->ActionOne = false;
		}
		//View picture loading
		if (pDoc->m_OnStatusPictureLoading)
		{
			AutoSetOnPictureLoading();
			pDoc->m_OnStatusPictureLoading = false;
		}
		//View picture Unloading left
		if (pDoc->m_OnStatusPictureUnloadingLeft)
		{
			AutoSetOnPictureUnloadingLeft();
			pDoc->m_OnStatusPictureUnloadingLeft = false;
		}
		//View picture Unloading Right
		if (pDoc->m_OnStatusPictureUnloadingRight)
		{
			AutoSetOnPictureUnloadingRight();
			pDoc->m_OnStatusPictureUnloadingRight = false;
		}
		//
		if (pDoc->m_FlagListViewLog)
		{
			AddLog(pDoc->m_DataListViewLog);
			pDoc->m_FlagListViewLog = false;
		}
		if (pDoc->ReadInput(Button_Stop))
		{
			m_PictureRready.SetPicture("C:\\Anh Icon InOut\\but_standby_off_click.JPG");
		}
		ViewStatusHamdler();
		break;
	}
	case 10:
	{
		if (pDoc->ReadSignalSensor())
		{

		}
		break;
	}
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


//vision
void AutoDlg::Generate()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	// Tray Loading
	int numRows, numColums, disRows, disColums;
	numRows = pDoc->RowTray;
	numColums = pDoc->ColumnTray;
	disRows = 20;
	disColums = 20;
	MappingPisition(numRows, numColums, disRows, disColums);

}

void AutoDlg::UpdatestStatusMap()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	for (int i = 0; i < pDoc->RowTray; i++)
		for (int j = 0; j < pDoc->ColumnTray; j++)
		{
			vPosition.at(i).at(j).bStatus = !pDoc->PosXY[m_Picture].at(i).at(j).status;
		}
	UpdatePosition();
}
void AutoDlg::MappingPisition(int numRows, int numColums, int disRows, int disColums)
{
	if (numRows == 0 || numColums == 0) {

		return;
	}
	this->numColums = numColums;
	this->numRows = numRows;

	int width = (int)mMap.cols / numColums;
	int height = (int)mMap.rows / numRows;

	Mat mTemp = mMap.clone();

	for (int i = 0; i < numRows; i++)
	{
		Point p1(0, i*height);
		Point p2(mMap.cols, i*height);
		line(mTemp, p1, p2, Scalar(255, 0, 0), disRows);
	}
	for (int i = 0; i < numColums; i++)
	{
		Point p1(i*width, 0);
		Point p2(i*width, mMap.rows);
		line(mTemp, p1, p2, Scalar(255, 0, 0), disColums);
	}
	//mShow = mTemp.clone();
	mShow = mTemp;
	vPosition.clear();
	vector<sPosition> vColums;
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColums; j++)
		{
			sPosition btnTemp;
			vColums.push_back(btnTemp);
		}
		vPosition.push_back(vColums);
		vColums.clear();

	}

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColums; j++)
		{
			vPosition.at(i).at(j).rRect = cv::Rect(j*(width), i*(height), width, height);
			CString str;
			str.Format("%d:%d", i, j);
			putText(mTemp, (string)(str), Point(j*(width)+width / 4, i*(height)+height / 4), FONT_HERSHEY_COMPLEX, disColums / 3, Scalar(0, 0, 255), disColums);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		DisplayImage(mPictureMap[i], mTemp);
	}
	
}

void AutoDlg::DisplayImage(im::CImAdvPanel& panel, cv::Mat& img)
{
	cv::Mat dispImg;
	try
	{
		if (img.empty())
		{
			dispImg.create(640, 480, CV_8UC1);
			dispImg = 0;
		}
		else
		{
			dispImg = img;
			cv::resize(dispImg, dispImg, cv::Size(img.cols, img.rows));
		}
		panel.SetImage(dispImg.data, (int)dispImg.total(), dispImg.cols, dispImg.rows, dispImg.channels());
		panel.UpdateDisplay();
		w = dispImg.cols;
		h = dispImg.rows;
	}
	catch (cv::Exception e)
	{
		TRACE("[Exception] UpdateImgPanel() %s", e.what());
	}

}

void AutoDlg::checkPosition(cv::Point point, int &x, int &y) {
	for (int i = 0; i < vPosition.size(); i++)
	{
		for (int j = 0; j < vPosition.at(0).size(); j++)
		{
			if (point.x > vPosition.at(i).at(j).rRect.x
				&& point.x < vPosition.at(i).at(j).rRect.x + vPosition.at(i).at(j).rRect.width
				&& point.y > vPosition.at(i).at(j).rRect.y
				&& point.y < vPosition.at(i).at(j).rRect.y + vPosition.at(i).at(j).rRect.height) {
				x = i;
				y = j;
				return;
			}
		}
	}

}
void AutoDlg::UpdatePosition()
{
	int width = (int)mMap.cols / numColums;
	int height = (int)mMap.rows / numRows;
	int offsetRect = 30;
	cv::Mat mTemp = mShow.clone();

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColums; j++)
		{
			vPosition.at(i).at(j).rRect = cv::Rect(j*(width)+offsetRect, i*(height)+offsetRect, width - offsetRect, height - offsetRect);
			CString str;
			str.Format("%d:%d", i, j);
			if (vPosition.at(i).at(j).bStatus == FALSE)
			{
				rectangle(mTemp, vPosition.at(i).at(j).rRect, Scalar(0, 192, 0), -1);// Scalar(0, 192, 0), -1);
			}

			putText(mTemp, (string)(str), Point(j*(width)+width / 4, i*(height)+height / 4), FONT_HERSHEY_COMPLEX, disColums / 3, Scalar(255, 0, 0), disColums);//Scalar(0, 0, 255)
		}
	}
	
	DisplayImage(mPictureMap[m_Picture], mTemp);
	
}

void AutoDlg::AutoSetOnPictureLoading()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_Picture = TrayLoading;
	for (int i = 0; i < pDoc->RowTray; i++)
		for (int j = 0; j < pDoc->ColumnTray; j++)
		{
			if (pDoc->PosXY[TrayLoading].at(i).at(j).status || pDoc->PosXY[TrayLoading].at(i).at(j).unloading)
			{
				vPosition.at(i).at(j).bStatus = FALSE;//XAM
			}
			else
			{
				vPosition.at(i).at(j).bStatus = TRUE;//XANH
			}

		}

	UpdatePosition();
}

void AutoDlg::AutoSetOnPictureUnloadingRight()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_Picture = TrayNgRight;
	for (int i = 0; i < pDoc->RowTray; i++)
		for (int j = 0; j < pDoc->ColumnTray; j++)
		{
			if (pDoc->PosXY[TrayNgRight].at(i).at(j).status)
			{
				vPosition.at(i).at(j).bStatus = FALSE;//XAM
			}
			else
			{
				vPosition.at(i).at(j).bStatus = TRUE;//XANH
			}

		}

	UpdatePosition();
}

void AutoDlg::AutoSetOnPictureUnloadingLeft()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_Picture = TrayNgLeft;
	for (int i = 0; i < pDoc->RowTray; i++)
		for (int j = 0; j < pDoc->ColumnTray; j++)
		{
			if (pDoc->PosXY[TrayNgLeft].at(i).at(j).status)
			{
				vPosition.at(i).at(j).bStatus = FALSE;//XAM
			}
			else
			{
				vPosition.at(i).at(j).bStatus = TRUE;//XANH
			}

		}

	UpdatePosition();
}

void AutoDlg::OnOptionOn()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	Point curPoint = CPoint2cvPoint(mPictureMap[m_Picture].c_point);
	int curX = 0, curY = 0;
	checkPosition(curPoint, curX, curY);

	pDoc->PosXY[m_Picture].at(curX).at(curY).status = true;
	if (m_Picture == 0)
	{
		pDoc->PosXY[m_Picture].at(curX).at(curY).unloading = FALSE;;
	}

	for (int i = 0; i < pDoc->RowTray; i++)
		for (int j = 0; j < pDoc->ColumnTray; j++)
		{
			if (pDoc->PosXY[m_Picture].at(i).at(j).status)
			{
				vPosition.at(i).at(j).bStatus = FALSE;//XAM
			}
			else
			{
				vPosition.at(i).at(j).bStatus = TRUE;//XANH
			}

		}

	UpdatePosition();
}


void AutoDlg::OnOptionOff()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	Point curPoint = CPoint2cvPoint(mPictureMap[m_Picture].c_point);
	int curX = 0, curY = 0;
	checkPosition(curPoint, curX, curY);

	pDoc->PosXY[m_Picture].at(curX).at(curY).status = false;
	if (m_Picture == 0)
	{
		pDoc->PosXY[m_Picture].at(curX).at(curY).unloading = TRUE;;
	}

	for (int i = 0; i < pDoc->RowTray; i++)
		for (int j = 0; j < pDoc->ColumnTray; j++)
		{
			if (pDoc->PosXY[m_Picture].at(i).at(j).status)
			{
				vPosition.at(i).at(j).bStatus = FALSE;//XAM
			}
			else
			{
				vPosition.at(i).at(j).bStatus = TRUE;//XANH
			}

		}

	UpdatePosition();
}


void AutoDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	int CtrlID = pWnd->GetDlgCtrlID();
	if (CtrlID == IDC_MAP_CONTROL)//  
	{
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU1));
		CMenu* pPopup = menu.GetSubMenu(0);
		pPopup->EnableMenuItem(ID_OPTION_ON, MF_ENABLED);
		pPopup->EnableMenuItem(ID_OPTION_OFF, MF_ENABLED);
		RECT rect;
		GetWindowRect(&rect);
		CPoint mousepos;
		GetCursorPos(&mousepos);
		pPopup->TrackPopupMenu(NULL, mousepos.x, mousepos.y, this);
		m_Picture = TrayLoading;
	}
	if (CtrlID == IDC_MAP_CONTROL2)//  
	{
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU1));
		CMenu* pPopup = menu.GetSubMenu(0);
		pPopup->EnableMenuItem(ID_OPTION_ON, MF_ENABLED);
		pPopup->EnableMenuItem(ID_OPTION_OFF, MF_ENABLED);
		RECT rect;
		GetWindowRect(&rect);
		CPoint mousepos;
		GetCursorPos(&mousepos);
		pPopup->TrackPopupMenu(NULL, mousepos.x, mousepos.y, this);
		m_Picture = TrayNgLeft;
	}
	if (CtrlID == IDC_MAP_CONTROL3)//  
	{
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU1));
		CMenu* pPopup = menu.GetSubMenu(0);
		pPopup->EnableMenuItem(ID_OPTION_ON, MF_ENABLED);
		pPopup->EnableMenuItem(ID_OPTION_OFF, MF_ENABLED);
		RECT rect;
		GetWindowRect(&rect);
		CPoint mousepos;
		GetCursorPos(&mousepos);
		pPopup->TrackPopupMenu(NULL, mousepos.x, mousepos.y, this);
		m_Picture = TrayNgRight;
	}




}
BEGIN_EVENTSINK_MAP(AutoDlg, CDialogEx)
	ON_EVENT(AutoDlg, IDB_ORIGIN_RETURN, DISPID_CLICK, AutoDlg::ClickOriginReturn, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_RESULT_TESTER_1, DISPID_CLICK, AutoDlg::ClickResultTester1, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_RESULT_TESTER_2, DISPID_CLICK, AutoDlg::ClickResultTester2, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_RESULT_TESTER_3, DISPID_CLICK, AutoDlg::ClickResultTester3, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_RESULT_TESTER_4, DISPID_CLICK, AutoDlg::ClickResultTester4, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_STOP, DISPID_CLICK, AutoDlg::ClickStop, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_STEP_DISP, DISPID_CLICK, AutoDlg::ClickStepDisp, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_UNIT_INITIAL, DISPID_CLICK, AutoDlg::ClickUnitInitial, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_START, DISPID_CLICK, AutoDlg::ClickStart, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_ON_OFF_LEFT, DISPID_CLICK, AutoDlg::ClickOnOffLeft, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_ON_OFF_RIGHT, DISPID_CLICK, AutoDlg::ClickOnOffRight, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_ON_OFF_LOADING, DISPID_CLICK, AutoDlg::ClickOnOffLoading, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_UNLOADING_TRAY, DISPID_CLICK, AutoDlg::ClickUnloadingTray, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_SAFETY, DISPID_CLICK, AutoDlg::ClickSafety, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_USING_VISION, DISPID_CLICK, AutoDlg::ClickUsingVision, VTS_NONE)
	ON_EVENT(AutoDlg, IDC_READY, DISPID_CLICK, AutoDlg::ClickReady, VTS_NONE)
	ON_EVENT(AutoDlg, IDB_END_TRAY, DISPID_CLICK, AutoDlg::ClickEndTray, VTS_NONE)
END_EVENTSINK_MAP()


void AutoDlg::ClickOriginReturn()
{
	DlgOriginAll ShowDlg;
	ShowDlg.DoModal();

}


void AutoDlg::ViewDataTester()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CString total, OK, NG, TactTime, Status;
	for (int i = 0; i < 4; i++)
	{
		if (pDoc->m_DataTester[i].Action && (pDoc->m_DataTester[i].TotalCount > 0))
		{
			total.Format("%d EA", pDoc->m_DataTester[i].TotalCount);
			m_TotalCount[i].SetCaption(total);

			OK.Format("%d EA(%d" , pDoc->m_DataTester[i].GoodCount, int(pDoc->m_DataTester[i].GoodCount *100)/ pDoc->m_DataTester[i].TotalCount);
			m_GoodCount[i].SetCaption(OK+"%)");

			NG.Format("%d EA(%d", pDoc->m_DataTester[i].NGCount, int(pDoc->m_DataTester[i].NGCount * 100) / pDoc->m_DataTester[i].TotalCount);
			m_NGCount[i].SetCaption(NG+"%)");

			TactTime.Format("%d sec", pDoc->m_DataTester[i].TactTime);
			m_TactTimer[i].SetCaption(TactTime);

	
			switch (pDoc->m_ResultTestSocket[i])
			{
			case 0:
			{
				if (!pDoc->m_DataTester[i].Loading && !pDoc->m_DataTester[i].StatusTester)
				{
					pDoc->m_DataTester[i].Status = "Testing";
					m_Status[i].SetCaption(pDoc->m_DataTester[i].Status);
				}
				else
				{
					pDoc->m_DataTester[i].Status = "Empty";
					m_Status[i].SetCaption(pDoc->m_DataTester[i].Status);
				}
				break;
			}
			case 1:
			{
				pDoc->m_DataTester[i].Status = "OK";
				m_Status[i].SetCaption(pDoc->m_DataTester[i].Status);
				break;
			}
			case 2:
			{
				pDoc->m_DataTester[i].Status = "NG";
				m_Status[i].SetCaption(pDoc->m_DataTester[i].Status);
				break;
			}
			default:
				break;
			}

			if (!pDoc->m_DataTester[i].StatusTester)
			{
				m_CommandTest[i].SetCaption("Command On");
			}
			else
			{
				m_CommandTest[i].SetCaption("Command Off");
			}
		}

		if (!pDoc->m_DataTester[i].Action)
		{
			m_Status[i].SetBackColor(RGB(192, 0, 0));//Mau do
			pDoc->m_DataTester[i].Status = "NotUse";
			m_Status[i].SetCaption(pDoc->m_DataTester[i].Status);
		}
		else
		{
			m_Status[i].SetBackColor(RGB(0, 192, 0));//Mau xanh la cay
		   //pDoc->m_DataTester[i].Status = "Use";
		}
	}
}

void AutoDlg::InitListLog()
{
	//Creat table with 2 colum
	m_listViewStep.InsertColumn(0, "Time", LVCFMT_LEFT, 80);
	m_listViewStep.InsertColumn(1, "Action", LVCFMT_LEFT, 340);
	//AddLog("Start program!");
}
void AutoDlg::AddLog(CString content)
{
	SYSTEMTIME	st;
	GetLocalTime(&st);
	CString strHours, strMin, strSec;
	if (st.wHour < 10)
	{
		strHours.Format("0%d", st.wHour);
	}
	else {
		strHours.Format("%d", st.wHour);
	}
	if (st.wMinute < 10)
	{
		strMin.Format("0%d", st.wMinute);
	}
	else {
		strMin.Format("%d", st.wMinute);
	}
	if (st.wSecond < 10)
	{
		strSec.Format("0%d", st.wSecond);
	}
	else {
		strSec.Format("%d", st.wSecond);
	}
	CString m_strCurrentTime = "[" + strHours + ":" + strMin + ":" + strSec + "]";


	m_listViewStep.InsertItem(0, m_strCurrentTime);
	m_listViewStep.SetItemText(0, 1, content);

}


void AutoDlg::ClickResultTester1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	if (!pDoc->m_DataTester[0].Action)
	{
		return;
	}

	pDoc->m_ResultTestSocket[0]++;
	if (pDoc->m_ResultTestSocket[0] == 4) pDoc->m_ResultTestSocket[0] = 0;

}


void AutoDlg::ClickResultTester2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	if (!pDoc->m_DataTester[1].Action)
	{
		return;
	}

	pDoc->m_ResultTestSocket[1]++;
	if (pDoc->m_ResultTestSocket[1] == 4) pDoc->m_ResultTestSocket[1] = 0;

}


void AutoDlg::ClickResultTester3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	if (!pDoc->m_DataTester[2].Action)
	{
		return;
	}

	pDoc->m_ResultTestSocket[2]++;
	if (pDoc->m_ResultTestSocket[2] == 4) pDoc->m_ResultTestSocket[2] = 0;

}


void AutoDlg::ClickResultTester4()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	if (!pDoc->m_DataTester[3].Action)
	{
		return;
	}

	pDoc->m_ResultTestSocket[3]++;
	if (pDoc->m_ResultTestSocket[3] == 4) pDoc->m_ResultTestSocket[3] = 0;

}


void AutoDlg::ClickStop()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->ActionStop();
}


void AutoDlg::ClickStart()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->m_operation = operation_start;
}

void AutoDlg::ClickStepDisp()
{
	ViewStepRunDlg ViewDlg;
	ViewDlg.DoModal();
}

void AutoDlg::ViewStatusHamdler()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	//Loading
	if (pDoc->m_Tool1Loading)
	{
		m_StatusTool1Loading.SetCaption("Busy");
	}
	else
	{
		m_StatusTool1Loading.SetCaption("Empty");
	}
	if (pDoc->m_Tool2Loading)
	{
		m_StatusTool2Loading.SetCaption("Busy");
	}
	else
	{
		m_StatusTool2Loading.SetCaption("Empty");
	}
   //Unloading
	if (pDoc->m_Tool1Unloading)
	{
		m_StatusTool1Unloading.SetCaption("Busy");
	}
	else
	{
		m_StatusTool1Unloading.SetCaption("Empty");
	}
	if (pDoc->m_Tool2Unloading)
	{
		m_StatusTool2Unloading.SetCaption("Busy");
	}
	else
	{
		m_StatusTool2Unloading.SetCaption("Empty");
	}
	//
	for (int i = 0; i < 4; i++)
	{
		switch (pDoc->m_ResultTestSocket[i])
		{
		case 0:
		{
			m_simotion_result_tester[i].SetCaption("None");
			break;
		}
		case 1:
		{
			m_simotion_result_tester[i].SetCaption("OK");
			break;
		}
		case 2:
		{
			m_simotion_result_tester[i].SetCaption("NG");
			break;
		}
		default:
			break;
		}
		
	}
}


void AutoDlg::ClickUnitInitial()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
     
	return;
	pDoc->ResetVariable();
}



void AutoDlg::ClickOnOffLeft()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (!m_FlagLeft)
	{
		m_FlagLeft = true;
		for (int i = 0; i < pDoc->RowTray; i++)
			for (int j = 0; j < pDoc->ColumnTray; j++)
			{
				pDoc->PosXY[TrayNgLeft].at(i).at(j).status = true;
			}
		pDoc->m_OnStatusPictureUnloadingLeft = true;
		m_OnOffLeft.SetCaption("On Left");
	}
	else
	{
		m_FlagLeft = false;
		for (int i = 0; i < pDoc->RowTray; i++)
			for (int j = 0; j < pDoc->ColumnTray; j++)
			{
				pDoc->PosXY[TrayNgLeft].at(i).at(j).status = false;
			}
		pDoc->m_OnStatusPictureUnloadingLeft = true;
		m_OnOffLeft.SetCaption("Off Left");
	}

}


void AutoDlg::ClickOnOffRight()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	if (!m_FlagRight)
	{
		m_FlagRight = true;
		for (int i = 0; i < pDoc->RowTray; i++)
			for (int j = 0; j < pDoc->ColumnTray; j++)
			{
				pDoc->PosXY[TrayNgRight].at(i).at(j).status = true;
			}
		pDoc->m_OnStatusPictureUnloadingRight = true;
		m_OnOffRight.SetCaption("On Right");
	}
	else
	{
		m_FlagRight = false;
		for (int i = 0; i < pDoc->RowTray; i++)
			for (int j = 0; j < pDoc->ColumnTray; j++)
			{
				pDoc->PosXY[TrayNgRight].at(i).at(j).status = false;
			}
		pDoc->m_OnStatusPictureUnloadingRight = true;
		m_OnOffRight.SetCaption("Off Right");
	}

}


void AutoDlg::ClickOnOffLoading()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	if (m_Flagloading)
	{
		m_Flagloading = false;
		for (int i = 0; i < pDoc->RowTray; i++)
			for (int j = 0; j < pDoc->ColumnTray; j++)
			{
				pDoc->PosXY[TrayLoading].at(i).at(j).status = true;
				pDoc->PosXY[TrayLoading].at(i).at(j).unloading = FALSE;
			}
		pDoc->m_OnStatusPictureLoading = true;
		m_OnOffLoading.SetCaption("Off");
	}
	else
	{
		m_Flagloading = true;
		for (int i = 0; i < pDoc->RowTray; i++)
			for (int j = 0; j < pDoc->ColumnTray; j++)
			{
				pDoc->PosXY[TrayLoading].at(i).at(j).status = false;
				pDoc->PosXY[TrayLoading].at(i).at(j).unloading = TRUE;;
			}

		pDoc->m_OnStatusPictureLoading = true;
		m_OnOffLoading.SetCaption("On");
	}
}

void AutoDlg::ClickUnloadingTray()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->UnloadingTray();
}


void AutoDlg::ClickSafety()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->m_NumberButtonSafety++;
	if ((pDoc->m_NumberButtonSafety % 2) == 1)
	{
		pDoc->NotUseSafety = true;
		m_Using_Safety_Door.SetCaption("Not Using Safety Door");
	}
	else
	{
		pDoc->NotUseSafety = false;
		m_Using_Safety_Door.SetCaption("Using Safety Door");
	}
}


void AutoDlg::ClickUsingVision()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	pDoc->m_NumberButtonVision++;
	if ((pDoc->m_NumberButtonVision % 2) == 1)
	{
		pDoc->m_UsingVision = false;
		m_Using_Vision.SetCaption("Not Using Vision");
	}
	else
	{
		pDoc->m_UsingVision = true;
		m_Using_Vision.SetCaption("Using Vision");
	}
}


void AutoDlg::ClickReady()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	if (pDoc->m_operation != operation_stop)
	{
		pDoc->m_ReadySuccess = false;
		AfxMessageBox("Don't Stop");
		return;
	}
	///*
	if (!pDoc->m_StatusOriginZLoading)
	{
		AfxMessageBox("Chua Origin Z Loading");
		return;
	}
	if (!pDoc->m_StatusOriginZUnloading)
	{
		AfxMessageBox("Chua Origin Z Loading");
		return;
	}
	if (!pDoc->m_StatusInitsocket)
	{
		AfxMessageBox("Chua Init Socket");
		return;
	}
	if (!pDoc->MootionDoneRobot())
	{
	    AfxMessageBox("Chua Init Robot");
     	return;
	}
	
	pDoc->m_ReadySuccess = true;
	m_PictureRready.SetPicture("C:\\Anh Icon InOut\\but_standby_on_eable.JPG");
}


void AutoDlg::ClickEndTray()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	return;
	if (pDoc->m_EndTray)
	{
		pDoc->m_EndTray = false;
    }
	else
	{
		pDoc->m_EndTray = true;;
	}
	if (pDoc->m_EndTray)
	{
		m_End_Tray.SetCaption("End Tray On");
	}
	else
	{
		m_End_Tray.SetCaption("End Tray Off");
	}

}
