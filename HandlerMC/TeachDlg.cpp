// TeachDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "TeachDlg.h"
#include "afxdialogex.h"


// TeachDlg dialog

IMPLEMENT_DYNAMIC(TeachDlg, CDialogEx)

TeachDlg::TeachDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEACH_MAIN_FORM, pParent)
	//, m_RobotUp(0)
{

}

TeachDlg::~TeachDlg()
{
}

void TeachDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE_TEACH, m_PictureTeach);
	DDX_Control(pDX, IDC_COORD_AXIS1_1_1, m_TargetPosX);
	DDX_Control(pDX, IDC_COORD_AXIS1_1_2, m_TargetPosY);
	DDX_Control(pDX, IDC_COORD_AXIS1_1_3, m_TargetPosZ);
	DDX_Control(pDX, IDC_COORD_AXIS1_1_4, m_TargetPosR);
	DDX_Control(pDX, IDB_AXIS1_SERVO_1, m_ServoOnOffX);
	DDX_Control(pDX, IDB_AXIS1_SERVO_2, m_ServoOnOffY);
	DDX_Control(pDX, IDC_Current_pos_X, m_Current_pos_X);
	DDX_Control(pDX, IDC_Current_pos_Y, m_Current_pos_Y);
	DDX_Control(pDX, IDC_Current_pos_X2, m_Current_posAct_X);
	DDX_Control(pDX, IDC_Current_pos_Y2, m_Current_posAct_Y);
	DDX_Control(pDX, IDC_VIEW_SPEED, m_ViewSpeedJog);
	DDX_Control(pDX, IDC_LIST1, m_ActionToo1Loading);
	DDX_Control(pDX, IDC_LIST2, m_ActionToo2Loading);
	DDX_Control(pDX, IDC_LIST3, m_ActionToo1Unloading);
	DDX_Control(pDX, IDC_LIST4, m_ActionToo2Unloading);
	DDX_Control(pDX, IDC_LIST5, m_ActionLoadingVision);
	DDX_Control(pDX, IDC_OFFSET_JOG_Z1, m_Offset_JogZ1);
	DDX_Control(pDX, IDC_LIST6, m_ActionuUnloadingTrayFull);
	DDX_Control(pDX, IDC_CONECT_COM, m_ConnectCom);
	DDX_Control(pDX, IDC_BAUDRATE, m_BaudRate);
	DDX_Control(pDX, IDB_CONNECT_COM, m_CaptionConnect);
	DDX_Control(pDX, IDC_LIST7, m_ActionToolRobot);
	DDX_Control(pDX, IDC_LIST8, m_ActionVaccumRobot);

	DDX_Control(pDX, IDB_ROBOT_UP, m_ViewRobotUpMediumDown[0]);
	DDX_Control(pDX, IDB_ROBOT_MEDIUM, m_ViewRobotUpMediumDown[1]);
	DDX_Control(pDX, IDB_ROBOT_LOW, m_ViewRobotUpMediumDown[2]);
}


BEGIN_MESSAGE_MAP(TeachDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_OPTION_SELECT, &TeachDlg::OnOptionSelect)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO3, &TeachDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO_TRAY_UNLOADING_LEFT, &TeachDlg::OnBnClickedRadioTrayUnloadingLeft)
	ON_COMMAND(ID_OPTION_RUNPOSTOOL2, &TeachDlg::OnOptionRunpostool2)
	ON_BN_CLICKED(IDC_RADIO2, &TeachDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO_TRAY_UNLOADING_LEFT2, &TeachDlg::OnBnClickedRadioTrayUnloadingLeft2)
END_MESSAGE_MAP()


// TeachDlg message handlers


BOOL TeachDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	SaveControlPosition();
	//vision
	//tray loading
	mShow = mMapBufer.clone();
	mMap = mMapBufer.clone();
	mMap.setTo(128);

	m_PictureTeach.SetStretchToScreen();
	//mPictureMap.SetDisplayCursor(TRUE, _T("(X,Y)"));
	m_PictureTeach.UpdateDisplay();
	DisplayImage(m_PictureTeach, mMap);

	//hien thi anh vision
	Generate();
	UpdatestStatusMap();//firt Run
	SetTimer(1, 50, NULL);
	//On Servo XY
	if (pDoc->StatusOpenCard)
	{
		pDoc->Motion.Servo_OnOff(AxisX, ENABLE);
		m_ServoOnOffX.SetCaption("On");
		pDoc->Motion.Servo_OnOff(AxisY, ENABLE);
		m_ServoOnOffY.SetCaption("On");
	}

	m_ActionToo1Loading.AddString("1.Tool1 Place Phone1");
	m_ActionToo1Loading.AddString("2.Tool1 Place Phone2");
	m_ActionToo1Loading.AddString("3.Tool1 Place Phone3");
	m_ActionToo1Loading.AddString("4.Tool1 Place Phone4");

	m_ActionToo2Loading.AddString("1.Tool2 Place Phone1");
	m_ActionToo2Loading.AddString("2.Tool2 Place Phone2");
	m_ActionToo2Loading.AddString("3.Tool2 Place Phone3");
	m_ActionToo2Loading.AddString("4.Tool2 Place Phone4");

	m_ActionToo1Unloading.AddString("1.Tool3 Pick Phone1");
	m_ActionToo1Unloading.AddString("2.Tool3 Pick Phone2");
	m_ActionToo1Unloading.AddString("3.Tool3 Pick Phone3");
	m_ActionToo1Unloading.AddString("4.Tool3 Pick Phone4");

	m_ActionToo2Unloading.AddString("1.Tool4 Pick Phone1");
	m_ActionToo2Unloading.AddString("2.Tool4 Pick Phone2");
	m_ActionToo2Unloading.AddString("3.Tool4 Pick Phone3");
	m_ActionToo2Unloading.AddString("4.Tool4 Pick Phone4");

	m_ActionLoadingVision.AddString("1.Tool1 Loading Vision");
	m_ActionLoadingVision.AddString("2.Tool2 Loading Vision");
	m_ActionLoadingVision.AddString("3.Tool1 Loading Aline");
	m_ActionLoadingVision.AddString("4.Tool2 Loading Aline");
	m_ActionLoadingVision.AddString("5.Tool1 Pick Aline");
	m_ActionLoadingVision.AddString("6.Tool2 Pick Aline");

	m_ActionuUnloadingTrayFull.AddString("1.Pick Tray Full");
	m_ActionuUnloadingTrayFull.AddString("2.Place Tray Full");
	m_ActionuUnloadingTrayFull.AddString("3.Robot go to  Pos ready");

	m_ActionToolRobot.AddString("1.Tool1 Robot");
	m_ActionToolRobot.AddString("2.Tool2 Robot");
	m_ActionToolRobot.AddString("3.Tool3 Robot");
	m_ActionToolRobot.AddString("4.Tool4 Robot");


	m_ActionVaccumRobot.AddString("1.Vaccum Tool1 Robot");
	m_ActionVaccumRobot.AddString("2.Vaccum Tool2 Robot");
	m_ActionVaccumRobot.AddString("3.Vaccum Tool3 Robot");
	m_ActionVaccumRobot.AddString("4.Vaccum Tool4 Robot");
	m_ActionVaccumRobot.AddString("5.Vaccum Tray Robot");
	m_ActionVaccumRobot.AddString("6.Cylinder Aline ");

	SetcaptionZ1Offset();
	SetupCOM();


	CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO2);
	pButton->SetCheck(true);

	ClickRobotUp();
	m_SelectTrayAction = 1;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void TeachDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	ChangeControlPosition();
}
void TeachDlg::SaveControlPosition()
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

