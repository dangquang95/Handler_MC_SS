#include "stdafx.h"
#include "CameraOmron.h"

CStApiAutoInit objStApiAutoInit;

// Create a system object for device scan and connection.
CIStSystemPtr pIStSystem(CreateIStSystem());

// Create a camera device object and connect to first detected device.
CIStDevicePtr pIStDevice(pIStSystem->CreateFirstIStDevice());

// Displays the DisplayName of the device.
// Create a DataStream object for handling image stream data.
CIStDataStreamPtr pIStDataStream(pIStDevice->CreateIStDataStream(0));

CameraOmron::CameraOmron()
{
	//InitLib();
}


CameraOmron::~CameraOmron()
{
	UnInitLib();
}

bool CameraOmron::Open()
{
	return false;
}

void CameraOmron::Close()
{
}

void CameraOmron::Stop()
{
}

bool CameraOmron::Grab(cv::Mat & grabImg)
{
	static Mat inputMat;
	if (pIStDataStream->IsGrabbing())
	{
		// Retrieve the buffer pointer of image data with a timeout of 5000ms.
		CIStStreamBufferPtr pIStStreamBuffer(pIStDataStream->RetrieveBuffer(1000));

		// Check if the acquired data contains image data.
		if (pIStStreamBuffer->GetIStStreamBufferInfo()->IsImagePresent())
		{
			// If yes, we create a IStImage object for further image handling.
			IStImage *pIStImage = pIStStreamBuffer->GetIStImage();

			// Check the pixelfomat of the input image.
			const StApi::EStPixelFormatNamingConvention_t ePFNC = pIStImage->GetImagePixelFormat();
			StApi::IStPixelFormatInfo * const pIStPixelFormatInfo = StApi::GetIStPixelFormatInfo(ePFNC);
			if (pIStPixelFormatInfo->IsMono() || pIStPixelFormatInfo->IsBayer())
			{
				// Check the size of the image.
				const size_t nImageWidth = pIStImage->GetImageWidth();
				const size_t nImageHeight = pIStImage->GetImageHeight();
				int nInputType = CV_8UC1;
				if (8 < pIStPixelFormatInfo->GetEachComponentTotalBitCount())
				{
					nInputType = CV_16UC1;
				}

				// Create a OpenCV buffer for the input image.
				if ((inputMat.cols != nImageWidth) || (inputMat.rows != nImageHeight) || (inputMat.type() != nInputType))
				{
					inputMat.create(nImageHeight, nImageWidth, nInputType);
				}

				// Copy the input image data to the buffer for OpenCV.
				const size_t dwBufferSize = inputMat.rows * inputMat.cols * inputMat.elemSize() * inputMat.channels();
				memcpy(inputMat.ptr(0), pIStImage->GetImageBuffer(), dwBufferSize);

				// Convert the pixelformat if needed.
				grabImg = inputMat.clone();
				if (pIStPixelFormatInfo->IsBayer())
				{
					int nConvert = 0;
					switch (pIStPixelFormatInfo->GetPixelColorFilter())
					{
					case(StPixelColorFilter_BayerRG): nConvert = CV_BayerRG2RGB;	break;
					case(StPixelColorFilter_BayerGR): nConvert = CV_BayerGR2RGB;	break;
					case(StPixelColorFilter_BayerGB): nConvert = CV_BayerGB2RGB;	break;
					case(StPixelColorFilter_BayerBG): nConvert = CV_BayerBG2RGB;	break;
					}
					if (nConvert != 0)
					{
						cvtColor(inputMat, grabImg, nConvert);
					}
				}
				return true;
			}
		}
		else
		{
			// If the acquired data contains no image data.
			TRACE("Image data does not exist");
		}
	}
	return false;
}

bool CameraOmron::IsGrabbing()
{
	return false;
}

bool CameraOmron::InitLib()

{
	try
	{
		StApiInitialize();
		bDone = true;
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool CameraOmron::UnInitLib()
{
	// Stop the image acquisition of the camera side.
	pIStDevice->AcquisitionStop();

	// Stop the image acquisition of the host side.
	pIStDataStream->StopAcquisition();
	try
	{
		StApiTerminate();
		return true;
	}
	catch (...)
	{
		return false;
	}
	
}
