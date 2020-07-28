//------------------------------------------------------------------------------
// StApi
//------------------------------------------------------------------------------
/*!
	@ingroup	StApiIP_PublicImpl
	@file	StApi_IP.h
	@~english	@details	Include file for using StApi Image Processing module
	@~japanese	@details	StApi画像処理モジュール用インクルードファイル
*/
#ifndef STAPI_IP_H__
#define STAPI_IP_H__

//---------------------------------------------------------------------
//Converter
//---------------------------------------------------------------------
#include "IStPixelFormatConverter.h"
#include "IStReverseConverter.h"

//---------------------------------------------------------------------
//Filter
//---------------------------------------------------------------------
#include "IStGammaCorrectionFilter.h"
#include "IStColorTransformationFilter.h"
#include "IStEdgeEnhancementFilter.h"
#include "IStBalanceRatioFilter.h"
#include "IStSNMeasurementFilter.h"
#include "IStNoiseReductionFilter.h"
#include "IStFlatFieldCorrectionFilter.h"
#include "IStChromaSuppressionFilter.h"

//---------------------------------------------------------------------
//Filer
//---------------------------------------------------------------------
#include "IStStillImageFiler.h"
#include "IStVideoFiler.h"

#ifndef STSDK_IP_EXPORTS
#pragma comment(lib, ST_FILE_NAME("STApi_IP", ".lib"))
#endif

#include "StApi_IPFunctions.h"

#endif //STAPI_IP_H__
