#ifndef NEPTUNE_EVENTLISTENER_H
#define NEPTUNE_EVENTLISTENER_H

#include "NeptuneClassLib.h"
#include "CameraInstance.h"
#include "FrameData.h"

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								Camera Event
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API CEventListener
	{
	public:
		CEventListener();
		~CEventListener();

/*
			Description : 
					Receive the camera's connected event.
			Parameters :
					[IN] camera : Camera object.
					[OUT] pParam : User parameter passed to the callback function.  
			Return Values :
					None.
*/
		virtual _void_t CALLBACK OnDeviceConnected(CCameraInstance& camera, _void_t* pParam=NULL);

/*
			Description : 
					Receive the camera's disconnected event.
			Parameters :
					[IN] camera : Camera object.
					[OUT] pParam : User parameter passed to the callback function.  
			Return Values :
					None.
*/
		virtual _void_t CALLBACK OnDeviceDisconnected(CCameraInstance& camera, _void_t* pParam=NULL);

/*
			Description : 
					Receive the camera's frame dropped event.
			Parameters :
					[IN] camera : Camera object.
					[OUT] pParam : User parameter passed to the callback function.  
			Return Values :
					None.
*/
		virtual _void_t CALLBACK OnFrameDropped(CCameraInstance& camera, _void_t* pParam=NULL);

/*
			Description : 
					Receive the camera's frame timeout event.
			Parameters :
					[IN] camera : Camera object.
					[OUT] pParam : User parameter passed to the callback function.  
			Return Values :
					None.
*/
		virtual _void_t CALLBACK OnFrameReceiveTimeout(CCameraInstance& camera, _void_t* pParam=NULL);

	protected:

	private:

	};
}

#endif /*NEPTUNE_EVENTLISTENER_H*/