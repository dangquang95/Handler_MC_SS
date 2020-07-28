#ifndef NEPTUNE_STREAMWRITER_H
#define NEPTUNE_STREAMWRITER_H

#include "CameraInstance.h"

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								AVI Capture
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API CStreamWriter
	{
	public:
		CStreamWriter(CCameraInstance* pInstance);
		~CStreamWriter();

/*
			Description :
					Start AVI stream capture.
			Parameters :
			    [IN] strFileName : File name to save an AVI.
					[IN] bCompress : Compression flag(H.264)
					[IN] eRotate : Rotate angle.
					[IN] fRate : Frame rate.
					[IN, optional] nBitRate : Bit rate value for H.264(valid only if the bCompress is true)
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CStreamWriter class is not created.
					NEPTUNE_ERR_DeviceNotStreaming
							Error is caused by a Acquisition status is not started.
					NEPTUNE_ERR_TimeOut
							Received FPS information is not updated.
					NEPTUNE_ERR_InvalidParameter
							H.264 encoder is not opened.
					NEPTUNE_ERR_Fail
							AVI stream capture start failed.
*/
		ENeptuneError API_CALLTYPE StartStreamCapture(_char_t* strFileName, ENeptuneBoolean bCompress, _uint32_t nBitRate=1000);
		ENeptuneError API_CALLTYPE StartStreamCapture(_char_t* strFileName, ENeptuneBoolean bCompress, ENeptuneRotationAngle eRotate, _uint32_t nBitRate=1000);
		ENeptuneError API_CALLTYPE StartStreamCapture(_char_t* strFileName, ENeptuneBoolean bCompress, _float32_t fRate, _uint32_t nBitRate=1000);

		// use gpu encoder.
		ENeptuneError API_CALLTYPE StartStreamCaptureEx(char* pszFilePath, int nBitRate, int nGOP = -1, float fSpeed = 1.0f);
/*
			Description :
					Stop AVI stream capture.
			Parameters : 
					None.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CStreamWriter class is not created.
*/
		ENeptuneError API_CALLTYPE StopStreamCapture();

/*
			Description :
					Add image frame to AVI file.(raw data)
			Parameters :
					[IN] pData : Grabbed data information.
					[IN] pInput : Raw data of image.
					[IN] nWidth : Width of image.
					[IN] nHeight : Height of image.
					[IN] eFormat : Pixel format of image.
			Return Values : 
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CStreamWriter class is not created.
*/
		ENeptuneError API_CALLTYPE WriteRawFrame(CFrameDataPtr& pData);
		ENeptuneError API_CALLTYPE WriteRawFrame(const _void_t* pInput, _uint32_t nWidth, _uint32_t nHeight, ENeptunePixelFormat eFormat);
/*
			Description :
					Add Image frame to AVI file.(converted data)
			Parameters :
					[IN] pInput : Converted data.
					[IN] nBufSize : pInput buffer's data size.
					[IN] nWidth : Image width.
					[IN] nHeight : Image height.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CStreamWriter class is not created.
					NEPTUNE_ERR_InvalidArraySize
							nBufSize value is invalid.
*/	
		ENeptuneError API_CALLTYPE WriteConvertFrame(const _void_t* pInput, _uint32_t nBufSize, _uint32_t nWidth, _uint32_t nHeight);

//2015-08-20
		ENeptuneError API_CALLTYPE WriteRawFrame_NET(_int64_t* pBuffer, _int32_t nIdx, _uint32_t nWidth, _uint32_t nHeight, _uint32_t nBufSize, ENeptunePixelFormat ePixelFormat, ENeptuneRotationAngle eAngle);

	protected:

	private:
		class CStreamWriterImpl;
		CStreamWriterImpl *m_pStreamWriterImpl;

		_void_t API_CALLTYPE SetCapture(CCameraInstance* pInstance);	

	};
}

#endif /* NEPTUNE_STREAMWRITER_H */