void TeachDlg::ChangeControlPosition()
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


//vision
void TeachDlg::Generate()
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

void TeachDlg::UpdatestStatusMap()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	for (int i = 0; i < pDoc->RowTray; i++)
		for (int j = 0; j < pDoc->ColumnTray; j++)
		{
			vPosition.at(i).at(j).bStatus = !pDoc->PosXY[m_SlectTray].at(i).at(j).status;
		}
	UpdatePosition();
}
void TeachDlg::MappingPisition(int numRows, int numColums, int disRows, int disColums)
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
	DisplayImage(m_PictureTeach, mTemp);
}

void TeachDlg::DisplayImage(im::CImAdvPanel& panel, cv::Mat& img)
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

void TeachDlg::checkPosition(cv::Point point, int &x, int &y) {
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
void TeachDlg::UpdatePosition()
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
				rectangle(mTemp, vPosition.at(i).at(j).rRect, Scalar(0, 192, 0), -1);//Scalar(100, 100, 100), -1); Scalar(0, 192, 0)
			}

			putText(mTemp, (string)(str), Point(j*(width)+width / 4, i*(height)+height / 4), FONT_HERSHEY_COMPLEX, disColums / 3, Scalar(255, 0, 0), disColums);//Scalar(0, 0, 255)
		}
	}

	DisplayImage(m_PictureTeach, mTemp);

}
void TeachDlg::AutoSetOnPictureLoading(int m_x, int m_y)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	Point curPoint = CPoint2cvPoint(m_PictureTeach.c_point);
	int curX = m_x;
	int	curY = m_y;

	for (int i = 0; i < pDoc->RowTray; i++)
		for (int j = 0; j < pDoc->ColumnTray; j++)
		{
			vPosition.at(i).at(j).bStatus = TRUE;//XAM
		}

	for (int i = 0; i < pDoc->RowTray; i++)
		for (int j = 0; j < pDoc->ColumnTray; j++)
		{
			if ((i >= curX) && (j >= curY))
			{
				vPosition.at(i).at(j).bStatus = FALSE;//XANH
			}
			if (i > curX)
			{
				vPosition.at(i).at(j).bStatus = FALSE;//XANH
			}
		}

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
				rectangle(mTemp, vPosition.at(i).at(j).rRect, Scalar(0, 192, 0), -1);//Scalar(100, 100, 100), -1);
			}

			putText(mTemp, (string)(str), Point(j*(width)+width / 4, i*(height)+height / 4), FONT_HERSHEY_COMPLEX, disColums / 3, Scalar(255, 0, 0), disColums);//Scalar(0, 0, 255)
		}
	}
	//

	DisplayImage(m_PictureTeach, mTemp);
}

void TeachDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	int CtrlID = pWnd->GetDlgCtrlID();
	if (CtrlID == IDC_PICTURE_TEACH)//  
	{
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU2));
		CMenu* pPopup = menu.GetSubMenu(0);
		pPopup->EnableMenuItem(ID_OPTION_SELECT, MF_ENABLED);
		//pPopup->EnableMenuItem(ID_OPTION_OFF, MF_ENABLED);
		RECT rect;
		GetWindowRect(&rect);
		CPoint mousepos;
		GetCursorPos(&mousepos);
		pPopup->TrackPopupMenu(NULL, mousepos.x, mousepos.y, this);
	}
}

void TeachDlg::OnOptionSelect()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	Point curPoint = CPoint2cvPoint(m_PictureTeach.c_point);
	int curX = 0, curY = 0;
	checkPosition(curPoint, curX, curY);

	CString m_DataView;
	m_DataView.Format("(%d,%d,", curX, curY);	
	UpdatePosTarget(curX, curY);

	SetDlgItemTextA(IDC_VIEW_DATA_RESULT, "");
	//	
	switch (m_SelectTrayAction)
	{
	case 1://Tray loading
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingTool1Up + m_DataView +"0)");
			ViewDataSend(pDoc->CmRunRobotLoadingTool1Up + m_DataView + "0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingTool1Down + m_DataView + "1)");
			ViewDataSend(pDoc->CmRunRobotLoadingTool1Down + m_DataView + "1)");
		}
		if (SelectZ[2])//Down_More
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotDownMore);
			ViewDataSend(pDoc->CmRunRobotDownMore);
		}
	
		break;
	case 2://Tray Unloading left
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingLeftTool3Up + m_DataView + "0,2,0)");
			ViewDataSend(pDoc->CmRunRobotUnloadingLeftTool3Up + m_DataView + +"0,2,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingLeftTool3Down + m_DataView + "0,2,1)");
			ViewDataSend(pDoc->CmRunRobotUnloadingLeftTool3Down + m_DataView + "0,2,1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 3://Tray Unloading Right
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingRightTool3Up + m_DataView + "0,3,0)");
			ViewDataSend(pDoc->CmRunRobotUnloadingRightTool3Up + m_DataView + "0,3,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingRightTool3Down + m_DataView + +"0,3,1)");
			ViewDataSend(pDoc->CmRunRobotUnloadingRightTool3Down + m_DataView + "0,3,1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 4://Tray OK
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingTrayOKTool3Up + m_DataView + "1,1,0)");
			ViewDataSend(pDoc->CmRunRobotUnloadingTrayOKTool3Up + m_DataView + "1,1,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingTrayOKTool3Down + m_DataView + "1,1,1)");
			ViewDataSend(pDoc->CmRunRobotUnloadingTrayOKTool3Down + m_DataView + "1,1,1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	default:
		AfxMessageBox("Chua chon tray");
		break;
	}

	
}

