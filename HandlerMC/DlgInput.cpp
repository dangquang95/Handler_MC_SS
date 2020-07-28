// DlgInput.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "DlgInput.h"
#include "afxdialogex.h"


// DlgInput dialog

IMPLEMENT_DYNAMIC(DlgInput, CDialogEx)

DlgInput::DlgInput(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_INPUT, pParent)
{

}

DlgInput::~DlgInput()
{
}

void DlgInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 32; i++)
	{
		DDX_Control(pDX, IDB_IO_0 + i, m_InOut[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		DDX_Control(pDX, IDC_IO_TITLE0 + i, m_Title[i]);
	}

}


BEGIN_MESSAGE_MAP(DlgInput, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// DlgInput message handlers
BEGIN_EVENTSINK_MAP(DlgInput, CDialogEx)
	ON_EVENT(DlgInput, IDB_EXIT1, DISPID_CLICK, DlgInput::ClickExit1, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_0, DISPID_CLICK,  DlgInput::ClickIo0, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_1, DISPID_CLICK,  DlgInput::ClickIo1, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_2, DISPID_CLICK,  DlgInput::ClickIo2, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_3, DISPID_CLICK,  DlgInput::ClickIo3, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_4, DISPID_CLICK,  DlgInput::ClickIo4, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_5, DISPID_CLICK,  DlgInput::ClickIo5, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_6, DISPID_CLICK,  DlgInput::ClickIo6, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_7, DISPID_CLICK,  DlgInput::ClickIo7, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_8, DISPID_CLICK,  DlgInput::ClickIo8, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_9, DISPID_CLICK,  DlgInput::ClickIo9, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_A, DISPID_CLICK,  DlgInput::ClickIoA, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_B, DISPID_CLICK,  DlgInput::ClickIoB, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_C, DISPID_CLICK,  DlgInput::ClickIoC, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_D, DISPID_CLICK,  DlgInput::ClickIoD, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_E, DISPID_CLICK,  DlgInput::ClickIoE, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_F, DISPID_CLICK,  DlgInput::ClickIoF, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_10, DISPID_CLICK, DlgInput::ClickIo10, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_11, DISPID_CLICK, DlgInput::ClickIo11, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_12, DISPID_CLICK, DlgInput::ClickIo12, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_13, DISPID_CLICK, DlgInput::ClickIo13, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_14, DISPID_CLICK, DlgInput::ClickIo14, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_15, DISPID_CLICK, DlgInput::ClickIo15, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_16, DISPID_CLICK, DlgInput::ClickIo16, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_17, DISPID_CLICK, DlgInput::ClickIo17, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_18, DISPID_CLICK, DlgInput::ClickIo18, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_19, DISPID_CLICK, DlgInput::ClickIo19, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_1A, DISPID_CLICK, DlgInput::ClickIo1A, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_1B, DISPID_CLICK, DlgInput::ClickIo1B, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_1C, DISPID_CLICK, DlgInput::ClickIo1C, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_1D, DISPID_CLICK, DlgInput::ClickIo1D, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_1E, DISPID_CLICK, DlgInput::ClickIo1E, VTS_NONE)
	ON_EVENT(DlgInput, IDB_IO_1F, DISPID_CLICK, DlgInput::ClickIo1F, VTS_NONE)
	ON_EVENT(DlgInput, IDB_NEXT, DISPID_CLICK, DlgInput::ClickNext, VTS_NONE)
	ON_EVENT(DlgInput, IDB_PREVIOUS, DISPID_CLICK, DlgInput::ClickPrevious, VTS_NONE)
END_EVENTSINK_MAP()


void DlgInput::ClickExit1()
{
	KillTimer(1);
	CDialog::OnCancel();
}

void DlgInput::SetNameCaption()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();
	CString  m_title;
	
	for (int i = 0; i < 32; i++)
	{
		if (pDoc->FlagInOut)
		{
			m_InOut[i].SetCaption(m_NameInput.at(i + IndexNext*32));
		}
		else
		{
			m_InOut[i].SetCaption(m_Nameoutput.at(i + IndexNext * 32));
		}	
	}
	if (pDoc->FlagInOut)
	{
		for (int i = 0; i < 4; i++)
		{
			m_title.Format("X00%d-X00%d", i*8, i*8 + 7);
			m_Title[i].SetCaption(m_title);
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			m_title.Format("Y00%d-Y00%d", i*8, i*8 + 7);
			m_Title[i].SetCaption(m_title);
		}
	}
}

BOOL DlgInput::OnInitDialog()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CDialogEx::OnInitDialog();

	if (pDoc->FlagInOut)
	{
		SetWindowText("Input");
	}
	else
	{
		SetWindowText("OutPut");
	}

	IndexNext = 0;
	ReadNameInput();
	ReadNameOutput();
	SetNameCaption();

	SetTimer(1, 50, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgInput::ReadNameInput()
{
	int TotalInput;
	CString m_name,m_input;
	CIniFile Total, NameInput;

	CString path = "DataSystem\\Input.dat";
	m_NameInput.clear();

	Total.SetPath(path);// đường dẫn file. Nhớ phải dung 2 sẹc (\\).
	TotalInput = Total.ReadInt("Data", "Total", 0);

	for (int i = 0 ; i < TotalInput; i++)
	{
		m_input.Format("Input%d", i);
		m_name = Total.ReadString("Data", m_input, "NoName");
		m_NameInput.push_back(m_name);
	}

}

void DlgInput::ReadNameOutput()
{
	int TotalOutput;
	CString m_name, m_output;
	CIniFile Total, NameOutput;

	CString path = "DataSystem\\Output.dat";
	m_Nameoutput.clear();

	Total.SetPath(path);// đường dẫn file. Nhớ phải dung 2 sẹc (\\).
	TotalOutput = Total.ReadInt("Data", "Total", 0);

	for (int i = 0 ; i < TotalOutput; i++)
	{
		m_output.Format("Output%d", i);
		m_name = Total.ReadString("Data", m_output, "NoName");
		m_Nameoutput.push_back(m_name);
	}

}
void DlgInput::ActionOutput(int output)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	CString m_output;
	if (!pDoc->FlagInOut)
	{
		if (pDoc->ReadOutput(output))
		{
			pDoc->ResetOutput(output);
		}
		else
		{
			pDoc->SetOutput(output);
		}
	}
}

void DlgInput::ClickIo0() { ActionOutput(0 + IndexNext*32); }
void DlgInput::ClickIo1() { ActionOutput(1 + IndexNext*32); }
void DlgInput::ClickIo2() { ActionOutput(2 + IndexNext*32); }
void DlgInput::ClickIo3() { ActionOutput(3 + IndexNext*32); }
void DlgInput::ClickIo4() { ActionOutput(4 + IndexNext*32); }
void DlgInput::ClickIo5() { ActionOutput(5 + IndexNext*32); }
void DlgInput::ClickIo6() { ActionOutput(6 + IndexNext*32); }
void DlgInput::ClickIo7() { ActionOutput(7 + IndexNext*32); }
void DlgInput::ClickIo8() { ActionOutput(8 + IndexNext*32); }
void DlgInput::ClickIo9() { ActionOutput(9 + IndexNext*32); }
void DlgInput::ClickIoA() { ActionOutput(10 + IndexNext*32); }
void DlgInput::ClickIoB() { ActionOutput(11 + IndexNext*32); }
void DlgInput::ClickIoC() { ActionOutput(12 + IndexNext*32); }
void DlgInput::ClickIoD() { ActionOutput(13 + IndexNext*32); }
void DlgInput::ClickIoE() { ActionOutput(14 + IndexNext*32); }
void DlgInput::ClickIoF() { ActionOutput(15 + IndexNext*32); }
void DlgInput::ClickIo10() { ActionOutput(16 + IndexNext*32); }
void DlgInput::ClickIo11() { ActionOutput(17 + IndexNext*32); }
void DlgInput::ClickIo12() { ActionOutput(18 + IndexNext*32); }
void DlgInput::ClickIo13() { ActionOutput(19 + IndexNext*32); }
void DlgInput::ClickIo14() { ActionOutput(20 + IndexNext*32); }
void DlgInput::ClickIo15() { ActionOutput(21 + IndexNext*32); }
void DlgInput::ClickIo16() { ActionOutput(22 + IndexNext*32); }
void DlgInput::ClickIo17() { ActionOutput(23 + IndexNext*32); }
void DlgInput::ClickIo18() { ActionOutput(24 + IndexNext*32); }
void DlgInput::ClickIo19() { ActionOutput(25 + IndexNext*32); }
void DlgInput::ClickIo1A() { ActionOutput(26 + IndexNext*32); }
void DlgInput::ClickIo1B() { ActionOutput(27 + IndexNext*32); }
void DlgInput::ClickIo1C() { ActionOutput(28 + IndexNext*32); }
void DlgInput::ClickIo1D() { ActionOutput(29 + IndexNext*32); }
void DlgInput::ClickIo1E() { ActionOutput(30 + IndexNext*32); }
void DlgInput::ClickIo1F() { ActionOutput(31 + IndexNext*32); }



void DlgInput::ClickNext()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	IndexNext = 1;
	SetNameCaption();
}


