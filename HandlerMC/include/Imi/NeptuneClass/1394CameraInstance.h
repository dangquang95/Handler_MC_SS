#ifndef NEPTUNE_1394CAMERAINSTANCE_H
#define NEPTUNE_1394CAMERAINSTANCE_H

#include "CameraInstance.h"
#include "1394Properties.h"

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								1394 Camera Control
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API C1394CameraInstance : public CCameraInstance, public C1394Properties
	{
	public:
		C1394CameraInstance();
		C1394CameraInstance(INeptuneDevice* pDevice, ENeptuneDevAccess eAccessFlag=NEPTUNE_DEV_ACCESS_EXCLUSIVE);
		~C1394CameraInstance();

/*
			Description :
					Create 1394 camera instance to control.
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
							Camera open error.
					NEPTUNE_ERR_DeviceCheck
							Camera interface is not 1394.
*/
		ENeptuneError API_CALLTYPE CameraOpen(INeptuneDevice* pDevice, ENeptuneDevAccess eAccessFlag=NEPTUNE_DEV_ACCESS_EXCLUSIVE);
		
/*
			Description : 
					Delete 1394 camera instance.
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
		C1394CameraInstance(const C1394CameraInstance&);
		C1394CameraInstance& operator=(const C1394CameraInstance& other); 

	};
}

#endif /*NEPTUNE_1394CAMERAINSTANCE_H*/