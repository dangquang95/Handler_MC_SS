#ifndef NEPTUNE_FRAMEDATA_PTR_H
#define NEPTUNE_FRAMEDATA_PTR_H

#include "NeptuneClassLib.h"

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								Grabbed Data Information
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API CFrameData
	{
	public:
/*
			Description :
					Get raw buffer pointer.
			Parameters :
			        	None.
			Return Values :
					m_pBufRaw variable's value is returned.
*/
		_void_t* API_CALLTYPE GetBufferPtr();

/*
			Description :
					Get timestamp data.
			Parameters :
					None.
			Return Values :
					m_nTimestamp variable's value is returned.
*/
		_uint64_t API_CALLTYPE GetTimestamp();

/*
			Description : 
					Get buffer index for API buffer.
			Parameters :
					None.
			Return Values :
					m_nBufIdx variable's value is returned.
*/
		_int32_t API_CALLTYPE GetBufferIndex();
		
/*
			Description : 
					Get Image width.
			Parameters :
					None.
			Return Values :
					m_nWidth variable's value is returned.
*/
		_uint32_t API_CALLTYPE GetWidth();

/*
			Description : 
					Get Image height.
			Parameters : 
					None.
			Return Values :
					m_nHeight variable's value is returned.
*/
		_uint32_t API_CALLTYPE GetHeight();

/*
			Description : 
					Get Image buffer size.
			Parameters : 
					None.
			Return Values :
					m_nBufSize variable's value is returned.
*/
		_uint32_t API_CALLTYPE GetBufferSize();

/*
			Description : 
					Get current pixel format.
			Parameters :
					None.
			Return Values :
					m_ePixelFormat variable's value is returned.
*/
		ENeptunePixelFormat API_CALLTYPE GetPixelFormat();

/*
			Description : 
					Check whether you have received a frame from the camera properly.
			Parameters :
					None.
			Return Values :
					m_bFrameValid variable's value is returned.
*/
		ENeptuneBoolean API_CALLTYPE GetFrameValid();
		
/*
			Description :
					Get rotate value.
			Parameters :
					None.
			Return Values :
					m_eAngle variable's value is returned.
*/
		ENeptuneRotationAngle API_CALLTYPE GetRotate();

/*
			Description :
					Get camera instance.
			Parameters : 
					None.
			Return Values :
					Camera instance is returned.
*/
		_void_t* GetCameraInstance();

	protected:
		CFrameData(_uchar_t* p=NULL);
		virtual ~CFrameData();

	private:
		friend class CCameraInstance;
		friend class CFrameDataPtr;

		CFrameData(const CFrameData&);
		void operator = (const CFrameData&);	

		_void_t* m_pBufRaw;
		ENeptuneBoolean m_bAlloc;
		_uint64_t m_nTimestamp;
		_int32_t m_nBufIdx;
		_uint32_t m_nWidth;
		_uint32_t m_nHeight;
		_uint32_t m_nBufSize;
		ENeptunePixelFormat m_ePixelFormat;
		ENeptuneBoolean m_bFrameValid;
		ENeptuneRotationAngle m_eAngle;
		_void_t* m_pCamInst;
	};

	class NEPTUNE_CLASS_API CFrameDataPtr
	{
	public:
		CFrameDataPtr(CFrameData* p=NULL);
		~CFrameDataPtr();

		CFrameData* operator->() { return m_pFrameDataObj; }
		CFrameData& operator*() { return *m_pFrameDataObj; }

		//static void API_CALLTYPE GetFrameData(CFrameDataPtr& pFrameData, _void_t* pBuffer, _int32_t nIdx, _uint32_t nWidth, _uint32_t nHeight, _uint32_t nBufSize, ENeptunePixelFormat ePixelFormat, _uint64_t nTimestamp);
//2015-05-06
		static void API_CALLTYPE GetFrameData(CFrameDataPtr& pFrameData, _void_t* pBuffer, _int32_t nIdx, _uint32_t nWidth, _uint32_t nHeight, _uint32_t nBufSize, ENeptunePixelFormat ePixelFormat, ENeptuneBoolean bFrameValid, ENeptuneRotationAngle eAngle, _uint64_t nTimestamp);

	protected:

	private:
		friend class CCameraInstance;

		CFrameData* m_pFrameDataObj;

	};

}

#endif /*NEPTUNE_FRAMEDDATA_PTR_H*/