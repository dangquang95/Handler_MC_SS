#pragma once
#include "impanel.h"

namespace im
{
	enum imITEMTYPE
	{
		imROI=0,
		imPOINT,
		imCROSS
	};

class CImAdvPanel : public CImPanel
{
public:
	CImAdvPanel(void);
	~CImAdvPanel(void);

	int m_iCurItemType;

	int m_iCurROIIdx;
	int m_iCurPointIdx;
	int m_iCurCrossIdx;

	void SetCurType(int type) {m_iCurItemType=type;};

	void SetCurROIIdx(int idx) {m_iCurROIIdx=idx;};
	void SetCurPointIdx(int idx) {m_iCurPointIdx=idx;};
	void SetCurCrossIdx(int idx) {m_iCurCrossIdx=idx;};

	void SetROIInfo(int idx, ImROI info) {m_ROI[idx]=info;};
	void SetPointInfo(int idx, ImPoint info) {m_Point[idx]=info;};
	void SetCrossInfo(int idx, ImCross info) {m_Cross[idx]=info;};

	void SetROI(int idx, CRect rect) {m_ROI[idx].rect=rect;};
	void SetPoint(int idx, CPoint pt, int size) {m_Point[idx].pt=pt; m_Point[idx].iSize=size;};
	void SetCross(int idx, CPoint pt, CSize size) {m_Cross[idx].pt=pt; m_Cross[idx].size=size;};

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

public:
	CPoint c_point;
};

};

