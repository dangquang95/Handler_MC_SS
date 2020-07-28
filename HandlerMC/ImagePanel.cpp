// ImagePanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImagePanel.h"
#include "MainFrm.h"

#define RED				RGB(255,0,0)
#define GREEN			RGB(0,255,0) 
#define BLUE			RGB(0,0,255)
#define YELLOW			RGB(255,255,0)
#define ORANGE			RGB(255,153,51)
#define HOT_PINK		RGB(255,51,153)
#define PURPLE			RGB(153,0,204)
#define CYAN			RGB(0,255,255)
#define BLACK			RGB(0,0,0)
#define WHITE			RGB(255,255,255)
#define LAVENDER		RGB(199,177,255)
#define PEACH			RGB(255,226,177)
#define SKY_BLUE		RGB(142,255,255)
#define FOREST_GREEN	RGB(0,192,0)
#define BROWN			RGB(80,50,0)
#define TURQUOISE		RGB(0,192,192)
#define ROYAL_BLUE		RGB(0,0,192)
#define GREY			RGB(192,192,192)
#define DARK_GREY		RGB(128,128,128)
#define TAN				RGB(255,198,107)
#define DARK_BLUE		RGB(0,0,128)
#define MAROON			RGB(128,0,0)
#define DUSK			RGB(255,143,107)
#define LIGHT_GREY		RGB(225,225,225)

// CImagePanel

IMPLEMENT_DYNAMIC(CImagePanel, CStatic)

CImagePanel::CImagePanel()
{
	m_iWidth = 5472;
	m_iHeight = 3648;
	m_iChannel = 1;
	m_pImageData = NULL;

	m_bShowCaption = FALSE;
	m_bShowROI = FALSE;

	m_CaptionColor = RGB(0, 255, 0);

	for (int i = 0; i < 32; i++)
	{
		m_ROIRect[i] = CRect(0, 0, 0, 0);
	}

	m_iPixelValue[0] = 0;
	m_iPixelValue[1] = 0;
	m_iPixelValue[2] = 0;

	CRect rect(10, 10, 100, 100);

	m_tracker.m_rect = rect;

	m_tracker.m_nStyle = 0;
	m_tracker.m_nStyle |= CRectTracker::dottedLine;
	m_tracker.m_nStyle |= CRectTracker::resizeOutside;

	m_dZoomFactor = 1.0;

	m_bUseRectTracker = FALSE;
}

CImagePanel::~CImagePanel()
{
	if (m_pImageData)
	{
		delete m_pImageData;
	}
}

BEGIN_MESSAGE_MAP(CImagePanel, CStatic)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CImagePanel::UpdateDisplay()
{
	Invalidate(FALSE);
}

void CImagePanel::SetImage(char* pImageData, int iWidth, int iHeight, int iChannel, BOOL bDisplayUpdate)
{
	if (NULL == pImageData)
	{
		return;
	}

	int iImageSize = iWidth*iHeight*iChannel;

	m_DisplayRect = CRect(0, 0, iWidth, iHeight);

	// 필요시 버퍼 재 할당
	if (NULL == m_pImageData)
	{
		m_pImageData = new char[iImageSize];
	}
	else
	{
		if (m_iWidth != iWidth || m_iHeight != iHeight || m_iChannel != iChannel)
		{
			delete[] m_pImageData;
			m_pImageData = new char[iImageSize];
		}
	}

	// 각 Image Parameter Update
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_iChannel = iChannel;

	// 이미지 Data Update
	memcpy(m_pImageData, pImageData, iImageSize*sizeof(char));

	if (bDisplayUpdate)
	{
		Invalidate(FALSE);
	}
}

void CImagePanel::SetCaption(int iIndex, CString strText)
{
	if (iIndex < 0 || iIndex > 6)
	{
		return;
	}

	int iSize = (int)m_strTextArray.GetSize();

	if (iIndex >= iSize)
	{
		m_strTextArray.Add(strText);
	}
	else
	{
		m_strTextArray.SetAt(iIndex, strText);
	}
}

void CImagePanel::DeleteAllCaptions()
{
	m_strTextArray.RemoveAll();
}

