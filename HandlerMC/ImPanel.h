#pragma once

#include "ImScrollHelper.h"
#include "afxext.h"

namespace im
{

#define POPUP_MENU_ID	20000

#define IMCOLOR_FILLED	-1

#define MAX_OBJECT		256

#define IMCOORD_SCREEN	1
#define IMCOORD_IMG		2

#define IMTEXT_C		0
#define IMTEXT_TL		1
#define IMTEXT_TR		2
#define IMTEXT_BR		3
#define IMTEXT_BL		4

#define FIT_NONE		0
#define FIT_X			1
#define FIT_Y			2
#define FIT_XY			3
#define FIT_STRETCH		4

#define MAX_ITEM 4

class CImRect
{
public:
	CImRect(){m_bValid=FALSE;}
	~CImRect(){};

	CRect m_Rect;
	COLORREF m_Color;
	int m_iLineWidth;
	int m_iCoord;
	BOOL m_bValid;
};

class CImCircle
{
public:
	CImCircle(){m_bValid=FALSE;}
	~CImCircle(){};

	CPoint m_Center;
	int m_iRadius;
	COLORREF m_Color;
	int m_iLineWidth;
	int m_iCoord;
	BOOL m_bValid;
};

class CImText
{
public:
	CImText(){m_bValid=FALSE;}
	~CImText(){};

	CPoint m_Pt;
	CString m_sText;
	COLORREF m_Color;
	int m_iHeight;
	int m_iAlign;
	int m_iCoord;
	CString m_sFont;
	BOOL m_bValid;
};

// CImPanel
class CImPanel : public CWnd
{
	DECLARE_DYNAMIC(CImPanel)

public:
	CImPanel();
	virtual ~CImPanel();

public:

	typedef struct ImROI
	{
		BOOL bUse;
		CRect rect;
		COLORREF rectColor;
		COLORREF centerLineColor;
		int iSizeStep;
		BOOL bFixedSize;
		BOOL bFixedPos;
	};

	typedef struct ImPoint
	{
		BOOL bUse;
		CPoint pt;
		int iSize;
		COLORREF circleColor;
		COLORREF centerLineColor;
		int iSizeStep;
		BOOL bFixedSize;
		BOOL bFixedPos;
	};

	typedef struct ImCross
	{
		BOOL bUse;
		CPoint pt;
		CSize size;
		COLORREF rectColor;
		COLORREF centerLineColor;
		int iSizeStep;
		BOOL bFixedSize;
		BOOL bFixedPos;
	};

	ImROI m_ROI[MAX_ITEM];
	ImPoint m_Point[MAX_ITEM];
	ImCross m_Cross[MAX_ITEM];

	CPoint m_ptCursorPosImgPx;

	CString m_sCursorText;
	BOOL m_bDisplayCursor;

	void SetTracker(CImPanel * pTrack);

	void SetStretchToScreen(BOOL bSet=TRUE);
	void SetFitToScreen();
	void SetFitXToScreen();
	void SetFitYToScreen();
	void SetUseRectTracker(BOOL bUse);

	void SetCenterLine(BOOL bSet=TRUE);
	void SetDisplayCursor(BOOL bSet, CString sText=_T(""));

	void SetImage(unsigned char* pImageData, int iDataSize, int iWidth, int iHeight, int iChannel, BOOL bDisplayUpdate = FALSE);

	void PutRect(int iNo, int iCoord, CRect rect, COLORREF color, int iLineWidth);
	void PutCircle(int iNo, int iCoord,  CPoint center, int iRadius, COLORREF color, int iLineWidth);
	void PutText(int iNo, int iCoord, CPoint pt, CString sText, int iHeight, COLORREF color, int iAlign, CString sFont=_T("Lucida Console"));

	void UpdateDisplay();
	void UpdateTracker();

	CPoint ScreenPosToImagePos(CPoint ptScreen);
	CPoint ImagePosToScreenPos(CPoint ptImage);

	void ChangeZoomFactor(double dRatio);

	void CheckCrossCenter(int idx);
	void CheckRoiCenter(int idx, int iRoiWidth, int iRoiHeight);

	int	m_iWidth;
	int m_iHeight;

protected:
	int m_iFitToScreen;
	BOOL m_bCenterLine;

	CImPanel * m_pTrackPanel;

	
	int m_iChannel;
	unsigned char* m_pImageData;

	CRect m_rVirtual;
	CRect m_rScreen;
	double m_dZoomFactor;
	BOOL m_bZoomChanged;
	CImScrollHelper m_ScrollHelper;
	BOOL m_bUseRectTracker;

	CSize m_ViewSize;
	CPoint m_ptViewOrg;

	CPoint m_ptROIStart;
	CPoint m_ptROIEnd;

	CImRect m_Rect[MAX_OBJECT];
	CImCircle m_Circle[MAX_OBJECT];
	CImText m_Text[MAX_OBJECT];

	void FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp);
	void PrepDC(CDC * pDC, const CRect & rVirt, const CRect & rScreen);
	void AdjustScrollbars();
	void AdjustZoomFactor();

	void DrawImage(CDC * pDC);
	void DrawZoomRect(CDC * pDC);
	void DrawRect(CDC * pDC);
	void DrawCircle(CDC * pDC);
	void DrawText(CDC * pDC);
	void DrawROI(CDC * pDC);
	void DrawCenterLine(CDC * pDC);

	void DrawPoint(CDC * pDC);
	void DrawCross(CDC * pDC);

	// hcpak ¸ðµ¨ µî·Ï¿ë rect tracker
	CRectTracker m_tracker;


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditZoomIn();

	void SetROIEnable(bool bSet);
	bool m_bROIEnble;

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	void SetRectTrackerScreen(CRect modelRect);
	CRect GetRectTrackerScreen(void);
	CRect GetviewSize(void);
	void SetRectTrackerImage(CRect modelrect);
	CRect GetRectTrackerImage(void);
};

};


