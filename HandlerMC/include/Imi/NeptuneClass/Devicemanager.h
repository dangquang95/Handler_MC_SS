#ifndef NEPTUNE_DEVICEMANAGER_H
#define NEPTUNE_DEVICEMANAGER_H

#include "NeptuneClassLib.h"
#include "NeptuneDevice.h"

#include <vector>

using namespace std;

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								Camera Management
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API CDeviceManager 
	{
	public:
/*
			Description :
					Get object of CDeviceManager class. 
			Parameters :
			        None.
			Return Values :
			        Object of CDeviceManager class.
*/
		static CDeviceManager& API_CALLTYPE GetInstance();

/*
			Description :
					Get object of INeptuneDevice interface.
			Parameters :
			        [IN] nIndex : One of camera list's index.
			Return Values :
					Object of INeptuneDeivce.
*/
		INeptuneDevice* API_CALLTYPE GetDeviceFromIndex(_uint32_t nIndex);

/*
			Description :
					Get object of INeptuneDevice interface.
			Parameters :
			        [IN] nIndex : One of camera list's serial number.
			Return Values :
					Object of INeptuneDevice.
*/
		INeptuneDevice* API_CALLTYPE GetDeviceFromSerial(_char_t* strSerial);
	
/*
			Description :
					Get number of cameras connected to the system.
			Parameters :
			        None.
			Return Values :
					Number of cameras.
*/
		_uint32_t API_CALLTYPE GetTotalCamera();

/*
			Description : 
					Get interface type for camera.
			Parameters :
					[IN] nIndex : One of camera list's index.
			Return Values :
					NEPTUNE_DEV_TYPE_UNKNOWN
							Camera interface type is unknown.
					NEPTUNE_DEV_TYPE_GIGE
							Camera interface type is GigE.
					NEPTUNE_DEV_TYPE_1394
							Camera interface type is 1394.
					NEPTUNE_DEV_TYPE_USB3
							Camera interface type is USB3.
*/
		ENeptuneDevType API_CALLTYPE GetDeviceTypeFromIndex(_uint32_t nIndex);

/*
			Description : 
					Get interface type for camera.
			Parameters :
					[IN] strSerial : One of camera list's serial number.
			Return Values :
					NEPTUNE_DEV_TYPE_UNKNOWN
							Camera interface type is unknown.
					NEPTUNE_DEV_TYPE_GIGE
							Camera interface type is GigE.
					NEPTUNE_DEV_TYPE_1394
							Camera interface type is 1394.
					NEPTUNE_DEV_TYPE_USB3
							Camera interface type is USB3.
*/
		ENeptuneDevType API_CALLTYPE GetDeviceTypeFromSerial(_char_t* strSerial);

/*
			Description : 
					Get cameras list from connected to the system.
			Parameters :
					[OUT] List : A Information for camera list.
					[IN]  nSize : A count for camera list.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CDeviceManager class is not created.
					NEPTUNE_ERR_DeviceInfo
							Connected device is not existed.
					NEPTUNE_ERR_InvalidArraySize
							nSize value is a small compared with count of camera list.
*/
		ENeptuneError API_CALLTYPE GetCameraList(NEPTUNE_CAM_INFO* pInfo, _uint32_t nSize);
/*
			Description :
					Register callback function called when number of device changed.
			Parameters : 
					[IN] functionPtr : Callback function.
					[IN,Optional] pContext : User parameter passed to the callback function.
			Return Values : 
					None.
*/
		_void_t API_CALLTYPE RegisterDeviceCheckListener(NeptuneCDevCheckCallback functionPtr, _void_t* pContext=NULL);

/*
			Description : 
					Unregister callback function for registered to RegisterDeviceCheckListener function.
			Parameters : 
					None.
			Return Values :
					None.
*/
		_void_t API_CALLTYPE UnregisterDeviceCheckListener();

/*
			Description : 
					Get last error message.
			Parameters : 
					[OUT] strErrMsg : Error message.
					[OUT] pnLen : Length of strErrMsg.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CDeviceManager class is not created.
*/
		ENeptuneBoolean API_CALLTYPE GetError(_char_t* strErrMsg, _uint32_t* pnLen);

/*
			Description : 
					Get last error message.
			Parameters : 
					[OUT] peError : Error message.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CDeviceManager class is not created.
*/
		ENeptuneBoolean API_CALLTYPE GetError(ENeptuneError* peError);

/*
			Description : 
					Get camera discovery time.
			Parameters :
					None.
			Return Values :
				    Current camera discovery time.
*/
		_uint32_t API_CALLTYPE GetDeviceCheckTime();

/*
			Description : 
					Get camera discovery time.
			Parameters :
					[IN] nTime : Device check time.
			Return Values :
				    None.
*/
		_void_t API_CALLTYPE SetDeviceCheckTime(_uint32_t nTime);


		ENeptuneError API_CALLTYPE GetCameraList(vector<NEPTUNE_CAM_INFO>& List);

		_void_t API_CALLTYPE SetCameraListOpt(ENeptuneCameraListOpt eCameraListOpt);
		
		ENeptuneCameraListOpt API_CALLTYPE GetCameraListOpt();

	protected:

	private:
		CDeviceManager();
		~CDeviceManager();		

		friend class CCameraInstance;
		friend class C1394CameraInstance;
		friend class CGigECameraInstance;
		friend class CUSBCameraInstance;
		friend class CCommonProperties;
		friend class C1394Properties;
		friend class CGigEProperties;
		friend class CUSBProperties;
		
		friend ENeptuneError API_CALLTYPE NeptuneClassLib::InitLibrary();
		friend ENeptuneError API_CALLTYPE NeptuneClassLib::UninitLibrary();

		class CDeviceManagerImpl;	
		CDeviceManagerImpl* m_pDeviceImpl;

	};
}

#endif /*NEPTUNE_DEVICEMANAGER_H*/