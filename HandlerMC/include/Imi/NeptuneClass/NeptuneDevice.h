#ifndef NEPTUNE_NEPTUNEDEVICE_H
#define NEPTUNE_NEPTUNEDEVICE_H

#include "NeptuneClassLib.h"

namespace NeptuneClassLib
{
	////////////////////////////////////////////////////////////////////////////////////////
	//				
	//								Camera Informatoin
	//
	////////////////////////////////////////////////////////////////////////////////////////
	interface NEPTUNE_CLASS_API INeptuneDevice
	{
	public:
		virtual _char_t* API_CALLTYPE GetSerialNumber() = 0;
		virtual _char_t* API_CALLTYPE GetVendorName() = 0;
		virtual _char_t* API_CALLTYPE GetModelName() = 0;
		virtual _char_t* API_CALLTYPE GetUserID() = 0;
		virtual _char_t* API_CALLTYPE GetMacAddress() = 0;
		virtual _char_t* API_CALLTYPE GetIPAddress() = 0;
		virtual _char_t* API_CALLTYPE GetSubnet() = 0;
		virtual _char_t* API_CALLTYPE GetGateway() = 0;
		virtual ENeptuneDevType API_CALLTYPE GetDeviceType() = 0;

	protected:

	private:

	};
}

#endif /*NEPTUNE_NEPTUNEDEVICE_H*/
