#ifndef NEPTUNE_GIGECAMERAINSTANCE_H
#define NEPTUNE_GIGECAMERAINSTANCE_H

#include "CameraInstance.h"
#include "GigEProperties.h"

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								GigE Camera Control
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API CGigECameraInstance : public CCameraInstance, public CGigEProperties
	{
	public:
		CGigECameraInstance();
		CGigECameraInstance(INeptuneDevice* pDevice, ENeptuneDevAccess eAccessFlag=NEPTUNE_DEV_ACCESS_EXCLUSIVE);
		~CGigECameraInstance();

/*
			Description :
					Create GigE camera instance to control.
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
							Camera interface is not GigE.
*/
		ENeptuneError API_CALLTYPE CameraOpen(INeptuneDevice* pDevice, ENeptuneDevAccess eAccessFlag=NEPTUNE_DEV_ACCESS_EXCLUSIVE);
		
/*
			Description : 
					Delete GigE camera instance.
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
		CGigECameraInstance(const CGigECameraInstance&);
		CGigECameraInstance& operator=(const CGigECameraInstance& other);
	};
}

#endif /*NEPTUNE_GIGECAMERAINSTANCE_H*/