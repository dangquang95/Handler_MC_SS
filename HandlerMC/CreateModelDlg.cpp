// CreateModelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "CreateModelDlg.h"
#include "afxdialogex.h"


// CreateModelDlg dialog

IMPLEMENT_DYNAMIC(CreateModelDlg, CDialogEx)

CreateModelDlg::CreateModelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATE_MODEL, pParent)
{

}

CreateModelDlg::~CreateModelDlg()
{
}

void CreateModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NAME_MODEL, m_NameModel);
	DDX_Control(pDX, IDC_NUMBER_ROW_MODEL, m_NumberRow);
	DDX_Control(pDX, IDC_NUMBER_COLUMN_MODEL, m_NumberColumn);
}


BEGIN_MESSAGE_MAP(CreateModelDlg, CDialogEx)
END_MESSAGE_MAP()


// CreateModelDlg message handlers
BEGIN_EVENTSINK_MAP(CreateModelDlg, CDialogEx)
	ON_EVENT(CreateModelDlg, IDB_EXIT, DISPID_CLICK, CreateModelDlg::ClickExit, VTS_NONE)
	ON_EVENT(CreateModelDlg, IDB_BTN_CREATE, DISPID_CLICK, CreateModelDlg::ClickBtnCreate, VTS_NONE)
	ON_EVENT(CreateModelDlg, IDC_NAME_MODEL, DISPID_CLICK, CreateModelDlg::ClickNameModel, VTS_NONE)
	ON_EVENT(CreateModelDlg, IDC_NUMBER_ROW_MODEL, DISPID_CLICK, CreateModelDlg::ClickNumberRowModel, VTS_NONE)
	ON_EVENT(CreateModelDlg, IDC_NUMBER_COLUMN_MODEL, DISPID_CLICK, CreateModelDlg::ClickNumberColumnModel, VTS_NONE)
END_EVENTSINK_MAP()


void CreateModelDlg::ClickExit()
{
	CDialog::OnCancel();
}


void CreateModelDlg::ClickBtnCreate()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CreatNewModel.NameModel = NameModel;
	CreatNewModel.Row = RowModel;
	CreatNewModel.Column = ColumnModel;
	if (NameModel != "" && RowModel > 0 && ColumnModel > 0)
	{
		pDoc->CNewModel.push_back(CreatNewModel);
		CreateForderModel();
		pDoc->CreateModelSuccses = TRUE;
		AfxMessageBox("Create Model Success");
	}
	else
	{
		AfxMessageBox("Create Model fail");
	}


	CDialog::OnCancel();
}


void CreateModelDlg::ClickNameModel()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	
	GCharDlg ShowDlg;
	ShowDlg.DoModal();

	NameModel = pDoc->CharReturn;
	if(NameModel != "") m_NameModel.SetCaption(NameModel);

}


void CreateModelDlg::ClickNumberRowModel()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	RowModel = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", RowModel);
	m_NumberRow.SetCaption(m_data);
}


void CreateModelDlg::ClickNumberColumnModel()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	GetNumberDlg ShowDlg;
	ShowDlg.DoModal();

	ColumnModel = (int)pDoc->NumberReturn;
	CString m_data;
	m_data.Format("%d", ColumnModel);
	m_NumberColumn.SetCaption(m_data);
}

