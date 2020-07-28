#pragma once

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
#define  NUM_CAM		2
#define  NUM_DELAY      10
#define  PATH_GENERAL_SETTING   ".\\Parameters\\Para.xml"
#define  PATH_POSITION_LEFT		".\\Parameters\\PositionLeft.xml"
#define  PATH_POSITION_RIGHT    ".\\Parameters\\PositionRight.xml"

#define IMAGE_LEFT				".\\Image\\Left\\"
#define IMAGE_RIGHT				".\\Image\\Right\\"
#define  IMAGE_CAPTURE			".\\Image\\"
#define  IMAGE_SAVE				".\\SaveImg\\"
#define  PLC_GRAB_LEFT			"D115"
#define  PLC_GRAB_LEFT_DONE		"D116"
#define  PLC_GRAB_RIGHT			"R115"
#define  PLC_GRAB_RIGHT_DONE	"R116"


#define  CALI_X_LEFT				11
#define  CALI_Y_LEFT				11
#define  CALI_X_RIGHT				11
#define  CALI_Y_RIGHT				11

#define NUM_POS_VISION				16

#define  CALI_X						0.0245
#define  CALI_Y						0.0245



enum _eRotateIMI
{
	DEGREE_0,
	DEGREE_90,
	DEGREE_180,
	DEGREE_270

};
enum DLGNO
{
	AUTO_DLG_ = 0,
	SETTING_DLG,
	MOTION_DLG
};

enum eColumLog
{
	TIME = 0,
	CONTENT

};
enum eColumPos
{
	NAME_POS = 0,
	POINT_BEGIN,
	POINT_END

};

enum eStep
{
	DO_NOTHING = 0,
	CHECK_SENSOR,
	ALIGN,
	MOVE_NEWPOS,
	CHECK_VISION,
	NEXT_POINT
};

enum eTimer
{
	TIME_CLOCK

};
enum eTool
{
	TOOL_1 = 0,
	TOOL_2
};

struct sLight
{
	int iCom = 1;
	int iBaudrate = 9600;
	int iCh1 = 0;
	int iCh2 = 0;
	int iCh3 = 0;
	int iCh4 = 0;

};

struct _general {
	CString ver = "ver1_06.11.2018";
	double     delay[NUM_DELAY] = { 0 };

	//ADD new
	CString SN_camLeft = "32601982US";
	CString SN_camRight = "32602129US";
	CString IP_PLCleft = "";
	CString IP_PLCright = "";

	int iLogical_left = 0;
	int iLogical_right = 0;

};
struct Position
{
	CString name = "";
	Point pBegin = Point(0, 0);
	Point pEnd = Point(0, 0);

};
struct _campara {
	cv::Rect roi = cv::Rect(0, 0, 640, 480);
	int iRotate = DEGREE_0;

	int iBrightness = 0;
	int iContrast = 0;
	int iSaturation = 0;

	int iWB = 2000;
	bool bAutoWB = false;

	int iExposure = 3;
	bool bAutoExposure = false;

	int iFocus = 0;
	bool bAutoFocus = false;

	int iZoom = 100;

	cv::Point pMasterPoint = Point(0, 0);
	double    dMasterAngle = 0.0;
};
struct RefPoint
{
	Point tl = Point(0, 0);
	Point tr = Point(0, 0);
	Point br = Point(0, 0);
	Point bl = Point(0, 0);
};

struct masterPoint
{
	Point2f msPoint = Point2f(0,0);
	float	alpha = 0.0;

};
struct VisionPara
{
	int                 iThresh = 128;
	int                 iSize = 3;
	int					iMor = 3;
	int                 iBlur = 3;
	int                 objWidthMin = -1;
	int                 objWidthMax = -1;
	int                 objHeightMin = -1;
	int                 objHeightMax = -1;
	int                 objAreaMin = -1;
	int                 objAreaMax = -1;

};
struct Capa
{
	int numOK = 0;
	int numNG = 0;
	int numTT = 0;
};
struct sPosition
{
	Rect rRect;
	BOOL bStatus = TRUE;

};





inline CString Rect2CString(Rect r)
{
	CString str = "";
	str.Format("%d,%d,%d,%d", r.x, r.y, r.width, r.height);
	return str;
}
inline CString Point2CString(Point p)
{
	CString str = "";
	str.Format("%d,%d", p.x, p.y);
	return str;
}

inline Rect CString2Rect(CString str)
{
	cv::Rect rect(0, 0, 0, 0);
	CString x, y, w, h;
	AfxExtractSubString(x, str, 0, ','); //Extracting the 'is' 
	AfxExtractSubString(y, str, 1, ','); //Extracting the 'a'
	AfxExtractSubString(w, str, 2, ','); //Extracting the 'test'
	AfxExtractSubString(h, str, 3, ','); //Extracting the 'test' 
	
	rect.x = atoi(x);
	rect.y = atoi(y);
	rect.width = atoi(w);
	rect.height = atoi(h);

	return rect;
}

inline Point CString2Point(CString str)
{
	cv::Point p(0, 0);
	CString x, y, w, h;
	AfxExtractSubString(x, str, 0, ','); //Extracting the 'is' 
	AfxExtractSubString(y, str, 1, ','); //Extracting the 'a'

	p.x = atoi(x);
	p.y = atoi(y);

	return p;
}

inline CString INT2CSTR(int index) {
	CString str;
	str.Format("%d", index);
	return str;
}
inline CRect cvRect2CRect(cv::Rect cvrect)
{
	CRect crect = CRect(cvrect.x, cvrect.y, cvrect.x + cvrect.width, cvrect.y + cvrect.height);
	return crect;
};
inline CPoint cvPoint2CPoint(cv::Point cvrect)
{
	CPoint cPoint = CPoint(cvrect.x, cvrect.y);
	return cPoint;
};
inline cv::Point CPoint2cvPoint(CPoint cPoint)
{
	cv::Point point = Point(cPoint.x, cPoint.y);
	return point;
};
inline cv::Rect CRect2cvRect(CRect crect)
{
	cv::Rect cvrect(crect.left, crect.top, crect.Width(), crect.Height());
	return cvrect;
};
inline cv::Mat drawCross(cv::Mat mImage, Point p) {
	Mat mShow = mImage.clone();
	if (mImage.channels() == 1) {
		cvtColor(mShow, mShow, COLOR_GRAY2BGR);
	}
	line(mShow, Point(p.x - 20, p.y), Point(p.x + 20, p.y), Scalar(0, 0, 255), 4);
	line(mShow, Point(p.x, p.y - 20), Point(p.x , p.y + 20), Scalar(0, 0, 255), 4);
	return mShow;

}
inline cv::Point2f rotatePoint(Point2f p, float angle) {
	cv::Point2f point(0, 0);
	point.x = cos(angle)*p.x - sin(angle)*p.y;
	point.y = sin(angle)*p.x + cos(angle)*p.y;
	return point;
}