#pragma once

#include "btnenh.h"
#include "GetNumberDlg.h"
#include "GCharDlg.h"
// DataMotorDlg dialog

class DataMotorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DataMotorDlg)

public:
	DataMotorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~DataMotorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATA_MOTOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	

	DECLARE_MESSAGE_MAP()
public:
	CBtnEnh m_AccDec;
	CBtnEnh m_SpeedJog1;
	CBtnEnh m_SpeedJog2;
	CBtnEnh m_SpeedJog3;
	CBtnEnh m_SpeedOriginZ1;
	CBtnEnh m_SpeedOriginZ2;
	CBtnEnh m_SpeedRunZ1;
	CBtnEnh m_SpeedRunZ2;

	void ViewDataMotor();
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	void ClickAccDec();
	void ClickSpeedJog1();
	void ClickSpeedJog2();
	void ClickSpeedJog3();
	void ClickSpeedOriginZ1();
	void ClickSpeedOriginZ2();
	void ClickSpeedRunZ1();
	void ClickSpeedRunZ2();
	void ClickExit1();
	void ClickSaveData();
};

