#include "StdAfx.h"
#include "ImgProcUtil.h"


ImgProcUtil::ImgProcUtil(void)
{
}


ImgProcUtil::~ImgProcUtil(void)
{
}

cv::Point2d ImgProcUtil::LinePtByX(cv::Vec4f line, double x)
{
	double vx = line.val[0];
	double vy = line.val[1];
	double x0 = line.val[2];
	double y0 = line.val[3];

	if(vx==0.0f) vx=0.00001f;
	double y = (vy * (x-x0)/vx) + y0;	

	return cv::Point2d(x,y);
}

cv::Point2d ImgProcUtil::LinePtByY(cv::Vec4f line, double y)
{
	double vx = line.val[0];
	double vy = line.val[1];
	double x0 = line.val[2];
	double y0 = line.val[3];

	if(vy==0.0f) vy=0.00001f;
	double x = (vx * (y-y0)/vy) + x0;	

	return cv::Point2d(x,y);
}

cv::Vec4f ImgProcUtil::LineFrom2Pt(cv::Point2d pt1, cv::Point2d pt2)
{
	double dx = pt2.x - pt1.x;
	double dy = pt2.y - pt1.y;
	double vx = dx/sqrt(dx*dx+dy*dy);
	double vy = dy/sqrt(dx*dx+dy*dy);
	
	cv::Vec4f line = (cv::Vec4f)cv::Vec4d(vx,vy,pt1.x,pt1.y);

	return line;
}

cv::Point2d ImgProcUtil::LineIntersectPt(cv::Vec4f line, cv::Point2d pt)
{
	double vx1 = line[0];
	double vy1 = line[1];
	double x1 = line[2];
	double y1 = line[3];

	double vx2 = 1/vx1;
	double vy2 = -1/vy1;
	double x2 = pt.x;
	double y2 = pt.y;

	double x = (vy1*x1/vx1 - vy2*x2/vx2 + y2 - y1) / (vy1/vx1 - vy2/vx2);
	double y = (vx1*y1/vy1 - vx2*y2/vy2 + x2 - x1) / (vx1/vy1 - vx2/vy2);

	return cv::Point2d(x,y);
}

cv::Point2d ImgProcUtil::LineIntersectPt(cv::Vec4f line1, cv::Vec4f line2)
{
	double x1 = line1[2];
	double y1 = line1[3];
	double u1 = line1[0];
	double u2 = line1[1];

	if(u1==0.0) u1=0.000000000001;
	if(u2==0.0) u2=0.000000000001;

	double x2 = line2[2];
	double y2 = line2[3];
	double v1 = line2[0];
	double v2 = line2[1];

	if(v1==0.0) v1=0.000000000001;
	if(v2==0.0) v2=0.000000000001;

	double x = (u2*x1/u1 - v2*x2/v1 + y2 - y1) / (u2/u1 - v2/v1);
	double y = (u1*y1/u2 - v1*y2/v2 + x2 - x1) / (u1/u2 - v1/v2);

	return cv::Point2d(x,y);
}

double ImgProcUtil::LinePtDist(cv::Vec4f line, cv::Point2d pt)
{
	double vx = line.val[0];
	double vy = line.val[1];
	double x0 = line.val[2];
	double y0 = line.val[3];

	cv::Point3d A(pt.x,pt.y,0);
	cv::Point3d P(x0,y0,0);
	cv::Vec3d PA = P-A;
	cv::Vec3d u(vx,vy,0);
	cv::Vec3d PAu = VecCrossProduct(PA,u);

	double d = VecSize(PAu)/VecSize(u);

	return d;
}

double ImgProcUtil::LineAngle_rad(cv::Vec4f line)
{
	double vx = line.val[0];
	double vy = line.val[1];
	double x0 = line.val[2];
	double y0 = line.val[3];

	double rad = atan2( vy, vx );

	return rad;
}

