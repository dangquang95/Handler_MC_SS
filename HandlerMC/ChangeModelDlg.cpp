// ChangeModelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "ChangeModelDlg.h"
#include "afxdialogex.h"
#include "HandlerMCView.h"

// ChangeModelDlg dialog

IMPLEMENT_DYNAMIC(ChangeModelDlg, CDialogEx)

ChangeModelDlg::ChangeModelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHANGE_MODEL, pParent)
{

}

ChangeModelDlg::~ChangeModelDlg()
{
}

void ChangeModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MODEL_LIST, m_modellist);
	DDX_Control(pDX, IDC_NUMBER_ROW_USE, m_NumberRow);
	DDX_Control(pDX, IDC_NUMBER_COLUMN_USE, m_NumberColumn);
	DDX_Control(pDX, IDC_NAME_MODEL_USE, m_NumberModel);
}


BEGIN_MESSAGE_MAP(ChangeModelDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// ChangeModelDlg message handlers
BEGIN_EVENTSINK_MAP(ChangeModelDlg, CDialogEx)
	ON_EVENT(ChangeModelDlg, IDB_MODEL_CREATE, DISPID_CLICK, ChangeModelDlg::ClickModelCreate, VTS_NONE)
	ON_EVENT(ChangeModelDlg, IDB_MODEL_DELETE, DISPID_CLICK, ChangeModelDlg::ClickModelDelete, VTS_NONE)
	ON_EVENT(ChangeModelDlg, IDB_EXIT, DISPID_CLICK, ChangeModelDlg::ClickExit, VTS_NONE)
	ON_EVENT(ChangeModelDlg, IDB_MODEL_LOAD, DISPID_CLICK, ChangeModelDlg::ClickModelLoad, VTS_NONE)
END_EVENTSINK_MAP()


void ChangeModelDlg::ClickModelCreate()
{
	CreateModelDlg ShowDlg;
	ShowDlg.DoModal();
}


void ChangeModelDlg::ClickModelDelete()
{
	const int result = MessageBox("Do you want delete model?", "Message", MB_YESNO); //MB_YESNOCANCEL)

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


	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	vector<CreatNewModel> BufferChangeModel;
	int SttNumber;
	SttNumber = m_modellist.GetCurSel();
	int k = pDoc->CNewModel.size();
	if (SttNumber < 0 || SttNumber > k) return;

	pDoc->DeleteForder("Model\\" + pDoc->CNewModel.at(SttNumber).NameModel);

	CString NameForderDelete = pDoc->CNewModel.at(SttNumber).NameModel;
	//lua vao buffer
	for (int i = SttNumber + 1; i < k; i++)
	{
		BufferChangeModel.push_back(pDoc->CNewModel.at(i));
	}
	//xoa cac phan tu
	for (int i = SttNumber; i < k; i++)
	{
		pDoc->CNewModel.pop_back();
	}
	//Nap lai phan tu
	for (int i = 0; i < BufferChangeModel.size(); i++)
	{
		pDoc->CNewModel.push_back(BufferChangeModel.at(i));
	}
	//
	pDoc->SaveNameDataAll();
	UpdateListBox();
}


void ChangeModelDlg::ClickExit()
{
	CDialog::OnCancel();
}


void ChangeModelDlg::ClickModelLoad()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	CHandlerMCView * pView = (CHandlerMCView *)pFrm->GetActiveView();

	const int result = MessageBox("Do you want load model?", "Message", MB_YESNO); //MB_YESNOCANCEL)

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


	int SttNumber;
	SttNumber = m_modellist.GetCurSel();
	int k = pDoc->CNewModel.size();

	if (SttNumber < 0 || SttNumber > k)
	{
		AfxMessageBox("Load model fail");
		return;
	}
	pDoc->RowTray = pDoc->CNewModel.at(m_modellist.GetCurSel()).Row;
	pDoc->ColumnTray = pDoc->CNewModel.at(m_modellist.GetCurSel()).Column;
	pDoc->NameModelUse = pDoc->CNewModel.at(m_modellist.GetCurSel()).NameModel;

	//Loading data form file .dat
	CString PathLoading[4];
    PathLoading[0] = "Model\\" + pDoc->NameModelUse + "\\PositionTrayLoading.dat";
	PathLoading[1] = "Model\\" + pDoc->NameModelUse + "\\PositionTrayNgLeft.dat";
	PathLoading[2] = "Model\\" + pDoc->NameModelUse + "\\PositionTrayNgRight.dat";
	PathLoading[3] = "Model\\" + pDoc->NameModelUse + "\\StatusUnloading.dat";

	pDoc->InitalinePos();
	for (int i = 0; i < 3; i++)
	{
		pDoc->ReadDataPosition(PathLoading[i],i);
	}
	pDoc->ReadDataStatusUnloading(PathLoading[3]);


	pDoc->StatusLoadingModel = TRUE;
	pDoc->StatusLoadingModel2 = TRUE;
	pDoc->ModelAction = SttNumber;
	pDoc->SaveNameDataAll();
	AfxMessageBox("Loading Data Succsess");
}

void ChangeModelDlg::UpdateListBox()
{
	//Update listbox
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	m_modellist.ResetContent();
	for (int i = 0; i < pDoc->CNewModel.size(); i++)
	{
		m_modellist.AddString(pDoc->CNewModel.at(i).NameModel);
	}
	//
}

void ChangeModelDlg::UpdaterowColumn()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	CString CapRow, CapColumn;

	int SttNumber;
	SttNumber = m_modellist.GetCurSel();
	int k = pDoc->CNewModel.size();
	if (SttNumber < 0 || SttNumber > k)
	{
		SttNumber = pDoc->ModelAction;
	}

	CapRow.Format("%d", pDoc->CNewModel.at(SttNumber).Row);
	CapColumn.Format("%d", pDoc->CNewModel.at(SttNumber).Column);

	m_NumberRow.SetCaption(CapRow);
	m_NumberColumn.SetCaption(CapColumn);
	m_NumberModel.SetCaption(pDoc->CNewModel.at(SttNumber).NameModel);
}

void ChangeModelDlg::OnTimer(UINT_PTR nIDEvent)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	switch (nIDEvent)
	{
	case 1:
		if (pDoc->CreateModelSuccses)
		{
			UpdateListBox();
			pDoc->CreateModelSuccses = FALSE;
		}
		UpdaterowColumn();
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL ChangeModelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetTimer(1,50, NULL);
	UpdateListBox();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}