void TeachDlg::OnOptionRunpostool2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	Point curPoint = CPoint2cvPoint(m_PictureTeach.c_point);
	int curX = 0, curY = 0;
	checkPosition(curPoint, curX, curY);

	CString m_DataView;
	m_DataView.Format("(%d,%d,", curX, curY);
	UpdatePosTarget(curX, curY);

	//	
	//	
	switch (m_SelectTrayAction)
	{
	case 1://Tray loading
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingTool2Up + m_DataView + "0)");
			ViewDataSend(pDoc->CmRunRobotLoadingTool2Up + m_DataView + "0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingTool2Down + m_DataView + "1)");
			ViewDataSend(pDoc->CmRunRobotLoadingTool2Down + m_DataView + "1)");
		}
		if (SelectZ[2])//Down_More
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotDownMore);
			ViewDataSend(pDoc->CmRunRobotDownMore);
		}
		break;
	case 2://Tray Unloading left
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingLeftTool4Up + m_DataView + "0,2,0)");
			ViewDataSend(pDoc->CmRunRobotUnloadingLeftTool4Up + m_DataView + +"0,2,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingLeftTool4Down + m_DataView + "0,2,1)");
			ViewDataSend(pDoc->CmRunRobotUnloadingLeftTool4Down + m_DataView + "0,2,1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 3://Tray Unloading Right
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingRightTool4Up + m_DataView + "0,3,0)");
			ViewDataSend(pDoc->CmRunRobotUnloadingRightTool4Up + m_DataView + "0,3,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingRightTool4Down + m_DataView + +"0,3,1)");
			ViewDataSend(pDoc->CmRunRobotUnloadingRightTool4Down + m_DataView + "0,3,1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 4://Tray OK
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingTrayOKTool4Up + m_DataView + "1,1,0)");
			ViewDataSend(pDoc->CmRunRobotUnloadingTrayOKTool4Up + m_DataView + "1,1,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingTrayOKTool4Down + m_DataView + "1,1,1)");
			ViewDataSend(pDoc->CmRunRobotUnloadingTrayOKTool4Down + m_DataView + "1,1,1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	default:
		AfxMessageBox("Chua chon tray");
		break;
	}

}


void TeachDlg::UpdatePosTarget(int x,int y)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CString m_DataX, m_DataY, m_DataZ;
	m_DataX.Format("%d", (int)pDoc->PosXY[m_SlectTray].at(x).at(y).dPositionX);
	m_DataY.Format("%d", (int)pDoc->PosXY[m_SlectTray].at(x).at(y).dPositionY);
	m_DataZ.Format("%d", (int)pDoc->PosXY[m_SlectTray].at(x).at(y).dPositionZ);

	m_TargetPosX.SetCaption(m_DataX);
	m_TargetPosY.SetCaption(m_DataY);;
	m_TargetPosZ.SetCaption(m_DataZ);

}

