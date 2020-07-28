
// HandlerMCView.h : interface of the CHandlerMCView class
//

#pragma once

#include "afxwin.h"
#include "AutoDlg.h"
#include "ManualDlg.h"
#include "DataDlg.h"
#include "TeachDlg.h"
#include "LogDlg.h"


enum DlgNo
{
	AUTO_DLG = 0,
	MANUAL_DLG,
	TEACH_DLG,
	DATA_DLG,
	LOG_DLG,
};


class CHandlerMCView : public CFormView
{
protected: // create from serialization only
	CHandlerMCView();
	DECLARE_DYNCREATE(CHandlerMCView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_HANDLERMC_FORM };
#endif

// Attributes
public:
	CHandlerMCDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CHandlerMCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()


	AutoDlg*			AUTODLG;
	ManualDlg*			MANUDLG;
	DataDlg*			DATADLG;
	TeachDlg*			TEACHDLG;
	LogDlg*				LOGDLG;


	void CreateDlg();
	void SelectDlg(int DlgNo);
public:
	CArray<CRect, CRect> m_PositionArray;
	void SaveControlPosition();
	void ChangeControlPosition();
	CRect m_rtDlgArea;
	DECLARE_EVENTSINK_MAP()
	void ClickBtnAuto();
	void ClickBtneManual();
	void ClickBtnTeach();
	void ClickBtnData();
	void ClickBtnLog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void SetDataError(CString m_data);
	int m_numberInc = 0;
	CBtnEnh m_ViewErrorStatus;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // debug version in HandlerMCView.cpp
inline CHandlerMCDoc* CHandlerMCView::GetDocument() const
   { return reinterpret_cast<CHandlerMCDoc*>(m_pDocument); }
#endif

