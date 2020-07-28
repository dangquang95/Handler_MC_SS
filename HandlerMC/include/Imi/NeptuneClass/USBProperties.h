#ifndef NEPTUNE_USBPROPERTIES_H
#define NEPTUNE_USBPROPERTIES_H

#include "CommonProperties.h"

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								USB Camera Properties
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API CUSBProperties
	{
	public:

/*
			Description :
				Set video mode of a camera.
			Parameters :
				[IN] eVideoMode : NTSC or PAL
			Return Values :
				NEPTUNE_ERR_Success
					Success.
				NEPTUNE_ERR_NotInitialized
					Object of CUSBProperties class is not created.
				NEPTUNE_ERR_Fail
					Video mode set failed.
*/
		ENeptuneError API_CALLTYPE SetNTSCPALSelector(ENeptuneVideoMode eVideoMode); 

/*
			Description :
				Get video mode from a camera.
			Parameters :
				[OUT] peVideoMode : NTSC or PAL
			Return Values :
				NEPTUNE_ERR_Success
					Success.
				NEPTUNE_ERR_NotInitialized
					Object of CUSBProperties class is not created.
				NEPTUNE_ERR_Fail
					Video mode get failed.
*/
		ENeptuneError API_CALLTYPE GetNTSCPALSelector(ENeptuneVideoMode* peVideoMode); 

/*
			Description :
				Set acquisition fps of a camera.
			Parameters :
				[IN] eFPS : FPS_30or25 or FPS_60or50
			Return Values :
				NEPTUNE_ERR_Success
					Success.
				NEPTUNE_ERR_NotInitialized
					Object of CUSBProperties class is not created.
				NEPTUNE_ERR_Fail
					Acquisition fps set failed.				
*/
		ENeptuneError API_CALLTYPE SetAcquisitionFrameRateSel(ENeptuneAcqFPS eFPS);

/*
			Description :
				Get acquisition fps from a camera.
			Parameters :
				[OUT] peFPS : FPS_30or25 or FPS_60or50
			Return Values :
				NEPTUNE_ERR_Success
					Success.
				NEPTUNE_ERR_NotInitialized
					Object of CUSBProperties class is not created.
				NEPTUNE_EFF_Fail
					Acquisition fps get failed.				
*/
		ENeptuneError API_CALLTYPE GetAcquisitionFrameRateSel(ENeptuneAcqFPS* peFPS);


/*
			Description :
				Get acquisition fps list from a camera.
			Parameters :
				[IN] peList : List of acquisition fps.
				[OUT] pnSize : Count of list.
			Return Values :
				NEPTUNE_ERR_Success
					Success.
				NEPTUNE_ERR_NotInitialized
					Object of CUSBProperties class is not created.
				NEPTUNE_ERR_Fail
					Acquisition fps list get failed.
*/
		ENeptuneError API_CALLTYPE GetAcquisitionFrameRateList(ENeptuneAcqFPS* peList, _uint32_t* pnSize);

/*
			Description :
				Set resolution of a camera.
			Parameters :
				[IN] eResolution : 1920x1080 or 1280x720
			Return Values :
				NEPTUNE_ERR_Success
					Success.
				NEPTUNE_ERR_NotInitialized
					Object of CUSBProperties class is not created.
				NEPTUNE_ERR_Fail
					Resolution set failed.				
*/
		ENeptuneError API_CALLTYPE SetResolutionSelector(ENeptuneResolution eResolution);

/*
			Description :
				Get resolution from a camera.
			Parameters :
				[OUT] peResolution : 1920x1080 or 1280x720
			Return Values :
				NEPTUNE_ERR_Success
					Success.
				NEPTUNE_ERR_NotInitialized
					Object of CUSBProperties class is not created.
				NEPTUNE_ERR_Fail
					Resolution get failed.				
*/
		ENeptuneError API_CALLTYPE GetResolutionSelector(ENeptuneResolution* peResolution);

/*
			Description :
				Get resolution list from a camera.
			Parameters :
				[IN] peList : List of resolution.
				[OUT] pnSize : Count of list.
			Return Values :
				NEPTUNE_ERR_Success
					Success.
				NEPTUNE_ERR_NotInitialized
					Object of CUSBProperties class is not created.
				NEPTUNE_ERR_Fail
					Acquisition fps list get failed.
*/
		ENeptuneError API_CALLTYPE GetResolutionList(ENeptuneResolution* peList, _uint32_t* pnSize);

/*
			Description :
				Set DayNight mode of a camera.
			Parameters :
				[IN] eDayNightMode : DayNight mode.
			Return Values :
				NEPTUNE_ERR_Success
					Success.
				NEPTUNE_ERR_NotInitialized
					Object of CUSBProperties class is not created.
				NEPTUNE_ERR_Fail
					DayNight mode set failed.				
*/
		ENeptuneError API_CALLTYPE SetDayNightModeSelector(ENeptuneDayNightMode eDayNightMode);

/*
			Description :
				Get DayNight mode from a camera.
			Parameters :
				[OUT] peDayNightMode :DayNight mode.
			Return Values :
				NEPTUNE_ERR_Success
					Success.
				NEPTUNE_ERR_NotInitialized
					Object of CUSBProperties class is not created.
				NEPTUNE_ERR_Fail
					DayNight mode get failed.				
*/
		ENeptuneError API_CALLTYPE GetDayNightModeSelector(ENeptuneDayNightMode *peDayNightMode);

	protected:
		CUSBProperties();
		~CUSBProperties();
		
	private:
		friend class CUSBCameraInstance;

		class CUSBPropImpl;	
		CUSBPropImpl* m_pUSBPropImpl;

	};
}


#endif /*NEPTUNE_USBPROPERTIES_H*/