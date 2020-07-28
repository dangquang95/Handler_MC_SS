#pragma once
#include "btnenh.h"

// SelectAction dialog

class SelectAction : public CDialogEx
{
	DECLARE_DYNAMIC(SelectAction)

public:
	SelectAction(CWnd* pParent = NULL);   // standard constructor
	virtual ~SelectAction();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECT_ACTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickExit1();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CBtnEnh m_StatusPhone[4];
	void ClickPhoneTest1();
	void ViewData();
	void ClickPhoneTest2();
	void ClickPhoneTest3();
	void ClickPhoneTest4();
	void ClickSaveData();
};
