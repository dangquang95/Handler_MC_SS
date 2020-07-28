#pragma once
#ifndef MIEHTNERNET_H
#define MIEHTNERNET_H
#include "StdAfx.h"
class IMEthernet
{

public:
	virtual int ReadData(CString& str, CString strMateIP = "") = 0;

	virtual void RequesStartRunVisionUnitbox2(int iUnit)=0;
	virtual void RequesFocus(int iUnit)=0;
	virtual BOOL IsAllConnected() = 0;
	virtual int ReadData(CString & str, int iUnit) = 0;
	//virtual void ReadDataAll(CString & str, int iLine, int iUnit) = 0;
	virtual void RequestUnitbox2(int iUnit) = 0;
	virtual BOOL IsSended(int iUnit) = 0;

	virtual int startServerSendFile() = 0;
	virtual void ThreadModeSendFileStop() = 0;
};
#endif // !MIEHTNERNET_H