void CImagePanel::SetCaptionShow(BOOL bShow)
{
	m_bShowCaption = bShow;
}

void CImagePanel::SetROIShow(BOOL bShow)
{
	m_bShowROI = bShow;
}

void CImagePanel::SetCaptionColor(int iRed, int iGreen, int iBlue)
{
	if (iRed < 0 || iRed > 255 || iGreen < 0 || iGreen > 255 || iBlue < 0 || iBlue > 255)
	{
		return;
	}

	m_CaptionColor = RGB(iRed, iGreen, iBlue);
}

void CImagePanel::SetROI(int iROINo, CRect rect)
{
	if (iROINo < 0 || iROINo > 31)
	{
		return;
	}

	m_ROIRect[iROINo] = rect;
}

void CImagePanel::DrawImage(CDC* pDC)
{
	if (m_pImageData == NULL)
	{
		return;
	}

	if (m_iWidth <= 0 || m_iHeight <= 0)
	{
		return;
	}

	CRect rect;
	GetClientRect(rect);

	// 그릴 영역의 크기를 구하고
	int cx = rect.Width();
	int cy = rect.Height();

	CDC memDC;
	CBitmap bitmap;

	memDC.CreateCompatibleDC(pDC);
	bitmap.CreateCompatibleBitmap(pDC, m_iWidth, m_iHeight);
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	unsigned char buffer[sizeof(BITMAPINFOHEADER)+1024];
	BITMAPINFO* bmi = (BITMAPINFO*)buffer;
	int bmp_w = m_iWidth;
	int bmp_h = m_iHeight;

	FillBitmapInfo(bmi, bmp_w, bmp_h, m_iChannel * 8);

	int res = SetDIBitsToDevice(
		memDC.m_hDC,
		0,
		0,
		bmp_w,
		bmp_h,
		0,
		0,
		0,
		bmp_h,	
		m_pImageData,
		(BITMAPINFO*)bmi,
		DIB_RGB_COLORS);

	pDC->SetStretchBltMode(COLORONCOLOR);

	int iROIW = m_DisplayRect.Width();
	int iROIH = m_DisplayRect.Height();

	double dRatioX = ((double)iROIW) / ((double)cx);
	double dRatioY = ((double)iROIH) / ((double)cy);

	int iWidth = cx;
	int iHeight = cy;
	int iStartX = 0;
	int iStartY = 0;

	if (dRatioX > dRatioY)	// 가로로 꽉차게 그린다.
	{
		iHeight = (int)(cx * iROIH / iROIW);
		iStartY = (cy - iHeight) / 2;
	}
	else   // 세로로 꽉차게 그린다.
	{
		iWidth = (int)(cy * iROIW / iROIH);
		iStartX = (cx - iWidth) / 2;
	}

	m_PanelRect.left = iStartX;
	m_PanelRect.right = iStartX + iWidth;
	m_PanelRect.top = iStartY;
	m_PanelRect.bottom = iStartY + iHeight;

	pDC->StretchBlt(iStartX, iStartY, iWidth, iHeight, &memDC, m_DisplayRect.left, m_DisplayRect.top, iROIW, iROIH, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
}

void CImagePanel::FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp)
{
	BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);

	memset(bmih, 0, sizeof(*bmih));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = width;
	bmih->biHeight = -abs(height);
	bmih->biPlanes = 1;
	bmih->biBitCount = bpp;
	bmih->biCompression = BI_RGB;

	if (bpp == 8)
	{
		RGBQUAD* palette = bmi->bmiColors;
		int i;
		for (i = 0; i < 256; i++)
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}
}

// CImagePanel 메시지 처리기입니다.
void CImagePanel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CStatic::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(rect);

	CDC MemDC;
	CBitmap BitMap;
	CBitmap *pOldBitMap;

	MemDC.CreateCompatibleDC(&dc);
	BitMap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitMap = MemDC.SelectObject(&BitMap);

	// 이미지를 바탕에 그린다.
	DrawImage(&MemDC);
	DrawZoomRect(&MemDC);
	if (m_bShowROI)
	{
		DrawROIArea(&MemDC);
	}

	// 글자 찍기
	DisplayCaption(&MemDC);

	// Memory DC를 실제 화면에 그린다.
	dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBitMap);
	MemDC.DeleteDC();
	
	// Rect Tracker
	//UpdateTracker();
	if (m_bUseRectTracker)
	{
		if ((m_tracker.m_rect.Width() > 2) && (m_tracker.m_rect.Height() > 2))
		{
			m_tracker.Draw(&dc);
		}
	}
	m_ScrollHelper.UpdateScrollInfo();
}

