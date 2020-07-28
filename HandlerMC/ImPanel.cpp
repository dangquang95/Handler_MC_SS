// ImPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImPanel.h"

// CImPanel
namespace im
{

IMPLEMENT_DYNAMIC(CImPanel, CWnd)

CImPanel::CImPanel()
{
	m_ScrollHelper.AttachWnd(this);

	m_pTrackPanel = NULL;

	m_iWidth = 640;
	m_iHeight = 480;
	m_iChannel = 0;
	m_pImageData = NULL;

	m_dZoomFactor = 1.0;
	m_bZoomChanged = FALSE;

	m_bCenterLine = FALSE;

	m_iFitToScreen = FIT_NONE;

	m_bDisplayCursor = FALSE;

	m_ptCursorPosImgPx = CPoint(-1,-1);

	m_bROIEnble = false;

	CRect rect(10, 10, 100, 100);

	m_tracker.m_rect = rect;

	m_tracker.m_nStyle = 0;
	m_tracker.m_nStyle |= CRectTracker::dottedLine;
	m_tracker.m_nStyle |= CRectTracker::resizeOutside;

	m_bUseRectTracker = FALSE;
}

CImPanel::~CImPanel()
{
	if(m_pImageData)
	{
		delete m_pImageData;
	}
}


BEGIN_MESSAGE_MAP(CImPanel, CWnd)
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEACTIVATE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CImPanel 명령입니다.

void CImPanel::SetTracker(CImPanel * pTracker)
{
	m_pTrackPanel = pTracker;
}

void CImPanel::UpdateDisplay()
{
	AdjustScrollbars();	
	Invalidate(FALSE);	
}

void CImPanel::UpdateTracker()
{
	if( m_pTrackPanel )
	{
		CRect rect;
		GetClientRect(&rect);

		CRect rDispImgArea( ScreenPosToImagePos(rect.TopLeft()), ScreenPosToImagePos(rect.BottomRight()) );

		CString sMsg;
		sMsg.Format(_T("Image Pos (%d,%d,%d,%d)\n"), rDispImgArea.left, rDispImgArea.top, rDispImgArea.Width(), rDispImgArea.Height() );
//		TRACE(sMsg);

		m_pTrackPanel->PutRect( 0, IMCOORD_IMG, rDispImgArea, RGB(0,255,0), 30 );
		m_pTrackPanel->UpdateDisplay();		
	}	
}

void CImPanel::SetStretchToScreen(BOOL bSet)
{
	if( bSet )
	{
		m_iFitToScreen = FIT_STRETCH;
	}
	else
	{
		m_iFitToScreen = FIT_NONE;
	}
}

void CImPanel::SetFitToScreen()
{
	m_iFitToScreen = FIT_XY;

	AdjustZoomFactor();
}

void CImPanel::SetFitXToScreen()
{
	m_iFitToScreen = FIT_X;

	AdjustZoomFactor();
}

void CImPanel::SetFitYToScreen()
{
	m_iFitToScreen = FIT_Y;

	AdjustZoomFactor();
}

void CImPanel::SetCenterLine(BOOL bSet)
{
	m_bCenterLine = bSet;
}

void CImPanel::SetDisplayCursor(BOOL bSet, CString sText)
{
	m_bDisplayCursor = bSet;
	m_sCursorText = sText;
}

void CImPanel::SetImage(unsigned char* pImageData, int iDataSize, int iWidth, int iHeight, int iChannel, BOOL bDisplayUpdate)
{
	if(NULL == pImageData)
	{
		return;
	}	

	try
	{
		int iRem = iWidth%4;
		if( iRem != 0 )
		{
			iRem = 4-iRem;
		}
		int iImageSize = (iWidth+iRem)*iHeight*iChannel;

		BOOL bImgSizeChanged = FALSE;

		if(NULL == m_pImageData)
		{
			m_pImageData = new unsigned char[iImageSize];

			bImgSizeChanged = TRUE;
		}
		else
		{
			if(m_iWidth != iWidth || m_iHeight != iHeight || m_iChannel != iChannel)
			{
				delete[] m_pImageData;
				m_pImageData = new unsigned char[iImageSize];

				bImgSizeChanged = TRUE;
			}
		}

		m_iWidth = iWidth;
		m_iHeight = iHeight;
		m_iChannel = iChannel;

		for( int i=0; i<iHeight; i++ )
		{
			memcpy( m_pImageData+i*(iWidth+iRem)*iChannel, pImageData+i*iWidth*iChannel, iWidth*iChannel*sizeof(unsigned char) );
		}

		if( bImgSizeChanged )
		{
			m_bZoomChanged = TRUE;
			AdjustZoomFactor();
		}

		if( m_pTrackPanel )
		{
			m_pTrackPanel->SetImage( pImageData, iDataSize, iWidth, iHeight, iChannel, FALSE );
		}

		if(bDisplayUpdate)
		{
			UpdateDisplay();
		}
	}
	catch(CException * e)
	{
		e->Delete();
	}
}

void CImPanel::PutRect(int iNo, int iCoord, CRect rect, COLORREF color, int iLineWidth)
{
	if( iNo<0 || iNo>=MAX_OBJECT ) return;
	m_Rect[iNo].m_bValid = TRUE;
	m_Rect[iNo].m_Rect = rect;
	m_Rect[iNo].m_Color = color;
	m_Rect[iNo].m_iCoord = iCoord;
	m_Rect[iNo].m_iLineWidth = iLineWidth;
}

void CImPanel::PutCircle(int iNo, int iCoord, CPoint center, int iRadius, COLORREF color, int iLineWidth)
{
	if( iNo<0 || iNo>=MAX_OBJECT ) return;
	m_Circle[iNo].m_bValid = TRUE;
	m_Circle[iNo].m_Center = center;
	m_Circle[iNo].m_iRadius = iRadius;
	m_Circle[iNo].m_Color = color;
	m_Circle[iNo].m_iCoord = iCoord;
	m_Circle[iNo].m_iLineWidth = iLineWidth;
}

void CImPanel::PutText(int iNo, int iCoord, CPoint pt, CString sText, int iHeight, COLORREF color, int iAlign, CString sFont)
{
	if( iNo<0 || iNo>=MAX_OBJECT ) return;
	m_Text[iNo].m_bValid = TRUE;
	m_Text[iNo].m_iCoord = iCoord;
	m_Text[iNo].m_Pt = pt;
	m_Text[iNo].m_sText = sText;
	m_Text[iNo].m_iHeight = iHeight;
	m_Text[iNo].m_Color = color;
	m_Text[iNo].m_sFont = sFont;
	m_Text[iNo].m_iAlign = iAlign;
}

void CImPanel::FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp)
{
	BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);

	memset(bmih, 0, sizeof(*bmih));
	bmih->biSize	= sizeof(BITMAPINFOHEADER);
	bmih->biWidth	= width;
	bmih->biHeight	= -abs(height);
	bmih->biPlanes	= 1;
	bmih->biBitCount	= bpp;
	bmih->biCompression	= BI_RGB;

	if(bpp == 8)
	{
		RGBQUAD* palette = bmi->bmiColors;
		int i;
		for(i=0; i<256; i++)
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}
}