double ImgProcUtil::LineAngle_deg(cv::Vec4f line)
{
	double vx = line.val[0];
	double vy = line.val[1];
	double x0 = line.val[2];
	double y0 = line.val[3];

	double rad = atan2( vy, vx );
	double deg = RAD2DEG(rad);

	return deg;
}

cv::Point2d ImgProcUtil::PtFromLineByDist(cv::Vec4f line, cv::Point2d ptInLine, double dist)
{
	double vx = line.val[0];
	double vy = line.val[1];

	double x = ptInLine.x;
	double y = ptInLine.y;

	cv::Point2d pt( dist*vx+x, dist*vy+y );
	return pt;
}

cv::Point2d ImgProcUtil::InterpolationPtByX(cv::Point2d pt1, cv::Point2d pt2, double x)
{
	cv::Point2d intpPt( (pt1.x+pt2.x)/2.0, (pt1.y+pt2.y)/2.0 );

	double a = (pt2.y-pt1.y)/(pt2.x-pt1.x);
	double b = pt1.y - a*pt1.x;

	double y = a*x+b;

	intpPt.x = x;
	intpPt.y = y;

	return intpPt;
}

cv::Point2d ImgProcUtil::InterpolationPtByY(cv::Point2d pt1, cv::Point2d pt2, double y)
{
	cv::Point2d intpPt( (pt1.x+pt2.x)/2.0, (pt1.y+pt2.y)/2.0 );

	double a = (pt2.y-pt1.y)/(pt2.x-pt1.x);
	double b = pt1.y - a*pt1.x;

	double x = (y - b)/a;

	intpPt.x = x;
	intpPt.y = y;

	return intpPt;
}

cv::Vec3d ImgProcUtil::VecCrossProduct(cv::Vec3d a, cv::Vec3d b)
{
	double a1 = a.val[0];
	double a2 = a.val[1];
	double a3 = a.val[2];

	double b1 = b.val[0];
	double b2 = b.val[1];
	double b3 = b.val[2];

	cv::Vec3d ret( a2*b3-a3*b2, -(a1*b3-a3*b1), a1*b2-a2*b1 );
	return ret;
}

double ImgProcUtil::VecSize(cv::Vec3d vec)
{
	double a = vec.val[0];
	double b = vec.val[1];
	double c = vec.val[2];

	double size = sqrt( a*a+b*b+c*c );

	return size;
}

cv::Point2d ImgProcUtil::RotatePt(cv::Point2d pt, cv::Point2d center, double deg)
{
	cv::Point2d shiftPt = pt-center;
	cv::Point2d rotZeroPt(	shiftPt.x*cos(DEG2RAD(deg))-shiftPt.y*sin(DEG2RAD(deg)),
							shiftPt.x*sin(DEG2RAD(deg))+shiftPt.y*cos(DEG2RAD(deg)) );
	cv::Point rotPt = rotZeroPt+center;
	return rotPt;
}

uchar ImgProcUtil::GetPixel(cv::Mat & srcImg, cv::Point pt)
{
	return srcImg.data[ pt.y*srcImg.cols + pt.x ];
}

void ImgProcUtil::SetPixel(cv::Mat & srcImg, cv::Point pt, uchar value)
{
	srcImg.data[ pt.y*srcImg.cols + pt.x ]= value;
}

cv::Vec3b ImgProcUtil::GetPixel3C(cv::Mat & srcImg, cv::Point pt)
{
	cv::Vec3b value;
	value.val[0] = srcImg.data[ pt.y*srcImg.cols*3 + pt.x*3 ];
	value.val[1] = srcImg.data[ pt.y*srcImg.cols*3 + pt.x*3 + 1 ];
	value.val[2] = srcImg.data[ pt.y*srcImg.cols*3 + pt.x*3 + 2 ];

	return value;
}

void ImgProcUtil::SetPixel3C(cv::Mat & srcImg, cv::Point pt, cv::Vec3b value)
{
	srcImg.data[ pt.y*srcImg.cols*3 + pt.x*3 ] = value.val[0];
	srcImg.data[ pt.y*srcImg.cols*3 + pt.x*3 + 1 ] = value.val[1];
	srcImg.data[ pt.y*srcImg.cols*3 + pt.x*3 + 2 ] = value.val[2];
}