void CImagePanel::DisplayCaption(CDC* pDC)
{
	int iSize = (int)m_strTextArray.GetSize();

	if (iSize <= 0)
	{
		return;
	}

	for (int i = 0; i < iSize; i++)
	{
		CPoint tmpPoint = CPoint(10, i * 15);
		DisplayText(pDC, tmpPoint, m_strTextArray.GetAt(i), m_CaptionColor);
	}
}

void CImagePanel::DisplayText(CDC* pDC, CPoint ptTextPosition, CString strText, COLORREF TextColor)
{
	if (strText.IsEmpty())
	{
		return;
	}

	CRect rTmp(0, 0, 0, 0);
	CRect rText(0, 0, 0, 0);
	CFont fontText;

	rText.top = ptTextPosition.y;
	rText.bottom = ptTextPosition.y + 20;

	rText.left = ptTextPosition.x - 5;
	rText.right = rText.left + strText.GetLength() * 20;

	////////////////////////////////////////////////////////////////////
	LOGFONT LogFont;

	memset(&LogFont, 0, sizeof(LogFont));

	LogFont.lfHeight = 10;
	LogFont.lfWidth = 0;
	LogFont.lfEscapement = FALSE;
	LogFont.lfOrientation = 0;
	LogFont.lfWeight = FW_NORMAL;
	LogFont.lfItalic = FALSE;
	LogFont.lfUnderline = FALSE;
	LogFont.lfStrikeOut = FALSE;
	LogFont.lfCharSet = DEFAULT_CHARSET;
	LogFont.lfOutPrecision = OUT_CHARACTER_PRECIS;
	LogFont.lfClipPrecision = CLIP_CHARACTER_PRECIS;
	LogFont.lfQuality = DEFAULT_QUALITY;
	LogFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	//	_tcscpy(LogFont.lfFaceName, /*_countof(_T("System")),*/ _T("System"));
	_tcscpy_s(LogFont.lfFaceName, _countof(_T("System")), _T("System"));
	fontText.CreateFontIndirect(&LogFont);
	/////////////////////////////////////////////////////////////////////

	CFont* pOldFont = pDC->SelectObject(&fontText);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(TextColor);
	pDC->DrawText(strText, -1, &rText, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	pDC->SelectObject(pOldFont);
}

void CImagePanel::DrawROIArea(CDC* pDC)
{
	if (m_PanelRect.IsRectEmpty())	return;

	// 투명 Brush 설정
	CBrush *pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	CPen tmpPen;
	CPen *pOldPen;
	tmpPen.CreatePen(PS_SOLID, 2, YELLOW);
	pOldPen = pDC->SelectObject(&tmpPen);

	CRect rect;
	GetClientRect(rect);

	int iWidth = m_PanelRect.Width();
	int iHeight = m_PanelRect.Height();

	int iROIW = m_DisplayRect.Width();
	int iROIH = m_DisplayRect.Height();

	// control 크기에 맞춰 Rectangle 크기 조정
	double dScaleX = ((double)iWidth) / ((double)iROIW);
	double dScaleY = ((double)iHeight) / ((double)iROIH);

	CPoint pTemp;

	for (int i = 0; i < 31; i++)
	{
		if (m_ROIRect[i].IsRectEmpty()) continue;

		int iXOffset = m_DisplayRect.left;
		int iYOffset = m_DisplayRect.top;

		pTemp.x = (int)((m_ROIRect[i].left - iXOffset) * dScaleX) + m_PanelRect.left;
		pTemp.y = (int)((m_ROIRect[i].top - iYOffset) * dScaleY) + m_PanelRect.top;
		pDC->MoveTo(pTemp);

		pTemp.x = (int)((m_ROIRect[i].right - iXOffset) * dScaleX) + m_PanelRect.left;
		pTemp.y = (int)((m_ROIRect[i].top - iYOffset) * dScaleY) + m_PanelRect.top;
		pDC->LineTo(pTemp);

		pTemp.x = (int)((m_ROIRect[i].right - iXOffset) * dScaleX) + m_PanelRect.left;
		pTemp.y = (int)((m_ROIRect[i].bottom - iYOffset) * dScaleY) + m_PanelRect.top;
		pDC->LineTo(pTemp);

		pTemp.x = (int)((m_ROIRect[i].left - iXOffset) * dScaleX) + m_PanelRect.left;
		pTemp.y = (int)((m_ROIRect[i].bottom - iYOffset) * dScaleY) + m_PanelRect.top;
		pDC->LineTo(pTemp);

		pTemp.x = (int)((m_ROIRect[i].left - iXOffset) * dScaleX) + m_PanelRect.left;
		pTemp.y = (int)((m_ROIRect[i].top - iYOffset) * dScaleY) + m_PanelRect.top;
		pDC->LineTo(pTemp);

		CString strROINo;
		pTemp.Offset(-5, 0);
		strROINo.Format(_T("%d"), i + 1);
		DisplayText(pDC, pTemp, strROINo, YELLOW);
	}

	// put back the old objects
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}


void CImagePanel::DrawZoomRect(CDC * pDC)
{
	CSize ptViewSize = pDC->GetViewportExt();
	CPoint ptViewOrg = pDC->GetViewportOrg();

	int iSave = pDC->SaveDC();

	double dViewRatioX = (double)m_iWidth / (double)ptViewSize.cx;
	double dViewRatioY = (double)m_iHeight / (double)ptViewSize.cy;

	CPoint ptOffStart = CPoint((int)(m_ptROIStart.x*dViewRatioX), (int)(m_ptROIStart.y*dViewRatioY));
	CPoint ptOffEnd = CPoint((int)(m_ptROIEnd.x*dViewRatioX), (int)(m_ptROIEnd.y*dViewRatioY));

	CRect roi(ptOffStart, ptOffEnd);

	pDC->SetROP2(R2_NOTXORPEN);
	pDC->Rectangle(&roi);

	pDC->RestoreDC(iSave);
}

void CImagePanel::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_pImageData != NULL)
	{
		if (nFlags == MK_SHIFT + MK_LBUTTON)
		{
			if (GetCapture() == this)
			{
				m_ptROIEnd = point;

				UpdateDisplay();
			}
		}

		if (nFlags == MK_LBUTTON)
		{
			CRect clientRect;
			GetClientRect(clientRect);

			double dRatio = 0.2 * (double)(m_DisplayRect.Width()) / (double)(clientRect.Width());
			CPoint ptMove = CPoint((int)(dRatio*(m_ptOld.x - point.x)), (int)(dRatio*(m_ptOld.y - point.y)));

			if (m_DisplayRect.Width() < m_iWidth || m_DisplayRect.Height() < m_iHeight)
			{
				CRect tmpRect = m_DisplayRect;
				tmpRect.OffsetRect(ptMove);

				if (tmpRect.left < 0)
				{
					tmpRect.left = 0;
					tmpRect.right = m_DisplayRect.Width();
				}

				if (tmpRect.right > m_iWidth)
				{
					tmpRect.left = m_iWidth - m_DisplayRect.Width();
					tmpRect.right = m_iWidth;
				}

				if (tmpRect.top < 0)
				{
					tmpRect.top = 0;
					tmpRect.bottom = m_DisplayRect.Height();
				}

				if (tmpRect.bottom > m_iHeight)
				{
					tmpRect.top = m_iHeight - m_DisplayRect.Height();
					tmpRect.bottom = m_iHeight;
				}

				m_DisplayRect = tmpRect;
			}
			CString strText;
			strText.Format(_T("ROI (%d, %d, %d, %d)"), m_DisplayRect.left, m_DisplayRect.top, m_DisplayRect.right, m_DisplayRect.bottom);
			SetCaption(1, strText);
			Invalidate(FALSE);

		}
		else
		{
			unsigned char ucPix[3] = { 0, 0, 0 };

			CRect tmpRect;
			GetClientRect(tmpRect);

			int cx = tmpRect.Width();
			int cy = tmpRect.Height();

			int iIndex = 0;
			int iXPos = -1;
			int iYPos = -1;

			int iDisplayW = m_DisplayRect.Width();
			int iDisplayH = m_DisplayRect.Height();

			int iLeft = m_DisplayRect.left;
			int iTop = m_DisplayRect.top;

			double dRatioX = ((double)iDisplayW) / ((double)cx);
			double dRatioY = ((double)iDisplayH) / ((double)cy);

			if (dRatioX > dRatioY)	// 가로로 꽉차게 그린다.
			{
				int iHeight = (int)(cx * iDisplayH / iDisplayW);
				int iStartY = (cy - iHeight) / 2;
				int iEndY = iStartY + iHeight - 1;

				if (point.y >= iStartY && point.y <= iEndY)
				{
					iXPos = iLeft + (iDisplayW * point.x) / cx;
					iYPos = iTop + (iDisplayH * (point.y - iStartY)) / iHeight;
				}
			}
			else   // 세로로 꽉차게 그린다.
			{
				int iWidth = (int)(cy * iDisplayW / iDisplayH);
				int iStartX = (cx - iWidth) / 2;
				int iEndX = iStartX + iWidth - 1;

				if (point.x >= iStartX && point.x <= iEndX)
				{
					iXPos = iLeft + (iDisplayW * (point.x - iStartX)) / iWidth;
					iYPos = iTop + (iDisplayH * point.y) / cy;
				}
			}

			if (iXPos >= 0 && iYPos >= 0 && iXPos < m_iWidth && iYPos < m_iHeight)
			{
				iIndex = iXPos + (m_iWidth * iYPos);

				if (m_iChannel == 3)
				{
					ucPix[0] = *(m_pImageData + (iIndex * 3));
					ucPix[1] = *(m_pImageData + (iIndex * 3 + 1));
					ucPix[2] = *(m_pImageData + (iIndex * 3 + 2));
				}
				else
				{
					ucPix[0] = m_pImageData[iIndex];
					ucPix[1] = m_pImageData[iIndex];
					ucPix[2] = m_pImageData[iIndex];
				}

				CString strText;
				strText.Format(_T("(%d, %d) R:%d G:%d B:%d"), iXPos, iYPos, ucPix[2], ucPix[1], ucPix[0]);
				SetCaption(0, strText);

				Invalidate(FALSE);
			}
			SetFocus();
		}
	}
	CStatic::OnMouseMove(nFlags, point);
}