void DlgInput::ClickPrevious()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	IndexNext = 0;
	SetNameCaption();

}


void DlgInput::OnTimer(UINT_PTR nIDEvent)
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	switch (nIDEvent)
	{
	case 1:
		ScanInOut();
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void DlgInput::ScanInOut()
{
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	if (pDoc->FlagInOut)
	{
		switch (IndexNext)//Input
		{
		case 0://0-31
			for (int i = 0; i < 32; i++)
			{
				if (pDoc->ReadInput(i))
				{
					m_InOut[i].SetPicture("C:\\Anh Icon InOut\\On.ico");
				}
				else
				{
					m_InOut[i].SetPicture("C:\\Anh Icon InOut\\Off.ico");
				}
			}		
			break;
		case 1://32-63
			for (int i = 0; i < 32; i++)
			{
				if (pDoc->ReadInput(i+32))
				{
					m_InOut[i].SetPicture("C:\\Anh Icon InOut\\On.ico");
				}
				else
				{
					m_InOut[i].SetPicture("C:\\Anh Icon InOut\\Off.ico");
				}
			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch (IndexNext)//Output
		{
		case 0://0-31
			for (int i = 0; i < 32; i++)
			{
				if (pDoc->ReadOutput(i))
				{
					m_InOut[i].SetPicture("C:\\Anh Icon InOut\\On.ico");
				}
				else
				{
					m_InOut[i].SetPicture("C:\\Anh Icon InOut\\Off.ico");
				}
			}
			break;
		case 1://32-63
			for (int i = 0; i < 32; i++)
			{
				if (pDoc->ReadOutput(i + 32))
				{
					m_InOut[i].SetPicture("C:\\Anh Icon InOut\\On.ico");
				}
				else
				{
					m_InOut[i].SetPicture("C:\\Anh Icon InOut\\Off.ico");
				}
			}
			break;
		default:
			break;
		}
	}

}