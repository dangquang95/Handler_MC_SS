#pragma once
#include "GCharDlg.h"
#include "btnenh.h"
#include "btnenh.h"
#include "IniFile.h" 

// DlgDelayCylinder dialog

class DlgDelayCylinder : public CDialogEx
{
	DECLARE_DYNAMIC(DlgDelayCylinder)

public:
	DlgDelayCylinder(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgDelayCylinder();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELAY_CYLINDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CBtnEnh m_Tool1_Robot;
	CBtnEnh m_Tool2_Robot;
	CBtnEnh m_Tool3_Robot;
	CBtnEnh m_Tool4_Robot;
	CBtnEnh m_Socket1_FwRV;
	CBtnEnh m_Socket2_FwRV;
	CBtnEnh m_Socket3_FwRV;
	CBtnEnh m_Socket4_FwRV;
	CBtnEnh m_Socket1_UpDown;
	CBtnEnh m_Socket2_UpDown;
	CBtnEnh m_Socket3_UpDown;
	CBtnEnh m_Socket4_UpDown;
	CBtnEnh m_Cylinder_Handler;
	CBtnEnh m_Cylinder_Aline;
	CBtnEnh m_Cylinder_Rotation;
	CBtnEnh m_Cylinder_Stack;
	DECLARE_EVENTSINK_MAP()
	void ClickExit1();
	void ClickSaveData();
	void ViewDataDelay();
	void ClickCylinderTool1Robot();
	void ClickCylinderTool2Robot();
	void ClickCylinderTool3Robot();
	void ClickCylinderTool4Robot();
	void ClickCylinderSocket1Fwrv();
	void ClickCylinderSocket2Fwrv();
	void ClickCylinderSocket3Fwrv();
	void ClickCylinderSocket4Fwrv();
	void ClickCylinderSocket1Updown();
	void ClickCylinderSocket2Updown();
	void ClickCylinderSocket3Updown();
	void ClickCylinderSocket4Updown();
	void ClickCylinderHandeler();
	void ClickCylinderAline();
	void ClickCylinderRotation();
	void ClickCylinderStack();
	virtual BOOL OnInitDialog();
};