BOOL CImagePanel::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect tmpRect;
	GetClientRect(tmpRect);
	CPoint tmpPoint = pt;
	ScreenToClient(&tmpPoint);

	//if (nFlags != MK_CONTROL) return FALSE;
	if (tmpRect.PtInRect(tmpPoint))
	{
		double dPanelRatio = (double)tmpRect.Height() / (double)tmpRect.Width();
		double dImageRatio = (double)m_iHeight / (double)m_iWidth;

		CRect tmpRect = m_DisplayRect;

		int iOffsetX = (int)(m_DisplayRect.Width() * 0.1);
		int iOffsetY = (int)(m_DisplayRect.Height() * 0.1);

		if (zDelta >= 120)
		{
			if (m_DisplayRect.Width() > 10 && m_DisplayRect.Height() > 10)//64
			{
				tmpRect.DeflateRect(iOffsetX, iOffsetY);
				tmpRect.NormalizeRect();
			}
		}
		else
		{
			if (m_DisplayRect.Width() < m_iWidth || m_DisplayRect.Height() < m_iHeight)
			{
				tmpRect.InflateRect(iOffsetX, iOffsetY);
				tmpRect.NormalizeRect();
			}
			else
			{
				tmpRect = CRect(0, 0, m_iWidth, m_iHeight);
			}
		}

		// 키우고 줄이다 범위를 벋어나면 예외 처리 해준다.
		if (tmpRect.left < 0)				tmpRect.left = 0;
		if (tmpRect.right > m_iWidth)		tmpRect.right = m_iWidth;
		if (tmpRect.top < 0)				tmpRect.top = 0;
		if (tmpRect.bottom > m_iHeight)		tmpRect.bottom = m_iHeight;

		double dTmpRatio = (double)tmpRect.Height() / (double)tmpRect.Width();
		if (dPanelRatio > dTmpRatio)
		{
			// 줄인 이미지가 표시 창보다 가로로 더 긴 비율이면 세로를 좀 더 늘인다.
			int iYExt = (int)(((tmpRect.Width() * dPanelRatio) - tmpRect.Height()) / 2.0);

			tmpRect.top -= iYExt;
			tmpRect.bottom += iYExt;

			if (tmpRect.top < 0) tmpRect.top = 0;
			if (tmpRect.bottom > m_iHeight) tmpRect.bottom = m_iHeight;
		}
		else
		{
			// 줄인 이미지가 표시 창보다 세로로 더 긴 비율이면 가로를 좀 더 늘인다.
			int iXExt = (int)(((tmpRect.Height() / dPanelRatio) - tmpRect.Width()) / 2.0);

			tmpRect.left -= iXExt;
			tmpRect.right += iXExt;

			if (tmpRect.left < 0) tmpRect.left = 0;
			if (tmpRect.right > m_iWidth) tmpRect.right = m_iWidth;
		}

		m_DisplayRect = tmpRect;

		if (m_DisplayRect.Width() > m_iWidth || (abs(m_DisplayRect.Width() - m_iWidth) < 32 && abs(m_DisplayRect.Height() - m_iHeight) < 32))
		{
			m_DisplayRect = CRect(0, 0, m_iWidth, m_iHeight);
			
		}

		CString strText;
		strText.Format(_T("ROI (%d, %d, %d, %d)"), m_DisplayRect.left, m_DisplayRect.top, m_DisplayRect.right, m_DisplayRect.bottom);
		SetCaption(1, strText);
		Invalidate(FALSE);
		///////////////////////////////////////////////////////////////////////
	}

	return CStatic::OnMouseWheel(nFlags, zDelta, pt);
}