uchar ImgProcUtil::SubPixelValue(cv::Mat & srcImg, cv::Point2d pt)
{
	cv::Point pt_c( (int)(pt.x+0.5), (int)(pt.y+0.5) );	

	if( pt.x<1 || pt.y<1 || pt.x>srcImg.cols-1 || pt.y>srcImg.rows-1 )
	{
		uchar pixel_c = Ut.GetPixel(srcImg,cv::Point(0,0));

		return pixel_c;
	}
	else
	{
		uchar pixel_c = Ut.GetPixel(srcImg,pt_c);

		cv::Point pt_t = pt_c - cv::Point(0,1);
		cv::Point pt_b = pt_c + cv::Point(0,1);
		cv::Point pt_l = pt_c - cv::Point(1,0);
		cv::Point pt_r = pt_c + cv::Point(1,0);

		if(pt_t.x < 0 || pt_t.y < 0 || pt_t.x >= srcImg.cols || pt_t.y >= srcImg.rows)	return 0;
		if(pt_b.x < 0 || pt_b.y < 0 || pt_b.x >= srcImg.cols || pt_b.y >= srcImg.rows)	return 0;
		if(pt_l.x < 0 || pt_l.y < 0 || pt_l.x >= srcImg.cols || pt_l.y >= srcImg.rows)	return 0;
		if(pt_r.x < 0 || pt_r.y < 0 || pt_r.x >= srcImg.cols || pt_r.y >= srcImg.rows)	return 0;

		uchar pixel_t = GetPixel(srcImg,pt_t); 
		uchar pixel_b = GetPixel(srcImg,pt_b); 
		uchar pixel_l = GetPixel(srcImg,pt_l); 
		uchar pixel_r = GetPixel(srcImg,pt_r); 

		double x = pt.x - pt_c.x;
		double y = pt.y - pt_c.y;

		double vx = pixel_c;
		double vy = pixel_c;

		if( x>0 )
		{
			vx = (pixel_c*(1-x)+pixel_r*x)/2.0;
		}
		else 
		{
			vx = (pixel_c*(1-fabs(x))+pixel_l*fabs(x))/2.0;
		}

		if( y>0 )
		{
			vy = (pixel_c*(1-y)+pixel_b*y)/2.0;
		}
		else 
		{
			vy = (pixel_c*(1-fabs(y))+pixel_t*fabs(y))/2.0;
		}

		double value = sqrt( vx*vx+vy*vy );
		return cv::saturate_cast<uchar>(value);
	}
}

cv::Point2d ImgProcUtil::CenterPt(cv::Point2d pt1, cv::Point2d pt2)
{
	return cv::Point2d( (pt1.x+pt2.x)/2.0, (pt1.y+pt2.y)/2.0 );
}

double ImgProcUtil::PtDist(cv::Point2d pt1, cv::Point2d pt2)
{
	double dx = pt2.x-pt1.x;
	double dy = pt2.y-pt1.y;

	return sqrt( dx*dx+dy*dy );
}

BOOL ImgProcUtil::IsPtInside(cv::Point & pt, cv::Rect & areaRect)
{
	if( pt.x<areaRect.x ) return FALSE;
	if( pt.y<areaRect.y ) return FALSE;
	if( pt.x>=areaRect.br().x ) return FALSE;
	if( pt.y>=areaRect.br().y ) return FALSE;

	return TRUE;
}

BOOL ImgProcUtil::IsPtInside(cv::Point & pt, cv::Mat & mat)
{
	cv::Rect areaRect(0,0,mat.cols,mat.rows);

	if( pt.x<areaRect.x ) return FALSE;
	if( pt.y<areaRect.y ) return FALSE;
	if( pt.x>=areaRect.br().x ) return FALSE;
	if( pt.y>=areaRect.br().y ) return FALSE;

	return TRUE;
}