void TeachDlg::OnTimer(UINT_PTR nIDEvent)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	switch (nIDEvent)
	{
	case 1:
		if (pDoc->StatusLoadingModel2)
		{
			Generate();
		    UpdatestStatusMap();//firt Run
			pDoc->StatusLoadingModel2 = FALSE;

		}
		if (pDoc->StatusOpenCard)
		{ 
			SetCurenntpos();
		}
		//nhan du lieu COM
		if (pDoc->m_SignReviceCom)
		{
		   SetDlgItemTextA(IDC_REVICE_DATA_COM, pDoc->m_DataComEvent);
		   pDoc->m_SignReviceCom = false;
		}
		//Show data TCP
		if (pDoc->m_client->m_Socket.ActionRevice /*&&  (pDoc->m_operation == operation_stop)*/)
		{
			m_GetDataRobot = pDoc->ReadDataRobot();
			if (m_GetDataRobot.GetLength() > 0)
			{
				SetDlgItemTextA(IDC_VIEW_DATA_RESULT, m_GetDataRobot);
			}			
			pDoc->m_client->m_Socket.ActionRevice = false;
	
		}

		ViewRatioSpeed();
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}
BEGIN_EVENTSINK_MAP(TeachDlg, CDialogEx)
	ON_EVENT(TeachDlg, IDB_AXIS1_SERVO_1, DISPID_CLICK, TeachDlg::ClickAxis1Servo1, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_AXIS1_SERVO_2, DISPID_CLICK, TeachDlg::ClickAxis1Servo2, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_JOG_HEAD1_Y_FOR, DISPID_MOUSEDOWN, TeachDlg::MouseDownJogHead1YFor, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(TeachDlg, IDB_JOG_HEAD1_Y_FOR, DISPID_MOUSEUP, TeachDlg::MouseUpJogHead1YFor, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(TeachDlg, IDB_JOG_HEAD1_Y_BACK, DISPID_MOUSEDOWN, TeachDlg::MouseDownJogHead1YBack, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(TeachDlg, IDB_JOG_HEAD1_Y_BACK, DISPID_MOUSEUP, TeachDlg::MouseUpJogHead1YBack, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(TeachDlg, IDB_JOG_HEAD1_Z_UP, DISPID_MOUSEDOWN, TeachDlg::MouseDownJogHead1ZUp, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(TeachDlg, IDB_JOG_HEAD1_Z_UP, DISPID_MOUSEUP, TeachDlg::MouseUpJogHead1ZUp, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(TeachDlg, IDB_JOG_HEAD1_Z_DOWN, DISPID_MOUSEDOWN, TeachDlg::MouseDownJogHead1ZDown, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(TeachDlg, IDB_JOG_HEAD1_Z_DOWN, DISPID_MOUSEUP, TeachDlg::MouseUpJogHead1ZDown, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(TeachDlg, IDB_AXIS1_POINT1_DOWN, DISPID_CLICK, TeachDlg::ClickAxis1Point1Down, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_AXIS1_POINT1_UP, DISPID_CLICK, TeachDlg::ClickAxis1Point1Up, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_AXIS2_POINT1_DOWN, DISPID_CLICK, TeachDlg::ClickAxis2Point1Down, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_AXIS2_POINT1_UP, DISPID_CLICK, TeachDlg::ClickAxis2Point1Up, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_AXIS1_POINT1_DOWN_RUN, DISPID_CLICK, TeachDlg::ClickAxis1Point1DownRun, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_AXIS1_POINT1_UP_RUN, DISPID_CLICK, TeachDlg::ClickAxis1Point1UpRun, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_AXIS2_POINT1_DOWN_RUN, DISPID_CLICK, TeachDlg::ClickAxis2Point1DownRun, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_AXIS2_POINT1_UP_RUN, DISPID_CLICK, TeachDlg::ClickAxis2Point1UpRun, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_JOG_INC_SPEED, DISPID_CLICK, TeachDlg::ClickJogIncSpeed, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_JOG_DEC1_SPEED, DISPID_CLICK, TeachDlg::ClickJogDec1Speed, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_TOOL1_LOADING, DISPID_CLICK, TeachDlg::ClickTool1Loading, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_TOOL2_LOADING, DISPID_CLICK, TeachDlg::ClickTool2Loading, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_TOOL1_UNLOADING, DISPID_CLICK, TeachDlg::ClickTool1Unloading, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_TOOL2_UNLOADING, DISPID_CLICK, TeachDlg::ClickTool2Unloading, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_LOADING_VISION, DISPID_CLICK, TeachDlg::ClickLoadingVision, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_LOADING_VISION, DISPID_CLICK, TeachDlg::ClickLoadingVision, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_LOADING_TRAY_Z1, DISPID_CLICK, TeachDlg::ClickLoadingTrayZ1, VTS_NONE)
	ON_EVENT(TeachDlg, IDC_OFFSET_JOG_Z1, DISPID_CLICK, TeachDlg::ClickOffsetJogZ1, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_UNLOADING_TRAY, DISPID_CLICK, TeachDlg::ClickUnloadingTray, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_AXIS2_POINT2_UP_RUN, DISPID_CLICK, TeachDlg::ClickAxis2Point2UpRun, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_AXIS2_POINT2_UP, DISPID_CLICK, TeachDlg::ClickAxis2Point2Up, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_UNLOADING_TRAY_FULL, DISPID_CLICK, TeachDlg::ClickUnloadingTrayFull, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_CONNECT_COM, DISPID_CLICK, TeachDlg::ClickConnectCom, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_SEND_DATA_COM, DISPID_CLICK, TeachDlg::ClickSendDataCom, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_TOOLROBOT_ON, DISPID_CLICK, TeachDlg::ClickToolrobotOn, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_TOOLROBOT_ON2, DISPID_CLICK, TeachDlg::ClickToolrobotOn2, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_TOOLROBOT_ON3, DISPID_CLICK, TeachDlg::ClickToolrobotOn3, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_TOOLROBOT_ON4, DISPID_CLICK, TeachDlg::ClickToolrobotOn4, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_TEST_VISION_TOOL1, DISPID_CLICK, TeachDlg::ClickTestVisionTool1, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_TEST_VISION_TOOL2, DISPID_CLICK, TeachDlg::ClickTestVisionTool2, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_ROBOT_UP, DISPID_CLICK, TeachDlg::ClickRobotUp, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_ROBOT_MEDIUM, DISPID_CLICK, TeachDlg::ClickRobotMedium, VTS_NONE)
	ON_EVENT(TeachDlg, IDB_ROBOT_LOW, DISPID_CLICK, TeachDlg::ClickRobotLow, VTS_NONE)
END_EVENTSINK_MAP()


void TeachDlg::ClickAxis1Servo1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (pDoc->Motion.Status_OnOff(AxisX))
	{
		pDoc->Motion.Servo_OnOff(AxisX, DISABLE);
		m_ServoOnOffX.SetCaption("Off");
	}

	else
	{
		pDoc->Motion.Servo_OnOff(AxisX, ENABLE);
		m_ServoOnOffX.SetCaption("On");
	}
}


void TeachDlg::ClickAxis1Servo2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	if (pDoc->Motion.Status_OnOff(AxisY))
	{
		pDoc->Motion.Servo_OnOff(AxisY, DISABLE);
		m_ServoOnOffY.SetCaption("Off");
	}

	else
	{
		pDoc->Motion.Servo_OnOff(AxisY, ENABLE);
		m_ServoOnOffY.SetCaption("On");
	}
}


void TeachDlg::MouseDownJogHead1YFor(short Button, short Shift, long x, long y)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	double m_speed = 0 + pDoc->DataMotor.SpeedJog;
	if (pDoc->Motion.Status_OnOff(AxisX) /*&& pDoc->SafetyRunXY()*/)
	{
		pDoc->Motion.JogRun(AxisX, m_speed, pDoc->DataMotor.Acc, pDoc->DataMotor.Dec);
	}
}



void TeachDlg::MouseUpJogHead1YFor(short Button, short Shift, long x, long y)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->Motion.JogStop(AxisX);

}


void TeachDlg::MouseDownJogHead1YBack(short Button, short Shift, long x, long y)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	double m_speed = 0 - pDoc->DataMotor.SpeedJog;
	if (pDoc->Motion.Status_OnOff(AxisX) /*&& pDoc->SafetyRunXY()*/)
	{
		pDoc->Motion.JogRun(AxisX, m_speed, pDoc->DataMotor.Acc, pDoc->DataMotor.Dec);
	}
}


void TeachDlg::MouseUpJogHead1YBack(short Button, short Shift, long x, long y)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->Motion.JogStop(AxisX);
}


void TeachDlg::MouseDownJogHead1ZUp(short Button, short Shift, long x, long y)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	double m_speed = 0 + pDoc->DataMotor.SpeedJog;

	if (pDoc->Motion.Status_OnOff(AxisY))
	{
		pDoc->Motion.JogRun(AxisY, m_speed, pDoc->DataMotor.Acc, pDoc->DataMotor.Dec);
	}
}


void TeachDlg::MouseUpJogHead1ZUp(short Button, short Shift, long x, long y)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->Motion.JogStop(AxisY);
}