void CImagePanel::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptOld = point;

	if (m_bUseRectTracker && nFlags & MK_SHIFT)
	{
		if (m_tracker.HitTest(point) < 0)
		{
			CRectTracker track;

			if (track.TrackRubberBand(this, point, true))
			{
				track.m_rect.NormalizeRect();
				m_tracker.m_rect = track.m_rect;
			}
		}
		else
		{
			if (m_tracker.Track(this, point, true)) // Check when click keep on Rect and moved
			{
				m_tracker.m_rect.NormalizeRect();

				if (m_tracker.m_rect.left < 0)
					m_tracker.m_rect.left = 0;

				if (m_tracker.m_rect.top < 0)
					m_tracker.m_rect.top = 0;

				/*		if (m_tracker.m_rect.right > m_iWidth)
							m_tracker.m_rect.right = m_iWidth;

							if (m_tracker.m_rect.bottom > m_iHeight)
							m_tracker.m_rect.bottom = m_iHeight;*/
			}
		}

		this->Invalidate();

	}


	CStatic::OnLButtonDown(nFlags, point);
}

BOOL CImagePanel::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_bUseRectTracker)
	{
		if (m_tracker.SetCursor(pWnd, nHitTest))
		{
			HCURSOR hCursor=NULL;
			CPoint point;
			::GetCursorPos(&point);
			ScreenToClient(&point);
			int nHitOn = m_tracker.HitTest(point);
			switch (nHitOn)
			{
			case CRectTracker::hitTopLeft:
			case CRectTracker::hitBottomRight:
				hCursor = ::LoadCursor(NULL, IDC_SIZENWSE);
				break;
			case CRectTracker::hitTopRight:
			case CRectTracker::hitBottomLeft:
				hCursor = ::LoadCursor(NULL, IDC_SIZENESW);
				break;
			case CRectTracker::hitTop:
			case CRectTracker::hitBottom:
				hCursor = ::LoadCursor(NULL, IDC_SIZENS);
				break;
			case CRectTracker::hitRight:
			case CRectTracker::hitLeft:
				hCursor = ::LoadCursor(NULL, IDC_SIZEWE);
				break;
			case CRectTracker::hitMiddle:
				hCursor = ::LoadCursor(NULL, IDC_SIZEALL);
				break;
			}

			SetCursor(hCursor);

			return TRUE;
		}
	}

	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CImagePanel::SetRectTrackerScreen(CRect modelRect)
{
	m_tracker.m_rect = modelRect;
}

