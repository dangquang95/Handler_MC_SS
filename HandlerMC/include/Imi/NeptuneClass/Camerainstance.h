#ifndef NEPTUNE_CAMERAINSTANCE_H
#define NEPTUNE_CAMERAINSTANCE_H

#include "DeviceManager.h"
#include "CommonProperties.h"

namespace NeptuneClassLib
{
	class CEventListener;

	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								Common Camera Control
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API CCameraInstance : public CCommonProperties
	{
	public:
		CCameraInstance();
		CCameraInstance(INeptuneDevice* pDevice, ENeptuneDevAccess eAccessFlag=NEPTUNE_DEV_ACCESS_EXCLUSIVE);
		~CCameraInstance();

/*
			Description :
					Create camera instance to control.
			Parameters :
			        [IN] pDevice : Object of INeptuneDeivce.
					[IN,Optional] eAccessFlag : Set to camera's access privilege.
			Return Values :
			        NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.
					NEPTUNE_ERR_InvalidParameter
							pDevice parameter is NULL.
					NEPTUNE_ERR_Fail
							pDevice for camera is already opened.
					NEPTUNE_ERR_DeivceOpen
							Failed to device open from TL.
					NEPTUNE_ERR_DeviceXML
							Failed to load XML file.
*/
		ENeptuneError API_CALLTYPE CameraOpen(INeptuneDevice* pDevice, ENeptuneDevAccess eAccessFlag=NEPTUNE_DEV_ACCESS_EXCLUSIVE);
	
/*
			Description : 
					Delete camera instance.
			Parameters :
					None.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.
					NEPTUNE_ERR_DeivceClose
							Camera is already closed.
*/
		ENeptuneError API_CALLTYPE CameraClose();
		
/*
			Description :
					Register to events that user will received.	
			Parameters : 
					[IN] pListener : Object of CEventListener inheritance class.
					[IN] nEventID : The combination of ENeptuneEventID enumeration's values.
					[IN,Optional] pParam : User parameter passed to the callback function.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.
					NEPTUNE_ERR_InvalidParameter
							nEventID value is invalid.
*/
		ENeptuneError API_CALLTYPE RegisterEvent(CEventListener* pListener, _uint32_t nEventID, _void_t* pParam=NULL);
		
/*
			Description :
					Unregister to events for registered to RegisterEvent function.
			Parameters : 
					[IN] nEventID : Delete event that is registered in RegisterEvent function.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.(camera is not opened)
					NEPTUNE_ERR_InvalidParameter
							nEventID value is invalid.
*/
		ENeptuneError API_CALLTYPE UnregisterEvent(_uint32_t nEventID);
		
/*
			Description : 
					Grab to data for one frame.
			Parameters :
					[OUT] pData : Grabbed data information.
					[IN] nTimeout : Time for try to grabbing data.
					[IN,Optional] pBuffer : When user buffer is set, grabbed data is copied to this variable.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class if not created.(camera is not opened)
					NEPTUNE_ERR_NotSupport
							User buffer is registered.
					NEPTUNE_ERR_Timeout
							Grabbing data fail.
*/
		ENeptuneError API_CALLTYPE OneFrameGrab(CFrameDataPtr& pData, _uint64_t nTimeout, _void_t* pBuffer=NULL);		

/*
			Description :
					Read 4 bytes from a camera register.
			Parameters :
					[IN] lAddr : Register address.
					[OUT] plData : Register value.
			Return Values : 
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.(camera is not opened)
					NEPTUNE_ERR_Fail
							Failed to read register data.
*/
		ENeptuneError API_CALLTYPE ReadRegister(_ulong32_t lAddr, _ulong32_t* plData);
		
/*
			Description :
					Write 4 bytes to a camera register.
			Parameters :
					[IN] lAddr : Register address.
					[IN] lData : Register value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.(camera is not opened)
					NEPTUNE_ERR_Fail
							Failed to write register data.
*/
		ENeptuneError API_CALLTYPE WriteRegister(_ulong32_t lAddr, _ulong32_t lData);
		
/*
			Description :
					Read data from a camera register.
			Parameters :
					[IN] lAddr : Register address.
					[OUT] pnData : Buffer to read data. 
					[IN/OUT] pnDataSize : Number of bytes to read. 
			Return Values : 
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.(camera is not opened)
					NETPUNE_ERR_InvalidArraySize
							pnDataSize parameter is invalid.
					NEPTUNE_ERR_Fail
							Failed to read block data.
*/
		ENeptuneError API_CALLTYPE ReadBlock(_ulong32_t lAddr, _int8_t* pnData, _uint32_t* pnDataSize);

/*
			Description :
					Write data to a camera register.
			Parameters :
					[IN] lAddr : Register address.
					[IN] pnData : Buffer to write data.
					[IN] nDataSize : Number of bytes to write.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.(camera is not opened)
					NEPTUNE_ERR_InvalidArraySize
							nDataSize parameter is invalid.
					NEPTUNE_ERR_Fail
							Failed to write block data.
*/
		ENeptuneError API_CALLTYPE WriteBlock(_ulong32_t lAddr, _int8_t* pnData, _uint32_t nDataSize);

/*
			Description :
					Set Acquisition start to a camera.
			Parameters :
					[IN] eGrabMode : Grab continuous or Grab one
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.(camera is not opened)
					NEPTUNE_ERR_Fail
							Acquisition is already started.
					NEPTUNE_ERR_DeviceStream
							Acquisition start failed.

*/
		ENeptuneError API_CALLTYPE AcquisitionStart(ENeptuneGrabMode eGrabMode=NEPTUNE_GRAB_CONTINUOUS);
		
/*
			Description :
					Set Acquisition stop to a camera.
			Parameters :
					None.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.(camera is not opened)
					NEPTUNE_ERR_Fail
							Acquisition is already stopped.
*/
		ENeptuneError API_CALLTYPE AcquisitionStop();
	
/*
			Description :
					Get grabbed data from a camera.
			Parameters :
					[OUT] pData : Grabbed data information.
					[IN] nTimeout : Time for try to grabbing data.					
			Return Values :
					NEPTUNE_ERR_Succes
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.(camera is not opened)
					NEPTUNE_ERR_Timeout
							Grabbing time is over. / Camera is applied to a trigger mode.
					NEPTUNE_ERR_Fail
						    Failed to grab data.
*/
		ENeptuneError API_CALLTYPE WaitEventDataStream(CFrameDataPtr& pData, _uint32_t nTimeout);		
			
/*
			Description : 
					To make buffer can be receiving a new image data. 
			Parameters :
					[IN] nBufferIndex : Index of a queue buffer.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.(camera is not opened)
*/
		ENeptuneError API_CALLTYPE QueueBufferDataStream(_int32_t nBufferIndex);
		
/*
			Description : 
					Set user accessible buffer.
			Parameters :
					[OUT] pBuffer : User buffer pointer.
					[IN] nSize : Buffer size.
					[IN] nCount : Total buffer count.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.(camera is not opened)
					NEPTUNE_ERR_InvalidAddress
							pBuffer is Invalid.
					NEPTUNE_ERR_InvalidArraySize
							nCount is up to 3.	
					NEPTUNE_ERR_DeviceStream
							Acquisition is already started.
*/
		ENeptuneError API_CALLTYPE SetUserBuffer(_void_t* pBuffer, _uint32_t nSize, _uint32_t nCount);	
		
/*
			Description :
					Set the number of image buffer of an NeptuneClass API.
					Default buffer count is 10.
			Parameters :
					[IN] nCount : number of buffer
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.(camera is not opened)
					NEPTUNE_ERR_InvalidArraySize
							nCount is up to 3.
*/
		ENeptuneError API_CALLTYPE SetBufferCount(_uint32_t nCount);
		
/*
			Description : 
					Get the number of image buffer of an Neptune Class API.		
			Parameters :
					None.
			Return Values :
					Number of a buffer.
*/
		_uint32_t API_CALLTYPE GetBufferCount();
		
/*
			Description :
					Get the real image data transfer rate.
			Parameters : 
					[OUT] pfRate : Received frame rate.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.(camera is not opened)
*/
		ENeptuneError API_CALLTYPE GetReceivedFrameRate(_float32_t* pfRate);
		
/*
			Description : 
					Get the interface type of a camera.
			Parameters :
					None.
			Return Values :
					NEPTUNE_DEV_TYPE_UNKNOWN
							Camera interface type is unknown.
					NEPTUNE_DEV_TYPE_GIGE
							Camera interface type is GigE
					NEPTUNE_DEV_TYPE_1394
							Camera interface type is 1394.
					NEPTUNE_DEV_TYPE_USB3
							Camera interface type is USB3.
*/
		ENeptuneDevType API_CALLTYPE GetCameraType();
		
/*
			Description : 
					Get current allocated INeptuneDevice interface object.
			Parameters :
					None.
			Return Values :
					Object of INeptuneDevice.					
*/
		INeptuneDevice* API_CALLTYPE GetCamera();

/*
			Description :
					When bRecvDropFrame is true, you can received a drop frame information through the GetFrameValid function of CFrameData class. 
			Parameters :
					[IN] bRecvDropFrame : Dropped frame enable or disable.
			Return Values :
				NEPTUNE_ERR_Success
					Success.
				NEPTUNE_ERR_NotInitialized
					Object of CCameraInstance class is not created.(camera is not opened)
				NEPTUNE_ERR_GrabFrameDropped
					Failed to set to receive drop frame.
*/			
		ENeptuneError API_CALLTYPE SetRecvDropFrame( ENeptuneBoolean bRecvDropFrame );

/*
			Description :
					Get receive status of dropped frame. 
			Parameters :
					None.
			Return Values :
					Receive status of dropped frame.
*/
		ENeptuneBoolean API_CALLTYPE GetRecvDropFrame();

/*
			Description :
					Set packet resend to a camera.
			Parameters :
					[IN] bResend : Enable or Disable a packet resend.
			Return  Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.	
					NEPTUNE_ERR_Fail
							Packet resend set failed.				
*/
		ENeptuneError API_CALLTYPE SetPacketResend(ENeptuneBoolean bResend);

/*
			Description :
				Get packet resend status from a camera.
			Parameters : 
				None.
			Return Values : 
				Receive status of packet resend.
*/
		ENeptuneBoolean API_CALLTYPE GetPacketResend();

/*
			Description :
					When camera is setting for trigger mode, initialize to a API buffer.
			Parameters : 
					None.
			Return Values :
					NEPTUNE_ERR_Success
						Success.
					NEPTUNE_ERR_NotInitialized
						Object of CCameraInstance class is not created.	
					NEPTUNE_ERR_Fail
						Trigger mode is not selected or camera is not playing.
*/
		ENeptuneError API_CALLTYPE FlushBuffer();

/*
			Description : 
					When camera is setting for live mode, initialize to a API buffer.
			Parameters : 
					None.
			Return Values :
					NEPTUNE_ERR_Success
						Success.
					NEPTUNE_ERR_NotInitialized
						Object of CCameraInstance class is not created.	
					NEPTUNE_ERR_Fail
						Live mode is not selected or camera is not playing.				
*/
		ENeptuneError API_CALLTYPE Grab();

		ENeptuneError API_CALLTYPE OneFrameGrab(_void_t* pBuffer, CFrameDataPtr& pData, _uint64_t nTimeout);
		ENeptuneError API_CALLTYPE OneFrameGrab_NET(_void_t* pBuffer, _int32_t* pnIdx, _uint32_t* pnWidth, _uint32_t* pnHeight, _uint32_t* pnBufSize, ENeptunePixelFormat *pePixelFormat, ENeptuneBoolean *pbFrameValid, ENeptuneRotationAngle* peAngle, _uint64_t* pnTimestamp, _uint64_t nTimeout);
		ENeptuneError API_CALLTYPE WaitEventDataStream_NET(_int64_t* pBuffer, _int32_t* pnIdx, _uint32_t* pnWidth, _uint32_t* pnHeight, _uint32_t* pnBufSize, ENeptunePixelFormat *pePixelFormat, ENeptuneBoolean *pbFrameValid, ENeptuneRotationAngle* peAngle, _uint64_t* pnTimestamp, _uint64_t nTimeout);

	protected:

	private:
		CCameraInstance(const CCameraInstance&); 
		CCameraInstance& operator=(const CCameraInstance& other); 

		friend class CDeviceManager;
		friend class CXMLDescription;
		friend class CCommonProperties;
		friend class C1394CameraInstance;
		friend class CGigECameraInstance;
		friend class CUSBCameraInstance;

		class CCameraInstanceImpl;
		CCameraInstanceImpl* m_pInstanceImpl;

	};

}


#endif /*NEPTUNE_CAMERAINSTANCE_H*/
