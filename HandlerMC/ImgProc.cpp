#include "stdafx.h"
#include "ImgProc.h"

ImgProc::ImgProc()
{

}
ImgProc::~ImgProc()
{

}

void ImgProc::BrightEqualize(cv::Mat InImg, cv::Mat& OutImg, int iMin, int iMax)
{
	cv::Mat ProcImg;
	if(InImg.channels() == 3)
	{
		cv::cvtColor(InImg, ProcImg, CV_BGR2GRAY);
	}
	else
	{
		ProcImg = InImg.clone();
	}
	cv::Mat ResultImg = ProcImg.clone();
	ResultImg = 0;

	int iCh = ProcImg.channels();

	int i, j;
	int iWidth = ProcImg.cols;
	int iHeight = ProcImg.rows;
	int iMaxVal = 0;
	int iMinVal = 99999;
	int iPixel;
	for(i=0; i<iHeight; i++)
	{
		for(j=0; j<iWidth; j++)
		{
			iPixel = ProcImg.at<uchar>(i, j);
			if(iMaxVal < iPixel)
			{
				iMaxVal = iPixel;
			}
			if(iMinVal > iPixel)
			{
				iMinVal = iPixel;
			}
		}
	}

	for(i=0; i<iHeight; i++)
	{
		for(j=0; j<iWidth; j++)
		{
			iPixel = (int)(ProcImg.at<uchar>(i, j)*((double)(iMax-iMin)/(double)(iMaxVal-iMinVal)));
			if(iPixel <= 0)
			{
				ResultImg.at<uchar>(i, j) = 0;
			}
			else if(iPixel >= 255)
			{
				ResultImg.at<uchar>(i, j) = 255;
			}
			else
			{
				ResultImg.at<uchar>(i, j) = iPixel;
			}
		}
	}
	OutImg = ResultImg.clone();	
}

BOOL ImgProc::ImageProcess(cv::Mat InImg, cv::Mat& OutImg)
{
	cv::Mat resImg, resImgIn, resImgOut;
	OutImg = InImg.clone();
	cvtColor(OutImg, OutImg, CV_GRAY2BGR);

	resImg = InImg.clone();
	resImg = 0;

	utSaveImg("srcImg.bmp", InImg);

	if (!InsideProcess(InImg, resImgIn, m_ImgParam[0])||!OutsideProcess(InImg, resImgOut, m_ImgParam[1]))
		return FALSE;

	resImg = resImgIn + resImgOut;
	utSaveImg("resImg.bmp", resImg);

	std::vector<std::vector<cv::Point>> vInsideContour;
	std::vector<cv::Rect> vbndRect;
	Ut.FindContours(resImg, resImg, vInsideContour,vbndRect,0,200000,0,200000,0,200000);
	int iNumDefect = vbndRect.size();
	for (int i=0; i<iNumDefect; i++)
	{
		cv::rectangle(OutImg, vbndRect[i], cv::Scalar(0,0,255), 3, 8);
	}
	utSaveImg("finalImg.bmp", OutImg);

	m_iDefect = iNumDefect;
	m_OutImg = OutImg.clone();

	return TRUE;
}

