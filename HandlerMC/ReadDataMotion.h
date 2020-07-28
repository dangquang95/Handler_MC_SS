#pragma once
#include "afxcmn.h"


// ReadDataMotion dialog

class ReadDataMotion : public CDialogEx
{
	DECLARE_DYNAMIC(ReadDataMotion)

public:
	ReadDataMotion(CWnd* pParent = NULL);   // standard constructor
	virtual ~ReadDataMotion();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READ_DATA_MOTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void InitListLog();

	void AddLog(CString content);

	void LoadingDataMotion();

	void LoadingDataIO();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ViewData;
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	void ClickLoadDataMotion();
	void ClickLoadDataIo();
};
