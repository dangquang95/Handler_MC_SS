#include "StdAfx.h"
#include "ImAdvPanel.h"

namespace im
{

CImAdvPanel::CImAdvPanel(void)
{
	m_iCurItemType = -1;

	m_iCurROIIdx = -1;
	m_iCurPointIdx = -1;
	m_iCurCrossIdx = -1;
}


CImAdvPanel::~CImAdvPanel(void)
{
}

BEGIN_MESSAGE_MAP(CImAdvPanel, CImPanel)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONUP()
	ON_COMMAND(POPUP_MENU_ID, CImPanel::OnEditZoomIn)
END_MESSAGE_MAP()


void CImAdvPanel::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPoint ptClk = ScreenPosToImagePos(point);

	switch( m_iCurItemType )
	{
	case imROI:
		{
		if( m_iCurROIIdx<0 || m_iCurROIIdx>=MAX_ITEM ) return;
		if( m_ROI[m_iCurROIIdx].bFixedPos ) return;

		CRect rect;
		
		rect.left = ptClk.x - m_ROI[m_iCurROIIdx].rect.Width()/2;
		rect.right = ptClk.x + m_ROI[m_iCurROIIdx].rect.Width()/2;
		rect.top = ptClk.y - m_ROI[m_iCurROIIdx].rect.Height()/2;
		rect.bottom = ptClk.y + m_ROI[m_iCurROIIdx].rect.Height()/2;

		if( rect.left<0 ) 
		{
			rect.left = 0;
			rect.right = rect.left + m_ROI[m_iCurROIIdx].rect.Width();
		}
		if( rect.top<0 )
		{
			rect.top = 0;
			rect.bottom = rect.top +  m_ROI[m_iCurROIIdx].rect.Height();
		}
		if( rect.right>m_iWidth )
		{
			rect.right = m_iWidth;
			rect.left = rect.right - m_ROI[m_iCurROIIdx].rect.Width();
		}
		if( rect.bottom>m_iHeight )
		{
			rect.bottom = m_iHeight;
			rect.top = rect.bottom - m_ROI[m_iCurROIIdx].rect.Height();
		}

		SetROI(m_iCurROIIdx, rect);
		}
		break;

	case imPOINT:
		{
		if( m_iCurPointIdx<0 || m_iCurPointIdx>=MAX_ITEM ) return;
		if( m_Point[m_iCurPointIdx].bFixedPos ) return;

		int size = m_Point[m_iCurPointIdx].iSize;
		SetPoint(m_iCurPointIdx, ptClk, size);
		}
		break;

	case imCROSS:
		{
		if( m_iCurCrossIdx<0 || m_iCurCrossIdx>=MAX_ITEM ) return;
		if( m_Cross[m_iCurCrossIdx].bFixedPos ) return;

		CSize size = m_Cross[m_iCurCrossIdx].size;

		if( ptClk.x-size.cx/2 < 0 )
		{
			ptClk.x = size.cx/2;
		}
		if( ptClk.y-size.cy/2 < 0 )
		{
			ptClk.y = size.cy/2;
		}
		if( ptClk.x+size.cx/2 > m_iWidth )
		{
			ptClk.x = m_iWidth - size.cx/2;
		}
		if( ptClk.y+size.cy/2 > m_iHeight )
		{
			ptClk.y = m_iHeight - size.cy/2;
		}

		SetCross(m_iCurCrossIdx, ptClk, size);
		}
		break;

	default:
		break;
	}
	
	UpdateDisplay();

	CImPanel::OnLButtonDown(nFlags, point);
}


void CImAdvPanel::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CImPanel::OnLButtonDblClk(nFlags, point);
}


