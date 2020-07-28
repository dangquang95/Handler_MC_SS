#pragma once
#include "CreateModelDlg.h"
#include "GetNumberDlg.h"
#include "GCharDlg.h"
#include "btnenh.h"
#include "afxwin.h"

// ChangeModelDlg dialog

class ChangeModelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeModelDlg)

public:
	ChangeModelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ChangeModelDlg();

// Dialog Data
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHANGE_MODEL };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickModelCreate();
	void ClickModelDelete();
	void ClickExit();
	void ClickModelLoad();
	void UpdateListBox();
	CListBox m_modellist;
    void UpdaterowColumn();
	void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	CBtnEnh m_NumberRow;
	CBtnEnh m_NumberColumn;
	CBtnEnh m_NumberModel;
};
