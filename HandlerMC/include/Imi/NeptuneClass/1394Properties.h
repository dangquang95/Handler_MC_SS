#ifndef NEPTUNE_1394PROPERTIES_H
#define NEPTUNE_1394PROPERTIES_H

#include "CommonProperties.h"

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								1394 Camera Properties
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API C1394Properties
	{
	public:
/*
			Description :
					Set the byte per packet to a camera.(for 1394 camera Format7 only)
			Parameters :
					[IN] nBpp : Byte per packet value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of C1394Properties class is not created.
					NEPTUNE_ERR_NotSupport
							Only Format7 applied.
					NEPTUNE_ERR_Fail
							Byte per packet set failed.
*/
		ENeptuneError API_CALLTYPE SetBytePerPacket(_uint32_t nBpp);

/*
			Description :
					Get the byte per packet to a camera.(for 1394 camera Format7 only)
			Parameters :
					[OUT] pnBpp : Current byte per packet value.
					[OUT, Optional] pnMin : Minimum byte per packet value supported.
					[OUT, Optional] pnMax : Maximum byte per packet value supported.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of C1394Properties class is not created.
					NEPTUNE_ERR_NotSupport
							Only Format7 applied.
					NEPTUNE_ERR_Fail
							Byte per packet get failed.
*/
		ENeptuneError API_CALLTYPE GetBytePerPacket(_uint32_t *pnBpp, _uint32_t* pnMin=NULL, _uint32_t* pnMax=NULL);
		
/*
			Description :
					Control camera to transfer saved frames.
			Parameters :
					[IN] bOnOff : Frame save on/off control.
					[IN] bTransfer : Transfer control.
					[IN] nFrames : Number of frames to transfer.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of C1394Properties class is not created.
					NEPTUNE_ERR_OutOfRange
							nFrames value is exceeded maximum save frames.
					
					cf. 
						 Resolution    |    Mono8    | Mono16/YUV422
					-------------------------------------------------
					      640 x 480    |  63 frames  |   31 frames
						  800 x 600    |  63 frames  |   31 frames
						 1024 x 768    |  31 frames  |   15 frames
						 1280 x 960    |  15 frames  |    7 frames
						1280 x 1024    |  15 frames  |    7 frames
						1600 x 1200    |  15 frames  |    7 frames
						2048 x 1536    |   7 frames  |    3 frames

					NEPTUNE_ERR_Fail
							Frame save register set failed. 
*/
		ENeptuneError API_CALLTYPE SetFrameSave(ENeptuneBoolean bOnOff, ENeptuneBoolean bTransfer, _uint32_t nFrames);
	
/*
			Description :
					Get frame save information from a camera.
			Parameters :
					[OUT] pbOnOff : Frame save on/off state.
					[OUT] pnFrameRemained : Number of frames remained in the camera memory.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUTNE_ERR_NotInitialized
							Object of C1394Properties class is not created.
					NEPTUNE_ERR_Fail
							Saved frame receive failed.  
*/
		ENeptuneError API_CALLTYPE GetFrameSave(ENeptuneBoolean* pbOnOff, _uint32_t* pnFrameRemained);

/*
			Description :
					Write broadcast to 1394 cameras
			Parameters :
					[IN] lAddr : Register address.
					[IN] lData : Value to write.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of C1394Properties class is not created.
					NEPTUNE_ERR_Fail
							Failed to write register to connected 1394 cameras.				
*/
		ENeptuneError API_CALLTYPE WriteBroadcast(_ulong32_t lAddr, _ulong32_t lData);

	protected:
		C1394Properties();
		~C1394Properties();

	private:
		friend class C1394CameraInstance;

		class C1394PropImpl;	
		C1394PropImpl* m_p1394PropImpl;

	};
}


#endif /*NEPTUNE_1394PROPERTIES_H*/