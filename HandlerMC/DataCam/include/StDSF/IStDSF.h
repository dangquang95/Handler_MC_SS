//------------------------------------------------------------------------------
//  IStDSF.h
//------------------------------------------------------------------------------
/*!
@ingroup	StDSF_PublicImpl
@file
@~english	@details	Include file for using StDSF.
@~japanese	@details	StDSF用インクルードファイル
*/
#pragma once

#include <StApi_TL.h>   //Transport Layer
#include <StApi_IP.h>   //Image Processing
#include <StApi_GUI.h>  //GUI

#ifdef __cplusplus
extern "C" {
#endif

#define SPECIFIC_STDSF_DEVICE_MAXIMUM_COUNT	10
	//
	// StDSF Video Input Device
	//// {022DB6DA-A8D2-4fa6-A5FB-15546A13CBAF}
	DEFINE_GUID(CLSID_StGeneralCamera, 0x22db6da, 0xa8d2, 0x4fa6, 0xa5, 0xfb, 0x15, 0x54, 0x6a, 0x13, 0xcb, 0xaf);
	// {05417B93-20AB-41e5-B26E-04F07030A54E}
	DEFINE_GUID(CLSID_StDetectedCamera1, 0x5417b93, 0x20ab, 0x41e5, 0xb2, 0x6e, 0x4, 0xf0, 0x70, 0x30, 0xa5, 0x4e);
	// {057AA587-ADB3-4deb-B135-C0CC1E6EB841}
	DEFINE_GUID(CLSID_StDetectedCamera2, 0x57aa587, 0xadb3, 0x4deb, 0xb1, 0x35, 0xc0, 0xcc, 0x1e, 0x6e, 0xb8, 0x41);
	// {05A0B5C2-D7E5-4b64-93E0-342B243DD205}
	DEFINE_GUID(CLSID_StDetectedCamera3, 0x5a0b5c2, 0xd7e5, 0x4b64, 0x93, 0xe0, 0x34, 0x2b, 0x24, 0x3d, 0xd2, 0x5);
	// {09FB62DA-25DF-4512-9CD2-BDCDA0E65FAE}
	DEFINE_GUID(CLSID_StDetectedCamera4, 0x9fb62da, 0x25df, 0x4512, 0x9c, 0xd2, 0xbd, 0xcd, 0xa0, 0xe6, 0x5f, 0xae);
	// {0B1BC456-F329-4913-9609-0C18B30233CA}
	DEFINE_GUID(CLSID_StDetectedCamera5, 0xb1bc456, 0xf329, 0x4913, 0x96, 0x9, 0xc, 0x18, 0xb3, 0x2, 0x33, 0xca);
	// {0C1EB0E1-9687-4423-A126-EA810A7B70FA}
	DEFINE_GUID(CLSID_StDetectedCamera6, 0xc1eb0e1, 0x9687, 0x4423, 0xa1, 0x26, 0xea, 0x81, 0xa, 0x7b, 0x70, 0xfa);
	// {0C83EE16-FA3E-4125-8A28-2EF9A684E0CB}
	DEFINE_GUID(CLSID_StDetectedCamera7, 0xc83ee16, 0xfa3e, 0x4125, 0x8a, 0x28, 0x2e, 0xf9, 0xa6, 0x84, 0xe0, 0xcb);
	// {0C9293CC-D8E3-47af-8289-D6C37979DF71}
	DEFINE_GUID(CLSID_StDetectedCamera8, 0xc9293cc, 0xd8e3, 0x47af, 0x82, 0x89, 0xd6, 0xc3, 0x79, 0x79, 0xdf, 0x71);
	// {0D2D2125-64BB-46c8-AA96-0C54775EFC3F}
	DEFINE_GUID(CLSID_StDetectedCamera9, 0xd2d2125, 0x64bb, 0x46c8, 0xaa, 0x96, 0xc, 0x54, 0x77, 0x5e, 0xfc, 0x3f);
	// {0D58C3B8-BF9B-47be-8D83-B47DEC621D41}
	DEFINE_GUID(CLSID_StDetectedCamera10, 0xd58c3b8, 0xbf9b, 0x47be, 0x8d, 0x83, 0xb4, 0x7d, 0xec, 0x62, 0x1d, 0x41);


	//
	// IStDSF Interface

	/*!
		@ingroup	StDSF_PublicImpl
		@~english	@details	IID_IStDSF GUID.
		@~japanese	@details	IID_IStDSF GUID値
	*/
	// {944A4488-FFBE-44ef-875B-639135A015BC}
	DEFINE_GUID(IID_IStDSF, 0x944a4488, 0xffbe, 0x44ef, 0x87, 0x5b, 0x63, 0x91, 0x35, 0xa0, 0x15, 0xbc);


	//-------------------------------------------------------------------------
	//Enumerator
	//-------------------------------------------------------------------------
	/*!
		@ingroup	StDSF_PublicImpl
		@enum EStInstanceCreationMode_t
		@~english	@brief	Enumerator for instance creation mode.
		@~english	@details	Enumerator for instance creation mode.
		@~japanese	@brief	インスタンス生成モード列挙子
		@~japanese	@details	インスタンス生成モード列挙子
	*/
	typedef enum
	{
		/*!
			@~english	@details	Normal
			@~japanese	@details	通常
		*/
		StInstanceCreationMode_Normal,

		/*!
			@~english	@details	Application1
			@~japanese	@details	アプリケーション1
		*/
		StInstanceCreationMode_Application1,

		/*!
			@~english	@details	Count of instance creation mode.
			@~japanese	@details	インスタンス生成モード数
		*/
		StInstanceCreationMode_Count
	}EStInstanceCreationMode_t, *PEStInstanceCreationMode_t;

	//---------------------------------------------------------------------
	// interface IStDSF
	//---------------------------------------------------------------------
	/*!
		@ingroup StDSF_PublicInterface
		@interface IStDSF
		@~english	@brief	Interface for StDSF object.
		@~english	@details	Interface for StDSF object.
		@~japanese	@brief	StDSF専用インターフェース
		@~japanese	@details	StDSF専用インターフェース
	*/
	DECLARE_INTERFACE_(IStDSF, IUnknown)
	{
		/*!
			@~english	@brief	Acquire registry path for saving and loading settings (under HKEY_CURRENT_USER).
			@~english	@details	Acquire registry path for saving and loading settings (under HKEY_CURRENT_USER).
			@~english	@param[out]	szName	Buffer pointer for storing the acquired registry path.
			@~english	@param[in]	nLength	Buffer size.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@brief	設定値の保存や読み込みに使用されるレジストリパス(HKEY_CURRENT_USER下)を取得します。
			@~japanese	@details	設定値の保存や読み込みに使用されるレジストリパス(HKEY_CURRENT_USER下)を取得します。
			@~japanese	@param[out]	szName	文字列取得用バッファポインター
			@~japanese	@param[in]	nLength	文字列バッファのサイズ(文字数).
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
		*/
		STDMETHOD(GetRegistryPath)(THIS_ wchar_t *szName, size_t nLength) PURE;

		/*!
			@~english	@brief	Save the current camera and image processing settings to registry.
			@~english	@details	Save the current camera and image processing settings to registry.
			@~english	@param[in]	szName	Setting name.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@brief	現在のカメラの設定やパソコン上で行われる画像処理の設定をレジストリへ保存します。
			@~japanese	@details	現在のカメラの設定やパソコン上で行われる画像処理の設定をレジストリへ保存します。
			@~japanese	@param[in]	szName	設定名
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
		*/
		STDMETHOD(SaveRegistry)(THIS_ wchar_t *szName) PURE;

		/*!
			@~english	@brief	Load the camera and image processing settings from the registry.
			@~english	@details	Load the camera and image processing settings from the registry.
			@~english	@param[in]	szName	Setting name.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@brief	レジストリに保存されているカメラの設定やパソコン上で行われる画像処理の設定をカメラへロードします。
			@~japanese	@details	レジストリに保存されているカメラの設定やパソコン上で行われる画像処理の設定をカメラへロードします。
			@~japanese	@param[in]	szName	設定名
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
		*/
		STDMETHOD(LoadRegistry)(THIS_ wchar_t *szName) PURE;

		/*!
			@~english	@brief	Set the default setting name whose data will be loaded when a camera is opened.
			@~english	@details	Set the default setting name whose data will be loaded when a camera is opened.
			@~english	@param[in]	szName	Setting name.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@brief	カメラオープン時に使用する初期設定名を設定します。
			@~japanese	@details	カメラオープン時に使用する初期設定名を設定します。
			@~japanese	@param[in]	szName	設定名
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
		*/
		STDMETHOD(SetDefaultRegistry)(THIS_ wchar_t *szName) PURE;

		/*!
			@~english	@brief	Get the default setting name whose data will be loaded when a camera is opened.
			@~english	@details	Get the default setting name whose data will be loaded when a camera is opened.
			@~english	@param[out]	szName	Buffer pointer for string.
			@~english	@param[in]	nLength	Buffer size.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@brief	カメラオープン時に使用する初期設定名を取得します。
			@~japanese	@details	カメラオープン時に使用する初期設定名を取得します。
			@~japanese	@param[out]	szName	文字列取得用バッファポインター
			@~japanese	@param[in]	nLength	文字列バッファのサイズ(文字数).
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
		*/
		STDMETHOD(GetDefaultRegistry)(THIS_ wchar_t *szName, size_t nLength) PURE;

		/*!
			@~english	@brief	Delete the setting data from the registry.
			@~english	@details	Delete the setting data from the registry.
			@~english	@param[in]	szName	Setting name.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@brief	設定データをレジストリから削除します。
			@~japanese	@details	設定データをレジストリから削除します。
			@~japanese	@param[in]	szName	設定名
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
		*/
		STDMETHOD(DeleteRegistry)(THIS_ wchar_t *szName) PURE;

		/*!
			@~english	@brief	Import the setting data from a file to the registry.
			@~english	@details	Import the setting data from a file to the registry.
			@~english	@param[in]	szFileName	File name.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@brief	設定データをファイルからレジストリへ取り込みます。
			@~japanese	@details	設定データをファイルからレジストリへ取り込みます。
			@~japanese	@param[in]	szFileName	ファイル名
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
		*/
		STDMETHOD(ImportRegistry)(THIS_ wchar_t *szFileName) PURE;

		/*!
			@~english	@brief	Export the setting data from the registry to a file.
			@~english	@details	Export the setting data from the registry to a file.
			@~english	@param[in]	szFileName	File name.
			@~english	@param[in]	szName	Setting name.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@brief	設定データをレジストリからファイルへ書き出します。
			@~japanese	@details	設定データをレジストリからファイルへ書き出します。
			@~japanese	@param[in]	szFileName	ファイル名
			@~japanese	@param[in]	szName	設定名
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
		*/
		STDMETHOD(ExportRegistry)(THIS_ wchar_t *szFileName, wchar_t *szName) PURE;

		/*!
		@~english	@brief	Acquire instance creation mode.
		@~english	@details	Acquire instance creation mode.
		@~english	@param[out]	pdwValue	Instance creation mode (0:Normal, 1:Application1)
		@~english	@return	HRESULT
		@~english	@exception	None.
		@~english @attention		Set to 0 (default) in normal situation. When the mode is set to 1, if an already opened camera is re-opened, the already opened camera will be used and the settings will be stored to registry.
		@~japanese	@brief	インスタンス生成モードを取得します。
		@~japanese	@details	インスタンス生成モードを取得します。
		@~japanese	@param[out]	pdwValue	インスタンス生成モード(0:通常, 1:アプリケーション1)
		@~japanese	@return	HRESULT
		@~japanese	@exception	なし
		@~japanese	@attention 通常は0(初期値)を設定してください。1に設定すると、カメラがオープンされる際に、すでにオープンされているカメラがある場合は、新たにカメラをオープンせずに既にオープンされているカメラが使用されるようになります。設定した内容はレジストリに保存されます。
		*/
		STDMETHOD(GetInstanceCreationMode) (THIS_ PDWORD pdwValue) PURE;

		/*!
		@~english	@brief	Set instance creation mode.
		@~english	@details	Set instance creation mode.
		@~english	@param[in]	dwValue	Instance creation mode (0:Normal, 1:Application1)
		@~english	@return	HRESULT
		@~english	@exception	None.
		@~japanese	@brief	インスタンス生成モードを設定します。
		@~japanese	@details	インスタンス生成モードを設定します。
		@~japanese	@param[in]	dwValue	インスタンス生成モード(0:通常, 1:アプリケーション1)
		@~japanese	@return	HRESULT
		@~japanese	@exception	なし
		*/
		STDMETHOD(SetInstanceCreationMode) (THIS_ DWORD dwValue) PURE;

		/*!
			@~english	@brief	Get total image size. When multi-ROI is enabled, the total image size is computed from the combined multi-ROI images.
			@~english	@details	Get total image size. When multi-ROI is enabled, the total image size is computed from the combined multi-ROI images.
			@~english	@param[out]	piWidth	Width of the image.
			@~english	@param[out]	piHeight	Height of the image.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@brief	全体の画像サイズを取得します。結合された長方形の画像が出力されるマルチROIが有効な場合、すべての領域を含んだサイズが取得されます。
			@~japanese	@details	全体の画像サイズを取得します。結合された長方形の画像が出力されるマルチROIが有効な場合、すべての領域を含んだサイズが取得されます。
			@~japanese	@param[out]	piWidth	画像の横サイズ
			@~japanese	@param[out]	piHeight	画像の縦サイズ
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
		*/
		STDMETHOD(GetWholeImageSize)(THIS_ int64_t *piWidth, int64_t *piHeight) PURE;

		/*!
			@~english	@brief	Acquire IStInterface pointer. Please refer to StApi help file for details.
			@~english	@details	Acquire IStInterface pointer. Please refer to StApi help file for details.
			@~english	@param[out]	ppIStInterface	IStInterface interface pointer.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~english	@attention	CreateIStDevice and CreateFirstIStDevice methods are used by the DirectShow filter internally. Therefore, please do not use them directly in your application.
			@~japanese	@brief	IStInterface インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@details	IStInterface インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@param[out]	ppIStInterface	IStInterfaceインターフェースポインター
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
			@~japanese	@attention	CreateIStDevice, CreateFirstIStDevice メソッドはDirectShowフィルター内部で使用されますので、アプリケーションからは直接使用しないでください。
		*/
		STDMETHOD(GetIStInterface)(THIS_ StApi::IStInterface **ppIStInterface) PURE;

		/*!
			@~english	@brief	Acquire IStDevice pointer. Please refer to StApi help file for details.
			@~english	@details	Acquire IStDevice pointer. Please refer to StApi help file for details.
			@~english	@param[out]	ppIStDevice	IStDevice interface pointer.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~english	@attention	CreateIStDataStream, AcquisitionStart, and AcquisitionStop methods are used by the DirectShow filter internally. Therefore, please do not use them directly in your application.
			@~english	@attention	Pixel format conversion is performed inside DirectShow filter. Consequently, changing the format of image data through camera PixelFormat settings does not neccessarily change the format of the image output by the DirectShow filter.
			@~japanese	@brief	IStDevice インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@details	IStDevice インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@param[out]	ppIStDevice	IStDeviceインターフェースポインター
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
			@~japanese	@attention	CreateIStDataStream, AcquisitionStart, AcquisitionStop メソッドはDirectShowフィルター内部で使用されますので、アプリケーションからは直接使用しないでください。
			@~japanese	@attention	カメラのPixelFormatを変更しカメラから出力される画像データの形式が変化しても、DirectShowフィルター内で変換が行われるため、DirectShowフィルターから出力される画像データの形式は変化しません。
		*/
		STDMETHOD(GetIStDevice)(THIS_ StApi::IStDevice **ppIStDevice) PURE;

		/*!
			@~english	@brief	Acquire IStDataStream pointer. Please refer to StApi help file for details.
			@~english	@details	Acquire IStDataStream pointer. Please refer to StApi help file for details.
			@~english	@param[out]	ppIStDataStream	IStDataStream interface pointer.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~english	@attention	RetrieveBuffer, StartAcquisition, and StopAcquisition methods are used by the DirectShow filter internally. Therefore, please do not use them directly in your application.
			@~japanese	@brief	IStDataStream インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@details	IStDataStream インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@param[out]	ppIStDataStream	IStDataStreamインターフェースポインター
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
			@~japanese	@attention	RetrieveBuffer, StartAcquisition, StopAcquisition メソッドはDirectShowフィルター内部で使用されますので、アプリケーションからは直接使用しないでください。
		*/
		STDMETHOD(GetIStDataStream)(THIS_ StApi::IStDataStream **ppIStDataStream) PURE;

		/*!
			@~english	@brief	Acquire IStPixelFormatConverter pointer. Please refer to StApi help file for details.
			@~english	@details	Acquire IStPixelFormatConverter pointer. Please refer to StApi help file for details.
			@~english	@param[out]	ppIStPixelFormatConverter	IStPixelFormatConverter interface pointer.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@attention	Supported PixelFormat by SetDestinationPixelFormat are StPFNC_Mono8, StPFNC_BGR8, and StPFNC_BGRa8 only. Also, ReverseY cannot be used as it is used by the DirectShow filter internally.
			@~japanese	@brief	IStPixelFormatConverter インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@details	IStPixelFormatConverter インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@param[out]	ppIStPixelFormatConverter	IStPixelFormatConverterインターフェースポインター
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
			@~japanese	@attention	SetDestinationPixelFormat で設定可能なPixelFormatは、StPFNC_Mono8, StPFNC_BGR8, StPFNC_BGRa8 のみとなります。また、ReverseY はDirectShowフィルター内部で使用されているため使用できません。
		*/
		STDMETHOD(GetIStPixelFormatConverter)(THIS_ StApi::IStPixelFormatConverter **ppIStPixelFormatConverter) PURE;

		/*!
			@~english	@brief	Acquire IStFlatFieldCorrectionFilter pointer. Please refer to StApi help file for details.
			@~english	@details	Acquire IStFlatFieldCorrectionFilter pointer. Please refer to StApi help file for details.
			@~english	@param[out]	ppIStFlatFieldCorrectionFilter	IStFlatFieldCorrectionFilter interface pointer.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@brief	IStFlatFieldCorrectionFilter インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@details	IStFlatFieldCorrectionFilter インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@param[out]	ppIStFlatFieldCorrectionFilter	IStFlatFieldCorrectionFilterインターフェースポインター
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
		*/
		STDMETHOD(GetIStFlatFieldCorrectionFilter)(THIS_ StApi::IStFlatFieldCorrectionFilter **ppIStFlatFieldCorrectionFilter) PURE;

		/*!
			@~english	@brief	Acquire IStColorTransformationFilter pointer. Please refer to StApi help file for details.
			@~english	@details	Acquire IStColorTransformationFilter pointer. Please refer to StApi help file for details.
			@~english	@param[out]	ppIStColorTransformationFilter	IStColorTransformationFilter interface pointer.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@brief	IStColorTransformationFilter インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@details	IStColorTransformationFilter インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@param[out]	ppIStColorTransformationFilter	IStColorTransformationFilterインターフェースポインター
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
		*/
		STDMETHOD(GetIStColorTransformationFilter)(THIS_ StApi::IStColorTransformationFilter **ppIStColorTransformationFilter) PURE;

		/*!
			@~english	@brief	Acquire IStEdgeEnhancementFilter pointer. Please refer to StApi help file for details.
			@~english	@details	Acquire IStEdgeEnhancementFilter pointer. Please refer to StApi help file for details.
			@~english	@param[out]	ppIStEdgeEnhancementFilter	IStEdgeEnhancementFilter interface pointer.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@brief	IStEdgeEnhancementFilter インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@details	IStEdgeEnhancementFilter インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@param[out]	ppIStEdgeEnhancementFilter	IStEdgeEnhancementFilterインターフェースポインター
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
		*/
		STDMETHOD(GetIStEdgeEnhancementFilter)(THIS_ StApi::IStEdgeEnhancementFilter **ppIStEdgeEnhancementFilter) PURE;

		/*!
			@~english	@brief	Acquire IStGammaCorrectionFilter pointer. Please refer to StApi help file for details.
			@~english	@details	Acquire IStGammaCorrectionFilter pointer. Please refer to StApi help file for details.
			@~english	@param[out]	ppIStGammaCorrectionFilter	IStGammaCorrectionFilter interface pointer.
			@~english	@return	HRESULT
			@~english	@exception	None.
			@~japanese	@brief	IStGammaCorrectionFilter インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@details	IStGammaCorrectionFilter インターフェースポインターを取得します。詳細につきましてはStApiのヘルプファイルをご参照ください。
			@~japanese	@param[out]	ppIStGammaCorrectionFilter	IStGammaCorrectionFilterインターフェースポインター
			@~japanese	@return	HRESULT
			@~japanese	@exception	なし
		*/
		STDMETHOD(GetIStGammaCorrectionFilter)(THIS_ StApi::IStGammaCorrectionFilter **ppIStGammaCorrectionFilter) PURE;

	};



#ifdef __cplusplus
}
#endif