void CImPanel::PrepDC(CDC *pDC, const CRect& rVirt, const CRect& rScreen)
{
	// maps virtual into client
	m_rVirtual = rVirt;
	m_rScreen = rScreen;

	pDC->IntersectClipRect(&rScreen);

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rVirt.Width(), rVirt.Height());

	LONG wid = (LONG)(m_dZoomFactor * (double)rVirt.Width() +0.5);
	LONG hgt = (LONG)(m_dZoomFactor * (double)rVirt.Height() +0.5);

	pDC->SetViewportExt(wid, hgt);

	m_ViewSize = CSize(wid,hgt);

	CSize scrollPos = m_ScrollHelper.GetScrollPos();
	pDC->SetViewportOrg(-scrollPos.cx, -scrollPos.cy);

	m_ptViewOrg = scrollPos;
}

void CImPanel::AdjustScrollbars()
{
	if( m_iFitToScreen == FIT_STRETCH )
	{
		int xMax = (int)((double)m_rScreen.Width() * m_dZoomFactor);
		int yMax = (int)((double)m_rScreen.Height() * m_dZoomFactor);
		m_ScrollHelper.SetPageSize(m_rScreen.Width(), m_rScreen.Height());
		m_ScrollHelper.SetDisplaySize(xMax, yMax);
		CSize scrollpos, newscrollpos;
		m_ScrollHelper.ScrollToOrigin(FALSE,FALSE);
	}
	else
	{
		int xMax = (int)((double)m_iWidth * m_dZoomFactor);
		int yMax = (int)((double)m_iHeight * m_dZoomFactor);
		m_ScrollHelper.SetPageSize(m_rScreen.Width(), m_rScreen.Height());
		m_ScrollHelper.SetDisplaySize(xMax, yMax);
		m_ScrollHelper.ScrollToOrigin(FALSE,FALSE);
	}	
}

void CImPanel::AdjustZoomFactor()
{
	CRect rect;
	GetClientRect(rect);

	double dXRatio = (double)rect.Width() / (double)m_iWidth;
	double dYRatio = (double)rect.Height() / (double)m_iHeight;

	if( m_iFitToScreen == FIT_X )
	{
		m_dZoomFactor = dXRatio;
	}
	else if( m_iFitToScreen == FIT_Y )
	{
		m_dZoomFactor = dYRatio;
	}
	else if( m_iFitToScreen == FIT_XY /*&& !m_bZoomChanged*/)
	{
		m_dZoomFactor = dXRatio<dYRatio?dXRatio:dYRatio;
	}
}