cv::Rect ImgProcUtil::EnlargeRect(cv::Rect & rect, int iX, int iY)
{
	cv::Rect enlarge( rect.x-iX, rect.y-iY, rect.width+iX*2, rect.height+iY*2);

	return enlarge;
}

cv::Rect ImgProcUtil::ReduceRect(cv::Rect & rect, int iX, int iY)
{
	cv::Rect enlarge( rect.x+iX, rect.y+iY, rect.width-iX*2, rect.height-iY*2);

	return enlarge;
}

cv::Rect ImgProcUtil::EnlargeRect(cv::Rect & rect, int iT, int iB, int iL, int iR)
{
	cv::Rect enlarge( rect.x-iL, rect.y-iT, rect.width+iL+iR, rect.height+iT+iB);

	return enlarge;
}

cv::Rect ImgProcUtil::ReduceRect(cv::Rect & rect, int iT, int iB, int iL, int iR)
{
	cv::Rect enlarge( rect.x+iL, rect.y+iT, rect.width-iL-iR, rect.height+iT-iB);

	return enlarge;
}

cv::Rect ImgProcUtil::MultiplyRect(cv::Rect & rect, double m)
{
	cv::Rect newRect;

	newRect.x = int(rect.x * m);
	newRect.y = int(rect.y * m);
	newRect.width = int(rect.width * m);
	newRect.height = int(rect.height * m);

	return newRect;
}

cv::Rect ImgProcUtil::RotateRect(cv::Rect & rect, double angle)
{
	cv::Point2f center = (cv::Point2f)RectCenter(rect);
	cv::RotatedRect rRect(center,rect.size(),(float)angle);
	cv::Rect bRect = rRect.boundingRect();
	return bRect;
}

cv::Point2d ImgProcUtil::RectCenter(cv::Rect & rect)
{
	return cv::Point2d( rect.x+rect.width/2.0, rect.y+rect.height/2.0 );
}

cv::Rect ImgProcUtil::AdjustRect(cv::Rect & rect, cv::Size & size, BOOL bFixedSize)
{
	cv::Rect adjust( rect.x, rect.y, rect.width, rect.height );

	if( rect.width>size.width ) adjust.width = size.width;
	if( rect.height>size.height ) adjust.height = size.height;
	if( rect.x<0 )
	{
		adjust.x = 0; 
		if(!bFixedSize) adjust.width+=rect.x;
	}
	if( rect.y<0 )
	{
		adjust.y = 0; 
		if(!bFixedSize) adjust.height+=rect.y;
	}
	if( rect.x>=size.width )
	{
		adjust.x = 0; 
		if(!bFixedSize) adjust.width+=rect.x;
	}
	if( rect.y>=size.height )
	{
		adjust.y = 0; 
		if(!bFixedSize) adjust.height+=rect.y;
	}
	if( rect.br().x>size.width ) adjust.width = size.width - adjust.x;
	if( rect.br().y>size.height ) adjust.height = size.height - adjust.y;

	return adjust;
}

BOOL ImgProcUtil::IsRectInside(cv::Rect & rect, cv::Rect & areaRect)
{
	if( rect.x < areaRect.x ) return FALSE;
	if( rect.y < areaRect.y ) return FALSE;
	if( rect.br().x > areaRect.br().x ) return FALSE;
	if( rect.br().y > areaRect.br().y ) return FALSE;
	if( rect.width<0 ) return FALSE;
	if( rect.height<0 ) return FALSE;

	return TRUE;
}

BOOL ImgProcUtil::IsRectInside(cv::Rect & rect, cv::Mat & mat)
{
	cv::Rect areaRect(0,0,mat.cols,mat.rows);

	return IsRectInside(rect, areaRect);
}

BOOL ImgProcUtil::IsRectOutside(cv::Rect & rect, cv::Rect & areaRect)
{
	if( rect.x > areaRect.br().x ) return TRUE;
	if( rect.y > areaRect.br().y ) return TRUE;
	if( rect.br().x < areaRect.x ) return TRUE;
	if( rect.br().y < areaRect.y ) return TRUE;
	if( rect.width<0 ) return FALSE;
	if( rect.height<0 ) return FALSE;

	return FALSE;
}

