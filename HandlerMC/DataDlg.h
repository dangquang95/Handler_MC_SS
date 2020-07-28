#pragma once
#include "ReadDataMotion.h"
#include "DataMotorDlg.h"
#include "SelectAction.h"
#include "VisionDlg.h"
#include "SaveDataModel.h"
// DataDlg dialog

class DataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DataDlg)

public:
	DataDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~DataDlg();

// Dialog Data
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATA_MAIN_FORM };
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
	DECLARE_EVENTSINK_MAP()
	void ClickModelData();
	void ClickTcpClient();
	void ClickLoadData();
	void ClickRunVelocity();
	void ClickSelectPhoneTest();
	void ClickVisionSetting();
	void ClickSaveData();
	void ClickVacuumDelay();
	void ClickCylinderDelay();
};
