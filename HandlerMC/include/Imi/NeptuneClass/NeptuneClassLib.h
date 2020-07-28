#ifndef NEPTUNE_CLASS_LIB_H
#define NEPTUNE_CLASS_LIB_H

#include "NeptuneDef.h"


#if defined(_NEPTUNE_CLASS_API_EXPORTS)
	#define NEPTUNE_CLASS_API __declspec(dllexport)
#else
	#define NEPTUNE_CLASS_API __declspec(dllimport)
#endif

#define	API_CALLTYPE	  __stdcall


enum ENeptuneEventID
{
	NEPTUNE_EVENT_DISCONNECT			= 0x01,
	NEPTUNE_EVENT_CONNECT				= 0x02,
	NEPTUNE_EVENT_IMAGERECEIVED			= 0x04,				// not used..
	NEPTUNE_EVENT_FRAMEDROP				= 0x08,
	NEPTUNE_EVENT_RECVTIMEOUT			= 0x10
};

enum ENeptuneGrabMode
{
	NEPTUNE_GRAB_CONTINUOUS				= 0,
	NEPTUNE_GRAB_ONE					= 1,
};

////////////////////////////////////////////////////////////////////////////////////////
//				
//								Neptune class library global function
//
////////////////////////////////////////////////////////////////////////////////////////
namespace NeptuneClassLib
{	
/*
			Description :
					Initialize Neptune class library.
			Parameters :
			        None.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_AlreadyInitialized
							Neptune class library initialize is already completed.
					NEPTUNE_ERR_Timeout
							Discovery is failed.
					NEPTUNE_ERR_APINotInitialized
							Neptune class library initialize is failed.
*/
	NEPTUNE_CLASS_API ENeptuneError API_CALLTYPE InitLibrary();

/*
			Description : 
					Clear Neptune class library.
			Parameters :
					None.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_APINotInitialized
							To begin with UninitNeptuneLibrary function, call InitNeptuneLibray first.
*/
	NEPTUNE_CLASS_API ENeptuneError API_CALLTYPE UninitLibrary();

/*
			Description :
					Set level of log and file path of log.
			Parameters :
					[IN] strLogFile : Log file path.
					[IN] eLogLevel : Log level.
			Return Values :
					NEPTUNE_ERR_Success
							Success.
					NEPTUNE_ERR_FileAccessError
							Default log path is D:\. 
*/
}

#include <iostream>
using namespace std;
#include <vector>

#endif /* NEPTUNE_CLASS_LIB_H */