#pragma once

#include "btnenh.h"
#include "MainFrm.h"
// GCharDlg dialog

class GCharDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GCharDlg)

public:
	GCharDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~GCharDlg();

// Dialog Data
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GET_CHAR };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	//
	void BtnDisable();
	CString GetStringValue();

	CBtnEnh	m_sDispValue;
	CBtnEnh	m_bDot;
	CBtnEnh	m_bEqual;
	CBtnEnh	m_bColon;
	CBtnEnh	m_bWon;
	CString Chara;//Result nhap du lieu
protected:
	BOOL ShiftKey;
	BOOL m_bpwd;
	BOOL m_bbtndisable;
	int m_intMaxChar;
	CString m_strWndText;
	void InitStaticDispWnd();
	BOOL VerifyMaxChar();

	afx_msg void OnKeyOk();
	afx_msg void OnKeyEsc();
	afx_msg void OnKeyBack();
	afx_msg void OnKeyClear();
	afx_msg void OnKey1();
	afx_msg void OnKey2();
	afx_msg void OnKey3();
	afx_msg void OnKey4();
	afx_msg void OnKey5();
	afx_msg void OnKey6();
	afx_msg void OnKey7();
	afx_msg void OnKey8();
	afx_msg void OnKey9();
	afx_msg void OnKey0();
	afx_msg void OnKeyQ();
	afx_msg void OnKeyW();
	afx_msg void OnKeyE();
	afx_msg void OnKeyR();
	afx_msg void OnKeyT();
	afx_msg void OnKeyY();
	afx_msg void OnKeyU();
	afx_msg void OnKeyI();
	afx_msg void OnKeyO();
	afx_msg void OnKeyP();
	afx_msg void OnKeyA();
	afx_msg void OnKeyS();
	afx_msg void OnKeyD();
	afx_msg void OnKeyF();
	afx_msg void OnKeyG();
	afx_msg void OnKeyH();
	afx_msg void OnKeyJ();
	afx_msg void OnKeyK();
	afx_msg void OnKeyL();
	afx_msg void OnKeyZ();
	afx_msg void OnKeyX();
	afx_msg void OnKeyC();
	afx_msg void OnKeyV();
	afx_msg void OnKeyB();
	afx_msg void OnKeyN();
	afx_msg void OnKeyM();
	afx_msg void OnKeyEqual();
	afx_msg void OnKeyShift();
	afx_msg void OnKeyColon();
	afx_msg void OnKeyDot();
	afx_msg void OnKeyDash();
	afx_msg void OnKeyUnderBar();

	DECLARE_EVENTSINK_MAP()


private:
	int m_cxChar;
	int m_cyChar;
	CRect m_rect;
	void UpdateDisplay(COLORREF bkcolor = RGB(255, 255, 255));

public:
	CString m_strGetVal;

	virtual BOOL OnInitDialog();

};
