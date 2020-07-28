#pragma once
#include "VirtualFG40.h" 
#pragma comment (lib, "VirtualFG40.lib")
#include "opencv2\opencv.hpp"
#pragma comment (lib, "opencv_world330d.lib")


class CameraCrevis
{
public:
	CameraCrevis();
	CameraCrevis(__int32 PosX, __int32 PosY, __int32 Height, __int32 Width, char* Mode, __int32 Id);
	~CameraCrevis();

public:

	__int32				 m_hDevice;
	__int32				 m_Width;
	__int32				 m_Height;
	__int32				 m_BufferSize;
	__int32			     m_IsOpenCamera;
	__int32				 m_PosX;
	__int32				 m_PosY;
	cv::Mat				 imgGrap;
	unsigned char*		 m_pImage;
public:
	void				 OnInitCamera(__int32 cPosX, __int32 cPosY, __int32 cHeight, __int32 cWidth, char* cMode, __int32 cId);
	bool				 ConnectCamera(char* cMode, __int32 cId);
	bool				 DisConnectCamera();
	void				 CaptureImage(cv::Mat &img);
};
