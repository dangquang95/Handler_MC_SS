// VisionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "VisionDlg.h"
#include "afxdialogex.h"



// VisionDlg dialog

IMPLEMENT_DYNAMIC(VisionDlg, CDialogEx)
CHandlerMCDoc * pDoc;

VisionDlg::VisionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION, pParent)
{
	
	pDoc = (CHandlerMCDoc*)(((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetActiveDocument());
	
}


VisionDlg::~VisionDlg()
{
	b_showImage = FALSE;
	Sleep(100);

	delete m_vision;
	delete m_savedata;
	
}

void VisionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_INFORMATON, lst_information);
	/*DDX_Control(pDX, IDC_EDT_MIN_WIDTH, edt_min_width);
	DDX_Control(pDX, IDC_EDT_MAX_WIDTH, edt_max_width);
	DDX_Control(pDX, IDC_EDT_MIN_HEIGHT, edt_min_height);
	DDX_Control(pDX, IDC_EDT_MAX_HEIGHT, edt_max_height);

	DDX_Control(pDX, IDC_BTN_APPLY, btn_apply);
	DDX_Control(pDX, IDC_BTN_LOADPARMA, btn_loadparameter);
	DDX_Control(pDX, IDC_BTN_START, btn_start);
	DDX_Control(pDX, IDC_BTN_PLAY, btn_play);
	DDX_Control(pDX, IDC_BTN_STOP, btn_stop);
	DDX_Control(pDX, IDC_BTN_GRAB, btn_grab);
	DDX_Control(pDX, IDC_BTN_SAVEPARA, btn_savepara);
	DDX_Control(pDX, IDC_CHECK_PROCESS, check_process);
	DDX_Check(pDX, IDC_RAD_TOOL_1, rad_tool_1);
	DDX_Check(pDX, IDC_RAD_TOOL_2, rad_tool_2);

	DDX_Control(pDX, IDC_EDT_RATE, edt_rate);
	DDX_Control(pDX, IDC_CHECK_RATE, check_rate);
	DDX_Control(pDX, IDC_EDT_OFFSET_X, edt_offset_x);
	DDX_Control(pDX, IDC_EDT_OFFSET_Y, edt_offset_y);
	DDX_Control(pDX, IDC_EDT_OFFSET_ANGLE, edt_offset_angle);
	DDX_Control(pDX, IDC_EDT_OFFSET_Y2, edt_offset_y2);
	DDX_Control(pDX, IDC_EDT_OFFSET_X2, edt_offset_x2);
	DDX_Control(pDX, IDC_CHECK_BLUR, check_blur);
	DDX_Control(pDX, IDC_EDT_KSIZE_TOOL_1, edt_kSize_tool_1);
	DDX_Control(pDX, IDC_EDT_KSIZE_TOOL_2, edt_kSize_tool_2);
	DDX_Control(pDX, IDC_EDT_THRESHOLD_TOOL_1, edt_threshoold_tool_1);
	DDX_Control(pDX, IDC_EDT_THRESHOLD_TOOL_2, edt_threshold_tool_2);
	DDX_Control(pDX, IDC_EDT_MORSIZE_TOOL_1, edt_morSize_tool_1);
	DDX_Control(pDX, IDC_EDT_MORSIZE_TOOL_2, edt_morSize_tool_2);
	DDX_Control(pDX, IDC_CHECK_APPLY_MORPHOLOGY, check_apply_morphology);
	DDX_Control(pDX, IDC_EDT_MINAREA, edt_minArea);
	DDX_Control(pDX, IDC_EDT_MAXAREA, edt_maxArea);
	DDX_Control(pDX, IDC_CHECK_REMOVE_NOISE, check_remove_noise);
	DDX_Control(pDX, IDC_CHECK2, check_threshold);
	DDX_Control(pDX, IDC_EDT_OFFSET_ANGLE_2, edt_angle_tool_2);*/

	DDX_Control(pDX, IDC_PANEL, mPanel);
}