BOOL ImgProc::InsideProcess(cv::Mat InImg, cv::Mat& ResultImg, ImgProcParam m_ImgParam)
{
	cv::Mat ProcImg;
	if (InImg.empty()) return FALSE;

	if(InImg.channels() == 3) cv::cvtColor(InImg, ProcImg, CV_BGR2GRAY);
	else
	{
		ProcImg = InImg.clone();
		//OutImg = InImg.clone();
		//cv::cvtColor(InImg, OutImg, CV_GRAY2BGR);
	}
	ResultImg = ProcImg.clone();
	ResultImg = 0;

	cv::Scalar mean = cv::mean(ProcImg); 
	if (mean[0]>220 || mean[0]<15) return FALSE;   // Have no jig or no light

	cv::Mat bitgrayImg;
	Ut.BitwiseGray(ProcImg, bitgrayImg);
	utSaveImg("0_Inbitgray.bmp", bitgrayImg);
	
	cv::Mat blurImg;
	cv::blur(bitgrayImg, blurImg, cv::Size(3,3));
	utSaveImg("1_InblurImg.bmp", blurImg);

	cv::Mat binImg;
	cv::adaptiveThreshold(blurImg, binImg, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 51, 10);
	utSaveImg("2_InadaptiveImg.bmp", binImg);

	cv::Mat andImg;
	cv::bitwise_and(blurImg, binImg, andImg);
	utSaveImg("3_InandImg.bmp", andImg);

	cv::threshold(andImg, binImg, 50, 255, CV_THRESH_BINARY_INV);
	utSaveImg("4_InbinImg.bmp", binImg);

	std::vector<std::vector<cv::Point>> vDefect;
	std::vector<cv::Point> contour;
	cv::Point2d pCenter;
	cv::Mat contourImg;
	Ut.LargestContourImg(binImg, contour, pCenter, contourImg);
	int l = m_ImgParam.iL;
	int r = m_ImgParam.iR;
	int b = m_ImgParam.iB;
	int t = m_ImgParam.iT;

	if(pCenter.x < l || pCenter.x > r || pCenter.y < t || pCenter.y > b) return FALSE; // Have no nozzle

	cv::Rect bndRect = cv::boundingRect(contour);
	bndRect = Ut.ReduceRect(bndRect, 25, 25);

	if(!Ut.IsRectInside(bndRect, binImg)) return FALSE;

	int offsetX = bndRect.x;
	int offsetY = bndRect.y;

	cv::Mat tmpImg = binImg(bndRect).clone();
	tmpImg = ~tmpImg;
	utSaveImg("5_IntmpImg.bmp", tmpImg);

	cv::Mat tmpContourImg;
	Ut.LargestContourImg(tmpImg, contour, pCenter, tmpContourImg);
	std::vector<std::vector<cv::Point>> vVHull;
	std::vector<cv::Point> vHull;
	vHull = Ut.ConvexHull(contour);
	vVHull.push_back(vHull);
	cv::drawContours(tmpContourImg,vVHull,-1,cv::Scalar(255,255,255),CV_FILLED);
	utSaveImg("6_IntmpConvexhull.bmp", tmpContourImg);

	cv::Mat andImg2;
	andImg2 = tmpContourImg - tmpImg;
	utSaveImg("7_InandImg2.bmp", andImg2);

	cv::Mat morphImg;
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3));
	cv::erode(andImg2, morphImg, kernel, cv::Point(-1,-1), 1);
	utSaveImg("8_InmophorImg.bmp", morphImg);

	morphImg.copyTo(ResultImg(bndRect));

	double dminW = m_ImgParam.dminW;
	double dmaxW = m_ImgParam.dmaxW;
	double dminH = m_ImgParam.dminH;
	double dmaxH = m_ImgParam.dmaxH;
	double dminA = m_ImgParam.dminA;
	double dmaxA = m_ImgParam.dmaxA;

	std::vector<std::vector<cv::Point>> vInsideContour;
	std::vector<cv::Rect> vbndRect;

	Ut.FindContours(ResultImg,ResultImg, vInsideContour,vbndRect,dminW,dmaxW,dminH,dmaxH,dminA,dmaxA);
	
	return TRUE;
}

