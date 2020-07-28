#include "stdafx.h"
#include "CameraCrevis.h"

CameraCrevis::CameraCrevis()
{
}

CameraCrevis::CameraCrevis(__int32 PosX, __int32 PosY, __int32 Height, __int32 Width, char* Mode, __int32 Id) {

	OnInitCamera(PosX, PosY, Height, Width, Mode, Id);

}


void CameraCrevis::OnInitCamera(__int32 cPosX = 0, __int32 cPosY = 0, __int32 cHeight = 0, __int32 cWidth = 0, char* cMode = PIXEL_FORMAT_MONO8, __int32 cId = 0) {

	m_hDevice = 0;
	m_PosX = cPosX;
	m_PosY = cPosY;
	m_Width = cWidth;
	m_Height = cHeight;
	m_BufferSize = m_Width * m_Height;
	m_pImage = (unsigned char*)malloc(m_BufferSize);
	memset((void*)m_pImage, 0, m_BufferSize);
	m_IsOpenCamera = false;

	if (ST_InitSystem() != MCAM_ERR_SUCCESS)
	{
		AfxMessageBox(_T("Initialze system failed"), MB_OK | MB_ICONSTOP);
		return;
	}
	ConnectCamera(cMode, cId);
}

bool CameraCrevis::ConnectCamera(char* cMode = PIXEL_FORMAT_MONO8, __int32 cId = 0) {

	__int32 status = MCAM_ERR_SUCCESS;
	unsigned __int32 camNum = 0;
	CString strErr;

	// Update Device List
	status = ST_UpdateDevice();
	if (status != MCAM_ERR_SUCCESS)
	{
		strErr.Format(_T("Update device list failed : %d"), status);
		AfxMessageBox(strErr, MB_OK | MB_ICONSTOP);
		return false;
	}

	// Get Available Camera number
	ST_GetAvailableCameraNum(&camNum);
	if (camNum <= 0)
	{
		strErr.Format(_T("No available camera."));
		AfxMessageBox(strErr, MB_OK | MB_ICONSTOP);
		return false;
	}

	// camera open
	status = ST_OpenDevice(cId, &m_hDevice);
	if (status != MCAM_ERR_SUCCESS)
	{
		strErr.Format(_T("Open device failed : %d"), status);
		AfxMessageBox(strErr, MB_OK | MB_ICONSTOP);
		return false;
	}

	status = ST_SetIntReg(m_hDevice, MCAM_WIDTH, m_Width);
	if (status != MCAM_ERR_SUCCESS)
	{
		strErr.Format(_T("Write Register failed : %d"), status);
		AfxMessageBox(strErr, MB_OK | MB_ICONSTOP);
		return false;
	}

	//Get Height
	status = ST_SetIntReg(m_hDevice, MCAM_HEIGHT, m_Height);
	if (status != MCAM_ERR_SUCCESS)
	{
		strErr.Format(_T("Write Register failed : %d"), status);
		AfxMessageBox(strErr, MB_OK | MB_ICONSTOP);
		return false;

	}

	status = ST_SetIntReg(m_hDevice, MCAM_OFFSET_Y, m_PosY);
	if (status != MCAM_ERR_SUCCESS)
	{
		strErr.Format(_T("Write Register failed : %d"), status);
		AfxMessageBox(strErr, MB_OK | MB_ICONSTOP);
		return false;
	}

	//Get Height
	status = ST_SetIntReg(m_hDevice, MCAM_OFFSET_X, m_PosX);
	if (status != MCAM_ERR_SUCCESS)
	{
		strErr.Format(_T("Write Register failed : %d"), status);
		AfxMessageBox(strErr, MB_OK | MB_ICONSTOP);
		return false;
	}

	// Set Trigger Mode : OFf
	status = ST_SetEnumReg(m_hDevice, MCAM_TRIGGER_MODE, TRIGGER_MODE_OFF);
	if (status != MCAM_ERR_SUCCESS)
	{
		strErr.Format(_T("Write Register failed : %d"), status);
		AfxMessageBox(strErr, MB_OK | MB_ICONSTOP);
		return false;
	}

	// Set PixelFormat : Mono8, BGR8PACKED
	status = ST_SetEnumReg(m_hDevice, MCAM_PIXEL_FORMAT, cMode);
	if (status != MCAM_ERR_SUCCESS)
	{
		strErr.Format(_T("Write Register failed : %d"), status);
		AfxMessageBox(strErr, MB_OK | MB_ICONSTOP);
		return false;
	}

	m_IsOpenCamera = true;
	return true;
}


bool CameraCrevis::DisConnectCamera() {

	__int32 status = MCAM_ERR_SUCCESS;
	CString strErr;

	if (m_IsOpenCamera == false)
		return false;
	try
	{

		status = ST_AcqStop(m_hDevice);
		if (status != MCAM_ERR_SUCCESS)
		{
			strErr.Format(_T("Acquisition stop failed : %d"), status);
			AfxMessageBox(strErr, MB_OK | MB_ICONSTOP);
			return false;
		}
	}
	catch (...)
	{

	}

	try {
		if (m_pImage != NULL)
		{
			free(m_pImage);
			m_pImage = NULL;
		}
	}
	catch (...) {

	}

	try {
		ST_CloseDevice(m_hDevice);
	}
	catch (...) {

	}

	m_IsOpenCamera = false;
	return true;
}

void CameraCrevis::CaptureImage(cv::Mat &img) {

	try {
		CString strErr;
		if (!m_IsOpenCamera) {
			AfxMessageBox(_T("Camera Disconnect!!!"), MB_OK | MB_ICONERROR);
			return;
		}
		int status = ST_AcqStart(m_hDevice);
		if (status != MCAM_ERR_SUCCESS)
		{

			strErr.Format(_T("Acquisition start failed : %d"), status);
			AfxMessageBox(strErr, MB_OK | MB_ICONSTOP);
			return;
		}

		 status = ST_GrabImage(m_hDevice, m_pImage, m_BufferSize);

		// to do somethings...
		if (m_pImage != NULL && status == MCAM_ERR_SUCCESS)
			img = cv::Mat(m_Height, m_Width, CV_8UC1, m_pImage);

		status = ST_AcqStop(m_hDevice);
		if (status != MCAM_ERR_SUCCESS)
		{
			strErr.Format(_T("Acquisition Stop failed : %d"), status);
			AfxMessageBox(strErr, MB_OK | MB_ICONSTOP);
			return;
		}
	}
	catch (...) {


	}
}
CameraCrevis::~CameraCrevis() {

	DisConnectCamera();
}