void CImPanel::DrawImage(CDC * pDC)
{	
	CRect rClient;
	GetClientRect(rClient);
	
	int iVirtWidth = (int)(m_iWidth*m_dZoomFactor);
	int iVirtHeight = (int)(m_iHeight*m_dZoomFactor);
	
	if( m_bZoomChanged )
	{
		m_bZoomChanged = FALSE;
		COLORREF backgrColor = RGB(40,40,40);
		pDC->FillRect(&rClient, &CBrush(backgrColor));
	}

	CDC memDC;
	CBitmap bitmap;

	memDC.CreateCompatibleDC(pDC);
	bitmap.CreateCompatibleBitmap(pDC, m_iWidth, m_iHeight);
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	unsigned char buffer[sizeof(BITMAPINFOHEADER) + 1024];
	BITMAPINFO* bmi = (BITMAPINFO*)buffer;
	int bmp_w = m_iWidth;
	int bmp_h = m_iHeight;

	FillBitmapInfo(bmi, bmp_w, bmp_h, m_iChannel*8);

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
		
	CRect rVirt(0, 0, m_iWidth, m_iHeight);
	PrepDC(pDC, rVirt, rClient);

	if( m_iFitToScreen == FIT_STRETCH )
	{
		pDC->StretchBlt(0, 0, rClient.Width(), rClient.Height(), &memDC, 0, 0,  m_iWidth,  m_iHeight, SRCCOPY);
	}
	else
	{
		pDC->StretchBlt(0, 0, m_iWidth, m_iHeight, &memDC, 0, 0,  m_iWidth,  m_iHeight, SRCCOPY);
	}	

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
}

void CImPanel::DrawZoomRect(CDC * pDC)
{
	CSize ptViewSize = pDC->GetViewportExt();
	CPoint ptViewOrg = pDC->GetViewportOrg();

	int iSave = pDC->SaveDC();

	double dViewRatioX = (double)m_iWidth / (double)m_ViewSize.cx;
	double dViewRatioY = (double)m_iHeight / (double)m_ViewSize.cy;

	CPoint ptOffStart = CPoint((int)(m_ptROIStart.x*dViewRatioX),(int)(m_ptROIStart.y*dViewRatioY));
	CPoint ptOffEnd = CPoint((int)(m_ptROIEnd.x*dViewRatioX),(int)(m_ptROIEnd.y*dViewRatioY));

	CRect roi(ptOffStart, ptOffEnd);
	pDC->SetROP2(R2_NOTXORPEN);
	pDC->Rectangle(&roi);

	pDC->RestoreDC(iSave);
}

void CImPanel::DrawROI(CDC * pDC)
{
	for(int i=0; i<MAX_ITEM; i++)
	{
		if( m_ROI[i].bUse && !m_ROI[i].rect.IsRectEmpty() )
		{
			int iSave = pDC->SaveDC();

			CRect roiRect;
			if( m_iFitToScreen == FIT_STRETCH )
			{
				CRect rect;
				GetClientRect(rect);

				double dXRatio =  (double)rect.Width() / (double)m_iWidth;
				double dYRatio =  (double)rect.Height() / (double)m_iHeight;

				roiRect.TopLeft().x = (int)(m_ROI[i].rect.TopLeft().x * dXRatio);
				roiRect.TopLeft().y = (int)(m_ROI[i].rect.TopLeft().y * dYRatio);
				roiRect.BottomRight().x = (int)(m_ROI[i].rect.BottomRight().x * dXRatio);
				roiRect.BottomRight().y = (int)(m_ROI[i].rect.BottomRight().y * dYRatio);
			}
			else
			{
				roiRect = m_ROI[i].rect;
			}

			CPen penRect;
			penRect.CreatePen(PS_SOLID, 1, m_ROI[i].rectColor);
			pDC->SelectObject( &penRect );

			pDC->MoveTo(roiRect.left, roiRect.top);
			pDC->LineTo(roiRect.right, roiRect.top);
		
			pDC->MoveTo(roiRect.right, roiRect.top);
			pDC->LineTo(roiRect.right, roiRect.bottom);

			pDC->MoveTo(roiRect.right, roiRect.bottom);
			pDC->LineTo(roiRect.left, roiRect.bottom);
		
			pDC->MoveTo(roiRect.left, roiRect.bottom);
			pDC->LineTo(roiRect.left, roiRect.top);

			// 센터 라인 그리기
			CPen penCenter;
			penCenter.CreatePen(PS_SOLID, 1, m_ROI[i].centerLineColor);
			pDC->SelectObject( &penCenter );

			int iWidth = roiRect.Width();
			int iHeight = roiRect.Height();

			int iCenterX = roiRect.left + iWidth/2;
			int iCenterY = roiRect.top + iHeight/2;

	//		int iDashDist = drawLineWidth/10;
		
			pDC->MoveTo(roiRect.left, iCenterY);
			pDC->LineTo(roiRect.right, iCenterY);
		
			pDC->MoveTo(iCenterX, roiRect.top);
			pDC->LineTo(iCenterX, roiRect.bottom);	

			pDC->RestoreDC( iSave );
		}	
	}
}