BEGIN_MESSAGE_MAP(VisionDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &VisionDlg::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_BTN_START, &VisionDlg::OnBnClickedBtnStart)
//	ON_BN_CLICKED(IDC_BTN_APPLY, &VisionDlg::OnBnClickedBtnApply)
//	ON_BN_CLICKED(IDC_BTN_PLAY, &VisionDlg::OnBnClickedBtnPlay)
//	ON_BN_CLICKED(IDC_BTN_STOP, &VisionDlg::OnBnClickedBtnStop)
//	ON_BN_CLICKED(IDC_BTN_GRAB, &VisionDlg::OnBnClickedBtnGrab)
	ON_BN_CLICKED(IDC_BTN_LOADPARMA, &VisionDlg::OnBnClickedBtnLoadparma)
	ON_BN_CLICKED(IDC_BTN_SAVEPARA, &VisionDlg::OnBnClickedBtnSavepara)
ON_BN_CLICKED(IDC_RAD_TOOL_1, &VisionDlg::OnBnClickedRadTool1)
ON_BN_CLICKED(IDC_RAD_TOOL_2, &VisionDlg::OnBnClickedRadTool2)
//ON_BN_CLICKED(IDC_BTN_GRAB2, &VisionDlg::OnBnClickedBtnGrab2)
ON_BN_CLICKED(IDC_BTN_LOAD, &VisionDlg::OnBnClickedBtnLoad)
END_MESSAGE_MAP()


// VisionDlg message handlers
BEGIN_EVENTSINK_MAP(VisionDlg, CDialogEx)
	ON_EVENT(VisionDlg, IDB_EXIT1, DISPID_CLICK, VisionDlg::ClickExit1, VTS_NONE)
	ON_EVENT(VisionDlg, IDB_MOVE_VISION_TOOL1, DISPID_CLICK, VisionDlg::ClickMoveVisionTool1, VTS_NONE)
	ON_EVENT(VisionDlg, IDB_MOVE_VISION_TOOL2, DISPID_CLICK, VisionDlg::ClickMoveVisionTool2, VTS_NONE)
	ON_EVENT(VisionDlg, IDB_SAVE, DISPID_CLICK, VisionDlg::ClickSave, VTS_NONE)
END_EVENTSINK_MAP()


void VisionDlg::ClickExit1()
{
	b_showImage = FALSE;
	KillTimer(1);
	CDialog::OnCancel();
}

BOOL VisionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	contPlay = 0;
	//display image
	m_pDlgMainViewStaticDC = GetDlgItem(IDC_STATIC)->GetDC();
	GetDlgItem(IDC_STATIC)->GetClientRect(&m_DlgMainViewRect);

	m_vision = new appVision();

	//load data
	m_savedata = new saveDatatsystem();


	//the first run
	infor = _T("Program ready");
	information(infor);

	LoadParameters();
	icurTool = TOOL_1;
	mPanel.SetStretchToScreen();
	mPanel.SetDisplayCursor(TRUE, _T("(X,Y)"));

	mPanel.SetUseRectTracker(TRUE);
	mPanel.UpdateDisplay();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void VisionDlg::ClickMoveVisionTool1()
{
	pDoc->SendDataEthernet(pDoc->CmRunRobotVisionTool1);
}


void VisionDlg::ClickMoveVisionTool2()
{
	pDoc->SendDataEthernet(pDoc->CmRunRobotVisionTool2);
}


void VisionDlg::OnBnClickedButton1()
{
	CString m_data;
	GetDlgItemText(IDC_GETDATATEST, m_data);

	pDoc->m_datagettest = m_data;
}


//void VisionDlg::OnBnClickedBtnStart()
//{
//	countResult += 1;
//	UpdateData(TRUE);
//	CString strTool = _T("Tool:");
//
//	double dx, dy;
//	double dAngle;
//	int tool_1 = Data_system.d_rad_tool_1;
//	int tool_2 = Data_system.d_rad_tool_2;
//
//	if (tool_1 == 1) {
//		strTool = _T("Tool 1");
//	}
//	if (tool_2 == 1) {
//		strTool = _T("Tool 2");
//	}
//	
//	if (pDoc->functionResult(dx, dy, dAngle, tool_1, tool_2) == TRUE)
//	{
//		CString strdx, strdy, strdAngle, strCount;
//		strCount.Format(_T("%d"), countResult);
//		strdx.Format(_T("%f"), dx);
//		strdy.Format(_T("%f"), dy);
//		strdAngle.Format(_T("%f"), dAngle);
//
//		CString strResult;
//		strResult = strTool + _T(": ") + _T("Stt: ") + strCount + _T(": ") + _T("dx: ") + strdx + _T("; ") + _T("dy: ") 
//			       + strdy + _T("; ") + _T("dangle: ") + strdAngle;
//
//		CString strdelta_dx, strdelta_dy, strdelta_pixcel, strAngleCurrent;
//		strdelta_dx.Format(_T("%.3f"), pDoc->pointCurrent.x);
//		strdelta_dy.Format(_T("%.3f"), pDoc->pointCurrent.y);
//		strAngleCurrent.Format(_T("%.3f"), pDoc->angleCurrent);
//
//		strdelta_pixcel = strTool + _T(": ") + _T("Stt: ") + strCount + _T(" ") + _T("Curren X: ") + strdelta_dx + _T("; ")
//			+ _T("Curren Y: ") + strdelta_dy + _T("; ") + _T("Angle Current: ") + strAngleCurrent;
//
//		
//		lst_information.AddString(strResult);
//		lst_information.AddString(strdelta_pixcel);
//		UpdateData(FALSE);
//	}
//	else {
//		CString strFunctionResultFail = _T("Has not object!");
//		lst_information.AddString(strFunctionResultFail);
//		UpdateData(FALSE);
//	}
//}


