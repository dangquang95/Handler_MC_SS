#ifndef NEPTUNE_COMMONPROPERTIES_H
#define NEPTUNE_COMMONPROPERTIES_H

#include "XMLDescription.h"
#include "FrameData.h"

#include <vector>

using namespace std;

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								Camera Property
	//
	////////////////////////////////////////////////////////////////////////////////////////
	class NEPTUNE_CLASS_API CCommonProperties : public CXMLDescription
	{
	public:

/*
			Description : 
					Get information of a camera.
			Parameters :
					[OUT] pInfo : Camera information.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
*/
		ENeptuneError API_CALLTYPE GetCameraInfo(NEPTUNE_CAM_INFO* pInfo);	

/*
			Description :
					Get the current acquisition information of a camera.
			Parameters :
					[OUT] pbAcquisition : Current acquisition status.
					[OUT] peMode : Current acquisition mode.
					[OUT] pnMultiFrameCount : Frame number.(valid only if the peMode is NEPTUNE_ACQ_MULTIFRAME)
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							Acquisition information get failed.
*/
		ENeptuneError API_CALLTYPE GetAcquisition(ENeptuneBoolean* pbAcquisition, ENeptuneAcquisitionMode* peMode=NULL, _uint32_t* pnMultiFrameCount=NULL);
	
/*
			Description : 
					Set the acquisition mode of a camera.
			Parameters :
					[IN] eMode : Acquisition mode.
					[IN] nMultiFrameCount : Multi frame image count.(valid only if the eMode is NEPTUNE_ACQ_MULTIFRAME)
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_OutOfRange
							pnMultiFrameCount's value is out of range. 
					NEPTUNE_ERR_Fail
							Acquisition mode set failed.
*/
		ENeptuneError API_CALLTYPE SetAcquisitionMode(ENeptuneAcquisitionMode eMode=NEPTUNE_ACQ_CONTINUOUS, _uint32_t nMultiFrameCount=2);

/*
			Description : 
					Number of bits per pixel of image data.
			Parameter : 
					None.
			Return Values :
					Bit per pixel value. (8, 12, 16 ..)
*/
		_uint32_t API_CALLTYPE GetBitPerPixel();

/*
			Description : 
					Get buffer's data size.
			Parameter :
					None.
			Return Values :
					Buffer size.(width * height * color depth)
			
			cf. color depth
			Mono8 : 1, Mono16 : 2, YUV422 : 2, RGB24 : 3..
*/
		_uint32_t API_CALLTYPE GetBufferSize();
		
/*
			Description :
					Get the current size information of an image.
			Parameter :
					[OUT] pImageSize : Image size information.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInititalized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							Image size Information get failed.
*/
		ENeptuneError API_CALLTYPE GetImageSize(NEPTUNE_IMAGE_SIZE* pImageSize);	
	
/*
			Description :
					Get the max size information of an image.
			Parameter :
					[OUT] pImageSize : Image size information.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							Image size information get failed.
*/
		ENeptuneError API_CALLTYPE GetMaxImageSize(NEPTUNE_IMAGE_SIZE* pImageSize);
		
/*
			Description :
					Set the image size of a camera.
			Parameter :
					[IN] ImageSize : Image size information.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							1394Camera is supported Format7 only.
					NEPTUNE_ERR_OutOfRange
							Image size is not a multiple of 4.
					NEPTUNE_ERR_Fail
							Image size set failed.
*/
		ENeptuneError API_CALLTYPE SetImageSize(NEPTUNE_IMAGE_SIZE ImageSize);

/*
			Description :
					Get the supported pixel format list of a camera.
			Parameter :
					[OUT] peList, pstrList : A list for pixel format.
					[OUT] pnSize : A count for pixel format list.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_InvalidArraySize
							pnSize's value is a small compared with count of camera pixel format list.
					NEPTUNE_ERR_Fail
							Pixel format list get failed.
*/
		ENeptuneError API_CALLTYPE GetPixelFormatList(ENeptunePixelFormat* peList, _uint32_t* pnSize);
		ENeptuneError API_CALLTYPE GetPixelFormatList(_char_t** pstrList, _uint32_t* pnSize);
/*
			Description : 
					Set the pixel format to a camera.
			Parameter :
					[IN] ePixelFormat, strPixelFormat : Pixel format of a camera.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							ePixelFormat/strPixelFormat is invalid.
					NEPTUNE_ERR_Fail
							Pixel format set failed.
*/
		ENeptuneError API_CALLTYPE SetPixelFormat(ENeptunePixelFormat ePixelFormat);
		ENeptuneError API_CALLTYPE SetPixelFormat(_char_t* strPixelFormat);
/*
			Description :
					Get the pixel format from a camera.
			Parameter :
					[IN] pePixelFormat, pstrPixelFormat : Pixel format of a camera.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Unknown pixel format.
					NEPTUNE_ERR_Fail
							Pixel format get failed.
*/							
		ENeptuneError API_CALLTYPE GetPixelFormat(ENeptunePixelFormat* pePixelFormat);
		ENeptuneError API_CALLTYPE GetPixelFormat(_char_t* pstrPixelFormat, _uint32_t* pnLen);
		
/*
			Description :
					Get the supported frame rate list from a camera.
			Parameter :
					[OUT] peList, pstrList : A list for frame rate.
					[IN/OUT] pnSize : A count for frame rate list.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Error is caused by a camera interface type is IEEE1394 and pixel format is selected Format7.
					NEPTUNE_ERR_InvalidArraySize
							pnSize's value is a small compared with count of camera frame rate list.
					NEPTUNE_ERR_Fail
							Frame rate list get failed.		
*/				
		ENeptuneError API_CALLTYPE GetFrameRateList(ENeptuneFrameRate* peList, _uint32_t* pnSize);
		ENeptuneError API_CALLTYPE GetFrameRateList(_char_t** pstrList, _uint32_t* pnSize);		

/*
			Description :
					Get the frame rate from a camera.
			Parameter :
					[OUT] peRate, pstrRate, pfValue : Frame rate of a camera.
					[OUT] nLen : Length of pstrRate.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Error is caused by a camera interface type is IEEE1394 and pixel format is selected Format7.
*/
		ENeptuneError API_CALLTYPE GetFrameRate(ENeptuneFrameRate* peRate, _double_t* pfValue);
		ENeptuneError API_CALLTYPE GetFrameRate(_char_t* pstrRate, _uint32_t* pnLen);

/*
			Description :
					Set the frame rate to a camera.
			Parameter :
					[IN] eRate, strRate, fValue : Frame rate of a camera.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Error is caused by a camera interface type is IEEE1394 and pixel format is selected Format7.
					NEPTUNE_ERR_OutOfRange
							Frame rate's value is out of range. 							
					NEPTUNE_ERR_Fail
							Frame rate set failed.
*/
		ENeptuneError API_CALLTYPE SetFrameRate(ENeptuneFrameRate eRate, _double_t fValue=0);
		ENeptuneError API_CALLTYPE SetFrameRate(_char_t* strRate);
		
/*
			Description :
					Set bayer conversion method and bayer pattern layout to one frame image.
			Parameter :
					[OUT] pOutput : Converted data.
					[IN] nBufSize : pOutput buffer's data size.
					[IN] pData : Grabbed data information.
					[IN] eLayout : Bayer pattern layout.
					[IN] eMethod : Bayer method.
					[IN] nEffect : Apply to flip / mirror / negative or none.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_InvalidArraySize
							pOutput data's array size is invalid.
					NEPTUNE_ERR_NotSupport
							YUV pixel format is not supported.
					NEPTUNE_ERR_Fail
							Bayer conversion set failed.
*/
		ENeptuneError API_CALLTYPE SetBayer(_void_t* pOutput, _uint32_t nBufSize, CFrameDataPtr& pData, ENeptuneBayerLayout eLayout, ENeptuneBayerMethod eMethod, _uint32_t nEffect);
		
/*
			Description :
					Set Image effect to one frame image.
			Parameter :
					[OUT] pOutput : Converted data.
					[IN] nBufSize : pOutput buffer's data size.
					[IN] pData : Grabbed data information.
					[IN] nEffect : Apply to flip / mirror / negative or none.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_InvaludArraySize
							pOutput data's array size is invalid.
					NEPTUNE_ERR_Fail
							Image effect set failed.
*/
		ENeptuneError API_CALLTYPE SetEffect(_void_t* pOutput, _uint32_t nBufSize, CFrameDataPtr& pData, _uint32_t nEffect);
		
/*
			Description : 
					Save image file for extension *.bmp, *.jpg, *.tif.
			Parameter :
					[IN] strFileName : Image file name.(Including the file extension)
					[IN] pData : Grabbed data information.
					[IN] nWidth : Width of image data.
					[IN] nHeight : Height of image data.
					[IN] eFormat : Pixel format of image data.
					[IN] pInput : Converted data.
					[IN] nBufSize : Size of converted data.
					[IN] nQuality : Jpeg image quality.(valid only when save to JPEG)
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_InvalidAddress
							When save to raw data, pInput was entered to a parameter.
					NEPTUNE_ERR_InvalidArraySize
							When save to converted data, nBufSize should not a zero.
					NEPTUNE_ERR_InvalidParameter
							File extension is invalid.
					NEPTUNE_ERR_Fail
							To Image file save was failed.
*/
		ENeptuneError API_CALLTYPE SaveImage(_char_t* strFileName, CFrameDataPtr& pData, const _void_t* pInput=NULL, _uint32_t nBufSize=0, _int32_t nQuality=80);
		ENeptuneError API_CALLTYPE SaveImage(_char_t* strFileName, _uint32_t nWidth, _uint32_t nHeight, ENeptunePixelFormat eFormat, const _void_t* pInput=NULL, _uint32_t nBufSize=0, _int32_t nQuality=80);
/*
			Description : 
					Control camera to transfer a single image frame.
					Acquisition mode should be set as NEPTUNE_ACQ_SINGLEFRAME
			Parameter :
					None.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							Camera is not playing.
*/
		ENeptuneError API_CALLTYPE OneShot();

/*
			Description :
					Control camera to transfer a multiple image frames.
					Acquisition mode should be set a NEPTUNE_ACQ_MULTIFRAME
			Parameter :
					None.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							Camera is not playing
*/
		ENeptuneError API_CALLTYPE MultiShot();

/*
			Description :
					Set trigger values to a camera.
			Parameters :
					[IN] Trigger : Trigger value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail;
							Trigger value set failed.
*/
		ENeptuneError API_CALLTYPE SetTrigger(NEPTUNE_TRIGGER Trigger);

/*
			Description : 
					Set trigger delay value to a camera.
			Parameters : 
					[IN] nDealy : Trigger delay value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_OutOfRange
							nDelay's value is out of range. 
					NEPTUNE_ERR_Fail
							Trigger delay value set failed.						
*/
		ENeptuneError API_CALLTYPE SetTriggerDelay(_uint32_t nDelay);

/*
			Description : 
					Make camera to load specific trigger table.
			Parameters : 
					[IN] Table : Trigger table.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Trigger mode12 and mode13 only applied. 
					NEPTUNE_ERR_Fail
							Trigger table save failed.
*/
		ENeptuneError API_CALLTYPE SaveTriggerTable(NEPTUNE_TRIGGER_TABLE Table);

/*
			Description :
					Set exposure setting for trigger mode14.
			Parameters :
					[IN] nNumber : Frames of number. 
					[IN] nDuration : Exposure time for trigger mode14.
					[IN] nInterval : Interval time for trigger mode14.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_OutOfRange
							nNumber's value is out of range.
					NEPTUNE_ERR_Fail
							Trigger mode14 exposure set failed. 
*/
		ENeptuneError API_CALLTYPE SetTriggerMode14Exposure(_uint32_t nNumber, _uint32_t nDuration, _uint32_t nInterval);

/*
			Description :
					Get trigger information supported by a camera.
			Parameters : 
					[OUT] pInfo : Trigger information.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							A camera is not supported trigger feature.
					NEPTUNE_ERR_Fail
							Trigger information get failed.
*/
		ENeptuneError API_CALLTYPE GetTriggerInfo(NEPTUNE_TRIGGER_INFO* pInfo);

/*
			Description :
					Get current trigger values.
			Parameters :
					[OUT] pTrigger : Trigger value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							Trigger value get failed.
*/
		ENeptuneError API_CALLTYPE GetTrigger(NEPTUNE_TRIGGER* pTrigger);

/*
			Description :
					Get current trigger delay value.
			Parameters :
					[OUT] pnDelay : Current trigger delay value.
					[OUT, Optional] pnMin : Minimum trigger value supported by a camera.
					[OUT, Optional] pnMax : Maximum trigger value supported by a camera.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							Trigger delay value set failed.	
*/			
		ENeptuneError API_CALLTYPE GetTriggerDelay(_uint32_t* pnDelay, _uint32_t* pnMin=NULL, _uint32_t* pnMax=NULL);

/*
			Description :
					Read trigger table from a camera.
			Parameters :
					[OUT] pTable : Trigger table.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Trigger mode12 and mode13 only applied.
					NEPTUNE_ERR_Fail
							Trigger table read failed.
*/
		ENeptuneError API_CALLTYPE ReadTriggerTable(NEPTUNE_TRIGGER_TABLE* pTable);

/*
			Description :
					Make camera to load specific trigger table.
			Parameters :
					[OUT] pTable : Trigger table.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Trigger mode12 and mode13 only applied.
					NEPTUNE_ERR_Fail
							Trigger table load failed.			
*/
		ENeptuneError API_CALLTYPE LoadTriggerTable(_uint32_t nIndex);

/*
			Description :
					Generate software trigger.
			Parameters :
					None.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							S/W trigger is not supported.
					NEPTUNE_ERR_Fail
							Trigger source get failed.
*/
		ENeptuneError API_CALLTYPE RunSoftwareTrigger();
	
/*
			Description :
					Set strobe value to a camera.
			Parameters :
					[IN] Strobe : Strobe value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_OutOfRange
							Strobe delay or duration value is out of range. 
					NEPTUNE_ERR_Fail
							Strobe value set failed.
*/
		ENeptuneError API_CALLTYPE SetStrobe(NEPTUNE_STROBE Strobe);

/*
			Description :
					Get the strobe information supported by a camera.
			Parameters :
					[IN] pInfo : Strobe information.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							A camera is not supported strobe feature.
					NEPTUNE_ERR_Fail
							Strobe information get failed.
*/
		ENeptuneError API_CALLTYPE GetStrobeInfo(NEPTUNE_STROBE_INFO* pInfo);
	
/*
			Description :
					Read strobe value from a camera.
			Parameters :
					[IN] pStrobe : Strobe value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							Strobe value get error.
*/
		ENeptuneError API_CALLTYPE GetStrobe(NEPTUNE_STROBE* pStrobe);

/*
			Description :
					Set feature value to a camera.
			Parameters :
					[IN] eFeature : Feature.
					[IN] Feature : Feature information.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Feature is not supported in a camera.
					NEPTUNE_ERR_AccessDenied
							Feature's access permission is read only. 
					NEPTUNE_ERR_Fail
							Feature value set failed.
*/
		ENeptuneError API_CALLTYPE SetFeature(ENeptuneFeature eFeature, NEPTUNE_FEATURE Feature);

/*
			Description :
					Get feature value from a camera.
			Parameters :
					[IN] eFeature : Feature.
					[OUT] pFeature : Feature information.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Feature is not supported in a camera.
					NEPTUNE_ERR_Fail
							Feature value get failed.
*/
		ENeptuneError API_CALLTYPE GetFeature(ENeptuneFeature eFeature, NEPTUNE_FEATURE* pFeature);
	
/*
			Description :
					Get supported user set by a camera.
			Parameters :
					[OUT] pUserSet : User set information.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							User set is not supported in a camera.
					NEPTUNE_ERR_Fail
							User set get failed.
*/
		ENeptuneError API_CALLTYPE GetUserSet(NEPTUNE_USERSET* pUserSet);

/*
			Description : 
					Save or load user set.
					If user set command is NEPTUNE_USERSET_CMD_SAVE, use set value is saved.
					If user set command is NEPTUNE_USERSET_CMD_LOAD, user set value is loaded.
			Parameters :
					[IN] UserSet : User set value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_OutOfRange
							User set index value is out of range. 
					NEPTUNE_ERR_Fail
							User set load/save failed.
*/
		ENeptuneError API_CALLTYPE SetUserSet(NEPTUNE_USERSET UserSet);

/*
			Description :
					Make specific user set as a default user set.
			Parameters :
					[IN] eUserSet : User set value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_OutOfRange
							User set index value is out of range.
					NEPTUNE_ERR_Fail
							User set save failed.
*/
		ENeptuneError API_CALLTYPE SetDefaultUserSet(ENeptuneUserSet eUserSet);

/*
			Description :
					Make specific user set as a default user set when camera is power on.
			Parameters :
					[IN] eUserSet : User set value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_OutOfRange
							User set index value is out of range.
					NEPTUNE_ERR_Fail
							User set load failed.
*/
		ENeptuneError API_CALLTYPE SetPowerOnDefault(ENeptuneUserSet eUserSet);
	
/*
			Description :
					Set 4-step knee table points.
			Parameters :
					[IN] KneeLUT : 4-step knee table points.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							4-step knee table points set failed.
*/
		ENeptuneError API_CALLTYPE SetKneeLUT(NEPTUNE_KNEE_LUT KneeLUT);

/*
			Description :
					Get 4-step knee table points.
			Parameters : 
					[OUT] pKneeLUT : 4-step knee table points.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							4-step knee table points get failed.
*/
		ENeptuneError API_CALLTYPE GetKneeLUT(NEPTUNE_KNEE_LUT* pKneeLUT);

/*
			Description :
					Set user look-up-table to a camera.
			Parameters :
					[IN] UserLUT : User look-up-table value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							User look-up-table value set failed.
*/
		ENeptuneError API_CALLTYPE SetUserLUT(NEPTUNE_USER_LUT UserLUT);
		
/*
			Description :
					Get user look-up-table from a camera.
			Parameters :
					[OUT] pUserLUT : User look-up-table value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							User look-up-table value get failed.					
*/
		ENeptuneError API_CALLTYPE GetUserLUT(NEPTUNE_USER_LUT* pUserLUT);

/*
			Description :
					Set camera's serial output port enable / disable.
			Parameters :
					[IN] Property : Serial port information.
			Return Values : 
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							SIO property set failed.
*/
		ENeptuneError API_CALLTYPE SetSIO(NEPTUNE_SIO_PROPERTY Property);

/*
			Description : 
					Write serial data to a camera.
			Parameters :
					[IN] Data : Serial data.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_InvalidArraySize
							Max data size is 256.
					NEPTUNE_ERR_TimeOut
							Occurred timeout when writing a serial data from a camera.
					NEPTUNE_ERR_Fail
							Serial data write failed.
*/
		ENeptuneError API_CALLTYPE WriteSIO(NEPTUNE_SIO Data);

/*
			Description :
					Read serial data from a camera.
			Parameters :
					[Out] pData : Serial data.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Timeout
							Occurred timeout when reading a serial data from a camera.
					NEPTUNE_ERR_Fail
							Serial data read failed.
*/
		ENeptuneError API_CALLTYPE ReadSIO(NEPTUNE_SIO* pData);

/*
			Description :
					Set GPIO to a camera.
			Parameters :
					[IN] Gpio : GPIO value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_Fail
							GPIO value set failed.
*/
		ENeptuneError API_CALLTYPE SetGPIO(NEPTUNE_GPIO Gpio);

/*
			Description :
					Set Auto-iris mode to a camera.
			Parameters :
					[IN] eMode : Set Auto-iris mode to auto or manual.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Auto-iris is not supported in a camera.
					NEPTUNE_ERR_Fail
							Auto-iris mode set failed.
*/
		ENeptuneError API_CALLTYPE SetAutoIrisMode(ENeptuneAutoIrisMode eMode);
	
/*
			Description :
					Get number of frames for averaging.
			Parameters :
					[OUT] pnVal : Current Auto-iris average frame value.
					[OUT, Optional] pnMin : Minimum Auto-iris average frame value supported.
					[OUT, Optional] pnMax : Maximum Auto-iris average frame value supported.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Auto-iris is not supported in a camera.
					NEPTUNE_ERR_Fail
							Auto-iris average frame value get failed.
*/
		ENeptuneError API_CALLTYPE GetAutoIrisAverageFrame(_uint32_t* pnVal, _uint32_t* pnMin=NULL, _uint32_t* pnMax=NULL);

/*
			Description :
					Set number of frames for averaging.
			Parameters :
					[IN] nVal : Auto-iris average frame value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Auto-iris is not supported in a camera.
					NEPTUNE_ERR_Fail
							Auto-iris average frame value set failed.
*/
		ENeptuneError API_CALLTYPE SetAutoIrisAverageFrame(_uint32_t nVal);
		
/*
			Description :
					Get value of Auto-iris averaging.
			Parameters :
					[OUT] pnVal : Current Auto-iris target value.
					[OUT, Optional] pnMin : Minimum Auto-iris target value.
					[OUT, Optional] pnMax : Maximum Auto-iris target value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Auto-iris is not supported in a camera.
					NEPTUNE_ERR_Fail
							Auto-iris target value set failed. 
*/
		ENeptuneError API_CALLTYPE GetAutoIrisTargetValue(_uint32_t* pnVal, _uint32_t* pnMin=NULL, _uint32_t* pnMax=NULL);

/*
			Description :
					Set value of Auto-iris averaging.
			Parameters :
					[IN] nVal : Auto-iris target value.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_NotSupport
							Auto-iris is not supported in a camera.
					NEPTUNE_ERR_Fail
							Auto-iris target value set failed.
*/
		ENeptuneError API_CALLTYPE SetAutoIrisTargetValue(_uint32_t nVal);

/*
			Description :
					Save camera setting value to a file.
			Parameters :
					[IN] strFile : Name of a file to be saving.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_InvalidParameter
							File name can not be NULL.
					NEPTUNE_ERR_Fail
							Camera setting save failed.
*/
		ENeptuneError API_CALLTYPE SaveCameraParameter(_char_t* pstrFile);

/*
			Description :
					Load camera setting value from a file.
			Parameters :
					[IN] strFile : Name of a file to be loading.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_NotInitialized
							Object of CCommonProperties class is not created.
					NEPTUNE_ERR_InvalidParameter
							File name can not be NULL.
					NEPTUNE_ERR_FileAccessError
						    File is not existed.
					NEPTUNE_ERR_Fail
							Camera setting load failed.
*/
		ENeptuneError API_CALLTYPE LoadCameraParameter(_char_t* pstrFile);

/*
			Description : 
					Show the camera control dialog.
			Parameters : 
					None.
			Return Values :
					None.
*/
		_void_t API_CALLTYPE ShowControlDialog();

/*
			Description :
				Convert YUVXXX format image data to RGB24 format image data.
			Parameters :
				[OUT] pOutput : Converted data.
				[IN] nBufSize : pOutput buffer's data size.
				[IN] pData : Grabbed data information.
			Return Values : 
				NEPTUNE_ERR_Success
						Success.
				NEPTUNE_ERR_NotInitialized
						Object of CCommonProperties class is not created.
				NEPTUNE_ERR_InvalidArraySize
						RGB buffer size is incorrect.
				NEPTUNE_ERR_Fail
						YUV to RGB24 convert is failed.
*/
		ENeptuneError API_CALLTYPE ConvertYUVToRGB24(_void_t* pOutput, _uint32_t nBufSize, CFrameDataPtr& pData);

/*
		Description :
			Convert raw data to YUV420 format image data.
		Parameters :
			[OUT] pOutput : YUV420 data.
			[IN] nBufSize : pOutput buffer's data size.
			[IN] pData : Grabbed data information.
		Return Values :
			NEPTUNE_ERR_Success
					Success.
			NEPTUNE_ERR_NotInitialized
					Object of CCommonProperties class is not created.
			NEPTUNE_ERR_InvalidArraySize
					YUV420 buffer size is incorrect.
			NEPTUNE_ERR_Fail
*/
		ENeptuneError API_CALLTYPE ConvertRawToYUV420(_void_t* pOutput, _uint32_t nBufSize, CFrameDataPtr& pData);

/*
			Description :
				Rotate for a image data to clockwise.
			Parameters :
				[IN] eAngle : Angle information.
			Return Values :
				NEPTUNE_ERR_Success
					Success.
				NEPTUNE_ERR_NotInitialized
					Object of CCommonProperties class is not created.
				
*/
		ENeptuneError API_CALLTYPE SetRotate(ENeptuneRotationAngle eAngle);

		ENeptuneError API_CALLTYPE GetPixelFormatList(vector<ENeptunePixelFormat>& List);
		ENeptuneError API_CALLTYPE GetPixelFormatList(vector<string>& List);
		ENeptuneError API_CALLTYPE GetFrameRateList(vector<ENeptuneFrameRate> &List);
		ENeptuneError API_CALLTYPE GetFrameRateList(vector<string> &List);	 

//2015-08-19
		ENeptuneError API_CALLTYPE SetBayer_NET(_void_t* pOutput, _uint32_t nOutputSize,
			_int64_t* pBuffer, _int32_t nIdx, _uint32_t nWidth, _uint32_t nHeight, _uint32_t nBufSize, ENeptunePixelFormat ePixelFormat, ENeptuneRotationAngle eAngle, 
			ENeptuneBayerLayout eLayout, ENeptuneBayerMethod eMethod, _uint32_t nEffect);
//2015-08-20		
		ENeptuneError API_CALLTYPE SetEffect_NET(_void_t* pOutput, _uint32_t nOutputSize, 
			_int64_t* pBuffer, _int32_t nIdx, _uint32_t nWidth, _uint32_t nHeight, _uint32_t nBufSize, ENeptunePixelFormat ePixelFormat, ENeptuneRotationAngle eAngle,
			_uint32_t nEffect);

//2015-08-20
		ENeptuneError API_CALLTYPE ConvertYUVToRGB24_NET(_void_t* pOutput, _uint32_t nOutputSize, 
			_int64_t* pBuffer, _int32_t nIdx, _uint32_t nWidth, _uint32_t nHeight, _uint32_t nBufSize, ENeptunePixelFormat ePixelFormat, ENeptuneRotationAngle eAngle );

//2015-09-07
		ENeptuneError API_CALLTYPE ConvertRawToYUV420_NET(_void_t* pOutput, _uint32_t nOutputSize, 
			_int64_t* pBuffer, _int32_t nIdx, _uint32_t nWidth, _uint32_t nHeight, _uint32_t nBufSize, ENeptunePixelFormat ePixelFormat );

//2016-02-18
		_uint32_t API_CALLTYPE GetDataBit();

//2017-08-30
		ENeptuneError API_CALLTYPE RunSoftwareTriggerEx(DWORD dwTimeout=0);

	protected:
		CCommonProperties();
		~CCommonProperties();

	private:
		friend class CDeviceManager;
		friend class CCameraInstance;

		class CCommonPropImpl;	
		CCommonPropImpl* m_pCommonPropImpl;

	};
}

#endif /*NEPTUNE_COMMONPROPERTIES_H*/