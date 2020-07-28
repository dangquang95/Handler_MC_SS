#pragma once
#include "btnenh.h"
#include "HandlerMCDoc.h"

// GetNumberDlg dialog

class GetNumberDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GetNumberDlg)

public:
	GetNumberDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~GetNumberDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GET_NUMBER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	CHandlerMCDoc* m_pDoc;
public:
	CString m_strText;
	double dbKeyBoad;
	CBtnEnh m_tText_result;
	void DisplayText();

	void ClickKeyBtnReset();
	void ClickKeyBtnDelete();
	void ClickKeyBtnEsc();
	void ClickKeyBtnOk();
	void ClickKeyBtnNum1();
	void ClickKeyBtnNum2();
	void ClickKeyBtnNum3();
	void ClickKeyBtnNum4();
	void ClickKeyBtnNum5();
	void ClickKeyBtnNum6();
	void ClickKeyBtnNum7();
	void ClickKeyBtnNum8();
	void ClickKeyBtnNum9();
	void ClickKeyBtnNum0();
	void ClickKeyBtn_();
	void ClickKeyBtnDot();



	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_EVENTSINK_MAP()

};