//void VisionDlg::OnBnClickedBtnApply()
//{
//	contPlay = 0;
//	b_showImage = FALSE;
//	CString strTool = _T("Tool:");
//	CString strApp = _T("Button Apply");
//	double deltaDx, deltaDy;
//	double deltadAngle;
//	
//	if (pDoc->resultApply(deltaDx, deltaDy, deltadAngle, tool_1, tool_2) == TRUE)
//	{
//		if (tool_1 == 1 && tool_2 != 1) {
//			Data_system.d_Point_Tool_1_X	= deltaDx;
//			Data_system.d_Point_Tool_1_Y	= deltaDy;
//			Data_system.d_dAgnle_Tool_1		= deltadAngle;
//
//			pDoc->pointSampleTool_1.x		= deltaDx;
//			pDoc->pointSampleTool_1.y		= deltaDy;
//			pDoc->angleSampleTool_1			= deltadAngle;
//
//			CString strdx, strdy, strdAngle;
//			strdx.Format(_T("%f"), deltaDx);
//			strdy.Format(_T("%f"), deltaDy);
//			strdAngle.Format(_T("%f"), deltadAngle);
//			strTool = _T("Tool 1:");
//
//			CString strResult;
//			strResult = strApp + _T(" : ");
//			strResult += strTool + _T(" ");
//			strResult += _T("dx: ") + strdx + _T("; ");
//			strResult += _T("dy: ") + strdy + _T("; ");
//			strResult += _T("dangle: ") + strdAngle;
//			lst_information.AddString(strResult);
//			UpdateData(FALSE);
//		}
//		if (tool_1 != 1 && tool_2 == 1) {
//			Data_system.d_Point_Tool_2_X	= deltaDx;
//			Data_system.d_Point_Tool_2_Y	= deltaDy;
//			Data_system.d_dAgnle_Tool_2		= deltadAngle;
//
//			pDoc->pointSampleTool_2.x	= deltaDx;
//			pDoc->pointSampleTool_2.y	= deltaDy;
//			pDoc->angleSampleTool_2		= deltadAngle;
//
//			CString strdx, strdy, strdAngle;
//			strdx.Format(_T("%f"), deltaDx);
//			strdy.Format(_T("%f"), deltaDy);
//			strdAngle.Format(_T("%f"), deltadAngle);
//			strTool = _T("Tool 2:");
//
//			CString strResult;
//			strResult = strApp + _T(" : ");
//			strResult += strTool + _T(" ");
//			strResult += _T("dx: ") + strdx + _T("; ");
//			strResult += _T("dy: ") + strdy + _T("; ");
//			strResult += _T("dangle: ") + strdAngle;
//			lst_information.AddString(strResult);
//			UpdateData(FALSE);
//		}
//	}
//}
BOOL VisionDlg::GetDataWidget(int iTool)
{
	VisionPara vTemp;
	vTemp.iThresh = GetDlgItemInt(IDC_EDT_THRESHOLD);
	vTemp.iBlur = GetDlgItemInt(IDC_EDT_BLUR);
	vTemp.iMor = GetDlgItemInt(IDC_EDT_MORSIZE);
	vTemp.objWidthMin =	GetDlgItemInt(IDC_EDT_MIN_WIDTH);
	vTemp.objWidthMax =	GetDlgItemInt(IDC_EDT_MAX_WIDTH);
	vTemp.objHeightMin =	GetDlgItemInt(IDC_EDT_MIN_HEIGHT);
	vTemp.objHeightMax =	GetDlgItemInt(IDC_EDT_MAX_HEIGHT);
	vTemp.objAreaMin =	GetDlgItemInt(IDC_EDT_MINAREA);
	vTemp.objAreaMax =	GetDlgItemInt(IDC_EDT_MAXAREA);

	//CString thestring("13.37");
	//master point tool1
	CString str;
	GetDlgItemText(IDC_EDT_MASTER_X1, str);	
	refPoint[TOOL_1].msPoint.x = atof(str);
	GetDlgItemText(IDC_EDT_MASTER_Y1, str);
	refPoint[TOOL_1].msPoint.y = atof(str);
	GetDlgItemText(IDC_EDT_MASTER_ANPHA1, str);
	refPoint[TOOL_1].alpha = atof(str);

	//master poit tool 2
	GetDlgItemText(IDC_EDT_MASTER_X2, str);
	refPoint[TOOL_2].msPoint.x = atof(str);
	GetDlgItemText(IDC_EDT_MASTER_Y2, str);
	refPoint[TOOL_2].msPoint.y = atof(str);
	GetDlgItemText(IDC_EDT_MASTER_ANPHA2, str);
	refPoint[TOOL_2].alpha = atof(str);

	
	switch (iTool)
	{
	case TOOL_1:
		visionPara[TOOL_1] = vTemp;
		break;
	case TOOL_2:
		visionPara[TOOL_2] = vTemp;
		break;
	default:
		break;
	}

	return TRUE;
}