void CImPanel::DrawCenterLine(CDC * pDC)
{
	CPen penRect;
	CPen * pOldPen;
	penRect.CreatePen(PS_DOT, 1, RGB(0,255,0));
	pOldPen = pDC->SelectObject( &penRect );

	CRect rect;
	GetClientRect(rect);

	int iWidth = rect.Width();
	int iHeight = rect.Height();

	pDC->MoveTo( 0, iHeight/2 );
	pDC->LineTo( iWidth, iHeight/2 );

	pDC->MoveTo( iWidth/2, 0 );
	pDC->LineTo( iWidth/2, iHeight );

	/*
	pDC->MoveTo( 0, (int)(iHeight*0.15) );
	pDC->LineTo( iWidth, (int)(iHeight*0.15) );

	pDC->MoveTo( 0, (int)(iHeight*0.85) );
	pDC->LineTo( iWidth, (int)(iHeight*0.85) );
	*/

	pDC->SelectObject( pOldPen );
}

void CImPanel::DrawPoint(CDC * pDC)
{
	for(int i=0; i<MAX_ITEM; i++)
	{
		if( m_Point[i].bUse )
		{
			if( m_Point[i].pt.x == -1 && m_Point[i].pt.y == -1 ) return; 

			CRect rect;
			GetClientRect(&rect);

			CPoint drawCenter;
			double dViewRatioX = (double)m_iWidth / (double)rect.Width();
	
			CPoint ptCenter;
			if( m_iFitToScreen == FIT_STRETCH )
			{
				CRect rect;
				GetClientRect(rect);

				double dXRatio =  (double)rect.Width() / (double)m_iWidth;
				double dYRatio =  (double)rect.Height() / (double)m_iHeight;

				dViewRatioX = dXRatio;

				ptCenter.x = (int)(m_Point[i].pt.x * dXRatio);
				ptCenter.y = (int)(m_Point[i].pt.y * dYRatio);
			}
			else
			{
				ptCenter = m_Point[i].pt;
			}	

			CPoint ptTemp(m_Point[i].iSize, 0);
			CPoint ptRad = ScreenPosToImagePos(ptTemp);
			int iDrawRadius = ptRad.x;
	
			int drawLineWidth = (int)(dViewRatioX*0.5);
			COLORREF drawColor = m_Point[i].circleColor;

			CBrush colorBrush, *oldBrush;
			CPen colorPen, *oldPen;
			colorPen.CreatePen(PS_SOLID, drawLineWidth, drawColor);
			colorBrush.CreateSolidBrush(drawColor);

			CRect drawRect( ptCenter.x-iDrawRadius, ptCenter.y-iDrawRadius, ptCenter.x+iDrawRadius, ptCenter.y+iDrawRadius );

			oldPen = pDC->SelectObject(&colorPen);
			if( drawLineWidth==IMCOLOR_FILLED )
			{
				oldBrush = pDC->SelectObject(&colorBrush);
			}
			else
			{
				oldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
			}
			
			pDC->Ellipse(drawRect);

		// 센터 라인 그리기
			CPen penCenter;
			penCenter.CreatePen(PS_SOLID, 1, m_Point[i].centerLineColor);
			pDC->SelectObject( &penCenter );

			int iCenterX = ptCenter.x;
			int iCenterY = ptCenter.y;
		
			pDC->MoveTo(ptCenter.x-iDrawRadius, iCenterY);
			pDC->LineTo(ptCenter.x+iDrawRadius, iCenterY);
		
			pDC->MoveTo(iCenterX, ptCenter.y-iDrawRadius);
			pDC->LineTo(iCenterX, ptCenter.y+iDrawRadius);	

			pDC->SelectObject(oldPen);
			pDC->SelectObject(oldBrush);
		}
	}
}


void CImPanel::DrawCross(CDC * pDC)
{
	for(int i=0; i<MAX_ITEM; i++)
	{
		if( m_Cross[i].bUse )
		{
			if( m_Cross[i].pt.x == -1 && m_Cross[i].pt.y == -1 ) return; 

			CPen penRect;
			CPen * pOldPen;
			penRect.CreatePen(PS_DOT, 1, m_Cross[i].rectColor);
			pOldPen = pDC->SelectObject( &penRect );

			CRect rect;
			GetClientRect(rect);

			CPoint ptCross;
			CRect rtCross;

			int iRtWidth = m_Cross[i].size.cx;
			int iRtHeight = m_Cross[i].size.cy;

			if( m_iFitToScreen == FIT_STRETCH )
			{
				double dXRatio =  (double)rect.Width() / (double)m_iWidth;
				double dYRatio =  (double)rect.Height() / (double)m_iHeight;

				ptCross.x = (int)(m_Cross[i].pt.x * dXRatio);
				ptCross.y = (int)(m_Cross[i].pt.y * dYRatio);

				iRtWidth = (int)(m_Cross[i].size.cx * dXRatio);
				iRtHeight = (int)(m_Cross[i].size.cy * dYRatio);
			}
			else
			{
				ptCross = m_Cross[i].pt;
			}	

			rtCross = CRect( ptCross.x-iRtWidth/2, ptCross.y-iRtHeight/2, ptCross.x+iRtWidth/2, ptCross.y+iRtHeight/2 );

			int iWidth = rect.Width();
			int iHeight = rect.Height();

			pDC->MoveTo( 0, ptCross.y );
			pDC->LineTo( iWidth, ptCross.y );

			pDC->MoveTo( ptCross.x, 0 );
			pDC->LineTo( ptCross.x, iHeight );

			pDC->MoveTo( CPoint( rtCross.left, rtCross.top ) );
			pDC->LineTo( CPoint( rtCross.right, rtCross.top ) );

			pDC->MoveTo( CPoint( rtCross.right, rtCross.top ) );
			pDC->LineTo( CPoint( rtCross.right, rtCross.bottom ) );

			pDC->MoveTo( CPoint( rtCross.right, rtCross.bottom ) );
			pDC->LineTo( CPoint( rtCross.left, rtCross.bottom ) );

			pDC->MoveTo( CPoint( rtCross.left, rtCross.bottom ) );
			pDC->LineTo( CPoint( rtCross.left, rtCross.top ) );

			pDC->SelectObject( pOldPen );
		}
	}
}

