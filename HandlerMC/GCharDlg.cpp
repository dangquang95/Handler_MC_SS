// GCharDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HandlerMC.h"
#include "GCharDlg.h"
#include "afxdialogex.h"

#include "HandlerMCDoc.h"
// GCharDlg dialog

IMPLEMENT_DYNAMIC(GCharDlg, CDialogEx)

GCharDlg::GCharDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GET_CHAR, pParent)
{

}

GCharDlg::~GCharDlg()
{
}

void GCharDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_DISP_CHAR, m_sDispValue);
	DDX_Control(pDX, IDB_KEY_DOT, m_bDot);
	DDX_Control(pDX, IDB_KEY_EQUAL, m_bEqual);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GCharDlg, CDialogEx)
END_MESSAGE_MAP()


// GCharDlg message handlers


void GCharDlg::BtnDisable()
{
	// TODO: Add your control notification handler code here
	m_bDot.EnableWindow(FALSE);
	m_bColon.EnableWindow(FALSE);
	m_bWon.EnableWindow(FALSE);
	m_bEqual.EnableWindow(FALSE);
}

void GCharDlg::OnKeyOk()
{
	// TODO: Add your control notification handler code here
	CMainFrame * pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	CHandlerMCDoc * pDoc = (CHandlerMCDoc *)pFrm->GetActiveDocument();

	Chara = m_strGetVal;
	pDoc->CharReturn = Chara;
	CDialog::OnOK();
}

void GCharDlg::OnKeyEsc()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void GCharDlg::OnKeyBack()
{
	// TODO: Add your control notification handler code here
	int len = m_strGetVal.GetLength();
	if (len)
	{
		m_strGetVal.SetAt(len - 1, ' ');
		m_strGetVal.TrimRight();
		UpdateDisplay();
	}
}

void GCharDlg::OnKeyClear()
{
	// TODO: Add your control notification handler code here
	m_strGetVal = "";
	UpdateDisplay();
}

void GCharDlg::OnKey1()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;

	m_strGetVal += "1";
	UpdateDisplay();
}
//void CGetCharDlg::ClickKey1()
//{
//	 TODO: Add your message handler code here
//}

void GCharDlg::OnKey2()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;

	m_strGetVal += "2";
	UpdateDisplay();
}

void GCharDlg::OnKey3()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;

	m_strGetVal += "3";
	UpdateDisplay();
}

void GCharDlg::OnKey4()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;

	m_strGetVal += "4";
	UpdateDisplay();
}

void GCharDlg::OnKey5()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;

	m_strGetVal += "5";
	UpdateDisplay();
}

void GCharDlg::OnKey6()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;

	m_strGetVal += "6";
	UpdateDisplay();
}

void GCharDlg::OnKey7()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;

	m_strGetVal += "7";
	UpdateDisplay();
}

void GCharDlg::OnKey8()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;

	m_strGetVal += "8";
	UpdateDisplay();
}

void GCharDlg::OnKey9()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;

	m_strGetVal += "9";
	UpdateDisplay();
}

void GCharDlg::OnKey0()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;

	m_strGetVal += "0";
	UpdateDisplay();
}

void GCharDlg::OnKeyQ()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "Q";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "q";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyW()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "W";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "w";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyE()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "E";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "e";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyR()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "R";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "r";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyT()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "T";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "t";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyY()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "Y";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "y";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyU()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "U";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "u";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyI()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "I";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "i";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyO()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "O";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "o";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyP()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "P";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "p";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyA()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "A";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "a";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyS()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "S";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "s";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyD()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "D";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "d";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyF()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "F";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "f";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyG()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "G";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "g";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyH()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "H";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "h";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyJ()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "J";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "j";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyK()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "K";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "k";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyL()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "L";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "l";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyZ()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "Z";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "z";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyX()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "X";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "x";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyC()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "C";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "c";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyV()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "V";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "v";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyB()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "B";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "b";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyN()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "N";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "n";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyM()
{
	// TODO: Add your control notification handler code here
	if (!VerifyMaxChar()) return;
	if (ShiftKey) {
		m_strGetVal += "M";
		ShiftKey = FALSE;
	}
	else {
		m_strGetVal += "m";
	}
	UpdateDisplay();
}

void GCharDlg::OnKeyEqual()
{
	// TODO: Add your control notification handler code here
	if (m_bpwd) return;

	if (!VerifyMaxChar()) return;

	m_strGetVal += "=";
	UpdateDisplay();
}

void GCharDlg::OnKeyShift()
{
	// TODO: Add your control notification handler code here
	ShiftKey = TRUE;
}

void GCharDlg::OnKeyColon()
{
	// TODO: Add your control notification handler code here
	if (m_bpwd) return;

	if (!VerifyMaxChar()) return;

	m_strGetVal += ":";
	UpdateDisplay();
}

void GCharDlg::OnKeyDot()
{
	// TODO: Add your control notification handler code here
	if (m_bpwd) return;

	if (!VerifyMaxChar()) return;

	m_strGetVal += ".";
	UpdateDisplay();
}