BOOL VisionDlg::SetDataWidget(int itool)
{
	CString str;
	str.Format("%.2f", refPoint[TOOL_1].msPoint.x);
	SetDlgItemText(IDC_EDT_MASTER_X1, str);
	str.Format("%.2f", refPoint[TOOL_1].msPoint.y);
	SetDlgItemText(IDC_EDT_MASTER_Y1, str);
	str.Format("%.2f", refPoint[TOOL_1].alpha);
	SetDlgItemText(IDC_EDT_MASTER_ANPHA1, str);

	str.Format("%.2f", refPoint[TOOL_2].msPoint.x);
	SetDlgItemText(IDC_EDT_MASTER_X2, str);
	str.Format("%.2f", refPoint[TOOL_2].msPoint.y);
	SetDlgItemText(IDC_EDT_MASTER_Y2, str);
	str.Format("%.2f", refPoint[TOOL_2].alpha);
	SetDlgItemText(IDC_EDT_MASTER_ANPHA2, str);

	VisionPara vTemp;
	switch (itool)
	{
	case TOOL_1:
		vTemp = visionPara[TOOL_1];
		break;
	case TOOL_2:
		vTemp = visionPara[TOOL_2];
		break;
	default:
		break;
	}

	SetDlgItemInt(IDC_EDT_BLUR, vTemp.iBlur);
	SetDlgItemInt(IDC_EDT_THRESHOLD, vTemp.iThresh);
	SetDlgItemInt(IDC_EDT_MORSIZE, vTemp.iMor);
	SetDlgItemInt(IDC_EDT_MIN_WIDTH, vTemp.objWidthMin);
	SetDlgItemInt(IDC_EDT_MAX_WIDTH, vTemp.objWidthMax);
	SetDlgItemInt(IDC_EDT_MIN_HEIGHT, vTemp.objHeightMin);
	SetDlgItemInt(IDC_EDT_MAX_HEIGHT, vTemp.objWidthMax);
	SetDlgItemInt(IDC_EDT_MINAREA, vTemp.objAreaMin);
	SetDlgItemInt(IDC_EDT_MAXAREA, vTemp.objAreaMax);

	return true;
}

