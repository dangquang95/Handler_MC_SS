//______________________________________________________________________________

// [] FileName: IniFile.cpp
// [] History :
//______________________________________________________________________________

#include "stdafx.h"
#include "IniFile.h"

//______________________________________________________________________________

CIniFile::CIniFile()
{
	Path = _T("");
}

//______________________________________________________________________________
CIniFile::~CIniFile()
{
}

//______________________________________________________________________________

int CIniFile::ReadInt(CString strSection, CString strKey, int iDefault)
{
	int iVal = GetPrivateProfileInt(strSection, strKey, iDefault, Path);
	return iVal;
}

//______________________________________________________________________________

CString CIniFile::ReadString(CString strSection, CString strKey, CString strDefault)
{
	//char buff[LINE_LENGTH+1];
	TCHAR buff[LINE_LENGTH+1];
	ZeroMemory(buff,LINE_LENGTH+1);
	GetPrivateProfileString(strSection, strKey, strDefault, buff, LINE_LENGTH, Path);
	CString strVal = CString(buff);
	return strVal;
}

//______________________________________________________________________________

CString CIniFile::ReadString(CString strSection, int no, CString strDefault)
{
	CString strKey = _T("");
	strKey.Format(_T("%d"), no);
	CString strVal = ReadString(strSection, strKey, strDefault);
	return strVal;
}

//______________________________________________________________________________

float CIniFile::ReadFloat(CString strSection, CString strKey, float fDefault)
{
	CString strDefault = _T("");
	strDefault.Format(_T("%f"), fDefault);
	CString strVal = ReadString(strSection, strKey, strDefault);
	float fVal = 0;
	//_stscanf(strVal,_T("%f"), &fVal);
	sscanf_s(strVal,_T("%f"), &fVal);

	return fVal;
}

//______________________________________________________________________________

double CIniFile::ReadDouble(CString strSection, CString strKey, double dDefault)
{
	CString strDefault = _T("");
	strDefault.Format(_T("%lf"), dDefault);
	CString strVal = ReadString(strSection, strKey, strDefault);
	double dVal = 0;
	//_stscanf(strVal,_T("%lf"), &dVal);
	sscanf_s(strVal,_T("%lf"), &dVal);

	return dVal;
}

//______________________________________________________________________________

int CIniFile::ReadHex(CString strSection, CString strKey, int iDefault)
{
	CString strDefault = ("");
	strDefault.Format(("%X"), iDefault);
	CString strVal = ReadString(strSection, strKey, strDefault);
	int iVal = 0;	
	//_stscanf(strVal, _T("%X"), &iVal);
	sscanf_s(strVal, ("%X"), &iVal);
	return iVal;
}

int CIniFile::ReadHex(CString strSection, int strKey, int iDefault)
{
	CString strDefault = _T("");
	strDefault.Format(_T("%X"), iDefault);
	
	CString Key = _T("");
	Key.Format(_T("%d"), strKey);

	CString strVal = ReadString(strSection, Key, strDefault);
	int iVal = 0;	
	
	//_stscanf(strVal, _T("%X"), &iVal);
	sscanf_s(strVal, _T("%X"), &iVal);
	return iVal;
}

//______________________________________________________________________________

BOOL CIniFile::WriteInt(CString strSection, CString strKey, int iVal)
{
	CString strVal = _T("");
	strVal.Format(_T("%d"), iVal);
	return WriteString(strSection, strKey, strVal);
	
}

//______________________________________________________________________________

BOOL CIniFile::WriteString(CString strSection, CString strKey, CString strVal)
{
	return WritePrivateProfileString(strSection, strKey, strVal, Path);
}

//______________________________________________________________________________

BOOL CIniFile::WriteString(CString strSection, int no, CString strVal)
{
	CString strKey = _T("");
	strKey.Format(_T("%d"), no);
	return WriteString(strSection, strKey, strVal);
}

//______________________________________________________________________________

BOOL CIniFile::WriteFloat(CString strSection, CString strKey, float fVal)
{
	CString strVal = _T("");
	strVal.Format(_T("%f"), fVal);
	return WriteString(strSection, strKey, strVal);
}

//______________________________________________________________________________

BOOL CIniFile::WriteDouble(CString strSection, CString strKey, double dVal)
{
	CString strVal = _T("");
	strVal.Format(_T("%lf"), dVal);
	return WriteString(strSection, strKey, strVal);
}

//______________________________________________________________________________

BOOL CIniFile::WriteHex(CString strSection, CString strKey, int iVal)
{
	CString strVal = _T("");
	strVal.Format(_T("%X"), iVal);
	return WriteString(strSection, strKey, strVal);
}

//______________________________________________________________________________