cv::Mat ImgProcUtil::EnlargeImg(cv::Mat & img, int iX, int iY, uchar fillValue)
{
	int x = abs(iX);
	int y = abs(iY);

	cv::Mat enlargeImg(img.rows+y*2,img.cols+x*2,img.type());
	enlargeImg = fillValue;
	
	cv::Rect rect(x,y,img.cols,img.rows);
	img.copyTo(enlargeImg(rect));

	return enlargeImg;
}

cv::Mat ImgProcUtil::ReduceImg(cv::Mat & img, int iX, int iY)
{
	int x = abs(iX);
	int y = abs(iY);

	cv::Mat reduceImg(img.rows-y*2, img.cols-x*2, img.type());
	reduceImg = 0;

	cv::Rect rect(x,y,reduceImg.cols,reduceImg.rows);
	img(rect).copyTo(reduceImg);

	return reduceImg;
}

cv::Mat ImgProcUtil::RotateImg(cv::Mat & img, int iFlag)
{
	cv::Mat rotImg;

	if(iFlag==ROT90)
	{
		cv::transpose(img,rotImg);
		cv::flip(rotImg,rotImg,1);
	}
	else if(iFlag==ROT180)
	{
		cv::flip(img,rotImg,-1);
	}
	else if(iFlag==ROT270)
	{
		cv::transpose(img,rotImg);
		cv::flip(rotImg,rotImg,0);
	}
	else
	{
		rotImg=img;
	}

	return rotImg;
}

cv::Point2d ImgProcUtil::ImgCenter(cv::Mat & srcImg)
{
	return cv::Point2d( srcImg.cols/2.0, srcImg.rows/2.0 );
}

cv::Mat ImgProcUtil::ShiftImg(cv::Mat & srcImg, int iX, int iY)
{
	cv::Mat shiftImg(srcImg.size(), srcImg.type());
	shiftImg = 0;

	shiftImg = Ut.EnlargeImg(shiftImg,abs(iX),abs(iY));

	cv::Rect shiftRect(abs(iX)+iX,abs(iY)+iY,srcImg.cols,srcImg.rows);
	srcImg.copyTo(shiftImg(shiftRect));

	shiftImg = ReduceImg(shiftImg,-abs(iX),-abs(iY));
	return shiftImg;
}

cv::Scalar ImgProcUtil::RandomColor(cv::RNG & rng)
{
	int iColor = (unsigned)rng;
	return cv::Scalar( iColor&255, (iColor>>8)&255, (iColor>>16)&255 );
}

void ImgProcUtil::OverlayLineImg(cv::Mat & srcImg, cv::Mat & lineImg, cv::Scalar color)
{
	if( srcImg.channels()==1 )
	{
		cv::Mat_<uchar>::iterator it_line = lineImg.begin<uchar>();
		cv::Mat_<uchar>::iterator it_src = srcImg.begin<uchar>();
		while( it_line!=lineImg.end<uchar>() && it_src!=srcImg.end<uchar>() )
		{
			uchar pixel_line = (*it_line);
			
			if( pixel_line==WHITE )
			{
				(*it_src) = (uchar)color.val[0];
			}

			++it_line;
			++it_src;
		}
	}
	else
	{
		cv::Mat_<uchar>::iterator it_line = lineImg.begin<uchar>();
		cv::Mat_<cv::Vec3b>::iterator it_src = srcImg.begin<cv::Vec3b>();
		while( it_line!=lineImg.end<uchar>() && it_src!=srcImg.end<cv::Vec3b>() )
		{
			uchar pixel_line = (*it_line);
			
			if( pixel_line==WHITE )
			{
				(*it_src).val[0] = (uchar)color.val[0];
				(*it_src).val[1] = (uchar)color.val[1];
				(*it_src).val[2] = (uchar)color.val[2];
			}

			++it_line;
			++it_src;
		}
	}
}


