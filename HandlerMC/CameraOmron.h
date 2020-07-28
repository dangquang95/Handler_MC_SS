#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <StApi_TL.h>

#ifdef _DEBUG
#define CV_LIBEXT "d.lib"
#else
#define CV_LIBEXT ".lib"
#endif
#define CV_LIB_FILE_NAME(MOD) MOD CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) CVAUX_STR(CV_SUBMINOR_VERSION) CV_LIBEXT
#if CV_MAJOR_VERSION < 3
#pragma comment(lib, CV_LIB_FILE_NAME("opencv_core"))
#pragma comment(lib, CV_LIB_FILE_NAME("opencv_imgproc"))
#pragma comment(lib, CV_LIB_FILE_NAME("opencv_highgui"))
#pragma comment(lib, "zlib" CV_LIBEXT)
#else
#pragma comment(lib, CV_LIB_FILE_NAME("opencv_world"))
#endif

const uint64_t nCountOfImagesToGrab = 100;

using namespace cv;
using namespace std;
using namespace StApi;
class CameraOmron
{
public:
	CameraOmron();
	~CameraOmron();

public:
	bool Open();
	void Close();
	void Stop();
	bool Grab(cv::Mat & grabImg);
	bool IsGrabbing();
	bool InitLib();
	bool UnInitLib();
	bool bDone = false;
private:
	CStApiAutoInit* objStApiAutoInit;
	// Create a system object for device scan and connection.
	CIStDevicePtr* pDevice;

	CIStSystemPtr* pSystem;
	CIStDataStreamPtr* pDataStream;
};