void CImPanel::DrawRect(CDC * pDC)
{
	for( int iNo=0; iNo<MAX_OBJECT; iNo++ )
	{
		if( m_Rect[iNo].m_bValid )
		{
			CRect drawRect;
			int drawLineWidth = m_Rect[iNo].m_iLineWidth;
			COLORREF drawColor = m_Rect[iNo].m_Color;

			if( m_Rect[iNo].m_iCoord==IMCOORD_SCREEN )
			{
				CPoint tl = ImagePosToScreenPos(m_Rect[iNo].m_Rect.TopLeft());
				CPoint br = ImagePosToScreenPos(m_Rect[iNo].m_Rect.BottomRight());

				drawRect = CRect( tl, br );
			}
			else if( m_Rect[iNo].m_iCoord==IMCOORD_IMG )
			{
				drawRect = m_Rect[iNo].m_Rect;				
			}			

			CBrush colorBrush;
			CPen colorPen;
			colorPen.CreatePen(PS_SOLID, drawLineWidth, drawColor);
			colorBrush.CreateSolidBrush(drawColor);

			if( drawLineWidth == IMCOLOR_FILLED )
			{
				pDC->Rectangle(drawRect);
			}
			else
			{
				pDC->FrameRect(drawRect, &colorBrush);
			}			
		}		
	}	
}

void CImPanel::DrawCircle(CDC * pDC)
{
	for( int iNo=0; iNo<MAX_OBJECT; iNo++ )
	{
		if( m_Circle[iNo].m_bValid )
		{
			CPoint drawCenter;
			int iDrawRadius = m_Circle[iNo].m_iRadius;
			int drawLineWidth = m_Circle[iNo].m_iLineWidth;
			COLORREF drawColor = m_Circle[iNo].m_Color;

			if( m_Circle[iNo].m_iCoord==IMCOORD_SCREEN )
			{
				drawCenter = m_Circle[iNo].m_Center;
			}
			else if( m_Rect[iNo].m_iCoord==IMCOORD_IMG )
			{
				drawCenter = ImagePosToScreenPos(m_Circle[iNo].m_Center);
			}			

			CBrush colorBrush, *oldBrush;
			CPen colorPen, *oldPen;
			colorPen.CreatePen(PS_SOLID, drawLineWidth, drawColor);
			colorBrush.CreateSolidBrush(drawColor);

			CRect drawRect( drawCenter.x-iDrawRadius, drawCenter.y-iDrawRadius, drawCenter.x+iDrawRadius, drawCenter.y+iDrawRadius );

			oldPen = pDC->SelectObject(&colorPen);
			if( drawLineWidth==IMCOLOR_FILLED )
			{
				oldBrush = pDC->SelectObject(&colorBrush);
			}
			else
			{
				oldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
			}
			
			pDC->Ellipse(drawRect);
			pDC->SelectObject(oldPen);
			pDC->SelectObject(oldBrush);
		}		
	}	
}

