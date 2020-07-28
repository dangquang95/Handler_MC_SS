#pragma once
#include "GetNumberDlg.h"
#include "GCharDlg.h"
#include "btnenh.h"


// CreateModelDlg dialog

class CreateModelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CreateModelDlg)

public:
	CreateModelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CreateModelDlg();

// Dialog Data
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATE_MODEL };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickExit();
	CBtnEnh m_NameModel;
	CBtnEnh m_NumberRow;
	CBtnEnh m_NumberColumn;
	CString cstrPathFilePositionRun[4];
	CreatNewModel CreatNewModel;
	int RowModel;
	int ColumnModel;
	CString NameModel;
public:
	void ClickBtnCreate();
	void ClickNameModel();
	void ClickNumberRowModel();
	void ClickNumberColumnModel();
	void CreateForderModel();
	void CreateDataModelLoading( CString mPath);
	void CreateDataModelUnloading(CString mPath);
	void CreateStatusUnloading(CString mPath);

};