void VisionDlg::showProcessImage()
{

	appVision vs;
	Mat mInput;
	Mat  mOutput;
	Mat mShow;
	cvtColor(mShow, mShow, CV_GRAY2BGR);
	VisionPara vPara = visionPara[icurTool];

	double  dX, dY;
	float alpha;
	Point2f points[4];
	RotatedRect  r;
	vs.ShowAlignTest(pDoc->image, mOutput, vPara, dX, dY, alpha, r);
	r.points(points);
	for (int i = 0; i < 4; i++) {
		line(mShow, points[i], points[(i + 1) % 4], Scalar(0, 255, 0), 5);

	}
	CString str;
	str.Format("dX: %.2f, dY: %.2f, alpha: %.2f", r.center.x, r.center.y, alpha);
	putText(mShow, string(str), r.center, FONT_HERSHEY_SIMPLEX, 2, Scalar(200, 0, 0), 8);

	m_vision->displayImage(mShow, m_pDlgMainViewStaticDC, m_DlgMainViewRect);
	return;
}
void VisionDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (b_showImage == TRUE || b_UpdateData == TRUE)
	{
		case 1:
			if (b_showImage == TRUE) {
				KillTimer(1);
				//showProcessImage();
				SetTimer(1, 100, NULL);
			}
		
	}

	CDialogEx::OnTimer(nIDEvent);
}


//void VisionDlg::OnBnClickedBtnPlay()
//{
//	mPattern = OpenImage();
//	DisplayImage(mPanel, mPattern);
//	return;
//	/*b_showImage = TRUE;
//	SetTimer(1, 100, NULL);*/
//	if (contPlay == 0) {
//		b_showImage = TRUE;
//		AfxBeginThread(ThreadCamera, this);
//	}
//	
//	contPlay = 1;
//
//}
UINT VisionDlg::ThreadCamera(VOID * pParam)
{
	VisionDlg* pthis = (VisionDlg*)pParam;
	while (pthis->b_showImage)
	{
		
		pthis->showProcessImage();
		Sleep(5);

	}
	return 0;
}


//void VisionDlg::OnBnClickedBtnStop()
//{
//	contPlay = 0;
//	b_showImage = FALSE;
//	//KillTimer(1);
//}


//void VisionDlg::OnBnClickedBtnGrab()
//{
//	b_showImage = FALSE;
//	CString grabimage;
//	cv::Mat imageR, imageDraw, imageBox;
//	//imageR = m_vision->RotationImage(image);
//	imageR = pDoc->image.clone();
//	imageDraw = m_vision->drawImage(imageR);
//	try {
//		if (imageDraw.empty())
//		{
//			grabimage = _T("Do not have image!");
//			AfxMessageBox(grabimage);
//		}
//		else
//		{
//			cv::imwrite("Picture/checkcam.jpg", imageDraw);
//			grabimage = _T("Have been grab image!");
//			AfxMessageBox(grabimage);
//			m_vision->displayImage(imageDraw, m_pDlgMainViewStaticDC, m_DlgMainViewRect);
//		}
//	}
//	catch (...) {
//
//	}
//}

void VisionDlg::OnBnClickedBtnLoadparma()
{
	
	if (loadParameter(_T("Parameter\\System.dat"), Data_system) == TRUE)
	{
		CString loadPara;
		loadPara = _T("Have been load data!");
		AfxMessageBox(loadPara);
	}
	else
	{
		CString loadPara;
		loadPara = _T("Have not load data!");
		AfxMessageBox(loadPara);
	}
}



void VisionDlg::OnBnClickedBtnSavepara()
{
	/*if (GetDataWidget() == TRUE) {
		CString savePara;
		savePara = _T("Have been save data!");
		AfxMessageBox(savePara);
	}
	else {
		CString savePara;
		savePara = _T("Have not save data!");
		AfxMessageBox(savePara);
	}*/
}

cv::Mat VisionDlg::OpenImage(void)
{
	cv::Mat ImgLoad;

	static TCHAR szFilter[] = _T("Image Files | *.bmp; *.tiff; *.jpg; *.PNG; *.* ||");
	CFileDialog dlg(TRUE, _T("*.bmp"), _T(""), OFN_OVERWRITEPROMPT, szFilter);
	CString sPath, sFileName;

	if (dlg.DoModal() == IDOK)
	{
		sPath = dlg.GetFolderPath();
		sFileName = dlg.GetFileName();

		sPath = sPath + _T("\\") + sFileName;

	}
	try
	{
		ImgLoad = cv::imread(std::string(sPath), CV_LOAD_IMAGE_UNCHANGED);
	}
	catch (cv::Exception e)
	{
		TRACE(e.what());
	}

	return ImgLoad;
}



void VisionDlg::information(CString information)
{
	lst_information.AddString(information);
	UpdateData(FALSE);
}


