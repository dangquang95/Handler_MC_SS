#ifndef NEPTUNE_DISPLAYIMAGE_H
#define NEPTUNE_DISPLAYIMAGE_H

#include "CameraInstance.h"

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								Image Display
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API CDisplayImage
	{
	public:
		CDisplayImage(HWND hWnd);
		~CDisplayImage();
/*
			Description :
					Display the raw data that received from the camera.
			Parameters :
			        [IN] pData : Grabbed data information.
			Return Values :
			        NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CDisplayImage class is not created.
							Windows display control's handle is not applied.
*/
		ENeptuneError API_CALLTYPE DrawRawImage(CFrameDataPtr& pData);

/*
			Description :
					Display converted data.
			Parameters :
			    [IN] pInput : Pointer of converted data
					[IN] nBufSize : pInput's data size.
					[IN] nWidth : Image width.
					[IN] nHeight : Image height.
					[IN] eRotate : Rotate angle.
			Return Values :
			        NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CDisplayImage class is not created.
							Windows display control's handle is not applied.
					NEPTUNE_ERR_InvalidArraySize
							nBufSize value is invalid. 
*/		
		ENeptuneError API_CALLTYPE DrawConvertImage(const _void_t* pInput, _uint32_t nBufSize, _uint32_t nWidth, _uint32_t nHeight );
		ENeptuneError API_CALLTYPE DrawConvertImage(const _void_t* pInput, _uint32_t nBufSize, _uint32_t nWidth, _uint32_t nHeight, ENeptuneRotationAngle eRotate);

/*
			Description :
				Set display window.
			Parameters :
				[IN] hWnd : Handle of window.
			Return Values :
				None.
*/
		_void_t API_CALLTYPE SetDisplay(HWND hWnd);
		
		//ENeptuneError API_CALLTYPE DrawRawImage_NET(_int64_t* pBuffer, _int32_t nIdx, _uint32_t nWidth, _uint32_t nHeight, _uint32_t nBufSize, ENeptunePixelFormat ePixelFormat, ENeptuneRotationAngle eAngle); 
		ENeptuneError API_CALLTYPE DrawRawImage_NET(_int64_t* pBuffer, _int32_t nIdx, _uint32_t nWidth, _uint32_t nHeight, _uint32_t nBufSize, ENeptunePixelFormat ePixelFormat, ENeptuneRotationAngle eAngle, _void_t* pCamInst); 

	protected:

	private:
		class CDisplayImageImpl;
		CDisplayImageImpl* m_pDisplayImageImpl;
	};
}

#endif /* NEPTUNE_DISPLAYIMAGE_H */