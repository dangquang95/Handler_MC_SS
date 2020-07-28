#pragma once
#include "DefineNameInOut.h"
#include "btnenh.h"
// DlgInput dialog

class DlgInput : public CDialogEx
{
	DECLARE_DYNAMIC(DlgInput)

public:
	DlgInput(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgInput();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_INPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickExit1();
	void SetNameCaption();
	CBtnEnh m_InOut[32];
	CBtnEnh m_Title[4];
	virtual BOOL OnInitDialog();
	void ReadNameInput();
	void ReadNameOutput();
	void ActionOutput(int output);
	vector<CString> m_NameInput;
	vector<CString> m_Nameoutput;
	int IndexNext = 0;
	
	void ClickIo0();	
	void ClickIo1();
	void ClickIo2();
	void ClickIo3();
	void ClickIo4();
	void ClickIo5();
	void ClickIo6();
	void ClickIo7();
	void ClickIo8();
	void ClickIo9();
	void ClickIoA();
	void ClickIoB();
	void ClickIoC();
	void ClickIoD();
	void ClickIoE();
	void ClickIoF();
	void ClickIo10();
	void ClickIo11();
	void ClickIo12();
	void ClickIo13();
	void ClickIo14();
	void ClickIo15();
	void ClickIo16();
	void ClickIo17();
	void ClickIo18();
	void ClickIo19();
	void ClickIo1A();
	void ClickIo1B();
	void ClickIo1C();
	void ClickIo1D();
	void ClickIo1E();
	void ClickIo1F();

	void ClickNext();
	void ClickPrevious();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ScanInOut();
};