void ImgProcUtil::OverlayLineImgOffset(cv::Mat & srcImg, cv::Mat & lineImg, cv::Scalar color, cv::Point offset)
{
	if( srcImg.channels()==1 )
	{
		for(int i=0;i<lineImg.cols;i++)
		{
			for(int j=0;j<lineImg.rows;j++)
			{
				cv::Point pt(i,j);
				cv::Point pt_offset = pt+offset;

				uchar pixel_line = lineImg.at<uchar>(pt);
				if(pixel_line==WHITE)
				{
					srcImg.at<uchar>(pt_offset) = (uchar)color.val[0];
				}
			}
		}		
	}
	else
	{
		for(int i=0;i<lineImg.cols;i++)
		{
			for(int j=0;j<lineImg.rows;j++)
			{
				cv::Point pt(i,j);
				cv::Point pt_offset = pt+offset;

				uchar pixel_line = lineImg.at<uchar>(pt);
				if(pixel_line==WHITE)
				{
					srcImg.at<cv::Vec3b>(pt_offset) = cv::Vec3b((uchar)color.val[0],(uchar)color.val[1],(uchar)color.val[2]);
				}
			}
		}	
	}
}

void ImgProcUtil::DrawCross(cv::Mat & img, cv::Point center, int len, cv::Scalar color, int thickness)
{
	cv::Point t,b,l,r;
	t = center + cv::Point(0,-len/2);
	b = center + cv::Point(0,+len/2);
	l = center + cv::Point(-len/2,0);
	r = center + cv::Point(+len/2,0);

	cv::line(img, t, b, color, thickness);
	cv::line(img, l, r, color, thickness);
}

void ImgProcUtil::DrawDiamond(cv::Mat & img, cv::Point center, int len, cv::Scalar color, int thickness)
{
	cv::Point t,b,l,r;
	t = center + cv::Point(0,-len/2);
	b = center + cv::Point(0,+len/2);
	l = center + cv::Point(-len/2,0);
	r = center + cv::Point(+len/2,0);

	cv::line(img, t, l, color, thickness);
	cv::line(img, l, b, color, thickness);
	cv::line(img, b, r, color, thickness);
	cv::line(img, r, t, color, thickness);
}

void ImgProcUtil::DrawRect(cv::Mat & img, cv::Point center, int len, cv::Scalar color, int thickness)
{
	cv::Point tl,tr,br,bl;
	tl = center + cv::Point(-len/2,-len/2);
	tr = center + cv::Point(+len/2,-len/2);
	br = center + cv::Point(+len/2,+len/2);
	bl = center + cv::Point(-len/2,+len/2);

	cv::line(img, tl, tr, color, thickness);
	cv::line(img, tr, br, color, thickness);
	cv::line(img, br, bl, color, thickness);
	cv::line(img, bl, tl, color, thickness);
}

void ImgProcUtil::DrawCircle(cv::Mat & img, cv::Point center, int radius, cv::Scalar color, int thickness)
{
	cv::circle(img, center, radius, color, thickness);
}

void ImgProcUtil::DispImg(std::string name, const cv::Mat & img, double ratio)
{
	cv::Mat dispImg;
	cv::resize(img,dispImg,cv::Size(),ratio,ratio);
	cv::imshow(name,dispImg);
}

void ImgProcUtil::SaveImg(std::string name, const cv::Mat & img, double ratio)
{
	cv::Mat saveImg;
	cv::resize(img,saveImg,cv::Size(),ratio,ratio);
	cv::imwrite(name+".bmp",saveImg);
}

cv::Point2d ImgProcUtil::GetMassCenterContour(std::vector<cv::Point>& contour)
{
	cv::Point2d pCenter;
	int iSz = contour.size();
	cv::Point Sum = 0;
	for (int i=0; i<iSz; i++)
	{
		Sum += contour[i];
	}
	pCenter.x = (double)Sum.x / iSz;
	pCenter.y = (double)Sum.y / iSz;
	return pCenter;
}

