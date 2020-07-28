#pragma once

#include "ImPanel.h"
#include "ImAdvPanel.h"
#include "afxwin.h"
#include "Mydefine.h"
#include "btnenh.h"
#include "afxcmn.h"
#include "ViewStepRunDlg.h"

// AutoDlg dialog

class AutoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AutoDlg)

public:
	AutoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AutoDlg();

// Dialog Data
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTO_MAIN_FORM };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	CArray<CRect, CRect> m_PositionArray;
	void SaveControlPosition();
	void ChangeControlPosition();

public:
	//Khai bao Mapping
	im::CImAdvPanel mPictureMap[3];
	void Generate();
	void MappingPisition(int numRows, int numColums, int disRows, int disColums);
	void DisplayImage(im::CImAdvPanel & panel, cv::Mat & img);
	//tray loading
	int numRows, numColums, disRows, disColums = 0;
	vector<vector<sPosition>> vPosition;
	int w = 640, h = 480;					//width - hight of picture from load
	cv::Mat mMap = Mat(5000, 5000, CV_8UC3);
	//cv::Mat mShow = mMap.clone();
	cv::Mat mShow = mMap;
	//
	void checkPosition(cv::Point point, int & x, int & y);
	void UpdatePosition();
	void AutoSetOnPictureLoading();
	void AutoSetOnPictureUnloadingRight();
	void AutoSetOnPictureUnloadingLeft();

	cv::Mat mMapBufer = Mat(5000, 5000, CV_8UC3);
	void UpdatestStatusMap();
	int m_Picture = 0;
	afx_msg void OnOptionOn();
	afx_msg void OnOptionOff();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point); 

	DECLARE_EVENTSINK_MAP()
	void ClickOriginReturn();
	void ViewDataTester();
	void InitListLog();
	void AddLog(CString content);
	CBtnEnh m_TotalCount[4];	
	CBtnEnh m_GoodCount[4];
	CBtnEnh m_NGCount[4];
	CBtnEnh m_TactTimer[4];
	CBtnEnh m_Status[4];
	CBtnEnh m_CommandTest[4];

	CListCtrl m_listViewStep;
	CBtnEnh m_simotion_result_tester[4];

	void ClickResultTester1();
	void ClickResultTester2();
	void ClickResultTester3();
	void ClickResultTester4();
	void ClickStop();
	void ClickStepDisp();

	CBtnEnh m_StatusTool1Loading;
	CBtnEnh m_StatusTool2Loading;
	CBtnEnh m_StatusTool1Unloading;
	CBtnEnh m_StatusTool2Unloading;

	CBtnEnh m_OnOffLeft;
	CBtnEnh m_OnOffRight;
	CBtnEnh m_OnOffLoading;
	bool m_FlagLeft = false;
	bool m_FlagRight = false;
	bool m_Flagloading = false;

	void ViewStatusHamdler();
	void ClickUnitInitial();
	void ClickStart();
	void ClickOnOffLeft();
	void ClickOnOffRight();
	
	void ClickOnOffLoading();
	void ClickUnloadingTray();
	void ClickSafety();
	CBtnEnh m_Using_Safety_Door;
	CBtnEnh m_Using_Vision;
	void ClickUsingVision();
	
	void ClickReady();
	CBtnEnh m_PictureRready;
	CBtnEnh m_End_Tray;
	void ClickEndTray();
};