BOOL VisionDlg::loadParameter(CString strPath, DataSystem & data_system)
{

	if (m_savedata->loadParameter(_T("Parameter\\System.dat"), Data_system) == TRUE)
	{
		//Blur
		CString strkSize_tool_1 = _T("");
		strkSize_tool_1.Format(_T("%d"), data_system.d_kSize_Tool_1);
		edt_kSize_tool_1.SetWindowText(strkSize_tool_1);
		

		CString strkSize_tool_2 = _T("");
		strkSize_tool_2.Format(_T("%d"), data_system.d_kSize_Tool_2);
		edt_kSize_tool_2.SetWindowText(strkSize_tool_2);

		//Threshold
		CString strthreshold_tool_1 = _T("");
		strthreshold_tool_1.Format(_T("%f"), data_system.d_threshold_tool_1);
		edt_threshoold_tool_1.SetWindowText(strthreshold_tool_1);

		CString strthreshold_tool_2 = _T("");
		strthreshold_tool_2.Format(_T("%f"), data_system.d_threshold_tool_2);
		edt_threshold_tool_2.SetWindowText(strthreshold_tool_2);

		//Offset point
		CString stroffset_x = _T("");
		stroffset_x.Format(_T("%.5f"), data_system.d_Point_Tool_1_X);
		edt_offset_x.SetWindowText(stroffset_x);

		CString stroffset_y = _T("");
		stroffset_y.Format(_T("%.5f"), data_system.d_Point_Tool_1_Y);
		edt_offset_y.SetWindowText(stroffset_y);

		CString stroffset_angle = _T("");
		stroffset_angle.Format(_T("%.3f"), data_system.d_dAgnle_Tool_1);
		edt_offset_angle.SetWindowText(stroffset_angle);

		CString stroffset_x2 = _T("");
		stroffset_x2.Format(_T("%.3f"), data_system.d_Point_Tool_2_X);
		edt_offset_x2.SetWindowText(stroffset_x2);

		CString stroffset_y2 = _T("");
		stroffset_y2.Format(_T("%.3f"), data_system.d_Point_Tool_2_Y);
		edt_offset_y2.SetWindowText(stroffset_y2);

		CString stroffset_angle2 = _T("");
		stroffset_angle2.Format(_T("%.3f"), data_system.d_dAgnle_Tool_2);
		edt_angle_tool_2.SetWindowText(stroffset_angle2);


		//Morphology
		CString strmorSize_tool_1 = _T("");
		strmorSize_tool_1.Format(_T("%d"), data_system.d_morSize_tool_1);
		edt_morSize_tool_1.SetWindowText(strmorSize_tool_1);

		CString strmorSize_tool_2 = _T("");
		strmorSize_tool_2.Format(_T("%d"), data_system.d_morSize_tool_2);
		edt_morSize_tool_2.SetWindowText(strmorSize_tool_2);

		//Remove noise
		CString strminArea = _T("");
		strminArea.Format(_T("%d"), data_system.d_minArea);
		edt_minArea.SetWindowText(strminArea);

		CString strmaxArea = _T("");
		strmaxArea.Format(_T("%d"), data_system.d_maxArea);
		edt_maxArea.SetWindowText(strmaxArea);

		CString strminWidth = _T("");
		strminWidth.Format(_T("%d"), data_system.d_minWidth);
		edt_min_width.SetWindowText(strminWidth);

		CString strmaxWidth = _T("");
		strmaxWidth.Format(_T("%d"), data_system.d_maxWidth);
		edt_max_width.SetWindowText(strmaxWidth);

		CString strminHeight = _T("");
		strminHeight.Format(_T("%d"), data_system.d_minHeight);
		edt_min_height.SetWindowText(strminHeight);

		CString strmaxHeight = _T("");
		strmaxHeight.Format(_T("%d"), data_system.d_maxHeight);
		edt_max_height.SetWindowText(strmaxHeight);

		CString strRate = _T("");
		strRate.Format(_T("%f"), data_system.d_rate);
		edt_rate.SetWindowText(strRate);

		//Check blur and thresh
		check_blur.SetCheck(data_system.d_check_blur);
		check_threshold.SetCheck(data_system.d_check_thresh);
		
		//Check remove noise and morphology
		check_apply_morphology.SetCheck(data_system.d_Check_Apply_Morphology);
		check_remove_noise.SetCheck(data_system.d_check_remove_noise);

		//rad remove noise
		rad_erode = data_system.d_erode;
		rad_dilate = data_system.d_dilate;
		rad_erode_dilate = data_system.d_e_dilate;
		rad_dilate_erode = data_system.d_d_erode;
		check_process.SetCheck(data_system.d_check_process);

		//Rad tool
		rad_tool_1	= Data_system.d_rad_tool_1;
		tool_1		= Data_system.d_rad_tool_1;
		rad_tool_2	= Data_system.d_rad_tool_2;
		tool_2		= Data_system.d_rad_tool_2;
		
		UpdateData(FALSE);

	}
	else {
		CString loadPara;
		loadPara = _T("Have not load data!");
		AfxMessageBox(loadPara);
		return FALSE;
	}


	return TRUE;
}

