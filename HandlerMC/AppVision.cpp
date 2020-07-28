#include "stdafx.h"
#include "vision.h"

appVision::appVision()
{
	m_iIterationNo = 1;

}
appVision::~appVision()
{
	
}
cv::Mat appVision::smooth(cv::Mat & image, int kSize)
{
	cv::Mat image_blur;
	cv::blur(image, image_blur, cv::Size(kSize, kSize));
	
	return image_blur;
}


cv::Mat appVision::binaryTh(cv::Mat image, double th_value)
{
	
	cv::Mat img;
	if (image.channels() == 1) {
		img = image.clone();
	}
	else {
		cv::cvtColor(image, img, CV_BGR2GRAY);
	}
			
	cv::threshold(img, img, th_value, 255, CV_THRESH_BINARY);
	return img;
}

cv::Mat appVision::morphologProc(cv::Mat & image, int morSize, int selectOP)
{

	cv::Mat img, img_e, img_d;
	cv::Mat kernel;
	kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(morSize, morSize));

	if (selectOP == 1) {
		cv::erode(image, image, kernel, cv::Point(-1, -1), 1);
	}
	else if (selectOP == 2) {
		cv::dilate(image, image, kernel, cv::Point(-1, -1), 1);
	}

	else if (selectOP == 3) {
		cv::erode(image, image, kernel, cv::Point(-1, -1), 1);
		cv::dilate(image, image, kernel, cv::Point(-1, -1), 1);
	}
	else if (selectOP == 4) {
		cv::dilate(image, image, kernel, cv::Point(-1, -1), 1);
		cv::erode(image, image, kernel, cv::Point(-1, -1), 1);
	}

	return image;
}
cv::Mat appVision::removeBolbAngle(cv::Mat image, int minArea, int maxArea, int minWidth, int maxWidth, int minHeight, int maxHeight)
{
	cv::Mat imagePro, imageOut;
	cv::Rect blobRect;
	imagePro = image.clone();
	imageOut = image.clone();
	imageOut = imageOut.setTo(0);

	//Find contours
	std::vector<std::vector<cv::Point> > contours;
	std::vector<std::vector<cv::Point> > result_contours;
	std::vector<cv::Vec4i> hierarchy;
	
	
	cv::RotatedRect rec;
	double x_angle;
	
	int iMode = CV_RETR_TREE;
	int iMethod = CV_CHAIN_APPROX_SIMPLE;
	cv::findContours(imagePro, contours, hierarchy, iMode, iMethod, cv::Point(0, 0));

	vector<cv::Moments> mu(contours.size());
	int iContourCnt = (int)contours.size();

	for (int i = 0; i < iContourCnt; i++)
	{
		int iContourArea = (int)cv::contourArea(contours[i]);
		rec = minAreaRect(contours[i]);
		mu[i] = moments(contours[i], false);
		

		if (minArea > 0 && iContourArea < minArea) continue;
		if (maxArea > 0 && iContourArea > maxArea) continue;

		blobRect = cv::boundingRect(contours[i]);


		if (minWidth > 0 && blobRect.width < minWidth) continue;
		if (minHeight > 0 && blobRect.height < minHeight) continue;
		if (maxWidth > 0 && blobRect.width > maxWidth) continue;
		if (maxHeight > 0 && blobRect.height > maxHeight) continue;

		p_center.x	= (mu[i].m10 / mu[i].m00);
		p_center.y	= (mu[i].m01 / mu[i].m00);
		x_angle		= rec.angle;
		areaContour = iContourArea;

		result_contours.push_back(contours[i]);
		if (x_angle < -45) {
			dRotAngle = 90 + x_angle;
		}
		if (x_angle >= -45) {
			dRotAngle = x_angle;
		}
	}
	

	cv::drawContours(imageOut, result_contours, -1, cv::Scalar(255), CV_FILLED);
	

	return imageOut;

}

void appVision::displayImage(cv::Mat image, CDC * pDC, CRect rect)
{
	{
		BITMAPINFO bitmapInfo;
		memset(&bitmapInfo, 0, sizeof(bitmapInfo));
		bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitmapInfo.bmiHeader.biPlanes = 1;
		bitmapInfo.bmiHeader.biCompression = BI_RGB;
		bitmapInfo.bmiHeader.biXPelsPerMeter = 0;
		bitmapInfo.bmiHeader.biYPelsPerMeter = 0;
		bitmapInfo.bmiHeader.biClrUsed = 0;
		bitmapInfo.bmiHeader.biClrImportant = 0;
		bitmapInfo.bmiHeader.biWidth = image.cols;
		bitmapInfo.bmiHeader.biHeight = -image.rows;

		if (image.channels() == 1) {
			cvtColor(image, image, CV_GRAY2BGR);
		}

		bitmapInfo.bmiHeader.biBitCount = 24;

		pDC->SetStretchBltMode(COLORONCOLOR);
		::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top, rect.right, rect.bottom, 0, 0, image.cols, image.rows, image.data, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	}
}

