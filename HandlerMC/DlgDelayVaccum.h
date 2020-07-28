#pragma once
#include "GCharDlg.h"
#include "btnenh.h"
#include "btnenh.h"
#include "IniFile.h" 
// DlgDelayVaccum dialog

class DlgDelayVaccum : public CDialogEx
{
	DECLARE_DYNAMIC(DlgDelayVaccum)

public:
	DlgDelayVaccum(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgDelayVaccum();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELAY_VACCUM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickExit1();
	void ClickVaccumTool1();
	CBtnEnh m_DataDelayVaccumToolRobot1;
	CBtnEnh m_DataDelayVaccumToolRobot2;
	CBtnEnh m_DataDelayVaccumToolRobot3;
	CBtnEnh m_DataDelayVaccumToolRobot4;
	CBtnEnh m_DataDelayVaccumSocket1;
	CBtnEnh m_DataDelayVaccumSocket2;
	CBtnEnh m_DataDelayVaccumSocket3;
	CBtnEnh m_DataDelayVaccumSocket4;
	CBtnEnh m_DataDelayVaccumTray;
	void ClickVaccumTool2();
	void ClickVaccumTool3();
	void ClickVaccumTool4();
	void ClickVaccumSocket1();
	void ClickVaccumSocket2();
	void ClickVaccumSocket3();
	void ClickVaccumSocket4();
	void ClickVaccumTray();
	void SetViewData();
	virtual BOOL OnInitDialog();
	void ClickSaveData();
};
