#pragma once
#include "afxcmn.h"
#include "btnenh.h"

// ViewStepRunDlg dialog

class ViewStepRunDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ViewStepRunDlg)

public:
	ViewStepRunDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ViewStepRunDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIEW_STEP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickExit1();
	
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SetCaptionMain();
	void SetColorCaptionAll(int m_data);
	void SetColorCaptionStep1(int m_data);
	void SetColorCaptionStep2(int m_data);
	CBtnEnh DataCaption[8];
	vector<CString> m_dataViewList;
	void ViewDataStep1BufferLoading();
	void ViewDataStep2BufferLoading();
	void ReSetCaptionStep2BufferLoading();
	void SetCaptionStep2BufferLoading();
	void ViewDataStep1RobotLoadingCam();
	void ViewDataStep2RobotLoadingCam();
	void ViewDataStep1RobotLoadingVision();
	void ViewDataStep1RobotLoadingTesterFirtRun();
	void ViewDataStep2RobotLoadingTester();
	void ViewDataStep2RobotUnloadingTester();
	void ViewDataStep1UnloadingTrayOKFull();
	void ViewDataStep1RobotLoadingAndUnloadingRun();
	void ViewDataStep1RobotMoveTrayOKNg();
	void ViewDataStep1CheckTrayOKFull();
	CBtnEnh m_Step_1[6];
	CBtnEnh m_Step_2[8];

};