void CImPanel::DrawText(CDC * pDC)
{
	for( int iNo=0; iNo<MAX_OBJECT; iNo++ )
	{
		if( m_Text[iNo].m_bValid )
		{
			CRect drawRect(0,0,0,0);
			CRect rText(0,0,0,0);
			CFont fontText;
			int iDTDir = DT_LEFT;

			CPoint drawPt(0,0);
			if( m_Text[iNo].m_iCoord==IMCOORD_SCREEN )
			{
				drawPt = m_Text[iNo].m_Pt;
			}
			else if( m_Text[iNo].m_iCoord==IMCOORD_IMG )
			{
				drawPt = ImagePosToScreenPos( m_Text[iNo].m_Pt );				
			}

			switch( m_Text[iNo].m_iAlign )
			{
			case IMTEXT_C:
				rText.top = drawPt.y - m_Text[iNo].m_iHeight/2;
				rText.bottom = drawPt.y + m_Text[iNo].m_iHeight/2;
				rText.left = drawPt.x - (m_Text[iNo].m_sText.GetLength()/2)*m_Text[iNo].m_iHeight;
				rText.right = drawPt.x + (m_Text[iNo].m_sText.GetLength()/2)*m_Text[iNo].m_iHeight;
				iDTDir = DT_CENTER;
				break;
			case IMTEXT_TL:
				rText.top = drawPt.y;
				rText.bottom = rText.top + m_Text[iNo].m_iHeight;
				rText.left =drawPt.x;
				rText.right = rText.left + m_Text[iNo].m_sText.GetLength()*m_Text[iNo].m_iHeight;
				iDTDir = DT_LEFT;
				break;
			case IMTEXT_TR:
				rText.top = drawPt.y;
				rText.bottom = rText.top + m_Text[iNo].m_iHeight;
				rText.right = drawPt.x;
				rText.left = rText.right - m_Text[iNo].m_sText.GetLength()*m_Text[iNo].m_iHeight;	
				iDTDir = DT_RIGHT;
				break;
			case IMTEXT_BR:		
				rText.bottom =drawPt.y;
				rText.top = rText.bottom - m_Text[iNo].m_iHeight;
				rText.right = drawPt.x;
				rText.left = rText.right - m_Text[iNo].m_sText.GetLength()*m_Text[iNo].m_iHeight;		
				iDTDir = DT_RIGHT;
				break;
			case IMTEXT_BL:
				rText.bottom = drawPt.y;
				rText.top = rText.bottom - m_Text[iNo].m_iHeight;
				rText.left = drawPt.x;
				rText.right = rText.left + m_Text[iNo].m_sText.GetLength()*m_Text[iNo].m_iHeight;
				iDTDir = DT_LEFT;
				break;
			default:
				break;
			}			

			////////////////////////////////////////////////////////////////////
			LOGFONT LogFont;

			memset(&LogFont, 0, sizeof(LogFont));

			LogFont.lfHeight = rText.Height();
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
			_tcscpy_s(LogFont.lfFaceName, _countof(_T("Lucida Console")), _T("Lucida Console"));
			fontText.CreateFontIndirect(&LogFont);
			/////////////////////////////////////////////////////////////////////

			CFont* pOldFont = pDC->SelectObject(&fontText);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(m_Text[iNo].m_Color);
			pDC->DrawText(m_Text[iNo].m_sText, -1, &rText, DT_SINGLELINE | iDTDir | DT_VCENTER);
			pDC->SelectObject(pOldFont);
		}
	}
}

CPoint CImPanel::ScreenPosToImagePos(CPoint ptScreen)
{
	CPoint ptRet;

	if( m_iFitToScreen==FIT_STRETCH )
	{
		CRect rect;
		GetClientRect(&rect);

		double dViewRatioX = (double)(m_iWidth/m_dZoomFactor) / (double)rect.Width();
		double dViewRatioY = (double)(m_iHeight/m_dZoomFactor) / (double)rect.Height();

//		ptRet.x = (int)((double)(ptScreen.x)*dViewRatioX+0.5);
//		ptRet.y = (int)((double)(ptScreen.y)*dViewRatioY+0.5);

		ptRet.x = (int)((double)(ptScreen.x+m_ptViewOrg.x)*dViewRatioX+0.5);
		ptRet.y = (int)((double)(ptScreen.y+m_ptViewOrg.y)*dViewRatioY+0.5);

		CString sMsg;
		sMsg.Format(_T("SPos(%d,%d)-IPos(%d,%d) : VR(%.2lf,%.2lf), VO(%d,%d)\n"), ptScreen.x, ptScreen.y, ptRet.x, ptRet.y, dViewRatioX, dViewRatioY, m_ptViewOrg.x, m_ptViewOrg.y);
//		TRACE(sMsg);

		if( ptRet.x > m_iWidth ) ptRet.x=-1;
		if( ptRet.y > m_iHeight ) ptRet.y=-1;		
	}
	else
	{
		double dViewRatioX = (double)m_iWidth / (double)m_ViewSize.cx;
		double dViewRatioY = (double)m_iHeight / (double)m_ViewSize.cy;

		ptRet.x = (int)((double)(ptScreen.x+m_ptViewOrg.x)*dViewRatioX+0.5);
		ptRet.y = (int)((double)(ptScreen.y+m_ptViewOrg.y)*dViewRatioY+0.5);

		CString sMsg;
		sMsg.Format(_T("!! SPos(%d,%d)-IPos(%d,%d) : VR(%.2lf,%.2lf), VO(%d,%d)\n"), ptScreen.x, ptScreen.y, ptRet.x, ptRet.y, dViewRatioX, dViewRatioY, m_ptViewOrg.x, m_ptViewOrg.y);
		//TRACE(sMsg);

		if( ptRet.x > m_iWidth ) ptRet.x=-1;
		if( ptRet.y > m_iHeight ) ptRet.y=-1;
	}	

	return ptRet;
}