void TeachDlg::MouseDownJogHead1ZDown(short Button, short Shift, long x, long y)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	double m_speed = 0 - pDoc->DataMotor.SpeedJog;

	if (pDoc->Motion.Status_OnOff(AxisZ))
	{
		pDoc->Motion.JogRun(AxisY, m_speed, pDoc->DataMotor.Acc, pDoc->DataMotor.Dec);

	}
}


void TeachDlg::MouseUpJogHead1ZDown(short Button, short Shift, long x, long y)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->Motion.JogStop(AxisY);
}

void TeachDlg::SetCurenntpos()
{

	CurentPosActX = TeachMotion.StatusGetActPos(AxisX);
	CurentPosACtY = TeachMotion.StatusGetActPos(AxisY);
	
	CurentPosX = TeachMotion.StatusGetCmdPos(AxisX);
	CurentPosY = TeachMotion.StatusGetCmdPos(AxisY);

	//Current_pos_Cmd_X
	m_CurentPosX.Format("%lf", CurentPosX);
	m_CurentPosY.Format("%lf", CurentPosY);


	m_Current_pos_X.SetCaption(m_CurentPosX);
	m_Current_pos_Y.SetCaption(m_CurentPosY);

	//m_Current_pos_Act_X
	m_CurentPosX.Format("%lf", CurentPosActX);
	m_CurentPosY.Format("%lf", CurentPosACtY);

	m_Current_posAct_X.SetCaption(m_CurentPosX);
	m_Current_posAct_Y.SetCaption(m_CurentPosY);


}
//Save Point
void TeachDlg::ClickAxis1Point1Down()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	const int result = MessageBox("Do you want save point1 of Z1 down?", "Message", MB_YESNO); //MB_YESNOCANCEL)

	switch (result)
	{
	case IDYES:
		// Do something
		break;
	case IDNO:
		return;
		break;
	case IDCANCEL:
		return;
		break;
	}

	pDoc->PosZ1Down = CurentPosActX;
	SavePointTeach();
}


void TeachDlg::ClickAxis1Point1Up()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	const int result = MessageBox("Do you want save point1 of Z1 up?", "Message", MB_YESNO); //MB_YESNOCANCEL)

	switch (result)
	{
	case IDYES:
		// Do something
		break;
	case IDNO:
		return;
		break;
	case IDCANCEL:
		return;
		break;
	}
	pDoc->PosZ1Up = CurentPosActX;
	SavePointTeach();
}


void TeachDlg::ClickAxis2Point1Down()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	const int result = MessageBox("Do you want save point1 of Z2 down?", "Message", MB_YESNO); //MB_YESNOCANCEL)

	switch (result)
	{
	case IDYES:
		// Do something
		break;
	case IDNO:
		return;
		break;
	case IDCANCEL:
		return;
		break;
	}
	pDoc->PosZ2Down = CurentPosACtY;
	SavePointTeach();
}


void TeachDlg::ClickAxis2Point1Up()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	const int result = MessageBox("Do you want save point1 of Z2 up?", "Message", MB_YESNO); //MB_YESNOCANCEL)

	switch (result)
	{
	case IDYES:
		// Do something
		break;
	case IDNO:
		return;
		break;
	case IDCANCEL:
		return;
		break;
	}
	pDoc->PosZ2Up = CurentPosACtY;
	SavePointTeach();
}

void TeachDlg::ClickAxis2Point2Up()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	const int result = MessageBox("Do you want save point1 of Z2 up?", "Message", MB_YESNO); //MB_YESNOCANCEL)

	switch (result)
	{
	case IDYES:
		// Do something
		break;
	case IDNO:
		return;
		break;
	case IDCANCEL:
		return;
		break;
	}
	pDoc->PosZ2Medium = CurentPosACtY;
	SavePointTeach();
}

void TeachDlg::SavePointTeach()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CString strPath = "DataSystem\\DataPointLoadUnload.dat";
	HANDLE hFile = CreateFile(strPath, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(hFile);

	CFileFind ffind;
	//CString strPath = "DataSystem\\DataPointLoadUnload.dat";

	if (ffind.FindFile((LPCTSTR)strPath) == FALSE)
	{
		AfxMessageBox("Not find");
	}
	else
	{
		CStdioFile fn;
		fn.Open(strPath, CFile::modeReadWrite);
		fn.WriteString("[Data]\n\n");
		CString cstr;
		cstr.Format("PosZ1Down			 = %lf \n", pDoc->PosZ1Down);
		fn.WriteString(cstr);
		cstr.Format("PosZ1Up		     = %lf \n", pDoc->PosZ1Up);
		fn.WriteString(cstr);
		cstr.Format("PosZ2Down           = %lf \n", pDoc->PosZ2Down);
		fn.WriteString(cstr);
		cstr.Format("PosZ2Up             = %lf \n", pDoc->PosZ2Up);
		fn.WriteString(cstr);
		cstr.Format("PosZ2Medium         = %lf \n", pDoc->PosZ2Medium);
		fn.WriteString(cstr);
		cstr.Format("OffsetZ1            = %lf \n", pDoc->OffsetJogLoadingZ1);
		fn.WriteString(cstr);
		fn.Close();
	}
	//

}

//Run point