BOOL ImgProc::OutsideProcess(cv::Mat InImg, cv::Mat& ResultImg, ImgProcParam m_ImgParam)
{
	cv::Mat ProcImg;
	if (InImg.empty()) return FALSE;

	if(InImg.channels() == 3) cv::cvtColor(InImg, ProcImg, CV_BGR2GRAY);
	else
	{
		ProcImg = InImg.clone();
		//OutImg = InImg.clone();
		//cv::cvtColor(InImg, OutImg, CV_GRAY2BGR);
	}
	ResultImg = ProcImg.clone();
	ResultImg = 0;

	cv::Scalar mean = cv::mean(ProcImg); 
	if (mean[0]>220 || mean[0]<15) return FALSE;   // Have no jig or no light

	cv::Mat bitgrayImg;
	Ut.BitwiseGray(ProcImg, bitgrayImg);
	utSaveImg("0_Outbitgray.bmp", bitgrayImg);

	cv::Mat blurImg;
	cv::blur(bitgrayImg, blurImg, cv::Size(3,3));
	utSaveImg("1_OutblurImg.bmp", blurImg);

	cv::Mat binImg;
	cv::adaptiveThreshold(blurImg, binImg, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 51, 20);
	utSaveImg("2_OutadaptiveImg.bmp", binImg);

	cv::Mat andImg;
	cv::bitwise_and(blurImg, binImg, andImg);
	utSaveImg("3_OutandImg.bmp", andImg);

	cv::threshold(andImg, binImg, 60, 255, CV_THRESH_BINARY_INV);
	utSaveImg("4_OutbinImg.bmp", binImg);

	cv::Mat morphBinImg;
	cv::Mat kernel0 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
	cv::morphologyEx(binImg,morphBinImg,cv::MORPH_CLOSE,kernel0,cv::Point(-1,-1),6);
	//cv::morphologyEx(binImg,morphBinImg,cv::MORPH_OPEN,kernel0,cv::Point(-1,-1),5);
	//cv::erode(binImg, morphBinImg, kernel0, cv::Point(-1,-1), 1);
	utSaveImg("5_OutmophorBinImg.bmp", morphBinImg);
	
	std::vector<std::vector<cv::Point>> vDefect;
	std::vector<cv::Point> contour;
	cv::Point2d pCenter;
	cv::Mat contourImg; 

	Ut.LargestContourImg(morphBinImg, contour, pCenter, contourImg);
	int l = m_ImgParam.iL;
	int r = m_ImgParam.iR;
	int b = m_ImgParam.iB;
	int t = m_ImgParam.iT;

	if(pCenter.x < l || pCenter.x > r || pCenter.y < t || pCenter.y > b) return FALSE; // Have no nozzle

	cv::Rect bndRect = cv::boundingRect(contour);
	bndRect = Ut.EnlargeRect(bndRect, 25, 25);
	
	if(!Ut.IsRectInside(bndRect, binImg)) return FALSE;

	int offsetX = bndRect.x;
	int offsetY = bndRect.y;

	cv::Mat tmpImg = contourImg(bndRect).clone();
	utSaveImg("6_OuttmpImg.bmp", tmpImg);

	cv::Mat tmpContourImg;
	Ut.LargestContourImg(tmpImg, contour, pCenter, tmpContourImg);
	std::vector<std::vector<cv::Point>> vVHull;
	std::vector<cv::Point> vHull;
	vHull = Ut.ConvexHull(contour);
	vVHull.push_back(vHull);
	cv::drawContours(tmpContourImg,vVHull,-1,cv::Scalar(255,255,255),CV_FILLED);
	utSaveImg("7_OuttmpConvexhull.bmp", tmpContourImg);

	//cv::RotatedRect rotRect = cv::minAreaRect(contour);
	//cv::Point pt = Ut.GetMassCenterContour(contour);
	
	cv::Mat andImg2;
	andImg2 = tmpContourImg - tmpImg;
	utSaveImg("8_OutandImg2.bmp", andImg2);

	cv::Mat morphImg;
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
	cv::erode(andImg2, morphImg, kernel, cv::Point(-1,-1), 1);
	utSaveImg("9_OutmophorImg.bmp", morphImg);

	morphImg.copyTo(ResultImg(bndRect));

	double dminW = m_ImgParam.dminW;
	double dmaxW = m_ImgParam.dmaxW;
	double dminH = m_ImgParam.dminH;
	double dmaxH = m_ImgParam.dmaxH;
	double dminA = m_ImgParam.dminA;
	double dmaxA = m_ImgParam.dmaxA;

	std::vector<std::vector<cv::Point>> vInsideContour;
	std::vector<cv::Rect> vbndRect;

	Ut.FindContours(ResultImg,ResultImg, vInsideContour,vbndRect,dminW,dmaxW,dminH,dmaxH,dminA,dmaxA);
	return TRUE;
}

void ImgProc::utSaveImg(CString sName, cv::Mat &img)
{
	if( bProcImgSave )
	{
		CString sPath;
		sPath.Format(_T("%s\\%s"), m_sProcImgSavePath, sName);
		cv::imwrite((LPCTSTR)sPath, img);
	}
}

void ImgProc::PROCESS_VISION()
{
	if (!ImageProcess(m_SrcImg, m_OutImg))
	{
		m_iDefect = -1;
	}
	
}
