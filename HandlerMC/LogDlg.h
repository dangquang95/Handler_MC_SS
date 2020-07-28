#pragma once
#include "afxcmn.h"
#include "ViewStepRunDlg.h"

// LogDlg dialog

class LogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LogDlg)

public:
	LogDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~LogDlg();

// Dialog Data
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOG_MAIN_FORM };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CArray<CRect, CRect> m_PositionArray;
	void SaveControlPosition();
	void ChangeControlPosition();
	void InitListLog();
	void AddLog(CString content);
	// void OnLvnItemchangedListViewStep(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_ListViewLog;
	// void OnLvnItemchangedListViewLog(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_EVENTSINK_MAP()
	void ClickStepDispLog();
};