void ImgProcUtil::LargestContourImg(cv::Mat& src, std::vector<cv::Point>& contour, cv::Point2d& pMassCenter, cv::Mat& dst)
{
	cv::Mat tempImg;
	if( src.channels()==3 ) cv::cvtColor(src,tempImg,CV_BGR2GRAY);
	else tempImg = src.clone();
	
	std::vector<std::vector<cv::Point>> vAllContours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(tempImg, vAllContours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	int iMaxIdx=0;
	double dMaxArea=0.0;

	std::vector<std::vector<cv::Point>> vContours;
	int iIdx=0;
	std::vector<std::vector<cv::Point>>::iterator it_blob = vAllContours.begin();
	while(it_blob!=vAllContours.end())
	{		
		double dArea = cv::contourArea(*it_blob);
		cv::Rect bndRect = cv::boundingRect(*it_blob);
		double dDist = DIST(0,0,bndRect.width,bndRect.height);

		if( dArea>dMaxArea )
		{
			iMaxIdx = iIdx;
			dMaxArea = dArea;
		}

		++it_blob;
		iIdx++;
	}	

	cv::Mat contImg;
	if( src.channels()==3 ) contImg.create(src.size(),CV_8UC3);
	else contImg.create(src.size(),CV_8UC1);

	contImg = cv::Scalar(0,0,0);
	cv::drawContours(contImg,vAllContours,iMaxIdx,cv::Scalar(255,255,255),CV_FILLED);

	contour = vAllContours[iMaxIdx];
	pMassCenter = GetMassCenterContour(vAllContours[iMaxIdx]);
	dst = contImg.clone();
}

void ImgProcUtil::FindContours(cv::Mat& src, cv::Mat& contourImg, std::vector<std::vector<cv::Point>>& contour, std::vector<cv::Rect>& vbndRect, double dMinW, double dMaxW, double dMinH, double dMaxH, double dminArea, double dmaxArea)
{
	cv::Mat tempImg;
	if( src.channels()==3 ) cv::cvtColor(src,tempImg,CV_BGR2GRAY);
	else tempImg = src.clone();
	
	contourImg = cv::Mat(src.rows, src.cols, CV_8UC1);
	contourImg = 0;

	std::vector<std::vector<cv::Point>> vAllContours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(tempImg, vAllContours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	
	std::vector<std::vector<cv::Point>> vContours;
	int iIdx=0;
	std::vector<std::vector<cv::Point>>::iterator it_blob = vAllContours.begin();
	while(it_blob!=vAllContours.end())
	{		
		double dArea = cv::contourArea(*it_blob);
		cv::Rect bndRect = cv::boundingRect(*it_blob);
		cv::RotatedRect rotRect = cv::minAreaRect(*it_blob);
		double dDist = DIST(0,0,bndRect.width,bndRect.height);
		double dW = rotRect.size.width;
		double dH = rotRect.size.height;
		if (dW < dH) std::swap(dW, dH);
		if( dArea>dminArea && dArea<dmaxArea && dW>dMinH && dW<dMaxH && dH>dMinH && dH<dMaxH)
		{
			vContours.push_back(*it_blob);
			vbndRect.push_back(bndRect);
			cv::drawContours(contourImg, vAllContours, iIdx, cv::Scalar(255,255,255), CV_FILLED);
		}

		++it_blob;
		iIdx++;
	}	
	contour = vContours;
}

std::vector<cv::Point> ImgProcUtil::ConvexHull(std::vector<cv::Point> &contour)
{
	std::vector<cv::Point> vHull;
	cv::convexHull(contour, vHull);
	return vHull;
}

void ImgProcUtil::BitwiseGray(cv::Mat& src, cv::Mat &dst)
{
	if (src.channels() != 1) return;
	cv::Mat img = src.clone();	
	dst = img.clone();

	for (int i=0; i<src.rows; i++)
	for (int j=0; j<src.cols; j++)
	{
		uchar uVal = src.at<uchar>(i,j);
		dst.at<uchar>(i,j) = 255 - uVal;  
	}	
}