BOOL im::CImAdvPanel::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int iStep=0;
	
	switch( m_iCurItemType )
	{
	case imROI:
		{
		if( m_iCurROIIdx<0 || m_iCurROIIdx>=MAX_ITEM ) return FALSE;
		if( m_ROI[m_iCurROIIdx].bFixedSize ) return FALSE;

		iStep = m_ROI[m_iCurROIIdx].iSizeStep;

		CRect rect = m_ROI[m_iCurROIIdx].rect;
		
		if( zDelta > 0 )
		{
			if( nFlags == MK_SHIFT )
			{
				rect.left -= iStep;
				rect.right += iStep;
			}
			else if( nFlags == MK_CONTROL )
			{
				rect.top -= iStep;
				rect.bottom += iStep;
			}
			else
			{
				rect.left -= iStep;
				rect.right += iStep;
				rect.top -= iStep;
				rect.bottom += iStep;
			}		
		}
		else if( zDelta < 0 )
		{
			if( nFlags == MK_SHIFT )
			{
				rect.left += iStep;
				rect.right -= iStep;
			}
			else if( nFlags == MK_CONTROL )
			{
				rect.top += iStep;
				rect.bottom -= iStep;
			}
			else
			{
				rect.left += iStep;
				rect.right -= iStep;
				rect.top += iStep;
				rect.bottom -= iStep;
			}	
		}

		if( rect.left<0 ) 
		{
			rect.left = 0;
			rect.right = rect.left + m_ROI[m_iCurROIIdx].rect.Width();
		}
		if( rect.top<0 )
		{
			rect.top = 0;
			rect.bottom = rect.top +  m_ROI[m_iCurROIIdx].rect.Height();
		}
		if( rect.right>m_iWidth )
		{
			rect.right = m_iWidth;
			rect.left = rect.right - m_ROI[m_iCurROIIdx].rect.Width();
		}
		if( rect.bottom>m_iHeight )
		{
			rect.bottom = m_iHeight;
			rect.top = rect.bottom - m_ROI[m_iCurROIIdx].rect.Height();
		}

		SetROI(m_iCurROIIdx, rect);
		}
		break;

	case imPOINT:
		{
		if( m_iCurPointIdx<0 || m_iCurPointIdx>=MAX_ITEM ) return FALSE;
		if( m_Point[m_iCurPointIdx].bFixedSize ) return FALSE;

		int iStep = m_Point[m_iCurPointIdx].iSizeStep;

		if( zDelta > 0 )
		{
			m_Point[m_iCurPointIdx].iSize += iStep;
		}
		else if( zDelta < 0 )
		{
			m_Point[m_iCurPointIdx].iSize -= iStep;
		}

		}
		break;

	case imCROSS:
		{
		if( m_iCurCrossIdx<0 || m_iCurCrossIdx>=MAX_ITEM ) return FALSE;
		if( m_Cross[m_iCurCrossIdx].bFixedSize ) return FALSE;

		int iStep = m_Cross[m_iCurCrossIdx].iSizeStep;
		CSize curSize = m_Cross[m_iCurCrossIdx].size;

		if(nFlags == MK_CONTROL)
		{
			if( zDelta > 0 )
			{
				m_Cross[m_iCurCrossIdx].size = CSize( curSize.cx+iStep, curSize.cy+iStep );
			}
			else if( zDelta < 0 )
			{
				m_Cross[m_iCurCrossIdx].size = CSize( curSize.cx-iStep, curSize.cy-iStep );
			}
		}
		}
		break;

	default:
		break;
	}

	UpdateDisplay();

	return CImPanel::OnMouseWheel(nFlags, zDelta, pt);
}

void im::CImAdvPanel::OnRButtonUp(UINT nFlags, CPoint point)
{
	//return;//atk
	/*CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING,POPUP_MENU_ID,_T("Zoom In"));
	
	CPoint pos;
	GetCursorPos(&pos);

	menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pos.x,pos.y,this);

	menu.DestroyMenu();*/
	c_point = ScreenPosToImagePos(point);
	CImPanel::OnRButtonUp(nFlags, point);
}

};