void CreateModelDlg::CreateForderModel()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	//Tao forder
	CString m_Path = "Model\\" + NameModel;
	CreateDirectory(m_Path, NULL);
	//Tao file.dat
	//1
	CString WorkTray = "\\WorkTray.dat";
	CString cstrPathFileName = m_Path + WorkTray;
	HANDLE hFile = CreateFile(cstrPathFileName,GENERIC_READ,FILE_SHARE_READ,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	CloseHandle(hFile);
	//2 Tao 3 file lua  toa do 3 tray
    cstrPathFilePositionRun[0] = m_Path + "\\PositionTrayLoading.dat";
	cstrPathFilePositionRun[1] = m_Path + "\\PositionTrayNgLeft.dat";
	cstrPathFilePositionRun[2] = m_Path + "\\PositionTrayNgRight.dat";
	cstrPathFilePositionRun[3] = m_Path + "\\StatusUnloading.dat";

	HANDLE hFile1 = CreateFile(cstrPathFilePositionRun[0],	GENERIC_READ,FILE_SHARE_READ,NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	CloseHandle(hFile1);
	CreateDataModelLoading(cstrPathFilePositionRun[0]);//truyen du lieu vao file sau khi tao

	HANDLE hFile4 = CreateFile(cstrPathFilePositionRun[3], GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(hFile1);
	CreateStatusUnloading(cstrPathFilePositionRun[3]);//truyen du lieu vao file sau khi tao

	//BOOL bRes1 = FALSE;
	HANDLE hFile2 = CreateFile(cstrPathFilePositionRun[1], GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(hFile2);
	CreateDataModelUnloading(cstrPathFilePositionRun[1]);//truyen du lieu vao file sau khi tao

	//BOOL bRes1 = FALSE;
	HANDLE hFile3 = CreateFile(cstrPathFilePositionRun[2], GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    CloseHandle(hFile3);
	CreateDataModelUnloading(cstrPathFilePositionRun[2]);//truyen du lieu vao file sau khi tao


	//
	CFileFind ffind;
	CString strPath = cstrPathFileName;

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
		cstr.Format("Row			 = %d \n", RowModel);
		fn.WriteString(cstr);
		cstr.Format("Column		     = %d \n", ColumnModel);
		fn.WriteString(cstr);
		cstr.Format("Name Model	     = %s \n", NameModel);
		fn.WriteString(cstr);

		fn.Close();
	}
	//
	pDoc->SaveNameDataAll();
}

void CreateModelDlg::CreateDataModelLoading(CString mPath)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CFileFind ffind;
	CString strPath = mPath;

	if (ffind.FindFile((LPCTSTR)strPath) == FALSE)
	{
		AfxMessageBox("Not find");
	}
	else
	{
		CStdioFile fn;
		fn.Open(strPath, CFile::modeReadWrite);
		fn.WriteString("[Data]\n\n");
		CString stt,cstr;
		for (int i = 0; i < RowModel; i++)
		{
			for (int j = 0; j < ColumnModel; j++)
			{
				stt.Format("PosX%d-Y%d = ", i, j);
				fn.WriteString(stt);
				cstr.Format("X :%ld   ", (i+j)*12  /*pDoc->PosXY.at(i).at(j).dPositionX*/);
				fn.WriteString(cstr);
				cstr.Format("Y :%ld    ", (i + j) * 12/*pDoc->PosXY.at(i).at(j).dPositionY*/);
				fn.WriteString(cstr);
				cstr.Format("Z :%ld    ", (i + j) * 12 /*pDoc->PosXY.at(i).at(j).dPositionZ*/);
				fn.WriteString(cstr);
				cstr.Format("Status:%d\n", 1 /*pDoc->PosXY.at(i).at(j).status*/);
				fn.WriteString(cstr);
			}
		}
		fn.Close();
	}
}
void CreateModelDlg::CreateDataModelUnloading(CString mPath)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CFileFind ffind;
	CString strPath = mPath;

	if (ffind.FindFile((LPCTSTR)strPath) == FALSE)
	{
		AfxMessageBox("Not find");
	}
	else
	{
		CStdioFile fn;
		fn.Open(strPath, CFile::modeReadWrite);
		fn.WriteString("[Data]\n\n");
		CString stt, cstr;
		for (int i = 0; i < RowModel; i++)
		{
			for (int j = 0; j < ColumnModel; j++)
			{
				stt.Format("PosX%d-Y%d = ", i, j);
				fn.WriteString(stt);
				cstr.Format("X :%ld   ", (i + j) * 12  /*pDoc->PosXY.at(i).at(j).dPositionX*/);
				fn.WriteString(cstr);
				cstr.Format("Y :%ld    ", (i + j) * 12/*pDoc->PosXY.at(i).at(j).dPositionY*/);
				fn.WriteString(cstr);
				cstr.Format("Z :%ld    ", (i + j) * 12 /*pDoc->PosXY.at(i).at(j).dPositionZ*/);
				fn.WriteString(cstr);
				cstr.Format("Status:%d\n", 0/*pDoc->PosXY.at(i).at(j).status*/);
				fn.WriteString(cstr);
			}
		}
		fn.Close();
	}
}

void CreateModelDlg::CreateStatusUnloading(CString mPath)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CFileFind ffind;
	CString strPath = mPath;

	if (ffind.FindFile((LPCTSTR)strPath) == FALSE)
	{
		AfxMessageBox("Not find");
	}
	else
	{
		CStdioFile fn;
		fn.Open(strPath, CFile::modeReadWrite);
		fn.WriteString("[Data]\n\n");
		CString stt, cstr;
		for (int i = 0; i < RowModel; i++)
		{
			for (int j = 0; j < ColumnModel; j++)
			{
				stt.Format("PosX%d-Y%d-StatusUnloading = %d \n", i, j, pDoc->PosXY[0].at(i).at(j).unloading);
				fn.WriteString(stt);
			}
		}
		fn.Close();
	}
}