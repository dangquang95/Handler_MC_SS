#pragma once

#include "btnenh.h"
#include "afxwin.h"
#include "CameraCrevis.h"
//#include "CameraOmron.h"
#include "savedata.h"
#include "vision.h"
#include "IniFile.h"
#include "XmlNodeWrapper.h"
#include "MyDefine.h"
#include "ImagePanel.h"
#include "afxwin.h"
#include "ImPanel.h"
#include "ImAdvPanel.h"
// VisionDlg dialog

using namespace xml;
class VisionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VisionDlg)

public:
	VisionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~VisionDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickExit1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	void ClickMoveVisionTool1();
	void ClickMoveVisionTool2();
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnBnClickedBtnStart();
//	afx_msg void OnBnClickedBtnApply();
//	afx_msg void OnBnClickedBtnPlay();
//	afx_msg void OnBnClickedBtnStop();
//	afx_msg void OnBnClickedBtnGrab();
	afx_msg void OnBnClickedBtnLoadparma();
	afx_msg void OnBnClickedBtnSavepara();
	cv::Mat OpenImage(void);
	CEdit edt_min_area;
	CEdit edt_max_area;
	CEdit edt_min_width;
	CEdit edt_max_width;
	CEdit edt_min_height;
	CEdit edt_max_height;
	CButton check_erode_dilate;
	CButton check_dilate_erode;
	CButton check_erode;
	CButton check_dilate;
	CButton btn_process;
	CListBox lst_information;
	CButton btn_apply;
	CButton btn_loadparameter;
	CButton btn_start;
	CButton btn_play;
	CButton btn_stop;
	CButton btn_grab;
	CButton btn_savepara;

public: //Function

	void				unlockitem(CString unlock);
	void				information(CString information);
	appVision			*m_vision;
	saveDatatsystem		*m_savedata;
	BOOL				loadParameter(CString strPath, DataSystem &data_system);
	DataSystem			Data_system;
	cv::Rect			b_Rect;
	

public: //variable
	CString		passlock;
	CString		infor;
	void		showProcessImage();
	bool		b_UpdateData;
	
	int			tool_1;
	int			tool_2;
	int			contPlay;

	bool		b_showImage;
	static UINT		ThreadCamera(VOID* pParam);
	CDC			*m_pDlgMainViewStaticDC;
	CRect		m_DlgMainViewRect;


	CButton		check_process;

	CString		strShowImage;

	//initial
	BOOL			GetDataWidget(int iTool);
	BOOL			SetDataWidget(int itool);
	bool			b_threadUpdate;
	
	int				countResult;
	CButton check_process1;
	CButton check_reomveBlob;
	CEdit edt_rate;
	virtual BOOL DestroyWindow();
	CButton check_rate;
	int rad_tool_1;
	CEdit edt_offset_x;
	CEdit edt_offset_y;
	CEdit edt_offset_angle;
	CEdit edt_offset_y2;
	CEdit edt_offset_x2;
	CButton check_blur;
	CEdit edt_kSize_tool_1;
	CEdit edt_threshoold_tool_1;
	CEdit edt_threshold_tool_2;
	CEdit edt_kSize_tool_2;
	CEdit edt_morSize_tool_1;
	CEdit edt_morSize_tool_2;
	int rad_erode;
	int rad_dilate;
	int rad_erode_dilate;
	int rad_dilate_erode;
	CButton check_apply_morphology;
	CEdit edt_minArea;
	CEdit edt_maxArea;
	CButton check_remove_noise;
	CButton check_threshold;
	CEdit edt_angle_tool_2;
	int rad_tool_2;
	void ClickSave();
	int icurTool = TOOL_1;
//	afx_msg void OnBnClickedBtnGrab2();
	afx_msg void OnBnClickedRadTool1();
	afx_msg void OnBnClickedRadTool2();
	BOOL SaveParameters();

	BOOL LoadParameters();

	VisionPara			visionPara[2];
	masterPoint			refPoint[2];

	Mat					mPattern;
//	afx_msg void OnBnClickedBtnGrab2();
	void DisplayImage(im::CImAdvPanel & panel, cv::Mat & img);
	im::CImAdvPanel mPanel;
	afx_msg void OnBnClickedBtnLoad();
};
