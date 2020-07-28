#pragma once
#include "CreateModelDlg.h"

// SaveDataModel dialog

class SaveDataModel : public CDialogEx
{
	DECLARE_DYNAMIC(SaveDataModel)

public:
	SaveDataModel(CWnd* pParent = NULL);   // standard constructor
	virtual ~SaveDataModel();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAVE_DATA_MODEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickExit();
	void ClickDataLoading();
	void ClickDataUnloadingLeft();
	void ClickDataUnloadingRight();
	void CreateDataModelUnloading(int m_array, CString mPath);
	void CreateDataStatusLoading(CString mPath);

	CreateModelDlg m_Data;
};
