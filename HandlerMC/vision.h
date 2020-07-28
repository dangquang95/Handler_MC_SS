#pragma once
#include "stdafx.h"
#include "afxwin.h"
#include "opencv2\opencv.hpp"
#pragma comment(lib, "opencv_world330d.lib")



class appVision
{
public:
	appVision();
	~appVision();
public:
	int		m_iIterationNo;

public:
	cv::Mat		smooth(cv::Mat & image, int kSize);
	cv::Mat		binaryTh(cv::Mat image, double th_value);
	cv::Mat		morphologProc(cv::Mat & image, int morSize, int selectOP);
	cv::Mat		removeBolbAngle(cv::Mat image, int minArea, int maxArea, int minWidth, int maxWidth, int minHeight, int maxHeight);

public:
	void		displayImage(cv::Mat image, CDC *pDC, CRect rect);
	CDC			*m_pDlgMainViewStaticDC;
	CRect		m_DlgMainViewRect;
	cv::Mat		RotationImage(cv::Mat image);
	cv::Mat		drawImage(cv::Mat image);
	BOOL		ShowAlignTest(Mat mInput, Mat & mOutput, VisionPara vPara, double & dX, double & dY, float & anpha, RotatedRect & rotRect);
	cv::Point	p_center;
	double		dRotAngle;
	int			areaContour;

};