BOOL VisionDlg::DestroyWindow()
{
	b_showImage = FALSE;
	Sleep(30);
	countResult = 0;
	
	KillTimer(1); 
	return CDialogEx::DestroyWindow();
}


void VisionDlg::ClickSave()
{
	// TODO: Add your message handler code here
	GetDataWidget(icurTool);
	SaveParameters();
}


//void VisionDlg::OnBnClickedBtnGrab2()
//{
//	// TODO: Add your control notification handler code here
//}


void VisionDlg::OnBnClickedRadTool1()
{
	// TODO: Add your control notification handler code here
	icurTool = TOOL_1;
	SetDataWidget(icurTool);
}


void VisionDlg::OnBnClickedRadTool2()
{
	// TODO: Add your control notification handler code here
	icurTool = TOOL_2;
	SetDataWidget(icurTool);
}
BOOL VisionDlg::SaveParameters()
{

	CXmlDocumentWrapper xmlDoc;
	if (!xmlDoc.LoadXML(_T("<General></General>")))
	{
		AfxMessageBox(_T("File setting General error!"));
		return FALSE;
	}

	CXmlNodeWrapper nodeManager(xmlDoc.AsNode());

	nodeManager.SetValue("iThresh1", visionPara[TOOL_1].iThresh);
	nodeManager.SetValue("iBlur1", visionPara[TOOL_1].iBlur);
	nodeManager.SetValue("iSize1", visionPara[TOOL_1].iSize);
	nodeManager.SetValue("objHeightMin1", visionPara[TOOL_1].objHeightMin);
	nodeManager.SetValue("objHeightMax1", visionPara[TOOL_1].objHeightMax);
	nodeManager.SetValue("objWidthMin1", visionPara[TOOL_1].objWidthMin);
	nodeManager.SetValue("objWidthMax1", visionPara[TOOL_1].objWidthMax);
	nodeManager.SetValue("objAreaMin1", visionPara[TOOL_1].objAreaMin);
	nodeManager.SetValue("objAreaMax1", visionPara[TOOL_1].objAreaMax);
	nodeManager.SetValue("iMor1", visionPara[TOOL_1].iMor);

	nodeManager.SetValue("iThresh2", visionPara[TOOL_2].iThresh);
	nodeManager.SetValue("iBlur2", visionPara[TOOL_2].iBlur);
	nodeManager.SetValue("iSize2", visionPara[TOOL_2].iSize);
	nodeManager.SetValue("objHeightMin2", visionPara[TOOL_2].objHeightMin);
	nodeManager.SetValue("objHeightMax2", visionPara[TOOL_2].objHeightMax);
	nodeManager.SetValue("objWidthMin2", visionPara[TOOL_2].objWidthMin);
	nodeManager.SetValue("objWidthMax2", visionPara[TOOL_2].objWidthMax);
	nodeManager.SetValue("objAreaMin2", visionPara[TOOL_2].objAreaMin);
	nodeManager.SetValue("objAreaMax2", visionPara[TOOL_2].objAreaMax);
	nodeManager.SetValue("iMor2", visionPara[TOOL_2].iMor);

	nodeManager.SetValue("msPoint_x1", refPoint[TOOL_1].msPoint.x);
	nodeManager.SetValue("msPoint_y1", refPoint[TOOL_1].msPoint.y);
	nodeManager.SetValue("alpha1", refPoint[TOOL_1].alpha);

	nodeManager.SetValue("msPoint_x2", refPoint[TOOL_2].msPoint.x);
	nodeManager.SetValue("msPoint_y2", refPoint[TOOL_2].msPoint.y);
	nodeManager.SetValue("alpha2", refPoint[TOOL_2].alpha);

	

	if (xmlDoc.Save(PATH_GENERAL_SETTING))
	{
		LoadParameters();
		return TRUE;
	}
	else
		return FALSE;
}
BOOL VisionDlg::LoadParameters()
{

	CXmlDocumentWrapper xmlDoc;
	if (!xmlDoc.Load(PATH_GENERAL_SETTING))
	{
		AfxMessageBox(_T("Load file Setting General.xml error!"));
		return FALSE;
	}

	CXmlNodeWrapper nodeManager(xmlDoc.AsNode());


	visionPara[TOOL_1].iThresh = nodeManager.GetValueInt("iThresh1");
	visionPara[TOOL_1].iBlur = nodeManager.GetValueInt("iBlur1");
	visionPara[TOOL_1].iSize = nodeManager.GetValueInt("iSize1");
	visionPara[TOOL_1].iMor = nodeManager.GetValueDouble("iMor1");
	visionPara[TOOL_1].objHeightMin = nodeManager.GetValueInt("objHeightMin1");
	visionPara[TOOL_1].objHeightMax = nodeManager.GetValueInt("objHeightMax1");
	visionPara[TOOL_1].objWidthMin = nodeManager.GetValueInt("objWidthMin1");
	visionPara[TOOL_1].objWidthMax = nodeManager.GetValueInt("objWidthMax1");
	visionPara[TOOL_1].objAreaMin = nodeManager.GetValueInt("objAreaMin1");
	visionPara[TOOL_1].objAreaMax = nodeManager.GetValueInt("objAreaMax1");

	visionPara[TOOL_2].iThresh = nodeManager.GetValueInt("iThresh2");
	visionPara[TOOL_2].iBlur = nodeManager.GetValueInt("iBlur2");
	visionPara[TOOL_2].iSize = nodeManager.GetValueInt("iSize2");
	visionPara[TOOL_2].iMor = nodeManager.GetValueDouble("iMor2");
	visionPara[TOOL_2].objHeightMin = nodeManager.GetValueInt("objHeightMin2");
	visionPara[TOOL_2].objHeightMax = nodeManager.GetValueInt("objHeightMax2");
	visionPara[TOOL_2].objWidthMin = nodeManager.GetValueInt("objWidthMin2");
	visionPara[TOOL_2].objWidthMax = nodeManager.GetValueInt("objWidthMax2");
	visionPara[TOOL_2].objAreaMin = nodeManager.GetValueInt("objAreaMin2");
	visionPara[TOOL_2].objAreaMax = nodeManager.GetValueInt("objAreaMax2");

	refPoint[TOOL_1].msPoint.x = nodeManager.GetValueInt("msPoint_x1");
	refPoint[TOOL_1].msPoint.y = nodeManager.GetValueInt("msPoint_y1");
	refPoint[TOOL_1].alpha = nodeManager.GetValueInt("alpha1");

	refPoint[TOOL_2].msPoint.x = nodeManager.GetValueInt("msPoint_x2");
	refPoint[TOOL_2].msPoint.y = nodeManager.GetValueInt("msPoint_y2");
	refPoint[TOOL_2].alpha = nodeManager.GetValueInt("alpha2");

	SetDataWidget(icurTool);

	return TRUE;

}

//void VisionDlg::OnBnClickedBtnGrab2()
//{
//	// TODO: Add your control notification handler code here
//	mPattern = OpenImage();
//	DisplayImage(mPanel, mPattern);
//	
//}
void VisionDlg::DisplayImage(im::CImAdvPanel& panel, cv::Mat& img)
{
	cv::Mat dispImg;
	int w = img.cols;
	int h = img.rows;
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
			cv::resize(dispImg, dispImg, cv::Size(w, h));
		}
		panel.SetImage(dispImg.data, (int)dispImg.total(), dispImg.cols, dispImg.rows, dispImg.channels());
		panel.UpdateDisplay();
	}
	catch (cv::Exception e)
	{
		TRACE("[Exception] UpdateImgPanel() %s", e.what());
	}

}

void VisionDlg::OnBnClickedBtnLoad()
{
	// TODO: Add your control notification handler code here
	mPattern = OpenImage();
	DisplayImage(mPanel, mPattern);
}
