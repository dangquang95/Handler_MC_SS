#ifndef NEPTUNE_GIGEPROPERTIES_H
#define NEPTUNE_GIGEPROPERTIES_H

#include "CommonProperties.h"

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								GigE Camera Properties
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API CGigEProperties
	{
	public:

/*
			Description :
					Set camera access permission.
			Parameters :
					[IN] eMode : Device access mode.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_Fail
							Camera permission set failed.
*/
		ENeptuneError API_CALLTYPE SetAccessMode(ENeptuneDevAccess eMode);

/*
			Description :
					Get current camera access permission.
			Parameters :
					None.
			Return Values :
					Device access mode.
*/
		ENeptuneDevAccess API_CALLTYPE GetAccessMode();

/*
			Description :
					Set the heartbeat time of GigE camera.
			Parameters :
					[IN] nTime : Heartbeat time in mili-second unit.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_OutofRange
							nTime value is out of range.
					NEPTUNE_ERR_Fail
							Heartbeat time set failed.
*/
		ENeptuneError API_CALLTYPE SetHeartbeatTime(_uint32_t nTime);

/*
			Description :
					Get the heartbeat time of GigE camera.
			Parameters :
					[OUT] pnTime : Heartbeat time in mili-second unit.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_Fail
							Heartbeat time get failed.					
*/
		ENeptuneError API_CALLTYPE GetHeartbeatTime(_uint32_t* pnTime);

/*
			Description :
					Get camera's IP address.
			Parameters : 
					[Out] pstrIP : IP address.
					[Out] pnSize : A string length for IP address.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_Fail
							IP address get failed.
*/
		ENeptuneError API_CALLTYPE GetIPAddress(_char_t* pstrIP, _uint32_t* pnSize);

/*
			Description :
					Set stream mode to a camera.
			Parameters :
					[IN] eMode : Stream mode.
					[IN] strIP : IP address.(valid only if the eMode is NEPTUNE_STRM_MULTICAST)
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_Fail
							Stream mode set failed.
*/
		ENeptuneError API_CALLTYPE SetStreamMode(ENeptuneStreamMode eMode, _char_t* strIP="239.0.5.21");

/*
			Description :
					Get stream mode from a camera.
			Parameters :
					[OUT] peMode : Stream mode.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_Fail
							Stream mode get failed.
*/
		ENeptuneError API_CALLTYPE GetStreamMode(ENeptuneStreamMode* peMode);
		
/*
			Description :
					Set camera user name to a camera.
			Parameters :
					[IN] strUser : User name.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_Fail
							User name Set failed.
*/
		ENeptuneError API_CALLTYPE SetUserID(_char_t* strUser);

/*
			Description :
					Get camera user name from a camera.
			Parameters :
					[Out] pstrUser : User name.
					[Out] pnSize : A string length for User name.					
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_Fail
							User name get failed.
*/
		ENeptuneError API_CALLTYPE GetUserID(_char_t* pstrUser, _uint32_t* pnSize);

/*
			Description :
					Get camera MAC address from a camera.
			Parameters :
					[Out] pstrMAC : MAC address.
					[Out] pnSize : A string legnth for MAC address.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_Fail
							MAC address get failed.
*/
		ENeptuneError API_CALLTYPE GetMACAddress(_char_t* pstrMAC, _uint32_t* pnSize);

/*
			Description :
					Set multicast address to a camera. 
			Parameters :
					[IN] strIP : Multicast ip address.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_OutOfRange
							Valid address range is 224.0.0.0 to 239.255.255.255
					NEPTUNE_ERR_Fail
							Multicast address set failed!
*/
		ENeptuneError API_CALLTYPE SetMulticastAddress(_char_t* strIP);

/*
			Description :
					Set binning of Image data.
			Parameters :
					[IN] bBinning : Enable to binning.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.	
					NEPTUNE_ERR_Fail
							To Fail Horizontal, vertical binning apply.
*/
		ENeptuneError API_CALLTYPE SetBinning(ENeptuneBoolean bBinning);

/*
			Description :
					Get current binning status.
			Parameters :
					[OUT] pbBinning : Binning status.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.	
					NEPTUNE_ERR_Fail
							Binning status get failed.
*/
		ENeptuneError API_CALLTYPE GetBinning(ENeptuneBoolean* pbBinning);

/*
			Description :
					Get GigE camera packet size.
			Parameters :
					[OUT] pnByte : Stream packet size.
					[OUT, Optional] pnMin : Minimum stream packet size value supported by a camera. 
					[OUT, Optional] pnMax : Maximum stream packet size value supported by a camera.
			Return  Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.	
					NEPTUNE_ERR_Fail
							Stream packet size get failed.					
*/
		ENeptuneError API_CALLTYPE GetStreamPacketSize(_uint32_t* pnByte, _uint32_t* pnMin=NULL, _uint32_t* pnMax=NULL);

/*
			Description :
					Set GigE camera packet size.
			Parameters :
					[IN] nByte : Stream packet size.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_OutOfRange
							nByte value is invalid.
					NEPTUNE_ERR_Fail
							Stream packet size get failed.					
*/
		ENeptuneError API_CALLTYPE SetStreamPacketSize(_uint32_t nByte);
	
/*
			Description :
					Get auto area control setting value from a camera.
			Parameters :
					[IN] nSelect : AutoExposure(0), AutoWhiteBalance(1), AutoFocus(2)
					[OUT] pArea : Current auto area setting value
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Auto area control is not supported in camera.
					NEPTUNE_ERR_Fail
							Auto area control setting value get failed.
					
*/
		ENeptuneError API_CALLTYPE GetAutoAreaControl(ENeptuneAutoAreaSelect eSelect, NEPTUNE_AUTOAREA* pArea);
		
/*
			Description :
					Set auto area control setting value to a camera.
			Parameters :
					[IN] nSelect : Auto Area mode.
					[IN] pArea : Auto area setting value
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Auto area control is not supported in camera.
					NEPTUNE_ERR_Fail
							Auto area control value set failed.
*/
		ENeptuneError API_CALLTYPE SetAutoAreaControl(ENeptuneAutoAreaSelect eSelect, NEPTUNE_AUTOAREA Area);
		
/*
			Description :
					Set auto focus control to a camera.
			Parameters :
					[IN] eControlMode : Auto focus mode.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Auto focus control is not supported in camera.
					NEPTUNE_ERR_TImeout
							Timeout occurred for Auto focus setting.
					NEPTUNE_ERR_InvalidParameter
							eControlMode value is invalid.
					NEPTUNE_ERR_Fail
							Auto focus control value set failed.
*/
		ENeptuneError API_CALLTYPE SetAutoFocusControl(ENeptuneAFMode eControlMode);
		
/*
			Description :
					Get package feature information from a camera.
			Parameters :
					[OUT] pPackageFeature : Package feature information.
			Return  Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.	
					NEPTUNE_ERR_Fail
							Package information get failed.				
*/
		ENeptuneError API_CALLTYPE GetPackageFeature(NEPTUNE_PACKAGE_FEATURE* pPackageFeature);

/*
			Description :
					Set package feature information to a camera.
			Parameters :
					[OUT] pPackageFeature : Package feature information.
			Return  Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CGigEProperties class is not created.	
					NEPTUNE_ERR_Fail
							Package information set failed.				
*/
		ENeptuneError API_CALLTYPE SetPackageFeature(NEPTUNE_PACKAGE_FEATURE PackageFeature);	

	protected:
		CGigEProperties();
		~CGigEProperties();

	private:
		friend class CGigECameraInstance;

		class CGigEPropImpl;	
		CGigEPropImpl* m_pGigEPropImpl;

	};
}


#endif /*NEPTUNE_GIGEPROPERTIES_H*/