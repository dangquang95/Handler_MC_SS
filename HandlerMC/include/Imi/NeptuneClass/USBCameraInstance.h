#ifndef NEPTUNE_USBCAMERAINSTANCE_H
#define NEPTUNE_USBCAMERAINSTANCE_H

#include "CameraInstance.h"
#include "USBProperties.h"

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								USB Camera Control
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API CUSBCameraInstance : public CCameraInstance, public CUSBProperties
	{
	public:
		CUSBCameraInstance();
		CUSBCameraInstance(INeptuneDevice* pDevice, ENeptuneDevAccess eAccessFlag=NEPTUNE_DEV_ACCESS_EXCLUSIVE);
		~CUSBCameraInstance();

/*
			Description :
					Create USB3 camera instance to control.
			Parameters :
			        [IN] pDevice : Object of INeptuneDeivce.
					[IN] eAccessFlag : Set to camera's access privilege. 
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
							Device open from TL.
					NEPTUNE_ERR_DeviceCheck
							Camera interface is not USB3.
*/
		ENeptuneError API_CALLTYPE CameraOpen(INeptuneDevice* pDevice, ENeptuneDevAccess eAccessFlag=NEPTUNE_DEV_ACCESS_EXCLUSIVE);
	
/*
			Description : 
					Delete USB3 camera instance.
			Parameters :
					None.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCameraInstance class is not created.
					NEPTUNE_ERR_Fail
							Camera close error.
*/		
		ENeptuneError API_CALLTYPE CameraClose();

	protected:

	private:
		CUSBCameraInstance(const CUSBCameraInstance&);
		CUSBCameraInstance& operator=(const CUSBCameraInstance& other); 

	};
}

#endif /*NEPTUNE_USBCAMERAINSTANCE_H*/