CRect CImagePanel::GetRectTrackerScreen(void)
{
	return m_tracker.m_rect;
}

CRect CImagePanel::GetviewSize(void)
{
	CRect clientRect;
	GetClientRect(clientRect);
	return clientRect;
}


void CImagePanel::SetRectTrackerImage(CRect modelrect)
{
	CPoint tl = modelrect.TopLeft();
	CPoint br = modelrect.BottomRight();

	CPoint tl_s = ImagePosToScreenPos(tl);
	CPoint br_s = ImagePosToScreenPos(br);

	m_tracker.m_rect = CRect(tl_s, br_s);
}


CRect CImagePanel::GetRectTrackerImage(void)
{
	CPoint tl = m_tracker.m_rect.TopLeft();
	CPoint br = m_tracker.m_rect.BottomRight();

	CPoint tl_i = ScreenPosToImagePos(tl);
	CPoint br_i = ScreenPosToImagePos(br);

	return CRect(tl_i, br_i);
}

CPoint CImagePanel::ScreenPosToImagePos(CPoint ptScreen)
{
	CPoint ptRet;
 		CRect rect;
 		GetClientRect(&rect);
 
  		double dViewRatioX = (double)(m_iWidth / m_dZoomFactor) / (double)rect.Width();
  		double dViewRatioY = (double)(m_iHeight / m_dZoomFactor) / (double)rect.Height();
 
  		ptRet.x = (int)((double)(ptScreen.x + m_ptViewOrg.x)*dViewRatioX + 0.5);
  		ptRet.y = (int)((double)(ptScreen.y + m_ptViewOrg.y)*dViewRatioY + 0.5);
  
 		CString sMsg;
 		sMsg.Format(_T("SPos(%d,%d)-IPos(%d,%d) : VR(%.2lf,%.2lf), VO(%d,%d)\n"), ptScreen.x, ptScreen.y, ptRet.x, ptRet.y, dViewRatioX, dViewRatioY, m_ptViewOrg.x, m_ptViewOrg.y);
 		//		TRACE(sMsg);
 
 		if (ptRet.x > m_iWidth) ptRet.x = -1;
 		if (ptRet.y > m_iHeight) ptRet.y = -1;
 	
 	return ptRet;
 }

 CPoint CImagePanel::ImagePosToScreenPos(CPoint ptImage)
 {
 	CPoint ptRet;
 	CRect rect;
	GetClientRect(&rect);

	double dViewRatioX = (double)(m_iWidth / m_dZoomFactor) / (double)rect.Width();
	double dViewRatioY = (double)(m_iHeight / m_dZoomFactor) / (double)rect.Height();

	ptRet.x = (int)(((double)(ptImage.x - m_ptViewOrg.x) / dViewRatioX) + 0.5);
	ptRet.y = (int)(((double)(ptImage.y - m_ptViewOrg.y) / dViewRatioY) + 0.5);

 	return ptRet;
 }

 void CImagePanel::SetUseRectTracker(BOOL bUse)
 {
	 m_bUseRectTracker = bUse;
 }

 void CImagePanel::UpdateTracker()
 {
	 CRect rect;
	 GetClientRect(&rect);

	 CRect rDispImgArea(ScreenPosToImagePos(rect.TopLeft()), ScreenPosToImagePos(rect.BottomRight()));

	 CString sMsg;
	 sMsg.Format(_T("Image Pos (%d,%d,%d,%d)\n"), rDispImgArea.left, rDispImgArea.top, rDispImgArea.Width(), rDispImgArea.Height());
	 //		TRACE(sMsg);

	// PutRect(0, IMCOORD_IMG, rDispImgArea, RGB(0, 255, 0), 30);
	 UpdateDisplay();

 }