cv::Mat appVision::RotationImage(cv::Mat image)
{
	cv::Point p_center = cv::Point(image.cols / 2, image.rows / 2);
	cv::Mat r = cv::getRotationMatrix2D(p_center, -90, 1);

	cv::Mat aff_image;
	cv::warpAffine(image, aff_image, r, cv::Size(image.rows, image.cols));
	return aff_image;
}

cv::Mat appVision::drawImage(cv::Mat image)
{
	cv::Mat aff_image;
	aff_image = image.clone();

	cv::Scalar color = cv::Scalar(255, 255, 255);
	cv::Scalar color1 = cv::Scalar(0, 0, 255);
	//cv::Rect rect = cv::Rect(40, 40, aff_image.cols - 80, aff_image.rows - 80);
	//cv::rectangle(aff_image, rect, color, 2, 8);
	//// + 1
	//cv::Point pt1_1, pt1_2, pt1_3, pt1_4;
	//cv::Point pt2_1, pt2_2, pt2_3, pt2_4;
	//pt1_1 = cv::Point(aff_image.cols / 2 - 200, (aff_image.rows / 2) - 400);
	//pt1_2 = cv::Point(aff_image.cols / 2 + 200, (aff_image.rows / 2) - 400);
	//pt1_3 = cv::Point(aff_image.cols / 2, (aff_image.rows / 2 - 20) - 400);
	//pt1_4 = cv::Point(aff_image.cols / 2, (aff_image.rows / 2 + 20) - 400);

	//pt2_1 = cv::Point(aff_image.cols / 2 - 200, (aff_image.rows / 2) + 400);
	//pt2_2 = cv::Point(aff_image.cols / 2 + 200, (aff_image.rows / 2) + 400);
	//pt2_3 = cv::Point(aff_image.cols / 2, (aff_image.rows / 2 - 20) + 400);
	//pt2_4 = cv::Point(aff_image.cols / 2, (aff_image.rows / 2 + 20) + 400);

	//cv::line(aff_image, pt1_1, pt1_2, color, 4, 8); // ngang
	//cv::line(aff_image, pt1_4, pt1_3, color, 4, 8); // doc

	//cv::line(aff_image, pt2_1, pt2_2, color, 4, 8); // ngang
	//cv::line(aff_image, pt2_3, pt2_4, color, 4, 8); // doc

	return aff_image;
}