void TeachDlg::ClickAxis1Point1DownRun()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	const int result = MessageBox("Do you want run point1 ?", "Message", MB_YESNO); //MB_YESNOCANCEL)

	switch (result)
	{
	case IDYES:
		// Do something
		break;
	case IDNO:
		return;
		break;
	case IDCANCEL:
		return;
		break;
	}

	pDoc->RunPosLoading(pDoc->PosZ1Down);

}


void TeachDlg::ClickAxis1Point1UpRun()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	const int result = MessageBox("Do you want run point1 ?", "Message", MB_YESNO); //MB_YESNOCANCEL)

	pDoc->RunPosLoading(pDoc->PosZ1Up);
}


void TeachDlg::ClickAxis2Point1DownRun()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	const int result = MessageBox("Do you want run point1 ?", "Message", MB_YESNO); //MB_YESNOCANCEL)

	pDoc->RunPosUnloading(pDoc->PosZ2Down);
}


void TeachDlg::ClickAxis2Point1UpRun()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	const int result = MessageBox("Do you want run point1 ?", "Message", MB_YESNO); //MB_YESNOCANCEL)

	pDoc->RunPosUnloading(pDoc->PosZ2Up);
}

void TeachDlg::ClickAxis2Point2UpRun()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	const int result = MessageBox("Do you want run point ?", "Message", MB_YESNO); //MB_YESNOCANCEL)

	pDoc->RunPosUnloading(pDoc->PosZ2Medium);
}


void TeachDlg::ClickJogIncSpeed()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_RatioSpeed = m_RatioSpeed + 1;
	if (m_RatioSpeed > 20) m_RatioSpeed = 20;
	pDoc->DataMotor.SpeedJog = pDoc->DataMotor.defireSpeedJog  * m_RatioSpeed;
	
}


void TeachDlg::ClickJogDec1Speed()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_RatioSpeed = m_RatioSpeed - 1;
	if (m_RatioSpeed == 0) m_RatioSpeed = 1;
	pDoc->DataMotor.SpeedJog = pDoc->DataMotor.defireSpeedJog  * m_RatioSpeed;

}
void TeachDlg::ViewRatioSpeed()
{
	m_ViewSpeed.Format("%d", m_RatioSpeed);
	m_ViewSpeedJog.SetCaption(m_ViewSpeed);
}
//Radio
void TeachDlg::OnBnClickedRadio2()
{
	m_SelectTrayAction = 1;
}

void TeachDlg::OnBnClickedRadioTrayUnloadingLeft()
{
	m_SelectTrayAction = 2;
}

void TeachDlg::OnBnClickedRadio3()
{
	m_SelectTrayAction = 3;
}

void TeachDlg::OnBnClickedRadioTrayUnloadingLeft2()
{
	m_SelectTrayAction = 4;
}
//
void TeachDlg::ViewDataSend(CString m_data)
{
	SetDlgItemText(IDC_VIEW_DATA_SEND, m_data);
}

void TeachDlg::ClickTool1Loading()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	int std = m_ActionToo1Loading.GetCurSel();
	SetDlgItemTextA(IDC_VIEW_DATA_RESULT, "");
	switch (std)
	{
	case 0:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket1Tool1Up + "(0,0,0,1,0)");
			ViewDataSend(pDoc->CmRunRobotLoadingSocket1Tool1Up + "(0,0,0,1,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket1Tool1Down);
			ViewDataSend(pDoc->CmRunRobotLoadingSocket1Tool1Down);
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 1:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket2Tool1Up + "(0,0,0,2,0)");
			ViewDataSend(pDoc->CmRunRobotLoadingSocket2Tool1Up + "(0,0,0,2,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket2Tool1Down);
			ViewDataSend(pDoc->CmRunRobotLoadingSocket2Tool1Down);
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 2:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket3Tool1Up + "(0,0,0,3,0)");
			ViewDataSend(pDoc->CmRunRobotLoadingSocket3Tool1Up + "(0,0,0,3,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket3Tool1Down);
			ViewDataSend(pDoc->CmRunRobotLoadingSocket3Tool1Down );
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 3:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket4Tool1Up + "(0,0,0,4,0)");
			ViewDataSend(pDoc->CmRunRobotLoadingSocket4Tool1Up + "(0,0,0,4,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket4Tool1Down );
			ViewDataSend(pDoc->CmRunRobotLoadingSocket4Tool1Down );
		};
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	default:
		break;
	}
	
}


void TeachDlg::ClickTool2Loading()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	int std = m_ActionToo2Loading.GetCurSel();
	SetDlgItemTextA(IDC_VIEW_DATA_RESULT, "");

	switch (std)
	{
	case 0:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket1Tool2Up + "(0,0,0,1,0)");
			ViewDataSend(pDoc->CmRunRobotLoadingSocket1Tool2Up + "(0,0,0,1,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket1Tool2Down );
			ViewDataSend(pDoc->CmRunRobotLoadingSocket1Tool2Down );
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 1:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket2Tool2Up + "(0,0,0,2,0)");
			ViewDataSend(pDoc->CmRunRobotLoadingSocket2Tool2Up + "(0,0,0,2,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket2Tool2Down );
			ViewDataSend(pDoc->CmRunRobotLoadingSocket2Tool2Down);
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 2:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket3Tool2Up + "(0,0,0,3,0)");
			ViewDataSend(pDoc->CmRunRobotLoadingSocket3Tool2Up + "(0,0,0,3,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket3Tool2Down );
			ViewDataSend(pDoc->CmRunRobotLoadingSocket3Tool2Down);
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 3:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket4Tool2Up + "(0,0,0,4,0)");
			ViewDataSend(pDoc->CmRunRobotLoadingSocket4Tool2Up + "(0,0,0,4,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotLoadingSocket4Tool2Down);
			ViewDataSend(pDoc->CmRunRobotLoadingSocket4Tool2Down );
		};
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	default:
		break;
	}
}


