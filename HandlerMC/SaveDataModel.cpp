// SaveDataModel.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "SaveDataModel.h"
#include "afxdialogex.h"


// SaveDataModel dialog

IMPLEMENT_DYNAMIC(SaveDataModel, CDialogEx)

SaveDataModel::SaveDataModel(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SAVE_DATA_MODEL, pParent)
{

}

SaveDataModel::~SaveDataModel()
{
}

void SaveDataModel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SaveDataModel, CDialogEx)
END_MESSAGE_MAP()


// SaveDataModel message handlers
BEGIN_EVENTSINK_MAP(SaveDataModel, CDialogEx)
	ON_EVENT(SaveDataModel, IDB_EXIT, DISPID_CLICK, SaveDataModel::ClickExit, VTS_NONE)
	ON_EVENT(SaveDataModel, IDB_DATA_LOADING, DISPID_CLICK, SaveDataModel::ClickDataLoading, VTS_NONE)
	ON_EVENT(SaveDataModel, IDB_DATA_UNLOADING_LEFT, DISPID_CLICK, SaveDataModel::ClickDataUnloadingLeft, VTS_NONE)
	ON_EVENT(SaveDataModel, IDB_DATA_UNLOADING_RIGHT, DISPID_CLICK, SaveDataModel::ClickDataUnloadingRight, VTS_NONE)
END_EVENTSINK_MAP()


void SaveDataModel::ClickExit()
{
	CDialog::OnCancel();
}


void SaveDataModel::ClickDataLoading()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CString m_Path = "Model\\" + pDoc->NameModelUse;
	CString m_Path2 = m_Path + "\\PositionTrayLoading.dat";
	CString m_Path3 = m_Path + "\\StatusUnloading.dat";
	//Tao forder
	//
	HANDLE hFile1 = CreateFile(m_Path2, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(hFile1);
	//
	//HANDLE hFile2 = CreateFile(m_Path3, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//CloseHandle(hFile2);
	//
	CreateDataModelUnloading(0, m_Path2);
	CreateDataStatusLoading(m_Path3);
	AfxMessageBox("Save Complete");
}


void SaveDataModel::ClickDataUnloadingLeft()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CString m_Path = "Model\\" + pDoc->NameModelUse;
	CString m_Path2 = m_Path + "\\PositionTrayNgLeft.dat";
	//Tao forder
	HANDLE hFile1 = CreateFile(m_Path2, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(hFile1);
	CreateDataModelUnloading(1, m_Path2);
	AfxMessageBox("Save Complete");
}


void SaveDataModel::ClickDataUnloadingRight()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CString m_Path = "Model\\" + pDoc->NameModelUse;
	CString m_Path2 = m_Path + "\\PositionTrayNgRight.dat";
	//Tao forder
	HANDLE hFile1 = CreateFile(m_Path2, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(hFile1);
	CreateDataModelUnloading(2, m_Path2);

	AfxMessageBox("Save Complete");
}


void SaveDataModel::CreateDataModelUnloading(int m_array,CString mPath)
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
		for (int i = 0; i < pDoc->RowTray; i++)
		{
			for (int j = 0; j < pDoc->ColumnTray; j++)
			{
				stt.Format("PosX%d-Y%d = ", i, j);
				fn.WriteString(stt);
				cstr.Format("X :%ld   ",  pDoc->PosXY[m_array].at(i).at(j).dPositionX);
				fn.WriteString(cstr);
				cstr.Format("Y :%ld    ", pDoc->PosXY[m_array].at(i).at(j).dPositionY);
				fn.WriteString(cstr);
				cstr.Format("Z :%ld    ", pDoc->PosXY[m_array].at(i).at(j).dPositionZ);
				fn.WriteString(cstr);
				cstr.Format("Status:%d\n", pDoc->PosXY[m_array].at(i).at(j).status);
				fn.WriteString(cstr);
			}
		}
		fn.Close();
	}
}

void SaveDataModel::CreateDataStatusLoading(CString mPath)
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
		for (int i = 0; i < pDoc->RowTray; i++)
		{
			for (int j = 0; j < pDoc->ColumnTray; j++)
			{
				stt.Format("PosX%d-Y%d-StatusUnloading = %d \n", i, j, pDoc->PosXY[0].at(i).at(j).unloading);
				fn.WriteString(stt);
			}
		}
		fn.Close();
	}
}