BOOL appVision::ShowAlignTest(Mat mInput, Mat & mOutput, VisionPara vPara, double & dX, double & dY, float & anpha, RotatedRect & rotRect)
{
	if (mInput.empty())
	{
		return FALSE;
	}

	if (mInput.channels() != 1)
	{
		cvtColor(mInput, mInput, CV_BGR2GRAY);
		//return FALSE;
	}
	cv::Mat mBlur, mBin;
	cv::blur(mInput, mBlur, cv::Size(vPara.iBlur, vPara.iBlur));
	inRange(mBlur, vPara.iThresh, 255, mBin);
	//imwrite("mBin.jpg", mBin);
	//threshold(mBlur, mBin, vPara.iThreshLeft, 255, CV_THRESH_OTSU);
	Mat melement = getStructuringElement(MORPH_ERODE, cv::Size(3, 3));
	erode(mBin, mBin, melement, Point(-1, -1), 3);

	vector<vector<Point> > contours;
	vector<vector<Point> > result_contours;
	vector<Vec4i> hierarchy;

	// find contours
	Mat mBinRo = mBin.clone();

	cv::findContours(mBin, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	if (contours.size() == 0)
	{
		return TRUE;
	}
	// drawContours

	cv::Rect blobRect;
	int filterWidthMin, filterHeightMin, filterWidthMax, filterHeightMax = 0;

	filterWidthMin = 200;
	filterHeightMin = 200;
	filterWidthMax = -1;
	filterHeightMax = -1;

	for (int i = 0; i < (int)contours.size(); i++)
	{

		blobRect = cv::boundingRect(contours[i]);
		if (blobRect.width < filterWidthMin && blobRect.width > filterWidthMax) continue;
		if (blobRect.height < filterHeightMin && blobRect.height > filterHeightMax) continue;

		result_contours.push_back(contours[i]);
	}
	if (result_contours.size() == 0)
	{
		return false;
	}
	int idx, imax = 0;
	for (int i = 0; i < result_contours.size(); i++)
	{
		if (contourArea(result_contours[i]) > imax) {
			imax = contourArea(result_contours[i]);
			idx = i;
		}

	}
	vector<Rect> boudingRect(result_contours.size());
	Mat M, rotated, cropped;
	RotatedRect rect;
	int dX_1, dY_1;

	// rect is the RotatedRect
	rect = cv::minAreaRect(Mat(result_contours[idx]));
	rotRect = rect;
	dX_1 = rotRect.center.x;
	dY_1 = rotRect.center.y;
	// get angle and size from the bounding box

	//float angle = rect.angle;
	Size rect_size = rect.size;
	Point2f rect_points[4];
	rect.points(rect_points);
	// thanks for http://felix.abecassis.me/2011/10/opencv-rotation-deskewing/
	if (rect.angle < -45.) {
		rect.angle += 90.0;
		swap(rect_size.width, rect_size.height);
	}
	anpha = rect.angle;

	//after Rotation
	cv::Point p_center = cv::Point(dX_1, dY_1);
	cv::Mat r = cv::getRotationMatrix2D(p_center, anpha, 1);

	cv::Mat aff_image;
	cv::warpAffine(mBinRo, aff_image, r, cv::Size(mBinRo.rows, mBinRo.cols));
	//imwrite("mRot.jpg", aff_image);
	vector<vector<Point> > contours_1;
	vector<vector<Point> > result_contours_1;
	vector<Vec4i> hierarchy_1;

	cv::findContours(aff_image, contours_1, hierarchy_1, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	if (contours.size() == 0)
	{
		return TRUE;
	}

	cv::Rect blobRect_1;
	int filterWidthMin_1, filterHeightMin_1, filterWidthMax_1, filterHeightMax_1 = 0;

	filterWidthMin_1 = 200;
	filterHeightMin_1 = 200;
	filterWidthMax_1 = -1;
	filterHeightMax_1 = -1;

	for (int i = 0; i < (int)contours_1.size(); i++)
	{

		blobRect = cv::boundingRect(contours_1[i]);
		if (blobRect.width < filterWidthMin_1 && blobRect.width > filterWidthMax_1) continue;
		if (blobRect.height < filterHeightMin_1 && blobRect.height > filterHeightMax_1) continue;

		result_contours_1.push_back(contours_1[i]);
	}
	if (result_contours_1.size() == 0)
	{
		return false;
	}
	int idx_1 = 0;
	int imax_1 = 0;
	for (int i = 0; i < result_contours_1.size(); i++)
	{
		if (contourArea(result_contours_1[i]) >= imax) {
			imax_1 = contourArea(result_contours_1[i]);
			idx_1 = i;
		}

	}
	//vector<Rect> boudingRect_1(result_contours_1.size());
	//Mat M, rotated, cropped;
	cv::Rect rect_1;

	// rect is the RotatedRect
	
		rect_1 = cv::boundingRect(result_contours_1[idx_1]);
		dX = rect_1.tl().x;
		dY = rect_1.tl().y;
	
	
	//dX = rect_1.
	//rotRect = rect_1;
	/*dX = rotRect.center.x;
	dY = rotRect.center.y;*/
	/*Point2f tmpLeft, tmpRight, tmpTop, tmpTopR, tmpBott, tmpBottR;
	vector<Point> cnt;
	for (int i = 0; i < result_contours.size(); ++i)
	{
		cnt = result_contours[i];
		tmpLeft.x = 1000;
		tmpRight.x = -1000;
		tmpTop.y = 1000;
		tmpTopR.y = 1000;
		tmpBott.y = -1000;
		tmpBottR.y = -1000;
		for (size_t j = 0; j < cnt.size(); ++j)
		{
			Point current = cnt[j];
			if (current.x < tmpLeft.x) {
				tmpLeft = current;
			}
			if (current.x > tmpRight.x) {
				tmpRight = current;
			}
			if (current.y < tmpTop.y) {
				tmpTop = current;
			}
			if (current.y > tmpBott.y) {
				tmpBott = current;
			}
			int delta1 = current.y - tmpTop.y;
			int delta2 = current.y - tmpBott.y;
			if (delta1 > 0 && delta1 == 5) {
				tmpTopR = current;
			}
			if (delta2 < 0 && delta2 == -1) {
				tmpBottR = current;
			}
		}
	}
	dX = tmpRight.x;
	dY = tmpTopR.y;*/
	
	return true;
}