void TeachDlg::ClickTool1Unloading()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	int std = m_ActionToo1Unloading.GetCurSel();
	SetDlgItemTextA(IDC_VIEW_DATA_RESULT, "");

	switch (std)
	{
	case 0:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket1Tool3Up);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket1Tool3Up);
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket1Tool3Down);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket1Tool3Down);
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 1:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket2Tool3Up);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket2Tool3Up);
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket2Tool3Down);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket2Tool3Down);
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 2:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket3Tool3Up);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket3Tool3Up);
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket3Tool3Down);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket3Tool3Down);
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 3:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket4Tool3Up);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket4Tool3Up);
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket4Tool3Down);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket4Tool3Down);
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	default:
		break;
	}
}


void TeachDlg::ClickTool2Unloading()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	int std = m_ActionToo2Unloading.GetCurSel();
	SetDlgItemTextA(IDC_VIEW_DATA_RESULT, "");

	switch (std)
	{
	case 0:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket1Tool4Up);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket1Tool4Up);
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket1Tool4Down);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket1Tool4Down);
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 1:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket2Tool4Up);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket2Tool4Up);
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket2Tool4Down);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket2Tool4Down);
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 2:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket3Tool4Up);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket3Tool4Up);
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket3Tool4Down);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket3Tool4Down);
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 3:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket4Tool4Up);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket4Tool4Up);
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingSocket4Tool4Down);
			ViewDataSend(pDoc->CmRunRobotUnloadingSocket4Tool4Down);
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	default:
		break;
	}
}

void TeachDlg::ClickLoadingVision()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	int std = m_ActionLoadingVision.GetCurSel();
	SetDlgItemTextA(IDC_VIEW_DATA_RESULT, "");

	switch (std)
	{
	case 0:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotVisionTool1 + "(1,0)");
			ViewDataSend(pDoc->CmRunRobotVisionTool1 + "(1,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotVisionTool1 + "(1,1)");
			ViewDataSend(pDoc->CmRunRobotVisionTool1 + "(1,1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 1:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotVisionTool2 + "(2,0)");
			ViewDataSend(pDoc->CmRunRobotVisionTool2 + "(2,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotVisionTool2 + "(2,1)");
			ViewDataSend(pDoc->CmRunRobotVisionTool2 + "(2,1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 2:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotAlineTool1 + "(1,0)");
			ViewDataSend(pDoc->CmRunRobotAlineTool1 + "(1,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotAlineTool1 + "(1,1)");
			ViewDataSend(pDoc->CmRunRobotAlineTool1 + "(1,1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 3:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotAlineTool2 + "(2,0)");
			ViewDataSend(pDoc->CmRunRobotAlineTool2 + "(2,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotAlineTool2 + "(2,1)");
			ViewDataSend(pDoc->CmRunRobotAlineTool2 + "(2,1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 4:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotAlinePickTool1 + "(1,0)");
			ViewDataSend(pDoc->CmRunRobotAlinePickTool1 + "(1,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotAlinePickTool1 + "(1,1)");
			ViewDataSend(pDoc->CmRunRobotAlinePickTool1 + "(1,1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	case 5:
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotAlinePickTool2 + "(2,0)");
			ViewDataSend(pDoc->CmRunRobotAlinePickTool2 + "(2,0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotAlinePickTool2 + "(2,1)");
			ViewDataSend(pDoc->CmRunRobotAlinePickTool2 + "(2,1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	default:
		break;
	}
}

void TeachDlg::ClickUnloadingTrayFull()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	int std = m_ActionuUnloadingTrayFull.GetCurSel();
	SetDlgItemTextA(IDC_VIEW_DATA_RESULT, "");

	switch (std)
	{
	case 0:
	{
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingTrayLoading + "(0)");
			ViewDataSend(pDoc->CmRunRobotUnloadingTrayLoading + "(0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingTrayLoading + "(1)");
			ViewDataSend(pDoc->CmRunRobotUnloadingTrayLoading + "(1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	}
	case 1:
	{
		if (SelectZ[0])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingTrayUnloading + "(0)");
			ViewDataSend(pDoc->CmRunRobotUnloadingTrayUnloading + "(0)");
		}
		if (SelectZ[1])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingTrayUnloading + "(1)");
			ViewDataSend(pDoc->CmRunRobotUnloadingTrayUnloading + "(1)");
		}
		if (SelectZ[2])
		{
			pDoc->SendDataEthernet(pDoc->CmRunRobotUnloadingTrayUnloading + "(1)");
			ViewDataSend(pDoc->CmRunRobotUnloadingTrayUnloading + "(1)");
		}
		if (SelectZ[2])//Down_More
		{
			AfxMessageBox("Donot support Robot Low");
		}
		break;
	}
	case 2:
	{
		pDoc->SendDataEthernet("Ready()");
		ViewDataSend("Ready()");
		break;
	}
	default:
		break;
	}
}


void TeachDlg::ClickLoadingTrayZ1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->m_trayLoading = 0;

	if (pDoc->m_operation == operation_stop)
	{
		while (true)
		{
			if (pDoc->m_BufferLoading())
			{
				pDoc->m_trayLoading = 0;
				return;
			}

			if (pDoc->ReadInput(Button_Stop))
			{
				return;
			}
		}
	}
}

void TeachDlg::ClickUnloadingTray()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	pDoc->m_ActionDownZUnloading = 0;

	if (pDoc->m_operation == operation_stop)
	{
		while (true)
		{
			if (pDoc->ActionDownZUnloading())
			{
				pDoc->m_ActionDownZUnloading = 0;
				return;
			}

			if (pDoc->ReadInput(Button_Stop))
			{
				return;
			}
		}
	}
}


void TeachDlg::ClickOffsetJogZ1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	CString data;
	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	pDoc->OffsetJogLoadingZ1 = (int)pDoc->NumberReturn;
	data.Format("%d", (int)pDoc->NumberReturn);

	m_Offset_JogZ1.SetCaption(data);
	SavePointTeach();
}

void TeachDlg::SetcaptionZ1Offset()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	CString data;
	data.Format("%d", (int)pDoc->OffsetJogLoadingZ1);
	m_Offset_JogZ1.SetCaption(data);
}





void TeachDlg::ClickConnectCom()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CString m_comNo, m_baudrate;
	int m_Compost;
	GetDlgItemTextA(IDC_CONECT_COM, m_comNo);
	GetDlgItemTextA(IDC_BAUDRATE, m_baudrate);

	m_Compost = GetDlgItemInt(IDC_CONECT_COM);
	pDoc->m_NumberComEvent = m_Compost;
	pDoc->m_BaudRateEvent = m_BaudRate.GetCurSel();

	pDoc->InitComPhone(pDoc->m_NumberComEvent, pDoc->m_BaudRateEvent);

}

void TeachDlg::SetupCOM()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CString data;
	for (int i = 0; i < 20; i++)
	{
		data.Format("%d", i);
		m_ConnectCom.AddString(data);
	}
	m_BaudRate.AddString("7200");
	m_BaudRate.AddString("9600");
	m_BaudRate.AddString("19200");
	m_BaudRate.AddString("38400");
	m_BaudRate.AddString("57600");
	m_BaudRate.AddString("115200");
	m_BaudRate.AddString("230400");
	m_BaudRate.AddString("460800");
	m_BaudRate.AddString("921600");

	m_ConnectCom.SetCurSel(pDoc->m_NumberComEvent);
	m_BaudRate.SetCurSel(pDoc->m_BaudRateEvent);

	
}

