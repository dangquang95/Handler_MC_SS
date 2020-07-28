
// HandlerMCDoc.cpp : implementation of the CHandlerMCDoc class
//BaN CHINH KHONG THAY DOI

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HandlerMC.h"
#endif

#include "HandlerMCDoc.h"

#include <propkey.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHandlerMCDoc

IMPLEMENT_DYNCREATE(CHandlerMCDoc, CDocument)

BEGIN_MESSAGE_MAP(CHandlerMCDoc, CDocument)
END_MESSAGE_MAP()

CHandlerMCDoc* g_this = NULL;


// CHandlerMCDoc construction/destruction

CHandlerMCDoc::CHandlerMCDoc()
{
	g_this = this;
	pcamOmron = nullptr;
}

CHandlerMCDoc::~CHandlerMCDoc()
{
	delete m_vision;
	if (pcamOmron) delete pcamOmron;
	delete m_savedata;
	delete m_client;
}

BOOL CHandlerMCDoc::OnNewDocument()
{
	//TA vision
	m_vision = new appVision();
	m_savedata = new saveDatatsystem();
	this->initializeVision();
	
	//--------------888------------
	if (!CDocument::OnNewDocument())
		return FALSE;
	//Setting COM Event
	ReadDataComEvent();
	InitComPhone(m_NumberComEvent, m_BaudRateEvent);
	//
	ReadDataModel();
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	ReadDataEthernet();
	//Init TCP
	ChoiceMethol = CaoHuy;
	switch (ChoiceMethol)
	{
	case CaoHuy:
		InitSocketCaoHuy(m_IpEthenet,m_PortServer);
		break;
	case DangQuang:
		InitSocket();
		break;
	default:
		break;
	}
	//Khoi tao card motion
	SetupInitiaization();
	ReadDataPointAxisZ();
	ReadDataPhone();
	ReadDataDelayVaccum();
	ReadDataDelayCylinder();
	PowerAirOn();
	StartThreadServo();
	ReadDataMotor();
	for (int i = 0; i < 4; i++)
	{
		m_ResultTestSocket[i] = 0;
		m_UnloadingLoading[i] = 0;
		if (m_DataTester[i].Action)
		{
			m_NumberTesterAct++;
		}

	}
	 VaccumSocket1Off();
     VaccumSocket2Off();
	 VaccumSocket3Off();
	 VaccumSocket4Off();

	// VaccumTool1RobotLoadingOff();
	 //VaccumTool2RobotLoadingOff();
	 //VaccumTool1RobotUnloadingOff();
	 //VaccumTool2RobotUnloadingOff();

	 XilanhTool1RobotLoadingOff();
	 XilanhTool2RobotLoadingOff();
	 XilanhTool1RobotUnloadingOff();
	 XilanhTool2RobotUnloadingOff();

	 XilanhAlineOff();
	return TRUE;
}
void CHandlerMCDoc::InitSocketCaoHuy(CString m_IP, int m_port)
{
	m_client = new GTCRobotCtrl2(m_IP, m_port);
	FlagConnectEthernet = m_client->Connect();
	if (!FlagConnectEthernet)
	{
		AfxMessageBox("Connect Ethernet Error");
	}
	else
	{
		AfxMessageBox("Connect Ethernet Success");
	}
}

void CHandlerMCDoc::DisConnectSocket()
{
	FlagConnectEthernet = m_client->Disconnect();
}

// CHandlerMCDoc serialization

void CHandlerMCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CHandlerMCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CHandlerMCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CHandlerMCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}



#endif // SHARED_HANDLERS

// CHandlerMCDoc diagnostics

#ifdef _DEBUG
void CHandlerMCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHandlerMCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Ethernet  commands

void CHandlerMCDoc::ReadDataEthernet()
{
	// TODO: Add your message handler code here
	CIniFile Input;
	Input.SetPath("DataSystem\\Ethernet.dat");// đường dẫn file. Nhớ phải dung 2 sẹc (\\).
	m_IpEthenet = Input.ReadString("Data", "IP", "None");
	m_PortServer = Input.ReadInt("Data", "Port", 0);

	if (m_IpEthenet == "None" || m_PortServer == 0)
	{
		AfxMessageBox("Loading data Socket error");
	}
	//Loading
	CmRunRobotLoadingTool1Up   = Input.ReadString("Data", "CmRunRobotLoadingTool1Up", "None");
	CmRunRobotLoadingTool2Up   = Input.ReadString("Data", "CmRunRobotLoadingTool2Up", "None");
	CmRunRobotLoadingTool1Down = Input.ReadString("Data", "CmRunRobotLoadingTool1Down", "None");
	CmRunRobotLoadingTool2Down = Input.ReadString("Data", "CmRunRobotLoadingTool2Down", "None");
	//Unloading tray NG left
	CmRunRobotUnloadingLeftTool3Up   = Input.ReadString("Data", "CmRunRobotUnloadingLeftTool3Up", "None");
	CmRunRobotUnloadingLeftTool4Up   = Input.ReadString("Data", "CmRunRobotUnloadingLeftTool4Up", "None");
	CmRunRobotUnloadingLeftTool3Down = Input.ReadString("Data", "CmRunRobotUnloadingLeftTool3Down", "None");
	CmRunRobotUnloadingLeftTool4Down = Input.ReadString("Data", "CmRunRobotUnloadingLeftTool4Down", "None");
	//Unloading tray NG Right
	CmRunRobotUnloadingRightTool3Up   = Input.ReadString("Data", "CmRunRobotUnloadingRightTool3Up", "None");
	CmRunRobotUnloadingRightTool4Up   = Input.ReadString("Data", "CmRunRobotUnloadingRightTool4Up", "None");
	CmRunRobotUnloadingRightTool3Down = Input.ReadString("Data", "CmRunRobotUnloadingRightTool3Down", "None");
	CmRunRobotUnloadingRightTool4Down = Input.ReadString("Data", "CmRunRobotUnloadingRightTool4Down", "None");
	//Unloading tray OK
	CmRunRobotUnloadingTrayOKTool3Up   = Input.ReadString("Data", "CmRunRobotUnloadingTrayOKTool3Up", "None");
	CmRunRobotUnloadingTrayOKTool4Up   = Input.ReadString("Data", "CmRunRobotUnloadingTrayOKTool4Up", "None");
	CmRunRobotUnloadingTrayOKTool3Down = Input.ReadString("Data", "CmRunRobotUnloadingTrayOKTool3Down", "None");
	CmRunRobotUnloadingTrayOKTool4Down = Input.ReadString("Data", "CmRunRobotUnloadingTrayOKTool4Down", "None");
	//Tool loading action socket
	CmRunRobotLoadingSocket1Tool1Up = Input.ReadString("Data", "CmRunRobotLoadingSocket1Tool1Up", "None");
	CmRunRobotLoadingSocket2Tool1Up = Input.ReadString("Data", "CmRunRobotLoadingSocket2Tool1Up", "None");
	CmRunRobotLoadingSocket3Tool1Up = Input.ReadString("Data", "CmRunRobotLoadingSocket3Tool1Up", "None");
	CmRunRobotLoadingSocket4Tool1Up = Input.ReadString("Data", "CmRunRobotLoadingSocket4Tool1Up", "None");

	CmRunRobotLoadingSocket1Tool1Down = Input.ReadString("Data", "CmRunRobotLoadingSocket1Tool1Down", "None");
	CmRunRobotLoadingSocket2Tool1Down = Input.ReadString("Data", "CmRunRobotLoadingSocket2Tool1Down", "None");
	CmRunRobotLoadingSocket3Tool1Down = Input.ReadString("Data", "CmRunRobotLoadingSocket3Tool1Down", "None");
	CmRunRobotLoadingSocket4Tool1Down = Input.ReadString("Data", "CmRunRobotLoadingSocket4Tool1Down", "None");


	CmRunRobotLoadingSocket1Tool2Up = Input.ReadString("Data", "CmRunRobotLoadingSocket1Tool2Up", "None");
	CmRunRobotLoadingSocket2Tool2Up = Input.ReadString("Data", "CmRunRobotLoadingSocket2Tool2Up", "None");
	CmRunRobotLoadingSocket3Tool2Up = Input.ReadString("Data", "CmRunRobotLoadingSocket3Tool2Up", "None");
	CmRunRobotLoadingSocket4Tool2Up = Input.ReadString("Data", "CmRunRobotLoadingSocket4Tool2Up", "None");

	CmRunRobotLoadingSocket1Tool2Down = Input.ReadString("Data", "CmRunRobotLoadingSocket1Tool2Down", "None");
	CmRunRobotLoadingSocket2Tool2Down = Input.ReadString("Data", "CmRunRobotLoadingSocket2Tool2Down", "None");
	CmRunRobotLoadingSocket3Tool2Down = Input.ReadString("Data", "CmRunRobotLoadingSocket3Tool2Down", "None");
	CmRunRobotLoadingSocket4Tool2Down = Input.ReadString("Data", "CmRunRobotLoadingSocket4Tool2Down", "None");
	
	//Tool Unloading action socket
	CmRunRobotUnloadingSocket1Tool3Up = Input.ReadString("Data", "CmRunRobotUnloadingSocket1Tool3Up", "None");
	CmRunRobotUnloadingSocket2Tool3Up = Input.ReadString("Data", "CmRunRobotUnloadingSocket2Tool3Up", "None");
	CmRunRobotUnloadingSocket3Tool3Up = Input.ReadString("Data", "CmRunRobotUnloadingSocket3Tool3Up", "None");
	CmRunRobotUnloadingSocket4Tool3Up = Input.ReadString("Data", "CmRunRobotUnloadingSocket4Tool3Up", "None");

	CmRunRobotUnloadingSocket1Tool3Down = Input.ReadString("Data", "CmRunRobotUnloadingSocket1Tool3Down", "None");
	CmRunRobotUnloadingSocket2Tool3Down = Input.ReadString("Data", "CmRunRobotUnloadingSocket2Tool3Down", "None");
	CmRunRobotUnloadingSocket3Tool3Down = Input.ReadString("Data", "CmRunRobotUnloadingSocket3Tool3Down", "None");
	CmRunRobotUnloadingSocket4Tool3Down = Input.ReadString("Data", "CmRunRobotUnloadingSocket4Tool3Down", "None");

	CmRunRobotUnloadingSocket1Tool4Up = Input.ReadString("Data", "CmRunRobotUnloadingSocket1Tool4Up", "None");
	CmRunRobotUnloadingSocket2Tool4Up = Input.ReadString("Data", "CmRunRobotUnloadingSocket2Tool4Up", "None");
	CmRunRobotUnloadingSocket3Tool4Up = Input.ReadString("Data", "CmRunRobotUnloadingSocket3Tool4Up", "None");
	CmRunRobotUnloadingSocket4Tool4Up = Input.ReadString("Data", "CmRunRobotUnloadingSocket4Tool4Up", "None");

	CmRunRobotUnloadingSocket1Tool4Down = Input.ReadString("Data", "CmRunRobotUnloadingSocket1Tool4Down", "None");
	CmRunRobotUnloadingSocket2Tool4Down = Input.ReadString("Data", "CmRunRobotUnloadingSocket2Tool4Down", "None");
	CmRunRobotUnloadingSocket3Tool4Down = Input.ReadString("Data", "CmRunRobotUnloadingSocket3Tool4Down", "None");
	CmRunRobotUnloadingSocket4Tool4Down = Input.ReadString("Data", "CmRunRobotUnloadingSocket4Tool4Down", "None");
	//
	CmRunRobotVisionTool1    = Input.ReadString("Data", "CmRunRobotVisionTool1", "None");
	CmRunRobotVisionTool2    = Input.ReadString("Data", "CmRunRobotVisionTool2", "None");
	CmRunRobotAlineTool1     = Input.ReadString("Data", "CmRunRobotAlineTool1", "None");
	CmRunRobotAlineTool2     = Input.ReadString("Data", "CmRunRobotAlineTool2", "None");
	CmRunRobotAlinePickTool1 = Input.ReadString("Data", "CmRunRobotAlinePickTool1", "None");
	CmRunRobotAlinePickTool2 = Input.ReadString("Data", "CmRunRobotAlinePickTool2", "None");
	//
	CmRunRobotUnloadingTrayLoading = Input.ReadString("Data", "CmRunRobotUnloadingTrayLoading", "None");
	CmRunRobotUnloadingTrayUnloading = Input.ReadString("Data", "CmRunRobotUnloadingTrayUnloading", "None");
	//
	CmRunRobotDownMore = Input.ReadString("Data", "CmRunRobotDownMore", "None");
}

int CHandlerMCDoc::SendDataEthernet(CString m_data)
{
	m_client->m_Socket.m_strRecvMsg = "";
	m_client->m_Socket.MotionRobotDone = false;
	ViewDataList(m_data);
	int m_result = 0;
	if (FlagConnectEthernet)
	{
		m_result = m_client->SendMsg(m_data);
	}
	else
	{
		AfxMessageBox("Disconnect");
	}
	return m_result;
}


bool CHandlerMCDoc:: MootionDoneRobot()
{
	return 	m_client->m_Socket.MotionRobotDone;
}

bool CHandlerMCDoc::MootionVisionDoneRobot()
{
	if (ReadDataRobot() == "done:ok")
	{
		FlagMotionVisionDoneRobot = true;
	}
	else
	{
		FlagMotionVisionDoneRobot = false;
	}
	return FlagMotionVisionDoneRobot;
}

bool CHandlerMCDoc::ActionReviceEthernet()
{
	FlagRevice = m_client->ActionRevice;
	return FlagRevice;
}

CString CHandlerMCDoc::ReadDataRobot()
{
	return m_client->m_Socket.GetNewMsg();
}

// CHandlerMCDoc commands
void CHandlerMCDoc::ReadDataModel()
{
	int TotalModel;
	int m_row, m_column;
	CString m_name,m_path;
    CIniFile Total,DetailModel;
	CreatNewModel m_DataModeVector;

	Total.SetPath("Model\\DataModel.dat");// đường dẫn file. Nhớ phải dung 2 sẹc (\\).
	TotalModel = Total.ReadInt("Data", "Total", 0);

	for (int i = 0; i < TotalModel; i++)
	{
		
		m_path.Format("Model%d", i);
		m_name = Total.ReadString("Data", m_path, "NoName");
		DetailModel.SetPath("Model\\" + m_name + "\\WorkTray.dat");
		m_row = DetailModel.ReadInt("Data", "Row", 0);
		m_column = DetailModel.ReadInt("Data", "Column", 0);

		m_DataModeVector.NameModel = m_name;
		m_DataModeVector.Row = m_row;
		m_DataModeVector.Column = m_column;

		CNewModel.push_back(m_DataModeVector);
	}

	ModelAction = Total.ReadInt("Data", "ModelAction", 0);
	NameModelUse = CNewModel.at(ModelAction).NameModel;
	RowTray = CNewModel.at(ModelAction).Row;
	ColumnTray = CNewModel.at(ModelAction).Column;
}

void CHandlerMCDoc::SaveNameDataAll()
{
	//Save Data All model
	CFileFind ffind;
	CString strPathAllModel = "Model\\DataModel.dat";

	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	if (ffind.FindFile((LPCTSTR)strPathAllModel) == FALSE)
	{
		AfxMessageBox("Not find to save model");
	}
	else
	{
		HANDLE hFile1 = CreateFile(strPathAllModel,//Tao file moi
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		CloseHandle(hFile1);//

		CStdioFile AllModel;
		AllModel.Open(strPathAllModel, CFile::modeReadWrite);
		AllModel.WriteString("[Data]\n\n");
		CString m_NameAll, BufferName, m_total,m_ModelAction;

		for (int i = 0; i < pDoc->CNewModel.size(); i++)
		{
			BufferName.Format("Model%d = ", i);
			AllModel.WriteString(BufferName + pDoc->CNewModel.at(i).NameModel + "\n");
		}
		m_total.Format("Total = %d \n", pDoc->CNewModel.size());
		AllModel.WriteString(m_total);
		m_ModelAction.Format("ModelAction = %d \n", ModelAction);
		AllModel.WriteString(m_ModelAction);
	}
}

void CHandlerMCDoc::DeleteForder(CString m_path)
{

	char folderPath[1024];
	strcpy_s(folderPath, (LPCTSTR)m_path);
	char fileFound[256];
	WIN32_FIND_DATA info;
	HANDLE hp;
	sprintf_s(fileFound, "%s\\*.*", folderPath);
	hp = FindFirstFile(fileFound, &info);
	do
	{
		sprintf_s(fileFound, "%s\\%s", folderPath, info.cFileName);
		DeleteFile(fileFound);

	} while (FindNextFile(hp, &info));
	FindClose(hp);

	if (!RemoveDirectory(m_path))
	{
		TRACE("Delete dir error");
	}
}

void CHandlerMCDoc::InitalinePos()
{
	PosY.clear();
	for (int i = 0; i < 3; i++)
	{
		PosXY[i].clear();
	}


	for (int j = 0; j < ColumnTray; j++)
	{
		PosY.push_back(datapos);
	}
	
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < RowTray; i++)
		{
			PosXY[j].push_back(PosY);
		}
	}

}

void CHandlerMCDoc::ReadDataPosition(CString m_Path,int m_Picture)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CIniFile Input;

	Input.SetPath(m_Path);
	CString stt;
	CString mData;
	long X, Y, Z;
	BOOL S;

	for (int i = 0; i < pDoc->RowTray; i++)
	{
		for (int j = 0; j < pDoc->ColumnTray; j++)
		{
			stt.Format("PosX%d-Y%d", i, j);
			mData = Input.ReadString("Data", stt, "NoData");
			if (mData == "NoData")
			{
				AfxMessageBox("Reading Data Error");
			}
			FindXYS(mData, X, Y, Z, S);
			pDoc->PosXY[m_Picture].at(i).at(j).dPositionX = X;
			pDoc->PosXY[m_Picture].at(i).at(j).dPositionY = Y;
			pDoc->PosXY[m_Picture].at(i).at(j).dPositionZ = Z;
			pDoc->PosXY[m_Picture].at(i).at(j).status = S;
			//
		}
	}
}

void CHandlerMCDoc::ReadDataStatusUnloading(CString m_Path)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CIniFile Input;

	Input.SetPath(m_Path);
	CString stt;
	int mData;
	long X, Y, Z;
	BOOL S;


	for (int i = 0; i < pDoc->RowTray; i++)
	{
		for (int j = 0; j < pDoc->ColumnTray; j++)
		{
			stt.Format("PosX%d-Y%d-StatusUnloading", i, j);//
			mData = Input.ReadInt("Data", stt, 2);
			if (mData == 2)
			{
				AfxMessageBox("Reading Data Status Unloading Error");
				return;
			}		
			pDoc->PosXY[TrayLoading].at(i).at(j).unloading = mData;
			//
		}
	}
}
void CHandlerMCDoc::FindXYS(CString m_data, long &mx, long &my, long &mz, BOOL &ms)
{
	CString input = m_data;
	string in = (string)input;

	string posx;
	string posy;
	string posz;
	string status;
	int m_x = 0, m_y = 0, m_z = 0, m_s = 0;

	for (int i = 0; i <(int)in.length(); i++)
	{
		if (in[i] == 'X')
		{
			m_x = i;
		}
		if (in[i] == 'Y')
		{
			m_y = i;
		}
		if (in[i] == 'Z')
		{
			m_z = i;
		}
		if (in[i] == 'S')
		{
			m_s = i;
		}
	}
	for (int i = m_x + 3; i < m_y - 1; i++)
	{
		posx = posx + in[i];
	}
	for (int i = m_y + 3; i < m_z - 1; i++)
	{
		posy = posy + in[i];
	}
	for (int i = m_z + 3; i < m_s - 1; i++)
	{
		posz = posz + in[i];
	}
	for (int i = m_s + 7; i < (int)in.length(); i++)
	{
		status = status + in[i];
	}

	mx = atol(posx.c_str());
	my = atol(posy.c_str());
	mz = atol(posz.c_str());
	ms = atol(status.c_str());
}

BOOL CHandlerMCDoc::InitSocket()
{
	sClient socket;
	socket.strIP = "107.107.89.100";
	socket.iPort = 8000;
	socket.dTime = 1000;
	mClient = new ClientSocket(socket);

	Sleep(2000);

	mClient->StartTest(true);

	return true;
}

void CHandlerMCDoc::SetupInitiaization()
{
	if (!Motion.Initiaization())//khoi tao cad
	{
		StatusOpenCard = FALSE;
		return;
	}
	else
	{
		StatusOpenCard = TRUE;
	}
	//Motion.Initdata();//

	for (int i = 0; i < Motion.InfoGetAxisCount(); i++)
	{
		Motion.SetPulseOutMethod(i, DataSettup.MethodPulse4);//phuong phap phat xung6

		Motion.SetEncInputMethod(i, DataSettup.MethodEncoderInput7);//phuong phap input encoder 3

		Motion.SignalSetLimit(i, DataSettup.EmergencyStop, DataSettup.uPositiveLevel0, DataSettup.uNegativeLevel0);//phuong phap dung khi gap limit // trang thai limit-+

		Motion.SignalSetInpos(i, DataSettup.HIGH);//Set Active Level of inposition signal to Active HIGH,
		Motion.SignalSetServoAlarm(i, DataSettup.LOW);// Set input level of alarm signal on axis 0. Default : HIGH. 
		Motion.SignalSetStop(i, DataSettup.EmergencyStop, DataSettup.HIGH);//Muc tin hieu stop

		Motion.StartSpeed(i); //setup speed min max

	}

	Motion.MotSetMoveUnitPerPulse(AxisX, 10, 10000);//Set do dich chuyen mot vomh quay va so xung de quay duoc 1 vong
	Motion.MotSetMoveUnitPerPulse(AxisY, 10, 10000);

	
}




//Input & Output
BOOL CHandlerMCDoc::ReadInput(int m_input)
{
	if (Motion.ReadInput(m_input))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}

