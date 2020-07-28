#pragma once
#include "DefineNameInOut.h"
#include  "btnenh.h"
// DlgOutput dialog

class DlgOutput : public CDialogEx
{
	DECLARE_DYNAMIC(DlgOutput)

public:
	DlgOutput(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgOutput();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_OUTPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickExit1();
	virtual BOOL OnInitDialog();
	void SetNameCaption();
	CBtnEnh m_Output[32];
};
