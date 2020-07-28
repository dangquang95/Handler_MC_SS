#pragma once 

class ImgProc
{
public:
	ImgProc(void);
	~ImgProc(void);

public:

	typedef struct ImgProcParam
	{
		int iL, iR, iB, iT;
		double dminW, dmaxW, dminH, dmaxH, dminA, dmaxA;
	};
	ImgProcUtil Ut;
	ImgProcParam m_ImgParam[2];
	void BrightEqualize(cv::Mat InImg, cv::Mat& OutImg, int iMin, int iMax);


	// 171202 Nozzle
	CString m_sProcImgSavePath;
	cv::Mat m_SrcImg;
	cv::Mat m_OutImg;
	int m_iDefect;
	BOOL bProcImgSave;

	inline void SetSrcImg(const cv::Mat &img){m_SrcImg = img;}
	inline void SetProcImgSavePath(CString sPath) {m_sProcImgSavePath = sPath;}
	inline cv::Mat GetOutImg(){return m_OutImg;}
	inline int GetNumDefect(){return m_iDefect;}

	BOOL ImageProcess(cv::Mat InImg, cv::Mat& OutImg);
	BOOL InsideProcess(cv::Mat InImg, cv::Mat& OutImg, ImgProcParam m_ImgParam);
	BOOL OutsideProcess(cv::Mat InImg, cv::Mat& OutImg, ImgProcParam m_ImgParam);
	void PROCESS_VISION();

	void utSaveImg(CString nameimg, cv::Mat &img);
};