CPoint CImPanel::ImagePosToScreenPos(CPoint ptImage)
{
	CPoint ptRet;

	if( m_iFitToScreen==FIT_STRETCH )
	{
		CRect rect;
		GetClientRect(&rect);

		double dViewRatioX = (double)(m_iWidth/m_dZoomFactor) / (double)rect.Width();
		double dViewRatioY = (double)(m_iHeight/m_dZoomFactor) / (double)rect.Height();

		ptRet.x = (int)(((double)(ptImage.x- m_ptViewOrg.x)/dViewRatioX)+0.5);
		ptRet.y = (int)(((double)(ptImage.y- m_ptViewOrg.y)/dViewRatioY)+0.5);

//		ptRet.x = (int)(((double)ptImage.x/dViewRatioX)+0.5);
//		ptRet.y = (int)(((double)ptImage.y/dViewRatioY)+0.5);
	}
	else
	{
		double dViewRatioX = (double)m_iWidth / (double)m_ViewSize.cx;
		double dViewRatioY = (double)m_iHeight / (double)m_ViewSize.cy;

		ptRet.x = (int)(((double)(ptImage.x- m_ptViewOrg.x)/dViewRatioX)+0.5);
		ptRet.y = (int)(((double)(ptImage.y- m_ptViewOrg.y)/dViewRatioY)+0.5);
	}

	return ptRet;
}

void CImPanel::ChangeZoomFactor(double dRatio)
{
	if( m_dZoomFactor+dRatio>0.0 )
	{
		m_dZoomFactor += dRatio;

		m_bZoomChanged = TRUE;

		UpdateDisplay();
	}
}

//kyj 0312 : init rect make in FOV area
void CImPanel::CheckCrossCenter(int idx)
{
	if(m_Cross[idx].pt.x < m_Cross[idx].size.cx/2) 
		m_Cross[idx].pt.x = m_Cross[idx].size.cx/2;
	if(m_Cross[idx].pt.x> m_iWidth- m_Cross[idx].size.cx/2) 
		m_Cross[idx].pt.x = m_iWidth - m_Cross[idx].size.cx/2;
	if(m_Cross[idx].pt.y < m_Cross[idx].size.cy/2)
		m_Cross[idx].pt.y = m_Cross[idx].size.cy/2;
	if(m_Cross[idx].pt.y> m_iHeight - m_Cross[idx].size.cy/2) 
		m_Cross[idx].pt.y = m_iHeight - m_Cross[idx].size.cy/2;	
}

void CImPanel::CheckRoiCenter(int idx, int iRoiWidth, int iRoiHeight)
{
	
	if(m_ROI[idx].rect.left < 0)
	{
		m_ROI[idx].rect.left = 0;
		m_ROI[idx].rect.right = m_ROI[idx].rect.left + iRoiWidth;
	}

	if(m_ROI[idx].rect.top <0)
	{
		m_ROI[idx].rect.top = 0;
		m_ROI[idx].rect.bottom = m_ROI[idx].rect.top + iRoiHeight;
	}

	if(m_ROI[idx].rect.right > m_iWidth)
	{
		m_ROI[idx].rect.right = m_iWidth;
		m_ROI[idx].rect.left = m_ROI[idx].rect.right - iRoiWidth;
	}

	if(m_ROI[idx].rect.bottom > m_iHeight)
	{
		m_ROI[idx].rect.bottom = m_iHeight;
		m_ROI[idx].rect.top = m_ROI[idx].rect.bottom - iRoiHeight;
	}
	
}


// CImPanel 메시지 처리기입니다.

void CImPanel::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	DrawImage(&dc);
	DrawZoomRect(&dc);	
	DrawRect(&dc);
	DrawCircle(&dc);
	DrawText(&dc);

	if(m_bROIEnble)
		DrawROI(&dc);

	DrawPoint(&dc);
	DrawCross(&dc);
	if(m_bCenterLine) DrawCenterLine(&dc);

	UpdateTracker();

	if( m_bUseRectTracker )
	{	
		if( (m_tracker.m_rect.Width() > 0) && (m_tracker.m_rect.Height() > 0) )
		{
			m_tracker.Draw(&dc);
		}
	}

	m_ScrollHelper.UpdateScrollInfo();
}


void CImPanel::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if( GetCapture()==this )
	{
		ReleaseCapture();
		m_ptROIEnd = point;
		//		Invalidate();

		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING,POPUP_MENU_ID,_T("Zoom In"));

		CPoint pos;
		GetCursorPos(&pos);

		menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pos.x,pos.y,this);

		menu.DestroyMenu();
	}

	CWnd::OnRButtonDown(nFlags, point);
}


BOOL CImPanel::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}


int CImPanel::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int status = CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
	SetFocus();
	return status;
}


void CImPanel::PreSubclassWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CWnd::PreSubclassWindow();
}


LRESULT CImPanel::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (message == WM_NCHITTEST || message == WM_NCLBUTTONDOWN || message == WM_NCLBUTTONDBLCLK || message == WM_NCRBUTTONDOWN) 
	{
		return ::DefWindowProc(m_hWnd, message, wParam, lParam);
	}
	return CWnd::WindowProc(message, wParam, lParam);
}


void CImPanel::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ScrollHelper.OnHScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
	UpdateTracker();
}