BOOL CHandlerMCDoc::ReadOutput(int m_output)
{
	if (Motion.ReadOuput(m_output))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
void CHandlerMCDoc::SetOutput(int m_output)
{
	Motion.SetOuput(m_output);
}
void CHandlerMCDoc::ResetOutput(int m_output)
{
	Motion.ResetOuput(m_output);
}
//Read Infor Data Card Motion
void CHandlerMCDoc::ReadInforDataMotion()
{
	CString InforData;
	DataInforCardMotion.clear();
	//1 Open card
	if (!StatusOpenCard) 
	{ 
		DataInforCardMotion.push_back("Open Card Error"); 
		return;
	}
	else
	{
		DataInforCardMotion.push_back("Open Card Success");
	}
	//2 Name card motion
	DataInforCardMotion.push_back(Motion.AddAxisInfo());
	//3 No axis run
	long m_NoAxis = Motion.InfoGetAxisCount();
	InforData.Format("No Axis Run: %d", m_NoAxis);
	DataInforCardMotion.push_back(InforData);

	//Get Value Limit 
	for (int i = 0; i < m_NoAxis; i++)
	{
		//4 Get pulse out method
		InforData.Format("pulse out method axis%d: ", i);
		DataInforCardMotion.push_back(InforData + Motion.GetPulseOutMethod(i));
		//5 Encoder input method
		InforData.Format("Encoder input method axis%d: ", i);
		DataInforCardMotion.push_back(InforData + Motion.GetEncInputMethod(i));
		//Get Value Limit 
		InforData.Format("Value Limit+ axis%d: ", i);
		DataInforCardMotion.push_back(InforData + Motion.SignalReadLimit(i,"Positive"));
		InforData.Format("Value Limit- axis%d: ", i);
		DataInforCardMotion.push_back(InforData + Motion.SignalReadLimit(i, "Negative"));
		//
		InforData.Format("Get Limit+ axis%d: ", i);
		DataInforCardMotion.push_back(InforData + Motion.SignalGetLimit(i, "Positive"));
		InforData.Format("Get Limit- axis%d: ", i);
		DataInforCardMotion.push_back(InforData + Motion.SignalGetLimit(i, "Negative"));
		//acc-dec
		InforData.Format("Acc-Dec- axis%d: ", i);
		DataInforCardMotion.push_back(InforData + Motion.Get_Mode_AccDcc(i));

	}
}

void CHandlerMCDoc::ReadInforDataIO()
{
	CString InforData;
	DataInforCardIO.clear();
	long m_ModuleCount;
	//
	DataInforCardIO.push_back("InfoGetModuleCount  :" + Motion.InfoGetModuleCount());
	//
	DataInforCardIO.push_back("InfoIsDIOModule  :" + Motion.InfoIsDIOModule());
	//
	DataInforCardIO.push_back("InfoGetModuleNo  :" + Motion.InfoGetModuleNo());
}

//Power air
void CHandlerMCDoc::PowerAirOn()
{
	Motion.SetOuput(PowerAir);
}
void CHandlerMCDoc::PowerAirOff()
{
	Motion.ResetOuput(PowerAir);
}


/////////////Control IO Left/////////////////////////////

//Bang tai
void CHandlerMCDoc::ConveyorLoadingOn()
{
	Motion.SetOuput(Conveyor_Loading);
}
void CHandlerMCDoc::ConveyorLoadingOff()
{
	Motion.ResetOuput(Conveyor_Loading);
}
//Chan Tray Loading
void CHandlerMCDoc::ChanTrayLoadingOn()
{
	Motion.SetOuput(XL_Chan_Tray_Loading_Dung);
	Motion.ResetOuput(XL_Chan_Tray_Loading_Nam);
}
void CHandlerMCDoc::ChanTrayLoadingOff()
{
	Motion.ResetOuput(XL_Chan_Tray_Loading_Dung);
	Motion.SetOuput(XL_Chan_Tray_Loading_Nam);
}
//Xi lanh do tray loading
void CHandlerMCDoc::XilanhDoTrayLoadingOn()
{
	Motion.SetOuput(XL_Do_Tray_Loading_Fw);
	Motion.ResetOuput(XL_Do_Tray_Loading_Rv);
}
void CHandlerMCDoc::XilanhDoTrayLoadingOff()
{
	Motion.ResetOuput(XL_Do_Tray_Loading_Fw);
	Motion.SetOuput(XL_Do_Tray_Loading_Rv);
}
//Xi lanh aline tray loading
void CHandlerMCDoc::XilanhAlineTrayLoadingOn()
{
	Motion.SetOuput(XL_Aline_Loading_Fw);
	Motion.ResetOuput(XL_Aline_Loading_Rv);
}
void CHandlerMCDoc::XilanhAlineTrayLoadingOff()
{
	Motion.ResetOuput(XL_Aline_Loading_Fw);
	Motion.SetOuput(XL_Aline_Loading_Rv);
}
//Xi lanh Chot tray loading
void CHandlerMCDoc::XilanhChotTrayLoadingOn()
{
	Motion.SetOuput(XL_Chot_Stack_Loading_Fw);
	Motion.ResetOuput(XL_Chot_Stack_Loading_Rv);
}
void CHandlerMCDoc::XilanhChotTrayLoadingOff()
{
	Motion.ResetOuput(XL_Chot_Stack_Loading_Fw);
	Motion.SetOuput(XL_Chot_Stack_Loading_Rv);
}

/////////////Control IO Right/////////////////////////////


//Bang tai
void CHandlerMCDoc::ConveyorUnloadingOn()
{
	Motion.SetOuput(Conveyor_Unloading);
	Motion.SetOuput(Conveyor_Unloading_Rv);
}
void CHandlerMCDoc::ConveyorUnloadingOff()
{
	Motion.ResetOuput(Conveyor_Unloading);
	Motion.ResetOuput(Conveyor_Unloading_Rv);
}
//Chan Tray Loading
void CHandlerMCDoc::ChanTrayUnloadingOn()
{
	Motion.SetOuput(XL_Chan_Tray_Unloading_Dung);
	Motion.ResetOuput(XL_Chan_Tray_Unloading_Nam);
}
void CHandlerMCDoc::ChanTrayUnloadingOff()
{
	Motion.ResetOuput(XL_Chan_Tray_Unloading_Dung);
	Motion.SetOuput(XL_Chan_Tray_Unloading_Nam);
}
//Xi lanh do tray loading
void CHandlerMCDoc::XilanhDoTrayUnloadingOn()
{
	Motion.SetOuput(XL_Do_Tray_Unloading_Fw);
	Motion.ResetOuput(XL_Do_Tray_Unloading_Rv);
}
void CHandlerMCDoc::XilanhDoTrayUnloadingOff()
{
	Motion.ResetOuput(XL_Do_Tray_Unloading_Fw);
	Motion.SetOuput(XL_Do_Tray_Unloading_Rv);
}
//Xi lanh aline tray loading
void CHandlerMCDoc::XilanhAlineTrayUnloadingOn()
{
	Motion.SetOuput(XL_Aline_Unloading_Fw);
	Motion.ResetOuput(XL_Aline_Unloading_Rv);
}
void CHandlerMCDoc::XilanhAlineTrayUnloadingOff()
{
	Motion.ResetOuput(XL_Aline_Unloading_Fw);
	Motion.SetOuput(XL_Aline_Unloading_Rv);
}
//Xi lanh Chot tray loading
void CHandlerMCDoc::XilanhChotTrayUnloadingOn()
{
	Motion.SetOuput(XL_Chot_Stack_Unloading_Fw);
	Motion.ResetOuput(XL_Chot_Stack_Unloading_Rv);
}
void CHandlerMCDoc::XilanhChotTrayUnloadingOff()
{
	Motion.ResetOuput(XL_Chot_Stack_Unloading_Fw);
	Motion.SetOuput(XL_Chot_Stack_Unloading_Rv);
}

//Xi lanh Aline
void CHandlerMCDoc::XilanhAlineOn()
{
	Motion.SetOuput(XL_Aline_CAM);
}
void CHandlerMCDoc::XilanhAlineOff()
{
	Motion.ResetOuput(XL_Aline_CAM);
}

//Open door after
void CHandlerMCDoc::OpenDoorAfter()
{
	Motion.SetOuput(Look_After);
}
void CHandlerMCDoc::CloseDoorAfter()
{
	Motion.ResetOuput(Look_After);
}

/////////////Control IO Robot/////////////////////////////
//Tool 1
void CHandlerMCDoc::XilanhTool1On()
{
	Motion.SetOuput(XL_Tool_Robot_1);
}
void CHandlerMCDoc::XilanhTool1Off()
{
	Motion.ResetOuput(XL_Tool_Robot_1);
	
}
void CHandlerMCDoc::VaccumTool1On()
{
	Motion.SetOuput(Vaccum_Robot_1);
}
void CHandlerMCDoc::VaccumTool1Off()
{
	Motion.ResetOuput(Vaccum_Robot_1);
}
bool CHandlerMCDoc::GetSignVaccumTool1Unloading()
{
	/*if (ReadInput())
	{

	}*/
	return false;
}
//Tool 2
void CHandlerMCDoc::XilanhTool2On()
{
	Motion.SetOuput(XL_Tool_Robot_2);
}
void CHandlerMCDoc::XilanhTool2Off()
{
	Motion.ResetOuput(XL_Tool_Robot_2);
}
void CHandlerMCDoc::VaccumTool2On()
{
	Motion.SetOuput(Vaccum_Robot_2);
}
void CHandlerMCDoc::VaccumTool2Off()
{
	Motion.ResetOuput(Vaccum_Robot_2);

}
//Tool 3
void CHandlerMCDoc::XilanhTool3On()
{
	Motion.SetOuput(XL_Tool_Robot_3);
}
void CHandlerMCDoc::XilanhTool3Off()
{
	Motion.ResetOuput(XL_Tool_Robot_3);
}
void CHandlerMCDoc::VaccumTool3On()
{
	Motion.SetOuput(Vaccum_Robot_3);
}
void CHandlerMCDoc::VaccumTool3Off()
{
	Motion.ResetOuput(Vaccum_Robot_3);
}
//Tool 4
void CHandlerMCDoc::XilanhTool4On()
{
	Motion.SetOuput(XL_Tool_Robot_4);
}
void CHandlerMCDoc::XilanhTool4Off()
{
	Motion.ResetOuput(XL_Tool_Robot_4);
}
void CHandlerMCDoc::VaccumTool4On()
{
	Motion.SetOuput(Vaccum_Robot_4);
}
void CHandlerMCDoc::VaccumTool4Off()
{
	Motion.ResetOuput(Vaccum_Robot_4);
}
//Tray in robot
void CHandlerMCDoc::VaccumTrayRobotOn()
{
	Motion.SetOuput(Robot_Vaccum_Tray);
}
void CHandlerMCDoc::VaccumTrayRobotOff()
{
	Motion.ResetOuput(Robot_Vaccum_Tray);
}

//Tool Robot Loading
//
void CHandlerMCDoc::XilanhTool1RobotLoadingOn()
{
	Motion.SetOuput(XL_Tool_Robot_1);
}
void CHandlerMCDoc::XilanhTool1RobotLoadingOff()
{
	Motion.ResetOuput(XL_Tool_Robot_1);
}
void CHandlerMCDoc::VaccumTool1RobotLoadingOn()
{
	Motion.SetOuput(Vaccum_Robot_1);
}
void CHandlerMCDoc::VaccumTool1RobotLoadingOff()
{
	Motion.ResetOuput(Vaccum_Robot_1);
}
//
void CHandlerMCDoc::XilanhTool2RobotLoadingOn()
{
	Motion.SetOuput(XL_Tool_Robot_2);
}
void CHandlerMCDoc::XilanhTool2RobotLoadingOff()
{
	Motion.ResetOuput(XL_Tool_Robot_2);
}
void CHandlerMCDoc::VaccumTool2RobotLoadingOn()
{
	Motion.SetOuput(Vaccum_Robot_2);
}
void CHandlerMCDoc::VaccumTool2RobotLoadingOff()
{
	Motion.ResetOuput(Vaccum_Robot_2);
}
//
void CHandlerMCDoc::XilanhTool1RobotUnloadingOn()
{
	Motion.SetOuput(XL_Tool_Robot_3);
}
void CHandlerMCDoc::XilanhTool1RobotUnloadingOff()
{
	Motion.ResetOuput(XL_Tool_Robot_3);
}
void CHandlerMCDoc::VaccumTool1RobotUnloadingOn()
{
	Motion.SetOuput(Vaccum_Robot_3);
}
void CHandlerMCDoc::VaccumTool1RobotUnloadingOff()
{
	Motion.ResetOuput(Vaccum_Robot_3);
}
//
void CHandlerMCDoc::XilanhTool2RobotUnloadingOn()
{
	Motion.SetOuput(XL_Tool_Robot_4);
}
void CHandlerMCDoc::XilanhTool2RobotUnloadingOff()
{
	Motion.ResetOuput(XL_Tool_Robot_4);
}
void CHandlerMCDoc::VaccumTool2RobotUnloadingOn()
{
	Motion.SetOuput(Vaccum_Robot_4);
}
void CHandlerMCDoc::VaccumTool2RobotUnloadingOff()
{
	Motion.ResetOuput(Vaccum_Robot_4);
}

//Socket 1
void CHandlerMCDoc::XilanhSocket1ForWard()
{
	Motion.ResetOuput(Socket_FW_1);
}
void CHandlerMCDoc::XilanhSocket1BackWard()
{	
	Motion.SetOuput(Socket_FW_1);
}
void CHandlerMCDoc::XilanhSocket1Up()
{
	Motion.SetOuput(Socket_UP_1);
}
void CHandlerMCDoc::XilanhSocket1Down()
{
	Motion.ResetOuput(Socket_UP_1);
}
void CHandlerMCDoc::VaccumSocket1On()
{
	Motion.SetOuput(Socket_Vaccum_1);
}
void CHandlerMCDoc::VaccumSocket1Off()
{
	Motion.ResetOuput(Socket_Vaccum_1);
}
//Socket 2
void CHandlerMCDoc::XilanhSocket2ForWard()
{
	Motion.ResetOuput(Socket_FW_2);
}
void CHandlerMCDoc::XilanhSocket2BackWard()
{
	Motion.SetOuput(Socket_FW_2);
}
void CHandlerMCDoc::XilanhSocket2Up()
{
	Motion.SetOuput(Socket_UP_2);
}
void CHandlerMCDoc::XilanhSocket2Down()
{
	Motion.ResetOuput(Socket_UP_2);
}
void CHandlerMCDoc::VaccumSocket2On()
{
	Motion.SetOuput(Socket_Vaccum_2);
}
void CHandlerMCDoc::VaccumSocket2Off()
{
	Motion.ResetOuput(Socket_Vaccum_2);
}
//Socket 3
void CHandlerMCDoc::XilanhSocket3ForWard()
{
	Motion.ResetOuput(Socket_FW_3);
}
void CHandlerMCDoc::XilanhSocket3BackWard()
{
	Motion.SetOuput(Socket_FW_3);
}
void CHandlerMCDoc::XilanhSocket3Up()
{
	Motion.SetOuput(Socket_UP_3);
}
void CHandlerMCDoc::XilanhSocket3Down()
{
	Motion.ResetOuput(Socket_UP_3);
}
void CHandlerMCDoc::VaccumSocket3On()
{
	Motion.SetOuput(Socket_Vaccum_3);
}
void CHandlerMCDoc::VaccumSocket3Off()
{
	Motion.ResetOuput(Socket_Vaccum_3);
}
//Socket 4
void CHandlerMCDoc::XilanhSocket4ForWard()
{
	Motion.ResetOuput(Socket_FW_4);
}
void CHandlerMCDoc::XilanhSocket4BackWard()
{
	Motion.SetOuput(Socket_FW_4);
}
void CHandlerMCDoc::XilanhSocket4Up()
{
	Motion.SetOuput(Socket_UP_4);
}
void CHandlerMCDoc::XilanhSocket4Down()
{
	Motion.ResetOuput(Socket_UP_4);
}
void CHandlerMCDoc::VaccumSocket4On()
{
	Motion.SetOuput(Socket_Vaccum_4);
}
void CHandlerMCDoc::VaccumSocket4Off()
{
	Motion.ResetOuput(Socket_Vaccum_4);
}
/////////////Control IO Door/////////////////////////////
void CHandlerMCDoc::OpenDoorFrontLeftOn()
{
	Motion.SetOuput(Open_Door_Font_Left);
}

void CHandlerMCDoc::OpenDoorFrontLeftOff()
{
	Motion.ResetOuput(Open_Door_Font_Left);
}

void CHandlerMCDoc::OpenDoorFrontRightOn()
{
	Motion.SetOuput(Open_Door_Font_Right);
}

void CHandlerMCDoc::OpenDoorFrontRightOff()
{
	Motion.ResetOuput(Open_Door_Font_Right);
}

void CHandlerMCDoc::OpenDoorSideRightOn()
{
	Motion.SetOuput(Open_Door_Side_Right);
}

void CHandlerMCDoc::OpenDoorsideRightOff()
{
	Motion.ResetOuput(Open_Door_Side_Right);
}

void CHandlerMCDoc::OpenDoorSideLeftOn()
{
	Motion.SetOuput(Open_Door_Side_Left);
}

void CHandlerMCDoc::OpenDoorsideLeftOff()
{
	Motion.ResetOuput(Open_Door_Side_Left);
}

void CHandlerMCDoc::AlarmOn()
{
	Motion.SetOuput(Alarm);
}
void CHandlerMCDoc::AlarmOff()
{
	Motion.ResetOuput(Alarm);
}

bool CHandlerMCDoc::RunPosLoading( double mPosition)
{
	Motion.MoveStartPos(AxisX, mPosition, DataMotor.SpeedRunAxisX, DataMotor.Acc, DataMotor.Dec);

	DWORD uStatus = 1 ;
	while (uStatus)
	{
	AxmStatusReadInMotion(AxisX, &uStatus);
	if (Motion.ReadInput(Button_Stop))
	{
		Motion.JogStop(AxisX);
		return false;
	}
	}

	return true;
}


bool CHandlerMCDoc::RunPosUnloading(double mPosition)
{
	Motion.MoveStartPos(AxisY, mPosition, DataMotor.SpeedRunAxisX, DataMotor.Acc, DataMotor.Dec);

	DWORD uStatus = 1;
	while (uStatus)
	{
		AxmStatusReadInMotion(AxisY, &uStatus);
		if (Motion.ReadInput(Button_Stop))
		{
			Motion.JogStop(AxisY);
			return false;
		}
	}

	return true;
}

void CHandlerMCDoc::ReadDataPointAxisZ()
{
	CIniFile Total;
	Total.SetPath("DataSystem\\DataPointLoadUnload.dat");// đường dẫn file. Nhớ phải dung 2 sẹc (\\).
	
	PosZ1Down = Total.ReadDouble("Data", "PosZ1Down", 0);
	PosZ1Up = Total.ReadDouble("Data", "PosZ1Up", 0);
	PosZ2Down = Total.ReadDouble("Data", "PosZ2Down", 0);
	PosZ2Up = Total.ReadDouble("Data", "PosZ2Up", 0);
	PosZ2Medium = Total.ReadDouble("Data", "PosZ2Medium", 0);
	OffsetJogLoadingZ1 = Total.ReadDouble("Data", "OffsetZ1", 0);
}

void CHandlerMCDoc::ReadDataPhone()
{
	CIniFile Total;
	Total.SetPath("DataSystem\\SelectPhone.dat");// đường dẫn file. Nhớ phải dung 2 sẹc (\\).
	CString data;
	for (int i = 0; i < 4; i++)
	{
		data.Format("%d", i+1);
		m_DataTester[i].Action = Total.ReadInt("Data", "Phone" + data, 0);
	}
}

void CHandlerMCDoc::ReadDataMotor()
{
	CIniFile Total;
	Total.SetPath("DataSystem\\DataMotor.dat");// đường dẫn file. Nhớ phải dung 2 sẹc (\\).

	DataMotor.Acc = Total.ReadDouble("Data", "AccDec", 0);
	DataMotor.SpeedJog1 = Total.ReadDouble("Data", "SpeedJog1", 0);
	DataMotor.SpeedJog2 = Total.ReadDouble("Data", "SpeedJog2", 0);
	DataMotor.SpeedJog3 = Total.ReadDouble("Data", "SpeedJog3", 0);
    DataMotor.SpeedOriginX = Total.ReadDouble("Data", "SpeedOriginZ1", 0);
	DataMotor.SpeedOriginY = Total.ReadDouble("Data", "SpeedOriginZ2", 0);
	DataMotor.SpeedRunAxisX = Total.ReadDouble("Data", "SpeedRunZ1", 0);
	DataMotor.SpeedRunAxisY = Total.ReadDouble("Data", "SpeedRunZ2", 0);

}

void CHandlerMCDoc::m_SendData(CString m_Data)
{
	//if (!m_Connect_com.GetPortStatus())
	//{
	//	AfxMessageBox("failed");
	//	return;
	//}
	//DWORD numberOfBytesWritten;
	//if (m_Connect_com.Write((LPTSTR)(LPCTSTR)m_Data, m_Data.GetLength(), numberOfBytesWritten))
	//{
	//	return;
	//}
	//CString m_data;
	//GetDlgItemTextA(IDC_SEND_DATA_COM, m_data);
	if (m_StatusConnectCom)
	{
		SendPhoneCom(m_Data);
	}
	else
	{
		AfxMessageBox("Don't Connect");
	}
}

CString CHandlerMCDoc::m_ReviceData(CString m_data)
{
	//char read_dt[12];
	//string data;
	CString m_Data;
	//int sizebuffer = sizeof(read_dt);
	//unsigned long length;
	//m_Connect_com.Read(read_dt, 6, length);
	//data = read_dt;
	//m_DataReviceCom = m_data;
	if (m_data.GetLength() >= 4)
	{
	//	m_DataReviceCom = data.c_str();
		m_DataReviceCom = m_data;
		m_Data = (CString)(m_DataReviceCom.GetAt(0)) + (CString)(m_DataReviceCom.GetAt(1)) + (CString)(m_DataReviceCom.GetAt(2)) + (CString)(m_DataReviceCom.GetAt(3));
		if (m_Data == "1_OK")
		{
			m_ResultTestSocket[0] = 1;
		}
		if (m_Data == "1_NG" || m_Data == "1_ER")
		{
			m_ResultTestSocket[0] = 2;
		}
		if (m_Data == "2_OK")
		{
			m_ResultTestSocket[1] = 1;
		}
		if (m_Data == "2_NG" || m_Data == "2_ER")
		{
			m_ResultTestSocket[1] = 2;
		}
		if (m_Data == "3_OK")
		{
			m_ResultTestSocket[2] = 1;
		}
		if (m_Data == "3_NG" || m_Data == "3_ER")
		{
			m_ResultTestSocket[2] = 2;
		}
		if (m_Data == "4_OK")
		{
			m_ResultTestSocket[3] = 1;
		}
		if (m_Data == "4_NG" || m_Data == "4_ER")
		{
			m_ResultTestSocket[3] = 2;
		}
	}
	else
	{
		m_DataReviceCom = "";
	}
	return m_DataReviceCom;
}

//-------------------888888888888888-----------------------
void ThreadUpData(CHandlerMCDoc *pPrivate)
{
	pPrivate->loopData();
}

void CHandlerMCDoc::initializeVision()
{
	pcamOmron = new CameraOmron();
	//m_camOmron = new CameraOmron();
	m_savedata->loadParameter(_T("Parameter\\System.dat"), Data_system);
	Sleep(20);
	loopData();
	

}
void CHandlerMCDoc::loopData()
{
	//Blur
	kSize_tool_1 = Data_system.d_kSize_Tool_1;
	kSize_tool_2 = Data_system.d_kSize_Tool_2;

	//Threshold
	valueThreshTool_1 = Data_system.d_threshold_tool_1;
	valueThreshTool_2 = Data_system.d_threshold_tool_2;
	
	//MorPhology
	morSize_tool_1 = Data_system.d_morSize_tool_1;
	morSize_tool_2 = Data_system.d_morSize_tool_2;

	//Remove noise
	d_minArea = Data_system.d_minArea;
	d_maxArea = Data_system.d_maxArea;
	d_minWidth = Data_system.d_minWidth;
	d_maxWidth = Data_system.d_maxWidth;
	d_minHeight = Data_system.d_minHeight;
	d_maxHeight = Data_system.d_maxHeight;

	//Image process
	check_process = Data_system.d_check_process;

	//Remove noise
	check_app_remove_noise = Data_system.d_check_remove_noise;

	//Morphology
	checkApplyMorphology = Data_system.d_Check_Apply_Morphology;
	erode = Data_system.d_erode;
	dilate = Data_system.d_dilate;
	erode_dilate = Data_system.d_e_dilate;
	dilate_erode = Data_system.d_d_erode;
	//Point and Angle tool 1
	pointSampleTool_1.x = Data_system.d_Point_Tool_1_X;
	pointSampleTool_1.y = Data_system.d_Point_Tool_1_Y;
	angleSampleTool_1	= Data_system.d_dAgnle_Tool_1;
	//Point ang Angle tool 2
	pointSampleTool_2.x = Data_system.d_Point_Tool_2_X;
	pointSampleTool_2.y = Data_system.d_Point_Tool_2_Y;
	angleSampleTool_2 = Data_system.d_dAgnle_Tool_2;
}

cv::Mat CHandlerMCDoc::filterAndThreshold(cv::Mat image, int th_value, int tool_1, int tool_2)
{
	int selectF = 0;
	int selectTH = 0;

	cv::Mat imageF, imageTH;
	
	if (tool_1 == 1 && tool_2 != 1) {
		imageF = (m_vision->smooth(image, kSize_tool_1)).clone();

		imageTH = (m_vision->binaryTh(imageF, th_value)).clone();

	}
	if (tool_2 == 1 && tool_1 != 1) {
		imageF = (m_vision->smooth(image, kSize_tool_2)).clone();

		imageTH = (m_vision->binaryTh(imageF, th_value)).clone();

	}

	return imageTH;

}

void CHandlerMCDoc::morphologyP(cv::Mat &image, int tool_1, int tool_2)
{
	int selectOp;

	if (erode == 1 && dilate == 0 && erode_dilate == 0 && dilate_erode == 0) {
		selectOp = 1;
	}
	if (erode == 0 && dilate == 1 && erode_dilate == 0 && dilate_erode == 0) {
		selectOp = 2;
	}
	if (erode == 0 && dilate == 0 && erode_dilate == 1 && dilate_erode == 0) {
		selectOp = 3;
	}
	if (erode == 0 && dilate == 0 && erode_dilate == 0 && dilate_erode == 1) {
		selectOp = 4;
	}
	if (selectOp <= 0 && selectOp > 4) {
		CString morphology;
		morphology = _T("You only select to use one morphology");
		AfxMessageBox(morphology);
	}
	if (tool_1 == 1 && tool_2 != 1) {
		image = (m_vision->morphologProc(image, morSize_tool_1, selectOp)).clone();
	}
	if (tool_2 == 1 && tool_1 != 1) {
		image = (m_vision->morphologProc(image, morSize_tool_2, selectOp)).clone();
	}
	
}
cv::Mat CHandlerMCDoc::showProcessImage(int result, int tool_1, int tool_2, int aut_value)
{
	//Mat m_grab;
	pcamOmron->Grab(m_Grab);
	image = m_Grab.clone();

	/*if (tool_1 == 1) {
		imwrite("mInput_1.jpg", image);
	}
	else if (tool_2 == 1) {
		imwrite("mInput_2.jpg", image);
	}*/

	appVision vs;
	Mat mInput;
	Mat  mOutput;
	Mat mShow = image.clone();
	cvtColor(mShow, mShow, CV_GRAY2BGR);
	VisionPara vPara[2];
	if (tool_1 == 1) {
		vPara[TOOL_1].iThresh = Data_system.d_threshold_tool_1;
		//vPara.iThreshLeft = valueThreshTool_1;

	}
	else if (tool_2 == 1) {
		vPara[TOOL_2].iThresh = Data_system.d_threshold_tool_2;
		//vPara.iThreshLeft = valueThreshTool_2;

	}

	/*double  dX, dY;
	float alpha;*/
	Point2f points[4];
	RotatedRect  r;
	vs.ShowAlignTest(image, mOutput, vPara[TOOL_1], dX, dY, alpha, r);
	r.points(points);
	for (int i = 0; i < 4; i++) {
		line(mShow, points[i], points[(i + 1) % 4], Scalar(0, 255, 0), 5);

	}
	CString str;
	double deltaX = -(dY - Data_system.d_Point_Tool_2_Y)*0.024;
	double deltaY = (dX - Data_system.d_Point_Tool_2_X)*0.024;
	str.Format("dX: %.2f, dY: %.2f, alpha: %.2f", deltaX, deltaY, -alpha);
	putText(mShow, string(str), r.center, FONT_HERSHEY_SIMPLEX, 2, Scalar(200, 0, 0), 8);
	angleCurrent = alpha;
	Point pointCurrent;
	pointCurrent.x = dX;
	pointCurrent.y = dY;
	circle(mShow, pointCurrent, 20, Scalar(200, 0, 0), -1, 8);
	
	return mShow;

	if (check_process == 0 && result == 0) {
		return image;
	}	
}

BOOL CHandlerMCDoc::functionResult(double &dx, double &dy, double &dAngle, int tool_1 = 0, int tool_2 = 0)
{
	Sleep(500);
	int result = 1;
	dAngle = 0;
	int aut_value = 0;
	cv::Mat imageResult;
	imageResult = showProcessImage(result, tool_1, tool_2, aut_value);
	if (tool_1 == 1 && tool_2 != 1) 
	{
		dx = 0;
		dy = 0;
		dAngle = 0;
		dAngle = -(alpha - Data_system.d_dAgnle_Tool_1);
		Point2f pointCurrent;
		
		pointCurrent.x = dX;
		pointCurrent.y = dY;
		dy = (pointCurrent.x - pointSampleTool_1.x)*0.0245;
		dx = -(pointCurrent.y - pointSampleTool_1.y)*0.0245;
		deltadX = dx;
		deltadY = dy;
		/*CString str, strPoint;
		strPoint.Format("Tool1 >> cur(%.2f,%.2f) mas(%.2f,%.2f)", pointCurrent.x, pointCurrent.y, pointSampleTool_1.x, pointSampleTool_1.y);
		TRACE(strPoint);
		str.Format("tool1 ->> dX: %.2f, dY: %.2f, alpha: %.2f", dx, dy, dAngle);
		TRACE(str);*/
		

	}
	if (tool_1 != 1 && tool_2 == 1) 
	{
		dx = 0;
		dy = 0;
		dAngle = 0;
		dAngle = -(alpha - Data_system.d_dAgnle_Tool_2);
		Point2f pointCurrent;

		pointCurrent.x = dX;
		pointCurrent.y = dY;
		dy = (pointCurrent.x - pointSampleTool_2.x)*0.0245;
		dx = -(pointCurrent.y - pointSampleTool_2.y)*0.0245;
		deltadX = dx;
		deltadY = dy;
		/*CString str, strPoint;
		strPoint.Format("Tool2 >> cur(%.2f,%.2f) mas(%.2f,%.2f)", pointCurrent.x, pointCurrent.y, pointSampleTool_2.x, pointSampleTool_2.y);
		TRACE(strPoint);
		str.Format("tool2 ->> dX: %.2f, dY: %.2f, alpha: %.2f", dx, dy, dAngle);
		TRACE(str);*/
		
	}
	result = 0;
	return TRUE;

}

BOOL CHandlerMCDoc::resultApply(double &dx, double &dy, double &dAngle, int tool_1, int tool_2)
{
	int result = 1;
	int aut_value = 0;
	cv::Mat imageResult;
	imageResult = showProcessImage(result, tool_1, tool_2, aut_value);
	if (tool_1 == 1 && tool_2 != 1) {
		//Point sample tool 1
		
		dAngle = alpha - Data_system.d_dAgnle_Tool_1;

		cv::Point2f	pointTool_1;

		pointSampleTool_1.x = dX;
		Data_system.d_Point_Tool_1_X = dX;
		pointSampleTool_1.y = dY;
		Data_system.d_Point_Tool_1_Y = dY;
		//Angle sample tool 1
		angleSampleTool_1 = alpha;
		Data_system.d_dAgnle_Tool_1 = alpha;
		
		dx = pointSampleTool_1.x;
		dy = pointSampleTool_1.y;
		dAngle = angleSampleTool_1;
	}
	if (tool_1 != 1 && tool_2 == 1) {
		//Point sample tool 2
		pointSampleTool_2.x	= dX;
		Data_system.d_Point_Tool_2_X = dX;
		pointSampleTool_2.y = dY;
		Data_system.d_Point_Tool_2_Y = dY;
		//Angle sample tool 2
		angleSampleTool_2 = alpha;
		Data_system.d_dAgnle_Tool_2 = alpha;

		dy = pointSampleTool_2.y;
		dx = pointSampleTool_2.x;
		dAngle = angleSampleTool_2;
		
	}
	result = 0;
	return TRUE;

}


//---------------8888888888888888-----------------

UINT CHandlerMCDoc::ThreadServo(LPVOID pParam)
{
	CHandlerMCDoc* pThis = (CHandlerMCDoc*)pParam;

	while (!pThis->bEndThreadServo)
	{
		pThis->LoopServo();
		Sleep(5);
	}
	return 0;

}

void CHandlerMCDoc::StopThreadServo()
{
	bEndThreadServo = TRUE;
}

void CHandlerMCDoc::StartThreadServo()
{
	bEndThreadServo = FALSE;
	AfxBeginThread(ThreadServo, this);
}

void CHandlerMCDoc::LoopServo()
{
	switch (m_operation) 
	{
	case operation_stop:
		LoopStop();
		ActionBotton();
		break;
	case operation_EMG:
		LoopEMG();
		ActionBotton();
		break;
	case operation_wait:
		LoopWait();
		ActionBotton();
		break;
	case operation_start:
		//Action Result tool 1
		if (m_ResultTestSocket[0] == 1 || m_ResultTestSocket[0] == 2)
		{
			ActionXilanhSocket1Result();
		}
		else
		{
			m_ActionXilanhSocket1Result = 0;
		}
		//Action Result tool 2
		if (m_ResultTestSocket[1] == 1 || m_ResultTestSocket[1] == 2)
		{
			ActionXilanhSocket2Result();
		}
		else
		{
			m_ActionXilanhSocket2Result = 0;
		}
		//Action Result tool 3
		if (m_ResultTestSocket[2] == 1 || m_ResultTestSocket[2] == 2)
		{
			ActionXilanhSocket3Result();
		}
		else
		{
			m_ActionXilanhSocket3Result = 0;
		}
		//Action Result tool 4
		if (m_ResultTestSocket[3] == 1 || m_ResultTestSocket[3] == 2)
		{
			ActionXilanhSocket4Result();
		}
		else
		{
			m_ActionXilanhSocket4Result = 0;
		}

		LoopStart();
		ActionBotton();
		break;
	default:
		break;
	}
}

void CHandlerMCDoc::ActionBotton()
{
	while (ReadInput(Button_Start))
	{
		m_operation = operation_start;
	}
	
	if ((m_operation == operation_start) && !m_ReadySuccess)
	{
		m_operation = operation_stop;
		AfxMessageBox("Don't Initalize");
	}
	if (Motion.ReadInput(ButtonStop)) 
	{ 
		Motion.JogStop(AxisX);
		Motion.JogStop(AxisY);
		ConveyorLoadingOff();
		ConveyorUnloadingOff();
		m_operation = operation_stop;
		m_ReadySuccess = false;
		m_manualloading = false;
	}
	if (Motion.ReadInput(ButtonReset))
	{
		AlarmOff();
	}
	if (Motion.ReadInput(EMG))        
	{
		m_operation = operation_EMG;
		AfxMessageBox("EMG");
	}
}
void CHandlerMCDoc::ActionStop()
{
	Motion.JogStop(AxisX);
	Motion.JogStop(AxisY);
	ConveyorLoadingOff();
	ConveyorUnloadingOff();
	m_operation = operation_stop;
	m_manualloading = false;
	m_ReadySuccess = false;
}

void CHandlerMCDoc::LoopStop()
{
	//Status Lamp
	if (!Motion.ReadOuput(LampYellow))
	{
		Motion.SetOuput(LampYellow);
		Motion.SetOuput(ButtonStop);

		Motion.ResetOuput(LampGreen);
		Motion.ResetOuput(LampRed);
		Motion.ResetOuput(ButtonStart);
	}

}

void CHandlerMCDoc::LoopEMG()
{
	//Status Lamp
	if (!Motion.ReadOuput(LampRed))
	{
		Motion.SetOuput(LampRed);
		Motion.ResetOuput(ButtonStop);

		Motion.ResetOuput(LampGreen);
		Motion.ResetOuput(LampYellow);
	}
	//
}

void CHandlerMCDoc::LoopWait()
{
	//Status Lamp
	if (!Motion.ReadOuput(LampYellow))
	{
		Motion.SetOuput(LampYellow);
		Motion.ResetOuput(ButtonStop);

		Motion.ResetOuput(LampGreen);
		Motion.ResetOuput(LampRed);
	}
	//
	
}
void CHandlerMCDoc::InitTrayLoading()
{
	//khoi tao gia tri tray
	for (int i = 0; i < RowTray; i++)
		for (int j = 0; j < ColumnTray; j++)
		{
			PosXY[TrayLoading].at(i).at(j).status = true;
			PosXY[TrayLoading].at(i).at(j).unloading = FALSE;
		}
	m_OnStatusPictureLoading = true;//Hien thi cac vi tri sang len
									//
}

void CHandlerMCDoc::LoopStart()
{
	//Status Lamp
	if (!Motion.ReadOuput(LampGreen))
	{
		Motion.SetOuput(LampGreen);
		Motion.SetOuput(ButtonStart);

		Motion.ResetOuput(LampYellow);
		Motion.ResetOuput(LampRed);
		Motion.ResetOuput(ButtonStop);
	}
	//Safety
	if (!SafetyDoor())
	{
		AlarmOn();
		ActionStop();
	}

	switch (m_ActionStart)
	{
	case BufferLoading:
	{
		/*m_ActionStart = RobotLoadingCam;
		break;*/

		if(m_BufferLoading())
		{			
			m_trayLoading = 0;
			m_ActionStart = RobotLoadingCam;
			break;
		}
		break;
	}
	case RobotLoadingCam:
	{
		if (m_RobotLoadingCamMove())
		{
			m_RobotLoadingCAM = 0;
			m_ActionStart = RobotLoadingVision;
		}

		break;
	}
	case RobotLoadingVision:
	{
		switch (m_RobotLoadingVision())
		{
		case 1:
		{
			m_LoadingVision = 0;
			m_ActionStart = RobotUnloadingAndLoadingTest;
			break;
		}
		case 2:
		{
			m_LoadingVision = 0;
			m_ActionStart = RobotLoadingfirst;//Lan chay dau tien
			break;
		}
		default:
			break;
		}
	 break;
	}
	case RobotLoadingfirst://Lan chay dau tien
	{
		if (m_RobotLoadingtestFirtRun())
		{
			if (!m_DataTester[0].Action) { m_DataTester[0].Loading = false;}
			if (!m_DataTester[1].Action) { m_DataTester[1].Loading = false; }
			if (!m_DataTester[2].Action) { m_DataTester[2].Loading = false; }
			if (!m_DataTester[3].Action) { m_DataTester[3].Loading = false; }

			if (!m_DataTester[0].Loading && !m_DataTester[1].Loading && 
				!m_DataTester[2].Loading && !m_DataTester[3].Loading)
			{
				flagFirtrun = true;
			}
			m_LoadingTest = 0;
			m_ActionStart = RobotLoadingCam;
		}
		break;
	}
	case UnloadingTrayOKFull:
	{
		if(m_UnloadingTrayLoadingFull())
		{
			InitTrayLoading();
			m_ActionStart = BufferLoading;// Di chuyen toi vi tri lay CAM
			m_NoUnloadingFull = 0;//Bien toan cuc cua ham
			break;
		}
		break;
	}
	case RobotUnloadingAndLoadingTest://Bao go ca loading va unloading luon
	{
		if (m_RobotUnloadingAndLoadingTest())
		{
			m_ActionStart = RobotMoveTrayOKNG;
		}
		break;
	}
	case RobotMoveTrayOKNG:
	{
		if (m_FlagThuahang)
		{
			m_FlagThuahang = false;
		}
		//
		if (m_NumberTesterAct == 3 && m_StatusRun3Tester)//Co 3 tester hoat dong, tay le
		{
			m_NoRobotUnloadTest = 0;//Reset
		}
		//
		if (m_RobotMoveTrayOKNG())
		{
			//End Tray
			if (m_EndTray && (m_ResultTestSocket[0]== 0) && (m_ResultTestSocket[1] == 0) && 
				             (m_ResultTestSocket[2] == 0) && (m_ResultTestSocket[3] == 0))
			{
				SendDataEthernet("Ready()");
				m_NorobotmovetrayOKNG = 0;
				ActionStop();
				AfxMessageBox("End Tray Complete");
				break;
			}
			//
			m_NorobotmovetrayOKNG = 0;
			m_ActionStart = CheckTrayOKNGFull;
		}
		break;
	}
	case CheckTrayOKNGFull:
	{
		m_ActionStart = RobotLoadingCam;//tam thoi
		break;
	}
	case RobotActionEndTray:
	{
		if (ActionEndTray())
		{
			m_ActionStart = RobotMoveTrayOKNG;
		}
		break;
	}
	default:
		break;
	}
}
void CHandlerMCDoc::ResetVariable()
{
	 m_NorunAlineTool1 = 0;
	 m_NorunAlineTool2 = 0;
	 m_NorunAlinePickTool1 = 0;
	 m_NorunAlinePickTool2 = 0;
	 m_NorunAlinePickTool = 0;
	 m_RunVisionTool1 = 0;
	 m_RunVisionTool2 = 0;
	 m_CylinderAlineAction = 0;
	 m_BufferDataVision = "";
	 m_NumberButtonSafety = 0;
	 m_NumberButtonVision = 0;

	 //---Loading tray
	 m_trayLoading = 0;
	 m_countjog = 0;
	 m_countaline = 0;
	 m_Tool1Loading = false;
	 m_Tool2Loading = false;
	 m_FlagThuahang = false;
	 //---Robot Loading Cam
	 m_RobotLoadingCAM = 0;
	 m_RobotLoadingCAMTool1 = 0;
	 m_RobotLoadingCAMTool2 = 0;
	 //---Loading Vision
	 m_LoadingVision = 0;
	 m_NoVisionToo1 = 0;
	 m_NoVisionToo2 = 0;
	 Dx1 = 0, Dy1 = 0, Dx2 = 0, Dy2 = 0;
	 Dr1 = 0, Dr2 = 0;
	 flagFirtrun = false;
	 m_UsingVision = true;
	 //Loading Test
	 m_LoadingTest = 0;
	 m_NoLoadingTest = 0;
	 m_SelectToolLoading = 0;
	 m_flagtoolloading = false;
	 //Test Command
	 m_NoTestCommand = 0;
	 m_flagTestCommand = true;
	 m_StatusRun3Tester = false;
	 m_NoRunLoadingTool2 = 0;
	 //Result Test
	 n_ResultTest = 0;
	 m_ResultTestSocket[4];//Ban dau bang 0
	 m_ActionXilanhSocket1Result = 0;
	 m_ActionXilanhSocket2Result = 0;
	 m_ActionXilanhSocket3Result = 0;
	 m_ActionXilanhSocket4Result = 0;
	 //Robot Unload test
	 m_NoRobotUnloadTest = 0;
	 m_SocketUnloading = 0;
	 m_Tool1Unloading = false;
	 m_Tool2Unloading = false;
	 m_flagtoolunloading = false;
	 m_SaveResultTestTool1 = false;
	 m_SaveResultTestTool2 = false;
	 m_UnloadingLoading[4];
	 //Robot move tray OK/NG
	 m_NorobotmovetrayOKNG = 0;
	 m_NorobotmovetrayOKNG0 = 0;
	 m_NorobotmovetrayOKNG1 = 0;
	 
	 m_UnloadingTrayOK1 = 0;
	 m_UnloadingTrayNGLeft1 = 0;
	 m_UnloadingTrayNGRight1 = 0;
	 
	 m_ResulttestTool1Unloading = false;
	 m_ResulttestTool2Unloading = false;
	 m_ActionTool1Unloading = 0;
	 //Check tray OK NG full 
	 m_ActionDownZUnloading = 0;
	 m_CheckTrayNGLeftFull = false;
	 m_CheckTrayNGRightFull = false;
	
	 //m_OnStatusPictureLoading = false;
	 //m_OnStatusPictureUnloadingLeft = false;
	 //m_OnStatusPictureUnloadingRight = false;

	 //---Unloading tray
	 m_trayUnloading = 0;
	 m_flagDown = false;
	 m_NumberAline = 0;
	 //Unloading tray loading full
	 m_NoUnloadingFull = 0;
	 //Buffer
	 m_ActionXilanh = 0;
	 m_FlagListViewLog = false;
	 //manual
	 m_manualloading = false;
	 m_manualunloading = false;
	
	 OriginComplete = false;
	 //
	 m_StatusInitsocket = false;
	 m_StatusOriginZLoading = false;
	 m_StatusOriginZUnloading = false;

	 FlagMotionVisionDoneRobot = false;
	 FlagRevice = false;

	ActionOne = false;

	m_DataTester[0].Loading = true;
	m_DataTester[1].Loading = true;
	m_DataTester[2].Loading = true;
	m_DataTester[3].Loading = true;
	//End tray
	m_EndTray = false;
	Flag_pick_cam = false;
}
void CHandlerMCDoc::ViewDataList( CString m_data)
{
	//Add ListLog View
	m_DataListViewLog = m_data;
	m_FlagListViewLog = true;
}
/////////////////////////////  Loading Buffer        ////////////////////////////////
bool CHandlerMCDoc::m_BufferLoading()
{
	if (ReadInput(SSXL_AlineTray_Loading_Out) && !ReadInput(Detech_Tray_Up_Loading) &&
		ReadInput(SSXL_Do_Tray_Loading_Out_Trai) && ReadInput(SSXL_Do_Tray_Loading_Out_Phai) && (PosZ1Down == Motion.StatusGetActPos(AxisX)))
	{
		m_trayLoading = 3;
	}

	switch (m_trayLoading)
	{
	case 0://Reset xilanh va truc Z di xuong
	{
		if (ReadInput(SSXL_AlineTray_Loading_Out) && !ReadInput(Detech_Tray_Up_Loading) &&
			ReadInput(SSXL_Do_Tray_Loading_Out_Trai) && ReadInput(SSXL_Do_Tray_Loading_Out_Phai))
		{
			m_trayLoading = 3;
			break; 
		}
		if (!ReadInput(Detech_Tray_Up_Loading))//Keo xl do ve
		{
			AfxMessageBox("Dang co tray hang");
			m_operation = operation_stop;
			return 0;
		}
		if ((ReadInput(SSXL_Do_Tray_Loading_Out_Trai) && !ReadInput(Detech_Tray_Up_Loading))
			&& ReadInput(Detech_Tray_On_Z_Loading) && ReadInput(SSXL_Do_Tray_Loading_Out_Phai)
			&& (PosZ1Down == Motion.StatusGetActPos(AxisX)))//du dieu kien loading
		{
			m_trayLoading = 3;
		}
		if (!ReadInput(SSXL_AlineTray_Loading_In) && ReadInput(Detech_Tray_Up_Loading))//Keo xl aline lai
		{
			XilanhAlineTrayLoadingOff();
		}
		if ((!ReadInput(SSXL_Do_Tray_Loading_In_Trai) || !ReadInput(SSXL_Do_Tray_Loading_In_Phai)) &&
			  ReadInput(Detech_Tray_Up_Loading))//Keo xl do ve
		{
			XilanhDoTrayLoadingOff();
		}
	
		if (!ReadInput(SSXL_Chan_Tray_Loading_Nam))//Ha xl chan tray xuong
		{
			ChanTrayLoadingOff();
		}
		if (ReadInput(SSXL_AlineTray_Loading_In) && ReadInput(SSXL_Do_Tray_Loading_In_Trai) 
			&& ReadInput(SSXL_Do_Tray_Loading_In_Phai))//Run axis z loading
		{
			if (RunPosLoading(PosZ1Down))
			{
				m_trayLoading = 1;
				break;
			}
		}
		break;
	}
	case 1://Hang vao
	{
		if (!ReadInput(DetechTrayInput) && !ReadInput(Detech_Tray_On_Z_Loading) 
			&& ReadInput(Detech_Tray_In_Loading))//Bang tai chay
		{
			ConveyorLoadingOn();
		}
		if (ReadInput(SSXL_Chan_Tray_Loading_Nam) && ReadInput(Detech_Tray_On_Z_Loading) 
			&& !ReadInput(Detech_Tray_In_Loading) && ReadOutput(Conveyor_Loading))//Dung Bang tai 
		{
			Sleep(2000);
			ConveyorLoadingOff();
		}
		if (ReadInput(SSXL_Chan_Tray_Loading_Nam) && ReadInput(Detech_Tray_On_Z_Loading) 
			&& !ReadInput(Detech_Tray_In_Loading) && !ReadOutput(Conveyor_Loading))//Nang xl aline
		{
			ChanTrayLoadingOn();		
		}
		if (ReadInput(SSXL_Chan_Tray_Loading_Dung) && ReadInput(Detech_Tray_On_Z_Loading) 
			&& !ReadInput(Detech_Tray_In_Loading) && !ReadOutput(Conveyor_Loading)
			&& ReadInput(Detech_Tray_Up_Loading) && ReadInput(SSXL_AlineTray_Loading_In))//Nang tray len
		{
			m_trayLoading = 2;
			m_countjog = 0;
			break;
		}
		break;
	}
	case 2://Hang len
	{
			switch (m_countjog)
			{
			case 0://Jog Len voi toc do speed1 cham senser thi dung lai
			{
				Motion.JogRun(AxisX, DataMotor.SpeedJog1, DataMotor.Acc, DataMotor.Dec);
				if (!ReadInput(Detech_Tray_Up_Loading))
				{
					Sleep(50);
					Motion.JogStop(AxisX);
					m_countjog = 1;
					break;
				}
				break;
			}
			case 1://Jog xuong voi toc do speed2 het senser thi dung lai
			{
				Motion.JogRun(AxisX, 0 - DataMotor.SpeedJog2, DataMotor.Acc, DataMotor.Dec);
				if (ReadInput(Detech_Tray_Up_Loading))
				{				
					Motion.JogStop(AxisX);
					Sleep(50);
					m_countjog = 2;
					PointStopJogLoading = Motion.StatusGetActPos(AxisX);
					break;
				}
				break;
			}		
			case 2://Chay len 1 doan offset
			{
				if (RunPosLoading(PointStopJogLoading + OffsetJogLoadingZ1))
				{
					m_countjog = 3;
				}
				break;
			}
			case 3://xilanh do va ha truc z xuong
			{
				if ((ReadInput(SSXL_Do_Tray_Loading_In_Trai) /*&& !ReadInput(Detech_Tray_Up_Loading)*/)
					&& ReadInput(Detech_Tray_On_Z_Loading) && ReadInput(SSXL_Do_Tray_Loading_In_Phai))//Day xl do ra
				{
					XilanhDoTrayLoadingOn();
				}
				if ((ReadInput(SSXL_Do_Tray_Loading_Out_Trai) /*&& !ReadInput(Detech_Tray_Up_Loading)*/)
					&& ReadInput(Detech_Tray_On_Z_Loading) && ReadInput(SSXL_Do_Tray_Loading_Out_Phai))//Day xl do ra
				{
					if (RunPosLoading(PosZ1Down))
					{
						m_countjog = 4;
					}
				}
				break;
			}
			case 4://aline
			{
				if (ReadInput(SSXL_AlineTray_Loading_In) && !ReadInput(Detech_Tray_Up_Loading) &&
					ReadInput(SSXL_Do_Tray_Loading_Out_Trai) && ReadInput(SSXL_Do_Tray_Loading_Out_Phai) &&
					(m_countaline == 0))//Day xl aline ra
				{
					XilanhAlineTrayLoadingOn();
					m_countaline = 1;
				}
				if (ReadInput(SSXL_AlineTray_Loading_Out) && !ReadInput(Detech_Tray_Up_Loading) &&
					ReadInput(SSXL_Do_Tray_Loading_Out_Trai) && ReadInput(SSXL_Do_Tray_Loading_Out_Phai) &&
					(m_countaline == 1))//Keo xl aline lai
				{
					XilanhAlineTrayLoadingOff();
					m_countaline = 2;
				}
				if (ReadInput(SSXL_AlineTray_Loading_In) && !ReadInput(Detech_Tray_Up_Loading) &&
					ReadInput(SSXL_Do_Tray_Loading_Out_Trai) && ReadInput(SSXL_Do_Tray_Loading_Out_Phai) &&
					(m_countaline == 2))//Day xl aline ra
				{
					XilanhAlineTrayLoadingOn();
					m_countaline = 3;
				}
				if (ReadInput(SSXL_AlineTray_Loading_Out) && !ReadInput(Detech_Tray_Up_Loading) &&
					ReadInput(SSXL_Do_Tray_Loading_Out_Trai) && ReadInput(SSXL_Do_Tray_Loading_Out_Phai) &&
					(m_countaline == 3))//
				{
					Sleep(1000);
					m_trayLoading = 3;
				}
				break;
			}
			default:
				break;
			}

		break;
	}
	case 3:
	{
		if (ReadInput(SSXL_AlineTray_Loading_Out))
		{
			m_countjog = 0;
			m_countaline = 0;
			return true;
		}
		else
		{
			XilanhAlineTrayLoadingOn();
		}
		break;
	}
	default:
		break;
	}

	return 0;
	
}
/////////////////////////////  Robot Loading Cam     ////////////////////////////////

bool CHandlerMCDoc::m_RobotLoadingCamMove()
{
	if (m_Tool1Loading && m_Tool2Loading)//2 tay hut co cam
	{
		return true;
	}
	switch (m_RobotLoadingCAM)
	{
	case 0://Tool 1 loading vision
	{
		if (m_RobotLoadingCamMoveTool1())
		{
			Dx1 = 0, Dy1 = 0, Dx2 = 0, Dy2 = 0;
			Dr1 = 0, Dr2 = 0;
			m_RobotLoadingCAMTool1 = 0;
			m_RobotLoadingCAM = 1;
			break;
		}
		break;
	}
	case 1://Tool 2 loading vision
	{
		if (m_RobotLoadingCamMoveTool2())
		{
			m_RobotLoadingCAMTool2 = 0;
			m_RobotLoadingCAM = 2;
			break;
		}
		break;
	}
	case 2://Return Result
	{
		return true;
		break;
	}
	default:
		break;
	}

	return false;
}

bool CHandlerMCDoc::m_RobotLoadingCamMoveTool1()
{
	switch (m_RobotLoadingCAMTool1)
	{
	case 0://Tim tao do vi tri tray co hang
	{
		//Unloading tray loading full
		if (m_CheckTrayLoadFull() && !m_Tool1Loading && !m_Tool2Loading && Safety4ToolRobot() && !m_EndTray)		
		{
			m_ActionStart = UnloadingTrayOKFull;
			break;
			return false;
		}
		//End tray loading 
		if (m_CheckTrayLoadFull() && !m_Tool1Loading && !m_Tool2Loading && Safety4ToolRobot() && m_EndTray)
		{
			m_ActionStart = RobotActionEndTray;
			break;
			return false;
		}
		//
		if (Safety4ToolRobot())
		{
			for (int i = 0; i < RowTray; i++)
				for (int j = 0; j < ColumnTray; j++)
				{
					if (PosXY[0].at(i).at(j).status && !PosXY[0].at(i).at(j).unloading)
					{
						m_iLoading = i;
						m_jLoading = j;
						m_NoLoadingRun.Format("(%d,%d,0)", m_iLoading, m_jLoading);
						m_RobotLoadingCAMTool1 = 1;
						return false;
					}
				}
		}
		else
		{
			XilanhTool1Off();
			XilanhTool2Off();
			XilanhTool3Off();
			XilanhTool4Off();
		}
		break;
	}
	case 1://Truyen du lieu lay hang
	{
		if (Safety4ToolRobot())
		{
			SendDataEthernet(CmRunRobotLoadingTool1Up + m_NoLoadingRun);//Run Up
			m_RobotLoadingCAMTool1 = 2;
		}
		break;
	}
	case 2://Doi ro bot phan hoi done
	{
		if (Safety4ToolRobot())
		{
			if (MootionDoneRobot())
			{
				m_RobotLoadingCAMTool1 = 5;
				break;
			}
			while (ReadInput(Button_Start))
			{
				m_RobotLoadingCAMTool1 = 1;
			}
		}
		break;
	}
	//Viet them xi lanh
	case 5:
	{
		if (ReadInput(SSXL_Tool1_RobotUp))
		{
			XilanhTool1RobotLoadingOn();
		}
		else
		{
			Sleep(DelayCylinderTool1Robot);
			m_RobotLoadingCAMTool1 = 6;
		}
		break;
	}
	case 6:
	{
		m_NoLoadingRun.Format("(%d,%d,1)", m_iLoading, m_jLoading);//Run Down
		SendDataEthernet(CmRunRobotLoadingTool1Down + m_NoLoadingRun);
		m_RobotLoadingCAMTool1 = 7;
		break;
	}
	case 7:
	{
		if (MootionDoneRobot())
		{
			m_RobotLoadingCAMTool1 = 3;
			break;
		}
		while (ReadInput(Button_Start))
		{
			m_RobotLoadingCAMTool1 = 6;
		}
		break;
	}
	//Ket thuc viet them xilanh
	case 3://Hoan thanh Hut tool1
	{
		//PosXY[TrayLoading].at(m_iLoading).at(m_jLoading).status = false;
		//m_OnStatusPictureLoading = true;

		if (!ReadInput(Vaccum_Tool1_Robot))
		{
			VaccumTool1RobotLoadingOn();
			Sleep(DelayVaccumToolRobot1);
		}
		else
		{
			if (ReadInput(Vaccum_Tool1_Robot) && !ReadInput(SSXL_Tool1_RobotUp))
			{
				XilanhTool1RobotLoadingOff();
			}
		}
		if (ReadInput(Vaccum_Tool1_Robot) && ReadInput(SSXL_Tool1_RobotUp))
		{
			//Sleep(DelayVaccumToolRobot1);  
			m_RobotLoadingCAMTool1 = 4;
			m_NoRunLoadingTool2++;
		}
		//Khong hut duoc CAM
		if (!ReadInput(SSXL_Tool1_RobotUp) && !ReadInput(Vaccum_Tool1_Robot))
		{
			SendDataEthernet(CmRunRobotDownMore);//Ha them 2 mm
			m_RobotLoadingCAMTool1 = 8;

		}
		if (m_NoRunLoadingTool2 == 1000)
		{
			m_NoRunLoadingTool2 = 10;
		}
		break;
	}
	case 8:
	{
		if (flagLoadingTool1Error)
		{
			if (MootionDoneRobot())
			{
				Sleep(DelayVaccumToolRobot1);
			}
			if (MootionDoneRobot() && ReadInput(Vaccum_Tool1_Robot) /*&& !ReadInput(SSXL_Tool1_RobotUp)*/)
			{
				XilanhTool1RobotLoadingOff();
				m_RobotLoadingCAMTool1 = 4;
				break;
			}
			if (MootionDoneRobot() && !ReadInput(Vaccum_Tool1_Robot)/* && !ReadInput(SSXL_Tool1_RobotUp)*/)
			{
				AlarmOn();
				XilanhTool1RobotLoadingOff();
				flagLoadingTool1Error = false;
				SendDataEthernet("Down_More(80)");//Nang robot len 3cm
				AfxMessageBox("Vaccum Tool 1 Error");
				ActionStop();
			}
		}
		else
		{
			if (ReadInput(SSXL_Tool1_RobotUp))
			{
				XilanhTool1RobotLoadingOn();
				Sleep(200);
			}
			else
			{
				m_RobotLoadingCAMTool1 = 6;
				flagLoadingTool1Error = true;
				break;
			}
		}
		break;
	}
	case 4:
	{
		flagLoadingTool1Error = true;
		if (Safety4ToolRobot() && ReadInput(Vaccum_Tool1_Robot))
		{
			PosXY[TrayLoading].at(m_iLoading).at(m_jLoading).status = false;
			m_OnStatusPictureLoading = true;

			m_Tool1Loading = true;
			return true;
		}
		if (Safety4ToolRobot() && !ReadInput(Vaccum_Tool1_Robot))
		{
			AlarmOn();
			AfxMessageBox("Vaccum Tool 1 Error");
			ActionStop();
		}
		break;
	}
	default:
		break;
	}
	return false;
}
bool CHandlerMCDoc::m_RobotLoadingCamMoveTool2()
{
	if (m_NumberTesterAct == 1)//Chi co tay 1 hut, tay 2 khong hut, 1 tester hoat dong
	{
		return true;
	}
	if (((m_NoRunLoadingTool2 % 2) == 0) && (m_NumberTesterAct == 3))
	{
		m_StatusRun3Tester = true;
	}
	else
	{
		m_StatusRun3Tester = false;
	}

	if (m_NumberTesterAct == 3 && m_StatusRun3Tester)//Chi co tay 1 hut, tay 2 khong hut 3 tester hoat dong
	{
		return true;
	}
	switch (m_RobotLoadingCAMTool2)
	{
	case 0://Tim tao do vi tri tray co hang
	{
		//Het tray nhuwng tren tool 1 van con hang
		if (m_CheckTrayLoadFull() && m_Tool1Loading && !m_Tool2Loading)
		{
			m_FlagThuahang = true;
			m_RobotLoadingCAM = 0;
			m_ActionStart = RobotUnloadingAndLoadingTest;
			break;
		}
		if (Safety4ToolRobot())
		{
			for (int i = 0; i < RowTray; i++)
				for (int j = 0; j < ColumnTray; j++)
				{
					if (PosXY[0].at(i).at(j).status && !PosXY[0].at(i).at(j).unloading)
					{
						m_iLoading = i;
						m_jLoading = j;
						m_NoLoadingRun.Format("(%d,%d,0)", m_iLoading, m_jLoading);
						m_RobotLoadingCAMTool2 = 1;
						return false;
					}
				}
		}
		else
		{
			XilanhTool1Off();
			XilanhTool2Off();
			XilanhTool3Off();
			XilanhTool4Off();
		}
		break;
	}
	case 1://Truyen du lieu lay hang
	{
		if (Safety4ToolRobot())
		{
			SendDataEthernet(CmRunRobotLoadingTool2Up + m_NoLoadingRun);
			m_RobotLoadingCAMTool2 = 2;
		}
	
		break;
	}
	case 2://Doi ro bot phan hoi done
	{
		if (Safety4ToolRobot())
		{
			if (MootionDoneRobot())
			{
				m_RobotLoadingCAMTool2 = 5;
				break;
			}
			while (ReadInput(Button_Start))
			{
				m_RobotLoadingCAMTool2 = 1;
			}
		}
		break;
	}
	//Viet them xi lanh
	case 5:
	{
		if (ReadInput(SSXL_Tool2_RobotUp))
		{
			XilanhTool2RobotLoadingOn();
		}
		else
		{
			Sleep(DelayCylinderTool2Robot);
			m_RobotLoadingCAMTool2 = 6;
		}
		break;
	}
	case 6:
	{
		m_NoLoadingRun.Format("(%d,%d,1)", m_iLoading, m_jLoading);
		SendDataEthernet(CmRunRobotLoadingTool2Down + m_NoLoadingRun);
		m_RobotLoadingCAMTool2 = 7;
		break;
	}
	case 7:
	{
		if (MootionDoneRobot())
		{
			m_RobotLoadingCAMTool2 = 3;
			break;
		}
		while (ReadInput(Button_Start))
		{
			m_RobotLoadingCAMTool2 = 6;
		}
		break;
	}
	//Ket thu viet them xilanh
	case 3://Hoan thanh Hut tool2
	{
		//PosXY[TrayLoading].at(m_iLoading).at(m_jLoading).status = false;
		//m_OnStatusPictureLoading = true;

		if (!ReadInput(SSXL_Tool2_RobotUp) && !ReadInput(Vaccum_Tool2_Robot))
		{
			VaccumTool2RobotLoadingOn();
			Sleep(DelayVaccumToolRobot2);
		}
		if (!ReadInput(SSXL_Tool2_RobotUp) && ReadInput(Vaccum_Tool2_Robot))
		{
			XilanhTool2RobotLoadingOff();
		
		}
		//Khong hut dc CAM
		if (!ReadInput(SSXL_Tool2_RobotUp) && !ReadInput(Vaccum_Tool2_Robot))
		{
			SendDataEthernet(CmRunRobotDownMore);//Ha them 2 mm
			m_RobotLoadingCAMTool2 = 8;
			break;
		}
		if (ReadInput(SSXL_Tool2_RobotUp) && ReadInput(Vaccum_Tool2_Robot))
		{
			m_RobotLoadingCAMTool2 = 4;
		}

		break;
	}
	case 8:
	{
		if (flagLoadingTool2Error)
		{
			if (MootionDoneRobot())
			{
				Sleep(DelayVaccumToolRobot2);
			}
			if (MootionDoneRobot() && ReadInput(Vaccum_Tool2_Robot))
			{
				XilanhTool2RobotLoadingOff();
				m_RobotLoadingCAMTool2 = 4;
				break;
			}

			if (MootionDoneRobot() && !ReadInput(Vaccum_Tool2_Robot) /*&& !ReadInput(SSXL_Tool2_RobotUp)*/)
			{
				AlarmOn();
				XilanhTool2RobotLoadingOff();
				flagLoadingTool2Error = false;
				SendDataEthernet("Down_More(80)");//Nang robot len 8cm
				AfxMessageBox("Vaccum Tool 2 Error");
				ActionStop();
			}
		}
		else
		{
			if (ReadInput(SSXL_Tool2_RobotUp))
			{
				XilanhTool2RobotLoadingOn();
				Sleep(200);
			}
			else
			{
				m_RobotLoadingCAMTool2 = 6;
				flagLoadingTool2Error = true;
				break;
			}
		}
		break;
	}
	case 4:
	{
		flagLoadingTool2Error = true;
		if (Safety4ToolRobot() && ReadInput(Vaccum_Tool2_Robot))
		{
			PosXY[0].at(m_iLoading).at(m_jLoading).status = false;//add
			m_OnStatusPictureLoading = true;
			m_Tool2Loading = true;
			return true;
		}
		if (Safety4ToolRobot() && !ReadInput(Vaccum_Tool2_Robot))
		{
			AlarmOn();
			AfxMessageBox("Vaccum Tool 2 Error");
			ActionStop();
		}

		break;
	}
	default:
		break;
	}
	return false;
}

///////////////////////////// Robot Loanding Vision  ////////////////////////////////

int CHandlerMCDoc::m_RobotLoadingVision()
{
	switch (m_LoadingVision)
	{
	case 0:// Run to vision Tool1
	{
		if (m_UsingVision)
		{
			if (m_VisionToo1())//Su dung vision
			{
				m_NoVisionToo1 = 0;
				m_LoadingVision = 1;
				break;
			}
		}
		else
		{
			if (m_AlineToo1())//Khong dung vision
			{
				m_NorunAlineTool1 = 0;
				m_LoadingVision = 1;
				break;
			}
		}
		break;
	}
	case 1:// Run to vision Tool2
	{
		if (m_NumberTesterAct == 1)//Chi co tay 1 hut, tay 2 khong hut,1 tester hoat dong
		{
			m_NoVisionToo2 = 0;
			m_LoadingVision = 2;
			break;
		}
		if (m_NumberTesterAct == 3 && m_StatusRun3Tester)//Co 3 tester hoat dong
		{
			m_NoVisionToo2 = 0;
			m_LoadingVision = 2;
			break;
		}
		if (m_UsingVision)
		{
			if (m_VisionToo2())//Su dung vision
			{
				m_NoVisionToo2 = 0;
				m_LoadingVision = 2;
				break;
			}
		}
		else
		{
			if (m_AlineToo2())//Khong dung vision
			{
				m_NoVisionToo2 = 0;
				m_NorunAlineTool2 = 0;
				m_LoadingVision = 2;
			
				break;
			}
		}
		break;
	}
	case 2://Aline CAM
	{
		if (m_UsingVision)
		{
			m_LoadingVision = 3;
		}
		else
		{
			if (ReadInput(SSXL_Aline_BW))
			{
				XilanhAlineOn();
			}
			if (ReadInput(SSXL_Aline_FW))
			{
				m_LoadingVision = 5;
			}
		}
		break;
	}
	case 5://Pick Aline Cam
	{
		switch (m_NorunAlinePickTool)
		{
		case 0://Pick tool 1
		{
			if (m_AlineToo1Pick())
			{
				m_NorunAlinePickTool1 = 0;
				m_NorunAlinePickTool = 1;
			}
			break;
		}
		case 1://Dong Xilanh Aline 
		{
			if (ReadInput(SSXL_Aline_BW))
			{
				XilanhAlineOn();
			}
			if (ReadInput(SSXL_Aline_FW))
			{
				m_NorunAlinePickTool = 2;
			}
			break;
		}
		case 2://Pick tool 2
		{
			if (m_NumberTesterAct == 1)//Chi co tay 1 hut, tay 2 khong hut,1 tester hoat dong
			{
				m_NorunAlinePickTool2 = 0;
				m_NorunAlinePickTool = 3;
				break;
			}
			if (m_NumberTesterAct == 3 && m_StatusRun3Tester)//Co 3 tester hoat dong
			{
				m_NorunAlinePickTool2 = 0;
				m_NorunAlinePickTool = 3;
				break;
			}
			if (m_AlineToo2Pick())
			{
				m_NorunAlinePickTool2 = 0;
				m_NorunAlinePickTool = 3;
			}
			break;
		}
		case 3://Mo xi lanh aline
		{
			if (ReadInput(SSXL_Aline_FW))
			{
				XilanhAlineOff();
			}
			if (ReadInput(SSXL_Aline_BW))
			{
				m_LoadingVision = 3;
			}	
			break;
		}
		default:
			break;
		}

		break;
	}
	case 3://Doi tin hieu Vision done
	{
		m_NorunAlinePickTool = 0;
		if (MootionVisionDoneRobot() && Safety4ToolRobot())
		{
			m_LoadingVision = 4;
			break;
		}
		break;
	}
	case 4:
	{
		if (flagFirtrun)
		{
			return 1;
		}
		else
		{
			return 2;
		}
		break;
	}
	break;
	}
	return 0;
}
bool CHandlerMCDoc::CylinderAlineAction()
{
	switch (m_CylinderAlineAction)
	{
	case 0:
	{
		if (ReadInput(SSXL_Aline_BW))
		{
			XilanhAlineOn();
		}
		if (ReadInput(SSXL_Aline_FW))
		{
			m_CylinderAlineAction = 1;
		}
		break;
	}
	default:
		break;
	}

	return false;
}
bool CHandlerMCDoc::m_VisionToo1()
{
	switch (m_NoVisionToo1)
	{
	case 0://Robot Run toi vi tri vision
	{
		SendDataEthernet(CmRunRobotVisionTool1 + "(1,1)");
		m_NoVisionToo1 = 1;
		break;
	}
	case 1://doi robot phan hoi done
	{
		if (MootionDoneRobot())
		{
			if (!m_FlagListViewLog)
			{
				m_NoVisionToo1 = 2;
			}
		//	FlagMotionDoneRobot = false;
			break;
		}
		while (ReadInput(Button_Start))
		{
			m_NoVisionToo1 = 0;
		}
		break;
	}
	case 2://Ra lenh check Vision Tool1
	{
		//Phan anh Vuong Tuan anh viet vao day

		//int Dx1 = 0, Dy1 = 0,
		//float Dr1 = 0.0
		//
		switch (m_RunVisionTool1)
		{
	    case 0 :
		{
			if (functionResult(Dx1, Dy1, Dr1, 1, 0))
			{
				m_RunVisionTool1 = 1;
			}
			else
			{
				m_RunVisionTool1 = 2;
			}
			break;
		}
	    case 1:
	    {
			if (!m_FlagListViewLog)
			{
				m_DataListViewLog = strResult;
				m_FlagListViewLog = true;

				m_RunVisionTool1 = 3;
			}
		    break;
	    }
		case 2:
		{
			AfxMessageBox("Khong bat duoc doi tuong");
			m_RunVisionTool1 = 0;
			ActionStop();
			break;
		}
		case 3:
		{
			if (!m_FlagListViewLog)
			{
				m_NoVisionToo1 = 3;
			}
			break;
		}
		default:
			break;
		}
		//
		break;
	}
	case 3:
	{
		m_RunVisionTool1 = 0;
		return true;
		break;
	}
	default:
		break;
	}
	return false;
}
bool CHandlerMCDoc::m_VisionToo2()
{
	switch (m_NoVisionToo2)
	{
	case 0://Robot Run toi vi tri vision
	{
		SendDataEthernet(CmRunRobotVisionTool2 + "(2,1)");
		m_NoVisionToo2 = 1;
		break;
	}
	case 1://doi robot phan hoi done
	{
		if (MootionDoneRobot())
		{
			if (!m_FlagListViewLog)
			{
				m_NoVisionToo2 = 2;
			}
			break;
		}
		while (ReadInput(Button_Start))
		{
			m_NoVisionToo2 = 0;
		}
		break;
	}
	case 2://Ra lenh check Vision Tool2
	{
		//Phan anh Vuong Tuan anh viet vao day

		//int Dx2 = 0, Dy2 = 0;
		//float Dr2 = 0.0;
		//
		switch (m_RunVisionTool2)
		{
		case 0:
		{
			if (functionResult(Dx2, Dy2, Dr2, 0, 1))
			{
				m_RunVisionTool2 = 1;
			}
			else
			{
				m_RunVisionTool2 = 2;
			}
			break;
		}
		case 1:
		{
			if (!m_FlagListViewLog)
			{
				m_DataListViewLog = strResult;
				m_FlagListViewLog = true;

				m_RunVisionTool2 = 3;		
			}
			break;
		}
		case 2:
		{
			AfxMessageBox("Khong bat duoc doi tuong");
			m_RunVisionTool2 = 0;
			ActionStop();
			break;
		}
		case 3:
		{
			if (!m_FlagListViewLog)
			{
				m_NoVisionToo2 = 3;
			}
			break;
		}
		default:
			break;
		}
		//
		break;
	}
	case 3:
	{
		m_RunVisionTool2 = 0;
		return true;
		break;
	}
	default:
		break;
	}
	return false;
}
bool CHandlerMCDoc::m_AlineToo1()
{
	switch (m_NorunAlineTool1)
	{
	case 0://Robot den vi tri aline tren cao
	{
		if (Safety4ToolRobot())
		{
			SendDataEthernet(CmRunRobotAlineTool1 + "(1,0)");
			m_NorunAlineTool1 = 1;
		}
		break;
	}
	case 1://Ha xi lanh tool 1 robot
	{
		if (MootionDoneRobot())
		{
			if (ReadInput(SSXL_Tool1_RobotUp))
			{
				XilanhTool1On();
				Sleep(500);
		    }
			else
			{
				m_NorunAlineTool1 = 2;
			}
		}
		break;
	}
	case 2://Ha Robot xuong vi tri thap
	{
		if (ReadInput(SSXL_Aline_BW))
		{
			SendDataEthernet(CmRunRobotAlineTool1 + "(1,1)");
			m_NorunAlineTool1 = 3;
		}
		else
		{
			AlarmOn();
			AfxMessageBox("Error Sensor Aline");
			ActionStop();
		}
		break;
	}
	case 3://Nang li lanh tool1 len
	{
		if (MootionDoneRobot())
		{
			VaccumTool1Off();
			if (!ReadInput(Vaccum_Tool1_Robot) && !ReadInput(SSXL_Tool1_RobotUp))
			{
				Sleep(500);
				XilanhTool1Off();
			}
			if (!ReadInput(Vaccum_Tool1_Robot) && ReadInput(SSXL_Tool1_RobotUp))
			{
				m_NorunAlineTool1 = 4;
			}
		}
		break;
	}
	case 4:
	{
		return true;
		break;
	}
	default:
		break;
	}

	return false;
}

bool CHandlerMCDoc::m_AlineToo2()
{
	switch (m_NorunAlineTool2)
	{
	case 0://Robot den vi tri aline tren cao
	{
		if (Safety4ToolRobot())
		{
			SendDataEthernet(CmRunRobotAlineTool2 + "(1,0)");
			m_NorunAlineTool2 = 1;
		}
		break;
	}
	case 1://Ha xi lanh tool 2 robot
	{
		if (MootionDoneRobot())
		{
			if (ReadInput(SSXL_Tool2_RobotUp))
			{
				XilanhTool2On();
				Sleep(500);
			}
			else
			{
				m_NorunAlineTool2 = 2;
			}
		}
		break;
	}
	case 2://Ha Robot xuong vi tri thap
	{
		if (ReadInput(SSXL_Aline_BW))
		{
			SendDataEthernet(CmRunRobotAlineTool2 + "(1,1)");
			m_NorunAlineTool2 = 3;
		}
		else
		{
			AlarmOn();
			AfxMessageBox("Error Sensor Aline");
			ActionStop();
		}
		break;
	}
	case 3://Nang li lanh tool1 len
	{
		if (MootionDoneRobot())
		{
			VaccumTool2Off();
			if (!ReadInput(Vaccum_Tool2_Robot) && !ReadInput(SSXL_Tool2_RobotUp))
			{
				Sleep(500);
				XilanhTool2Off();
			}
			if (!ReadInput(Vaccum_Tool2_Robot) && ReadInput(SSXL_Tool2_RobotUp))
			{
				m_NorunAlineTool2 = 4;
			}
		}
		break;
	}
	case 4:
	{
		return true;
		break;
	}
	default:
		break;
	}

	return false;
}

bool CHandlerMCDoc::m_AlineToo1Pick()
{
	switch (m_NorunAlinePickTool1)
	{
	case 0://Robot den vi tri aline tren cao
	{
		if (Safety4ToolRobot())
		{
			SendDataEthernet(CmRunRobotAlinePickTool1 + "(1,0)");
			m_NorunAlinePickTool1 = 1;
		}
		break;
	}
	case 1://Ha xi lanh tool 2 robot
	{
		if (MootionDoneRobot())
		{
			if (ReadInput(SSXL_Tool1_RobotUp))
			{
				XilanhTool1On();
				Sleep(500);
			}
			else
			{
				m_NorunAlinePickTool1 = 2;
			}
		}
		break;
	}
	case 2://Ha Robot xuong vi tri thap
	{
		if (ReadInput(SSXL_Aline_FW))
		{
			SendDataEthernet(CmRunRobotAlinePickTool1 + "(1,1)");
			m_NorunAlinePickTool1 = 3;
		}
		else
		{
			AlarmOn();
			AfxMessageBox("Error Sensor Aline");
			ActionStop();
		}
		break;
	}
	case 3://Nang li lanh tool1 len
	{
		if (MootionDoneRobot())
		{
			if (!ReadInput(Vaccum_Tool1_Robot))
			{
				VaccumTool1On();
				Sleep(DelayVaccumToolRobot1);
				//Error vaccum
				if (!ReadInput(Vaccum_Tool1_Robot) || !ReadInput(SSXL_Aline_FW))
				{
					AlarmOn();
					m_NorunAlinePickTool1 = 2;
					ActionStop();
					SendDataEthernet("Down_More(80)");
					break;
				}
			}
			if (ReadInput(Vaccum_Tool1_Robot) && ReadInput(SSXL_Aline_FW))
			{
				XilanhAlineOff();
			}
			if (ReadInput(Vaccum_Tool1_Robot) && !ReadInput(SSXL_Tool1_RobotUp) && ReadInput(SSXL_Aline_BW))
			{
				
				XilanhTool1Off();
			}
			if (ReadInput(Vaccum_Tool1_Robot) && ReadInput(SSXL_Tool1_RobotUp) && ReadInput(SSXL_Aline_BW))
			{
				m_NorunAlinePickTool1 = 4;
			}

			
		}
		break;
	}
	case 4:
	{
		return true;
		break;
	}
	default:
		break;
	}

	return false;
}

bool CHandlerMCDoc::m_AlineToo2Pick()
{
	switch (m_NorunAlinePickTool2)
	{
	case 0://Robot den vi tri aline tren cao
	{
		if (Safety4ToolRobot())
		{
			SendDataEthernet(CmRunRobotAlinePickTool2 + "(1,0)");
			m_NorunAlinePickTool2 = 1;
		}
		break;
	}
	case 1://Ha xi lanh tool 2 robot
	{
		if (MootionDoneRobot())
		{
			if (ReadInput(SSXL_Tool2_RobotUp))
			{
				XilanhTool2On();
				Sleep(500);
			}
			else
			{
				m_NorunAlinePickTool2 = 2;
			}
		}
		break;
	}
	case 2://Ha Robot xuong vi tri thap
	{
		if (ReadInput(SSXL_Aline_FW))
		{
			SendDataEthernet(CmRunRobotAlinePickTool2 + "(1,1)");
			m_NorunAlinePickTool2 = 3;
		}
		else
		{
			AlarmOn();
			AfxMessageBox("Error Sensor Aline");
			ActionStop();
		}
		break;
	}
	case 3://Nang li lanh tool1 len
	{
		if (MootionDoneRobot())
		{
			if (!ReadInput(Vaccum_Tool2_Robot))
			{
				VaccumTool2On();
				Sleep(DelayVaccumToolRobot2);
				//Error vaccum tool2 robot
				if (!ReadInput(Vaccum_Tool2_Robot) || !ReadInput(SSXL_Aline_FW))
				{
					AlarmOn();
					m_NorunAlinePickTool2 = 2;
					ActionStop();
					SendDataEthernet("Down_More(80)");
					break;
				}

			}
			if (ReadInput(Vaccum_Tool2_Robot) && ReadInput(SSXL_Aline_FW))
			{
				XilanhAlineOff();
			}
			if (ReadInput(Vaccum_Tool2_Robot) && !ReadInput(SSXL_Tool2_RobotUp) && ReadInput(SSXL_Aline_BW))
			{
				XilanhTool2Off();
			}
			if (ReadInput(Vaccum_Tool2_Robot) && ReadInput(SSXL_Tool2_RobotUp) && ReadInput(SSXL_Aline_BW))
			{
				m_NorunAlinePickTool2 = 4;
			}
		}
		break;
	}
	case 4:
	{
		return true;
		break;
	}
	default:
		break;
	}

	return false;
}
///////////////////////////// Robot Loading Test 1   //////////////////////////////////

bool CHandlerMCDoc::m_RobotLoadingtestFirtRun()
{
	switch (m_LoadingTest)
	{
	case 0://Tester 0
	{
		if (!m_DataTester[0].Action)//Not Use
		{
			m_LoadingTest = 1;//chuyen sang loading tester 1	
			break;
		}
		//
		if (m_RobotLoadingtest0())
		{
			m_DataTester[0].Loading = false;//Tester 0 da co hang
			m_SelectToolLoading = 0;
			m_NoLoadingTest = 0;
			//if (m_DataTester[0].StatusTester)//Chua ra lenh test
			{
				m_TestCommand(m_LoadingTest);
			}
			m_LoadingTest = 1;//chuyen sang loading tester 1	
							  //	if (m_NumberTesterAct != 3)
			{
				if (!m_Tool1Loading && !m_Tool2Loading)//2 tool khong con hang
				{
					m_LoadingTest = 4;//Return true
					break;
				}
			}
		}
		break;
	}
	case 1://Tester 1
	{
		if (!m_DataTester[1].Action)//Not Use
		{
			m_LoadingTest = 2;//chuyen sang loading tester 1	
			break;
		}
		//
		if (m_RobotLoadingtest1())
		{
			m_DataTester[1].Loading = false;//Tester 1 da co hang
			m_SelectToolLoading = 0;
			m_NoLoadingTest = 0;
			//if (m_DataTester[1].StatusTester)//Chua ra lenh test
			{
				m_TestCommand(m_LoadingTest);
			}
			m_LoadingTest = 2;//chuyen sang loading tester 2
							  //if (m_NumberTesterAct != 3)
			{
				if (!m_Tool1Loading && !m_Tool2Loading)//2 tool khong con hang
				{
					m_LoadingTest = 4;//Return true
					break;
				}
			}
		}
		break;
	}
	case 2://Tester 2
	{
		if (!m_DataTester[2].Action)//Not Use
		{
			m_LoadingTest = 3;//chuyen sang loading tester 1	
			break;
		}
		//
		if (m_RobotLoadingtest2())
		{
			m_DataTester[2].Loading = false;//Tester 2 da co hang
			m_SelectToolLoading = 0;
			m_NoLoadingTest = 0;
			//if (m_DataTester[2].StatusTester)//Chua ra lenh test
			{
				m_TestCommand(m_LoadingTest);
			}
			m_LoadingTest = 3;//chuyen sang loading tester 3
							  //if (m_NumberTesterAct != 3)
			{
				if (!m_Tool1Loading && !m_Tool2Loading)//2 tool khong con hang
				{
					m_LoadingTest = 4;//Return true
					break;
				}
			}
		}
		break;
	}
	case 3://Tester 3
	{
		if (!m_DataTester[3].Action)//Not Use
		{
			m_LoadingTest = 4;//chuyen sang loading tester 1	
			break;
		}
		//
		if (m_RobotLoadingtest3())
		{
			m_DataTester[3].Loading = false;//Tester 3 da co hang
			m_SelectToolLoading = 0;
			m_NoLoadingTest = 0;
			//if (m_DataTester[3].StatusTester)//Chua ra lenh test
			{
				m_TestCommand(m_LoadingTest);
			}
			m_LoadingTest = 4;//Return true
							  //if (m_NumberTesterAct != 3)
			{
				if (!m_Tool1Loading && !m_Tool2Loading)//2 tool khong con hang
				{
					m_LoadingTest = 4;//Return true
					break;
				}
			}
		}

		break;
	}
	case 4://Result
	{
		return true;
	}
	default:
		break;
	}
	return false;
}

//Loading cho tester 0
bool CHandlerMCDoc::m_RobotLoadingtest0()
{
	switch (m_NoLoadingTest)
	{
	case 0://check Tester 1 co trong khong
	{
		if (m_DataTester[0].Loading)
		{
			m_NoLoadingTest = 1;//Co the loading cho tester 0
			break;
		}
		else
		{
			m_NoLoadingTest = 2; //Khong the loading cho tester 0
		}
		break;
	}
	case 1://Loading vao tester
	{
		if (m_RobotLoadingtest00())
		{
			m_SelectToolLoading = 0;
			m_NoLoadingTest = 2;
			break;
		}
		break;
	}
	case 2:
	{
		return true;
		break;
	}
	default:
		break;
	}
	return false;
}
bool CHandlerMCDoc::m_RobotLoadingtest00()
{
	switch (m_SelectToolLoading)
	{
	case 0://tool1 loading
	{
		if (m_Tool1Loading)
		{
			//Too1 co hang loading vao tester1
			m_DataBufferVison.Format("(%lf,%lf,%lf,1,0)", Dx1, Dy1, Dr1);
			SendDataEthernet(CmRunRobotLoadingSocket1Tool1Up + m_DataBufferVison);
			m_flagtoolloading = false;
			m_SelectToolLoading = 2;
		}
		else
		{
			//Tool1 khong co hang - chuyen tool2
			if (!ReadInput(Vaccum_Tool1_Robot))
			{
				m_SelectToolLoading = 1;
			}
			else
			{
				AfxMessageBox("Error process");
				ActionStop();
			}
			break;
		}
		break;

	}
	case 1://Tool2 Loading
	{
		if (m_Tool2Loading)
		{
			//Tool2 co hang loading vao tester1
			m_DataBufferVison.Format("(%lf,%lf,%lf,1,0)", Dx2, Dy2, Dr2);
			SendDataEthernet(CmRunRobotLoadingSocket1Tool2Up + m_DataBufferVison);
			m_flagtoolloading = true;
			m_SelectToolLoading = 2;
		}
		else
		{
			//Tool2 khong co hang 
			/*if (ReadInput(Vaccum_Tool2_Robot))
			{
				m_Tool2Loading = true;
			}
			else
			{
				AfxMessageBox("Tool 2 loading miss CAM");
				ActionStop();
			}
			break;*/
		}
		break;
	}
	case 2://Doi ket qua done cua robot
	{
		if (MootionDoneRobot())
		{
			m_SelectToolLoading = 4;
			break;
		}
		if (ReadInput(Button_Start))
		{
			m_SelectToolLoading = 0;
			while (ReadInput(Button_Start))
			{
			}
		}
		break;
	}
	//Them xi lanh
	case 4:
	{
		if (m_flagtoolloading)
		{
			XilanhTool2RobotLoadingOn();
		}
		else
		{
			XilanhTool1RobotLoadingOn();
		}
		if (!ReadInput(Socket1_Fw) && !ReadInput(Vaccum_Socket_1) && !ReadOutput(Socket_UP_1) && 
			((m_flagtoolloading && !ReadInput(SSXL_Tool2_RobotUp)) || (!m_flagtoolloading && !ReadInput(SSXL_Tool1_RobotUp))))
		{
			if (m_flagtoolloading)
			{
				m_DataBufferVison.Format("(%lf,%lf,%lf,1,1)", Dx2, Dy2, Dr2);
				SendDataEthernet(CmRunRobotLoadingSocket1Tool2Up + m_DataBufferVison);
				//SendDataEthernet(CmRunRobotLoadingSocket1Tool2Down);
				m_SelectToolLoading = 5;
				break;
			}
			else
			{
				m_DataBufferVison.Format("(%lf,%lf,%lf,1,1)", Dx1, Dy1, Dr1);
				SendDataEthernet(CmRunRobotLoadingSocket1Tool1Up + m_DataBufferVison);
				//SendDataEthernet(CmRunRobotLoadingSocket1Tool1Down);
				m_SelectToolLoading = 5;
				break;
			}
		}
		break;
	}
	case 5:
	{
		if (MootionDoneRobot())
		{
			m_SelectToolLoading = 6;
			break;
		}
		if (ReadInput(Button_Start))
		{
			m_SelectToolLoading = 4;
			while (ReadInput(Button_Start))
			{
			}
		}
		break;
	}
	case 6://Action Socket
	{
		switch (m_ActionXilanh)//Action
		{
		case 0 :
		{
			//Off vaccum tool hut cua robot
			if (m_flagtoolloading)
			{
				VaccumTool2RobotLoadingOff();
			}
			else
			{
				VaccumTool1RobotLoadingOff();
			}
			//Nang xi lanh len
			if (!ReadInput(SSXL_Tool1_RobotUp) && !ReadInput(Vaccum_Tool1_Robot))
			{ 
				Sleep(DelayVaccumToolRobot1);
				XilanhTool1RobotLoadingOff();
			}
			if (!ReadInput(SSXL_Tool2_RobotUp) && !ReadInput(Vaccum_Tool2_Robot))
			{
				Sleep(DelayVaccumToolRobot2);
				XilanhTool2RobotLoadingOff();
			}

			if (Safety4ToolRobot() && !ReadInput(Vaccum_Socket_1))
			{
				VaccumSocket1On();
				Sleep(DelayVaccumSocket1);
				//
				if (!ReadInput(Vaccum_Socket_1))//Vaccum socket 1 error tra ket qua NG
				{
					m_ResultTestSocket[0] = 2;
					m_SelectToolLoading = 3;
					VaccumSocket1Off();
					m_DataTester[0].StatusTester = false;
					if (m_flagtoolloading)
					{
						m_Tool2Loading = false;//Tool 2 khong con hang
					}
					else
					{
						m_Tool1Loading = false;//Tool 1 khong con hang
					}
					break;
				}
				//
			}
			if (Safety4ToolRobot() && ReadInput(Vaccum_Socket_1))
			{				
				m_ActionXilanh = 1;
				break;
			}
			break;
		}
		case 1://Keo xilanh vao
		{
			if (!ReadInput(Socket1_Fw) && ReadInput(Socket1_Rv))
			{
				XilanhSocket1BackWard();
			}
			
			if (ReadInput(Socket1_Fw) && !ReadInput(Socket1_Rv))
			{
				Sleep(DelayCylinderSocket1FwRv);
				m_ActionXilanh = 2;
			}
			break;
		}
		case 2://Up len
		{	
			if (ReadInput(Socket1_Fw) && !ReadInput(Socket1_Rv) && ReadInput(Socket1_Up) && ReadInput(Vaccum_Socket_1))
			{
				Sleep(DelayCylinderSocket1UpDown);
				XilanhSocket1Up();

				if (m_flagtoolloading)
				{
					m_Tool2Loading = false;//Tool 2 khong con hang
				}
				else
				{
					m_Tool1Loading = false;//Tool 1 khong con hang
				}
			}
			if (Safety4ToolRobot() && !ReadInput(Socket1_Up) && ReadInput(Vaccum_Socket_1))
			{
				m_SelectToolLoading = 3;
				m_DataTester[0].TotalCount++;
			}
			break;
		}
		default:
			break;
		}
		break;
	}
	//ket thuc them xi lanh
	case 3:
	{
		m_ActionXilanh = 0;
		return true;
		break;
	}
	default:
		break;
	}
	return false;
}

//loading cho tester 1
bool CHandlerMCDoc::m_RobotLoadingtest1()
{
	switch (m_NoLoadingTest)
	{
	case 0://check Tester 1 co trong khong
	{
		if (m_DataTester[1].Loading)
		{
			m_NoLoadingTest = 1;//Co the loading cho tester 1
			break;
		}
		else
		{
			return true; //Khong the loading cho tester 1
		}
		break;
	}
	case 1://Loading vao tester
	{
		if (m_RobotLoadingtest11())
		{
			m_SelectToolLoading = 0;
			m_NoLoadingTest = 2;
			break;
		}
		break;
	}
	case 2:
	{
		return true;
		break;
	}
	default:
		break;
	}
	return false;
}
bool CHandlerMCDoc::m_RobotLoadingtest11()
{
	switch (m_SelectToolLoading)
	{
	case 0://tool1 loading
	{
		if (m_Tool1Loading)
		{
			//Too1 co hang loading vao tester1
			m_DataBufferVison.Format("(%lf,%lf,%lf,2,0)", Dx1, Dy1, Dr1);
			SendDataEthernet(CmRunRobotLoadingSocket2Tool1Up + m_DataBufferVison);
			m_flagtoolloading = false;
			m_SelectToolLoading = 2;
		}
		else
		{
			//Tool1 khong co hang - chuyen tool2
			if (!ReadInput(Vaccum_Tool1_Robot))
			{
				m_SelectToolLoading = 1;
			}
			else
			{
				AfxMessageBox("Error process");
				ActionStop();
			}
			break;
		}
		break;
	}
	case 1://Tool2 Loading
	{
		if (m_Tool2Loading)
		{
			//Tool2 co hang loading vao tester1
			m_DataBufferVison.Format("(%lf,%lf,%lf,2,0)", Dx2, Dy2, Dr2);
			SendDataEthernet(CmRunRobotLoadingSocket2Tool2Up + m_DataBufferVison);
			m_flagtoolloading = true;
			m_SelectToolLoading = 2;
		}
		else
		{
			////Tool2 khong co hang  
			//if (ReadInput(Vaccum_Tool2_Robot))
			//{
			//	m_Tool2Loading = true;
			//}
			//else
			//{
			//	AfxMessageBox("Tool 2 loading miss CAM");
			//	ActionStop();
			//}
			//break;
		}
		break;
	}
	case 2://Doi ket qua done cua robot
	{
		if (MootionDoneRobot())
		{
			m_SelectToolLoading = 4;
			break;
		}
		if (ReadInput(Button_Start))
		{
			m_SelectToolLoading = 0;
			while (ReadInput(Button_Start))
			{
			}
		}
		break;
	}
	//Them xi lanh
	case 4:
	{
		if (m_flagtoolloading)
		{
			XilanhTool2RobotLoadingOn();
		}
		else
		{
			XilanhTool1RobotLoadingOn();
		}
		if (!ReadInput(Socket2_Fw) && !ReadInput(Vaccum_Socket_2) && !ReadOutput(Socket_UP_2) &&
			((m_flagtoolloading && !ReadInput(SSXL_Tool2_RobotUp)) || (!m_flagtoolloading && !ReadInput(SSXL_Tool1_RobotUp))))
		{
			if (m_flagtoolloading)
			{
				m_DataBufferVison.Format("(%lf,%lf,%lf,2,1)", Dx2, Dy2, Dr2);
				SendDataEthernet(CmRunRobotLoadingSocket2Tool2Up + m_DataBufferVison);
				//SendDataEthernet(CmRunRobotLoadingSocket2Tool2Down);
				m_SelectToolLoading = 5;
				break;
			}
			else
			{
				m_DataBufferVison.Format("(%lf,%lf,%lf,2,1)", Dx1, Dy1, Dr1);
				SendDataEthernet(CmRunRobotLoadingSocket2Tool1Up + m_DataBufferVison);
				//SendDataEthernet(CmRunRobotLoadingSocket2Tool1Down);
				m_SelectToolLoading = 5;
				break;
			}
		}
		break;
	}
	case 5://
	{
		if (MootionDoneRobot())
		{
			m_SelectToolLoading = 6;
			break;
		}
		if (ReadInput(Button_Start))
		{
			m_SelectToolLoading = 4;
			while (ReadInput(Button_Start))
			{
			}
		}
		break;
	}
	case 6://Action Socket
	{
		switch (m_ActionXilanh)
		{
		case 0://Action 
		{
			//Off vaccum tool hut cua robot
			if (m_flagtoolloading)
			{
				VaccumTool2RobotLoadingOff();				
			}
			else
			{
				VaccumTool1RobotLoadingOff();
			}
			//Nang xi lanh len
			if (!ReadInput(SSXL_Tool1_RobotUp) && !ReadInput(Vaccum_Tool1_Robot))
			{ 
				Sleep(DelayVaccumToolRobot1);
				XilanhTool1RobotLoadingOff();
			}
			if (!ReadInput(SSXL_Tool2_RobotUp) && !ReadInput(Vaccum_Tool2_Robot))
			{
				Sleep(DelayVaccumToolRobot2);
				XilanhTool2RobotLoadingOff();
			}
			if (Safety4ToolRobot() &&  !ReadInput(Vaccum_Socket_2))
			{ 
				VaccumSocket2On();
				Sleep(DelayVaccumSocket2);
				//
				if (!ReadInput(Vaccum_Socket_2))//Vaccum socket 2 error tra ket qua NG
				{
					m_ResultTestSocket[1] = 2;
					m_SelectToolLoading = 3;
					VaccumSocket2Off();
					m_DataTester[1].StatusTester = false;
					if (m_flagtoolloading)
					{
						m_Tool2Loading = false;//Tool 2 khong con hang
					}
					else
					{
						m_Tool1Loading = false;//Tool 1 khong con hang
					}
					break;
				}
				//
			}			
			if (Safety4ToolRobot() && ReadInput(Vaccum_Socket_2))
			{			
				m_ActionXilanh = 1;
				break;
			}
			break;
		}
		case 1:
		{
			if (!ReadInput(Socket2_Fw) && ReadInput(Socket2_Rv))
			{
				XilanhSocket2BackWard();
			}
			if (ReadInput(Socket2_Fw) && !ReadInput(Socket2_Rv))
			{
				Sleep(DelayCylinderSocket2FwRv);
				m_ActionXilanh = 2;
			}
			break;
		}
		case 2:
		{	
			if (ReadInput(Socket2_Fw) && !ReadInput(Socket2_Rv) && ReadInput(Socket2_Up) && ReadInput(Vaccum_Socket_2))
			{
				Sleep(DelayCylinderSocket2UpDown);
				XilanhSocket2Up();

				if (m_flagtoolloading)
				{
					m_Tool2Loading = false;//Tool 2 khong con hang
				}
				else
				{
					m_Tool1Loading = false;//Tool 1 khong con hang
				}

			}
			if (Safety4ToolRobot() && !ReadInput(Socket2_Up) && ReadInput(Vaccum_Socket_2))
			{
				m_SelectToolLoading = 3;
				m_DataTester[1].TotalCount++;
			}
			break;
		}
		default:
			break;
		}
		break;
	}
	//ket thuc them xi lanh
	case 3:
	{
		m_ActionXilanh = 0;
		return true;
		break;
	}
	default:
		break;
	}
	return false;
}

//loading cho tester 2
bool CHandlerMCDoc::m_RobotLoadingtest2()
{
	switch (m_NoLoadingTest)
	{
	case 0://check Tester 1 co trong khong
	{
		if (m_DataTester[2].Loading)
		{
			m_NoLoadingTest = 1;//Co the loading cho tester 2
			break;
		}
		else
		{
			return true; //Khong the loading cho tester 2
		}
		break;
	}
	case 1://Loading vao tester
	{
		if (m_RobotLoadingtest22())
		{
			m_SelectToolLoading = 0;
			m_NoLoadingTest = 2;
			break;
		}
		break;
	}
	case 2:
	{
		return true;
		break;
	}
	default:
		break;
	}
	return false;
}
bool CHandlerMCDoc::m_RobotLoadingtest22()
{
	switch (m_SelectToolLoading)
	{
	case 0://tool1 loading
	{
		if (m_Tool1Loading)
		{
			//Too1 co hang loading vao tester1
			m_DataBufferVison.Format("(%lf,%lf,%lf,3,0)", Dx1, Dy1, Dr1);
			SendDataEthernet(CmRunRobotLoadingSocket3Tool1Up + m_DataBufferVison);
			m_flagtoolloading = false;
			m_SelectToolLoading = 2;
		}
		else
		{		
			//Tool1 khong co hang - chuyen tool2
			if (!ReadInput(Vaccum_Tool1_Robot))
			{
				m_SelectToolLoading = 1;
			}
			else
			{
				AfxMessageBox("Error process");
				ActionStop();
			}
			break;
		}
		break;

	}
	case 1://Tool2 Loading
	{
		if (m_Tool2Loading)
		{
			//Tool2 co hang loading vao tester1
			m_DataBufferVison.Format("(%lf,%lf,%lf,3,0)", Dx2, Dy2, Dr2);
			SendDataEthernet(CmRunRobotLoadingSocket3Tool2Up + m_DataBufferVison);
			m_flagtoolloading = true;
			m_SelectToolLoading = 2;
		}
		else
		{
			//Tool2 khong co hang 
			/*if (ReadInput(Vaccum_Tool2_Robot))
			{
				m_Tool2Loading = true;
			}
			else
			{
				AfxMessageBox("Tool 2 loading miss CAM");
				ActionStop();		
			break;
			}*/
		}
		break;
	}
	case 2://Doi ket qua done cua robot
	{
		if (MootionDoneRobot())
		{
			m_SelectToolLoading = 4;
			break;
		}
		if (ReadInput(Button_Start))
		{
			m_SelectToolLoading = 0;
			while (ReadInput(Button_Start))
			{
			}
		}
		break;
	}
	//Them xi lanh
	case 4:
	{
		if (m_flagtoolloading)
		{
			XilanhTool2RobotLoadingOn();
		}
		else
		{
			XilanhTool1RobotLoadingOn();
		}
		if (!ReadInput(Socket3_Fw) && !ReadInput(Vaccum_Socket_3) && !ReadOutput(Socket_UP_3) &&
			((m_flagtoolloading && !ReadInput(SSXL_Tool2_RobotUp)) || (!m_flagtoolloading && !ReadInput(SSXL_Tool1_RobotUp))))
		{
			if (m_flagtoolloading)
			{
				m_DataBufferVison.Format("(%lf,%lf,%lf,3,1)", Dx2, Dy2, Dr2);
				SendDataEthernet(CmRunRobotLoadingSocket3Tool2Up + m_DataBufferVison);
				//SendDataEthernet(CmRunRobotLoadingSocket3Tool2Down);
				m_SelectToolLoading = 5;
				break;
			}
			else
			{
				m_DataBufferVison.Format("(%lf,%lf,%lf,3,1)", Dx1, Dy1, Dr1);
				SendDataEthernet(CmRunRobotLoadingSocket3Tool1Up + m_DataBufferVison);
				//SendDataEthernet(CmRunRobotLoadingSocket3Tool1Down);
				m_SelectToolLoading = 5;
				break;
			}
		}
		break;
	}
	case 5:
	{
		if (MootionDoneRobot())
		{
			m_SelectToolLoading = 6;
			break;
		}
		if (ReadInput(Button_Start))
		{
			m_SelectToolLoading = 4;
			while (ReadInput(Button_Start))
			{
			}
		}
		break;
	}
	case 6://Action Socket
	{
		switch (m_ActionXilanh)
		{
		case 0://Action
		{
			//Off vaccum tool hut cua robot
			if (m_flagtoolloading)
			{
				VaccumTool2RobotLoadingOff();
			}
			else
			{
				VaccumTool1RobotLoadingOff();
			}
			//
			if (!ReadInput(SSXL_Tool1_RobotUp) && !ReadInput(Vaccum_Tool1_Robot))
			{
				Sleep(DelayVaccumToolRobot1);
				XilanhTool1RobotLoadingOff();
			}
			if (!ReadInput(SSXL_Tool2_RobotUp) && !ReadInput(Vaccum_Tool2_Robot))
			{
				Sleep(DelayVaccumToolRobot2);
				XilanhTool2RobotLoadingOff();
			}
			if (Safety4ToolRobot() && !ReadInput(Vaccum_Socket_3))
			{
				VaccumSocket3On();
				Sleep(DelayVaccumSocket3);
				//
				if (!ReadInput(Vaccum_Socket_3))//Vaccum socket 3 error tra ket qua NG
				{
					m_ResultTestSocket[2] = 2;
					m_SelectToolLoading = 3;
					VaccumSocket3Off();
					m_DataTester[2].StatusTester = false;
					if (m_flagtoolloading)
					{
						m_Tool2Loading = false;//Tool 2 khong con hang
					}
					else
					{
						m_Tool1Loading = false;//Tool 1 khong con hang
					}
					break;
				}
				//
			}
			
			if (Safety4ToolRobot() && ReadInput(Vaccum_Socket_3))
			{
				m_ActionXilanh = 1;
				break;
			}
			break;
		}
		case 1:
		{
			if (!ReadInput(Socket3_Fw) && ReadInput(Socket3_Rv) && ReadInput(Vaccum_Socket_3))
			{
				Sleep(DelayCylinderSocket3FwRv);
				XilanhSocket3BackWard();
			}
			if (ReadInput(Socket3_Fw) && !ReadInput(Socket3_Rv) && ReadInput(Vaccum_Socket_3))
			{				
				m_ActionXilanh = 2;
			}
			break;
		}
		case 2:
		{
			if (ReadInput(Socket3_Fw) && !ReadInput(Socket3_Rv) && ReadInput(Vaccum_Socket_3) && ReadInput(Socket3_Up))
			{
				Sleep(DelayCylinderSocket3UpDown);
				XilanhSocket3Up();

				if (m_flagtoolloading)
				{
					m_Tool2Loading = false;//Tool 2 khong con hang
				}
				else
				{
					m_Tool1Loading = false;//Tool 1 khong con hang
				}
			}
			if (Safety4ToolRobot() && ReadInput(Vaccum_Socket_3) && !ReadInput(Socket3_Up))
			{
				m_SelectToolLoading = 3;
				m_DataTester[2].TotalCount++;
			}
			break;
			//
		}
		default:
			break;
		}
		break;
	}
	//ket thuc them xi lanh
	case 3:
	{
		m_ActionXilanh = 0;
		return true;
		break;
	}
	default:
		break;
	}
	return false;
}

//loading cho tester 3
bool CHandlerMCDoc::m_RobotLoadingtest3()
{
	switch (m_NoLoadingTest)
	{
	case 0://check Tester 1 co trong khong
	{
		if (m_DataTester[3].Loading)
		{
			m_NoLoadingTest = 1;//Co the loading cho tester 3
			break;
		}
		else
		{
			return true; //Khong the loading cho tester 3
		}
		break;
	}
	case 1://Loading vao tester
	{
		if (m_RobotLoadingtest33())
		{
			m_SelectToolLoading = 0;
			m_NoLoadingTest = 2;
			break;
		}
		break;
	}
	case 2:
	{
		return true;
		break;
	}
	default:
		break;
	}
	return false;
}
bool CHandlerMCDoc::m_RobotLoadingtest33()
{
	switch (m_SelectToolLoading)
	{
	case 0://tool1 loading
	{
		if (m_Tool1Loading)
		{
			//Too1 co hang loading vao tester1
			m_DataBufferVison.Format("(%lf,%lf,%lf,4,0)", Dx1, Dy1, Dr1);
			SendDataEthernet(CmRunRobotLoadingSocket4Tool1Up + m_DataBufferVison);
			m_flagtoolloading = false;
			m_SelectToolLoading = 2;
		}
		else
		{
			//Tool1 khong co hang - chuyen tool2
			if (!ReadInput(Vaccum_Tool1_Robot))
			{
				m_SelectToolLoading = 1;
			}
			else
			{
				AfxMessageBox("Error process");
			    ActionStop();
			}
			break;
		}
		break;

	}
	case 1://Tool2 Loading
	{
		if (m_Tool2Loading)
		{
			//Tool2 co hang loading vao tester1
			m_DataBufferVison.Format("(%lf,%lf,%lf,4,0)", Dx2, Dy2, Dr2);
			SendDataEthernet(CmRunRobotLoadingSocket4Tool2Up + m_DataBufferVison);
			m_flagtoolloading = true;
			m_SelectToolLoading = 2;
		}
		else
		{
			////Tool2 khong co hang 
			//if (ReadInput(Vaccum_Tool2_Robot))
			//{
			//	m_Tool2Loading = true;
			//}
			//else
			//{
			//	AfxMessageBox("Tool 2 loading miss CAM");
			//	ActionStop();
			//}
			//break;
		}
		break;
	}
	case 2://Doi ket qua done cua robot
	{
		if (MootionDoneRobot())
		{
			m_SelectToolLoading = 4;
			break;
		}
		if (ReadInput(Button_Start))
		{
			m_SelectToolLoading = 0;
			while (ReadInput(Button_Start))
			{
			}
		}
		break;
	}
	//Them xi lanh
	case 4:
	{
		if (m_flagtoolloading)
		{
			XilanhTool2RobotLoadingOn();
		}
		else
		{
			XilanhTool1RobotLoadingOn();
		}
		if (!ReadInput(Socket4_Fw) && !ReadInput(Vaccum_Socket_4) && !ReadOutput(Socket_UP_4) &&
			((m_flagtoolloading && !ReadInput(SSXL_Tool2_RobotUp)) || (!m_flagtoolloading && !ReadInput(SSXL_Tool1_RobotUp))))
		{
			if (m_flagtoolloading)
			{
				m_DataBufferVison.Format("(%lf,%lf,%lf,4,1)", Dx2, Dy2, Dr2);
				SendDataEthernet(CmRunRobotLoadingSocket4Tool2Up + m_DataBufferVison);
				//SendDataEthernet(CmRunRobotLoadingSocket4Tool2Down);
				m_SelectToolLoading = 5;
				break;
			}
			else
			{
				m_DataBufferVison.Format("(%lf,%lf,%lf,4,1)", Dx1, Dy1, Dr1);
				SendDataEthernet(CmRunRobotLoadingSocket4Tool1Up + m_DataBufferVison);
				//SendDataEthernet(CmRunRobotLoadingSocket4Tool1Down);
				m_SelectToolLoading = 5;
				break;
			}
		}
		break;
	}
	case 5:
	{
		if (MootionDoneRobot())
		{
			m_SelectToolLoading = 6;
			break;
		}
		if (ReadInput(Button_Start))
		{
			m_SelectToolLoading = 4;
			while (ReadInput(Button_Start))
			{
			}
		}
		break;
	}
	case 6://Action Socket
	{
		switch (m_ActionXilanh)
		{
		case 0://Action
		{
			//Off vaccum tool hut cua robot
			if (m_flagtoolloading)
			{
				VaccumTool2RobotLoadingOff();
			}
			else
			{
				VaccumTool1RobotLoadingOff();
			}
			if (!ReadInput(SSXL_Tool1_RobotUp) && !ReadInput(Vaccum_Tool1_Robot))
			{	
				Sleep(DelayCylinderTool1Robot);
				XilanhTool1RobotLoadingOff();		
			}
			if (!ReadInput(SSXL_Tool2_RobotUp) && !ReadInput(Vaccum_Tool2_Robot))
			{	
				Sleep(DelayCylinderTool2Robot);
				XilanhTool2RobotLoadingOff();				
			}
			if (Safety4ToolRobot() && !ReadInput(Vaccum_Socket_4))
			{ 
				VaccumSocket4On(); 
				Sleep(DelayVaccumSocket4);
				//
				if (!ReadInput(Vaccum_Socket_4))//Vaccum socket 4 error tra ket qua NG
				{
					m_ResultTestSocket[3] = 2;
					m_SelectToolLoading = 3;
					VaccumSocket4Off();
					m_DataTester[3].StatusTester = false;
					if (m_flagtoolloading)
					{
						m_Tool2Loading = false;//Tool 2 khong con hang
					}
					else
					{
						m_Tool1Loading = false;//Tool 1 khong con hang
					}
					break;
				}
				//
			}

			if (Safety4ToolRobot() && ReadInput(Vaccum_Socket_4))
			{
				m_ActionXilanh = 1;
				break;
			}
			break;
		}
		case 1:
		{
			if (!ReadInput(Socket4_Fw) && ReadInput(Socket4_Rv) && ReadInput(Vaccum_Socket_4))
			{				
				XilanhSocket4BackWard();
				Sleep(DelayCylinderSocket4FwRv);
			}
			if (ReadInput(Socket4_Fw) && !ReadInput(Socket4_Rv) /*&& ReadInput(Vaccum_Socket_4)*/)
			{			
				m_ActionXilanh = 2;
			}
			break;
		}
		case 2:
		{
			if (ReadInput(Socket4_Fw) && !ReadInput(Socket4_Rv) /*&& ReadInput(Vaccum_Socket_4)*/ && ReadInput(Socket4_Up))
			{
				XilanhSocket4Up();
				Sleep(DelayCylinderSocket4UpDown);

				if (m_flagtoolloading)
				{
					m_Tool2Loading = false;//Tool 2 khong con hang
				}
				else
				{
					m_Tool1Loading = false;//Tool 1 khong con hang
				}
			}
			if (Safety4ToolRobot() && ReadInput(Socket4_Fw) && !ReadInput(Socket4_Rv) /*&& ReadInput(Vaccum_Socket_4)*/ && !ReadInput(Socket4_Up))
			{
				m_SelectToolLoading = 3;
				m_DataTester[3].TotalCount++;
			}
			break;
		}
		default:
			break;
		}
		break;
	}
	//ket thuc them xi lanh
	case 3:
	{
		m_ActionXilanh = 0;
		return true;
		break;
	}
	default:
		break;
	}
	return false;
}

//
void CHandlerMCDoc::m_TestCommand(int m_Socketer)
{
	switch (m_Socketer)
	{
	case 0://Test Command Tester 1
	{
		//Dang Quang viet vao day
		m_SendData("1_2_2_2");
		m_DataTester[m_Socketer].StatusTester = false;
		break;
	}
	case 1://Test Command Tester 2
	{
		//Dang Quang viet vao day
		m_SendData("2_1_2_2");
		m_DataTester[m_Socketer].StatusTester = false;
		break;
	}
	case 2://Test Command Tester 3
	{
		//Dang Quang viet vao day
		m_SendData("2_2_1_2");
		m_DataTester[m_Socketer].StatusTester = false;
		break;
	}
	case 3://Test Command Tester 4
	{
		//Dang Quang viet vao day
		m_SendData("2_2_2_1");
		m_DataTester[m_Socketer].StatusTester = false;
		break;
	}
	default:
		break;
	}

}

bool CHandlerMCDoc::ActionXilanhSocket1Result()
{
	/*if (!ReadInput(Socket1_Fw) && ReadInput(Socket1_Rv) && ReadInput(Socket1_Up) && !ReadInput(Vaccum_Socket_1))
	{
		m_ActionXilanhSocket1Result = 0;
		return true;
	}*/
	switch (m_ActionXilanhSocket1Result)
	{
	case 0://xi lanh up ha xuong
	{
		if (!ReadInput(Socket1_Up))
		{
			XilanhSocket1Down();			
		}	
		if (ReadInput(Socket1_Up))
		{	
			Sleep(DelayCylinderSocket1UpDown);
			m_ActionXilanhSocket1Result = 1;
		}
		break;
	}
	case 1://Xi lanh forward  lui ra
	{
		if (ReadInput(Socket1_Fw) && !ReadInput(Socket1_Rv) && ReadInput(Socket1_Up))
		{
			XilanhSocket1ForWard();
		}
		if (!ReadInput(Socket1_Fw) && ReadInput(Socket1_Rv) && ReadInput(Socket1_Up))
		{
			m_ActionXilanhSocket1Result = 2;
		}
		break;
	}
	case 2://Off vaccum
	{
		if (!ReadInput(Socket1_Fw) && ReadInput(Socket1_Rv) && ReadInput(Socket1_Up))
		{
			VaccumSocket1Off();
		}
		if (!ReadInput(Socket1_Fw) && ReadInput(Socket1_Rv) && ReadInput(Socket1_Up) && !ReadInput(Vaccum_Socket_1))
		{
			m_ActionXilanhSocket1Result = 3;
		}
		break;
	}
	case 3:
	{
		return true;
		break;
	}
	default:
		break;
	}
	return false;
}

bool CHandlerMCDoc::ActionXilanhSocket2Result()
{
	//if (!ReadInput(Socket2_Fw) && ReadInput(Socket2_Rv) && ReadInput(Socket2_Up) && !ReadInput(Vaccum_Socket_2))
	//{
	//	m_ActionXilanhSocket2Result = 0;
	//	return true;
	//}
	switch (m_ActionXilanhSocket2Result)
	{
	case 0://xi lanh up ha xuong
	{
		if (!ReadInput(Socket2_Up))
		{
			XilanhSocket2Down();
		}
		if (ReadInput(Socket2_Up))
		{
			Sleep(DelayCylinderSocket2UpDown);
			m_ActionXilanhSocket2Result = 1;
		}		
		break;
	}
	case 1://Xi lanh forward  lui ra
	{
		if (ReadInput(Socket2_Fw) && !ReadInput(Socket2_Rv) && ReadInput(Socket2_Up))
		{
			XilanhSocket2ForWard();
		}
		if (!ReadInput(Socket2_Fw) && ReadInput(Socket2_Rv) && ReadInput(Socket2_Up))
		{
			m_ActionXilanhSocket2Result = 2;
		}
		break;
	}
	case 2://Off vaccum
	{
		if (!ReadInput(Socket2_Fw) && ReadInput(Socket2_Rv) && ReadInput(Socket2_Up))
		{
			VaccumSocket2Off();
		}
		if (!ReadInput(Socket2_Fw) && ReadInput(Socket2_Rv) && ReadInput(Socket2_Up) && !ReadInput(Vaccum_Socket_2))
		{
			m_ActionXilanhSocket2Result = 3;
		}
		break;
	}
	case 3:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}

bool CHandlerMCDoc::ActionXilanhSocket3Result()
{
	/*if (!ReadInput(Socket3_Fw) && ReadInput(Socket3_Rv) && ReadInput(Socket3_Up) && !ReadInput(Vaccum_Socket_3))
	{
		m_ActionXilanhSocket3Result = 0;
		return true;
	}*/
	switch (m_ActionXilanhSocket3Result)
	{
	case 0://xi lanh up ha xuong
	{
		if (!ReadInput(Socket3_Up))
		{
			XilanhSocket3Down();
		}
		if (ReadInput(Socket3_Up))
		{
			Sleep(DelayCylinderSocket3UpDown);
			m_ActionXilanhSocket3Result = 1;
		}
		break;
	}
	case 1://Xi lanh forward  lui ra
	{
		if (ReadInput(Socket3_Fw) && !ReadInput(Socket3_Rv) && ReadInput(Socket3_Up))
		{
			XilanhSocket3ForWard();
		}
		if (!ReadInput(Socket3_Fw) && ReadInput(Socket3_Rv) && ReadInput(Socket3_Up))
		{
			m_ActionXilanhSocket3Result = 2;
		}
		break;
	}
	case 2://Off vaccum
	{
		if (!ReadInput(Socket3_Fw) && ReadInput(Socket3_Rv) && ReadInput(Socket3_Up))
		{
			VaccumSocket3Off();
		}
		if (!ReadInput(Socket3_Fw) && ReadInput(Socket3_Rv) && ReadInput(Socket3_Up) && !ReadInput(Vaccum_Socket_3))
		{
			m_ActionXilanhSocket3Result = 3;
		}
		break;
	}
	case 3:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}

bool CHandlerMCDoc::ActionXilanhSocket4Result()
{
	/*if (!ReadInput(Socket4_Fw) && ReadInput(Socket4_Rv) && ReadInput(Socket4_Up) && !ReadInput(Vaccum_Socket_4))
	{
		m_ActionXilanhSocket4Result = 0;
		return true;
	}*/
	switch (m_ActionXilanhSocket4Result)
	{
	case 0://xi lanh up ha xuong
	{
		if (!ReadInput(Socket4_Up))
		{
			XilanhSocket4Down();
		}
		if (ReadInput(Socket4_Up))
		{
			Sleep(DelayCylinderSocket4UpDown);
			m_ActionXilanhSocket4Result = 1;
		}
		break;
	}
	case 1://Xi lanh forward  lui ra
	{
		if (ReadInput(Socket4_Fw) && !ReadInput(Socket4_Rv) && ReadInput(Socket4_Up))
		{
			XilanhSocket4ForWard();
		}
		if (!ReadInput(Socket4_Fw) && ReadInput(Socket4_Rv) && ReadInput(Socket4_Up))
		{
			m_ActionXilanhSocket4Result = 2;
		}
		break;
	}
	case 2://Off vaccum
	{
		if (!ReadInput(Socket4_Fw) && ReadInput(Socket4_Rv) && ReadInput(Socket4_Up))
		{
			VaccumSocket4Off();
		}
		if (!ReadInput(Socket4_Fw) && ReadInput(Socket4_Rv) && ReadInput(Socket4_Up) && !ReadInput(Vaccum_Socket_4))
		{
			m_ActionXilanhSocket4Result = 3;
		}
		break;
	}
	case 3:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}
///////////////////////////// Result Test  /////////////////////////////////////////
bool CHandlerMCDoc::m_ResultTest()
{
	//Dang Quang tra ket qua ve day

	//m_ResultTestSocket[0] = 1;//0: Doi ket qua  1:OK  2:NG
	//m_ResultTestSocket[1] = 1;//0: Doi ket qua  1:OK  2:NG
	//m_ResultTestSocket[2] = 1;//0: Doi ket qua  1:OK  2:NG
	//m_ResultTestSocket[3] = 1;//0: Doi ket qua  1:OK  2:NG

	//
	//Update trang thai
	for (int i = 0; i < 4; i++)
	{
		switch (m_ResultTestSocket[i])
		{
		case 0:
		{
			if (!m_DataTester[i].Loading)
			{
				m_DataTester[i].Status = "Testing";
			}
			break;
		}
		case 1:
		{
			if (!m_DataTester[i].Loading)
			{
				m_DataTester[i].Status = "OK";
			}
			break;
		}
		case 2:
		{
			if (!m_DataTester[i].Loading)
			{
				m_DataTester[i].Status = "NG";
			}
			break;
		}
		default:
			break;
		}

	}
	//View tester
	ActionOne = true;
	//Step 1
	if (!m_Tool1Loading && !m_Tool2Loading && //2 Tool loading khong co hang 
		!m_Tool1Unloading && !m_Tool1Unloading)//2 Tool unloading khong co hang quay ve lay hang
	{
		n_ResultTest = 2;//Quay ve loading CAM tu tray loading
	}
	//Step 2
	if (m_Tool1Loading || m_Tool2Loading)// Mot trong 2 tool loading co hang
	{
		n_ResultTest = 1;//Di chuyen toi vi tri unloading test phone jig lay CAM ra
	}
	//Step 3
	if ((m_Tool1Unloading && m_Tool2Unloading) && //2 tool unloading deu co hang
		!m_Tool1Loading && !m_Tool2Loading)//2 tool Loading deu co hang
	{
		n_ResultTest = 3;//Di chuyen toi vi tri tray OK/NG
	}

	return false;

}

///////////////////////////// Robot Unloading Test  ///////////////////////////////////
//Dang chinh sua
bool CHandlerMCDoc::m_RobotUnloadingAndLoadingTest()
{
	//Lua chon case hop ly
	if (Status_Loading_Unloading)
	{
		for (int i = 0; i<4; i++)
		{
			if ((m_ResultTestSocket[i] == 1) || (m_ResultTestSocket[i] == 2) && m_DataTester[i].Action)
			{
				m_NoRobotUnloadTest = i;
				Status_Loading_Unloading = false;
				break;
			}
			//else
			//{
			//	m_NoRobotUnloadTest = -1;
			//}
		}

	}
	else
	{
		if (!Status_Loading_Unloading)
		{
			//Run
			switch (m_NoRobotUnloadTest)
			{
			case 0://Unloading Socket 0
			{
				if (RobotUnloadingLoadingTest0())
				{
					m_UnloadingLoading[0] = 0;
					Status_Loading_Unloading = true;
					m_NoRobotUnloadTest = -1;
					return ReturnResultUnloadingLoading();//Add more
				}
				break;
			}
			case 1://Unloading Socket 1
			{
				if (RobotUnloadingLoadingTest1())
				{
					m_UnloadingLoading[1] = 0;
					Status_Loading_Unloading = true;
					m_NoRobotUnloadTest = -1;
					return ReturnResultUnloadingLoading();//Add more
				}
				break;
			}
			case 2://Unloading Socket 2
			{
				if (RobotUnloadingLoadingTest2())
				{
					m_UnloadingLoading[2] = 0;
					Status_Loading_Unloading = true;
					m_NoRobotUnloadTest = -1;
					return ReturnResultUnloadingLoading();//Add more
				}
				break;
			}
			case 3://Unloading Socket 3
			{
				if (RobotUnloadingLoadingTest3())
				{
					m_UnloadingLoading[3] = 0;
					Status_Loading_Unloading = true;
					m_NoRobotUnloadTest = -1;
					return ReturnResultUnloadingLoading();//Add more
				}
				break;
			}
			default:
			{
				break;
			}
			}
		}
		//return ReturnResultUnloadingLoading();
	}

	return false;
}
//
bool CHandlerMCDoc::RobotUnloadingLoadingTest0()
{
	switch (m_UnloadingLoading[0])
	{
	case 0://Unloading truoc
	{
		if (RobotUnloadingTest0())
		{
			m_DataTester[0].Loading = true;//Tester 0 trong
			m_DataTester[0].StatusTester = true;// Tester khong co lenh test
			m_SocketUnloading = 0;//Bien ham chinh lop 1
			m_ResultTestSocket[0] = 0;//Reset ket qua test
			m_UnloadingLoading[0] = 1;//Next
		}
		break;
	}
	case 1://Loading sau
	{
		if (m_RobotLoadingtest0())
		{
			m_DataTester[0].Loading = false;//Tester 0 da co hang
			m_SelectToolLoading = 0;// bien ham chinh lop 2
			m_NoLoadingTest = 0;//bien ham chinh lop 1
			//if (m_DataTester[0].StatusTester && !ReadInput(Socket1_Rv) && !ReadInput(Socket1_Up))//Chua ra lenh test
			if (m_DataTester[0].StatusTester && ReadInput(Socket1_Fw) && !ReadInput(Socket1_Rv) && !ReadInput(Socket1_Up) && ReadInput(Vaccum_Socket_1))
			{
				m_TestCommand(0);//Ra lenh test cua tester 0
			}
			m_UnloadingLoading[0] = 2;//Next
		}
		break;
	}
	case 2:
	{
		return true;	
	}
	default:
		break;
	}

	return false;
}

bool CHandlerMCDoc::RobotUnloadingLoadingTest1()
{
	switch (m_UnloadingLoading[1])
	{
	case 0://Unloading truoc
	{
		if (RobotUnloadingTest1())
		{
			m_DataTester[1].Loading = true;//Tester 1 trong
			m_DataTester[1].StatusTester = true;// Tester khong co lenh test
			m_SocketUnloading = 0;//Bien ham chinh lop 1
			m_ResultTestSocket[1] = 0;//Reset ke qua test
			m_UnloadingLoading[1] = 1;//Next
		}
		break;
	}
	case 1://Loading sau
	{
		if (m_RobotLoadingtest1())
		{
			m_DataTester[1].Loading = false;//Tester 1 da co hang
			m_SelectToolLoading = 0;// bien ham chinh lop 2
			m_NoLoadingTest = 0;//bien ham chinh lop 1
			//if (m_DataTester[1].StatusTester && !ReadInput(Socket2_Rv) && !ReadInput(Socket2_Up))//Chua ra lenh test
			if (m_DataTester[1].StatusTester && ReadInput(Socket2_Fw) && !ReadInput(Socket2_Rv) && !ReadInput(Socket2_Up) && ReadInput(Vaccum_Socket_2))
			{
				m_TestCommand(1);//Ra lenh test cua tester 0
			}
			m_UnloadingLoading[1] = 2;//Next
		}
		break;
	}
	case 2:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}

bool CHandlerMCDoc::RobotUnloadingLoadingTest2()
{
	switch (m_UnloadingLoading[2])
	{
	case 0://Unloading truoc
	{
		if (RobotUnloadingTest2())
		{
			m_DataTester[2].Loading = true;//Tester 2 trong
			m_DataTester[2].StatusTester = true;// Tester khong co lenh test
			m_SocketUnloading = 0;//Bien ham chinh lop 1
			m_ResultTestSocket[2] = 0;//Reset ke qua test
			m_UnloadingLoading[2] = 1;//Next
		}
		break;
	}
	case 1://Loading sau
	{
		if (m_RobotLoadingtest2())
		{
			m_DataTester[2].Loading = false;//Tester 1 da co hang
			m_SelectToolLoading = 0;// bien ham chinh lop 2
			m_NoLoadingTest = 0;//bien ham chinh lop 1
			//if (m_DataTester[2].StatusTester && !ReadInput(Socket3_Rv) && !ReadInput(Socket3_Up))//Chua ra lenh test
			if (m_DataTester[2].StatusTester && ReadInput(Socket3_Fw) && !ReadInput(Socket3_Rv) && !ReadInput(Socket3_Up) && ReadInput(Vaccum_Socket_3))

			{
				m_TestCommand(2);//Ra lenh test cua tester 0
			}
			m_UnloadingLoading[2] = 2;//Next
		}
		break;
	}
	case 2:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}

bool CHandlerMCDoc::RobotUnloadingLoadingTest3()
{
	switch (m_UnloadingLoading[3])
	{
	case 0://Unloading truoc
	{
		if (RobotUnloadingTest3())
		{
			m_DataTester[3].Loading = true;//Tester 3 trong
			m_DataTester[3].StatusTester = true;// Tester khong co lenh test
			m_SocketUnloading = 0;//Bien ham chinh lop 1
			m_ResultTestSocket[3] = 0;//Reset ke qua test
			m_UnloadingLoading[3] = 1;//Next
		}
		break;
	}
	case 1://Loading sau
	{
		if (m_RobotLoadingtest3())
		{
			m_DataTester[3].Loading = false;//Tester 1 da co hang
			m_SelectToolLoading = 0;// bien ham chinh lop 2
			m_NoLoadingTest = 0;//bien ham chinh lop 1
			//if (m_DataTester[3].StatusTester && !ReadInput(Socket4_Rv) && !ReadInput(Socket4_Up))//Chua ra lenh test
			if (m_DataTester[3].StatusTester && ReadInput(Socket4_Fw) && !ReadInput(Socket4_Rv) && !ReadInput(Socket4_Up) && ReadInput(Vaccum_Socket_4))

			{
				m_TestCommand(3);//Ra lenh test cua tester 0
			}
			m_UnloadingLoading[3] = 2;//Next
		}
		break;
	}
	case 2:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}

bool CHandlerMCDoc::ReturnResultUnloadingLoading()
{
	if (m_FlagThuahang)
	{
		return true;
	}
	switch (m_NumberTesterAct)
	{
	case 1://Chi co 1 Tool Hoat dong
	{	
		//Tool1 Unloading co hang va tool1 loading khong co hang  
		if (m_Tool1Unloading && !m_Tool1Loading && 
			ReadInput(Vaccum_Tool3_Robot) && !ReadInput(Vaccum_Tool1_Robot) && Safety4ToolRobot())
		{
			return true;
		}
		break;
	}
	case 2:
	{
		//Tool1 Unloading co hang va tool1 loading khong co hang  
		if (m_Tool1Unloading && !m_Tool1Loading && m_Tool2Unloading && !m_Tool2Loading &&
			ReadInput(Vaccum_Tool3_Robot) && !ReadInput(Vaccum_Tool1_Robot) && 
			ReadInput(Vaccum_Tool4_Robot) && !ReadInput(Vaccum_Tool2_Robot) && Safety4ToolRobot())
		{
			return true;
		}
		break;
	}
	case 3:
	{
		if (m_Tool1Unloading && !m_Tool1Loading &&
			ReadInput(Vaccum_Tool3_Robot) && !ReadInput(Vaccum_Tool1_Robot) && m_StatusRun3Tester &&
		    Safety4ToolRobot())
		{
			return true;
		}
		break;
	}
	case 4:
	{
		//Tool1 Unloading co hang va tool1 loading khong co hang  
		if (m_Tool1Unloading && !m_Tool1Loading && m_Tool2Unloading && !m_Tool2Loading &&
			ReadInput(Vaccum_Tool3_Robot) && !ReadInput(Vaccum_Tool1_Robot) &&
			ReadInput(Vaccum_Tool4_Robot) && !ReadInput(Vaccum_Tool2_Robot) && Safety4ToolRobot())
		{
			return true;
		}
		break;
	}
	default:
		return false;
		break;
	}
	return false;
}
//Unloading Tester 0
bool CHandlerMCDoc::RobotUnloadingTest0()
{
	switch (m_SocketUnloading)
	{
	case 0://Wait Result Test
	{
		//Co ket qua test thi moi cho robot gap ra
		if (m_ResultTestSocket[0] == 1 || m_ResultTestSocket[0] == 2)
		{
			m_SocketUnloading = 1;
		}
		break;
	}
	case 1://Tool3
	{
		if (m_Tool1Unloading && m_Tool2Unloading)
		{
			//2 tool deu co hang
			m_SocketUnloading = 4;
			break;
		}
		//
		if (!m_Tool1Unloading && !m_DataTester[0].Loading && !m_DataTester[0].StatusTester && 
			!ReadInput(Socket1_Fw) && Safety4ToolRobot())
		{
			//Tool 1 Khong co hang
			SendDataEthernet(CmRunRobotUnloadingSocket1Tool3Up);
			m_SocketUnloading = 5;
			m_flagtoolunloading = false;
			//m_Tool1Unloading = true;//Tool 1 co hang tren tool
			m_SaveResultTestTool1 = GetResultTool(0);
			break;
		}
		
		if(ReadInput(Vaccum_Tool3_Robot) && ReadInput(SSXL_Tool3_RobotUp))
		{
			//Tool1 da co hang
			m_SocketUnloading = 2;//Chuyen tool2
		}

		break;
	}
	case 2://Tool4
	{
			if (!m_Tool2Unloading && !m_DataTester[0].Loading && !m_DataTester[0].StatusTester && 
				!ReadInput(Socket1_Fw) && Safety4ToolRobot())
			{
				//Tool 2 khong co hang
				SendDataEthernet(CmRunRobotUnloadingSocket1Tool4Up);
				m_SocketUnloading = 5;
				m_flagtoolunloading = true;
				//m_Tool2Unloading = true;//Tool 2 co hang tren tool	
				m_SaveResultTestTool2 = GetResultTool(0);
				break;
			}
			if (ReadInput(Vaccum_Tool3_Robot) && ReadInput(Vaccum_Tool4_Robot))
			{
				//2 Tool da co hang san
				AfxMessageBox("2 Tool unloading co hang");
				ActionStop();
				return false;
			}
			break;
	}
	case 5:
	{
		if (MootionDoneRobot())
		{

			if (m_flagtoolunloading)
			{
				//Them :Ha xi lanh xuong
				if (ReadInput(SSXL_Tool4_RobotUp) && !ReadInput(Vaccum_Tool4_Robot))
				{
					XilanhTool2RobotUnloadingOn();		
				}
				//Ha truc z robot xuong
				if (!m_Tool2Unloading && !m_DataTester[0].Loading && !m_DataTester[0].StatusTester &&
					!ReadInput(Socket1_Fw) && !ReadInput(SSXL_Tool4_RobotUp))
				{
					SendDataEthernet(CmRunRobotUnloadingSocket1Tool4Down);
					m_SocketUnloading = 6;
				}
			}
			else
			{
				//Them : Ha xi lanh xuong
				if (ReadInput(SSXL_Tool3_RobotUp) && !ReadInput(Vaccum_Tool3_Robot))
				{
					XilanhTool1RobotUnloadingOn();
				}
				//Ha tuc z robot xuong
				if (!m_Tool2Unloading && !m_DataTester[0].Loading && !m_DataTester[0].StatusTester &&
					!ReadInput(Socket1_Fw) && !ReadInput(SSXL_Tool3_RobotUp))
				{
					SendDataEthernet(CmRunRobotUnloadingSocket1Tool3Down);
					m_SocketUnloading = 6;
				}
			}
		}
		break;
	}
	case 6:
	{
		if (MootionDoneRobot())
		{
			m_SocketUnloading = 3;
		}
		//
		while (ReadInput(Button_Start))
		{
			m_SocketUnloading = 5;
		}
		//
		break;
	}
	case 3://Doi ket qua done cua robot
	{
		//Them
		if (m_flagtoolunloading)
		{
			if (!ReadInput(SSXL_Tool4_RobotUp) && !ReadInput(Vaccum_Tool4_Robot))
			{
				VaccumTool2RobotUnloadingOn();
			}
			if (!ReadInput(SSXL_Tool4_RobotUp) && ReadInput(Vaccum_Tool4_Robot))
			{
				Sleep(DelayVaccumToolRobot4);
				XilanhTool2RobotUnloadingOff();
			}
		}
		else
		{
			if (!ReadInput(SSXL_Tool3_RobotUp) && !ReadInput(Vaccum_Tool3_Robot))
			{
				VaccumTool1RobotUnloadingOn();
			}
			if (!ReadInput(SSXL_Tool3_RobotUp) && ReadInput(Vaccum_Tool3_Robot))
			{
				Sleep(DelayVaccumToolRobot3);
				XilanhTool1RobotUnloadingOff();
			}
		}
		//them safety 4 xi lanh
		if (MootionDoneRobot() && Safety4ToolRobot() && ( m_flagtoolunloading && ReadInput(Vaccum_Tool4_Robot)  ||
			                                            (!m_flagtoolunloading && ReadInput(Vaccum_Tool3_Robot))))
		{
			m_SocketUnloading = 4;
			if (m_flagtoolunloading)
			{
				m_Tool2Unloading = true;//Tool 2 co hang tren tool	
				if (m_ResultTestSocket[0] == 1) { m_ResulttestTool2Unloading = true; }
				if (m_ResultTestSocket[0] == 2) { m_ResulttestTool2Unloading = false; }
			}
			else
			{
				m_Tool1Unloading = true;//Tool 1 co hang tren tool	
				if (m_ResultTestSocket[0] == 1) { m_ResulttestTool1Unloading = true; }
				if (m_ResultTestSocket[0] == 2) { m_ResulttestTool1Unloading = false; }
			}

			if (m_ResultTestSocket[0] == 2) { m_DataTester[0].NGCount++; }
			if (m_ResultTestSocket[0] == 1) { m_DataTester[0].GoodCount++; }

			m_ResultTestSocket[0] = 0;
			m_DataTester[0].Loading = true;
			break;
		}
		//
		while (ReadInput(Button_Start))
		{
			if (m_flagtoolunloading)
			{
				m_Tool2Unloading = false;
			}
			else
			{
				m_Tool1Unloading = false;
			}
			m_SocketUnloading = 1;
		}
		//
		break;
	}
	case 4:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}
//Unloading Tester 1
bool CHandlerMCDoc::RobotUnloadingTest1()
{
	switch (m_SocketUnloading)
	{
	case 0:
	{
		//Co ket qua test thi moi cho robot gap ra
		if (m_ResultTestSocket[1] == 1 || m_ResultTestSocket[1] == 2)
		{
			m_SocketUnloading = 1;
		}
		break;
	}
	case 1://Tool1
	{
		if (m_Tool1Unloading && m_Tool2Unloading)
		{
			//2 tool deu co hang
			m_SocketUnloading = 4;
			break;
		}
		//Them : Ha xi lanh xuong
		/*if (ReadInput(SSXL_Tool3_RobotUp) && !ReadInput(Vaccum_Tool3_Robot) && !m_Tool1Unloading)
		{
			XilanhTool1RobotUnloadingOn();
			Sleep(DataSleep);
		}*/
		//
		if (!m_Tool1Unloading && !ReadInput(Socket2_Fw) && Safety4ToolRobot())
		{
			//Tool 1 Khong co hang
			SendDataEthernet(CmRunRobotUnloadingSocket2Tool3Up) ;
			m_SocketUnloading = 5;
			//m_Tool1Unloading = true;//Tool 1 co hang
			m_flagtoolunloading = false;
			m_SaveResultTestTool1 = GetResultTool(1);
		}
		if (ReadInput(SSXL_Tool3_RobotUp) && ReadInput(Vaccum_Tool3_Robot))
		{
			//Tool1 da co hang
			m_SocketUnloading = 2;//Chuyen tool2
		}
		break;
	}
	case 2://Tool2
	{
		//Them :Ha xi lanh xuong
		//if (ReadInput(SSXL_Tool4_RobotUp) && !ReadInput(Vaccum_Tool4_Robot))
		//{
		//	XilanhTool2RobotUnloadingOn();
		//	Sleep(DataSleep);
		//}
		if (!m_Tool2Unloading && !ReadInput(Socket2_Fw) && Safety4ToolRobot())
		{
			//Tool 1 Khong co hang
			SendDataEthernet(CmRunRobotUnloadingSocket2Tool4Up);
			m_SocketUnloading = 5;
			m_flagtoolunloading = true;
			m_SaveResultTestTool2 = GetResultTool(1);
		}
		else
		{
			//2 Tool da co hang san
			//AfxMessageBox("2 Tool unloading co hang");
			return false;
		}
		break;
	}
	case 5:
	{
		if (MootionDoneRobot())
		{
			if (m_flagtoolunloading)
			{
				//Them :Ha xi lanh xuong
				if (ReadInput(SSXL_Tool4_RobotUp) && !ReadInput(Vaccum_Tool4_Robot))
				{
					XilanhTool2RobotUnloadingOn();
				}
				//Ha tuc z robot xuong
				if (!m_Tool2Unloading && !m_DataTester[1].Loading && !m_DataTester[1].StatusTester &&
					!ReadInput(Socket2_Fw) && !ReadInput(SSXL_Tool4_RobotUp))
				{
					SendDataEthernet(CmRunRobotUnloadingSocket2Tool4Down);
					m_SocketUnloading = 6;
				}

			}
			else
			{
				//Them : Ha xi lanh xuong
				if (ReadInput(SSXL_Tool3_RobotUp) && !ReadInput(Vaccum_Tool3_Robot))
				{
					XilanhTool1RobotUnloadingOn();
				}
				//Ha tuc z robot xuong
				if (!m_Tool2Unloading && !m_DataTester[1].Loading && !m_DataTester[1].StatusTester &&
					!ReadInput(Socket2_Fw) && !ReadInput(SSXL_Tool3_RobotUp))
				{
					SendDataEthernet(CmRunRobotUnloadingSocket2Tool3Down);
					m_SocketUnloading = 6;
				}

			}
		}
		break;
	}
	case 6:
	{
		if (MootionDoneRobot())
		{
			m_SocketUnloading = 3;
		}
		//
		while (ReadInput(Button_Start))
		{
			m_SocketUnloading = 5;
		}
		//
		break;
	}
	case 3://Do ket qua done cua robot
	{
		//Them
		if (m_flagtoolunloading)
		{
			if (!ReadInput(SSXL_Tool4_RobotUp) && !ReadInput(Vaccum_Tool4_Robot))
			{
				VaccumTool2RobotUnloadingOn();
			}
			if (!ReadInput(SSXL_Tool4_RobotUp) && ReadInput(Vaccum_Tool4_Robot))
			{
				Sleep(DelayVaccumToolRobot4);
				XilanhTool2RobotUnloadingOff();
			}
		}
		else
		{
			if (!ReadInput(SSXL_Tool3_RobotUp) && !ReadInput(Vaccum_Tool3_Robot))
			{
				VaccumTool1RobotUnloadingOn();
			}
			if (!ReadInput(SSXL_Tool3_RobotUp)  &&  ReadInput(Vaccum_Tool3_Robot))
			{
				Sleep(DelayVaccumToolRobot3);
				XilanhTool1RobotUnloadingOff();
			}
		}
		if (MootionDoneRobot() && Safety4ToolRobot() && ( m_flagtoolunloading && ReadInput(Vaccum_Tool4_Robot) ||
		                                             	(!m_flagtoolunloading && ReadInput(Vaccum_Tool3_Robot))))
		{
			m_SocketUnloading = 4;
			if (m_flagtoolunloading)
			{
				m_Tool2Unloading = true;//Tool 2 co hang tren tool	
				if (m_ResultTestSocket[1] == 1) { m_ResulttestTool2Unloading = true; }
				if (m_ResultTestSocket[1] == 2) { m_ResulttestTool2Unloading = false; }
			}
			else
			{
				m_Tool1Unloading = true;//Tool 1 co hang tren tool	
				if (m_ResultTestSocket[1] == 1) { m_ResulttestTool1Unloading = true; }
				if (m_ResultTestSocket[1] == 2) { m_ResulttestTool1Unloading = false; }
			}

			if (m_ResultTestSocket[1] == 2) { m_DataTester[1].NGCount++; }
			if (m_ResultTestSocket[1] == 1) { m_DataTester[1].GoodCount++; }

			m_ResultTestSocket[1] = 0;
			m_DataTester[1].Loading = true;
			break;
		}

		while (ReadInput(Button_Start))
		{
			if (m_flagtoolunloading)
			{
				m_Tool2Unloading = false;
			}
			else
			{
				m_Tool1Unloading = false;
			}
			m_SocketUnloading = 1;
		}
		//
		break;
	}
	case 4:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}
//Unloading Tester 2
bool CHandlerMCDoc::RobotUnloadingTest2()
{
	switch (m_SocketUnloading)
	{
	case 0://Tool1
	{
		//Co ket qua test thi moi cho robot gap ra
		if (m_ResultTestSocket[2] == 1 || m_ResultTestSocket[2] == 2)
		{
			m_SocketUnloading = 1;
		}
		break;
	}
	case 1://Tool1
	{
		if (m_Tool1Unloading && m_Tool2Unloading)
		{
			//2 tool deu co hang
			m_SocketUnloading = 4;
			break;
		}
		//Them : Ha xi lanh xuong
		//if (ReadInput(SSXL_Tool3_RobotUp) && !ReadInput(Vaccum_Tool3_Robot) && !m_Tool1Unloading)
		//{
		//	XilanhTool1RobotUnloadingOn();
		//	Sleep(DataSleep);
		//}
		//
		if (!m_Tool1Unloading && !ReadInput(Socket3_Fw) && Safety4ToolRobot())
		{
			//Tool 1 Khong co hang
			SendDataEthernet(CmRunRobotUnloadingSocket3Tool3Up );
			m_SocketUnloading = 5;
			m_flagtoolunloading = false;
			m_SaveResultTestTool1 = GetResultTool(2);
		}
		if (ReadInput(SSXL_Tool3_RobotUp) && ReadInput(Vaccum_Tool3_Robot))
		{
			//Tool1 da co hang
			m_SocketUnloading = 2;//Chuyen tool2
		}
		break;
	}
	case 2://Tool2
	{
		if (m_Tool1Unloading && m_Tool2Unloading)
		{
			//2 tool deu co hang
			m_SocketUnloading = 4;
			break;
		}
		//Them :Ha xi lanh xuong
		//if (ReadInput(SSXL_Tool4_RobotUp) && !ReadInput(Vaccum_Tool4_Robot))
		//{
		//	XilanhTool2RobotUnloadingOn();
		//	Sleep(DataSleep);
		//}
		if (!m_Tool2Unloading && !ReadInput(Socket3_Fw) && Safety4ToolRobot())
		{
			//Tool 1 Khong co hang
			SendDataEthernet(CmRunRobotUnloadingSocket3Tool4Up);
			m_SocketUnloading = 5;
			m_flagtoolunloading = true;
			m_SaveResultTestTool2 = GetResultTool(2);
		}
		else
		{
			//2 Tool da co hang san
			//AfxMessageBox("2 Tool unloading co hang");
			return false;
		}
		break;
	}
	case 5:
	{
		if (MootionDoneRobot())
		{
			if (m_flagtoolunloading)
			{
				//Them :Ha xi lanh xuong
				if (ReadInput(SSXL_Tool4_RobotUp) && !ReadInput(Vaccum_Tool4_Robot))
				{
					XilanhTool2RobotUnloadingOn();		
				}
				//Ha tuc z robot xuong
				if (!m_Tool2Unloading && !m_DataTester[1].Loading && !m_DataTester[1].StatusTester &&
					!ReadInput(Socket3_Fw) && !ReadInput(SSXL_Tool4_RobotUp))
				{
					SendDataEthernet(CmRunRobotUnloadingSocket3Tool4Down /*+ "(3,1)"*/);
					m_SocketUnloading = 6;
				}

			}
			else
			{
				//Them : Ha xi lanh xuong
				if (ReadInput(SSXL_Tool3_RobotUp) && !ReadInput(Vaccum_Tool3_Robot))
				{
					XilanhTool1RobotUnloadingOn();
				}
				//Ha tuc z robot xuong
				if (!m_Tool2Unloading && !m_DataTester[1].Loading && !m_DataTester[1].StatusTester &&
					!ReadInput(Socket3_Fw) && !ReadInput(SSXL_Tool3_RobotUp))
				{
					SendDataEthernet(CmRunRobotUnloadingSocket3Tool3Down);
					m_SocketUnloading = 6;
				}

			}
		}
		break;
	}
	case 6:
	{
		if (MootionDoneRobot())
		{
			m_SocketUnloading = 3;
		}
		//
		while (ReadInput(Button_Start))
		{
			m_SocketUnloading = 5;
		}
		//
		break;
	}
	case 3://Do ket qua done cua robot
	{
		//Them
		if (m_flagtoolunloading)
		{
			if (!ReadInput(SSXL_Tool4_RobotUp) && !ReadInput(Vaccum_Tool4_Robot))
			{
				VaccumTool2RobotUnloadingOn();
			}
			if (!ReadInput(SSXL_Tool4_RobotUp) && ReadInput(Vaccum_Tool4_Robot))
			{
				Sleep(DelayVaccumToolRobot4);
				XilanhTool2RobotUnloadingOff();
			}
		}
		else
		{
			if (!ReadInput(SSXL_Tool3_RobotUp) && !ReadInput(Vaccum_Tool3_Robot))
			{
				VaccumTool1RobotUnloadingOn();
			}
			if (!ReadInput(SSXL_Tool3_RobotUp) && ReadInput(Vaccum_Tool3_Robot))
			{
				Sleep(DelayVaccumToolRobot3);
				XilanhTool1RobotUnloadingOff();
			}
		}
		if (MootionDoneRobot() && Safety4ToolRobot() && (m_flagtoolunloading && ReadInput(Vaccum_Tool4_Robot) ||
			(!m_flagtoolunloading && ReadInput(Vaccum_Tool3_Robot))))
		{
			m_SocketUnloading = 4;
			if (m_flagtoolunloading)
			{
				m_Tool2Unloading = true;//Tool 2 co hang tren tool	
				if (m_ResultTestSocket[2] == 1) { m_ResulttestTool2Unloading = true; }
				if (m_ResultTestSocket[2] == 2) { m_ResulttestTool2Unloading = false; }
			}
			else
			{
				m_Tool1Unloading = true;//Tool 1 co hang tren tool	
				if (m_ResultTestSocket[2] == 1) { m_ResulttestTool1Unloading = true; }
				if (m_ResultTestSocket[2] == 2) { m_ResulttestTool1Unloading = false; }
			}

			if (m_ResultTestSocket[2] == 2) { m_DataTester[2].NGCount++; }
			if (m_ResultTestSocket[2] == 1) { m_DataTester[2].GoodCount++; }

			m_ResultTestSocket[2] = 0;
			m_DataTester[2].Loading = true;
			break;
		}

		while (ReadInput(Button_Start))
		{
			if (m_flagtoolunloading)
			{
				m_Tool2Unloading = false;
			}
			else
			{
				m_Tool1Unloading = false;
			}
			m_SocketUnloading = 1;
		}
		//
		break;
	}
	case 4:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}
//Unloading Tester 3
bool CHandlerMCDoc::RobotUnloadingTest3()
{
	switch (m_SocketUnloading)
	{
	case 0://Tool1
	{
		//Co ket qua test thi moi cho robot gap ra
		if (m_ResultTestSocket[3] == 1 || m_ResultTestSocket[3] == 2)
		{
			m_SocketUnloading = 1;
		}
		break;
	}
	case 1://Tool1
	{
		if (m_Tool1Unloading && m_Tool2Unloading)
		{
			//2 tool deu co hang
			m_SocketUnloading = 4;
			break;
		}
		//Them : Ha xi lanh xuong
		//if (ReadInput(SSXL_Tool3_RobotUp) && !ReadInput(Vaccum_Tool3_Robot) && !m_Tool1Unloading)
		//{
		//	XilanhTool1RobotUnloadingOn();
		//	Sleep(DataSleep);
		//}
		//
		if (!m_Tool1Unloading && !ReadInput(Socket4_Fw) && Safety4ToolRobot())
		{
			//Tool 1 Khong co hang
			SendDataEthernet(CmRunRobotUnloadingSocket4Tool3Up);
			m_SocketUnloading = 5;
			//m_Tool1Unloading = true;
			m_flagtoolunloading = false;
			m_SaveResultTestTool1 = GetResultTool(3);
		}
		if (ReadInput(SSXL_Tool3_RobotUp) && ReadInput(Vaccum_Tool3_Robot))
		{
			//Tool1 da co hang
			m_SocketUnloading = 2;//Chuyen tool2
		}
		break;
	}
	case 2://Tool2
	{
		//Them :Ha xi lanh xuong
		/*if (ReadInput(SSXL_Tool4_RobotUp) && !ReadInput(Vaccum_Tool4_Robot))
		{
			XilanhTool2RobotUnloadingOn();
			Sleep(DataSleep);
		}*/
		if (!m_Tool2Unloading && !ReadInput(Socket4_Fw) && Safety4ToolRobot())
		{
			//Tool 1 Khong co hang
			SendDataEthernet(CmRunRobotUnloadingSocket4Tool4Up);
			m_SocketUnloading = 5;
			//m_Tool2Unloading = true;
			m_flagtoolunloading = true;
			m_SaveResultTestTool2 = GetResultTool(3);
		}
		else
		{
			//2 Tool da co hang san
			//AfxMessageBox("2 Tool unloading co hang");
			return false;
		}
		break;
	}
	case 5:
	{
		if (MootionDoneRobot())
		{
			if (m_flagtoolunloading)
			{
				//Them :Ha xi lanh xuong
				if (ReadInput(SSXL_Tool4_RobotUp) && !ReadInput(Vaccum_Tool4_Robot))
				{
					XilanhTool2RobotUnloadingOn();
				}
				//Ha tuc z robot xuong
				if (!m_Tool2Unloading && !m_DataTester[1].Loading && !m_DataTester[1].StatusTester &&
					!ReadInput(Socket4_Fw) && !ReadInput(SSXL_Tool4_RobotUp))
				{
					SendDataEthernet(CmRunRobotUnloadingSocket4Tool4Down);
					m_SocketUnloading = 6;
				}

			}
			else
			{
				//Them : Ha xi lanh xuong
				if (ReadInput(SSXL_Tool3_RobotUp) && !ReadInput(Vaccum_Tool3_Robot))
				{
					XilanhTool1RobotUnloadingOn();;
				}
				//Ha tuc z robot xuong
				if (!m_Tool2Unloading && !m_DataTester[1].Loading && !m_DataTester[1].StatusTester &&
					!ReadInput(Socket4_Fw) && !ReadInput(SSXL_Tool3_RobotUp))
				{
					SendDataEthernet(CmRunRobotUnloadingSocket4Tool3Down);
					m_SocketUnloading = 6;
				}
			}
		}
		break;
	}
	case 6:
	{
		if (MootionDoneRobot())
		{
			m_SocketUnloading = 3;
		}
		//
		while (ReadInput(Button_Start))
		{
			m_SocketUnloading = 5;
		}
		//
		break;
	}
	case 3://Do ket qua done cua robot
	{
		//Them
		if (m_flagtoolunloading)
		{
			if (!ReadInput(SSXL_Tool4_RobotUp) && !ReadInput(Vaccum_Tool4_Robot))
			{
				VaccumTool2RobotUnloadingOn();
			}
			if (!ReadInput(SSXL_Tool4_RobotUp) && ReadInput(Vaccum_Tool4_Robot))
			{
				Sleep(DelayVaccumToolRobot4);
				XilanhTool2RobotUnloadingOff();
			}
		}
		else
		{
			if (!ReadInput(SSXL_Tool3_RobotUp) && !ReadInput(Vaccum_Tool3_Robot))
			{
				VaccumTool1RobotUnloadingOn();
			}
			if (!ReadInput(SSXL_Tool3_RobotUp) && ReadInput(Vaccum_Tool3_Robot))
			{
				Sleep(DelayVaccumToolRobot3);
				XilanhTool1RobotUnloadingOff();
			}
		}
		if (MootionDoneRobot() && Safety4ToolRobot() && (m_flagtoolunloading && ReadInput(Vaccum_Tool4_Robot) ||
			(!m_flagtoolunloading && ReadInput(Vaccum_Tool3_Robot))))
		{
			m_SocketUnloading = 4;
			//View tester
			//m_DataTester[3].Status = "Empty";
			//ActionOne = true;
			if (m_flagtoolunloading)
			{
				m_Tool2Unloading = true;//Tool 2 co hang tren tool	
				if (m_ResultTestSocket[3] == 1) { m_ResulttestTool2Unloading = true; }
				if (m_ResultTestSocket[3] == 2) { m_ResulttestTool2Unloading = false; }
			}
			else
			{
				m_Tool1Unloading = true;//Tool 1 co hang tren tool	
				if (m_ResultTestSocket[3] == 1) { m_ResulttestTool1Unloading = true; }
				if (m_ResultTestSocket[3] == 2) { m_ResulttestTool1Unloading = false; }
			}

			if (m_ResultTestSocket[3] == 2) { m_DataTester[3].NGCount++; }
			if (m_ResultTestSocket[3] == 1) { m_DataTester[3].GoodCount++; }

			m_ResultTestSocket[3] = 0;
			m_DataTester[3].Loading = true;
			break;
		}

		while (ReadInput(Button_Start))
		{
			if (m_flagtoolunloading)
			{
				m_Tool2Unloading = false;
			}
			else
			{
				m_Tool1Unloading = false;
			}
			m_SocketUnloading = 1;
		}
		//
		break;
	}
	case 4:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}

bool CHandlerMCDoc::Safety4ToolRobot()
{
	if (ReadInput(SSXL_Tool1_RobotUp) && ReadInput(SSXL_Tool2_RobotUp) &&
		ReadInput(SSXL_Tool3_RobotUp) && ReadInput(SSXL_Tool4_RobotUp))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

//Get ket qua test tren 2 tool
bool CHandlerMCDoc::GetResultTool(int m_Socket)
{
	switch (m_ResultTestSocket[m_Socket])
	{
	case 0:
	{
		AfxMessageBox("Ket qua khong xac dinh");
		ActionStop();
		return false;
		break;
	}
	case 1:
	{
		return true;
	}
	case 2:
	{
		return false;
	}
	default:
	{
		AfxMessageBox("Ket qua khong xac dinh");
		ActionStop();
		return false;
		break;
	}
	}

}

///////////////////////////// Robot Move TRay OK NG  ///////////////////////////////////
bool CHandlerMCDoc::m_RobotMoveTrayOKNG()
{
	if (m_CheckTrayUnloadRightFull() && m_CheckTrayUnloadLeftFull())
	{
		AlarmOn();
		AfxMessageBox("2 Tray NG Full");
		ActionStop();
	}
	switch (m_NorobotmovetrayOKNG)
	{
	case 0://Tool1 unloading
	{
		if (!m_Tool1Unloading)
		{
			m_NorobotmovetrayOKNG = 1;
		}
		else
		{
			if (m_RobotMoveTrayOKNG0())//Tool1 unloading tray OK or NG
			{
				m_ActionTool1Unloading = 0;//Bien toan cuc cua ham
				m_NorobotmovetrayOKNG = 1;//next
				m_Tool1Unloading = false;
			}
		}
		break;
	}
	case 1://Tool2 unloading
	{
		if (!m_Tool2Unloading)
		{
			m_NorobotmovetrayOKNG = 2;
		}
		else
		{
			if (m_RobotMoveTrayOKNG1())//Tool2 unloading tray OK or NG
			{
				m_ActionTool1Unloading = 0;//Bien toan cuc cua ham
				m_NorobotmovetrayOKNG = 2;//next
				m_Tool2Unloading = false;
			}
		}
		break;
	}
	case 2://result
	{
		return true;
	}
	default:
		break;
	}
	return false;
}
//Action tool1
bool CHandlerMCDoc::m_RobotMoveTrayOKNG0()//Tool1 unloading tray OK or NG
{
	if (m_ResulttestTool1Unloading)
	{
		//Tool1 ket qua OK
		if (m_Tool1ResulOKUnload())
		{
			return true;
		}
		//
	}
	else
	{
		//Tool1 ket qua NG
		if (m_Tool1ResulNGUnload())
		{
			return true;
		}
		//
	}
	return false;
}

//Action tool2
bool CHandlerMCDoc::m_RobotMoveTrayOKNG1()
{
	if (m_ResulttestTool2Unloading)
	{
		//Tool2 ket qua OK
		if (m_Tool2ResulOKUnload())
		{
			return true;
		}
	}
	else
	{
		//Tool 2 ket qua NG
		if (m_Tool2ResulNGUnload())
		{
			return true;
		}
	}

	return false;
}

// Tool 1 ket qua OK unload
bool CHandlerMCDoc::m_Tool1ResulOKUnload()
{
	//Tool1 ket qua OK
	switch (m_ActionTool1Unloading)
	{
	case 0:
	{
		//if (!m_CheckTrayLoadFull())//Check tray OK Chua full
		{
			if (m_UnloadingTrayOKUpDown(CmRunRobotUnloadingTrayOKTool3Up))
			{
				m_UnloadingTrayOK1 = 0;
				m_ActionTool1Unloading = 1;
			}
		}
		break;
	}
	case 1:
	{
		m_ActionTool1Unloading = 2;
		break;
	}
	case 2:
	{
		return true;
	}
	default:
		break;
	}

	return false;
}
// Tool 1 ket qua NG unload
bool CHandlerMCDoc::m_Tool1ResulNGUnload()
{
	switch (m_ActionTool1Unloading)
	{
	case 0:
	{
		if (!m_CheckTrayUnloadLeftFull())//Neu tray NG left chua day thi loading vao
		{
			if (m_UnloadingTrayNGLeftUpDown(CmRunRobotUnloadingLeftTool3Up))
			{
				m_UnloadingTrayNGLeft1 = 0;//Bien toan cuc cua ham
				m_ActionTool1Unloading = 1;//Next
				PosXY[TrayNgLeft].at(i_trayUnloadingLeft).at(j_trayUnloadingLeft).status = true;
				break;
			}
		}
		else
		{
			if (!m_CheckTrayUnloadRightFull())//Neu tray NG right chua day thi loading vao
			{
				if (m_UnloadingTrayNGRightUpDown(CmRunRobotUnloadingRightTool3Up))
				{
					m_UnloadingTrayNGRight1 = 0;
					m_ActionTool1Unloading = 1;
					PosXY[TrayNgRight].at(i_trayUnloadingRight).at(j_trayUnloadingRight).status = true;
					break;
				}
			}
		}
		break;
	}
	case 1:
	{
		if (m_CheckTrayUnloadRightFull())//Neu tray NG right day thi dung may
		{
			AfxMessageBox(" 2 Tray NG Full");
			ActionStop();
		}
		else
		{
			m_ActionTool1Unloading = 2;
		}
	}
	case 2:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}
// Tool 2 ket qua OK unload
bool CHandlerMCDoc::m_Tool2ResulOKUnload()
{
	switch (m_ActionTool1Unloading)
	{
	case 0:
	{
		//	if (!m_CheckTrayLoadFull())//Check tray OK full
		{
			if (m_UnloadingTrayOKUpDown(CmRunRobotUnloadingTrayOKTool4Up))
			{
				m_UnloadingTrayOK1 = 0;//Bien toan cuc cua ham
				m_ActionTool1Unloading = 1;//Next			
			}
		}
		//else
		//{
		//	AfxMessageBox("Tray Loading Full");
		//	ActionStop();
		//}
		break;
	}
	case 1:
	{
		m_ActionTool1Unloading = 2;
		break;
	}
	case 2:
	{
		return true;
	}
	default:
		break;
	}
	return false;
	//
}
// Tool 2 ket qua NG unload
bool CHandlerMCDoc::m_Tool2ResulNGUnload()
{
	switch (m_ActionTool1Unloading)
	{
	case 0:
	{
		//if (m_UnloadingTrayNGLeftUpDown(CmRunRobotUnloadingLeftTool4Up))
		//{
		//	m_UnloadingTrayNGLeft1 = 0;//Bien toan cuc cua ham
		//	m_ActionTool1Unloading = 1;//Next
		//}

		if (!m_CheckTrayUnloadLeftFull())//Nau tray NG left chua day thi loading vao
		{
			if (m_UnloadingTrayNGLeftUpDown(CmRunRobotUnloadingLeftTool4Up))
			{
				m_UnloadingTrayNGLeft1 = 0;
				m_ActionTool1Unloading = 1;
				PosXY[TrayNgLeft].at(i_trayUnloadingLeft).at(j_trayUnloadingLeft).status = true;
				break;
			}
		}
		else
		{
			if (!m_CheckTrayUnloadRightFull())//Nau tray NG right chua day thi loading vao
			{
				if (m_UnloadingTrayNGRightUpDown(CmRunRobotUnloadingLeftTool4Up))
				{
					m_UnloadingTrayNGRight1 = 0;
					m_ActionTool1Unloading = 1;
					PosXY[TrayNgRight].at(i_trayUnloadingRight).at(j_trayUnloadingRight).status = true;
					break;
				}
			}
		}
		//
		break;
	}
	case 1:
	{
		return true;
	}
	default:
		break;
	}

}
// Thuc hien unloading cam ra tray OK voi tool duoc lua chon
bool CHandlerMCDoc::m_UnloadingTrayOKUpDown(CString m_slecttool)
{
	if (m_slecttool == CmRunRobotUnloadingTrayOKTool3Up)
	{
		m_FlagBuffer = true;
	}
	else
	{
		m_FlagBuffer = false;
	}
	switch (m_UnloadingTrayOK1)
	{
	case 0://Tim tao do vi tri tray co hang
	{
		if (Safety4ToolRobot())
		{
			for (int i = 0; i < RowTray; i++)
				for (int j = 0; j < ColumnTray; j++)
				{
					if (!PosXY[TrayLoading].at(i).at(j).status && !PosXY[TrayLoading].at(i).at(j).unloading)//Tim vi tri tray con trong
					{
						i_trayLoading = i;
						j_trayLoading = j;
						m_NoLoadingRun.Format("(%d,%d,1,1,0)", i_trayLoading, j_trayLoading);
						m_UnloadingTrayOK1 = 1;
						return false;
					}
				}
		}
		break;
	}
	case 1://Truyen du lieu lay hang
	{
		if (m_FlagBuffer)
		{
			if (ReadInput(Vaccum_Tool3_Robot) && Safety4ToolRobot())
			{
				SendDataEthernet(m_slecttool + m_NoLoadingRun);//Run Up
				m_UnloadingTrayOK1 = 2;
			}
		}
		else
		{
			if (ReadInput(Vaccum_Tool4_Robot) && Safety4ToolRobot())
			{
				SendDataEthernet(m_slecttool + m_NoLoadingRun);//Run Up
				m_UnloadingTrayOK1 = 2;
			}

		}
		break;
	}
	case 2://Doi ro bot phan hoi done
	{
		if (MootionDoneRobot())
		{
			m_UnloadingTrayOK1 = 5;
			break;
		}
		while (ReadInput(Button_Start))
		{
			m_UnloadingTrayOK1 = 1;
		}
		break;
	}
	case 5:
	{
		if (m_FlagBuffer)//Tool 3 hoat dong
		{
			if (ReadInput(SSXL_Tool3_RobotUp) && ReadInput(Vaccum_Tool3_Robot))
			{
				XilanhTool3On();
				Sleep(DelayCylinderTool3Robot);
			}
			if (!ReadInput(SSXL_Tool3_RobotUp) && ReadInput(Vaccum_Tool3_Robot))
			{
				m_NoLoadingRun.Format("(%d,%d,1,1,1)", i_trayLoading, j_trayLoading);
				SendDataEthernet(m_slecttool + m_NoLoadingRun);//Run Down
				m_UnloadingTrayOK1 = 6;
			}
		}
		else//Tool 4 hoat dong
		{
			if (ReadInput(SSXL_Tool4_RobotUp) && ReadInput(Vaccum_Tool4_Robot))
			{
				XilanhTool4On();
				Sleep(DelayCylinderTool4Robot);
			}
			if (!ReadInput(SSXL_Tool4_RobotUp) && ReadInput(Vaccum_Tool4_Robot))
			{
				m_NoLoadingRun.Format("(%d,%d,1,1,1)", i_trayLoading, j_trayLoading);
				SendDataEthernet(m_slecttool + m_NoLoadingRun);//Run Down
				m_UnloadingTrayOK1 = 6;
			}
		}

		break;
	}
	case 6:
	{
		if (MootionDoneRobot())
		{
			if (m_FlagBuffer)//Tool 3 hoat dong
			{
				VaccumTool3Off();
				if (!ReadInput(Vaccum_Tool3_Robot) && !ReadInput(SSXL_Tool3_RobotUp))
				{
					Sleep(DelayVaccumToolRobot3);
					XilanhTool3Off();
				}
			}
			else
			{
				VaccumTool4Off();//Tool 4 hoat dong
				if (!ReadInput(Vaccum_Tool4_Robot) && !ReadInput(SSXL_Tool4_RobotUp))
				{
					Sleep(DelayVaccumToolRobot4);
					XilanhTool4Off();
				}
			}
			if (Safety4ToolRobot() && (!ReadInput(Vaccum_Tool3_Robot) && m_FlagBuffer) || 
				                      (ReadInput(Vaccum_Tool4_Robot) && !m_FlagBuffer))
			{
				m_UnloadingTrayOK1 = 3;
			}
			
			break;
		}
		while (ReadInput(Button_Start))
		{
			m_UnloadingTrayOK1 = 5;
		}
		break;
	}
	case 3://Hoan thanh nha tool1 unloading
	{
		PosXY[TrayLoading].at(i_trayLoading).at(j_trayLoading).status = false;//sua
		PosXY[TrayLoading].at(i_trayLoading).at(j_trayLoading).unloading = true;
		m_OnStatusPictureLoading = true;
		m_UnloadingTrayOK1 = 4;
		break;
	}
	case 4:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}

// Thuc hien unloading cam ra tray NG Left voi tool duoc lua chon
bool CHandlerMCDoc::m_UnloadingTrayNGLeftUpDown(CString m_slecttool)
{
	if (m_slecttool == CmRunRobotUnloadingLeftTool3Up)
	{
		m_FlagBuffer = true;
	}
	else
	{
		m_FlagBuffer = false;
	}
	switch (m_UnloadingTrayNGLeft1)
	{
	case 0://Tim tao do vi tri tray co hang
	{
		if (Safety4ToolRobot())
		{
			for (int i = 0; i < RowTray; i++)
				for (int j = 0; j < ColumnTray; j++)
				{
					if (!PosXY[TrayNgLeft].at(i).at(j).status)//Tim vi tri tray con trong
					{
						i_trayUnloadingLeft = i;
						j_trayUnloadingLeft = j;
						m_NoLoadingRun.Format("(%d,%d,0,2,0)", i_trayUnloadingLeft, j_trayUnloadingLeft);
						m_UnloadingTrayNGLeft1 = 1;
						return false;
					}
				}
		}
		break;
	}
	case 1://Truyen du lieu lay hang
	{ 
		if (m_FlagBuffer)
		{
			if (ReadInput(Vaccum_Tool3_Robot) && Safety4ToolRobot())
			{
				SendDataEthernet(m_slecttool + m_NoLoadingRun);//Run Up
				m_UnloadingTrayNGLeft1 = 2;
			}
		}
		else
		{
			if (ReadInput(Vaccum_Tool4_Robot) && Safety4ToolRobot())
			{
				SendDataEthernet(m_slecttool + m_NoLoadingRun);//Run Up
				m_UnloadingTrayNGLeft1 = 2;
			}
		}
		break;
	}
	case 2://Doi ro bot phan hoi done
	{
		if (MootionDoneRobot())
		{
			m_UnloadingTrayNGLeft1 = 5;
			break;
		}
		while (ReadInput(Button_Start))
		{
			m_UnloadingTrayNGLeft1 = 1;
		}
		break;
	}
	case 5:
	{
		if (m_FlagBuffer)//Tool 3 hoat dong
		{
			if (ReadInput(SSXL_Tool3_RobotUp) && ReadInput(Vaccum_Tool3_Robot))
			{
				XilanhTool3On();
				Sleep(DelayCylinderTool3Robot);
			}
			if (!ReadInput(SSXL_Tool3_RobotUp))
			{
				m_NoLoadingRun.Format("(%d,%d,0,2,1)", i_trayUnloadingLeft, j_trayUnloadingLeft);//Run Down
				SendDataEthernet(m_slecttool + m_NoLoadingRun);
				m_UnloadingTrayNGLeft1 = 6;
			}
		}
		else//Tool 4 hoat dong
		{
			if (ReadInput(SSXL_Tool4_RobotUp) && ReadInput(Vaccum_Tool4_Robot))
			{
				XilanhTool4On();
				Sleep(DelayCylinderTool4Robot);
			}
			if (!ReadInput(SSXL_Tool4_RobotUp))
			{
				m_NoLoadingRun.Format("(%d,%d,0,2,1)", i_trayUnloadingLeft, j_trayUnloadingLeft);//Run Down
				SendDataEthernet(m_slecttool + m_NoLoadingRun);
				m_UnloadingTrayNGLeft1 = 6;
			}
		}

		break;
	}
	case 6:
	{
		if (MootionDoneRobot())
		{
			if (m_FlagBuffer)//Tool 3 hoat dong
			{
				VaccumTool3Off();
				if (!ReadInput(Vaccum_Tool3_Robot) && !ReadInput(SSXL_Tool3_RobotUp))
				{
					Sleep(DelayVaccumToolRobot3);
					XilanhTool3Off();
				}
			}
			else
			{
				VaccumTool4Off();
				if (!ReadInput(Vaccum_Tool4_Robot) && !ReadInput(SSXL_Tool4_RobotUp))
				{
					Sleep(DelayVaccumToolRobot4);
					XilanhTool4Off();
				}
			}
			if (Safety4ToolRobot() && (!ReadInput(Vaccum_Tool3_Robot) && m_FlagBuffer) ||
				(ReadInput(Vaccum_Tool4_Robot) && !m_FlagBuffer))
			{
				m_UnloadingTrayNGLeft1 = 3;
			}	
		}
		while (ReadInput(Button_Start))
		{
			m_UnloadingTrayNGLeft1 = 5;
		}
		break;
	}
	case 3://Hoan thanh nha tool1 unloading
	{
		//PosXY[TrayNgLeft].at(i_trayUnloadingLeft).at(j_trayUnloadingLeft).status = true;
		m_OnStatusPictureUnloadingLeft = true;
		m_UnloadingTrayNGLeft1 = 4;
		break;
	}
	case 4:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}
// Thuc hien unloading cam ra tray NG Right voi tool duoc lua chon
bool CHandlerMCDoc::m_UnloadingTrayNGRightUpDown(CString m_slecttool)
{
	if (m_slecttool == CmRunRobotUnloadingLeftTool3Up)
	{
		m_FlagBuffer = true;
	}
	else
	{
		m_FlagBuffer = false;
	}
	switch (m_UnloadingTrayNGRight1)
	{
	case 0://Tim tao do vi tri tray co hang
	{
		if (Safety4ToolRobot())
		{
			for (int i = 0; i < RowTray; i++)
				for (int j = 0; j < ColumnTray; j++)
				{
					if (!PosXY[TrayNgRight].at(i).at(j).status)//Tim vi tri tray con trong
					{
						i_trayUnloadingRight = i;
						j_trayUnloadingRight = j;
						m_NoLoadingRun.Format("(%d,%d,0,3,0)", i_trayUnloadingRight, j_trayUnloadingRight);
						m_UnloadingTrayNGRight1 = 1;
						return false;
					}
				}
		}
		break;
	}
	case 1://Truyen du lieu lay hang
	{
		if (m_FlagBuffer)
		{
			if (ReadInput(Vaccum_Tool3_Robot) && Safety4ToolRobot())
			{
				SendDataEthernet(m_slecttool + m_NoLoadingRun);// Run Up
				m_UnloadingTrayNGRight1 = 2;
			}
		}
		else
		{
			if (ReadInput(Vaccum_Tool4_Robot) && Safety4ToolRobot())
			{
				SendDataEthernet(m_slecttool + m_NoLoadingRun);// Run Up
				m_UnloadingTrayNGRight1 = 2;
			}
		}
		break;
	}
	case 2://Doi ro bot phan hoi done
	{
		if (MootionDoneRobot())
		{
			m_UnloadingTrayNGRight1 = 5;
			break;
		}
		while (ReadInput(Button_Start))
		{
			m_UnloadingTrayNGRight1 = 1;
		}
		break;
	}
	case 5:
	{
		if (m_FlagBuffer)//Tool 3 hoat dong
		{
			if (ReadInput(SSXL_Tool3_RobotUp) && ReadInput(Vaccum_Tool3_Robot))
			{
				XilanhTool3On();
				Sleep(DelayCylinderTool3Robot);
			}
			if (!ReadInput(SSXL_Tool3_RobotUp))
			{
				m_NoLoadingRun.Format("(%d,%d,0,3,1)", i_trayUnloadingRight, j_trayUnloadingRight);
				SendDataEthernet(m_slecttool + m_NoLoadingRun);// Run Down
				m_UnloadingTrayNGRight1 = 6;
			}
		}
		else//Tool 4 hoat dong
		{
			if (ReadInput(SSXL_Tool4_RobotUp) && ReadInput(Vaccum_Tool4_Robot))
			{
				XilanhTool4On();
				Sleep(DelayCylinderTool4Robot);
			}
			if (!ReadInput(SSXL_Tool4_RobotUp))
			{
				m_NoLoadingRun.Format("(%d,%d,0,3,1)", i_trayUnloadingRight, j_trayUnloadingRight);
				SendDataEthernet(m_slecttool + m_NoLoadingRun);// Run Down
				m_UnloadingTrayNGRight1 = 6;
			}
		}
		break;
	}
	case 6:
	{
		if (MootionDoneRobot())
		{
			if (MootionDoneRobot())
			{
				if (m_FlagBuffer)//Tool 3 hoat dong
				{
					VaccumTool3Off();
					if (!ReadInput(Vaccum_Tool3_Robot) && !ReadInput(SSXL_Tool3_RobotUp))
					{
						Sleep(DelayVaccumToolRobot3);
						XilanhTool3Off();
					}
					
				}
				else
				{
					VaccumTool4Off();
					if (!ReadInput(Vaccum_Tool4_Robot) && !ReadInput(SSXL_Tool4_RobotUp))
					{
						Sleep(DelayVaccumToolRobot4);
						XilanhTool4Off();
					}			
				}
				if (Safety4ToolRobot() && (!ReadInput(Vaccum_Tool3_Robot) && m_FlagBuffer) ||
					(ReadInput(Vaccum_Tool4_Robot) && !m_FlagBuffer))
				{
					m_UnloadingTrayNGRight1 = 3;
				}
			}		
			break;
		}
		while (ReadInput(Button_Start))
		{
			m_UnloadingTrayNGRight1 = 5;
		}
		break;
	}
	case 3://Hoan thanh nha tool1 unloading
	{
		//PosXY[TrayNgRight].at(i_trayUnloadingRight).at(j_trayUnloadingRight).status = true;
		m_OnStatusPictureUnloadingRight = true;
		m_UnloadingTrayNGRight1 = 4;
		break;
	}
	case 4:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}

// Check tray OK full
bool CHandlerMCDoc::m_CheckTrayLoadFull()
{
	//New
	for (int i = 0; i < RowTray; i++)
	{
		for (int j = 0; j < ColumnTray; j++)
		{
			if (PosXY[TrayLoading].at(i).at(j).status)
			{
				return false;
			}
		}
	}
	return true;
}

// Check tray Unloading left full
bool CHandlerMCDoc::m_CheckTrayUnloadLeftFull()
{
	for (int i = 0; i < RowTray; i++)
		for (int j = 0; j < ColumnTray; j++)
		{
			if (!PosXY[TrayNgLeft].at(i).at(j).status)
			{
				return false;
			}
		}

	return true;
}
// Check tray Unloading right full
bool CHandlerMCDoc::m_CheckTrayUnloadRightFull()
{
	for (int i = 0; i < RowTray; i++)
		for (int j = 0; j < ColumnTray; j++)
		{
			if (!PosXY[TrayNgRight].at(i).at(j).status)
			{
				return false;
			}
		}

	return true;
}
//////////////////////////////////////////////  Unloading tray loading full ////////////////////////////////

bool CHandlerMCDoc::m_UnloadingTrayLoadingFull()
{
	switch (m_NoUnloadingFull)
	{
	case 0:
	{   //Di chuyen den vi tri lay tray
		if (ReadyToLoadingTray())
		{
			SendDataEthernet(CmRunRobotUnloadingTrayLoading + "(1)");
			m_NoUnloadingFull = 1;
		}	
		/*else
		{
			AlarmOn();
			AfxMessageBox("Tray Loading Not Ready To Unloading");
			ActionStop();
		}*/
		break;
	}
	case 1:
	{
		//Doi ro bot phan hoi done
		if (MootionDoneRobot())
		{
			VaccumTrayRobotOn();
		}
		if (MootionDoneRobot() && ReadInput(Vaccum_Tray_Robot))
		{
			Sleep(DelayVaccumTrayRobot);
			XilanhDoTrayLoadingOff();
			XilanhDoTrayUnloadingOff();
			XilanhAlineTrayLoadingOff();		
		}
		if (ReadInput(Vaccum_Tray_Robot) && ReadInput(SSXL_Do_Tray_Loading_In_Trai) &&
			ReadInput(SSXL_Do_Tray_Loading_In_Phai) && ReadInput(SSXL_AlineTray_Loading_In))
		{
			m_NoUnloadingFull = 2;
		}
		while (ReadInput(Button_Start))
		{
			m_NoUnloadingFull = 1;
		}
		break;
	}
	case 2:
	{
		//Di chuyen den vi tri Place
		if (ReadInput(Vaccum_Tray_Robot) && ReadInput(SSXL_Do_Tray_Loading_In_Trai) &&
			ReadInput(SSXL_Do_Tray_Loading_In_Phai) && ReadInput(SSXL_AlineTray_Loading_In) &&
			ReadyToUnloadingTray())
		{
			SendDataEthernet(CmRunRobotUnloadingTrayUnloading + "(1)");
			m_NoUnloadingFull = 3;
		}
		else
		{
			AlarmOn();
			AfxMessageBox("Tray Loading Not Ready To Unloading");
			ActionStop();
		}
		break;
	}
	case 3:
	{
		//Doi ro bot phan hoi done
		if (MootionDoneRobot())
		{
			VaccumTrayRobotOff();
			if (!ReadInput(Vaccum_Tray_Robot))
			{
				Sleep(1000);
				m_NoUnloadingFull = 4;
			}

		}
		//while (ReadInput(Button_Start))
		//{
		//	m_NoUnloadingFull = 2;
		//}
		break;
	}
	case 4:
	{
		if (ActionDownZUnloading())
		{
			m_ActionDownZUnloading = 0;
			m_NoUnloadingFull = 5;
		}
		break;		
	}
	case 5:
	{
		SendDataEthernet("Ready()");
		m_NoUnloadingFull = 6;
		break;
	}
	case 6:
	{
		if (MootionDoneRobot())
		{
			m_NoUnloadingFull = 7;
		}
		break;
	}
	case 7:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}

//////////////////////////////////////////////  Unloading tray ////////////////////////////////
bool CHandlerMCDoc::m_BufferUnloading()
{
	switch (m_trayUnloading)
	{
	case 0://Truc z2 len vi tri doi
	{
	//	if (ReadInput(SSXL_Do_Tray_Unloading_Out_Trai) || ReadInput(SSXL_Do_Tray_Unloading_Out_Phai))
	//	{
	//		XilanhDoTrayUnloadingOff();//Keo xl do ve
	//	}
		if (ReadInput(SSXL_AlineTray_Unloading_Out))
		{
			XilanhAlineTrayUnloadingOff();//keo xl aline ve
		}

		if (/*ReadInput(SSXL_Do_Tray_Unloading_In_Trai) && ReadInput(SSXL_Do_Tray_Unloading_In_Phai) &&*/
			ReadInput(SSXL_AlineTray_Unloading_In) && !ReadInput(Detech_Tray_On_Z_Unloading))
		{
			if (RunPosUnloading(PosZ2Up))//chay len vi tri lay tray unloading
			{
				m_trayUnloading = 1;
			}
		}

		if (/*ReadInput(SSXL_Do_Tray_Unloading_In_Trai) && ReadInput(SSXL_Do_Tray_Unloading_In_Phai) &&*/
			ReadInput(SSXL_AlineTray_Unloading_In) && ReadInput(Detech_Tray_On_Z_Unloading))
		{   //Ha truc z unloading xuong khi co hang ten truc
		   Motion.JogRun(AxisY, DataMotor.SpeedRunAxisZ2, DataMotor.Acc,DataMotor.Dec);
		}

		if (/*ReadInput(SSXL_Do_Tray_Unloading_In_Trai) && ReadInput(SSXL_Do_Tray_Unloading_In_Phai) &&*/
			ReadInput(SSXL_AlineTray_Unloading_In) && ReadInput(Detech_Tray_On_Z_Unloading) && 
			!ReadInput(Detech_Tray_Up_Unloading))
		{
			Motion.JogStop(AxisY);
			m_trayUnloading = 1;
		}
		break;
	}
	case 1://Aline  tray
	{
		if (/*ReadInput(SSXL_Do_Tray_Unloading_In_Trai)  && ReadInput(SSXL_Do_Tray_Unloading_In_Phai)*/
		    ReadInput(Detech_Tray_On_Z_Unloading)  && !ReadInput(Detech_Tray_Up_Unloading)
			&& ReadInput(SSXL_AlineTray_Unloading_In) && (m_NumberAline < 3))
		{
			XilanhAlineTrayUnloadingOn();
			Sleep(DelayCylinderAline);
		}

		if (/*(ReadInput(SSXL_Do_Tray_Unloading_In_Trai) && ReadInput(SSXL_Do_Tray_Unloading_In_Phai)*/
			 ReadInput(Detech_Tray_On_Z_Unloading) && !ReadInput(Detech_Tray_Up_Unloading)
			&& ReadInput(SSXL_AlineTray_Unloading_Out))
		{
			XilanhAlineTrayUnloadingOff();
			Sleep(DelayCylinderAline);
			m_NumberAline++;
		}
		//
		if (/*(ReadInput(SSXL_Do_Tray_Unloading_In_Trai) && ReadInput(SSXL_Do_Tray_Unloading_In_Phai)*/
			 ReadInput(Detech_Tray_On_Z_Unloading)   && !ReadInput(Detech_Tray_Up_Unloading)
			&& ReadInput(SSXL_AlineTray_Unloading_In) && (m_NumberAline >= 3))
		{
			m_trayUnloading = 2;		
		}
		break;
	}
	case 2://Ha xuong thap hon vi tri sensor
	{
		m_NumberAline = 0;
		while (true)
		{
			Motion.JogRun(AxisY, -DataMotor.SpeedRunAxisZ2, DataMotor.Acc, DataMotor.Dec);
			if (ReadInput(Detech_Tray_Up_Unloading))
			{
				Motion.JogStop(AxisY);
				m_trayUnloading = 3;
				break;
			}
			if (Motion.ReadInput(ButtonStop))
			{
				ActionStop();
				return false;
			}
		}
		break;
	}	
	case 3:
	{
		return true;
		break;
	}
	default:
		break;
	}
	return false;
}
///////////////////////End Tray//////////////////////////////////////////////////////////////////////
bool CHandlerMCDoc::ActionEndTray()
{
	//Lua chon case hop ly
	if (Status_Loading_Unloading)
	{
		for (int i = 0; i<4; i++)
		{
			if ((m_ResultTestSocket[i] == 1) || (m_ResultTestSocket[i] == 2) && m_DataTester[i].Action)
			{
				m_NoRobotUnloadTest = i;
				Status_Loading_Unloading = false;
				break;
			}
			else
			{
				m_NoRobotUnloadTest = -1;
			}
		}

	}
	//Run
	switch (m_NoRobotUnloadTest)
	{
	     case 0://Unloading Socket 0
	     {
			if (RobotUnloadingTest0())
			{
				m_DataTester[0].Loading = true;//Tester 0 trong
				m_DataTester[0].StatusTester = true;// Tester khong co lenh test
				m_SocketUnloading = 0;//Bien ham chinh lop 1
				m_ResultTestSocket[0] = 0;//Reset ket qua test			
			}
	     	break;
	     }
	     case 1://Unloading Socket 1
	     {

			 if (RobotUnloadingTest1())
			 {
				 m_DataTester[1].Loading = true;//Tester 1 trong
				 m_DataTester[1].StatusTester = true;// Tester khong co lenh test
				 m_SocketUnloading = 0;//Bien ham chinh lop 1
				 m_ResultTestSocket[1] = 0;//Reset ke qua test
			 }
	     	break;
	     }
	     case 2://Unloading Socket 2
	     {
			 if (RobotUnloadingTest2())
			 {
				 m_DataTester[2].Loading = true;//Tester 2 trong
				 m_DataTester[2].StatusTester = true;// Tester khong co lenh test
				 m_SocketUnloading = 0;//Bien ham chinh lop 1
				 m_ResultTestSocket[2] = 0;//Reset ke qua test
			 }
	     	break;
	     }
	     case 3://Unloading Socket 3
		 {
			 if (RobotUnloadingTest3())
		     {
			     m_DataTester[3].Loading = true;//Tester 3 trong
			     m_DataTester[3].StatusTester = true;// Tester khong co lenh test
			     m_SocketUnloading = 0;//Bien ham chinh lop 1
			     m_ResultTestSocket[3] = 0;//Reset ke qua test
		     }
	     	break;
	     }
	     default:
	     {
	     	return false;
	     }
	}
	return ReturnEndTray();
}
bool CHandlerMCDoc::ReturnEndTray()
{
	switch (m_NumberTesterAct)
	{
	case 1://Chi co 1 Tool Hoat dong
	{
		//Tool1 Unloading co hang va tool1 loading khong co hang  
		if (m_Tool1Unloading && !m_Tool1Loading &&
			ReadInput(Vaccum_Tool3_Robot) && !ReadInput(Vaccum_Tool1_Robot) && Safety4ToolRobot())
		{
			return true;
		}
		break;
	}
	case 2:
	{
		//Tool1 Unloading co hang va tool1 loading khong co hang  
		if (m_Tool1Unloading && !m_Tool1Loading && m_Tool2Unloading && !m_Tool2Loading &&
			ReadInput(Vaccum_Tool3_Robot) && !ReadInput(Vaccum_Tool1_Robot) &&
			ReadInput(Vaccum_Tool4_Robot) && !ReadInput(Vaccum_Tool2_Robot) && Safety4ToolRobot())
		{
			return true;
		}
		break;
	}
	case 3:
	{
		if (!Flag_pick_cam)
		{
			//Luot lay dau lay 2 cam
			if (m_Tool1Unloading && !m_Tool1Loading && m_Tool2Unloading && !m_Tool2Loading &&
				ReadInput(Vaccum_Tool3_Robot) && !ReadInput(Vaccum_Tool1_Robot) &&
				ReadInput(Vaccum_Tool4_Robot) && !ReadInput(Vaccum_Tool2_Robot) && Safety4ToolRobot())
			{
				Flag_pick_cam = true;
				return true;
			}
		}
		else
		{
			//Luot sau lay 1 cam
			if (m_Tool1Unloading && !m_Tool1Loading &&
				ReadInput(Vaccum_Tool3_Robot) && !ReadInput(Vaccum_Tool1_Robot) && m_StatusRun3Tester &&
				Safety4ToolRobot())
			{
				return true;
			}
		}
		break;
	}
	case 4:
	{
		//Tool1 Unloading co hang va tool1 loading khong co hang  
		if (m_Tool1Unloading && !m_Tool1Loading && m_Tool2Unloading && !m_Tool2Loading &&
			ReadInput(Vaccum_Tool3_Robot) && !ReadInput(Vaccum_Tool1_Robot) &&
			ReadInput(Vaccum_Tool4_Robot) && !ReadInput(Vaccum_Tool2_Robot) && Safety4ToolRobot())
		{
			return true;
		}
		break;
	}
	default:
		return false;
		break;
	}
	return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Data Com Phone
void CHandlerMCDoc::ReceivePhoneCom(CString m_DataCom)
{
	g_this->m_ReviceData(m_DataCom);
	g_this->m_SignReviceCom = true;
	g_this->m_DataComEvent = m_DataCom;
}

void CHandlerMCDoc::SendPhoneCom(CString Data)
{
	m_PhoneCom.SendData(Data);
}

void CHandlerMCDoc::InitComPhone(int m_ComPort, int m_Baudrate)
{
	if (!m_PhoneCom.Initialize(m_ComPort, m_Baudrate))
	{
		m_StatusConnectCom = false;
		AfxMessageBox("Open Com Fail");
	}
	else
	{
		m_StatusConnectCom = true;
		SaveDataComEvent();
	}

	m_PhoneCom.CallbackFuncCount(ReceivePhoneCom);
}

void CHandlerMCDoc::SaveDataComEvent()
{
	// TODO: Add your message handler code here
	CFileFind ffind;
	CString strPath = "DataSystem\\DataCom.dat";
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
		cstr.Format("Com			 = %d \n", m_NumberComEvent);
		fn.WriteString(cstr);
		cstr.Format("BaudRate		 = %d \n", m_BaudRateEvent);
		fn.WriteString(cstr);
		fn.Close();
	}
}

void CHandlerMCDoc::ReadDataComEvent()
{
	CIniFile DataCom;
	DataCom.SetPath("DataSystem\\DataCom.dat");// đường dẫn file. Nhớ phải dung 2 sẹc (\\).
	m_NumberComEvent = DataCom.ReadInt("Data", "Com ", 0);
    m_BaudRateEvent = DataCom.ReadInt("Data", "BaudRate ", 1);
}

void CHandlerMCDoc::ReadDataDelayVaccum()
{
	CIniFile DataCom;
	DataCom.SetPath("DataSystem\\DataDelayVaccum.dat");// đường dẫn file. Nhớ phải dung 2 sẹc (\\).
	DelayVaccumToolRobot1 = DataCom.ReadInt("Data", "DelayVaccumTool1Robot ", 0);
	DelayVaccumToolRobot2 = DataCom.ReadInt("Data", "DelayVaccumTool2Robot ", 0);
	DelayVaccumToolRobot3 = DataCom.ReadInt("Data", "DelayVaccumTool3Robot ", 0);
	DelayVaccumToolRobot4 = DataCom.ReadInt("Data", "DelayVaccumTool4Robot ", 0);

	DelayVaccumSocket1 = DataCom.ReadInt("Data", "DelayVaccumSocket1 ", 0);
	DelayVaccumSocket2 = DataCom.ReadInt("Data", "DelayVaccumSocket2 ", 0);
	DelayVaccumSocket3 = DataCom.ReadInt("Data", "DelayVaccumSocket3 ", 0);
	DelayVaccumSocket4 = DataCom.ReadInt("Data", "DelayVaccumSocket4 ", 0);

	DelayVaccumTrayRobot = DataCom.ReadInt("Data", "m_DataDelayVaccumTray ", 0);
}

void CHandlerMCDoc::ReadDataDelayCylinder()
{
	CIniFile DataCom;
	DataCom.SetPath("DataSystem\\DataDelayCylinder.dat");// đường dẫn file. Nhớ phải dung 2 sẹc (\\).
	DelayCylinderTool1Robot = DataCom.ReadInt("Data", "DelayCylinderTool1Robot ", 0);
	DelayCylinderTool2Robot = DataCom.ReadInt("Data", "DelayCylinderTool2Robot ", 0);
	DelayCylinderTool3Robot = DataCom.ReadInt("Data", "DelayCylinderTool3Robot ", 0);
	DelayCylinderTool4Robot = DataCom.ReadInt("Data", "DelayCylinderTool4Robot ", 0);

	DelayCylinderSocket1FwRv = DataCom.ReadInt("Data", "DelayCylinderSocket1FwRv ", 0);
	DelayCylinderSocket2FwRv = DataCom.ReadInt("Data", "DelayCylinderSocket2FwRv ", 0);
	DelayCylinderSocket3FwRv = DataCom.ReadInt("Data", "DelayCylinderSocket3FwRv ", 0);
	DelayCylinderSocket4FwRv = DataCom.ReadInt("Data", "DelayCylinderSocket4FwRv ", 0);

	DelayCylinderSocket1UpDown = DataCom.ReadInt("Data", "DelayCylinderSocket1UpDown ", 0);
	DelayCylinderSocket2UpDown = DataCom.ReadInt("Data", "DelayCylinderSocket2UpDown ", 0);
	DelayCylinderSocket3UpDown = DataCom.ReadInt("Data", "DelayCylinderSocket3UpDown ", 0);
	DelayCylinderSocket4UpDown = DataCom.ReadInt("Data", "DelayCylinderSocket4UpDown ", 0);

	DelayCylinderHandler = DataCom.ReadInt("Data", "DelayCylinderHandler ", 0);
	DelayCylinderAline = DataCom.ReadInt("Data", "DelayCylinderAline ", 0);
	DelayCylinderRotation = DataCom.ReadInt("Data", "DelayCylinderRotation ", 0);
	DelayCylinderStack = DataCom.ReadInt("Data", "DelayCylinderStack ", 0);

}

//Safety sign sensor

bool CHandlerMCDoc::ReadSignalSensor()
{
	//Tool Robot
	if (Motion.ReadOuput(Vaccum_Robot_1) && !Motion.ReadInput(Vaccum_Tool1_Robot)) { MessengerData = "Vaccum Tool 1 Robot Error"; return true; }
	if (Motion.ReadOuput(Vaccum_Robot_2) && !Motion.ReadInput(Vaccum_Tool2_Robot)) { MessengerData = "Vaccum Tool 2 Robot Error"; return true; }
	if (Motion.ReadOuput(Vaccum_Robot_3) && !Motion.ReadInput(Vaccum_Tool3_Robot)) { MessengerData = "Vaccum Tool 3 Robot Error"; return true; }
	if (Motion.ReadOuput(Vaccum_Robot_4) && !Motion.ReadInput(Vaccum_Tool4_Robot)) { MessengerData = "Vaccum Tool 4 Robot Error"; return true; }

	if (!Motion.ReadOuput(XL_Tool_Robot_1) && !Motion.ReadInput(SSXL_Tool1_RobotUp)) { MessengerData = "Sensor Tool 1 Robot Error"; return true; }
	if (!Motion.ReadOuput(XL_Tool_Robot_2) && !Motion.ReadInput(SSXL_Tool2_RobotUp)) { MessengerData = "Sensor Tool 2 Robot Error"; return true; }
	if (!Motion.ReadOuput(XL_Tool_Robot_3) && !Motion.ReadInput(SSXL_Tool3_RobotUp)) { MessengerData = "Sensor Tool 3 Robot Error"; return true; }
	if (!Motion.ReadOuput(XL_Tool_Robot_4) && !Motion.ReadInput(SSXL_Tool4_RobotUp)) { MessengerData = "Sensor Tool 4 Robot Error"; return true; }

	if (Motion.ReadOuput(Robot_Vaccum_Tray) && !Motion.ReadInput(Vaccum_Tray_Robot)) { MessengerData = "Vaccum Tray Robot Error"; return true; }

	//Socket
	if (Motion.ReadOuput(Socket_Vaccum_1) && !Motion.ReadInput(Vaccum_Socket_1)) { MessengerData = "Vaccum Socket 1 Error"; return true; }
	if (Motion.ReadOuput(Socket_Vaccum_2) && !Motion.ReadInput(Vaccum_Socket_2)) { MessengerData = "Vaccum Socket 2 Error"; return true; }
	if (Motion.ReadOuput(Socket_Vaccum_3) && !Motion.ReadInput(Vaccum_Socket_3)) { MessengerData = "Vaccum Socket 3 Error"; return true; }
	if (Motion.ReadOuput(Socket_Vaccum_4) && !Motion.ReadInput(Vaccum_Socket_4)) { MessengerData = "Vaccum Socket 4 Error"; return true; }
	
	if (Motion.ReadOuput(Socket_FW_1) && !Motion.ReadInput(Socket1_Fw)) { MessengerData = "Sensor Socket 1 FW Error"; return true; }
	if (Motion.ReadOuput(Socket_FW_2) && !Motion.ReadInput(Socket2_Fw)) { MessengerData = "Sensor Socket 2 FW Error"; return true; }
	if (Motion.ReadOuput(Socket_FW_3) && !Motion.ReadInput(Socket3_Fw)) { MessengerData = "Sensor Socket 3 FW Error"; return true; }
	if (Motion.ReadOuput(Socket_FW_4) && !Motion.ReadInput(Socket4_Fw)) { MessengerData = "Sensor Socket 4 FW Error"; return true; }

	if (!Motion.ReadOuput(Socket_FW_1) && !Motion.ReadInput(Socket1_Rv)) { MessengerData = "Sensor Socket 1 RV Error"; return true; }
	if (!Motion.ReadOuput(Socket_FW_2) && !Motion.ReadInput(Socket2_Rv)) { MessengerData = "Sensor Socket 2 RV Error"; return true; }
	if (!Motion.ReadOuput(Socket_FW_3) && !Motion.ReadInput(Socket3_Rv)) { MessengerData = "Sensor Socket 3 RV Error"; return true; }
	if (!Motion.ReadOuput(Socket_FW_4) && !Motion.ReadInput(Socket4_Rv)) { MessengerData = "Sensor Socket 4 RV Error"; return true; }
	
	if (Motion.ReadOuput(Socket_UP_1) && Motion.ReadInput(Socket1_Up)) { MessengerData = "Sensor Socket 1 Up Error"; return true; }
	if (Motion.ReadOuput(Socket_UP_2) && Motion.ReadInput(Socket2_Up)) { MessengerData = "Sensor Socket 2 Up Error"; return true; }
	if (Motion.ReadOuput(Socket_UP_3) && Motion.ReadInput(Socket3_Up)) { MessengerData = "Sensor Socket 3 Up Error"; return true; }
	if (Motion.ReadOuput(Socket_UP_4) && Motion.ReadInput(Socket4_Up)) { MessengerData = "Sensor Socket 4 Up Error"; return true; }

	//Tray Loading
	if (Motion.ReadOuput(XL_Do_Tray_Loading_Fw) && (!Motion.ReadInput(SSXL_Do_Tray_Loading_Out_Trai) || !Motion.ReadInput(SSXL_Do_Tray_Loading_Out_Phai))) { MessengerData = "Sensor Hander Tray Loading Out Error"; return true; }
	if (Motion.ReadOuput(XL_Do_Tray_Loading_Rv) && (!Motion.ReadInput(SSXL_Do_Tray_Loading_In_Trai) || !Motion.ReadInput(SSXL_Do_Tray_Loading_In_Phai)))   { MessengerData = "Sensor Hander Tray Loading In Error"; return true; }
	
	if (Motion.ReadOuput(XL_Aline_Loading_Fw) && !Motion.ReadInput(SSXL_AlineTray_Loading_Out)) { MessengerData = "Sensor Aline Tray Loading Fw Error"; return true; }
	if (Motion.ReadOuput(XL_Aline_Loading_Rv) && !Motion.ReadInput(SSXL_AlineTray_Loading_In)) { MessengerData = "Sensor Aline Tray Loading Rv Error"; return true; }

	//if (Motion.ReadOuput(XL_Chot_Stack_Loading_Fw) && !Motion.ReadInput(XL_Chot_Stack_Loading_Fw)) { MessengerData = "Sensor Stack Tray Loading Fw Error"; return true; }
	//if (Motion.ReadOuput(XL_Chot_Stack_Loading_Rv) && !Motion.ReadInput(XL_Chot_Stack_Loading_Rv)) { MessengerData = "Sensor Stack Tray Loading Rv Error"; return true; }

	if (Motion.ReadOuput(XL_Chan_Tray_Loading_Dung) && !Motion.ReadInput(SSXL_Chan_Tray_Loading_Dung)) { MessengerData = "Sensor Rotation Tray Loading Up Error"; return true; }
	if (Motion.ReadOuput(XL_Chan_Tray_Loading_Nam) && !Motion.ReadInput(SSXL_Chan_Tray_Loading_Nam))   { MessengerData = "Sensor Rotation Tray Loading Down Error"; return true; }

	//Tray Unloading
	//if (Motion.ReadOuput(XL_Do_Tray_Unloading_Fw) && (!Motion.ReadInput(SSXL_Do_Tray_Unloading_Out_Trai) || !Motion.ReadInput(SSXL_Do_Tray_Unloading_Out_Phai))) { MessengerData = "Sensor Hander Tray Unloading Out Error"; return true; }
	//if (Motion.ReadOuput(XL_Do_Tray_Unloading_Rv) && (!Motion.ReadInput(SSXL_Do_Tray_Unloading_In_Trai) || !Motion.ReadInput(SSXL_Do_Tray_Unloading_In_Phai)))   { MessengerData = "Sensor Hander Tray Unloading In Error"; return true; }

	if (Motion.ReadOuput(XL_Aline_Unloading_Fw) && !Motion.ReadInput(SSXL_AlineTray_Unloading_Out)) { MessengerData = "Sensor Aline Tray Unloading Fw Error"; return true; }
	if (Motion.ReadOuput(XL_Aline_Unloading_Rv) && !Motion.ReadInput(SSXL_AlineTray_Unloading_In)) { MessengerData = "Sensor Aline Tray Unloading Rv Error"; return true; }

	if (Motion.ReadOuput(XL_Chot_Stack_Unloading_Fw) && !Motion.ReadInput(XL_Chot_Stack_Unloading_Fw)) { MessengerData = "Sensor Stack Tray Unloading Fw Error"; return true; }
	if (Motion.ReadOuput(XL_Chot_Stack_Unloading_Rv) && !Motion.ReadInput(XL_Chot_Stack_Unloading_Rv)) { MessengerData = "Sensor Stack Tray Unloading Rv Error"; return true; }

	if (Motion.ReadOuput(XL_Chan_Tray_Unloading_Dung) && !Motion.ReadInput(SSXL_Chan_Tray_Unloading_Dung)) { MessengerData = "Sensor Rotation Tray Unloading Up Error"; return true; }
	if (Motion.ReadOuput(XL_Chan_Tray_Unloading_Nam) && !Motion.ReadInput(SSXL_Chan_Tray_Unloading_Nam)) { MessengerData = "Sensor Rotation Tray Unloading Down Error"; return true; }
//
	if (Motion.ReadOuput(XL_Aline_CAM) && !Motion.ReadInput(SSXL_Aline_FW)) { MessengerData = "Sensor Aline FW Error"; return true; }
	if (!Motion.ReadOuput(XL_Aline_CAM) && !Motion.ReadInput(SSXL_Aline_BW)) { MessengerData = "Sensor Aline BW Error"; return true; }

	
	MessengerData = "";
	return false;
}

bool CHandlerMCDoc::UnloadingTray()
{

	int  m_StepRun = 0;
	while (true)
	{
		if (Motion.ReadInput(Button_Stop))
		{
			ActionStop();
			break;
		}
		switch (m_StepRun)
		{
		case 0:
		{
			//Keo xi lanh ve
			//if (Motion.ReadInput(SSXL_Do_Tray_Unloading_Out_Trai) || Motion.ReadInput(SSXL_Do_Tray_Unloading_Out_Phai))
			//{
			//	XilanhDoTrayUnloadingOff();
			//}
			//Keo Aline ve
			if (!Motion.ReadInput(XL_Aline_Unloading_Rv))
			{
			    XilanhAlineTrayUnloadingOff();
			}
			//Off Rotation
			if (!Motion.ReadInput(XL_Chan_Tray_Unloading_Nam))
			{
			    ChanTrayUnloadingOff();
			}
			//Next
			if (/*Motion.ReadInput(SSXL_Do_Tray_Unloading_In_Trai) && Motion.ReadInput(SSXL_Do_Tray_Unloading_In_Phai) &&*/
				Motion.ReadInput(XL_Aline_Unloading_Rv) && Motion.ReadInput(SSXL_Chan_Tray_Unloading_Nam))
			{
				m_StepRun = 1;
			}
			//
			break;
		}
		case 1:
		{
			//Chay xuong vi tri Down
			if (RunPosUnloading(PosZ2Down))
			{
				m_StepRun = 2;
			}
			break;
		}
		case 2:
		{
			//Chay Bang tai
			if (Motion.ReadInput(Detech_Tray_On_Z_Unloading) || !Motion.ReadInput(Detech_Tray_In_Unloading))
			{
				ConveyorUnloadingOn();
			}
			
			//Off bang tai
			if (!Motion.ReadInput(Detech_Tray_On_Z_Unloading_Out))
			{
				ConveyorUnloadingOff();
			}
			
			if ( Motion.ReadInput(Detech_Tray_In_Unloading) && !Motion.ReadInput(Detech_Tray_On_Z_Unloading) && 
			     !Motion.ReadOuput(Conveyor_Unloading))
			{
				m_StepRun = 3;
			}
		
			break;
		}
		case 3:
		{
			//Nang len Vi tri ready
			if (RunPosUnloading(PosZ2Up))
			{
				m_StepRun = 4;
			}		
			break;
		}
		case 4:
		{
			return true;
		}
		default:
			break;
		}
	}
	return false;
}

bool CHandlerMCDoc::ReadyToUnloadingTray()
{
	if (Motion.ReadInput(Detech_Tray_On_Z_Unloading))
	{
		if ((PosZ2Up > Motion.StatusGetActPos(AxisY)) && !Motion.ReadInput(Detech_Tray_Up_Unloading))
		{
			return true;
		}
	}
	else
	{
		if (/*PosZ2Up == Motion.StatusGetActPos(AxisY)) && */!Motion.ReadInput(Detech_Tray_Up_Unloading))
		{
			return true;
		}

	}
	return false;
}
bool CHandlerMCDoc::ReadyToLoadingTray()
{
	if (ReadInput(SSXL_AlineTray_Loading_Out) && !ReadInput(Detech_Tray_Up_Loading) &&
		ReadInput(SSXL_Do_Tray_Loading_Out_Trai) && ReadInput(SSXL_Do_Tray_Loading_Out_Phai)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
//Xilanh tien
bool CHandlerMCDoc::SafetyDownZ2UnloadingTien()
{
	if (
		!ReadInput(Detech_Tray_Up_Unloading) &&
		//ReadInput(SSXL_Do_Tray_Unloading_In_Trai) &&
		//ReadInput(SSXL_Do_Tray_Unloading_In_Phai) &&
		ReadInput(SSXL_AlineTray_Unloading_In) //&&
		//ReadInput(Detech_Tray_On_Z_Unloading)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//Xilanh lui
bool CHandlerMCDoc::SafetyDownZ2UnloadingLui()
{
	if (
		!ReadInput(Detech_Tray_Up_Unloading) &&
		ReadInput(SSXL_AlineTray_Unloading_Out) //&&
											   //ReadInput(Detech_Tray_On_Z_Unloading)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CHandlerMCDoc::ActionDownZUnloading()
{
	switch (m_ActionDownZUnloading)
	{
	case 0://Tien xi lanh aline lan dau
	{
		if (SafetyDownZ2UnloadingTien())
		{
			XilanhAlineTrayUnloadingOn();
		}
		if (SafetyDownZ2UnloadingLui())
		{
			Sleep(200);
			m_ActionDownZUnloading = 1;
		}
		
		break;
	}
	case 1://Lui xi lanh aline lan dau
	{
		if (SafetyDownZ2UnloadingLui())
		{
			XilanhAlineTrayUnloadingOff();			
		}
		if (SafetyDownZ2UnloadingTien())
		{
			Sleep(200);
			m_ActionDownZUnloading = 2;
		}
		
		break;
	}
	case 2://Tien xi lanh lan 2
	{
		if (SafetyDownZ2UnloadingTien())
		{
			XilanhAlineTrayUnloadingOn();
		}
		if (SafetyDownZ2UnloadingLui())
		{
			Sleep(200);
			m_ActionDownZUnloading = 3;
		}
		break;
	}
	case 3://Lui xilanh lan 2
	{
		if (SafetyDownZ2UnloadingLui())
		{
			XilanhAlineTrayUnloadingOff();
		}
		if (SafetyDownZ2UnloadingTien())
		{
			Sleep(200);
			m_ActionDownZUnloading = 4;
		}

		break;
	}
	case 4://Jog ha thap truc Z2 xuong voi toc do  speed jog 2
	{
		if (!ReadInput(Detech_Tray_Up_Unloading))
		{
			if (Motion.Status_OnOff(AxisZ))
			{
				Motion.JogRun(AxisY, -DataMotor.SpeedJog2, DataMotor.Acc, DataMotor.Dec);
			}
		}
		else
		{
			Sleep(1000);
			Motion.JogStop(AxisY);
			m_ActionDownZUnloading = 5;
		}
		break;
	}
	case 5://Jog z2 len voi toc do speed jog 3
	{
		if (ReadInput(Detech_Tray_Up_Unloading))
		{
			if (Motion.Status_OnOff(AxisZ))
			{
				Motion.JogRun(AxisY, DataMotor.SpeedJog3, DataMotor.Acc, DataMotor.Dec);
			}
		}
		else
		{
			Sleep(200);
			Motion.JogStop(AxisY);
			m_ActionDownZUnloading = 6;
		}
		break;
	}
	case 6:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}


bool CHandlerMCDoc::SafetyDoor()
{
	if (NotUseSafety)
	{
		return true;
	}
	//
	if (!ReadInput(Safety_Door_Side_Left))
	{
		AfxMessageBox("Door Side Left Open");
	}
	if (!ReadInput(Safety_Door_Front_Left))
	{
		AfxMessageBox("Door Front Left Open");
	}
	if (!ReadInput(Safety_Door_Front_Right))
	{
		AfxMessageBox("Door Side Right Open");
	}
	if (!ReadInput(Safety_Door_Side_Right))
	{
		AfxMessageBox("Door Side Right Open");
	}
	if (!ReadInput(Safety_Door_After))
	{
		AfxMessageBox("Door After Open");
	}
	//
	if (ReadInput(Safety_Door_Side_Left) && ReadInput(Safety_Door_Front_Left) &&
		ReadInput(Safety_Door_Front_Right) && ReadInput(Safety_Door_Side_Right) && ReadInput(Safety_Door_After))
	{
		return true;
	}

	return false;
}