#pragma once
class ImgProcUtil
{
public:
	ImgProcUtil(void);
	~ImgProcUtil(void);

	typedef enum{BLACK=0,WHITE=255};

	/* Line */
	cv::Point2d		LinePtByX(cv::Vec4f line, double x);	
	cv::Point2d		LinePtByY(cv::Vec4f line, double y);	/* */

	cv::Vec4f		LineFrom2Pt(cv::Point2d pt1, cv::Point2d pt2);	/*  */
	cv::Point2d		LineIntersectPt(cv::Vec4f line, cv::Point2d pt);	/*  */
	cv::Point2d		LineIntersectPt(cv::Vec4f line1, cv::Vec4f line2);	/* ê */

	double			LinePtDist(cv::Vec4f line, cv::Point2d pt);	/*  */
	double			LineAngle_rad(cv::Vec4f line);	/*  */
	double			LineAngle_deg(cv::Vec4f line);	/*  */
	
	cv::Point2d		PtFromLineByDist(cv::Vec4f line, cv::Point2d ptInLine, double dist);	/*  */

	cv::Point2d		InterpolationPtByX(cv::Point2d pt1, cv::Point2d pt2, double x);	/* */
	cv::Point2d		InterpolationPtByY(cv::Point2d pt1, cv::Point2d pt2, double y);	/* */

	cv::Vec3d		VecCrossProduct(cv::Vec3d a, cv::Vec3d b);	/*  */
	double			VecSize(cv::Vec3d vec);	/*  */

	cv::Point2d		RotatePt(cv::Point2d pt, cv::Point2d center, double deg);	/*  */

	/* Pixel */
	uchar			SubPixelValue(cv::Mat & srcImg, cv::Point2d pt);	/* Sub Pixel  */
	uchar			GetPixel(cv::Mat & srcImg, cv::Point pt);	/* */
	void			SetPixel(cv::Mat & srcImg, cv::Point pt, uchar value);	/*  */
	cv::Vec3b		GetPixel3C(cv::Mat & srcImg, cv::Point pt);	/* */
	void			SetPixel3C(cv::Mat & srcImg, cv::Point pt, cv::Vec3b value);	/*  */

	/* Point */	
	cv::Point2d		CenterPt(cv::Point2d pt1, cv::Point2d pt2);	/*  */
	double			PtDist(cv::Point2d pt1, cv::Point2d pt2);	/*  */
	BOOL			IsPtInside(cv::Point & pt, cv::Rect & areaRect);	/* */
	BOOL			IsPtInside(cv::Point & pt, cv::Mat & mat);	/* */

	/* Rect */
	cv::Rect		EnlargeRect(cv::Rect & rect, int iX, int iY);	/*  */
	cv::Rect		ReduceRect(cv::Rect & rect, int iX, int iY);	/*  */
	cv::Rect		EnlargeRect(cv::Rect & rect, int iT, int iB, int iL, int iR);	/*  */
	cv::Rect		ReduceRect(cv::Rect & rect, int iT, int iB, int iL, int iR);	/*  */
	cv::Rect		MultiplyRect(cv::Rect & rect, double m);	/* */
	cv::Rect		RotateRect(cv::Rect & rect, double angle);	/* */
	cv::Point2d		RectCenter(cv::Rect & rect);	/*  */
	cv::Rect		AdjustRect(cv::Rect & rect, cv::Size & size, BOOL bFixedSize);	/*  */

	BOOL			IsRectInside(cv::Rect & rect, cv::Rect & areaRect);	/*  */
	BOOL			IsRectInside(cv::Rect & rect, cv::Mat & mat);	/*  */
	BOOL			IsRectOutside(cv::Rect & rect, cv::Rect & areaRect);	/*  */

	/**/
	cv::Mat			EnlargeImg(cv::Mat & img, int iX, int iY,uchar fillValue=0);	/*  */
	cv::Mat			ReduceImg(cv::Mat & img, int iX, int iY);	/*  */
	typedef enum Rotate{ROT0=0,ROT90,ROT180,ROT270};
	cv::Mat			RotateImg(cv::Mat & img, int iFlag);	/*  */
	cv::Point2d		ImgCenter(cv::Mat & srcImg);	/*  */
	cv::Mat			ShiftImg(cv::Mat & srcImg, int iX, int iY);	/*  */

	/**/
	cv::Scalar		RandomColor(cv::RNG & rng);
	void			OverlayLineImg(cv::Mat & srcImg, cv::Mat & lineImg, cv::Scalar color); 
	void			OverlayLineImgOffset(cv::Mat & srcImg, cv::Mat & lineImg, cv::Scalar color, cv::Point offset); 	
	void			DrawCross(cv::Mat & img, cv::Point center, int len, cv::Scalar color, int thickness);
	void			DrawDiamond(cv::Mat & img, cv::Point center, int len, cv::Scalar color, int thickness);
	void			DrawRect(cv::Mat & img, cv::Point center, int len, cv::Scalar color, int thickness);
	void			DrawCircle(cv::Mat & img, cv::Point center, int radius, cv::Scalar color, int thickness);
	void			DispImg(std::string name, const cv::Mat & img, double ratio);
	void			SaveImg(std::string name, const cv::Mat & img, double ratio);

	/* Contour */
	cv::Point2d     GetMassCenterContour(std::vector<cv::Point>& contour);
	void			LargestContourImg(cv::Mat& src, std::vector<cv::Point>& contour, cv::Point2d& pMassCenter, cv::Mat& dst);
	void			FindContours(cv::Mat& src,cv::Mat& contourImg, std::vector<std::vector<cv::Point>>& contour, std::vector<cv::Rect>& vbndRect,  double dMinW, double dMaxW, double dMinH, double dMaxH, double dminArea, double dmaxArea);
	std::vector<cv::Point>	ConvexHull(std::vector<cv::Point> &contour);
	/* Transform */
	void			BitwiseGray(cv::Mat& src, cv::Mat &dst);
};

