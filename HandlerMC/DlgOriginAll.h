#pragma once

#include "btnenh.h"
// DlgOriginAll dialog

class DlgOriginAll : public CDialogEx
{
	DECLARE_DYNAMIC(DlgOriginAll)

public:
	DlgOriginAll(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgOriginAll();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ORIGINALL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	CBtnEnh m_CurrentPosZ1;
	CBtnEnh m_CurrentPosZ2;
	CBtnEnh m_OnOffServoZ1;
	CBtnEnh m_OnOffServoZ2;

	CString m_ViewCurrentPosZ1;
	CString m_ViewCurrentPosZ2;
	CString m_ViewOnOffServoZ1;
	CString m_ViewOnOffServoZ2;

	double  CurentPosX;
	double  CurentPosY;

	DECLARE_EVENTSINK_MAP()
	void ClickAxis1Origin();
	void ClickAxis2Origin();
	void ClickAxis1ServoLeft();
	void ClickAxis1ServoRight();
	void ViewPosition();
	void ClickStoporigin();
	void ClickInitLoading();
	void ClickInitUnloading();



	bool ClickInitSocket();
	void ClickInitToolRobot();
};