void CImPanel::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ScrollHelper.OnVScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
	UpdateTracker();
}


void CImPanel::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if( m_bUseRectTracker )
	{
		if(m_tracker.HitTest(point) < 0) 
		{
			CRectTracker track;

			if(track.TrackRubberBand(this, point, true) )
			{
				track.m_rect.NormalizeRect();
				m_tracker.m_rect = track.m_rect;
			}
		}
		else
		{
			if(m_tracker.Track(this, point, true)) // Check when click keep on Rect and moved
			{
				m_tracker.m_rect.NormalizeRect();
		
				if(m_tracker.m_rect.left < 0)
					m_tracker.m_rect.left = 0;

				if(m_tracker.m_rect.top < 0)
					m_tracker.m_rect.top = 0;
			}
		}

		this->Invalidate();
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void CImPanel::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if( nFlags == MK_SHIFT && MK_LBUTTON )
	{
		if( GetCapture()==this )
		{
			m_ptROIEnd = point;

			UpdateDisplay();
		}
	}

	m_ptCursorPosImgPx = ScreenPosToImagePos(point);

	if( m_bDisplayCursor )
	{
		CString sMsg;
		int iIndex = 0;
		iIndex = m_ptCursorPosImgPx.x + (m_iWidth * m_ptCursorPosImgPx.y);
		uchar ucPix[3];
		if (m_iChannel == 3)
		{
			ucPix[0] = *(m_pImageData + (iIndex * 3));
			ucPix[1] = *(m_pImageData + (iIndex * 3 + 1));
			ucPix[2] = *(m_pImageData + (iIndex * 3 + 2));
		}
		else if (m_iChannel == 1)
		{
			ucPix[0] = m_pImageData[iIndex];
			ucPix[1] = m_pImageData[iIndex];
			ucPix[2] = m_pImageData[iIndex];
		}
		else
		{
			ucPix[0] = 0;
			ucPix[1] = 0;
			ucPix[2] = 0;
		}


		//sMsg.Format(_T("%s (%d,%d) R:%d G:%d B:%d\n"), m_sCursorText, m_ptCursorPosImgPx.x, m_ptCursorPosImgPx.y, ucPix[0], ucPix[1], ucPix[2]);
		sMsg.Format(_T("(%d,%d) R:%d G:%d B:%d\n"), m_ptCursorPosImgPx.x, m_ptCursorPosImgPx.y, ucPix[0], ucPix[1], ucPix[2]);
		int iHeight = 20;// (int)(sqrt((double)(m_iWidth*m_iWidth+m_iHeight*m_iHeight))*0.005);
		PutText(254, IMCOORD_SCREEN, CPoint(0,0), sMsg, iHeight, RGB(0,255,0), IMTEXT_TL);

		UpdateDisplay();
	}


	if( m_bUseRectTracker )
	{
		HCURSOR hCursor;
		hCursor = ::LoadCursor(NULL, IDC_ARROW);
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
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CImPanel::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if( GetCapture()==this )
	{
		ReleaseCapture();
		m_ptROIEnd = point;
//		Invalidate();

		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING,POPUP_MENU_ID,_T("Zoom In"));

		CPoint pos;
		GetCursorPos(&pos);

		menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pos.x,pos.y,this);

		menu.DestroyMenu();
	}

	CWnd::OnLButtonUp(nFlags, point);
}

// setcursor
BOOL CImPanel::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if( m_bUseRectTracker )
	{
		if(m_tracker.SetCursor(pWnd, nHitTest))
		{
			HCURSOR hCursor = NULL;
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


};


void im::CImPanel::SetROIEnable(bool bSet)
{
	m_bROIEnble = bSet;
}

void im::CImPanel::SetUseRectTracker(BOOL bUse)
{
	m_bUseRectTracker = bUse;
}


// hcpak tracker로 모델 등록
void im::CImPanel::SetRectTrackerScreen(CRect modelRect)
{
	m_tracker.m_rect = modelRect;
}


CRect im::CImPanel::GetRectTrackerScreen(void)
{
	return m_tracker.m_rect;
}


CRect im::CImPanel::GetviewSize(void)
{
	CRect clientRect;
	GetClientRect(clientRect);
	return clientRect;
}


void im::CImPanel::SetRectTrackerImage(CRect modelrect)
{
	CPoint tl = modelrect.TopLeft();
	CPoint br = modelrect.BottomRight();

	CPoint tl_s = ImagePosToScreenPos(tl);
	CPoint br_s = ImagePosToScreenPos(br);

	m_tracker.m_rect = CRect(tl_s,br_s);
}


CRect im::CImPanel::GetRectTrackerImage(void)
{
	CPoint tl = m_tracker.m_rect.TopLeft();
	CPoint br = m_tracker.m_rect.BottomRight();

	CPoint tl_i = ScreenPosToImagePos(tl);
	CPoint br_i = ScreenPosToImagePos(br);

	return CRect(tl_i,br_i);
}


void im::CImPanel::OnEditZoomIn()
{
	AfxMessageBox("abc");
}