void TeachDlg::ClickSendDataCom()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CString m_data;
	GetDlgItemTextA(IDC_SEND_DATA_COM, m_data);
	if (pDoc->m_StatusConnectCom)
	{
		pDoc->SendPhoneCom(m_data);
	}
	else
	{
		AfxMessageBox("Don't Connect");
	}
	
}

void TeachDlg::ClickToolrobotOn()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	int std = m_ActionToolRobot.GetCurSel();
	switch (std)
	{
	case 0:
		pDoc->XilanhTool1Off();
		break;
	case 1:
		pDoc->XilanhTool2Off();
		break;
	case 2:
		pDoc->XilanhTool3Off();
		break;
	case 3:
		pDoc->XilanhTool4Off();
		break;
	default:
		break;
	}
}


void TeachDlg::ClickToolrobotOn2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	int std = m_ActionToolRobot.GetCurSel();
	switch (std)
	{
	case 0:
		pDoc->XilanhTool1On();
		break;
	case 1:
		pDoc->XilanhTool2On();
		break;
	case 2:
		pDoc->XilanhTool3On();
		break;
	case 3:
		pDoc->XilanhTool4On();
		break;
	default:
		break;
	}
}


void TeachDlg::ClickToolrobotOn3()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	int std = m_ActionVaccumRobot.GetCurSel();
	switch (std)
	{
	case 0:
		pDoc->VaccumTool1On();
		break;
	case 1:
		pDoc->VaccumTool2On();
		break;
	case 2:
		pDoc->VaccumTool3On();
		break;
	case 3:
		pDoc->VaccumTool4On();
		break;
	case 4:
		pDoc->VaccumTrayRobotOn();
		break;
	case 5:
		pDoc->XilanhAlineOn();
		break;
	default:
		break;
	}
}


void TeachDlg::ClickToolrobotOn4()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	int std = m_ActionVaccumRobot.GetCurSel();
	switch (std)
	{
	case 0:
		pDoc->VaccumTool1Off();
		break;
	case 1:
		pDoc->VaccumTool2Off();
		break;
	case 2:
		pDoc->VaccumTool3Off();
		break;
	case 3:
		pDoc->VaccumTool4Off();
		break;
	case 4:
		pDoc->VaccumTrayRobotOff();
		break;
	case 5:
		pDoc->XilanhAlineOff();
		break;
	default:
		break;
	}
}


void TeachDlg::ClickTestVisionTool1()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	
	CString m_ViewResulVisionTool1;
	if (!pDoc->functionResult(pDoc->Dx1, pDoc->Dy1, pDoc->Dr1, 1, 0))
	{
		AfxMessageBox("Khong bat duoc doi tuong");
	}
	m_ViewResulVisionTool1.Format("Dx = %lf ,Dy = %lf, Dr = %lf", pDoc->Dx1, pDoc->Dy1, pDoc->Dr1);
	SetDlgItemTextA(IDC_RESULT_VISION_TOOL1, m_ViewResulVisionTool1);
}


void TeachDlg::ClickTestVisionTool2()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	if (!pDoc->functionResult(pDoc->Dx2 ,pDoc->Dy2, pDoc->Dr2, 1, 0))
	{
		AfxMessageBox("Khong bat duoc doi tuong");
	}
	CString m_ViewResulVisionTool2;
	m_ViewResulVisionTool2.Format("Dx = %lf ,Dy = %lf, Dr = %lf", pDoc->Dx2, pDoc->Dy2, pDoc->Dr2);
	SetDlgItemTextA(IDC_RESULT_VISION_TOOL2, m_ViewResulVisionTool2);
}


void TeachDlg::ClickRobotUp()
{
	SelectZ[0] = true;
	SelectZ[1] = false;
	SelectZ[2] = false;

	m_ViewRobotUpMediumDown[0].SetBackColor(RGB(192, 0, 0));//Mau do
	m_ViewRobotUpMediumDown[1].SetBackColor(RGB(0, 192, 0));//Mau xanh la cay
	m_ViewRobotUpMediumDown[2].SetBackColor(RGB(0, 192, 0));//Mau xanh la cay
	
}


void TeachDlg::ClickRobotMedium()
{
	SelectZ[0] = false;
	SelectZ[1] = true;
	SelectZ[2] = false;

	m_ViewRobotUpMediumDown[0].SetBackColor(RGB(0, 192, 0));
	m_ViewRobotUpMediumDown[1].SetBackColor(RGB(192, 0, 0)); 
	m_ViewRobotUpMediumDown[2].SetBackColor(RGB(0, 192, 0));
}


void TeachDlg::ClickRobotLow()
{
	SelectZ[0] = false;
	SelectZ[1] = false;
	SelectZ[2] = true;

	m_ViewRobotUpMediumDown[0].SetBackColor(RGB(0, 192, 0));
	m_ViewRobotUpMediumDown[1].SetBackColor(RGB(0, 192, 0));
	m_ViewRobotUpMediumDown[2].SetBackColor(RGB(192, 0, 0));
}