void GCharDlg::OnKeyDash()
{
	// TODO: Add your control notification handler code here
	if (m_bpwd) return;

	if (!VerifyMaxChar()) return;

	m_strGetVal += "-";
	UpdateDisplay();
}

void GCharDlg::OnKeyUnderBar()
{
	// TODO: Add your control notification handler code here
	if (m_bpwd) return;

	if (!VerifyMaxChar()) return;

	m_strGetVal += "_";
	UpdateDisplay();
}

void GCharDlg::UpdateDisplay(COLORREF bkcolor)
{
	/*    CClientDC dc (this);
	dc.DrawEdge(m_rect, EDGE_SUNKEN, BF_RECT);

	CFont* pOldFont = dc.SelectObject( GetFont() );
	CSize size = dc.GetTextExtent(m_strGetVal);

	CRect rect = m_rect;
	rect.InflateRect(-2, -2);
	//    int x = rect.right - size.cx - m_cxChar;		// Right Align
	int x = rect.left + 2;							// Left Align
	int y = rect.top + ((rect.Height() - m_cyChar) / 2);

	dc.SetBkColor(bkcolor);

	dc.ExtTextOut(x, y, ETO_OPAQUE, rect, m_strGetVal, NULL);
	dc.SelectObject(pOldFont);
	*/
	int len;//, i;
	CString bufstr;

	if (m_bpwd)
	{
		len = m_strGetVal.GetLength();
		if (len <= 0)
		{
			bufstr = "";
			m_sDispValue.SetCaption(bufstr);
			return;
		}
		//for(i=0;i<len;i++) bufstr += m_strGetVal; //"*";
		m_sDispValue.SetCaption(m_strGetVal);
	}
	else m_sDispValue.SetCaption(m_strGetVal);
	UpdateData(FALSE);
}

BOOL GCharDlg::VerifyMaxChar()
{
	if (m_strGetVal.GetLength() >= m_intMaxChar) return FALSE;
	else return TRUE;
}

void GCharDlg::InitStaticDispWnd()
{
	CStatic* pRect = (CStatic*)GetDlgItem(IDC_DISP_CHAR);
	pRect->GetWindowRect(&m_rect);
	pRect->DestroyWindow();
	ScreenToClient(&m_rect);

	TEXTMETRIC tm;
	CClientDC dc(this);
	dc.GetTextMetrics(&tm);
	m_cxChar = tm.tmAveCharWidth;
	m_cyChar = tm.tmHeight - tm.tmDescent;
}

CString GCharDlg::GetStringValue()
{
	return m_strGetVal;
}

BOOL GCharDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_intMaxChar = 20;
	m_strGetVal = "";


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
BEGIN_EVENTSINK_MAP(GCharDlg, CDialogEx)

	ON_EVENT(GCharDlg, IDB_KEY_ENTER, -600 /* Click */, OnKeyOk, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_ESC, -600 /* Click */, OnKeyEsc, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_BACK, -600 /* Click */, OnKeyBack, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_1, -600 /* Click */, OnKey1, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_2, -600 /* Click */, OnKey2, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_3, -600 /* Click */, OnKey3, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_4, -600 /* Click */, OnKey4, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_5, -600 /* Click */, OnKey5, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_6, -600 /* Click */, OnKey6, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_7, -600 /* Click */, OnKey7, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_8, -600 /* Click */, OnKey8, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_9, -600 /* Click */, OnKey9, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_0, -600 /* Click */, OnKey0, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_Q, -600 /* Click */, OnKeyQ, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_W, -600 /* Click */, OnKeyW, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_E, -600 /* Click */, OnKeyE, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_R, -600 /* Click */, OnKeyR, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_T, -600 /* Click */, OnKeyT, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_Y, -600 /* Click */, OnKeyY, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_U, -600 /* Click */, OnKeyU, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_I, -600 /* Click */, OnKeyI, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_O, -600 /* Click */, OnKeyO, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_P, -600 /* Click */, OnKeyP, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_A, -600 /* Click */, OnKeyA, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_S, -600 /* Click */, OnKeyS, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_D, -600 /* Click */, OnKeyD, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_F, -600 /* Click */, OnKeyF, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_G, -600 /* Click */, OnKeyG, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_H, -600 /* Click */, OnKeyH, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_J, -600 /* Click */, OnKeyJ, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_K, -600 /* Click */, OnKeyK, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_L, -600 /* Click */, OnKeyL, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_Z, -600 /* Click */, OnKeyZ, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_X, -600 /* Click */, OnKeyX, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_C, -600 /* Click */, OnKeyC, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_V, -600 /* Click */, OnKeyV, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_B, -600 /* Click */, OnKeyB, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_N, -600 /* Click */, OnKeyN, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_M, -600 /* Click */, OnKeyM, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_EQUAL, -600 /* Click */, OnKeyEqual, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_Shift, -600 /* Click */, OnKeyShift, VTS_NONE)
	ON_EVENT(GCharDlg, IDB_KEY_DOT, -600 /* Click */, OnKeyDot, VTS_NONE)
	
END_EVENTSINK_MAP()


